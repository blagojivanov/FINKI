//Да се дефинира класа IceCream во која се чуваат податоци за:
//
//име (динамичка низа од знаци),
//состав (низа од знаци, најмногу 100)
//цена (децимален број),
//попуст (цел број, изразен во проценти) иницијална вредност 0.
//За потребите на класата да се имплементираат:
//
//соодветни конструктори и деструктор (да се погледнат повиците во функцијата main)
//оператор << за печатење на податоците за сладоледот во следниов формат:
//име: состав цена [цена на попуст]
//
//делот „цена на попуст“ се печати само ако за сладоледот се нуди попуст (вредноста на попустот е поголема од нула)
//
//оператор ++ во префикс нотација за зголемување на попустот за 5
//оператор + - за собирање на објект од класата IceCream со низа од знаци. Собирањето се реализира на начин што името на новиот сладолед се добива со спојување на името на сладоледот и низата од знаци одделени со „ + “. Цената на новиот сладолед се зголемува за 10, а попустот и составот на сладоледот остануваат исти.
//метод void setDiscount(int discount) со кој може да се смени вредноста на попустот. Дозволените вредности на попустот се во интервалот [0,100]
//метод void setName(char* name) со кој се менува името на сладоледот.
//Да се креира класа IceCreamShop во која се чува:
//
//име на продавницата (низа од знаци, најмногу 50)
//динамички резервирано поле од објекти од класата IceCream
//број на сладоледи во полето (цел број).
//За оваа класа да се обезбедат:
//
//соодветни конструктори и деструктор (погледнете ги повиците во main функцијата)
//оператор += за додавање нов објект од класата IceCream во полето
//оператор << за печатење на листа од сите сладоледи во продавницата. Прво се печати името на продавницата, а потоа се печатат податоците за сите сладоледи одделени со нов ред.
#include <iostream>
#include <cstring>

using namespace std;

class IceCream {
private:
    char *name;
    char composition[100];
    float price;
    int discount = 0;
public:

    IceCream(const char *name = "", const char *composition = "", float price = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strncpy(this->composition, composition, 99);
        this->composition[99] = '\0';
        this->price = price;
        this->discount = 0;
    }

    IceCream(const IceCream &ic) {
        name = new char[strlen(ic.name) + 1];
        strcpy(name, ic.name);
        strcpy(composition, ic.composition);
        composition[99] = '\0';
        price = ic.price;
        discount = ic.discount;
    }

    IceCream &operator=(const IceCream &ic) {
        if (this == &ic) return *this;


        delete[] name;
        name = new char[strlen(ic.name) + 1];
        strcpy(name, ic.name);
        strcpy(composition, ic.composition);
        composition[99] = '\0';
        price = ic.price;
        discount = ic.discount;

        return *this;
    }

    friend ostream &operator<<(ostream &out, const IceCream &ic) {
        out << ic.name << ": " << ic.composition << " " << ic.price;

        if (ic.discount > 0) {
            out << " (" << ic.price * float(100 - ic.discount) / 100 << ")";
        }
        return out;
    }

    void setDiscount(int d) {

        if (d >= 0 && d <= 100)
            discount = d;
    }

    void setName(char *name) {
        delete[] this->name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    ~IceCream() {
        delete[] name;
    }

    IceCream &operator++() {
        discount += 5;
        return *this;
    }

    IceCream operator+(const char *name) {
        char *tname = new char[strlen(name) + strlen(this->name) + 4];
        strcpy(tname, this->name);
        strcat(tname, " + ");
        strcat(tname, name);

        IceCream res(tname, composition, price + 10);
        res.setDiscount(discount);

        delete[] tname;
        return res;
    }


};

class IceCreamShop {
private:
    char name[50];
    IceCream *iceCreams;
    int n;

public:

    IceCreamShop(char *name) {
        strcpy(this->name, name);
        this->n = 0;
        this->iceCreams = NULL;
    }

    IceCreamShop(const IceCreamShop &ics)
    {
        strcpy(this->name, ics.name);
        this->n = ics.n;
        iceCreams = new IceCream[ics.n];
        for (int i = 0; i < n; ++i) {
            iceCreams[i] = ics.iceCreams[i];
        }
    }

    IceCreamShop &operator=(const IceCreamShop &ics)
    {
        if (this != &ics)
        {
            delete [] iceCreams;
            strcpy(this->name, ics.name);
            this->n = ics.n;
            iceCreams = new IceCream[ics.n];
            for (int i = 0; i < n; ++i) {
                iceCreams[i] = ics.iceCreams[i];
            }
        }
        return *this;
    }

    IceCreamShop &operator+=(IceCream &ic) {
        IceCream *ics = iceCreams;
        iceCreams = new IceCream[n + 1];
        for (int i = 0; i < n; i++) {
            iceCreams[i] = ics[i];
        }
        iceCreams[n] = ic;
        n++;
        delete[] ics;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const IceCreamShop &ics) {
        cout << ics.name << endl;
        for (int i = 0; i < ics.n; ++i) {
            out << ics.iceCreams[i] << endl;
        }
        return out;
    }

    ~IceCreamShop() {
        delete[] iceCreams;
    }

};

int main() {

    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if (testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if (testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        //cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if (testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if (testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics += x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}