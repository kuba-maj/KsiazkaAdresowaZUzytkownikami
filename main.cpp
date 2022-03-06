#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <vector>

using namespace std;

struct Uzytkownik {
    int id = 0;
    string nazwa = "", haslo = "";
};

struct Adresat {
    int id = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

void rejestracja(vector <Uzytkownik> &uzytkownicy) {
    Uzytkownik uzytkownik;
    int id = 0;
    string nazwaUzytkownika, haslo, nazwa;
    int iloscAdresatow = 0;
    system("cls");
    if (uzytkownicy.empty() == true) {
        uzytkownik.id = 1;
    } else {
        uzytkownik.id = uzytkownicy.back().id + 1;
    }
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwaUzytkownika;
    while (iloscAdresatow < uzytkownicy.size())  {
        if (uzytkownicy[iloscAdresatow].nazwa == nazwaUzytkownika) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwaUzytkownika;
            iloscAdresatow = 0;

        } else {
            iloscAdresatow++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;
    uzytkownik.nazwa = nazwaUzytkownika;
    uzytkownik.haslo = haslo;
    uzytkownicy.push_back(uzytkownik);
    cout << "Konto zalozone" << endl;
    Sleep(1000);
}

int logowanie(vector <Uzytkownik> &uzytkownicy) {
    string nazwaUzytkownika, hasloUzytkownika;
    int iloscAdresatow = 0;
    system("cls");
    cout << "Podaj login: ";
    cin >> nazwaUzytkownika;
    while(iloscAdresatow < uzytkownicy.size()) {
        if (uzytkownicy[iloscAdresatow].nazwa == nazwaUzytkownika) {
            for (int proby = 0; proby < 3; proby++) {
                cout << "Podaj haslo. Pozostalo prob " << 3 - proby << " : ";
                cin >> hasloUzytkownika;
                if (uzytkownicy[iloscAdresatow].haslo == hasloUzytkownika) {
                    cout << "Zalogowales sie" << endl;
                    Sleep(1000);
                    return uzytkownicy[iloscAdresatow].id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(3000);
            return 0;
        }
        iloscAdresatow++;
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1500);
    return 0;
}

int main() {
    //vector <Adresat> adresaci;
    vector <Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = 0;
    char wybor;
    while(1) {
        if (idZalogowanegoUzytkownika == 0) {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >> wybor;

            if (wybor == '1') {
                rejestracja(uzytkownicy);
            } else if (wybor == '2') {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
            } else if (wybor == '9') {
                exit(0);
            }
        } else {
            system("cls");
            cout << "1. Zmiana hasla" << endl;
            cout << "2. Wylogowanie" << endl;
            cin >> wybor;
            if (wybor == '1') {
                ;//zmianaHasla(uzytkownicy, iloscUzytkownikow, idZalogowanegoUzytkownika);
            } else if (wybor == '2') {
                idZalogowanegoUzytkownika = 0;
            }
        }

    }
    return 0;
}
