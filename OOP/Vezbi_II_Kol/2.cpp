#include <iostream>
#include <cstring>

using namespace std;

class Vozac {
protected:
    char name[30];
    int age;
    int n;
    bool vet;
public:

    Vozac(const char *name = "", int age = 0, int n = 0, bool vet = false) {
        strcpy(this->name, name);
        this->age = age;
        this->n = n;
        this->vet = vet;
    }

    Vozac(const Vozac &v) {
        strcpy(this->name, v.name);
        this->age = v.age;
        this->n = v.n;
        this->vet = v.vet;
    }

    Vozac &operator=(const Vozac &v) {
        if (this == &v) return *this;
        strcpy(this->name, v.name);
        this->age = v.age;
        this->n = v.n;
        this->vet = v.vet;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Vozac &vozac) {
        os << vozac.name << endl << vozac.age << endl << vozac.n << endl;
        if (vozac.vet) {
            os << "VETERAN" << endl;
        }
        return os;
    }

    virtual float danok()=0;
    virtual float zarabotuvacka() const =0;
    bool operator==(Vozac &v)
    {
        return (v.zarabotuvacka() == this->zarabotuvacka());
    };

};

class Avtomobilist : public Vozac
{
private:
    double cena;

public:
    Avtomobilist(const char *name = "", int age = 0, int n = 0, bool vet = false, double cena = 0)
    : Vozac(name, age, n, vet)
    {
        this->cena = cena;
    }
    Avtomobilist(const Avtomobilist &av)
            : Vozac(av)
    {
        this->cena = av.cena;
    }
    Avtomobilist &operator=(const Avtomobilist &av)
    {
        if (this == &av) return *this;
        strcpy(this->name, av.name);
        this->age = av.age;
        this->n = av.n;
        this->vet = av.vet;
        this->cena = av.cena;
        return *this;
    }

    float zarabotuvacka() const
    {
        return cena/5;
    }
    float danok()
    {
        if (n > 10)
            return (zarabotuvacka())*0.15;
        return (zarabotuvacka())*0.1;
    }
//    bool operator==(Vozac *v)
//    {
//        if (v->zarabotuvacka() == this->zarabotuvacka())
//            return true;
//        return false;
//    }
};

class Motociklist : public Vozac
{
private:
    int mokjnost;

public:
    Motociklist(const char *name = "", int age = 0, int n = 0, bool vet = false, int mokjnost = 0)
            : Vozac(name, age, n, vet)
    {
        this->mokjnost = mokjnost;
    }
    Motociklist(const Motociklist &mt)
            : Vozac(mt)
    {
        this->mokjnost = mt.mokjnost;
    }
    Motociklist &operator=(const Motociklist &mt)
    {
        if (this == &mt) return *this;
        strcpy(this->name, mt.name);
        this->age = mt.age;
        this->n = mt.n;
        this->vet = mt.vet;
        this->mokjnost = mt.mokjnost;
        return *this;
    }

    float zarabotuvacka() const
    {
        return mokjnost*20;
    }
    float danok()
    {
        if (vet)
            return (zarabotuvacka())*0.25;
        return (zarabotuvacka())*0.2;
    }
//    bool operator==(Vozac *v)
//    {
//        if (v->zarabotuvacka() == this->zarabotuvacka())
//            return true;
//        return false;
//    }

};

int soIstaZarabotuvachka(Vozac **vozaci, int n, Vozac *x)
{
    int c = 0;
    for (int i = 0; i<n; i++)
    {
        if (vozaci[i]->zarabotuvacka() == x->zarabotuvacka())
        {
            ++c;
        }
    }
//    {
////        Vozac *temp = dynamic_cast<Motociklist *>(vozaci[i]);
////        Vozac *temp2 = dynamic_cast<Avtomobilist *>(vozaci[i]);
//        if (temp != 0)
//        {
//            if (temp == x)
//            {
//              ++c;
//            }
//        } else
//        {
//            if (temp2 == x)
//            {
//                ++c;
//            }
//        }
//    }
    return c;
}

// vashiot kod ovde

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac *[n];
    char ime[30];
    int vozrast;
    int trki;
    bool vet;
    for (int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if (i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for (int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete[] v;
    delete vx;
    return 0;
}
