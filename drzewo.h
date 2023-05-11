#ifndef DRZEWO_H_INCLUDED
#define DRZEWO_H_INCLUDED

/// d) drzewo czerwono- czarne (BST najpierw)

struct Node          //Struktura dla pojedynczego wierzcho³ka
{

public:
    int key;        //wartoœæ klucza
    int color;      //zmienna okreslajaca kolor: 1- czarny, 2- czerwony
    Node *left;     //wskaŸnik na lewego potomka
    Node *right;    //wskaŸnik na prawego potomka
    Node *parent;   //wskaŸnik na rodzica
    bool found = false;
};

class Drzewo
{

public:
    int rozmiar, roz=0;
    Node *root;                                         //korzen - wskaznik na poczatek
    Node S;                                             //wezel straznika - zamiast NULL
    string kreska_prawo, kreska_lewo, kreska_pion;      // lancuchy do rysowania polaczen (relacji) miedzy elementami drzewa
    HANDLE hOut;

public:

    //konstruktor drzewa
    Drzewo(int rozmiar, HANDLE h)
    {
        rozmiar = rozmiar;
        S.color = 1;
        S.parent = &S;
        S.left = &S;
        S.right = &S;
        root = &S;          //Korzen wskazuje na straznika
        this->hOut = h;
    }

    void completeTree(int value)             //funkcja do uzupelnienia drzewa
    {
        Node *p = new Node;
        p->left = p->right = &S;
        p->parent = root;
        p->key = value;
        p->color = 2;               // Nowy wezel wstawiany do drzewa kolorujemy na czerwono

        if(p->parent == &S)        //Jezeli nie ma jeszcze zadnych elementow, to jest to pierwszy element drzewa
        {
            root = p;
        }
        else                    //Jezeli juz chociaz jeden element znajduje sie w drzewie, to:
        {
            while(true)
            {

                if(p->key <= p->parent->key)
                {
                    //Jezeli wartosc nowego klucza jest <= curr to idziemy w lewo

                    //Najpierw sprawdzamy, czy miejsce, do ktorego chcemy sie udac jest puste.
                    //Jesli nie, to mozemy tam przejsc

                    if(p->parent->left != &S)
                        p->parent = p->parent->left;
                    else
                    {
                        //Jak dojdziemy do momentu, ze curr = NULL, to tam wstawiamy w to miejsce nowy element
                        p->parent->left = p;
                        break;
                    }

                }
                else if(p->key >= p->parent->key)
                {
                    //Jezeli wartosc nowego klucza jest >= curr to idziemy w prawo

                    if(p->parent->right != &S)
                        p->parent = p->parent->right;
                    else
                    {
                        //Jak dojdziemy do momentu, ze curr = NULL, to tam wstawiamy w to miejsce nowy element
                        p->parent->right = p;
                        break;
                    }

                }

            }
        }

            while((p != root) && (p->parent->color == 2))
            {
                //Jezeli wstawiamy element z lewej strony

                if(p->parent == p->parent->parent->left)
                {
                    //p A
                    //ojciec B
                    //stryj D
                    //dziadek C

                    Node *ojciec = p->parent;
                    Node *stryj = p->parent->parent->right;
                    Node *dziadek = p->parent->parent;

                    // Przypadek 1
                    //Stryj wstawianego wezla (brat ojca) jest czerwony
                    //Zmiana koloru ojca i stryja na czarny
                    //a dziadka na czerwony

                    if(stryj->color == 2)
                    {
                        ojciec->color = 1;
                        stryj->color = 1;
                        dziadek->color = 2;
                        p = dziadek;    //Sprawdzenie co sie dzieje po zamianie
                        continue;
                    }

                    //Przypadek 3
                    // Stryj jest czarny, a wstawiany wezel jest prawym potomkiem

                    if(p == ojciec->right) //Nie trzeba sprawdzac, czy stryj jest czarny, bo nawet jesli jest to straznik to i tak jest czarny
                    {
                        // Rotacja lew dla ojca
                        p = ojciec;
                        rot_left(p);
                        //Mamy przypadek 2
                    }

                    // Przypadek 2
                    //Stryj jest czarny
                    //lewy potomek = rotacja w prawo wzgledem dziadka
                    //zmiana kolorów ojca i dziadka

                    if(p == ojciec->left)
                    {
                        rot_right(dziadek);
                        ojciec->color = 1;
                        dziadek->color = 2;
                        break;
                    }
                }
                else
                {
                    //Jezeli wstawiamy element z prawej strony

                    Node *ojciec = p->parent;
                    Node *stryj = p->parent->parent->left;
                    Node *dziadek = p->parent->parent;

                    // Przypadek 1

                    if(stryj->color == 2)
                    {
                        ojciec->color = 1;
                        stryj->color = 1;
                        dziadek->color = 2;
                        p = dziadek;
                        continue;
                    }

                    // Przypadek 3
                    //Stryj jest czarny
                    //lewy potomek = rotacja w prawo wzgledem ojca

                    if(p == ojciec->left)
                    {
                        p = ojciec;
                        rot_right(p);
                        //Mamy teraz przypadek 2
                    }

                    // Przypadek 2
                    //Stryj jest czarny
                    //prawy potomek = rotacja w lewo wzgledem dziadka
                    //zmiana kolorów ojca i dziadka

                    if(p == ojciec->right)
                    {
                        ojciec->color = 1;
                        dziadek->color = 2;
                        rot_left(dziadek);
                        break;
                    }

                }

        } root->color = 1;
        roz++;
    }

