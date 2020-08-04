#include <iostream>
#include<windows.h>
#include<cstdlib>
#include<conio.h>
#include<string>
#include<fstream>
#include<vector>
#include <sstream>
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


int DodawanieKontaktu(vector<Kontakt> &osoby, int id, int idUzytkownika)
{
    int iloscKontaktow=osoby.size();


    fstream plik;
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


    plik.open("ksiazka Adresowa.txt",ios::out|ios::app);

    if (plik.good())
    {
        plik<<osoby[iloscKontaktow].id<<"|";
        plik<<idUzytkownika<<"|";
        plik<<osoby[iloscKontaktow].imie<<"|";
        plik<<osoby[iloscKontaktow].nazwisko<<"|";
        plik<<osoby[iloscKontaktow].telefon<<"|";
        plik<<osoby[iloscKontaktow].email<<"|";
        plik<<osoby[iloscKontaktow].adres<<"|";
        plik<<endl;
        plik.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: ksiazka Adresowa.txt" << endl;
        Sleep(1500);
    }
    system ("cls");
    cout<<"Dodano nowy kontakt"<<endl;
    Sleep(1500);

    return id+1;
}
ZapisWektoraDoPliku(vector<Kontakt>&osoby)
{
    fstream plik;
    plik.open("ksiazka Adresowa.txt",ios::out);
    for(int j=0; j<osoby.size(); j++)
    {
        if (plik.good())
        {
            plik<<osoby[j].id<<"|";
            plik<<osoby[j].idUzytkownika<<"|";
            plik<<osoby[j].imie<<"|";
            plik<<osoby[j].nazwisko<<"|";
            plik<<osoby[j].telefon<<"|";
            plik<<osoby[j].email<<"|";
            plik<<osoby[j].adres<<"|";
            plik<<endl;
        }
        else
        {
            cout << "Nie mozna otworzyc pliku: ksiazka Adresowa.txt" << endl;
            Sleep(1500);
        }
    }
    plik.close();
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
        cout<<"Znaleziono "<<licznik<<" wynikow.";
        cout<<" Czy kontynuowac szukanie? t/n"<<endl;
        cin>>znak;
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
        cout<<"Znaleziono "<<licznik<<" wynikow.";
        cout<<" Czy kontynuowac szukanie? t/n"<<endl;
        cin>>znak;
        system ("cls");
    }
}
int WczytajCalyPlik(vector<Kontakt> &WszyskieKontakty)
{
fstream plik;
    plik.open("ksiazka Adresowa.txt",ios::in);

    if (plik.good()==false)
    {
        cout<<"plik nie istnieje! zostanie on utworzny przy dodaniu pierwszego kontaktu"<<endl;
        Sleep(1000);
        return (0);
    }
    string linia,item;
    int nr_lini=1, j=0;
    while(getline(plik,linia))
    {
        int nr_pola=1;
        WszyskieKontakty.push_back(Kontakt());
        stringstream ss(linia);
        while (getline(ss, item, '|'))
        {
            switch(nr_pola)
            {
            case 1:
                WszyskieKontakty[j].id=atoi(item.c_str());
                break;
            case 2:
                WszyskieKontakty[j].idUzytkownika=atoi(item.c_str());
                break;
            case 3:
                WszyskieKontakty[j].imie=item;
                break;
            case 4:
                WszyskieKontakty[j].nazwisko=item;
                break;
            case 5:
                WszyskieKontakty[j].telefon=item;
                break;
            case 6:
                WszyskieKontakty[j].email=item;
                break;
            case 7:
                WszyskieKontakty[j].adres=item;
                break;
            }
            nr_pola++;
        }
        j++;
        nr_lini++;
    }
    plik.close();
    return j;
}


