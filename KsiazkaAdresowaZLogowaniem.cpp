#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <windows.h>

using namespace std;

struct Uzytkownik
{
    int id=0;
    string login, haslo;
};

struct Adresat
{
    int id=0, idUzytkownika=0;
    string imie, nazwisko, telefon, email, adres;
};

vector <string> stworzWektor (string nazwa_pliku)
{
    fstream plik;
    string linia;
    vector <string> wektor_danych;
    plik.open(nazwa_pliku,ios::out | ios::in);

    while(getline(plik,linia))
    {
        stringstream linia_do_pociecia(linia);
        string dane;
        while (getline(linia_do_pociecia, dane, '|'))
        {
            wektor_danych.push_back(dane);
        }
    }

    plik.close();
    return wektor_danych;
}

void znajdzPlik (string nazwa_pliku)
{
    fstream plik;
    plik.open(nazwa_pliku,ios::in);
    if (plik.good() == false)
    {
        cout << "Nie znaleziono pliku!" << endl;
        exit(0);
    }
    plik.close();
}

int policz()
{
    fstream plik;
    string id, linia;
    int nr_linii=1;
    int iloscUzytkownikow=0;

    plik.open("Adresaci-tymczasowy.txt",ios::in);

    if (plik.good() == false)
    {
        iloscUzytkownikow=0;
    }
    else if (plik.good() == true)
    {
        while(getline(plik,linia))
        {
            nr_linii=0;
            iloscUzytkownikow++;
            nr_linii++;
        }
    }
    plik.close();
    return iloscUzytkownikow;
}

bool sprawdzLogin(string login)
{
    znajdzPlik("Uzytkownicy.txt");
    string nazwa;
    vector <string> wektor_danych;
    wektor_danych=stworzWektor("Uzytkownicy.txt");

    for(unsigned int i=0; i<(wektor_danych.size()/3); i++)
    {
        if (wektor_danych[i*3+1]==login)
        {
            nazwa=wektor_danych[i*3+1];
            return true;
        }
    }
    return false;
}

string sprawdzIdDlaPodanegoLoginu(string login)
{
    znajdzPlik("Uzytkownicy.txt");

    string IdTegoLoginu;

    vector <string> wektor_danych;
    wektor_danych=stworzWektor("Uzytkownicy.txt");

    for(unsigned int i=0; i<(wektor_danych.size()/3); i++)
    {
        if (wektor_danych[i*3+1]==login)
        {
            IdTegoLoginu=wektor_danych[i*3];
        }
    }
    return IdTegoLoginu;
}

string sprawdzHasloDlaPodanegoLoginu(string login)
{
    znajdzPlik("Uzytkownicy.txt");

    string HasloTegoLoginu;

    vector <string> wektor_danych;
    wektor_danych=stworzWektor("Uzytkownicy.txt");

    for(unsigned int i=0; i<(wektor_danych.size()/3); i++)
    {
        if (wektor_danych[i*3+1]==login)
        {
            HasloTegoLoginu=wektor_danych[i*3+2];
        }
    }
    return HasloTegoLoginu;
}

void zapiszUzytkownika ()
{
    string login, haslo, haslo1, haslo2;
    fstream plik;

    vector <string> wektor_danych;
    wektor_danych=stworzWektor("Uzytkownicy.txt");

    int idOstatniegoUzytkownika=0;

    if (wektor_danych.size()!=0)
    {
        idOstatniegoUzytkownika = atoi(wektor_danych[wektor_danych.size()-3].c_str());
    }

    plik.open("Uzytkownicy.txt",ios::out | ios::app);

    cin.sync();

    while(1)
    {

        cout << "Podaj login: ";
        getline(cin, login);

        if (sprawdzLogin(login) == true)
        {
            cout << "Taki uzytkownik juz istnieje!" << endl;
            continue;
        }

        else
        {

            while (1)
            {

                cout <<  "Podaj haslo: ";
                getline(cin, haslo1);

                cout << "Powtorz haslo: ";
                getline(cin, haslo2);

                if (haslo1 == haslo2)
                {
                    haslo = haslo2;
                    break;
                }

                else
                {
                    cout << "Podales dwa rozne hasla! Podaj haslo jeszcze raz." << endl;
                }
            }

            plik << idOstatniegoUzytkownika+1 << "|";
            plik << login << "|" ;
            plik << haslo << "|";
            plik << endl;

            plik.close();

            string numer=sprawdzIdDlaPodanegoLoginu(login);
            cout << "Twoj numer ID to: " << numer << endl;

            break;
        }
    }
}

