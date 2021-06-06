#include "lab11.h"
#include <random>
#include <iostream>
#include <thread>
#include "kolory.h"
#include "omp.h"
#include <iomanip>


using namespace std;


short wynik1, wynik2;
int rozmiarTablicy = 10;
unsigned int polowa = rozmiarTablicy / 2;


void wypelnijLosowymi(short T[], int n) {
    random_device maszynkaLosujaca;
    uniform_int_distribution<short> dystrybucja(-10, 10);
    for (int i = 0; i < n; i++) T[i] = dystrybucja(maszynkaLosujaca);
}


void wyswietlTablice(const short T[], int n) {
    short suma = 0;
    cout << "informacje o tablicy:" << endl;
    for (int i = 0; i < n; i++) {
        cout << T[i] << " ";
        suma += T[i];
    }
    cout << endl << "Suma=" << suma << endl << endl;
}


void l3z1() {
    static short *TAB; //Tablica
    TAB = new short[rozmiarTablicy];

    wypelnijLosowymi(TAB, rozmiarTablicy);

    wyswietlTablice(TAB, rozmiarTablicy);
    unsigned int polowa = rozmiarTablicy / 2;
    omp_set_num_threads(2);
    string k = Kolor::nastepny(), r = Kolor::reset();
    int wynik = 0;
#pragma omp parallel
    {

        int wynikW = 0;
#pragma omp for schedule(dynamic, polowa)
        for (int i = 0; i < rozmiarTablicy; i++) {
            wynikW += TAB[i];

            string info = k + to_string(TAB[i]) + r + "\n";
            cout << info;
        };
        cout << "suma watku= " + std::to_string(wynikW) + "\n";
        wynik += wynikW;
    }

    cout << "suma=  " + std::to_string(wynik) + "\n";


    delete[] TAB;
}


void l3z2() {
    static short *TAB; //Tablica
    TAB = new short[rozmiarTablicy];

    wypelnijLosowymi(TAB, rozmiarTablicy);

    wyswietlTablice(TAB, rozmiarTablicy);

    omp_set_num_threads(2);
    string k = Kolor::nastepny(), r = Kolor::reset();
    int wynik = 0;
#pragma omp parallel
    {

        int wynikW = 0;
#pragma omp for schedule(static, 1)
        for (int i = 0; i < rozmiarTablicy; i++) {
            wynikW += TAB[i];

            string info = k + to_string(TAB[i]) + r + "\n";
            cout << info;
        };
        cout << "suma watku= " + std::to_string(wynikW) + "\n";
        wynik += wynikW;
    }

    cout << "suma=  " + std::to_string(wynik) + "\n";


    delete[] TAB;
}


void l3z3() {
    static short *TAB; //Tablica
    TAB = new short[rozmiarTablicy];

    wypelnijLosowymi(TAB, rozmiarTablicy);

    wyswietlTablice(TAB, rozmiarTablicy);

    omp_set_num_threads(2);
    string k = Kolor::nastepny(), r = Kolor::reset();
    int wynik = 0;
    bool isMinusTaken = false;
    omp_set_num_threads(2);
#pragma omp parallel
    {
        bool addMinus = false;
        if (isMinusTaken == false) {
            isMinusTaken = true;
            addMinus = true;
        }
        int wynikW = 0;

        for (int i = 0; i < rozmiarTablicy; i++) {
            if (addMinus && TAB[i] < 0) {
                wynikW += TAB[i];

                string info = k + to_string(TAB[i]) + r + "\n";
                cout << info;
            }
            if (!addMinus && TAB[i] > 0) {
                wynikW += TAB[i];

                string info = k + to_string(TAB[i]) + r + "\n";
                cout << info;
            }


        };
        cout << "suma watku= " + std::to_string(wynikW) + "\n";
        wynik += wynikW;
    }

    cout << "suma=  " + std::to_string(wynik) + "\n";


    delete[] TAB;
}

void kwadratujIPodminCoDrugi(short T[], int poczatek, int koniec) {

    string k = Kolor::nastepny(), r = Kolor::reset();


    for (int i = poczatek; i < koniec; i = i + 2) {


        string info = k + to_string(T[i]) + r + "\n";
        cout << info;

        T[i] = T[i] * T[i];
    }

}

void l3z4() {
    short *TAB; //Tablica
    TAB = new short[rozmiarTablicy];

    wypelnijLosowymi(TAB, rozmiarTablicy);

    wyswietlTablice(TAB, rozmiarTablicy);


    omp_set_num_threads(2);
    string k = Kolor::nastepny(), r = Kolor::reset();
    int wynik = 0;

    {

        ;
#pragma omp for
        for (int i = 0; i < rozmiarTablicy; i++) {
            string info = k + to_string(TAB[i]) + r + "\n";
            cout << info;

            TAB[i] = TAB[i] * TAB[i];
        };

    }


    ;

    wyswietlTablice(TAB, rozmiarTablicy);


    delete[] TAB;
}

void wyswietlTablice(const float T[], int n) {

    cout << "informacje o tablicy:" << endl;
    for (int i = 0; i < n; i++) {
        cout << setprecision(2) << T[i] << " ";

    }

}

void filtrDyskretnyCoDrugi(short T[], float resT[], int poczatek, int koniec) {

    string k = Kolor::nastepny(), r = Kolor::reset();


    for (int i = poczatek; i < koniec; i = i + 2) {


        string info = k + to_string(T[i]) + r + "\n";
        cout << info;

        if (i == 0) {
            resT[i] = (float) (T[i] + T[i + 1]) / 2;
        } else if (i == koniec - 1) {
            resT[i] = (float) (T[i - 1] + T[i]) / 2;
        } else {
            resT[i] = (float) (T[i - 1] + T[i] + T[i + 1]) / 3;
        }


    }

}

void l3z5() {
    static short *TAB; //Tablica
    TAB = new short[rozmiarTablicy];

    float *resTAB = new float[rozmiarTablicy];

    wypelnijLosowymi(TAB, rozmiarTablicy);
    cout << "Dane" << endl;
    wyswietlTablice(TAB, rozmiarTablicy);


    string k = Kolor::nastepny(), r = Kolor::reset();


    omp_set_num_threads(2);
#pragma omp for
    for (int i = 0; i < rozmiarTablicy; i++) {


        string info = k + to_string(TAB[i]) + r + "\n";
        cout << info;

        if (i == 0) {
            resTAB[i] = (float) (TAB[i] + TAB[i + 1]) / 2;
        } else if (i == rozmiarTablicy - 1) {
            resTAB[i] = (float) (TAB[i - 1] + TAB[i]) / 2;
        } else {
            resTAB[i] = (float) (TAB[i - 1] + TAB[i] + TAB[i + 1]) / 3;
        }


    }


    cout << "Wyniki" << endl;
    wyswietlTablice(resTAB, rozmiarTablicy);

    delete[] TAB;
    delete[] resTAB;
}
