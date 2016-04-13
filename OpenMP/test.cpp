#include <iostream>
#include <cmath>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(){
	clock_t t = clock();
	long N = 100000000;
	int sum=0;
	auto begin = steady_clock::now();
    

	for(int i=0; i < N;++i){
		sqrt(i)*sqrt(i);
		pow(i,3);
		sqrt(i)*sqrt(i);
		pow(i,3);
		sqrt(i)*sqrt(i);
		pow(i,3);
		sqrt(i)*sqrt(i);
		pow(i,3);
	}
	auto end = steady_clock::now();
    auto dur = duration_cast<microseconds>(end - begin).count();
	cout << "Time taken: "<< setprecision(4) << dur<<" µs"<< endl;

	begin = steady_clock::now();
		

	int i;
	#pragma omp parallel for private(i)  schedule(static)
	for(i=0; i < N;++i){
		sqrt(i)*sqrt(i);
		pow(i,3);
		sqrt(i)*sqrt(i);
		pow(i,3);
		sqrt(i)*sqrt(i);
		pow(i,3);
		sqrt(i)*sqrt(i);
		pow(i,3);
	}
	end = steady_clock::now();
    dur = duration_cast<microseconds>(end - begin).count();
	cout << "Time taken: "<< setprecision(4) << dur <<" µs"<< endl;

	return 0;
}