vector<Adresat> stworzWektorStrukturZPliku(string nazwa_pliku)
{
    fstream plik;
    string linia;
    vector <Adresat> wektor_wynikowy;
    plik.open(nazwa_pliku,ios::out | ios::in);

    while(getline(plik,linia))
    {
        stringstream linia_do_pociecia(linia);
        string dane;
        vector<string> wektor_danych;

        while (getline(linia_do_pociecia, dane, '|'))
        {
            wektor_danych.push_back(dane);
        }

        Adresat adresat;
        adresat.id = stoi(wektor_danych[0]);
        adresat.idUzytkownika = stoi(wektor_danych[1]);
        adresat.imie = wektor_danych[2];
        adresat.nazwisko = wektor_danych[3];
        adresat.telefon = wektor_danych[4];
        adresat.email = wektor_danych[5];
        adresat.adres = wektor_danych[6];

        wektor_wynikowy.push_back(adresat);
    }

    plik.close();
    return wektor_wynikowy;
}

void stworzPlikTymczasowy(string login)
{
    fstream plik;

    vector <Adresat> wektorAdresatow = stworzWektorStrukturZPliku("Adresaci.txt");

    plik.open("Adresaci-tymczasowy.txt", ios::out);

    string numer=sprawdzIdDlaPodanegoLoginu(login);

    for (int i=0; i<wektorAdresatow.size(); i++)
    {
        Adresat dane_adresata = wektorAdresatow[i];
        if (stoi(numer) == dane_adresata.idUzytkownika)
        {
            plik << dane_adresata.id << "|";
            plik << numer << "|";
            plik << dane_adresata.imie << "|";
            plik << dane_adresata.nazwisko << "|";
            plik << dane_adresata.telefon << "|";
            plik << dane_adresata.email << "|";
            plik << dane_adresata.adres << "|";
            plik << endl;
        }
    }

    plik.close();
}

void dodajAdresata (string login)
{
    string id, imie, nazwisko, adres, email, telefon;
    fstream plik;

    vector <string> wektor_danych;
    wektor_danych=stworzWektor("Adresaci.txt");

    int idOstatniegoAdresata=0;

    if (wektor_danych.size()!=0)
    {
        idOstatniegoAdresata = atoi(wektor_danych[wektor_danych.size()-7].c_str());
    }

    plik.open("Adresaci.txt",ios::out | ios::app);

    cin.sync();

    plik << idOstatniegoAdresata+1 << "|";

    string numerUzytkownika=sprawdzIdDlaPodanegoLoginu(login);
    plik << numerUzytkownika << "|";

    cout << "Podaj imie: ";
    getline(cin, imie);
    plik << imie << "|" ;

    cout << "Podaj nazwisko: ";
    getline(cin, nazwisko);
    plik << nazwisko << "|" ;

    cout << "Podaj numer telefonu: ";
    getline(cin, telefon);
    plik << telefon << "|" ;

    cout << "Podaj numer adres e-mail: ";
    getline(cin, email);
    plik << email << "|" ;

    cout << "Podaj adres domowy (w jednej linii): ";
    getline(cin, adres);
    plik << adres << "|" ;

    plik << endl;

    plik.close();

    stworzPlikTymczasowy(login);
}

void wypiszStrukture(Adresat dane_adresata)
{
    cout << dane_adresata.id << endl;
    cout << dane_adresata.imie << endl;
    cout << dane_adresata.nazwisko << endl;
    cout << dane_adresata.telefon << endl;
    cout << dane_adresata.email << endl;
    cout << dane_adresata.adres << endl;
}

