#include <iostream>
#include<windows.h>
#include<cstdlib>
#include<conio.h>
#include<string>
#include<fstream>
#include<vector>
#include <sstream>
#include <cstdio>
using namespace std;

struct Kontakt
{
    int id,idUzytkownika;
    string imie,nazwisko,adres,email,telefon;
};
struct Uztkownicy
{
    int idUzytkownika;
    string nazwa,haslo;
};
void ZapisWektoraDoPliku(vector<Kontakt>&osoby, int itr)
{
    fstream plik;
    plik.open("ksiazka Adresowa.txt",ios::out|ios::app);

    if (plik.good())
    {
        plik<<osoby[itr].id<<"|";
        plik<<osoby[itr].idUzytkownika<<"|";
        plik<<osoby[itr].imie<<"|";
        plik<<osoby[itr].nazwisko<<"|";
        plik<<osoby[itr].telefon<<"|";
        plik<<osoby[itr].email<<"|";
        plik<<osoby[itr].adres<<"|";
        plik<<endl;
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: ksiazka Adresowa.txt" << endl;
        Sleep(1500);
    }
    plik.close();
}
int NadawanieIdDoKontaku()
{
    string OstatniaLinia,item;
    int id;
    fstream plik;
    plik.open("ksiazka Adresowa.txt",ios::in);
    if (plik.good()==false)
    {
        id=0;
    }
    else
    {
        while(getline(plik,OstatniaLinia))
        {
            stringstream ss(OstatniaLinia);
            getline(ss, item, '|');
            id=atoi(item.c_str());
        }
    }
    return id;
}
int DodawanieKontaktu(vector<Kontakt> &osoby,int idUzytkownika)
{
    int id=NadawanieIdDoKontaku();
    int iloscKontaktow=osoby.size();

    osoby.push_back(Kontakt());
    cout<<"podaj imie"<<endl;
    cin>>osoby[iloscKontaktow].imie;
    cout<<"podaj nazwisko"<<endl;
    cin>>osoby[iloscKontaktow].nazwisko;
    cout<<"podaj numer telefonu"<<endl;
    cin>>osoby[iloscKontaktow].telefon;
    cout<<"podaj adres email"<<endl;
    cin>>osoby[iloscKontaktow].email;
    cout<<"podaj adres"<<endl;
    cin.sync();
    getline(cin,osoby[iloscKontaktow].adres);
    osoby[iloscKontaktow].id=id+1;
    osoby[iloscKontaktow].idUzytkownika=idUzytkownika;

    ZapisWektoraDoPliku(osoby,iloscKontaktow);

    system ("cls");
    cout<<"Dodano nowy kontakt"<<endl;
    Sleep(1500);

    return id+1;
}
void WyswitlanieWynikuWyszukiwania(vector<Kontakt> &osoby, int NumerZnalenionejOsoby)
{
    cout<<osoby[NumerZnalenionejOsoby].imie<<" "<<osoby[NumerZnalenionejOsoby].nazwisko<<endl;
    cout<<"Nr tel: "<<osoby[NumerZnalenionejOsoby].telefon<<endl;
    cout<<"email: "<<osoby[NumerZnalenionejOsoby].email<<endl;
    cout<<"adres: "<<osoby[NumerZnalenionejOsoby].adres<<endl;
    cout<<endl;
}
void SzukajPoImieniu(vector<Kontakt> &osoby,int id)
{
    string szukaneImie;
    char znak='t';
    while(znak=='t')
    {
        cout<<"wpisz szukana fraza "<<endl;
        cin>>szukaneImie;
        int licznik=0;
        for(int i=0; i<id; i++)
        {
            if(osoby[i].imie==szukaneImie)
            {
                WyswitlanieWynikuWyszukiwania(osoby,i);
                licznik++;
            }
        }
        system ("cls");
    }
}
void SzukajPoNazwisku(vector<Kontakt> &osoby,int id)
{
    string szukaneNazwisko;
    char znak='t';
    while(znak=='t')
    {
        cout<<"wpisz szukana fraza "<<endl;
        cin>>szukaneNazwisko;
        int licznik=0;
        for(int i=0; i<id; i++)
        {
            if(osoby[i].nazwisko==szukaneNazwisko)
            {
                WyswitlanieWynikuWyszukiwania(osoby,i);
                licznik++;
            }
        }
        system ("cls");
    }
}
void WczytajDaneDoTablicy(vector<Kontakt> &osoba, int idUzytkownika)
{
    fstream plik;
    plik.open("ksiazka Adresowa.txt",ios::in);

    if (plik.good()==false)
    {
        cout<<"plik nie istnieje! zostanie on utworzny przy dodaniu pierwszego kontaktu"<<endl;
        Sleep(1000);

    }
    string linia,item, imie1, nazwisko1, telefon1, email1, adres1;
    int nr_lini=1, j=0,id1=0,idUzytkownika1;
    while(getline(plik,linia))
    {
        int nr_pola=1;
        stringstream ss(linia);
        while (getline(ss, item, '|'))
        {
            switch(nr_pola)
            {
            case 1:
                id1=atoi(item.c_str());
                break;
            case 2:
                idUzytkownika1=atoi(item.c_str());
                break;
            case 3:
                imie1=item;
                break;
            case 4:
                nazwisko1=item;
                break;
            case 5:
                telefon1=item;
                break;
            case 6:
                email1=item;
                break;
            case 7:
                adres1=item;
                break;
            }
            nr_pola++;
        }
        if(idUzytkownika==idUzytkownika1)
        {
            osoba.push_back(Kontakt());
            osoba[j].id=id1;
            osoba[j].idUzytkownika=idUzytkownika1;
            osoba[j].imie=imie1;
            osoba[j].nazwisko=nazwisko1;
            osoba[j].telefon=telefon1;
            osoba[j].email=email1;
            osoba[j].adres=adres1;
            j++;
        }
        nr_lini++;
    }
    plik.close();
}
void WyswietlWszystkieKontakty(vector<Kontakt> &osoby,int id)
{
    int iloscKontaktow=osoby.size();
    system ("cls");
    cout<<"W Twojej ksiazce jest "<<iloscKontaktow<<" kontaktow:"<<endl;
    for(int i=0; i<iloscKontaktow; i++)
    {
        cout<<"id: "<<osoby[i].id<<endl;
        WyswitlanieWynikuWyszukiwania(osoby,i);
    }
    cout<<"Aby wrocic do menu wcisnij dowolny kalwisz"<<endl;
    getch();
}
int Edytowanie(vector<Kontakt>&osoby)
{
    cout<<"podaj id"<<endl;
    int id;
    cin>>id;
    system ("cls");
    char wybor;

    int iloscKontaktow=osoby.size();
    for(int i=0; i<iloscKontaktow; i++)
    {
        if(osoby[i].id==id)
        {
            cout<<"1 - imie"<<endl;
            cout<<"2 - nazwisko"<<endl;
            cout<<"3 - numer telefonu"<<endl;
            cout<<"4 - email"<<endl;
            cout<<"5 - adres"<<endl;
            cin>>wybor;
            switch(wybor)
            {
            case '1':
                cout<<"Podaj nowe imie"<<endl;
                cin>>osoby[i].imie;
                break;
            case '2':
                cout<<"Podaj nowe nazwisko"<<endl;
                cin>>osoby[i].nazwisko;
                break;
            case '3':
                cout<<"Podaj nowy numer telefonu"<<endl;
                cin>>osoby[i].telefon;
                break;
            case '4':
                cout<<"Podaj nowy email"<<endl;
                cin>>osoby[i].email;
                break;
            case '5':
                cout<<"Podaj nowy adres"<<endl;
                cin.sync();
                getline(cin,osoby[i].adres);
                break;
            }
            cout<<"dane zostaly zmienione";
            return id;
        }
    }
    cout<<"Nie mozna edytowac kontaktu o takim id";
    Sleep(1500);
    return 0;
}
int PrzepisanieDoPliku(vector<Kontakt>&osoby, int id, bool WpisUsuniety)
{
    string linia, item;
    int id1;
    fstream plik;
    fstream plikTymczas;
    plik.open("ksiazka Adresowa.txt",ios::in);

    plikTymczas.open("Adresaci Tymczasowi.txt",ios::out|ios::app);

    int j=0;
    while(getline(plik,linia))
    {
        stringstream ss(linia);
        getline(ss, item, '|');
        id1=atoi(item.c_str());
        if (plik.good()==false)
        {
            cout<<"probem z pilkiem w funkcji edytowanie"<<endl;
            Sleep(1500);
            return (0);
        }

        if (plikTymczas.good())
        {
            if (id1==id)
            {
                if(WpisUsuniety==false)
                {
                    plikTymczas<<osoby[j].id<<"|";
                    plikTymczas<<osoby[j].idUzytkownika<<"|";
                    plikTymczas<<osoby[j].imie<<"|";
                    plikTymczas<<osoby[j].nazwisko<<"|";
                    plikTymczas<<osoby[j].telefon<<"|";
                    plikTymczas<<osoby[j].email<<"|";
                    plikTymczas<<osoby[j].adres<<"|";
                    plikTymczas<<endl;
                }
            }
            else
            {
                plikTymczas<<linia;
                plikTymczas<<endl;
            }
        }
        j++;
    }
    plik.close();
    plikTymczas.close();
    remove("ksiazka Adresowa.txt");
    rename( "Adresaci Tymczasowi.txt","ksiazka Adresowa.txt") ;
}

