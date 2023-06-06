#include<iostream>
#include<string.h>

using namespace std;

class OutOfBoundException : public exception {
public:
    OutOfBoundException() {
//        cout << "Brojot na pin kodovi ne moze da go nadmine dozvolenoto";
    }
};

class Karticka {
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
public:
    Karticka(const char *smetka = "", int pin = 0) {
        strcpy(this->smetka, smetka);
        this->pin = pin;
        this->povekjePin = false;
    }

    virtual int tezinaProbivanje() {
        int ct = 0;
        int temp = pin;
        while (temp > 0) {
            ct++;
            temp /= 10;
        }
        return ct;
    }

    bool getDopolnitelenPin() {
        return povekjePin;
    }

    const char *getSmetka() const {
        return smetka;
    }

    friend ostream &operator<<(ostream &os, Karticka karticka) {
        os << karticka.smetka << ": " << karticka.tezinaProbivanje() << endl;
        return os;
    }

    // дополниете ја класата
};

//вметнете го кодот за SpecijalnaKarticka

class SpecijalnaKarticka : public Karticka {
private:
    int *pins;
    int nump;
    const static int P;
public:
    SpecijalnaKarticka(const char *smetka = " ", int pin = 0, int *pins = 0, int nump = 0)
            : Karticka(smetka, pin) {
        this->povekjePin = true;
        this->pins = new int[nump];
        this->nump = nump;
        for (int i = 0; i < nump; i++) {
            this->pins[i] = pins[i];

        }
    }

    SpecijalnaKarticka(const SpecijalnaKarticka &sk) : Karticka(sk) {
        nump = sk.nump;
        this->povekjePin = true;
        pins = new int[nump];
        for (int i = 0; i < nump; i++) {
            pins[i] = pins[i];
        }
    }

    SpecijalnaKarticka &operator=(const SpecijalnaKarticka &sk) {
        if (this == &sk) return *this;
        nump = sk.nump;
        this->povekjePin = true;
        delete[] pins;
        pins = new int[nump];
        for (int i = 0; i < nump; i++) {
            pins[i] = pins[i];
        }
        return *this;
    }

    ~SpecijalnaKarticka() {
        delete[] pins;
    }

    int tezinaProbivanje() {
        int tezh = Karticka::tezinaProbivanje();
        tezh += nump;
        return tezh;
    }

    SpecijalnaKarticka &operator+=(int pin) {
        if (nump + 1 > P) {
            throw OutOfBoundException();
        } else {
            int *temp = new int[nump+1];
            for (int i = 0; i < nump; i++) {
                temp[i] = pins[i];
            }
            temp[nump++] = pin;
            delete[] pins;
            pins = temp;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, SpecijalnaKarticka &karticka) {
        os << karticka.smetka << ": " << karticka.tezinaProbivanje() << endl;
        return os;
    }

    int getN() {
        return nump;
    }
};

const int SpecijalnaKarticka::P = 4;

class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka **karticki, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++) {
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()) {
                this->karticki[i] = new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka *>(karticki[i]));
            } else this->karticki[i] = new Karticka(*karticki[i]);
        }
        this->broj = broj;
    }

    static void setLIMIT(int l) {
        Banka::LIMIT = l;
    }


    void pecatiKarticki() {
        cout << "Vo bankata " << naziv << " moze da se probijat kartickite: " << endl;
        for (int i = 0; i < broj; i++) {
            if (karticki[i]->getDopolnitelenPin() == true) {
                SpecijalnaKarticka *sk = dynamic_cast<SpecijalnaKarticka *>(karticki[i]);
                if (sk->tezinaProbivanje() <= LIMIT) {
                    cout << *sk;
                }
            } else {
                if (karticki[i]->tezinaProbivanje() <= LIMIT) {
                    cout << *karticki[i];
                }
            }
        }
    }

    void dodadiDopolnitelenPin(char *smetka, int p) {
        for (int i = 0; i < broj; i++) {
            if (strcmp(karticki[i]->getSmetka(), smetka) == 0) {
                SpecijalnaKarticka *sk = dynamic_cast<SpecijalnaKarticka *>(karticki[i]);
                if (sk != 0) {
                    try {
                        *sk += p;
                    } catch (OutOfBoundException) {

                    }
                }
            }

        }
    }

    ~Banka() {
        for (int i = 0; i < broj; i++) delete karticki[i];
    }

    //да се дополни класата

};

int Banka::LIMIT = 7;

int main() {

    Karticka **niza;
    int n, m, pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin >> n;
    niza = new Karticka *[n];
    for (int i = 0; i < n; i++) {
        cin >> smetka;
        cin >> pin;
        cin >> daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i] = new Karticka(smetka, pin);
        else
            niza[i] = new SpecijalnaKarticka(smetka, pin);
    }

    Banka komercijalna("Komercijalna", niza, n);
    for (int i = 0; i < n; i++) delete niza[i];
    delete[] niza;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> smetka >> pin;

        komercijalna.dodadiDopolnitelenPin(smetka, pin);

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