void wypiszAdresatowPoImieniu(string login)
{
    int iloscAdresatow=policz();

    if (iloscAdresatow == 0)
    {
        cout << "Nie masz jeszcze wpisow!" << endl;
    }

    else
    {
        string imie;
        cout << "Podaj imie do wyszukania: " << endl;
        cin >> imie;

        vector <Adresat> wektorAdresatow = stworzWektorStrukturZPliku("Adresaci-tymczasowy.txt");

        bool znaleziono=false;

        for (int i=0; i<wektorAdresatow.size(); i++)
        {
            if (imie == wektorAdresatow[i].imie)
            {
                znaleziono=true;
                wypiszStrukture(wektorAdresatow[i]);
            }
        }

        if (!znaleziono)
        {
            cout << "Nie znaleziono adresata o takim imieniu." << endl;
        }
    }
}

void wypiszAdresatowPoNazwisku(string login)
{
    int iloscAdresatow=policz();

    if (iloscAdresatow == 0)
    {
        cout << "Nie masz jeszcze wpisow!" << endl;
    }

    else
    {

        string nazwisko;
        cout << "Podaj nazwisko do wyszukania: " << endl;
        cin >> nazwisko;

        vector <Adresat> wektorAdresatow = stworzWektorStrukturZPliku("Adresaci-tymczasowy.txt");

        bool znaleziono=false;

        for (int i=0; i<wektorAdresatow.size(); i++)
        {
            if (nazwisko == wektorAdresatow[i].nazwisko)
            {
                znaleziono=true;
                wypiszStrukture(wektorAdresatow[i]);
            }
        }

        if (!znaleziono)
        {
            cout << "Nie znaleziono adresata o takim nazwisku." << endl;
        }
    }
}

bool wypiszAdresatowPoId(string id)
{
    vector <Adresat> wektorAdresatow = stworzWektorStrukturZPliku("Adresaci-tymczasowy.txt");

    bool znaleziono=false;

    for (int i=0; i<wektorAdresatow.size(); i++)
    {
        if (stoi(id) == wektorAdresatow[i].id)
        {
            znaleziono=true;
            wypiszStrukture(wektorAdresatow[i]);
        }
    }

    if (!znaleziono)
    {
        cout << "Nie znaleziono adresata o takim numerze id." << endl;
        return false;
    }
}

void wypiszAdresatow(string login)
{
    int iloscAdresatow=policz();

    if (iloscAdresatow == 0)
    {
        cout << "Nie masz jeszcze wpisow!" << endl;
    }

    else
    {
        vector <Adresat> wektorAdresatow = stworzWektorStrukturZPliku("Adresaci-tymczasowy.txt");

        for (int i=0; i<wektorAdresatow.size(); i++)
        {
            wypiszStrukture(wektorAdresatow[i]);
        }
    }
}

void synchronizujPliki (string login)
{
    vector <Adresat> wektorAdresatowGlownych, wektorAdresatowTymczasowych, wektorWynikowy;

    wektorAdresatowGlownych = stworzWektorStrukturZPliku("Adresaci.txt");
    wektorAdresatowTymczasowych = stworzWektorStrukturZPliku("Adresaci-tymczasowy.txt");

    int sprawdzoneID=stoi(sprawdzIdDlaPodanegoLoginu(login));

    for (int i=0; i<wektorAdresatowGlownych.size(); i++)
    {
        if (wektorAdresatowGlownych[i].idUzytkownika != sprawdzoneID)
        {
            wektorWynikowy.push_back(wektorAdresatowGlownych[i]);
        }
        else
        {
            for (int j=0; j<wektorAdresatowTymczasowych.size(); j++)
            {
                if (wektorAdresatowTymczasowych[j].id == wektorAdresatowGlownych[i].id)
                {
                    wektorWynikowy.push_back(wektorAdresatowTymczasowych[j]);
                }
            }
        }
    }

    fstream plik;
    plik.open("Adresaci.txt", ios::out);

    for (int i=0; i<wektorWynikowy.size(); i++)
    {

        Adresat dane_adresata = wektorWynikowy[i];

        plik << dane_adresata.id << "|";
        plik << dane_adresata.idUzytkownika << "|";
        plik << dane_adresata.imie << "|";
        plik << dane_adresata.nazwisko << "|";
        plik << dane_adresata.telefon << "|";
        plik << dane_adresata.email << "|";
        plik << dane_adresata.adres << "|";
        plik << endl;
    }

    plik.close();
}