int UsunKontakty(vector<Kontakt>&osoby)
{
    int id;
    char wybor;
    cout<<"Podaj id osoby, ktora chcesz usunac z listy kontaktow"<<endl;
    cin>>id;
    for(int i=0; i<osoby.size(); i++)
    {
        if( osoby[i].id==id)
        {
            cout<<"Czy na pewno chcesz usunac ten kontakt t/n ?"<<endl;
            cin>>wybor;
            if(wybor=='t')
            {
                osoby.erase( osoby.begin()+i);
                cout<<"kontakt usuniety";
                Sleep(2000);
                return id;
            }
        }
    }
    cout<<"Nie mozna usunac kontaktu o takim id";
    Sleep(2000);
    return 0;
}
int WczytajUzytkownikow(vector<Uztkownicy> &ListaUzytkownikow)
{
    fstream plik;
    plik.open("Uzytkownicy.txt",ios::in);
    if (plik.good()==false)
    {
        cout<<"Brak uzytkownikow musisz sie zarejestrowac"<<endl;
        Sleep(1500);
        system("cls");
        return (0);
    }
    string linia,item;
    int nr_lini=1, j=0;
    while(getline(plik,linia))
    {
        int nr_pola=1;
        ListaUzytkownikow.push_back(Uztkownicy());
        stringstream ss(linia);
        while (getline(ss, item, '|'))
        {
            switch(nr_pola)
            {
            case 1:
                ListaUzytkownikow[j].idUzytkownika=atoi(item.c_str());
                break;
            case 2:
                ListaUzytkownikow[j].nazwa=item;
                break;
            case 3:
                ListaUzytkownikow[j].haslo=item;
                break;
            }
            nr_pola++;
        }
        j++;
        nr_lini++;
    }
    plik.close();
    return ListaUzytkownikow.size();
}

