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
    int id;
    string imie,nazwisko,adres,email,telefon;
};

int DodawanieKontaktu(vector<Kontakt> &osoby, int id)
{
    int iloscKontaktow=osoby.size();
    if(!osoby.empty())
    {
        id = osoby[iloscKontaktow-1].id;
    }
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


    plik.open("ksiazka Adresowa.txt",ios::out|ios::app);

    if (plik.good())
    {
        plik<<osoby[iloscKontaktow].id<<"|";
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
int WczytajDaneDoTablicy(vector<Kontakt> &osoba)
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
        osoba.push_back(Kontakt());
        stringstream ss(linia);
        while (getline(ss, item, '|'))
        {
            switch(nr_pola)
            {
            case 1:
                osoba[j].id=atoi(item.c_str());
                break;
            case 2:
                osoba[j].imie=item;
                break;
            case 3:
                osoba[j].nazwisko=item;
                break;
            case 4:
                osoba[j].telefon=item;
                break;
            case 5:
                osoba[j].email=item;
                break;
            case 6:
                osoba[j].adres=item;
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
void Edytowanie(vector<Kontakt>&osoby, int id)
{
    cout<<"podaj id osoby ktora chcesz edytowac "<<endl;
    cin>>id;
    system ("cls");
    char wybor;
    string ZmienianePole;
    cout<<"1 - imie"<<endl;
    cout<<"2 - nazwisko"<<endl;
    cout<<"3 - numer telefonu"<<endl;
    cout<<"4 - email"<<endl;
    cout<<"5 - adres"<<endl;

    for(int i=0; i<osoby.size(); i++)
    {
        if(osoby[i].id==id)
        {
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
                cin>>osoby[i].adres;
                break;
            }
        }
    }
    ZapisWektoraDoPliku(osoby);

    cout<<"dane zostaly zmienione";
    Sleep(1500);
}
UsunKontakty(vector<Kontakt>&osoby)
{
    int id;
    char wybor;
    cout<<"Podaj id osoby, ktora chcesz usunac z listy kontaktow"<<endl;
    cin>>id;
    for(int i=0; i<osoby.size(); i++)
    {
        if(osoby[i].id==id)
        {
            cout<<"Czy na pewno chcesz usunac ten kontakt t/n ?"<<endl;
            cin>>wybor;
            if(wybor=='t')
            {
                osoby.erase(osoby.begin()+i);
                cout<<"kontakt usuniety";
                Sleep(1000);
            }
        }
    }
    ZapisWektoraDoPliku(osoby);
}
int main()
{
    char wybor;
    int id=0;
    vector<Kontakt> osoby;
    id=WczytajDaneDoTablicy(osoby);

    while(true)
    {
        system ("cls");
        cout<<">>KSIAZKA ADRESOWA<<"<<endl;
        cout<<"1. Dodaj nowy kontakt "<<endl;
        cout<<"2. Szukaj po imieniu "<<endl;
        cout<<"3. Szukaj po nazwisku "<<endl;
        cout<<"4. Wyowietl wszystkie kontakty"<<endl;
        cout<<"5. Edytuj kontakty"<<endl;
        cout<<"6. Usun kontakty"<<endl;
        cout<<"7. zakoncz program "<<endl;
        cout<<"Twoj wybor:  "<<endl;

        cin>>wybor;

        if(wybor=='1')
        {
            id=DodawanieKontaktu(osoby,id);
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
            Edytowanie(osoby,id);
        }
        else if(wybor=='6')
        {
            UsunKontakty(osoby);
        }
        else if (wybor=='7')
        {
            exit (0);
        }
        else
        {
            cout<<"Nie ma takiej opcji. Wybiersz numer od 1 do 4"<<endl;
            Sleep(1500);
        }
    }
    return 0;
}
