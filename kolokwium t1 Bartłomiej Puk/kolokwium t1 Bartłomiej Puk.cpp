
//BLOK 2
#include <iostream>
#include <stdexcept>
#include <cassert>
using namespace std;


using Tekst = char[1000];

enum class Dostepnosc {
    Dostepny,
    Niedostepny,
    Dostawa_wkrotce
};

struct Producent {
    Tekst nazwa;
};

struct Towar {
    char nazwa[1000];
    double cena;
    Dostepnosc dostepnosc;
    Producent* producent;
};

void wypelnij(Towar& towar, Producent* producent, Dostepnosc dostepnosc, double cena) {
    towar.producent = producent;
    towar.dostepnosc = dostepnosc;
    towar.cena = cena;
};

void wypisz(const Towar& towar) {
    cout << "Nazwa: " << towar.nazwa << "\nCena: " << towar.cena << "\nDostepnosc: ";
    switch (towar.dostepnosc) {
    case Dostepnosc::Dostepny:
        cout << "Dostepny";
        break;
    case Dostepnosc::Niedostepny:
        cout << "Niedostepny";
        break;
    case Dostepnosc::Dostawa_wkrotce:
        cout << "Dostawa wkrotce";
        break;
    default:
        break;
    };
    cout << "\nProducent: " << towar.producent->nazwa << endl;
}

// Funkcja ma wczytać tablicę towarów i producenta
// a następnie zwrocić średnią cenę dostępnych u niego towarów.

double sredniaCena(Towar dane[], int n, const char* producent)
{
    if (dane == nullptr)
    {
        throw invalid_argument("Liczba adresow tablicy jest nullptr");
    }

    int suma = 0;
    int iloscDostepnych = 0;

    for (int i = 0; i < n; ++i)
    {
        if (dane[i].producent != nullptr && dane[i].producent->nazwa == producent)
        {
            switch (dane[i].dostepnosc)
            {
            case Dostepnosc::Dostepny:
            case Dostepnosc::Dostawa_wkrotce:
                suma += dane[i].cena;
                iloscDostepnych++;
                break;
            default:
                break;
            }
        }
    }

    if (iloscDostepnych == 0)
    {
        throw runtime_error("Brak dostepnych towarow od danego producenta");
    }

    return static_cast<double>(suma) / iloscDostepnych;
}



void test_Sredniej_Ceny() {

    Towar towary1[] = {
        {"Sledze", 10.99, Dostepnosc::Dostepny, new Producent{"Sprytny Rybak"}},
        {"Haczyki", 4.99, Dostepnosc::Dostepny, new Producent{"Sprytny Rybak"}},
        {"Eko-Groszek", 800.0, Dostepnosc::Dostepny, new Producent{"KWK Świderek"}}
    };

    try {
        double srednia1 = sredniaCena(towary1, sizeof(towary1) / sizeof(towary1[0]), "Sprytny Rybak");
        assert(srednia1 == (10.99 + 4.99) / 2.0);
        cout << "Test 1 - Srednia cena dostepnych towarow: " << srednia1 << " - PASSED\n";
    }
    catch (const exception& e) {
        cerr << "Blad testu 1: " << e.what() << endl;
    }


    Towar towary2[] = {
        {"Węgiel", 1000.0, Dostepnosc::Niedostepny, new Producent{"KWK Świderek"}},
        {"Masaz", 501.29, Dostepnosc::Niedostepny, new Producent{"Agencja T. Chryzantema"}},
        {"Komputer", 3000.0, Dostepnosc::Niedostepny, new Producent{"Agencja T. Chryzantema"}}
    };

    try {
        double srednia2 = sredniaCena(towary2, sizeof(towary2) / sizeof(towary2[0]), "Sprytny Rybak");
        cout << "Test 2 - Srednia cena dostepnych towarow: " << srednia2 << endl;
    }
    catch (const exception& e) {
        assert(string(e.what()) == "Brak dostepnych towarow od danego producenta");
        cout << "Test 2 - Wyjatek: " << e.what() << " - PASSED\n";
    }

    //zwalnianie miejsca w pamięci
    for (auto& towar : towary1) {
        delete towar.producent;
    }
}

int main() {
   


    Producent producenci[] = {
        {"Sprytny Rybak"},
        {"KWK Świderek"},
        {"Agencja T. Chryzantema"}
    };

    Towar towary[] = {
        {"Sledze", 10.99, Dostepnosc::Dostepny, &producenci[0]},
        {"Węgiel", 1000.0, Dostepnosc::Niedostepny, &producenci[1]},
        {"Masaz", 501.29, Dostepnosc::Niedostepny, &producenci[2]},
        {"Haczyki", 4.99, Dostepnosc::Dostepny,&producenci[0]},
        {"Eko-Groszek", 800.0, Dostepnosc::Dostepny,&producenci[1]},
        {"Czerwone Roze", 14.99, Dostepnosc::Niedostepny,&producenci[2]},
    };


    for (const auto& towar : towary)
    {
        wypisz(towar);
        cout << endl;
        cout << "-------------------------\n";
    }


    try
    {
        double srednia = sredniaCena(towary, sizeof(towary) / sizeof(towary[0]), "Sprytny Rybak");
        assert(srednia == (10.99 + 4.99) / 2.0);
        cout << "Srednia cena dostepnych towarow: " << srednia << " - PASSED\n";
    }
    catch (const exception& e)
    {
        cerr << "Wyjatek: " << e.what() << endl;
    }


    test_Sredniej_Ceny();

    return 0;
}


