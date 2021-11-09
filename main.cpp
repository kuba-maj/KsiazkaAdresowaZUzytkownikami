#include <iostream>
#include <windows.h>

using namespace std;

struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};

int main()
{
    vector <Adresat> adresaci;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = 0;
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
                rejestracja(adresaci);
            }
            else if (wybor == '2')
            {
                idZalogowanegoUzytkownika = logowanie(adresaci);
            }
            else if (wybor == '9')
            {
                exit(0);
            }
        }

    }
    return 0;
}
