#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

//место за вашиот код

class NegativnaVrednost : public exception {
public:
    NegativnaVrednost() {
        cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!" << endl;
    }
};

class Oglas {
private:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    double cena;

public:
    Oglas(const char *naslov = "", const char *kategorija = "", const char *opis = "", double cena = 0) {
        strcpy(this->naslov, naslov);
        strcpy(this->kategorija, kategorija);
        strcpy(this->opis, opis);
        this->cena = cena;
    }

    bool operator>(Oglas &o) {
        if (cena > o.cena) {
            return true;
        }
        return false;
    }

    friend ostream &operator<<(ostream &os, Oglas &o) {
        os << o.naslov << endl;
        os << o.opis << endl;
        os << o.cena << " evra " << endl;
        return os;
    }

    double getCena() {
        return cena;
    }

    const char *getCat() {
        return kategorija;
    }
};

class Oglasnik {
private:
    char ime[20];
    Oglas *osi;
    int n;

public:
    Oglasnik(const char *ime = "", Oglas *osi = 0, int n = 0) {
        strcpy(this->ime, ime);
        this->n = n;
        this->osi = new Oglas[n];
        for (int i = 0; i < n; i++) {
            this->osi[i] = osi[i];
        }
    }

    Oglasnik(const Oglasnik &o) {
        strcpy(this->ime, o.ime);
        this->n = o.n;
        this->osi = new Oglas[o.n];
        for (int i = 0; i < o.n; i++) {
            this->osi[i] = o.osi[i];
        }
    }

    Oglasnik &operator=(const Oglasnik &o) {
        if (this == &o) return *this;
        strcpy(this->ime, o.ime);
        this->n = o.n;
        this->osi = new Oglas[o.n];
        delete[] osi;
        for (int i = 0; i < o.n; i++) {
            this->osi[i] = o.osi[i];
        }
        return *this;
    }

    ~Oglasnik() {
        delete[] osi;
    }

    Oglasnik &operator+=(Oglas &o) {
        if (o.getCena() < 0) {
            throw NegativnaVrednost();
        } else {
            Oglas *temp = new Oglas[n + 1];
            for (int i = 0; i < n; i++) {
                temp[i] = osi[i];
            }
            temp[n++] = o;
            delete[] osi;
            osi = temp;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, Oglasnik &ogs) {
        os << ogs.ime << endl;
        for (int i = 0; i < ogs.n; i++) {
            os << ogs.osi[i]<<endl;
        }
        return os;
    }

    void oglasiOdKategorija(const char *k) {
        for (int i = 0; i < n; i++) {
            if (strcmp(osi[i].getCat(), k) == 0) {
                cout<<osi[i]<<endl;
            }
        }
    }

    void najniskaCena() {
        Oglas low = osi[0];
        for (int i = 1; i<n; i++)
        {
            if (low.getCena() > osi[i].getCena())
            {
                low = osi[i];
            }
        }
        cout << low;
    }
};


int main() {

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin >> tip;

    if (tip == 1) {
        cout << "-----Test Oglas & operator <<-----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout << o;
    } else if (tip == 2) {
        cout << "-----Test Oglas & operator > -----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1 > o2) cout << "Prviot oglas e poskap." << endl;
        else cout << "Prviot oglas ne e poskap." << endl;
    } else if (tip == 3) {
        cout << "-----Test Oglasnik, operator +=, operator << -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << ogl;
    } else if (tip == 4) {
        cout << "-----Test oglasOdKategorija -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

    } else if (tip == 5) {
        cout << "-----Test Exception -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            } catch (NegativnaVrednost ex) {

            }
        }
        cout << ogl;

    } else if (tip == 6) {
        cout << "-----Test najniskaCena -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();

    } else if (tip == 7) {
        cout << "-----Test All -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try
            {
                ogl += o;
            } catch (NegativnaVrednost ex)
            {

            }
        }
        cout << ogl;

        cin.get();
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();

    }

    return 0;
}
