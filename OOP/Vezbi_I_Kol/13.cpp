//Да се креира класата Zichara во која ќе се чуваат информации за:
//
//место (динамичко алоцирано поле од знаци)
//цена на дневна карта (цел број)
//Да се креира класа PlaninarskiDom во која се чуваат информации за:
//
//име (статичко поле од најмногу 15 знаци)
//цени по сезони (поле од 2 цели броеви кои ја претставуваат цената за спиење за еден ден во планинарскиот дом во двете различни сезони. Секој планинарски дом има две сезони: летна и зимска. Летната сезона почнува на 1ви април и завршува до 1ви сепмтември. На пример цената за престој на 24ти Јули ќе биде сместена во полето со индекс 0 - каде е сместена цената за летната сезона)
//класа на планинарскиот дом (еден знак кој може да има вредност од A до F, каде A е најдобра класа)
//дали има жичара (bool-тип)
//жичарата на планинарскиот дом (покажувач кон објект од класата Zichara)
//За дадените класи дефинирајте ги потребните: конструктори, деструктори, set и get методи. Оптоварете го соодветно операторот =. (20 поени)
//
//Да се оптоварат:
//
//операторот -- (префискен) за намалување на класата на планинарскиот дом (во класата PlaninarskiDom). Да се запази дека за планинарскиот дом најмала класа е F. (5 поени)
//операторот << за печатење на објект одPlaninarskiDom. (5 поени)
//операторот <= за одредување дали планинарскиот дом има класа помала или еднаква со дадениот знак (споредба на планинарски дом со знак). (5 поени)
//Формат на печатење на информации за еден планинарски дом:
//
//Pelister klasa:A so zichara //ако има жичара
//Korab klasa:B //ако нема жичара
//Во класата PlaninarskiDom да се имплементира функција со име presmetajDnevenPrestoj со која се пресметува цената за дневен престој во планинарскиот дом за даден ден и месец во годината. Ако планинарскиот дом има жичара во цената за дневен престој влегува и дневната карта за жичарата. Функцијата враќа void (не враќа ништо). Првиот аргумент на функцијата е денот (1-31), а вториот е месецот (1-12) за кои се пресметува цената. Третиот аргумент е цената за дневен престој која ќе се пресмета во функцијата. Доколку денот или месецот се невалидни да се фрли соодветен исклучок со кој се справуваме во main-функцијата. Да се земе дека секој месец има 31 ден. (15 поени)
//
//Дадена е main-функција во која се користат класите Zichara и PlaninarskiDom. Без таа да се менува креирајте ги опишаните класи.

#include <iostream>
#include <cstring>
using namespace std;

class Zichara
{
private:
    char *mesto;
    int price;

public:

    Zichara(char *mesto = "", int price = 0)
    {
        this->mesto = new char[strlen(mesto)+1];
        strcpy(this->mesto, mesto);
        this->price = price;
    }

    Zichara(const Zichara &z)
    {
        this->mesto = new char[strlen(z.mesto)+1];
        strcpy(this->mesto, z.mesto);
        this->price = z.price;
    }

    int getPrice() const {
        return price;
    }

    Zichara &operator=(const Zichara &z)
    {
        if (this == &z) return *this;
        delete [] mesto;
        this->mesto = new char[strlen(z.mesto)+1];
        strcpy(this->mesto, z.mesto);
        this->price = z.price;
        return *this;
    }

    ~Zichara()
    {
        delete [] mesto;
    }

};

class PlaninarskiDom {
private:
    char name[15];
    int prices[2];
    char klasa;
    bool tf;
    Zichara *zichara;
public:

    PlaninarskiDom(char *name = "", int *prices = nullptr, char klasa ='A', bool tf = false, Zichara *zichara = nullptr)
    {
        strcpy(this->name, name);
        if (prices != nullptr)
        {
            this->prices[0] = prices[0];
            this->prices[1] = prices[1];
        }
        this->klasa = klasa;
        this->tf = tf;
        this->zichara = zichara;
    }

    PlaninarskiDom(const PlaninarskiDom &p)
    {
        strcpy(this->name, p.name);
        this->prices[0] = p.prices[0];
        this->prices[1] = p.prices[1];
        this->klasa = p.klasa;
        this->tf = p.tf;
        this->zichara = p.zichara;
    }
    PlaninarskiDom &operator=(const PlaninarskiDom &p)
    {
        if (this == &p) return *this;
        strcpy(this->name, p.name);
        this->prices[0] = p.prices[0];
        this->prices[1] = p.prices[1];
        this->klasa = p.klasa;
        this->tf = p.tf;
        this->zichara = p.zichara;
        return *this;
    }


    PlaninarskiDom& operator--()
    {
        if (klasa =='F')
            return *this;
        klasa++;
        return *this;
    }

    bool operator<=(char k) const
    {
        if (klasa >= k)
        {
            return true;
        }
        return false;
    }
    friend ostream &operator<<(ostream &out, const PlaninarskiDom &p)
    {
        out<<p.name<<" klasa:"<<p.klasa;
        if (p.tf)
        {
            out<<" so Zichara";
        }
        out<<endl;
    }

    void setZichara(Zichara zichara) {
        this->zichara = &zichara;
        this->tf = true;
    }

    void presmetajDnevenPrestoj(int den, int mesec, int &cena)
    {
        cena = 0;
        if (den>=0 && den <=31) {
            if (mesec >= 4 && mesec <= 9) {
                cena += prices[0];
            } else if ((mesec > 0 && mesec < 4) || (mesec > 9 && mesec <= 12)) {
                cena += prices[1];
            } else {
                throw int();
            }
        } else
        {
            throw int();
        }
        if (tf)
        {
            cena+=zichara->getPrice();
        }
    }
};
int main(){

    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15],mestoZichara[30],klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin>>imePlaninarskiDom;
    for (int i=0;i<2;i++) cin>>ceni[i];
    cin>>klasa;
    cin>>daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
    if (daliZichara) {
        cin>>mestoZichara>>dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom,ceni,klasa);
        Zichara r(mestoZichara,dnevnakartaZichara);
        pom.setZichara(r);
        p=pom;
    }
    else{
        PlaninarskiDom *pok=new PlaninarskiDom(imePlaninarskiDom,ceni,klasa);
        p=*pok;
    }

    //се намалува класата на планинарскиот дом за 2
    --p;
    --p;

    int cena;
    int den,mesec;
    cin>>den>>mesec;
    try{
        p.presmetajDnevenPrestoj(den,mesec,cena); //тука се користи функцијата presmetajDnevenPrestoj
        cout<<"Informacii za PlaninarskiDomot:"<<endl;
        cout<<p;
        if (p<='D')
            cout<<"Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

        cout<<"Cenata za "<<den<<"."<<mesec<<" e "<<cena; //се печати цената за дадениот ден и месец
    }
    catch (int){
        cout<<"Mesecot ili denot e greshno vnesen!";
    }
}
