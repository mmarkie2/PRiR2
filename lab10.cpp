#include "lab10.h"

#include <iostream>
#include "omp.h"
#include <chrono>
#include <thread>
#include <cmath>

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


void mxv(int m, int n, double *a, double *b, double *c) {
    int i, j;
    for (i = 0; i < m; i++) {
        a[i] = 0.0;
        //pętla obliczająca iloczyn i-tego wiesza macierzy b
        //i wektora c; wynikime jest i-ty element wektora a
        for (j = 0; j < n; j++) {
            a[i] += b[i * n + j] * c[j]; //a[i] = b[i][j] * c[j]
        }
    }
}

#define M 16
#define N 16

void cwiczenie_1_1() { //bez OpenMP

    cout << endl << "--- cwiczenie_1_1" << endl;

    double A[M], B[M * N], C[N];
    int k, l;

    //inicjalizujemy macierz B oraz wektor C
    for (k = 0; k < M; k++) {
        for (l = 0; l < N; l++) {
            C[l] = l * 1.0;
            B[k * N + l] = l * 0.1 + k;
        }
    }

    //obliczamy wektor A
    mxv(M, N, A, B, C);

    cout.precision(1);
    cout << fixed;

    for (k = 0; k < M; k++) {
        cout << A[k] << " ";
    }

    cout << endl;
}

void mxv_mp(int m, int n, double *a, double *b, double *c) {
    int i, j;

#pragma omp paraller for
    for (i = 0; i < m; i++) {
        a[i] = 0.0;
        //pętla obliczająca iloczyn i-tego wiesza macierzy b
        //i wektora c; wynikime jest i-ty element wektora a
#pragma omp paraller for
        for (j = 0; j < n; j++) {
            a[i] += b[i * n + j] * c[j]; //a[i] = b[i][j] * c[j]
        }
    }
}


void cwiczenie_1_2() { //to co w cwiczenie_1_1, ale zrównoleglone

    cout << endl << "--- cwiczenie_1_2" << endl;

    double A[M], B[M * N], C[N];
    int k, l;

    //inicjalizujemy macierz B oraz wektor C
    for (k = 0; k < M; k++) {
        for (l = 0; l < N; l++) {
            C[l] = l * 1.0;
            B[k * N + l] = l * 0.1 + k;
        }
    }

    //obliczamy wektor A
    mxv_mp(M, N, A, B, C);

    cout.precision(1);
    cout << fixed;

    for (k = 0; k < M; k++) {
        cout << A[k] << " ";
    }

    cout << endl;


}

void matmul(int m, int n, double *a, double *b, double *c) {
    int i, j, l;

#pragma omp paraller for
    for (i = 0; i < m; i++) {

#pragma omp paraller for
        for (j = 0; j < n; j++) {
            for (l = 0; l < n; l++) {
                a[i * m + j] += b[i * m + l] * c[l * n + j];
            }
        }
    }
}

void cwiczenie_2() {

    cout << endl << "--- cwiczenie_2" << endl;


    double A[M], B[M * N], C[N];
    int k, l;

    //inicjalizujemy macierz B oraz wektor C
    for (k = 0; k < M; k++) {
        for (l = 0; l < N; l++) {
            C[l] = l * 1.0;
            B[k * N + l] = l * 0.1 + k;
        }
    }

    //obliczamy wektor A
    matmul(M, N, A, B, C);

    cout.precision(1);
    cout << fixed;

    for (k = 0; k < M; k++) {
        cout << A[k] << " ";
    }

    cout << endl;

}

void cwiczenie_3_1() {

    cout << endl << "--- cwiczenie_3_1" << endl;

    int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, threads;
    long int a = -1;
    int a_thr = 1;
    threads = omp_get_num_procs();
    omp_set_num_threads(threads);

#pragma omp parallel firstprivate(a_thr) shared(a)
    {
#pragma omp for
        for (int i = 0; i < 10; i++) {
            a_thr *= tab[i];
        }
#pragma omp critical
        a *= a_thr;
    }
    cout << "a= " << a << endl;
}

void cwiczenie_3_2() {

    cout << endl << "--- cwiczenie_3_2" << endl;

    int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, threads;
    long int a = -1;
    int a_thr = 1;
    threads = omp_get_num_procs();
    omp_set_num_threads(threads);

#pragma omp parallel
    {
#pragma omp for reduction(*:a)
        for (int i = 0; i < 10; i++) {
            a *= tab[i];
        }

    }
    cout << "a= " << a << endl;

}

void cwiczenie_3_3() {

    cout << endl << "--- cwiczenie_3_3" << endl;

    int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, threads;
    long int a = -1, b = 0;
    int a_thr = 1;
    threads = omp_get_num_procs();
    omp_set_num_threads(threads);

#pragma omp parallel
    {
#pragma omp for reduction(+:b)
        for (int i = 0; i < 10; i++) {
            b = b + tab[i];
        }

    }
    cout << "b= " << b << endl;


}


void cwiczenie_4() {

    cout << endl << "--- cwiczenie_4" << endl;
   long int count = 999;
    int T[count];
    for (int i = 0; i < count; i++) {
        T[i] = (float(rand()) / RAND_MAX) * 10;
    }


    {
        // Record start time
        auto start = std::chrono::high_resolution_clock::now();


        int threads = omp_get_num_procs();
        omp_set_num_threads(threads);
        int sum=0;

#pragma omp parallel for reduction (+:sum)
            for (  long int i = 0; i < count; i++) {
                sum = sum + T[i];std::this_thread::sleep_for(chrono::milliseconds(10));
            }



// Record end time
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        cout << "czas sumowania wiele watkow: " << elapsed.count() <<"suma: "<<sum<< endl;

    }

    {
        // Record start time
        auto start = std::chrono::high_resolution_clock::now();


        int threads = omp_get_num_procs();
        omp_set_num_threads(threads);
        int sum=0;


            for (  long int i = 0; i < count; i++) {
                sum = sum + T[i];std::this_thread::sleep_for(chrono::milliseconds(10));
            }



// Record end time
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        cout << "czas sumowania jeden watek: " << elapsed.count() <<"suma: "<<sum<< endl;
    }

}

void cwiczenie_5() {

    cout << endl << "--- cwiczenie_5" << endl;

    int LICZBA_PUNKTOW = 20;
    double a = 0, b = 3.14;
    cout << "Wątek pracuje..." << endl;
    double h = (b - a) / LICZBA_PUNKTOW;
    double s = sin(a);
#pragma omp parallel
    {
#pragma omp for
        for (int i = 1; i < LICZBA_PUNKTOW; i++) {
            //lekkie spowolnienie wątku (wartość w milisekundach) //warto wypróbować różne wartości
            std::this_thread::sleep_for(chrono::milliseconds(10));
            s += 2 * sin(a + i * h);
        }
    }


    s += sin(b);
    int wynik = s * h / 2;
    cout << "Wątek się zakończył..." << "wynik: " << wynik << endl;

}