int logowanie(vector<Uztkownicy> &ListaUzytkownikow)
{
    string nazwa,haslo;
    cout<<"Podaj nazwe uzytkownika"<<endl;
    cin>>nazwa;
    for(int i =0; i<ListaUzytkownikow.size(); i++)
    {
        while (nazwa==ListaUzytkownikow[i].nazwa)
        {
            cout<<"Podaj haslo"<<endl;
            cin>>haslo;
            if(haslo==ListaUzytkownikow[i].haslo)
            {
                cout<<"Udalo sie zalogowac"<<endl;
                Sleep(1500);
                return ListaUzytkownikow[i].idUzytkownika;
            }
            else
                cout<<"Bledne haslo"<<endl;
        }
    }
    cout<<"Nie ma uzytkownika o takiej nazwie"<<endl;
    return 0;
}
int RejestracjaNowegoUzytkownika(vector<Uztkownicy> &uzytkownik)
{
    int iloscKontaktow=uzytkownik.size();

    fstream plik;
    uzytkownik.push_back(Uztkownicy());
    cout<<"podaj nazwe uzytkownika"<<endl;
    cin>>uzytkownik[iloscKontaktow].nazwa;
    cout<<"podaj haslo"<<endl;
    cin>>uzytkownik[iloscKontaktow].haslo;
    cin.sync();

    uzytkownik[iloscKontaktow].idUzytkownika=iloscKontaktow+1;

    plik.open("Uzytkownicy.txt",ios::out|ios::app);

    if (plik.good())
    {
        plik<<uzytkownik[iloscKontaktow].idUzytkownika<<"|";
        plik<<uzytkownik[iloscKontaktow].nazwa<<"|";
        plik<<uzytkownik[iloscKontaktow].haslo<<"|";
        plik<<endl;
        plik.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: ksiazka Adresowa.txt" << endl;
        Sleep(1500);
    }
    cout<<"Dodano nowego uzytkownika"<<endl;
    system ("cls");
    Sleep(1500);
}
int main()
{
    char wybor;
    int id=0,idUzytkownika=0;
    bool WpisUsuniety;
    vector<Kontakt> osoby;
    vector<Uztkownicy> NowyUzytkownik;
    vector<Uztkownicy> ListaUzytkownikow;

    WczytajUzytkownikow(ListaUzytkownikow);
    while(idUzytkownika==0)
    {
        cout<<"1. Logowanie"<<endl;
        cout<<"2. Rejestracja"<<endl;
        cout<<"3. zakoncz"<<endl;

        cin>>wybor;
        switch(wybor)
        {
        case '1':
            idUzytkownika=logowanie(ListaUzytkownikow);
            break;
        case '2':
            RejestracjaNowegoUzytkownika(ListaUzytkownikow);
            break;
        case '3':
            exit (0);
        }

        WczytajDaneDoTablicy(osoby,idUzytkownika);
        while(idUzytkownika!=0)
        {
            system ("cls");
            cout<<">>KSIAZKA ADRESOWA<<"<<endl;
            cout<<"1. Dodaj nowy kontakt "<<endl;
            cout<<"2. Szukaj po imieniu "<<endl;
            cout<<"3. Szukaj po nazwisku "<<endl;
            cout<<"4. Wyowietl wszystkie kontakty"<<endl;
            cout<<"5. Edytuj kontakty"<<endl;
            cout<<"6. Usun kontakty"<<endl;
            cout<<"7. Wyloguj "<<endl;
            cout<<"Twoj wybor:  "<<endl;

            cin>>wybor;

            if(wybor=='1')
            {
                DodawanieKontaktu(osoby,idUzytkownika);
            }
            else if (wybor=='2')
            {
                system ("cls");

                SzukajPoImieniu(osoby,id);
            }
            else if(wybor=='3')
            {
                system ("cls");
                SzukajPoNazwisku(osoby,id);
            }

            else if (wybor=='4')
            {
                WyswietlWszystkieKontakty(osoby,id);
            }
            else if(wybor=='5')
            {
                id=Edytowanie(osoby);
                WpisUsuniety=false;
                if (id!=0)
                {
                    PrzepisanieDoPliku(osoby,id,WpisUsuniety);
                }
            }
            else if(wybor=='6')
            {
                id=UsunKontakty(osoby);
                WpisUsuniety=true;
                if (id!=0)
                {
                    PrzepisanieDoPliku(osoby,id,WpisUsuniety);
                }
            }
            else if (wybor=='7')
            {
                idUzytkownika=0;
                osoby.clear();
                system("cls");
            }
            else
            {
                cout<<"Nie ma takiej opcji. Wybiersz numer od 1 do 4"<<endl;
                Sleep(1500);
            }
        }
    }
    return 0;
}
