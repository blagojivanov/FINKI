#include<iostream>
#include<string.h>

using namespace std;

//место за вашиот код

class Delo {
protected:
    char name[50];
    int year;
    char country[50];

public:
    Delo(const char *name = "", int year = 0, const char *country = "") {
        strcpy(this->name, name);
        this->year = year;
        strcpy(this->country, country);
    }

    bool operator==(Delo d) {
        if (strcmp(d.name, name) == 0) {
            return true;
        }
        return false;
    }

    const char *getIme() const {
        return name;
    }

    int getYear() const {
        return year;
    }

    const char *getCountry() const {
        return country;
    }

};

class Pretstava {
protected:
    Delo d;
    int k;
    char date[15];
public:
    Pretstava(Delo d = 0, int k = 0, const char *date = "") {
        this->d = d;
        this->k = k;
        strcpy(this->date, date);
    }

    virtual int cena() {
        int m, n;
        if (d.getYear() > 1900) {
            m = 50;
        } else if (d.getYear() > 1800) {
            m = 75;
        } else {
            m = 100;
        }

        if (strcmp(d.getCountry(), "Italija") == 0) n = 100;
        else if (strcmp(d.getCountry(), "Rusija") == 0) n = 150;
        else n = 80;

        return (n + m);
    }

    int sold() {
        return k;
    }

    Delo getDelo() {
        return d;
    }
};

class Balet : public Pretstava {
private:
    static int add;

public:
    Balet(Delo d = 0, int k = 0, const char *date = "") : Pretstava(d, k, date) {
    }

    int cena() override {
        int total = Pretstava::cena();
        total += Balet::add;
        return total;
    }

    static void setCenaBalet(int b) {
        Balet::add = b;
    }

};

class Opera : public Pretstava {
private:

public:
    Opera(Delo d = 0, int k = 0, const char *date = "") : Pretstava(d, k, date) {
    }
};

int prihod(Pretstava **niza, int n) {
    int retval = 0;
    for (int i = 0; i < n; i++) {
        retval += niza[i]->cena() * niza[i]->sold();
    }
    return retval;
}

int brojPretstaviNaDelo(Pretstava **niza, int n, Delo d) {
    int ct = 0;
    for (int i = 0; i < n; i++) {
        if (d == niza[i]->getDelo()) {
            ct++;
        }
    }
    return ct;

}

int Balet::add = 150;

//citanje na delo
Delo readDelo() {
    char ime[50];
    int godina;
    char zemja[50];
    cin >> ime >> godina >> zemja;
    return Delo(ime, godina, zemja);
}

//citanje na pretstava
Pretstava *readPretstava() {
    int tip; //0 za Balet , 1 za Opera
    cin >> tip;
    Delo d = readDelo();
    int brojProdadeni;
    char data[15];
    cin >> brojProdadeni >> data;
    if (tip == 0) return new Balet(d, brojProdadeni, data);
    else return new Opera(d, brojProdadeni, data);
}

int main() {
    int test_case;
    cin >> test_case;

    switch (test_case) {
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout << "======TEST CASE 1=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->getDelo().getIme() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->getDelo().getIme() << endl;
        }
            break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout << "======TEST CASE 2=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->cena() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->cena() << endl;
        }
            break;

        case 3:
            //Testiranje na operator ==
        {
            cout << "======TEST CASE 3=======" << endl;
            Delo f1 = readDelo();
            Delo f2 = readDelo();
            Delo f3 = readDelo();

            if (f1 == f2) cout << "Isti se" << endl; else cout << "Ne se isti" << endl;
            if (f1 == f3) cout << "Isti se" << endl; else cout << "Ne se isti" << endl;

        }
            break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout << "======TEST CASE 4=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();

            }
            cout << prihod(pole, n);
        }
            break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout << "======TEST CASE 5=======" << endl;
            int cenaBalet;
            cin >> cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }
            cout << prihod(pole, n);
        }
            break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout << "======TEST CASE 6=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }

            Delo f = readDelo();
            cout << brojPretstaviNaDelo(pole, n, f);
        }
            break;

    };


    return 0;
}
