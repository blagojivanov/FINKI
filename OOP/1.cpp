//Да се дефинира класата Pesna во која се чуваат информации за (5 поени):
//
//име на песна (динамички алоцирано поле од знаци)
//времетраење на песната во минути
//тип на песна кој може да биде: поп, рап или рок (енумерација tip)
//Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (10 поени)
//Дополнително за оваа класа да се дефинира методот:
//
//pecati() - функција во која ќе се печатат одделени со цртичка(-): името на песната во наводници и времетраењето на песната со постфикс min. (5 поени)
//Да се креира класата CD во која се чуваат информации за (5 поени):
//
//низа од песни снимени на CD-то (Поле од најмногу 10 објекти од класата Pesna )
//број на песни снимени на CD-то
//максимално времетраење на песните на CD-то (во минути)
//Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (5 поени)
//
//Дополнително за оваа класа да се дефинираат методите:
//
//dodadiPesna (Pesna p) - со кој се додава песната p на CDто, но само ако има доволно преостанато место (земајќи го предвид максималното времетраење на песните на CDто и времетраењата на песните на CD-то) и ако има помалку од 10 песни на CD-то. (10 поени)
//pecatiPesniPoTip(tip t) – со кој се печатат информациите за сите песни од тип t (поп, рап или рок). (10 поени)
//Комплетна функционалност (5 поени).
#include <iostream>
#include <cstring>
using namespace std;

enum tip {
    POP, RAP, ROCK
};

class Pesna
{
private:
    char *name;
    int min;
    tip t;

public:

    Pesna(char *name ="", int min = 0, tip t = POP)
    {
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
        this->min = min;
        this->t = t;
    }
    Pesna(const Pesna &p)
    {
        this->name = new char[strlen(p.name)+1];
        strcpy(this->name, p.name);
        this->min = p.min;
        this->t = p.t;
    }
    Pesna &operator=(const Pesna &p)
    {
        if (this == &p) return *this;

        delete [] name;
        this->name = new char[strlen(p.name)+1];
        strcpy(this->name, p.name);
        this->min = p.min;
        this->t = p.t;
        return *this;
    }

    void pecati()
    {
        cout<<"\""<<name<<"\"-"<<min<<"min\n";
    }

    ~Pesna()
    {
        delete [] name;
    }

    int getMin()
    {
        return min;
    }

    int getType()
    {
        return (tip) t;
    }

};

class CD {
private:
    Pesna *pesni;
    int n;
    int maxMin;

public:
    CD(int maxMin = 0)
    {
        this->maxMin = maxMin;
        this->n = 0;
    }

    CD(const CD &c)
    {
        this->maxMin = c.maxMin;
        this->n = c.n;
        this->pesni = new Pesna[c.n];
        for (int i = 0; i<n; i++)
        {
            this->pesni[i] = c.pesni[i];
        }
    }

    CD &operator=(const CD &c)
    {
        if (this == &c) return *this;

        this->maxMin = c.maxMin;
        delete [] pesni;
        this->n = c.n;
        this->pesni = new Pesna[c.n];
        for (int i = 0; i<n; i++)
        {
            this->pesni[i] = c.pesni[i];
        }
    }

    ~CD()
    {
        delete [] pesni;
    }

    void dodadiPesna(Pesna p)
    {
        int sum = 0;
        for(int i = 0; i<n; i++)
        {
            sum+=pesni[i].getMin();
        }
        if (sum + p.getMin() <= maxMin && n<10)
        {
            Pesna *temp = new Pesna[n+1];
            for (int i = 0; i<n; i++)
            {
                temp[i] = pesni[i];
            }
            temp[n++] = p;
            //delete [] pesni;
            pesni = temp;
        }
        //return *this; samo ako e CD&
    }

    void pecatiPesniPoTip(tip t)
    {
        for (int i = 0; i<n; i++)
        {
            if (pesni[i].getType() == t)
            {
                pesni[i].pecati();
            }
        }
    }
    int getBroj()
    {
        return n;
    }
    Pesna getPesna(int i)
    {
        return pesni[i];
    }
};


int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

    return 0;
}
