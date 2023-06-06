#include <iostream>
#include <cstring>

using namespace std;

class Transport
{
protected:
    char dest[20];
    int cena;
    int km;

public:
    Transport(const char *dest = "", int cena = 0, int km = 0)
    {
        strcpy(this->dest, dest);
        this->cena = cena;
        this->km = km;
    }
    virtual int cenaTransport()=0;
    bool operator<(Transport &t)
    {
        if (km < t.km)
        {
            return true;
        }
        return false;
    }
    int getkm()
    {
        return km;
    }
    const char *getDest() const {
        return dest;
    }

};
class AvtomobilTransport : public Transport
{
private:
    bool shofer;

public:
    AvtomobilTransport(const char *dest = "", int cena = 0, int km = 0, bool shofer = false)
            : Transport(dest, cena, km){
        this->shofer = shofer;
    }
    int cenaTransport() override
    {
        return (shofer) ? cena*1.2 : cena;
    }
};

class KombeTransport : public Transport
{
private:
    int br;
public:
    KombeTransport(const char *dest = "", int cena = 0, int km = 0, int br = 0)
            : Transport(dest, cena, km){
        this->br = br;
    }

    int cenaTransport() override
    {
        return cena-(br*200);
    }
};

void pecatiPoloshiPonudi(Transport **ponudi,int n, Transport &t)
{
    Transport **kopija = new Transport*[n];
    kopija = ponudi;
    for (int i = 0; i<n; i++)
    {
        int id = i;
        Transport *temp = kopija[i];
        for (int j = i; j<n; j++)
        {
            int km1 = temp->getkm();
            int km2 = kopija[j]->getkm();
            if (temp->getkm() > kopija[j]->getkm())
            {
                id = j;
                temp = kopija[j];
            }
        }
        if (id != i)
        {
            swap(kopija[i], kopija[id]);
        }
    }
    Transport *tp = &t;
    for (int i = 0; i<n; i++)
    {
        if (kopija[i]->cenaTransport() > tp->cenaTransport())
        {
            cout<<kopija[i]->getDest()<<" "<<kopija[i]->getkm()<<" "<<kopija[i]->cenaTransport()<<endl;
        }
    }

}


int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
