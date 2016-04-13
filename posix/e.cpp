#include <iostream>
#include <iomanip>
#include <chrono>
#include <pthread.h>

#define NUM_THREADS 2
using namespace std;
using namespace std::chrono;

pthread_mutex_t mutex;
typedef long double ld;
const ld dx = 0.000000001l;
ld sum[NUM_THREADS];
ld a[NUM_THREADS];

ld p_sum(){
	ld s = 0.0l;
	for(int i=0; i< NUM_THREADS; ++i) s+= sum[i];
	return s;
}

ld p_e(){
	ld s = 0.0l;
	for(int i=0; i< NUM_THREADS; ++i) s+= a[i];
	return s;
}
ld max_e(){
	ld s = a[0];
	for(int i=0; i< NUM_THREADS; ++i) {
		if( a[i] > s)
			s = a[i];
	}
	return s;
}
ld calcula() {
	ld sum = 0.0;
	ld a = 1.0;
	while (sum <= 1.0) {
		sum += dx/a ;
		a += dx;
	}
	return a;
}
void* hiloCalculo(void* threadid) {
	long id =  *((int*)threadid);
	cout<<"thread id: "<<id<<endl;
	while (p_sum() <= 1.0) {
		sum[id] += dx/a[id];
		a[id] = max_e()+dx;
	}
	cout <<"p_sum: "<<p_sum() << endl;
	return NULL;
}
void init(){
	for(int i=0; i < NUM_THREADS; ++i){
		a[i]=1.0;
		sum[i]=0.0;
	}
}
void calculaHilos() {
	init();
	pthread_t threads[NUM_THREADS];
	int ids[NUM_THREADS];
	//pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < NUM_THREADS; ++i) {
		ids[i]=i;
		pthread_create(&threads[i], NULL, hiloCalculo, (void *)&ids[i]);
	}for (int i = 0; i < NUM_THREADS; ++i) {
		pthread_join(threads[i], NULL);
	}	
}

int main() {
	high_resolution_clock::time_point t1, t2;
	/*t1 = high_resolution_clock::now();
	ld e=calcula();
	t2 = high_resolution_clock::now();
	auto duration2 = duration_cast<microseconds>(t2 - t1).count();
	cout << "e: " << setprecision(12) << e << endl;
	cout << "Normal: " << duration2 << " micro seg." << endl;
*/
	t1 = high_resolution_clock::now();
	calculaHilos();
	t2 = high_resolution_clock::now();
	auto duration1 = duration_cast<microseconds>(t2 - t1).count();
	cout << "e: " << setprecision(12) << p_e() << endl;
	cout << "Paralelo: " << duration1 << " micro seg." << endl;
	getchar();
	return 0;
}