    //Rotacja w lewo wzgledem x

    void rot_left(Node *a)
    {
        Node *b = a->right;
        Node *p;

        if(b != &S)
        {
            p = a->parent;
            a->right = b->left;

            if(a->right != &S)
                a->right->parent = a;

            b->parent = p;
            b->left = a;
            a->parent = b;

            if(p != &S)
            {
                if(p->left == a)
                    p->left = b;
                else
                    p->right = b;
            }
            else
                root = b;
        }
    }

    //Rotacja w prawo wzgledem x

    void rot_right(Node *a)
    {
        Node *b = a->left;
        Node *p;

        if(b != &S)
        {
            p = a->parent;
            a->left = b->right;

            if(a->left != &S)
                a->left->parent = a;

            b->right = a;
            b->parent = p;
            a->parent =b;

            if(p != &S)
            {
                //Sprawdzenie czy wezel a jest lewym czy prawym potomkiem
                if(p->left == a)
                    p->left = b;
                else
                    p->right = b;
            }
            else
                root=b;
        }
    }

    void menu()
     {
         cout << " MENU DRZEWA:" << endl;
         cout << " 1. Wyswietlenie drzewa czerwono- czarnego" << endl;
         cout << " 2. Wyszukanie wartosci danego klucza w drzewie" << endl;
         cout << " 3. Dodanie nowego wezla do drzewa" << endl;
         cout << " 4. Usuniecie wezla z drzewa" << endl;
         cout << " 0. EXIT" << endl;
     }

    void choice()
     {
        int wybor, dane, zwrot;
        do
        {
            this->menu();
            cin >> wybor;
            system("cls");

            switch(wybor)
            {
                case 1:
                    display( "", "", root);
                    break;

                case 2:
                    display( "", "", root);
                    cout << endl;
                    cout << "Podaj wartosc, ktora chcesz znalezc w drzewie: ";
                    cin >> dane;
                    system("cls");
                    showFound(dane);
                    break;

                case 3:
                    display( "", "", root);
                    cout << endl;
                    cout << "Podaj klucz, ktory chcesz dodac do drzewa: ";
                    cin >> dane;
                    addElem(dane);
                    cout << endl;
                    display( "", "", root);
                    break;

                case 4:
                    display( "", "", root);
                    cout << endl;
                    cout << "Podaj wezel, ktory chcesz usunac z drzewa: ";
                    cin >> dane;
                    Node *p = findElem(dane);
                    zwrot = deleteElem(p);

                    if(zwrot == 3)
                        cout << "Drzewo jest puste! Najpierw musisz je uzupelnic\n";

                    if(zwrot == 2)
                        cout << "Nie ma takiego klucza" << endl;

                    cout << endl;
                    display( "", "", root);
                    break;
            }
            cout << endl;

        }while(wybor!=0);
    }