void usun (string login)
{
    int iloscAdresatow=policz();

    if (iloscAdresatow == 0)
    {
        cout << "Nie masz jeszcze wpisow!" << endl;
    }

    else
    {
        string id;
        cout << "Podaj id adresata do usuniecia: ";
        cin >> id;

        if (wypiszAdresatowPoId(id)==false)
        {
            return;
        }

        cout << "Czy jestes pewien, ze chcesz usunac tego uzytkownika? Zatwierdz klawiszem 't'. " << endl;
        string odpowiedz;
        cin >> odpowiedz;

        if (odpowiedz != "t")
        {
            return;
        }
        else
        {
            vector <Adresat> wektorAdresatow = stworzWektorStrukturZPliku("Adresaci-tymczasowy.txt");
            fstream plik;
            plik.open("Adresaci-tymczasowy.txt", ios::out);

            for (int i=0; i<wektorAdresatow.size(); i++)
            {

                Adresat dane_adresata = wektorAdresatow[i];

                if (dane_adresata.id != stoi(id))
                {
                    plik << dane_adresata.id << "|";
                    plik << dane_adresata.idUzytkownika << "|";
                    plik << dane_adresata.imie << "|";
                    plik << dane_adresata.nazwisko << "|";
                    plik << dane_adresata.telefon << "|";
                    plik << dane_adresata.email << "|";
                    plik << dane_adresata.adres << "|";
                    plik << endl;
                }
            }

            plik.close();
        }

        cout << "Adresat zostal usuniety." << endl;
        synchronizujPliki(login);
    }
}

vector<Adresat> zmianaDanych(string id, string wybor, string dane_do_zmiany)
{

    vector<Adresat> wektor_ze_zmienionymi_danymi = stworzWektorStrukturZPliku("Adresaci-tymczasowy.txt");

    for (int i=0; i<wektor_ze_zmienionymi_danymi.size(); i++)
    {
        if (wektor_ze_zmienionymi_danymi[i].id == stoi(id) )
        {
            if (wybor == "1")
            {
                wektor_ze_zmienionymi_danymi[i].imie=dane_do_zmiany;
            }
            else if  (wybor == "2")
            {
                wektor_ze_zmienionymi_danymi[i].nazwisko=dane_do_zmiany;
            }
            else if (wybor == "3")
            {
                wektor_ze_zmienionymi_danymi[i].telefon=dane_do_zmiany;
            }
            else if (wybor == "4")
            {
                wektor_ze_zmienionymi_danymi[i].email=dane_do_zmiany;
            }
            else if (wybor == "5")
            {
                wektor_ze_zmienionymi_danymi[i].adres=dane_do_zmiany;
            }
        }
    }

    return wektor_ze_zmienionymi_danymi;
}

