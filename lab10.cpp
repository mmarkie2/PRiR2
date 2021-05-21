#include "lab10.h"

#include <iostream>
#include "omp.h"

using namespace std;

void lab10_uruchomienie() {
  cwiczenie_1_1(); //bez MP
  cwiczenie_1_2(); //z MP
  cwiczenie_2();
  cwiczenie_3_1();
  cwiczenie_3_2();
  cwiczenie_3_3();
  cwiczenie_4();
  cwiczenie_5();
}


void mxv(int m, int n, double * a, double * b, double * c) {
  int i,j;
  for(i = 0; i < m; i++) {
    a[i] = 0.0;
    //pętla obliczająca iloczyn i-tego wiesza macierzy b
    //i wektora c; wynikime jest i-ty element wektora a
    for(j = 0; j < n; j++){
      a[i] += b[i*n+j] * c[j]; //a[i] = b[i][j] * c[j]
    }
  }
}

#define M 16
#define N 16

void cwiczenie_1_1() { //bez OpenMP

  cout << endl << "--- cwiczenie_1_1" << endl;
  
  double A[M], B[M*N], C[N];
  int k, l;
  
  //inicjalizujemy macierz B oraz wektor C
  for(k = 0; k < M; k++){
    for(l = 0; l < N; l++) {
      C[l] = l * 1.0;
      B[k*N + l] = l*0.1 + k;
    }
  }

  //obliczamy wektor A 
  mxv(M, N, A, B, C);

  cout.precision(1);
  cout << fixed;

  for(k = 0; k < M; k++){
    cout << A[k] << " ";
  }

  cout << endl;
}

void mxv_mp(int m, int n, double * a, double * b, double * c) {
  int i,j;

  #pragma omp paraller for
  for(i = 0; i < m; i++) {
    a[i] = 0.0;
    //pętla obliczająca iloczyn i-tego wiesza macierzy b
    //i wektora c; wynikime jest i-ty element wektora a
    #pragma omp paraller for
    for(j = 0; j < n; j++){
      a[i] += b[i*n+j] * c[j]; //a[i] = b[i][j] * c[j]
    }
  }
}



void cwiczenie_1_2() { //to co w cwiczenie_1_1, ale zrównoleglone

  cout << endl << "--- cwiczenie_1_2" << endl;

  double A[M], B[M*N], C[N];
  int k, l;
  
  //inicjalizujemy macierz B oraz wektor C
  for(k = 0; k < M; k++){
    for(l = 0; l < N; l++) {
      C[l] = l * 1.0;
      B[k*N + l] = l*0.1 + k;
    }
  }

  //obliczamy wektor A 
  mxv_mp(M, N, A, B, C);

  cout.precision(1);
  cout << fixed;

  for(k = 0; k < M; k++){
    cout << A[k] << " ";
  }

  cout << endl;



}

void matmul(int m, int n, double * a, double * b, double * c) {
  int i,j,l;

  #pragma omp paraller for
  for(i = 0; i < m; i++) {
  
    #pragma omp paraller for
    for(j = 0; j < n; j++){
      for(l = 0; l < n; l++){
      a[i*m+j] += b[i*m+l] * c[l*n+j]; 
    }
    }
  }
}

void cwiczenie_2() {

  cout << endl << "--- cwiczenie_2" << endl;

 
  double A[M], B[M*N], C[N];
  int k, l;
  
  //inicjalizujemy macierz B oraz wektor C
  for(k = 0; k < M; k++){
    for(l = 0; l < N; l++) {
      C[l] = l * 1.0;
      B[k*N + l] = l*0.1 + k;
    }
  }

  //obliczamy wektor A 
  matmul(M, N, A, B, C);

  cout.precision(1);
  cout << fixed;

  for(k = 0; k < M; k++){
    cout << A[k] << " ";
  }

  cout << endl;

}

void cwiczenie_3_1() {

  cout << endl << "--- cwiczenie_3_1" << endl;

 int tab[]={1,2,3,4,5,6,7,8,9,10};
 long int a =-1;

}

void cwiczenie_3_2() {

  cout << endl << "--- cwiczenie_3_2" << endl;

  cout << "  DO ZROBIENIA !!!" << endl;

}

void cwiczenie_3_3() {

  cout << endl << "--- cwiczenie_3_3" << endl;

  cout << "  DO ZROBIENIA !!!" << endl;


}

void cwiczenie_4() {

  cout << endl << "--- cwiczenie_4" << endl;

  cout << "  DO ZROBIENIA !!!" << endl;

}

void cwiczenie_5() {

  cout << endl << "--- cwiczenie_5" << endl;

  cout << "  DO ZROBIENIA !!!" << endl;

}