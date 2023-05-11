#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "tablica.h"
#include "lista.h"
#include "kopiec.h"
#include "drzewo.h"
using namespace std;

//Badanie efektywnoœci operacji na danych w podstawowych strukturach danych
HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );

//Menu do wybierania, jaka strukture przetestowac
void menu();
void menu2();

int main()
{
    int wybor, wartosc, rozmiar;
    string nazwa;
    cout << "Podaj nazwe pliku, z ktorego chcesz wczytac dane: ";
    cin >> nazwa;
    do
    {
        system("cls");
        menu();
        cin >> wybor;
        system("cls");

        switch(wybor)
        {
            case 1:
                {
                    system("color 0F");
                    ifstream plik(nazwa);

                    if(plik.is_open())
                    {
                        int liczba, i = 0; //i - indeksem potrzebny przy uzupelnianiu tablicy

                        //Pierwsza liczba z pliku - rozmiar tablicy

                        plik >> rozmiar;
                        Tablica tablica(rozmiar, hOut);

                        //Odczyt pozostałych linii i uzupełnienie tablicy

                        string linia;

                        while(getline(plik, linia))
                        {
                            plik >> liczba;
                            tablica.complete(i, liczba);
                            i++;
                        }

                        plik.close();
                        tablica.choice();
                        cout << endl;
                    }
                    else
                        cout << "Nie udalo sie otworzyc pliku" << endl;
                }
                break;
            case 2:
                {
                    system("color 0F");
                    ifstream plik(nazwa);

                    if(plik.is_open())
                    {
                        int liczba;

                        //Pierwsza liczba z pliku - rozmiar listy

                        plik >> rozmiar;
                        Lista lista(rozmiar, hOut);

                        //Odczyt pozostałych linii i uzupełnienie tablicy

                        string linia;

                        while(getline(plik, linia))
                        {
                            plik >> liczba;
                            lista.addElements(liczba);
                        }

                        plik.close();
                        lista.choice();
                        cout << endl;
                    }
                    else
                        cout << "Nie udalo sie otworzyc pliku" << endl;
                }
                break;
            case 3:
                {
                    system("color 0F");
                    ifstream plik(nazwa);

                    if(plik.is_open())
                    {
                         int liczba, i = 0; //i - indeks potrzebny przy uzupelnianiu tablicy kopca

                        //Pierwsza liczba z pliku - rozmiar tablicy

                        plik >> rozmiar;
                        Kopiec kopiec(rozmiar, hOut);

                        kopiec.kreska_prawo = kopiec.kreska_lewo = kopiec.kreska_pion = "  ";
                        kopiec.kreska_prawo [ 0 ] = 218; kopiec.kreska_prawo [ 1 ] = 196;
                        kopiec.kreska_lewo [ 0 ] = 192; kopiec.kreska_lewo [ 1 ] = 196;
                        kopiec.kreska_pion [ 0 ] = 179;

                        string linia;

                        while(getline(plik, linia))
                        {
                            plik >> liczba;
                            kopiec.complete(i, liczba);
                            i++;
                        }
                        //Naprawa kopca:
                        kopiec.completeMound();

                        plik.close();
                        kopiec.choice();
                        cout << endl;
                    }
                    else
                        cout << "Nie udalo sie otworzyc pliku" << endl;
                }
                break;

            case 4:
                {
                    system("color F0"); // ustawia koloru tla na bialy
                    ifstream plik(nazwa);

                    if(plik.is_open())
                    {
                        int liczba;

                        plik >> rozmiar;
                        Drzewo drzewo(rozmiar, hOut);

                        drzewo.kreska_prawo = drzewo.kreska_lewo = drzewo.kreska_pion = "  ";
                        drzewo.kreska_prawo [ 0 ] = 218; drzewo.kreska_prawo [ 1 ] = 196;
                        drzewo.kreska_lewo [ 0 ] = 192; drzewo.kreska_lewo [ 1 ] = 196;
                        drzewo.kreska_pion [ 0 ] = 179;

                        string linia;

                        while(getline(plik, linia))
                        {
                            plik >> liczba;
                            drzewo.completeTree(liczba);
                        }

                        plik.close();
                        drzewo.choice();
                        cout << endl;
                    }
                    else
                        cout << "Nie udalo sie otworzyc pliku" << endl;
                }
                break;

            case 5:
                {
                    srand(time(NULL));
                    int wybor2;

                    do
                    {
                        system("cls");
                        menu2();
                        cin >> wybor2;
                        system("cls");


                        switch(wybor2)
                        {
                        case 1:
                            {
                                ofstream plik2("pomiaryTablica.txt");
                                ifstream plik(nazwa);

                                if(plik2.is_open())
                                {
                                    plik2 << "Pomiary dla tablicy" << endl << endl;

                                    for(int i=0; i<99; i++)
                                    {
                                        Tablica tablica(20000, hOut);

                                        for(int i=0; i<20000; i++)
                                        {
                                            //Uzupelnienie tablicy
                                            int liczba = rand();
                                            tablica.complete(i, liczba);
                                        }

                                        //Losowanie elementu do wyszukania
                                        int elem = rand() % 20000;

                                        //pomiar czasu przed wykonaniem operacji
                                        LARGE_INTEGER start;
                                        QueryPerformanceCounter(&start);

                                        tablica.findElem(elem);

                                        //pomiar czasu po wykonaniu operacji
                                        LARGE_INTEGER koniec;
                                        QueryPerformanceCounter(&koniec);

                                        //obliczenie czasu
                                        LARGE_INTEGER frequency;
                                        QueryPerformanceFrequency(&frequency);
                                        double czas = (koniec.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

                                        plik2 << czas << "   ";

                                        // 2 Dodanie elementu

                                        //Losowanie elementu do wyszukania
                                        elem = rand() % 20000;
                                        int liczba = rand();

                                        QueryPerformanceCounter(&start);

                                        tablica.addAnywhere(elem, liczba);

                                        QueryPerformanceCounter(&koniec);

                                        //obliczenie czasu
                                        QueryPerformanceFrequency(&frequency);
                                        czas = (koniec.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

                                        plik2 << czas << "   ";

                                        // 3 Usuniecie elementu

                                        //Losowanie elementu do uSuniecia
                                        elem = rand() % 20000;

                                        QueryPerformanceCounter(&start);

                                        tablica.deleteElemFirst();

                                        QueryPerformanceCounter(&koniec);

                                        //obliczenie czasu
                                        QueryPerformanceFrequency(&frequency);
                                        czas = (koniec.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

                                        plik2 << czas << "   " << endl;
                                    }

                                }
                                else
                                    cout << "Nie udalo sie otworzyc pliku" << endl;
                                plik2.close();
                            }
                            break;
                        case 2:
                            {
                                ofstream plik2("pomiaryLista.txt");
                                ifstream plik(nazwa);

                                if(plik2.is_open())
                                {
                                    plik2 << "Pomiary dla listy" << endl << endl;

                                    for(int i=0; i<99; i++)
                                    {
                                        Lista lista(20000, hOut);

                                        for(int i=0; i<20000; i++)
                                        {
                                            //Uzupelnienie listy
                                            int liczba = rand();
                                            lista.addElements(liczba);
                                        }

                                        // 1 Wyszukanie danego elementu

                                        //Losowanie elementu do wyszukania
                                        int elem = rand();

                                        LARGE_INTEGER start;
                                        QueryPerformanceCounter(&start);

                                        lista.find2(elem);

                                        LARGE_INTEGER koniec;
                                        QueryPerformanceCounter(&koniec);

                                        //obliczenie czasu
                                        LARGE_INTEGER frequency;
                                        QueryPerformanceFrequency(&frequency);
                                        double czas = (koniec.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

                                        plik2 << czas << "   ";

                                        // 2 Dodanie elementu

                                        //Losowanie elementu
                                        elem = rand() % 20000;
                                        int liczba = rand();

                                        QueryPerformanceCounter(&start);

                                        lista.addAnywhere(elem, liczba);

                                        QueryPerformanceCounter(&koniec);

                                        //obliczenie czasu
                                        QueryPerformanceFrequency(&frequency);
                                        czas = (koniec.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

                                        plik2 << czas << "   ";

                                        // 3 Usuniecie elementu

                                        //Losowanie elementu do usuniecia
                                        elem = rand() % 20000;

                                        QueryPerformanceCounter(&start);

                                        lista.deleteAny(elem);

                                        QueryPerformanceCounter(&koniec);

                                        //obliczenie czasu
                                        QueryPerformanceFrequency(&frequency);
                                        czas = (koniec.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

                                        plik2 << czas << "   " << endl;

                                    }

                                }
                                else
                                    cout << "Nie udalo sie otworzyc pliku" << endl;

                                plik2.close();
                            }
                            break;
                        case 3:
                            {
                                ofstream plik2("pomiaryKopiec.txt");
                                ifstream plik(nazwa);

                                if(plik2.is_open())
                                {
                                    plik2 << "Pomiary dla kopca" << endl << endl;

                                    for(int i=0; i<99; i++)
                                    {
                                        Kopiec kopiec(1000, hOut);

                                        kopiec.kreska_prawo = kopiec.kreska_lewo = kopiec.kreska_pion = "  ";
                                        kopiec.kreska_prawo [ 0 ] = 218; kopiec.kreska_prawo [ 1 ] = 196;
                                        kopiec.kreska_lewo [ 0 ] = 192; kopiec.kreska_lewo [ 1 ] = 196;
                                        kopiec.kreska_pion [ 0 ] = 179;

                                        for(int i=0; i<1000; i++)
                                        {
                                            int liczba = rand();
                                            kopiec.complete(i, liczba);
                                        }

                                        kopiec.completeMound();


                                        // 1 Wyszukanie danego elementu

                                        //Losowanie elementu do wyszukania
                                        int wartosc = rand();

                                        //pomiar czasu przed wykonaniem operacji
                                        LARGE_INTEGER start;
                                        QueryPerformanceCounter(&start);

                                        int cos = kopiec.findElemValue(wartosc);
                                        //kopiec.wyswietl();

                                        LARGE_INTEGER koniec;
                                        QueryPerformanceCounter(&koniec);

                                        //obliczenie czasu
                                        LARGE_INTEGER frequency;
                                        QueryPerformanceFrequency(&frequency);
                                        double czas = (koniec.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

                                        plik2 << czas << "   ";

                                       // 2 Dodanie elementu

                                        //Losowanie elementu
                                        int liczba = rand();

                                        QueryPerformanceCounter(&start);

                                        kopiec.addElem(liczba);

                                        QueryPerformanceCounter(&koniec);

                                        //obliczenie czasu
                                        QueryPerformanceFrequency(&frequency);
                                        czas = (koniec.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

                                        plik2 << czas << "   ";

                                        // 3 Usuniecie elementu

                                        QueryPerformanceCounter(&start);

                                        //Usuniecie korzenia
                                        kopiec.deleteRoot();

                                        QueryPerformanceCounter(&koniec);

                                        //obliczenie czasu
                                        QueryPerformanceFrequency(&frequency);
                                        czas = (koniec.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

                                        plik2 << czas << " " << endl;

                                    }

                                }
                                else
                                    cout << "Nie udalo sie otworzyc pliku" << endl;

                                plik2.close();

                            }
                            break;
                        case 4:
                            {
                                ofstream plik2("pomiaryDrzewo.txt");
                                ifstream plik(nazwa);

                                if(plik2.is_open())
                                {
                                    plik2 << "Pomiary dla drzewa" << endl << endl;

                                    for(int i=0; i<100; i++)
                                    {
                                        Drzewo drzewo(1000, hOut);

                                        drzewo.kreska_prawo = drzewo.kreska_lewo = drzewo.kreska_pion = "  ";
                                        drzewo.kreska_prawo [ 0 ] = 218; drzewo.kreska_prawo [ 1 ] = 196;
                                        drzewo.kreska_lewo [ 0 ] = 192; drzewo.kreska_lewo [ 1 ] = 196;
                                        drzewo.kreska_pion [ 0 ] = 179;

                                        for(int i=0; i<1000; i++)
                                        {
                                            //Uzupelnienie drzewa
                                            int liczba = rand();
                                            drzewo.completeTree(liczba);
                                        }

                                        // 1 Wyszukanie danego elementu

                                        //Losowanie elementu do wyszukania
                                        int wartosc = rand();

                                        //pomiar czasu przed wykonaniem operacji
                                        LARGE_INTEGER start;
                                        QueryPerformanceCounter(&start);

                                        Node *p = drzewo.findElem(wartosc);

                                        //pomiar czasu po wykonaniu operacji
                                        LARGE_INTEGER koniec;
                                        QueryPerformanceCounter(&koniec);

                                        //obliczenie czasu
                                        LARGE_INTEGER frequency;
                                        QueryPerformanceFrequency(&frequency);
                                        double czas = (koniec.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

                                        plik2 << czas << "   ";

                                       // 2 Dodanie elementu

                                        //Losowanie elementu
                                        int liczba = rand();

                                        QueryPerformanceCounter(&start);

                                        drzewo.addElem(liczba);

                                        QueryPerformanceCounter(&koniec);

                                        //obliczenie czasu
                                        QueryPerformanceFrequency(&frequency);
                                        czas = (koniec.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

                                        plik2 << czas << "   ";

                                        // 3 Usuniecie elementu

                                        do                                  //Wylosowanie wartosci znajdujacej sie w drzewie
                                        {
                                            wartosc = rand();
                                            p = drzewo.findElem(wartosc);
                                            cout << "P " << p->key << endl;
                                        }while(p->key==0);

                                        QueryPerformanceCounter(&start);

                                        //Usuniecie elementu

                                        drzewo.deleteElem(p);

                                        QueryPerformanceCounter(&koniec);

                                        //obliczenie czasu
                                        QueryPerformanceFrequency(&frequency);
                                        czas = (koniec.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;

                                        plik2 << czas << "   " << endl;

                                    }
                                }
                                else
                                    cout << "Nie udalo sie otworzyc pliku" << endl;

                                plik2.close();
                            }
                            break;

                        }

                    }while(wybor2!=0);

                }
                break;
        }
    }while(wybor!=0);

    return 0;
}

void menu()
{
    cout << "Wybierz, jaka strukture chcesz teraz przetestowac: " << endl;
    cout << "1. Tablica" << endl;
    cout << "2. Lista" << endl;
    cout << "3. Kopiec" << endl;
    cout << "4. Drzewo czerwono- czarne" << endl;
    cout << "5. POMIARY" << endl;
    cout << "0. EXIT" << endl;
}

void menu2()
{
        cout << "Wybierz strukture, dla ktorej chcesz wykonac pomiary: " << endl;
        cout << "1. Tablica " << endl;
        cout << "2. Lista " << endl;
        cout << "3. Kopiec " << endl;
        cout << "4. Drzewo czerowno- czarne" << endl;
        cout << "0. EXIT" << endl;
}
