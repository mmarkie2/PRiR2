#include "lab09.h"

#include <iostream>
#include "omp.h"

using namespace std;

void lab09_uruchomienie() {
    //Tutaj zebrane wszystkie listingi
    cwiczenie_1_1();
    omp_set_num_threads(4);
    cwiczenie_1_2_a();
    cwiczenie_1_2_b();
    cwiczenie_1_2_c();

    listing_1_3_1();
    listing_1_3_2();
    listing_1_3_3();

    listing_1_4_1();
    listing_1_4_2();
    listing_1_4_3();

    listing_1_5_1();
    cwiczenie_1_5_1();
}

//---

void cwiczenie_1_1() {
    cout << endl << "--- cwiczenie_1_1" << endl;

    omp_set_num_threads(4);

#pragma omp parallel
    {
        cout << "Hello " << "World !" << endl;
    }

#pragma omp parallel
    {
#pragma omp critical
        {
            cout << "Witaj " << "Świecie !" << endl;
        }
    }

}

//---

void cwiczenie_1_2_a() {
    cout << endl << "--- cwiczenie_1_2_a" << endl;
    int numThreads = 3;
    omp_set_num_threads(numThreads);
#pragma omp parallel
    {
        cout << "Wątek  " << omp_get_thread_num() << " z " << omp_get_num_threads() << endl;
    }
}

void cwiczenie_1_2_b() {
    cout << endl << "--- cwiczenie_1_2_b" << endl;
    int numThreads = 3;
    omp_set_num_threads(numThreads);

#pragma omp parallel
    {
        cout << "W czesci sekwencyjnej działa Wątek  " + std::to_string(omp_get_thread_num()) + " z " +
                std::to_string(omp_get_num_threads()) + "\n";
#pragma omp critical
        {
            cout << "Wątek  " << omp_get_thread_num() << " z " << omp_get_max_threads() << endl;
        }
    }


}

void cwiczenie_1_2_c() {
    cout << endl << "--- cwiczenie_1_2_c" << endl;
    int numThreads = omp_get_num_procs();
    omp_set_num_threads(numThreads);
#pragma omp parallel
    {
        cout << "Wątek  " << omp_get_thread_num() << " z " << omp_get_num_threads() << endl;
    }

}

//---

void listing_1_3_1() {

    //START: Wątek główny
    cout << endl << "--- listing_1_3_1" << endl;

    //ROZDZIELENIE: Wypuszczenie 4 wątków
#pragma omp parallel num_threads(4)
    {
#pragma omp critical
        cout << "Wątek nr " << omp_get_thread_num() << " z " << omp_get_num_threads() << endl;
    }
    //BARIERA KOŃCZĄCA: Takie niejawine .join

    cout << endl;

    //ROZDZIELENIE: Wypuszczenie 2 wątków
#pragma omp parallel num_threads(2)
    {
#pragma omp cricical
        cout << "Wątek nr " << omp_get_thread_num() << " z " << omp_get_num_threads() << endl;
    }
    //BARIERA KOŃCZĄCA

}

//---

void listing_1_3_2() {
    cout << endl << "--- listing_1_3_2" << endl;
    int id;
    int nthreads = omp_get_max_threads();
#pragma omp parallel private(id)
    {
        id = omp_get_thread_num();
#pragma omp critical
        cout << "Wątek nr " << id << " z " << nthreads << endl;
    }

}

//---

void listing_1_3_3() {
    cout << endl << "--- listing_1_3_3" << endl;

    int id;
#pragma omp parallel private(id)
    {
        id = omp_get_thread_num();;
        int nthreads = omp_get_max_threads();

#pragma omp critical
        cout << "Wątek nr " << id << " z " << nthreads << endl;
    }
}

//---
void listing_1_4_1() {
    cout << endl << "--- listing_1_4_1" << endl;
    int id;
    int nthreads = omp_get_max_threads();
#pragma omp parallel private(id)
    {
        id = omp_get_thread_num();
#pragma omp single
        nthreads = omp_get_thread_num();
#pragma omp for
        for (int i = 0; i < 16; ++i) {
#pragma omp critical
            cout << "Krok " << i << " Wątek nr " << id << " z " << nthreads << endl;
        }

    }
}

//---

void listing_1_4_2() {
    cout << endl << "--- listing_1_4_2" << endl;
    int id;
    int nthreads = omp_get_max_threads();
#pragma omp parallel private(id)
    {
        id = omp_get_thread_num();
#pragma omp single
        nthreads = omp_get_thread_num();
#pragma omp for schedule(static,1)
        for (int i = 0; i < 16; ++i) {
#pragma omp critical
            cout << "Krok " << i << " Wątek nr " << id << " z " << nthreads << endl;
        }

    }
}

//---

void listing_1_4_3() {
    cout << endl << "--- listing_1_4_3" << endl;
    int id;
    int nthreads = omp_get_max_threads();
#pragma omp parallel for schedule(static,1)


        for (int i = 0; i < 16; ++i) {
#pragma omp critical
            cout << "Krok " << i << " Wątek nr " <<  omp_get_thread_num() << " z " << nthreads << endl;
        }


}

//---

#include <unistd.h> //usleep
#include <iomanip> //fixed, setprecision

#define MAX 32

void listing_1_5_1() {
    cout << endl << "--- listing_1_5_1" << endl;
    double t;

    t = omp_get_wtime(); //Routine returns elapsed wall clock time in seconds.



    for (int i = 0; i < MAX; i++) {
        usleep(1); //Suspend execution for microsecond intervals
    }

    t = omp_get_wtime() - t;

    cout << fixed << setprecision(0) << t * 1e6 << " mikro sekund" << endl;

}

//---

void cwiczenie_1_5_1() {
    cout << endl << "--- cwiczenie_1_5_1" << endl;
    double t;

    t = omp_get_wtime(); //Routine returns elapsed wall clock time in seconds.


#pragma omp parallel num_threads(omp_get_num_procs())
    {
#pragma omp parallel
        for (int i = 0; i < MAX; i++) {
            usleep(1); //Suspend execution for microsecond intervals
        }
    }


    t = omp_get_wtime() - t;

    cout << fixed << setprecision(0) << t * 1e6 << " mikro sekund" << endl;

}