    //wyswietlanie drzewa

    void display(string sp, string sn, Node *curr)
    {
        string s;

        if(curr!=&S)
        {
            s=sp;
            if(sn == kreska_prawo) s[s.length()-2] = ' ';
            display(s + kreska_pion, kreska_prawo, curr->right);

            s = s.substr (0, sp.length() - 2);

            if(curr->color == 2)       //Kolorowanie na czerwono
            {
                cout << s << sn;
                SetConsoleTextAttribute(hOut, 252); //FC - tlo biale, kolor czerwony = 252
                cout << curr->key << endl;
                SetConsoleTextAttribute(hOut, 240); //F0 - tlo biale, kolor czarny = 240
            }
            else        //Kolorowanie na czarno - automatycznie, bo biale tlo
            {
                cout << s << sn << curr->key  << endl;
            }

            s = sp;
            if(sn == kreska_lewo) s[s.length() -2] = ' ';
            display(s + kreska_pion, kreska_lewo, curr->left);
        }

    }

    void displayFind(string sp, string sn, Node *curr)
    {
        string s;

        if(curr!=&S)
        {
            s=sp;
            if(sn == kreska_prawo) s[s.length()-2] = ' ';
            displayFind(s + kreska_pion, kreska_prawo, curr->right);

            s = s.substr (0, sp.length() - 2);



            if(curr->color == 2)       //Kolorowanie na czerwono
            {

                cout << s << sn;

                if(curr->found == true)
                {
                    //Jezeli trafimy na szukany element, to wyswietlamy go na zielono np czy cos
                    SetConsoleTextAttribute(hOut, 250); //172 zielone tlo
                    //Zmieniamy status na false
                    curr->found = false;
                }
                else
                    SetConsoleTextAttribute(hOut, 252); //FC - tlo biale, kolor czerwony = 252

                cout << curr->key << endl;
                SetConsoleTextAttribute(hOut, 240); //F0 - tlo biale, kolor czarny = 240
            }
            else        //Kolorowanie na czarno - automatycznie, bo biale tlo
            {
                cout << s << sn;

                if(curr->found == true)
                {
                    SetConsoleTextAttribute(hOut, 250); //250 zielona literka
                    curr->found = false;
                }

                 cout << curr->key << endl;
                 SetConsoleTextAttribute(hOut, 240); //F0 - tlo biale, kolor czarny = 240
            }

            s = sp;
            if(sn == kreska_lewo) s[s.length() -2] = ' ';
            displayFind(s + kreska_pion, kreska_lewo, curr->left);
        }

    }

    //Dodawanie elementu

    void addElem(int value)
    {
        completeTree(value);
    }

    //Szukanie elementu w drzewie

    Node* findElem(int value)
    {
        //Iteracyjna wersja wyszukiwania klucza w drzewie

        Node *curr = root;      //Start od korzenia
        int i=0;

        while(((curr!=NULL) && (curr->key != value)) && (i<roz))
        {
            if(value < curr->key)
                curr = curr->left;
            else
                curr = curr->right;
            i++;
        }

        if(i>=roz)
        {
            S.key = 0;
            return &S;
        }

        return curr;
    }

    void showFound(int v)
    {
        Node *elem = findElem(v);

        if(elem == &S)
            cout << "Nie ma takiego klucza " << endl;
        else
        {
            elem->found = true;
            displayFind( "", "", root);
        }
    }

