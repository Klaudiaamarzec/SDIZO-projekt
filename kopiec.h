#ifndef KOPIEC_H_INCLUDED
#define KOPIEC_H_INCLUDED

/// c) kopiec binarny (typu maksimum - element maksymalny w korzeniu)

class Kopiec
{

public:
    int rozmiar, roz = 0;                               //roz = rozmiar przy tworzeniu
    int *root;                                   //korzeñ - wskaŸnik na poczatek
    string kreska_prawo, kreska_lewo, kreska_pion;      // ³añcuchy do rysowania po³¹czeñ (relacji) miêdzy elementami kopca
    HANDLE hOut;

public:

    //konstruktor kopca
    Kopiec(int rozmiar, HANDLE h)
    {
        this->rozmiar = rozmiar;
        this->root = new int[rozmiar];        //Stworzenie tablicy elementów kopca
        this->hOut = h;
    }

    //Wyswietlenie tabeli kopca
    void wyswietl()
    {
        for(int i=0; i<rozmiar; i++)
            cout << root[i] << " ";
    }

    void menu()
     {
         cout << "MENU KOPIEC:" << endl;
         cout << "1. Wyswietlenie tablicy kopca" << endl;
         cout << "2. Wyswietlenie kopca" << endl;
         cout << "3. Wyszukanie danego elementu na kopcu" << endl;
         cout << "4. Wyszukanie wartosci dla podanego indeksu kopca" << endl;
         cout << "5. Dodanie nowego elementu na kopiec" << endl;
         cout << "6. Usuniecie elementu z kopca (usuniecie korzenia)" << endl;
         cout << "0. EXIT" << endl;
     }

    void choice()
     {
        int wybor, dane, indeks, zwrot;
        do
        {
            this->menu();
            cin >> wybor;
            system("cls");

            switch(wybor)
            {
                case 1:
                    wyswietl();
                    break;

                case 2:
                    display( "", "", 0);
                    break;

                case 3:
                    display( "", "", 0);
                    cout << endl;
                    cout << "Podaj wartosc, ktora chcesz znalezc na kopcu: ";
                    cin >> dane;
                    system("cls");
                    indeks = findElemValue(dane);

                    if(indeks == -1)
                        cout << "Nie udalo sie znalezc podanej wartosci na kopcu" << endl << endl;
                    else
                        displayColor( "", "", 0, indeks);

                    break;

                case 4:
                    display( "", "", 0);
                    cout << endl;
                    cout << "Podaj indeks, ktory chcesz znalezc: ";
                    cin >> dane;
                    system("cls");
                    findElemIndex(dane);
                    break;

                case 5:
                    display( "", "", 0);
                    cout << endl;
                    cout << "Podaj wartosc, ktora chcesz dodac na kopiec: ";
                    cin >> dane;
                    indeks = addElem(dane);
                    displayColor( "", "", 0, indeks);
                    break;

                case 6:
                    zwrot = deleteRoot();
                    cout << endl;

                    if(zwrot == 3)
                        cout << "Kopiec jest pusty! Najpierw nalezy go uzupelnic\n";

                    display( "", "", 0);
                    break;
            }
            cout << endl;

        }while(wybor!=0);
    }

    //dodadwanie wartosci do tabeli, z której powstanie kopiec

   void complete(int index, int value)
    {
        root[index] = value;
    }

    //Uzupe³nienie kopca
    //Tworzenie kopca maksymalnego- ka¿dy element po kolei jest dodawany i sprawdzany jest warunek kopca maksymalnego

    void completeMound()
    {
        do
        {
            int idx = roz++, przechowalnia;
            int father = (idx-1)/2;

            //Sprawdzenie, czy ostatnia liczba jest wiêksza od rodzica

            while(idx>0 && root[idx] > root[father])
            {
                przechowalnia = root[idx];
                root[idx] = root[father];
                root[father] = przechowalnia;
                idx=father;                          //Po zamianie roz ustawiamy na ojca, zgodnie z algorytmem
                father = (idx-1)/2;
            }
        }while(roz!=rozmiar);
    }

    //wyswietlanie kopca

    void display(string sp, string sn, int k)
    {
        string s;

        if(k<rozmiar)
        {
            s=sp;
            if(sn == kreska_prawo) s[s.length()-2] = ' ';
            display(s + kreska_pion, kreska_prawo, 2*k +2); //2k+2 - prawy potomek

            s = s.substr (0, sp.length() - 2);

            cout << s << sn << root[k]  << endl;

            s = sp;
            if(sn == kreska_lewo) s[s.length() -2] = ' ';
            display(s + kreska_pion, kreska_lewo, 2*k +1); //2k+1 - lewy potomek
        }
    }

    //wyswietlenie kopca z zaznaczeniem szukanego elementu

