//За потребите на една продавница за гитари, потребно е да се направи програма за менаџирање на магацинот.
//
//За таа цел, треба да се креира класа Gitara (5 поени). Класата треба да содржи:
//
//Сериски број (низа од 25 знаци)
//Набавна цена (реален број)
//Година на производство (цел број)
//Тип (низа од 40 знаци)
//Да се дефинира метод daliIsti кој како аргумент ќе добие објект од тип Gitara и ќе ги спореди двете гитари според нивниот сериски број (5 поени)
//
//Дополнително, за оваа класа да се направи функција pecati() за печатење на објектот во следниот формат (5 поени):
//
//[СерискиБрој] [Тип] [Цена]
//
//Да се креира класа Magacin (5 поени) која содржи:
//
//Име на магацинот (низа од 30 знаци)
//Локација на магацинот (низа од 60 знаци)
//Низа од гитари кои ги поседува магацинот (динамички алоцирана низа од објекти од класата Gitara)
//Број на објекти во низата (цел број)
//Година на отвoрање (цел број)
//За класата Magacin да се дефинира метод double vrednost() што ќе ја пресметува моменталната вредност на гитарите кои се наоѓаат во магацинот. Таа се пресметува како збир од вредноста на сите гитари од кои е составен магацинот (5 поени).
//
//Дополнително, за класата да се дефинираат функциите:
//
//-void dodadi(Gitara d) за сместување на нова гитара во магацин (додавање на нов објект од класата Gitara во динамички алоцираната низа со гитари) (10 поени)
//
//-void prodadi(Gitara p) за бришење на дадена гитара од магацинот (бришење на сите објекти кои се исти како аргументот проследен во фунцијата)(10 поени)
//
//-void pecati(bool daliNovi) за печатење на информации за магацинот така што во првиот ред ќе биде прикажано имете и локацијата на магацинот, а потоа во секој нареден ред ќе бидат прикажани гитарите кои се наоѓаат во магацинот. Доколку пратената променлива има вредност true ќе се печатат само гитарите кои имаат година на производство понова од годината на отварање на магацинот. Во спротивно се печатат сите гитари (5 поени).
//
//За класите да се дефинираат потребните конструктори, деструктор и сите останати методи за правилно функционирање на програмата (5 поени). Сите податочни членови во класите се приватни.
#include <iostream>
#include <cstring>

using namespace std;

class Gitara
{
private:
    char serialN[25];
    double price;
    int year;
    char type[40];
public:
    Gitara(char *type = "", char *serialN = "",int year = 0,double price = 0)
    {
        strcpy(this->serialN, serialN);
        this->price = price;
        this->year = year;
        strcpy(this->type, type);
    }

    Gitara(const Gitara &g)
    {
        strcpy(this->serialN, g.serialN);
        this->price = g.price;
        this->year = g.year;
        strcpy(this->type, g.type);
    }

    Gitara &operator=(const Gitara &g)
    {
        if (this == &g) return *this;
        strcpy(this->serialN, g.serialN);
        this->price = g.price;
        this->year = g.year;
        strcpy(this->type, g.type);
        return *this;
    }

    char *getSeriski() {
        return serialN;
    }

    double getNabavna(){
        return price;
    }

    int getGodina() {
        return year;
    }

    char *getTip() {
        return type;
    }

    bool daliIsti(Gitara g)
    {
        if (strcmp(serialN, g.serialN) == 0)
        {
            return true;
        }
        return false;
    }

    void pecati()
    {
        cout<<serialN<<" "<<type<<" "<<price<<endl;
    }

};

class Magacin
{
private:
    char name[30];
    char location[60];
    Gitara *gitari;
    int n;
    int year;
public:
    Magacin(char *name = "", char *location = "", int year = 0)
    {
        strcpy(this->name, name);
        strcpy(this->location, location);
        this->n = 0;
        gitari = NULL;
        this->year = year;
    }

    Magacin(const Magacin &m)
    {
        strcpy(this->name, m.name);
        strcpy(this->location, m.location);
        this->n = m.n;
        this->year = m.year;
        gitari = new Gitara[m.n];
        for(int i = 0; i<n;i++)
        {
            gitari[i] = m.gitari[i];
        }
    }

    Magacin &operator=(const Magacin &m)
    {
        if (this == &m) return *this;
        strcpy(this->name, m.name);
        strcpy(this->location, m.location);
        this->n = m.n;
        this->year = m.year;
        delete [] gitari;
        gitari = new Gitara[m.n];
        for(int i = 0; i<n;i++)
        {
            gitari[i] = m.gitari[i];
        }
        return *this;
    }

    ~Magacin()
    {
        delete [] gitari;
    }

    double vrednost()
    {
        double v = 0;
        for(int i = 0; i<n; i++)
        {
            v+=gitari[i].getNabavna();
        }
        return v;
    }

    void dodadi(Gitara &d)
    {
        Gitara *temp = new Gitara[n+1];

        for (int i = 0;i<n; i++)
        {
            temp[i] = gitari[i];
        }
        temp[n++]=d;
        delete [] gitari;
        gitari = temp;
    }

    void prodadi(Gitara &p)
    {
        int isti = 0, nc = 0;
        for (int i = 0;i<n; i++)
        {
            if (p.daliIsti(gitari[i]))
            {
                isti++;
            }
        }

        Gitara *temp = new Gitara[n-isti];
        for (int i = 0;i<n; i++)
        {
            if (!p.daliIsti(gitari[i]))
            {
                temp[nc++] = gitari[i];
            }
        }

        delete [] gitari;
        gitari = temp;
        n=nc;
    }

    void pecati(bool daliNovi)
    {
        cout<<name<<" "<<location<<endl;
        for(int i = 0; i<n;i++)
        {
            if (daliNovi)
            {
                if(gitari[i].getGodina() > year)
                {
                    gitari[i].pecati();
                }
            }else
            {
                gitari[i].pecati();
            }
        }
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50],tip[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
        cout<<g.getTip()<<endl;
        cout<<g.getSeriski()<<endl;
        cout<<g.getGodina()<<endl;
        cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
        cin>>n;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
    else if(testCase ==6)
    {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            kb.dodadi(g);
        }
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
    }
    return 0;
}
