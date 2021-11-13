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
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwaUzytkownika;
    cout << uzytkownicy.size() << endl;
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
    uzytkownik.id = id;
    uzytkownicy.push_back(uzytkownik);
    cout << "Konto zalozone" << endl;

    Sleep(1000);
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
                ;//idZalogowanegoUzytkownika = logowanie(adresaci);
            } else if (wybor == '9') {
                exit(0);
            }
        }

    }
    return 0;
}