    Node* nastepnik(Node *p)
    {
        //Funkcja znajduje nastepnika dla p

        Node *curr;

        if(p != &S)
        {
            // Przypadek 1

            //Jezeli wezel p posiada prawego syna:

            if(p->right != &S)
            {
                curr = p->right;

                if(curr!= &S)
                {
                    while(curr->left!=&S)
                    {
                        curr = curr->left;
                    }
                }
            }
            else
            {
                // Wezel x nie posiada prawego syna
                // Idziemy w gore drzewa
                // Musimy znalezc pierwszego ojca, dla ktorego nasz wezel lezy w lewym poddrzewie
                curr = p->parent;
                Node *pomocnik=p;

                while((pomocnik != curr->left) && curr!=&S)
                {
                    //Idziemy do gory
                    pomocnik=curr;
                    curr = curr->parent;
                }

                if(curr == &S)
                    return p;       //Brak nastepnika
            }

            return curr;
        }

        return &S;       //Brak nastepnika
    }

    //Funkcja usuwajaca rekurencyjnie drzewo

    void deleteTree(Node *curr)
    {
        if(curr!=&S)
        {
            deleteTree(curr->left);        //usuniecie lewego poddrzewa
            deleteTree(curr->right);       //usuniecie prawego poddrzewa
            delete curr;
        }
    }

