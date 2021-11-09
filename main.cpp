#include <iostream>
#include <windows.h>

using namespace std;

struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};

void rejestracja(vector <Adresat> &adresaci)
{
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;
    int i = 0;
    while(i < usersCount)
    {
        if (users[i].nazwa == nazwa)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;
    users[usersCount].nazwa = nazwa;
    users[usersCount].haslo = haslo;
    users[usersCount].id = usersCount+1;
    cout << "Konto zalozone" << endl;
    Sleep(1000);
    return usersCount + 1;
}

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