void edytuj(string login)
{
    int iloscAdresatow=policz();

    if (iloscAdresatow == 0)
    {
        cout << "Nie masz jeszcze wpisow!" << endl;
    }

    else
    {
        string id;
        cout << "Podaj id adresata do edycji: ";
        cin >> id;

        if (wypiszAdresatowPoId(id)==false)
        {
            return;
        }



        string wybor;

        do
        {
            //system ("cls");
            cout << endl;
            cout << "Podaj dane do zmiany:" << endl;
            cout << "1 - imie" << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - e-mail" << endl;
            cout << "5 - adres domowy" << endl;
            cout << "Twoj wybor: ";

            cin >> wybor;
            cout << endl;
        }
        while ((wybor != "1") && (wybor != "2") && (wybor != "3") && (wybor != "4") && (wybor != "5"));

        string dane_do_zmiany;
        cin.sync();

        if (wybor == "1")
        {
            cout << "Wybrales zmiane imienia" << endl;
            cout << "Podaj nowe imie: ";
            getline(cin, dane_do_zmiany);
            // cin >> dane_do_zmiany;
            // vector<Adresat> wektor_po_edycji=zmianaDanych(id,wybor,dane_do_zmiany);
        }
        else if (wybor == "2")
        {
            cout << "Wybrales zmiane nazwiska" << endl;
            cout << "Podaj nowe nazwisko: ";
            getline(cin, dane_do_zmiany);
            //   vector<Adresat> wektor_po_edycji=zmianaDanych(id,wybor,dane_do_zmiany);
        }
        else if (wybor == "3")
        {
            cout << "Wybrales zmiane numeru telefonu" << endl;
            cout << "Podaj nowy numer telefonu: ";
            getline(cin, dane_do_zmiany);
            // vector<Adresat> wektor_po_edycji=zmianaDanych(id,wybor,dane_do_zmiany);
        }
        else if (wybor == "4")
        {
            cout << "Wybrales zmiane adresu e-mail" << endl;
            cout << "Podaj nowy adres e-mail: ";
            getline(cin, dane_do_zmiany);
            // vector<Adresat> wektor_po_edycji=zmianaDanych(id,wybor,dane_do_zmiany);
        }
        else if (wybor == "5")
        {
            cout << "Wybrales zmiane adresu domowego" << endl;
            cout << "Podaj nowy adres domowy: ";
            getline(cin, dane_do_zmiany);
            // vector<Adresat> wektor_po_edycji=zmianaDanych(id,wybor,dane_do_zmiany);
        }
        vector<Adresat> wektor_po_edycji=zmianaDanych(id,wybor,dane_do_zmiany);

        fstream plik;

        plik.open("Adresaci-tymczasowy.txt", ios::out);

        for (int i=0; i<wektor_po_edycji.size(); i++)
        {
            Adresat dane_adresata = wektor_po_edycji[i];

            plik << dane_adresata.id << "|";
            plik << dane_adresata.idUzytkownika << "|";
            plik << dane_adresata.imie << "|";
            plik << dane_adresata.nazwisko << "|";
            plik << dane_adresata.telefon << "|";
            plik << dane_adresata.email << "|";
            plik << dane_adresata.adres << "|";
            plik << endl;

        }

        plik.close();

        cout << "Dane zostaly zmienione!" << endl;
        synchronizujPliki(login);
    }
}

void zmienHaslo(string login)
{
    fstream plik;
    string haslo;

    vector <string> wektor_danych;
    wektor_danych=stworzWektor("Uzytkownicy.txt");

    cout << "Podaj nowe haslo:" << endl;
    cin >> haslo;

    for (int i=0; i<wektor_danych.size()/3; i++)
    {
        if  (wektor_danych[i*3+1] == login)
        {
            wektor_danych[i*3+2] = haslo;
        }
    }

    plik.open("Uzytkownicy.txt",ios::out);

    for(int i=0; i<(wektor_danych.size()/3); i++)
    {
        for(int j=(i*3); j<(i*3+3); j++)
        {
            plik << wektor_danych[j] << "|";
        }
        plik << endl;
    }

    plik.close();

    cout << "Haslo zostalo zmienione!" <<endl;
    Sleep(1000);
}