    int deleteElem(Node *curr)
    {
        // Przeszukiwanie drzewa, gdzie znajduje sie wezel, ktory ma zostac usuniety

        //Node *curr = findElem(value);
        if(root == &S || root == NULL)
        {
            return 3;
        }
        else
        {

            if(curr == root && curr->left == &S && curr->right == &S)
            {
                //deleteTree(root);
                delete root;
                root = &S;
            }
            else
            {
                // Przypadek 1
                //Jezeli usuwany wezel jest lisciem

                if(curr == &S)
                {
                    return 2;
                }
                else
                {
                    if(curr->left == &S && curr->right == &S)
                    {
                        Node *parent = curr->parent;

                        // Sprawdzenie po ktorej stronie

                        if(curr == parent->left)
                        {
                            // Po lewej stronie rodzica
                            parent->left = &S;

                        }
                        else
                            parent->right = &S;     // Po prawej stronie rodzica

                        delete curr;
                    }

                    // Przypadek 2
                    // Usuwany wezel ma tylko jednego potomka

                    else if((curr->left == &S) || (curr->right == &S))
                    {
                Node *child, *parent;
                parent = curr->parent;

                //Sprawdzenie, ktorego potomka posiada

                if(curr->left != &S)
                    child = curr->left; //Posiada lewego potomka
                else
                    child = curr->right; // Posiada prawego potomka

                child->parent = curr->parent;
                // Sprawdzenie, z ktorej strony jest ojciec, o ile istnieje

                if(parent == &S)
                    root = child;
                else
                {
                    if(curr == parent->left)
                        parent->left = child;
                    else
                        parent->right = child;
                }

                        delete curr;
                    }
                else if(curr->left != &S && curr->right != &S)
                {
                    // Przypadek 3
                    // Usuwany wezel posiada dwoch synow
                    // Znajdujemy wezel bedacy nastepnikiem usuwanego wezle

                    Node *n;        //nastepnik
                    n = nastepnik(curr);
                    Node *poddrzewo;
                    Node *nowy;

                    //Poddrzewo oznacza lewe poddrzewo nastepnika, a jezeli
                    // nie istnieje, to oznacza prawe poddrzewo

                    if(n->right != &S)
                        poddrzewo = n->right;
                    else if(n->left != &S)
                        poddrzewo = n->left;

                    // Przenosimy dane i klucz z nastepnika do usuwanego wezla

                    curr->key = n->key;

                    // Sprawdzenie, czy nie zostaly zaburzone wlasnosci drzewa
                    // Sprawdzenie czy dla czerwonego curr ojciec tez jest czerwony
                    // Jesli tak, to mamy 3 przypadki do rozpatrzenia - tak jak przy tworzeniu

                    // Sprawdzenie czy nastepnik byl czarny - jesli tak, to drzewo zostalo zaburzone

                    if(n->color == 1)
                    {
                        while((poddrzewo != root) && (poddrzewo->color == 1))
                        {
                            // Jezeli poddrzewo znajduje sie z lewej strony nastepnika:

                            if(poddrzewo == poddrzewo->parent->left)
                            {
                                nowy = poddrzewo->parent->right;

                                // Przypadek 1

                                // Nowy wezel - kandydat na zastapienie poddrzewa jest czerwony
                                // Rotacja w lewo wzgledem ojca poddrzewa
                                //Zamiana kolorów ojca poddrzewa i nowego wezla


                                if(nowy->color == 2)
                                {
                                    nowy->color = 1;
                                    poddrzewo->parent->color = 2;
                                    rot_left(poddrzewo->parent);
                                    nowy = poddrzewo->parent->right;

                                    // Otrzymujemy przypadek 2, 3 lub 4
                                }

                                // Przypadek 2

                                // Brat poddrzewa jest czarny i posiada czarnych synow
                                // Zmiana koloru nowego na czerwony

                                if(nowy->left->color == 1 && nowy->right->color == 1)
                                {
                                    nowy->color = 2;
                                    poddrzewo = poddrzewo->parent;
                                    continue;

                                    // Powrot do rozpatrywania przypadkow w gornej czesci drzewa
                                }

                                // Przypadek 3

                                //Nowy wezel jest czarny, jego lewy syn czerwony, a prawy- czarny
                                // Zamiana kolorow pomiedzy wezlami nowy i nowy lewy syn
                                // Rotacja w prawo wzgledem nowego wezla

                                if((nowy->color == 1) && (nowy->left->color == 2) && (nowy->right->color == 1))
                                {
                                    nowy->left->color = 1;
                                    nowy->color = 2;
                                    rot_right(nowy);
                                    nowy = poddrzewo->parent->right;

                                    // Otrzymujemy przypadek 4
                                }

                                // Przypadek 4

                                // Brat poddrzewa jest czarny, a jego prawy syn jest czerwony
                                // Rotacja wzgledem ojca poddrzewa
                                // Przeniesienie kolorow ojca poddrzewa i nowego

                                nowy->color = poddrzewo->parent->color;
                                poddrzewo->parent->color = 1;
                                nowy->right->color = 1;
                                rot_left(poddrzewo->parent);
                                poddrzewo = root;

                                // Transformacja z przypadku 4 przywraca strukture drzewa czerwono- czarnego
                            }
                            else
                            {
                                // Poddrzewo znajduje sie z prawej strony nastepnika
                                nowy = poddrzewo->parent->left;

                                // Przypadek 1

                                if(nowy->color == 2)
                                {
                                    nowy->color = 1;
                                    poddrzewo->parent->color = 2;
                                    rot_right(poddrzewo->parent);
                                    nowy = poddrzewo->parent->left;
                                }

                                // Przypadek 2

                                if(nowy->right->color == 1 && nowy->left->color == 1)
                                {
                                    nowy->color = 2;
                                    poddrzewo = poddrzewo->parent;
                                    continue;
                                }

                                // Przypadek 3

                                if((nowy->color == 1) && (nowy->right->color == 2) && (nowy->left->color == 1))
                                {
                                    nowy->right->color = 1;
                                    nowy->color = 2;
                                    rot_left(nowy);
                                    nowy = poddrzewo->parent->left;
                                }

                                // Przypadek 4

                                nowy->color = poddrzewo->parent->color;
                                poddrzewo->parent->color = 1;
                                nowy->left->color = 1;
                                rot_right(poddrzewo->parent);
                                poddrzewo = root;
                            }
                        }


                        poddrzewo->color = 1;

                    }

                    deleteElem(n);
                    //delete n;
                    }
                }
            }
        }
}

    //dekonstruktor
    ~Drzewo()
    {
        deleteTree(root);
    }
};



#endif // DRZEWO_H_INCLUDED