    void displayColor(string sp, string sn, int k, int index)
    {
        string s;

        if(k<rozmiar)
        {
            s=sp;
            if(sn == kreska_prawo) s[s.length()-2] = ' ';

            displayColor(s + kreska_pion, kreska_prawo, 2*k +2, index); //2k+2 - prawy potomek

            s = s.substr (0, sp.length() - 2);

            if(k == index)
            {
                cout << s << sn;
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
                cout << root[k]  << endl;
                SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else
            {
                cout << s << sn << root[k] << endl;
            }

            s = sp;
            if(sn == kreska_lewo) s[s.length() -2] = ' ';

            displayColor(s + kreska_pion, kreska_lewo, 2*k +1, index); //2k+1 - lewy potomek
        }
    }

    //dodawanie nowego elementu do kopca
    int addElem(int value)
    {
        if(rozmiar==0)
        {
            this->root = new int[1];
            root[0] = value;
            rozmiar++;
            return 0;
        }
        else
        {
            //Dodanie nowego elementu na koniec tablicy kopca - realokacja pamiêci

            int* nowa_tablica = new int[rozmiar+1];

            for(int i=0; i<rozmiar; i++)
            {
                nowa_tablica[i] = root[i];
            }
            delete[] root;
            root = nowa_tablica;
            root[rozmiar] = value;
            rozmiar++;

            //Element zostaje tym samym wstawiony na ostatnie miejsce kopca

            int idx = rozmiar-1, przechowalnia;
            int father = (idx-1)/2;

            //Sprawdzenie jak wygl¹da sytuacja w miejscu wstawienia nowej liczby i ewentualna modyfikacja, je¿eli
            //kopiec maksymalny zosta³ zaburzony

            while(root[idx] > root[father])
            {
                przechowalnia = root[idx];
                root[idx] = root[father];
                root[father] = przechowalnia;
                idx=father;
                father = (idx-1)/2;
            }

            return idx;
        }
    }

    //Znajdowanie konkretnej wartoœci

    int findElemValue(int value)
    {
       //Uzytkownik podaje liczbe jaka chce znalezc - funkcja znajduje indeks elementu
        for(int i=0; i<rozmiar; i++)
        {
            if(root[i] == value)
            {
                return i;           //Funkcja dziala do momentu znalezienia pierwszego takiego elementu, pozniej wychodzi
            }
        }
        return -1;
    }

    //Podanie indeksu i znalezienie odpowiadaj¹cej mu wartoœci

    void findElemIndex(int index)
    {
        if(index >= rozmiar || index<0)
            cout << "Blad! Nie ma takiego indeksu" << endl;
        else
        {
            cout << endl << "Znaleziona wartosc to: " << root[index-1] << endl;
            displayColor( "", "", 0, index-1);
        }
    }

    int deleteRoot()
    {
        if(rozmiar<=0)
            return 3;
        else
        {
            int i, j, v;

              if( rozmiar-- )
              {
                v= root[rozmiar];

                i = 0;
                j = 1;

                while( j < rozmiar )
                {
                  if( j + 1 < rozmiar && root[ j + 1 ] > root[ j ] ) j++;
                  if( v >= root[ j ] ) break;
                  root[ i ] = root[ j ];
                  i = j;
                  j = 2 * j + 1;
                }

                root[ i ] = v;
              }
        }
    }

    //usuwanie elementu z kopca - usuwanie korzenia
  /*  int deleteRoot()
    {
        //Kopiec drzewa jest usuwany i zastepywany ostatnim lisciem
        //Realokacja pamiêci - tablica kopca

        if(rozmiar<=0)
            return 3;
        else
        {
            {
                int* nowa_tablica = new int[rozmiar-1];
                nowa_tablica[0] = root[rozmiar-1];      //Ostatni element jest umieszczany w korzeniu

                for(int i=1; i<=rozmiar-2; i++)
                {
                    nowa_tablica[i] = root[i];
                }

                delete[] root;
                root = nowa_tablica;
                rozmiar--;

                if(rozmiar == 0) //usuniecie tablicy dynamiecznej, je¿eli nie ma ¿adnych elementów
                {
                    delete[] root;
                }
                else
                {
                    int index = 0;
                    int pot1 = 2*index + 1; //lewy potomek
                    int pot2 = 2*index + 2; //prawy potomek

                    //Sprawdzanie warunkow kopca
                    while((root[index] < root[pot1] || root[index] < root[pot2]) && index <rozmiar && pot1<rozmiar && pot2<rozmiar)
                    {
                        int przechowalnia;

                        //Zamiana miejscami z najwiekszym potomkiem
                        if(root[pot1] >= root[pot2])
                        {
                            //Zamiana miejsc z potomkiem 1
                            przechowalnia = root[index];
                            root[index] = root[pot1];
                            root[pot1] = przechowalnia;

                            przechowalnia = index;
                            index = pot1;
                            pot1 = przechowalnia;
                        }
                        else
                        {
                            //Zamiana miejsc z potomkiem 1
                            przechowalnia = root[index];
                            root[index] = root[pot2];
                            root[pot2] = przechowalnia;

                            przechowalnia = index;
                            index = pot2;
                            pot2 = przechowalnia;
                        }

                        pot1 = 2*index + 1;
                        pot2 = 2*index + 2;
                    }
                }
            }
        }
    }*/

    //dekonstruktor
    ~Kopiec()
    {
        if(rozmiar!=0)
            delete[] root;
    }
};


#endif // KOPIEC_H_INCLUDED
