//Треба да се напише класа FoodItem која што ги има овие две чисти виртуелни функции:
//
//getPrice() - цена на храната
//getTime() - време за подготвување на храната
//        Исто така, треба класата да ги има следните информации:
//
//type (динамички алоцирана низа од карактери) - типот на храната
//num(int)- количина на храната
//        Понатаму, треба да креирате 2 подкласи на FoodItem наречени:
//
//Pizza
//        Steak
//Класата Pizza треба да ги има овие информации:
//
//dough (динамички алоцирана низа од карактери) - какво тесто е пицата
//Цана на едно тесто:
//- "wholeWheat" : 250
//- "glutenFree" : 350
//
//Време на правење на пица е 25 минути, независно од колку пици има.
//Ако се прават n пици потребна е n количина на тесто.
//Класата Steak треба да ги има овие информации:
//
//bool cooked (дали е well done или medium rare)
//Време на правење, независно колку steaks има:
//
//-  well done : 20 min
//
//-  medium rare: 15 min
//
//        Цена на еден стек е 1300 ден.
//
//
//
//Треба исто така да напишете глобална функција:
//
//getMaxFoodItem(FoodItem *pItem[], int n) , која што ќе враќа покажувач до најскапиот FoodItem

#include <iostream>
#include <cstring>

using namespace std;

class FoodItem {
protected:
    char *type;
    int num;
public:
    FoodItem(char *type = "", int num = 0) {
        this->type = new char[strlen(type) + 1];
        strcpy(this->type, type);
        this->num = num;
    }

    FoodItem(const FoodItem &fi) {
        this->type = new char[strlen(fi.type) + 1];
        strcpy(this->type, fi.type);
        this->num = fi.num;
    }

    FoodItem &operator=(const FoodItem &fi) {
        if (this == &fi) return *this;
        delete[] type;
        this->type = new char[strlen(fi.type) + 1];
        strcpy(this->type, fi.type);
        this->num = fi.num;
        return *this;
    }

    ~FoodItem() {
        delete[] type;
    }

    char* getType()
    {
        return type;
    }

    virtual int getPrice() = 0;

    virtual int getTime() = 0;
};

class Pizza : public FoodItem {
private:
    char *dough;
public:
    Pizza(char *type = "", int num = 0, char *dough = "") : FoodItem(type, num) {
        this->dough = new char[strlen(dough) + 1];
        strcpy(this->dough, dough);
    }

    Pizza(const Pizza &p) : FoodItem(p) {
        this->dough = new char[strlen(p.dough) + 1];
        strcpy(this->dough, p.dough);
    }

    Pizza &operator=(const Pizza &p) {
        if (this == &p) return *this;
        delete[] type;
        delete[] dough;
        this->type = new char[strlen(p.type) + 1];
        strcpy(this->type, p.type);
        this->num = p.num;

        this->dough = new char[strlen(p.dough) + 1];
        strcpy(this->dough, p.dough);
        return *this;
    }

    ~Pizza()
    {
        delete [] dough;
    }
    int getPrice() override
    {
        int price = 0;
        if (strcmp(dough, "wholeWheat") == 0)
        {
            price = 250;
        } else if (strcmp(dough, "glutenFree") == 0)
        {
            price = 350;
        }
        return num*price;
    }

    int getTime() override
    {
        return 25;
    }
};

class Steak : public FoodItem
{
private:
    bool cooked;
public:
    Steak(char *type = "", int num = 0, bool cooked = false) : FoodItem(type, num)
    {
        this->cooked = cooked;
    }
    Steak(const Steak &s) : FoodItem(s)
    {
        this->cooked = s.cooked;
    }

    Steak &operator=(const Steak &s) {
        if (this == &s) return *this;
        delete[] type;
        this->cooked = s.cooked;
        this->type = new char[strlen(s.type) + 1];
        strcpy(this->type, s.type);
        this->num = s.num;
        return *this;
    }

    int getPrice() override
    {
        return num*1300;
    }

    int getTime() override
    {
        if (cooked)
        {
            return 20;
        }
        return 15;
    }
};

FoodItem* getMaxFoodItem(FoodItem *pItem[], int n)
{
    FoodItem *max = pItem[0];
    for (int i = 1; i<n; i++)
    {
        if (max->getPrice() < pItem[i]->getPrice())
        {
            max = pItem[i];
        }
    }
    return max;
}

int main() {
    FoodItem *p;
    int n;
    cin >> n;

    char type[30];
    char dough[30];
    bool cooked;
    int size;

    FoodItem *items[n];

    for (int i = 0; i < n; ++i) {
        cin >> type;
        cin >> size;


        if (strcmp(type, "pizza") == 0) {
            cin >> dough;
            items[i] = new Pizza(type, size, dough);
        } else {
            cin >> cooked;
            items[i] = new Steak(type, size, cooked);
        }


    }

    FoodItem *it = getMaxFoodItem(items, n);
    cout << "Type: " << it->getType() << endl;
    cout << "The max price is: " << it->getPrice() << endl;
    cout << "Time to cook: " << it->getTime();
    return 0;
}
