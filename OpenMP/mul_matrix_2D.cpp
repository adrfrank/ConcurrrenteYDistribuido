#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

#define show_init 0

using namespace std;
using namespace std::chrono;



int mult_mat2d(int m, int n, int p, float** a, float** b, float** c)
{
   int i,j,k;
#pragma omp parallel shared(a,b,c) private(i,j,k) 
   {
#pragma omp for  schedule(static)
   for (i=0; i<m; i=i+1){
      for (j=0; j<n; j=j+1){
         a[i][j]=0.;
         for (k=0; k<p; k=k+1){
            a[i][j]=(a[i][j])+((b[i][k])*(c[k][j]));
         }
      }
   }
   }
   return 0;
}

void init_random_mat2d(int a, int b, float ** &m){
   m = new float*[a];
   for(int i=0; i < a; ++i){
      m[i]= new float[b];
      for(int j=0; j < b; ++j){
         m[i][j] = rand() % 100;
         if(show_init)
            cout << m[i][j]<< " ";
      }
      if(show_init)
      cout <<endl;

   }
      if(show_init)
      cout <<endl;

}

void print_mat2d(int a,int b,float** &m){
   for(int i=0; i < a; ++i){
      for(int j=0; j < b; ++j){
         cout << m[i][j]<< " ";
      }
      cout <<endl;
   }
}

int main(){
   srand (time(NULL));
   int tam = 1000;

   float**m1, **m2, **m3;
   init_random_mat2d(tam,tam,m1);
   init_random_mat2d(tam,tam,m2);
   init_random_mat2d(tam,tam,m3);
   cout << "Init "<<tam<<" x "<<tam << " matrix"<<endl;
   auto begin = steady_clock::now();

   mult_mat2d(tam,tam,tam,m1,m2,m3);

   auto end = steady_clock::now();
   auto dur = duration_cast<microseconds>(end - begin).count();
   //print_mat2d(tam,tam,m1);
   cout << "Time taken: "<< setprecision(4) << dur<<" µs"<< endl;

   return 0;
}