int WczytajDaneDoTablicy(vector<Kontakt> &osoba, int idUzytkownika)
{

    fstream plik;
    plik.open("ksiazka Adresowa.txt",ios::in);

    if (plik.good()==false)
    {
        cout<<"plik nie istnieje! zostanie on utworzny przy dodaniu pierwszego kontaktu"<<endl;
        Sleep(1000);
        return (0);
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
    return id1;
}
void WyswietlWszystkieKontakty(vector<Kontakt> &osoby,int id)
{
    int iloscKontaktow=osoby.size();
    system ("cls");
    cout<<"W Twojej ksiazce jest "<<id<<" kontaktow:"<<endl;
    for(int i=0; i<iloscKontaktow; i++)
    {
        cout<<"id: "<<osoby[i].id<<endl;
        WyswitlanieWynikuWyszukiwania(osoby,i);
    }
    cout<<"Aby wrocic do menu wcisnij dowolny kalwisz"<<endl;
    getch();
}
void Edytowanie(vector<Kontakt>&osoby,vector<Kontakt> &WszystkieKontakty)
{
    WczytajCalyPlik(WszystkieKontakty);
    int id;
    cout<<"podaj id osoby ktora chcesz edytowac "<<endl;
    cin>>id;
    system ("cls");
    char wybor;
    cout<<"1 - imie"<<endl;
    cout<<"2 - nazwisko"<<endl;
    cout<<"3 - numer telefonu"<<endl;
    cout<<"4 - email"<<endl;
    cout<<"5 - adres"<<endl;

    int iloscKontaktow=WszystkieKontakty.size();
    for(int i=0; i<iloscKontaktow; i++)
    {
        if(WszystkieKontakty[i].id==id)
        {
            cin>>wybor;
            switch(wybor)
            {
            case '1':
                cout<<"Podaj nowe imie"<<endl;
                cin>>WszystkieKontakty[i].imie;
                break;
            case '2':
                cout<<"Podaj nowe nazwisko"<<endl;
                cin>>WszystkieKontakty[i].nazwisko;
                break;
            case '3':
                cout<<"Podaj nowy numer telefonu"<<endl;
                cin>>WszystkieKontakty[i].telefon;
                break;
            case '4':
                cout<<"Podaj nowy email"<<endl;
                cin>>WszystkieKontakty[i].email;
                break;
            case '5':
                cout<<"Podaj nowy adres"<<endl;
                cin>>WszystkieKontakty[i].adres;
                break;
            }
        }
    }

    ZapisWektoraDoPliku(WszystkieKontakty);

    cout<<"dane zostaly zmienione";
    Sleep(1500);
}

    void UsunKontakty(vector<Kontakt>&osoby,vector<Kontakt> WszyskieKontakty)
{
    WczytajCalyPlik(WszyskieKontakty);
    int id;
    char wybor;
    cout<<"Podaj id osoby, ktora chcesz usunac z listy kontaktow"<<endl;
    cin>>id;
    for(int i=0; i< WszyskieKontakty.size(); i++)
    {
        if( WszyskieKontakty[i].id==id)
        {
            cout<<"Czy na pewno chcesz usunac ten kontakt t/n ?"<<endl;
            cin>>wybor;
            if(wybor=='t')
            {
                 WszyskieKontakty.erase( WszyskieKontakty.begin()+i);
                cout<<"kontakt usuniety";
                Sleep(1500);
            }
        }
    }
    ZapisWektoraDoPliku( WszyskieKontakty);
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
            else cout<<"Bledne haslo"<<endl;
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
    vector<Kontakt> osoby;
    vector<Uztkownicy> NowyUzytkownik;
    vector<Uztkownicy> ListaUzytkownikow;
    vector<Kontakt> WszyskieKontakty;


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


    id=WczytajDaneDoTablicy(osoby,idUzytkownika);
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
            id=DodawanieKontaktu(osoby,id,idUzytkownika);
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
            Edytowanie(osoby,WszyskieKontakty);
            osoby.clear();
            WczytajDaneDoTablicy(osoby,idUzytkownika);
            WszyskieKontakty.clear();

        }
        else if(wybor=='6')
        {
            UsunKontakty(osoby,WszyskieKontakty);
            osoby.clear();
            WczytajDaneDoTablicy(osoby,idUzytkownika);
            WszyskieKontakty.clear();
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
