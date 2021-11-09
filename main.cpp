#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

struct Uzytkownik {
    int id;
    string nazwa, haslo;
};

struct Adresat {
    int id = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

void rejestracja(vector <Uzytkownik> uzytkownicy) {
    Uzytkownik uzytkownik;
    int id = 0;
    string nazwa, haslo;
        if (uzytkownicy.size() == 0) {
        id = 1;
    } else {
        id = uzytkownicy[uzytkownicy.size() - 1].id + 1;
    }
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;
    int i = 0;
    while(i < uzytkownicy.size()) {
        if (uzytkownicy[i].nazwa == nazwa) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;
    uzytkownik.nazwa = nazwa;
    uzytkownik.haslo = haslo;
    uzytkownik.id = id;
    uzytkownicy.push_back(uzytkownik);
    cout << "Konto zalozone" << endl;
    Sleep(1000);
}

int main() {
    vector <Adresat> adresaci;
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
