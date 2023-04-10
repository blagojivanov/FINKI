//Да се дефинира класа Пица за која ќе се чуваат податоци за:
//
//име на пицата (низа од 15 знаци)
//цена (цел број)
//состојки (динамички алоцирана низа од знаци)
//намалување на цената во проценти (цел број) - ако пицата не е на промоција намалувањето има вредност нула, во спротивно, вредност поголема од нула и не поголема од 100.
//За потребите на оваа класа да се креираат потребните конструктори и да се напише соодветен деструктор. Дополнително за оваа класа да се дефинира функцијата:
//
//pecati() - функција во која ќе се печатат податоците за пицата во следниот формат: име - состојки, цена.
//istiSe(Pica p) - функција за споредба на две пици според состојките :
//Да се дефинира класа Picerija во која се чуваат:
//
//име (низа од максимум 15 знаци)
//динмички алоцирана низа од објекти од класата Pica
//број на пици (цел број)
//За потребите на оваа класа да се дефинираат потребните конструктори и да се напише соодветен деструктор. Да се имплементираат и следниве методи:
//
//dodadi(Pica P) - за додавање нова пица во пицеријата, но само ако не постои иста во низата (нема пица со исти состојки со пицата што треба да се додаде).
//void piciNaPromocija() - се печатат сите пици од пицеријата што се на промоција во формат : име - состојки, цена, цена со попуст.
#include <iostream>
#include <cstring>

using namespace std;

class Pica {
private:
    char name[15];
    int price;
    char *sostojki;
    int proc;

public:

    Pica(char *name = "", int price = 0, char *sostojki = "", int proc=0) {
        strcpy(this->name, name);
        this->price = price;
        this->sostojki = new char[strlen(sostojki) + 1];
        strcpy(this->sostojki, sostojki);
        this->proc = proc;
    }

    Pica(const Pica &p) {
        strcpy(name, p.name);
        price = p.price;
        sostojki = new char[strlen(p.sostojki) + 1];
        strcpy(sostojki, p.sostojki);
        proc = p.proc;
    }

    Pica &operator=(const Pica& p) {
        if (this != &p) {
            strcpy(name, p.name);
            price = p.price;
            delete[] sostojki;
            sostojki = new char[strlen(p.sostojki) + 1];
            strcpy(sostojki, p.sostojki);
            proc = p.proc;
        }
        return *this;
    }

    ~Pica() {
        delete[] sostojki;
    }

    void pecati() {
        cout << name << " - " << sostojki << ", " << price;
    }

    bool istiSe(const Pica &p){
        return (strcmp(sostojki, p.sostojki) == 0);
    }

    int getPrice() {
        return price;
    }

    int getProc()
    {
        return proc;
    }

};

class Picerija
{
private:
    char name[15];
    Pica *pizzas;
    int n;

public:

    Picerija(char *name = "", int n = 0, Pica *pizzas = nullptr)
    {
        strcpy(this->name, name);
        this->n = n;
        this->pizzas = new Pica[n];
        for (int i = 0; i<n; i++)
        {
            this->pizzas[i] = pizzas[i];
        }
    }

    Picerija(const Picerija &p)
    {
        strcpy(this->name, p.name);
        this->n = p.n;
        this->pizzas = new Pica[p.n];
        for (int i = 0; i<p.n; i++)
        {
            this->pizzas[i] = p.pizzas[i];
        }
    }

    Picerija &operator=(const Picerija &p)
    {
        if (this == &p) return *this;
        strcpy(this->name, p.name);
        this->n = p.n;
        delete [] pizzas;
        this->pizzas = new Pica[p.n];
        for (int i = 0; i<p.n; i++)
        {
            this->pizzas[i] = p.pizzas[i];
        }
        return *this;
    }

    void dodadi(const Pica &p)
    {
        for (int i = 0; i<n; i++)
        {
            if (pizzas[i].istiSe(p))
            {
                return;
            }
        }
        Pica *temp = new Pica[n+1];
        for (int i = 0; i<n; i++)
        {
            temp[i] = pizzas[i];
        }

        temp[n++] = p;
        delete [] pizzas;
        pizzas = temp;
    }

    void piciNaPromocija()
    {
        for (int i = 0; i<n; i++)
        {
            if (pizzas[i].getProc() > 0)
            {
                pizzas[i].pecati();
                cout<<" "<<pizzas[i].getPrice()*(1-(float)pizzas[i].getProc()/100)<<endl;
            }
        }
    }

    void setIme(char *ime)
    {
        strcpy(this->name, ime);
    }

    char *getIme()
    {
        return name;
    }

    ~Picerija()
    {
        delete [] pizzas;
    }


};

int main() {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1.dodadi(p);
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2.dodadi(p);

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}