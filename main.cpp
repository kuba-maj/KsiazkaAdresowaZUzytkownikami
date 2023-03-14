#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cstdio>

using namespace std;

struct Uzytkownik
{
    int idUzytkownika = 0;
    string nazwa = "", haslo = "";
};

struct Adresat
{
    int idAdresata = 0;
    int idUzytkownika = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

void wczytajUzytkownikow(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownik;
    string nazwaUzytkownika = "", haslo = "";
    fstream plik;
    int pozycjaSeparatora = 0;
    string wycinekLinii = "";
    int iloscZnakow = 0;
    plik.open("Uzytkownicy.txt", ios::in);
    if (plik.good() == false)
    {
        cout << "Plik nie istnieje" << endl;
    }
    else if (plik.good() == true)
    {
        while(getline(plik, wycinekLinii, '|'))
        {
            switch(iloscZnakow)
            {
            case 0:
                uzytkownik.idUzytkownika = atoi( wycinekLinii.c_str() );
                break;
            case 1:
                uzytkownik.nazwa = wycinekLinii;
                break;
            case 2:
                uzytkownik.haslo = wycinekLinii;
                break;
            }
            if( pozycjaSeparatora == 2 )
            {
                uzytkownicy.push_back(uzytkownik);
                iloscZnakow = 0;
                pozycjaSeparatora = 0;
            }
            else
            {
                iloscZnakow++;
                pozycjaSeparatora++;
            }
        }
    }
    plik.close();
}

int wczytajAdresatow(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    Adresat adresat;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
    int liczbaWszystkichAdresatow = 0;
    fstream plik;
    int pozycjaSeparatora = 0;
    string wycinekLinii = "";
    int iloscZnakow = 0;
    adresaci.clear();
    plik.open("KsiazkaAdresowa.txt", ios::in);
    if (plik.good() == false)
    {
        cout << "Plik nie istnieje" << endl;
    }
    else if (plik.good() == true)
    {
        while(getline(plik, wycinekLinii, '|'))
        {
            switch( iloscZnakow )
            {
            case 0:
                adresat.idAdresata = atoi( wycinekLinii.c_str() );
                break;
            case 1:
                adresat.idUzytkownika = atoi(wycinekLinii.c_str());
                break;
            case 2:
                adresat.imie = wycinekLinii;
                break;
            case 3:
                adresat.nazwisko = wycinekLinii;
                break;
            case 4:
                adresat.numerTelefonu = wycinekLinii;
                break;
            case 5:
                adresat.email = wycinekLinii;
                break;
            case 6:
                adresat.adres = wycinekLinii;
                break;
            }

            if(pozycjaSeparatora == 6)
            {
                iloscZnakow = 0;
                pozycjaSeparatora = 0;
                liczbaWszystkichAdresatow++;
                if(adresat.idUzytkownika == idZalogowanegoUzytkownika)
                {
                    adresaci.push_back(adresat);
                }
            }

            else
            {
                iloscZnakow++;
                pozycjaSeparatora++;
            }
        }
    }
    plik.close();
    return liczbaWszystkichAdresatow;
}

int rejestracja(vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow)
{
    Uzytkownik uzytkownik;
    int idUzytkownika = 1;
    string nazwaUzytkownika="", haslo="", nazwa="";
    fstream plik;
    system("cls");
    if (uzytkownicy.size() == 0)
    {
        idUzytkownika = 1;
    }
    else
    {
        idUzytkownika = uzytkownicy[uzytkownicy.size() - 1].idUzytkownika + 1;
    }

    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwaUzytkownika;
    while (iloscUzytkownikow < uzytkownicy.size())
    {
        if (uzytkownicy[iloscUzytkownikow].nazwa == nazwaUzytkownika)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwaUzytkownika;
            iloscUzytkownikow = 0;
        }
        else
        {
            iloscUzytkownikow++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;
    uzytkownik.idUzytkownika = idUzytkownika;
    uzytkownik.nazwa = nazwaUzytkownika;
    uzytkownik.haslo = haslo;
    uzytkownicy.push_back(uzytkownik);
    plik.open("Uzytkownicy.txt", ios::out | ios::app);

    plik << idUzytkownika << "|";
    plik << nazwaUzytkownika << "|";
    plik << haslo << "|" << endl;
    cout << "Konto zalozone" << endl;
    Sleep(2000);
    plik.close();
    return idUzytkownika;
}

int logowanie(vector <Uzytkownik> &uzytkownicy)
{
    string nazwaUzytkownika="", hasloUzytkownika="";
    int iloscUzytkownikow = 0;
    int idZalogowanegoUzytkownika = 0;
    system("cls");
    cout << "Podaj login: ";
    cin >> nazwaUzytkownika;
    while(iloscUzytkownikow < uzytkownicy.size())
    {
        if (uzytkownicy[iloscUzytkownikow].nazwa == nazwaUzytkownika)
        {
            for (int proby = 0; proby < 3; proby++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3 - proby << " : ";
                cin >> hasloUzytkownika;
                if (uzytkownicy[iloscUzytkownikow].haslo == hasloUzytkownika)
                {
                    cout << "Zalogowales sie" << endl;
                    idZalogowanegoUzytkownika++;
                    Sleep(3000);
                    return uzytkownicy[iloscUzytkownikow].idUzytkownika;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(3000);
            return 0;
        }
        iloscUzytkownikow++;
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(2000);
    return idZalogowanegoUzytkownika;
}

void dodajNowaOsobe(vector <Adresat> &adresaci, int idUzytkownika, int liczbaWszystkichAdresatow, int idOstatniegoAdresata)
{
    Adresat adresat;
    int idAdresata = 0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
    fstream plik;

    if (liczbaWszystkichAdresatow == 0)
    {
        idAdresata = 1;
    }
    else
    {
        idAdresata = idOstatniegoAdresata + 1;
    }
    system("cls");

    cout << "Dodawanie nowego adresata" << endl;
    cout << "Podaj imie uzytkownika: ";
    cin >> imie;
    cout << "Podaj nazwisko uzytkownika: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu uzytkownika: ";
    cin.sync();
    getline(cin, numerTelefonu);
    cout << "Podaj email uzytkownika: ";
    cin >> email;
    cout << "Podaj adres uzytkownika: ";
    cin.sync();
    getline(cin, adres);

    adresat.idAdresata = idAdresata;
    adresat.idUzytkownika = idUzytkownika;
    adresat.imie = imie;
    adresat.nazwisko = nazwisko;
    adresat.numerTelefonu = numerTelefonu;
    adresat.email = email;
    adresat.adres = adres;

    adresaci.push_back(adresat);

    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    plik << idAdresata << "|";
    plik << idUzytkownika << "|";
    plik << imie << "|";
    plik << nazwisko << "|";
    plik << numerTelefonu << "|";
    plik << email << "|";
    plik << adres << "|" << endl;
    plik.close();
    cout << "Nowy adresat zostal dodany do ksiazki adresowej" << endl;

    Sleep(2000);
}

void wyszukiwanieOsobyPoImieniu(vector <Adresat> &adresaci)
{
    int licznik = 0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
    system("cls");
    cout << "Wyszukiwanie adresata" << endl;
    cout << "Podaj imie szukanego adresata: ";
    cin >> imie;
    for (int i = 0; i < adresaci.size(); i++)
    {
        if(adresaci[i].imie == imie)
        {
            cout << adresaci[i].idAdresata << "|" << adresaci[i].idUzytkownika << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|" <<  endl;
            licznik = 0;
        }
        else
        {
            licznik ++;
        }
    }
    if (licznik == adresaci.size())
    {
        cout << "Nie ma zapisanego adresata o takim imieniu. Za chwile nastapi przekierowanie do menu glownego" << endl;
    }
    Sleep(2000);
}

void wyszukiwanieOsobyPoNazwisku(vector <Adresat> &adresaci)
{
    int licznik = 0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
    system("cls");
    cout << "Wyszukiwanie adresata" << endl;
    cout << "Podaj nazwisko szukanego adresata: ";
    cin >> nazwisko;
    for (int i = 0; i < adresaci.size(); i++)
    {
        if(adresaci[i].nazwisko == nazwisko)
        {
            cout << adresaci[i].idAdresata << "|"  << adresaci[i].idUzytkownika << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|" <<  endl;
            licznik=0;
        }
        else
        {
            licznik++;
        }
    }
    if (licznik == adresaci.size())
    {
        cout << "Nie ma zapisanego adresata o takim nazwisku. Za chwile nastapi przekierowanie do menu glownego" << endl;
    }
    Sleep(2000);
}

void wyswietlOsobyZPlikuAdresaci(vector <Adresat> &adresaci, int idUzytkownika)
{
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
    system("cls");

    cout << "Lista adresatow" << endl;
    fstream plik;

    plik.open("KsiazkaAdresowa.txt", ios::in);

    if(!ifstream("KsiazkaAdresowa.txt", ios::ate).tellg())
    {
        cout << "Nie ma jeszcze zadnych zapisanych adresatow" << endl;
    }

    if (plik.good() == false)
    {
        cout << "Plik nie istnieje!";
        exit(0);
    }
    else
    {
        for (int i = 0; i < adresaci.size(); i++)
        {
            if(adresaci[i].idUzytkownika == idUzytkownika)
            {
                cout << adresaci[i].idAdresata << "|" << adresaci[i].idUzytkownika << "|"<< adresaci[i].imie << "|" <<  adresaci[i].nazwisko << "|" <<  adresaci[i].numerTelefonu << "|" <<  adresaci[i].email << "|" <<  adresaci[i].adres << "|" <<  endl;
            }
        }
    }
    plik.close();
    system("pause");
}

void usuwanieAdresata(vector <Adresat> &adresaci)
{
    int idAdresata = 0;
    int idAdresataDoEdycji = 0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="", linia="";
    int licznik = 0;
    char wybor;
    fstream plikDoOdczytu, plikDoZapisu;
    cout << "Podaj id adresata, ktorego chcesz usunac: ";
    cin >> idAdresataDoEdycji;;

    for (int i = 0; i <= adresaci.size(); ++i)
    {
        if (adresaci[i].idAdresata == idAdresataDoEdycji)
        {
            cout << "Czy na pewno chcesz usunac adresata o id " << idAdresataDoEdycji << " ? Jesli tak, wybierz klawisz t. Jesli nie, wybierz klawisz n" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;
            if ((wybor == 't') || (wybor == 'T'))
            {
                adresaci.erase(adresaci.begin() + i);
                cout << "Adresat zostal usuniety. Za chwile nastapi przekierowanie do menu glownego" << endl;
                licznik = 0;

            }
            else if ((wybor == 'n') || (wybor == 'N'))
            {
                cout << "Adresat nie zostal usuniety. Za chwile nastapi przekierowanie do menu glownego" << endl;
                break;
            }
        }
        else
        {
            licznik ++;
        }
    }
    if (licznik == adresaci.size() + 1)
    {
        cout << "Nie ma zapisanego adresata o takim numerze id. Za chwile nastapi przekierowanie do menu glownego" << endl;
        Sleep(2000);
    }

    plikDoOdczytu.open("KsiazkaAdresowa.txt", ios::in);
    plikDoZapisu.open("KsiazkaAdresowaTymczasowa.txt", ios::out);
    if(!ifstream("KsiazkaAdresowa.txt", ios::ate).tellg())
    {
        cout << "Nie ma jeszcze zadnych zapisanych adresatow" << endl;
    }

    if (plikDoOdczytu.good() == false)
    {
        cout << "Plik nie istnieje!";
        exit(0);
    }
    else
    {
        while(getline(plikDoOdczytu, linia))
        {
            for(int pozycjaZnaku = 0; pozycjaZnaku < linia.length(); pozycjaZnaku++)
            {
                if(linia[pozycjaZnaku] == '|')
                {
                    idAdresata = atoi(linia.substr(0,pozycjaZnaku).c_str());
                    break;
                }
            }

            if (idAdresataDoEdycji == idAdresata)
            {
                goto wczytajKolejnaLinie;
            }
            else
            {
                plikDoZapisu << linia << endl;
            }
wczytajKolejnaLinie:
            ;
        }
    }
    plikDoOdczytu.close();
    plikDoZapisu.close();
}

void edycjaAdresata(vector <Adresat> &adresaci, int liczbaWszystkichAdresatow)
{
    Adresat adresat;
    int idAdresata = 0;
    int idAdresataDoEdycji = 0;
    int idUzytkownika = 0;
    int licznik = 0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
    char wybor;
    fstream plikDoOdczytu, plikDoZapisu;
    string edytowaneImie="", edytowaneNazwisko="", edytowanyNumerTelefonu="", edytowanyEmail="", EdytowanyAdres="", linia="";
    cout << "Podaj id adresata do edycji: ";
    cin >> idAdresata;
    idAdresataDoEdycji = idAdresata;
    for (int i = 0; i <= adresaci.size(); ++i)
    {
        if (adresaci[i].idAdresata == idAdresata)
        {
            system("cls");
            cout << "Wybierz kategorie do edycji:" << endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Numer Telefonu" << endl;
            cout << "4. Adres email" << endl;
            cout << "5. Adres zamieszkania" << endl;
            cout << "6. Powrot do menu" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;
            if (wybor == '1')
            {
                cout << "Podaj imie uzytkownika: ";
                cin >> edytowaneImie;
                adresaci[i].imie = edytowaneImie;
                cout << "Dane zostaly zmienione" << endl;
            }
            else if (wybor == '2')
            {
                cout << "Podaj nazwisko uzytkownika: ";
                cin >> edytowaneNazwisko;
                adresaci[i].nazwisko = edytowaneNazwisko;
                cout << "Dane zostaly zmienione" << endl;
            }
            else if (wybor == '3')
            {
                cout << "Podaj numer telefonu uzytkownika: ";
                cin.sync();
                getline(cin, edytowanyNumerTelefonu);
                adresaci[i].numerTelefonu = edytowanyNumerTelefonu;
                cout << "Dane zostaly zmienione" << endl;
            }
            else if (wybor == '4')
            {
                cout << "Podaj email uzytkownika: ";
                cin >> edytowanyEmail;
                adresaci[i].email = edytowanyEmail;
                cout << "Dane zostaly zmienione" << endl;
            }
            else if (wybor == '5')
            {
                cout << "Podaj adres uzytkownika: ";
                cin.sync();
                getline(cin, EdytowanyAdres);
                adresaci[i].adres = EdytowanyAdres;
                cout << "Dane zostaly zmienione" << endl;
            }
            else if (wybor == '6')
            {
                cout << "Za chwile nastapi przekierowanie do menu glownego";
                break;
            }
        }
        else
        {
            licznik ++;
        }
    }
    if (licznik == adresaci.size()+1)
    {
        cout << "Nie ma zapisanego adresata o takim numerze id. Za chwile nastapi przekierowanie do menu glownego" << endl;
        Sleep(2000);
    }

    plikDoOdczytu.open("KsiazkaAdresowa.txt", ios::in);
    plikDoZapisu.open("KsiazkaAdresowaTymczasowa.txt", ios::out);

    if(!ifstream("KsiazkaAdresowa.txt", ios::ate).tellg())
    {
        cout << "Nie ma jeszcze zadnych zapisanych adresatow" << endl;
    }

    if (plikDoOdczytu.good() == false)
    {
        cout << "Plik nie istnieje!";
        exit(0);
    }
    else
    {
        while(getline(plikDoOdczytu, linia))
        {
            for(int pozycjaZnaku = 0; pozycjaZnaku < linia.length(); pozycjaZnaku++)
            {
                if(linia[pozycjaZnaku] == '|')
                {
                    idAdresata = atoi(linia.substr(0,pozycjaZnaku).c_str());
                    break;
                }
            }
            for (int i = 0; i != adresaci.size(); i++)
            {
                if ((adresaci[i].idAdresata == idAdresata) && (idAdresataDoEdycji == idAdresata))
                {
                    plikDoZapisu << adresaci[i].idAdresata << "|"  << adresaci[i].idUzytkownika << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|" <<  endl;
                    goto wczytajKolejnaLinie;
                }
            }
            plikDoZapisu << linia << endl;

wczytajKolejnaLinie:
            ;
        }
    }

    plikDoOdczytu.close();
    plikDoZapisu.close();
}

int pobierzIdOstatniegoAdresata(vector <Adresat> &adresaci, int liczbaWszystkichAdresatow)
{
    fstream plikDoOdczytu;
    string linia="";
    int idOstatniegoAdresata = 0;

    plikDoOdczytu.open("KsiazkaAdresowa.txt", ios::in);

    if(!ifstream("KsiazkaAdresowa.txt", ios::ate).tellg())
    {
        cout << "Nie ma jeszcze zadnych zapisanych adresatow" << endl;
    }

    if (plikDoOdczytu.good() == false)
    {
        cout << "Plik nie istnieje!";
        exit(0);
    }
    else
    {
        while(getline(plikDoOdczytu, linia))
        {
            for(int pozycjaZnaku = 0; pozycjaZnaku < linia.length(); pozycjaZnaku++)
            {
                if(linia[pozycjaZnaku] == '|')
                {
                    idOstatniegoAdresata = atoi(linia.substr(0,pozycjaZnaku).c_str());
                    break;
                }
            }
        }
    }
    return idOstatniegoAdresata;
}

void zmianaHasla(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika, int iloscUzytkownikow)
{
    fstream plik;
    string nazwa="", haslo="", noweHaslo="";
    system("cls");

    cout << "Podaj nowe haslo: ";
    cin >> noweHaslo;

    for (int i = 0; i != uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = noweHaslo;
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(3000);
        }
    }

    plik.open("Uzytkownicy.txt");
    for (int i = 0; i < uzytkownicy.size(); i++)
    {
        plik << uzytkownicy[i].idUzytkownika << "|" << uzytkownicy[i].nazwa << "|" <<  uzytkownicy[i].haslo << "|" <<  endl;
    }
}

int main()
{
    vector <Adresat> adresaci;
    vector <Uzytkownik> uzytkownicy;
    wczytajUzytkownikow(uzytkownicy);
    int idUzytkownika = 0;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = 0;
    int liczbaWszystkichAdresatow = 0;
    int idOstatniegoAdresata = 0;
    char wybor;
    while(1)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >> wybor;

            if (wybor == '1')
            {
                idUzytkownika = rejestracja(uzytkownicy, iloscUzytkownikow);
            }
            else if (wybor == '2')
            {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
                liczbaWszystkichAdresatow = wczytajAdresatow(adresaci, idZalogowanegoUzytkownika);
            }
            else if (wybor == '9')
            {
                exit(0);
            }
        }
        else
        {
            system("cls");
            cout << ">>> MENU UZYTKOWNIKA <<<" << endl;
            cout << "---------------------------------------" << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "---------------------------------------" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "8. Wyloguj sie" << endl;
            cout << "---------------------------------------" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;
            if (wybor == '1')
            {
                idOstatniegoAdresata = pobierzIdOstatniegoAdresata(adresaci, liczbaWszystkichAdresatow);
                dodajNowaOsobe(adresaci, idZalogowanegoUzytkownika, liczbaWszystkichAdresatow, idOstatniegoAdresata);
            }
            else if (wybor == '2')
            {
                system("cls");
                cout << "Wyszukaj po imieniu" << endl;
                wyszukiwanieOsobyPoImieniu(adresaci);
            }
            else if(wybor =='3')
            {
                system("cls");
                cout << "Wyszukaj po nazwisku" << endl;
                wyszukiwanieOsobyPoNazwisku(adresaci);
            }
            else if (wybor == '4')
            {
                wyswietlOsobyZPlikuAdresaci(adresaci, idZalogowanegoUzytkownika);
            }
            else if (wybor == '5')
            {
                system("cls");
                usuwanieAdresata(adresaci);
                remove("KsiazkaAdresowa.txt");
                rename("KsiazkaAdresowaTymczasowa.txt", "KsiazkaAdresowa.txt");
            }
            else if (wybor == '6')
            {
                system("cls");
                edycjaAdresata(adresaci, liczbaWszystkichAdresatow);
                remove("KsiazkaAdresowa.txt");
                rename("KsiazkaAdresowaTymczasowa.txt", "KsiazkaAdresowa.txt");
            }
            else if (wybor == '7')
            {
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika, iloscUzytkownikow);
            }
            else if (wybor == '8')
            {
                idZalogowanegoUzytkownika = 0;
            }
        }

    }
    return 0;
}