void menuPoZalogowaniu(string login)
{
    while(1)
    {
        string wybor;
        system ("cls");
        cout << "MENU KSIAZKI ADRESOWEJ" << endl;
        cout << "------------------------------------" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "7. Zmien haslo" << endl;
        cout << "8. Wyloguj sie" << endl;
        cout << "------------------------------------" << endl;

        do
        {
            cin >> wybor;

            if (wybor == "1")
            {
                system ("cls");
                cout << "Wybrales dodanie adresata do ksiazki adresowej" << endl;
                dodajAdresata (login);
                system ("pause");
                continue;
            }

            else if (wybor == "2")
            {
                system ("cls");
                cout << "Wybrales wyszukiwanie po imieniu" << endl;
                stworzPlikTymczasowy(login);
                wypiszAdresatowPoImieniu(login);
                system ("pause");
                continue;
            }

            else if (wybor == "3")
            {
                system ("cls");
                cout << "Wybrales wyszukiwanie po nazwisku" << endl;
                stworzPlikTymczasowy(login);
                wypiszAdresatowPoNazwisku(login);
                system ("pause");
                continue;
            }

            else if (wybor == "4")
            {
                system ("cls");
                cout << "Wybrales wyswietlenie wszystkich adresatow z twojej ksiazki adresowej" << endl;
                stworzPlikTymczasowy(login);
                wypiszAdresatow(login);
                system ("pause");
                continue;
            }

            else if (wybor == "5")
            {
                system ("cls");
                cout << "Wybrales usuniecie adresata." << endl;
                usun(login);
                system ("pause");
                continue;
            }

            else if (wybor == "6")
            {
                system ("cls");
                cout << "Wybrales edycje adresata." << endl;
                edytuj(login);
                system ("pause");
                continue;
            }

            else if (wybor == "7")
            {
                system ("cls");
                cout << "Wybrales zmiane hasla." << endl;
                zmienHaslo(login);
                system ("pause");
                continue;
            }

            else if (wybor == "8")
            {
                system ("cls");
                cout << "Czy chcesz sie wylogowac? Zatwierdz wybierajac 't'." << endl;
                string odpowiedz;
                cin >> odpowiedz;
                if (odpowiedz=="t")
                {
                    cout << "Wylogowales sie poprawnie. Do zobaczenia!" << endl;
                    Sleep (2000);
                    return;
                }

            }

            else
            {
                cout << "Nieprawidlowy wybor" << endl;
            }
        }
        while ((wybor != "1") && (wybor != "2") && (wybor != "3") && (wybor != "4") && (wybor != "5") && (wybor != "6") && (wybor != "7") && (wybor != "8"));
    }
}

void logowanie()
{
    while(1)
    {
        string login, haslo;

        cout << "Podaj login: ";
        cin >> login;

        if (sprawdzLogin(login) == false)
        {
            cout << "Nie ma takiego uzytkownika!" << endl;
            continue;
        }

        else
        {
            for (int proba=0; proba<3; proba++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3-proba << ": " << endl;
                cin >> haslo;

                string sprawdzoneHaslo=sprawdzHasloDlaPodanegoLoginu(login);

                if (sprawdzoneHaslo == haslo)
                {
                    cout << "Haslo poprawne!" << endl;
                    string numer=sprawdzIdDlaPodanegoLoginu(login);
                    cout << "Twoj numer ID to: " << numer << endl;
                    Sleep(1000);
                    cout << "Zalogowales sie poprawnie!" << endl;
                    Adresat adresaci;
                    stworzPlikTymczasowy(login);
                    menuPoZalogowaniu(login);
                    return;
                }
            }
            cout << "Podales 3 razy zle haslo" <<endl;
            Sleep(5000);
            break;
        }
    }
}

void rejestracja()
{
    vector<Uzytkownik> uzytkownicy;
    int iloscUzytkownikow = 0;
    cout << "Wprowadz dane swoje dane. Zostana one zapisane w pliku Uzytkownicy.txt" << endl;

    zapiszUzytkownika();

    cout << endl;
    cout << "Rejestracja przebiegla pomyslnie!" << endl;
    cout << endl;
}

int main()
{
    while (1)
    {
        string wybor;
        system ("cls");
        cout << "MENU GLOWNE" << endl;
        cout << "--------------------------" << endl;
        cout << "1 - Logowanie" << endl;
        cout << "2 - Rejestracja" << endl;
        cout << "3 - Zamknij program" << endl;
        cout << "--------------------------" << endl;

        do
        {
            cin >> wybor;

            if (wybor == "1")
            {
                system ("cls");
                cout << "Wybrales logowanie" << endl;
                logowanie();
            }

            else if (wybor == "2")
            {
                system ("cls");
                cout << "Wybrales rejestracje" << endl;
                rejestracja();
                system("pause");
            }

            else if (wybor == "3")
            {
                system ("cls");
                cout << "Wybrales zamkniecie programu" << endl;
                return 0;
            }

            else
            {
                cout << "Nieprawidlowy wybor" << endl;
            }
        }
        while ((wybor != "1") && (wybor != "2") && (wybor != "3"));
    }
    return 0;
}
