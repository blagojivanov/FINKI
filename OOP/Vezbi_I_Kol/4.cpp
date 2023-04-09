//(40 поени)
//
//Да се креира класа Patnik во која се чуваат податоци за патниците на еден воз и тоа: име (низа од максимум 100 знаци), класа на вагон во која се вози (цел број 1 или 2) и велосипед (булова променлива).
//
//За оваа класа да се преоптоварат:
//
//Оператор << - за печатење на информациите за патникот во формат:
//Име на патник
//
//        Бројот на класата (1 или 2)
//
//Дали има велосипед?
//
//Потоа да се креира клaса Voz во која се чува: крајна дестинација (низа од максимум 100 знаци), динамички алоцирана низа од објекти од класата Patnik, како и број на елементи во низата (цел број), број на дозволени велосипеди (цел број).
//
//За класата да се обезбедат:
//
//Оператор += – за додавање нов патник во воз. Патник со велосипед ќе може да се качи во воз само ако возот го дозволува тоа.
//Оператор << - за печатење на крајната дестинација до која вози и листата на патници
//Функција со потпис: patniciNemaMesto(). Со оваа функција се пресметува вкупниот број на патници (од 1-ва класа и 2-ра класа) за кои нема место да влезат во возот со велосипед. Притоа треба да се внимава дека во пресметувањето на вкупниот број патници со велосипеди кои ќе влезат во возот прво треба да се земат предвид патниците од 1-ва класа, а потоа се дозволува да влегуваат патниците од 2-ра класа се додека не се достигне максималниот број на дозволени велосипеди во возот. На крај се печати бројот на патници со велосипеди кои остануваат (не влегуваат во возот) од 1-ва класа, а потоа од 2-ра класа.

#include<iostream>
#include<cstring>
using namespace std;

class Patnik{

private:
    char name[30];
    int wagon;
    bool bike;
public:

    Patnik(char *name = "", int wagon = 1, bool bike = 0)
    {
        strcpy(this->name, name);
        this->wagon = wagon;
        this->bike = bike;
    }

    Patnik(const Patnik &p)
    {
        strcpy(this->name, p.name);
        this->wagon = p.wagon;
        this->bike = p.bike;
    }

    Patnik &operator=(const Patnik &p)
    {
        if (this == &p) return *this;
        strcpy(this->name, p.name);
        this->wagon = p.wagon;
        this->bike = p.bike;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Patnik &p)
    {
        out <<p.name<<endl;
        out <<p.wagon<<endl;
        out <<p.bike<<endl;
    }

    bool isBike() const{
        return bike;
    }

    int getWagon() const {
        return wagon;
    }
};

class Voz{

private:
    char dest[30];
    Patnik *patnici;
    int n;
    int brVel;

public:

    Voz(char *dest = "", int brVel = 0)
    {
        strcpy(this->dest, dest);
        this->brVel = brVel;
        this->n = 0;
        this->patnici = nullptr;
    }

    Voz(const Voz &v)
    {
        strcpy(this->dest, v.dest);
        this->brVel = v.brVel;
        this->n = v.n;
        this->patnici = new Patnik[v.n];
        for (int i = 0; i<v.n; i++)
        {
            patnici[i] = v.patnici[i];
        }
    }

    Voz &operator=(const Voz &v)
    {
        if (this ==&v) return *this;
        strcpy(this->dest, v.dest);
        this->brVel = v.brVel;
        this->n = v.n;
        delete [] patnici;
        this->patnici = new Patnik[v.n];
        for (int i = 0; i<v.n; i++)
        {
            patnici[i] = v.patnici[i];
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Voz &v)
    {
        out<<v.dest<<endl;
        for (int i = 0; i<v.n; i++)
        {
            out<<v.patnici[i]<<endl;
        }
    }

    Voz &operator+=(const Patnik &p)
    {
        Patnik *temp = new Patnik[n+1];
        if (p.isBike() && brVel > 0)
        {
            for (int i = 0; i<n; i++)
            {
                temp[i] = patnici[i];
            }
            temp[n++] = p;
            delete [] patnici;
            patnici = temp;
        } else if (!p.isBike())
        {
            for (int i = 0; i<n; i++)
            {
                temp[i] = patnici[i];
            }
            temp[n++] = p;
            delete [] patnici;
            patnici = temp;
        }
        return *this;
    }

    ~Voz()
    {
        delete [] patnici;
    }

    void patniciNemaMesto()
    {
        int pat[2] = {0,0};
        for (int i = 0; i<n; i++)
        {
            if (patnici[i].getWagon() == 1 && patnici[i].isBike())
            {
                pat[0]++;
            } else if (patnici[i].getWagon() == 2 && patnici[i].isBike())
            {
                pat[1]++;
            }
            if (patnici[i].isBike() && patnici[i].getWagon()==1 && brVel>0)
            {
                brVel--;
                pat[0]--;
            }
        }
        for (int i = 0; i<n && brVel>0; i++)
        {
            if (patnici[i].isBike() && patnici[i].getWagon() == 2)
            {
                brVel--;
                pat[1]--;
            }
        }
        cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: "<<pat[0]<<endl;
        cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<pat[1];
    }

};


int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
