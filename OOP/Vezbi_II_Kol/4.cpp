#include <cstring>
#include <iostream>

using namespace std;

// Your Code goes here

enum Size {
    small, large, familijarna
};

class Pizza {
protected:
    char name[20];
    char ingredients[100];
    float cena;

public:
    Pizza(const char *name = "", const char *ingredients = "", float cena = 0) {
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
        this->cena = cena;
    }

    friend ostream &operator<<(ostream &os, Pizza &p)
    {
        os << p.name << ": " << p.ingredients;
    }
    bool operator<(Pizza &p)
    {
        Pizza *t = &p;
        if ((int) price() < (int) t->price()) return true;
        return false;
    }
    virtual float price() = 0;

};

class FlatPizza : public Pizza {
private:
    Size s;
public:
    FlatPizza(const char *name = "", const char *ingredients = "", float cena = 0, int s = (Size) 0)
            : Pizza(name, ingredients, cena) {
        this->s = (Size) s;
    }
    float price()
    {
        if (s == small) return cena*1.1;
        else if (s == large) return cena*1.2;
        else if (s == familijarna) return cena*1.3;
    }

    friend ostream &operator<<(ostream &os, FlatPizza &fp)
    {
        os << fp.name << ": "<< fp.ingredients;
        if (fp.s == small) os << ", small";
        else if (fp.s == large) os << ", large";
        else if (fp.s == familijarna) os << ", family";
        os<<" - "<< fp.price()<<endl;
        return os;
    }
};

class FoldedPizza : public Pizza {
private:
    bool whiteFlour;
public:
    FoldedPizza(const char *name = "", const char *ingredients = "", float cena = 0, bool whiteFlour = false)
            : Pizza(name, ingredients, cena) {
        this->whiteFlour = true;
    }

    float price()
    {
        if (whiteFlour)
        {
            return cena*1.1;
        }
        else {
            return cena * 1.3;
        }
    }
    friend ostream &operator<<(ostream &os, FoldedPizza &fp)
    {
        os << fp.name << ": "<< fp.ingredients;

        if (fp.whiteFlour)
        {
            os << ", wf";
        }
        else
        {
            os << ", nwf";
        }

        os<<" - "<< fp.price()<<endl;
        return os;
    }
    void setWhiteFlour(bool tf)
    {
        whiteFlour = tf;
    }
};


void expensivePizza(Pizza **niza, int n)
{
    Pizza *ret = niza[0];
    int maxc = 0;
    int maxPrice = niza[0]->price();
    for (int i = 0; i<n; i++)
    {
        FoldedPizza *fold = dynamic_cast<FoldedPizza *>(niza[i]);
        FlatPizza *flat = dynamic_cast<FlatPizza*>(niza[i]);
        if (fold !=0)
        {
            if (ret->price() < fold->price())
            {
                ret = fold;
                maxc = i;
                maxPrice = fold ->price();
            }
        } else
        {
            if (ret->price() < flat->price())
            {
                ret = flat;
                maxc = i;
                maxPrice = flat->price();

            }
        }
    }
    FoldedPizza *fold = dynamic_cast<FoldedPizza *>(niza[maxc]);
    FlatPizza *flat = dynamic_cast<FlatPizza*>(niza[maxc]);
    if (fold != 0)
    {
        cout << *fold;
    } else
    {
        cout << *flat;
    }
}


// Testing

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        int s;
        cin >> s;
        FlatPizza fp(name, ingredients, inPrice, (Size) s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp1;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp2;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout << "Lower price: " << endl;
        if (*fp1 < *fp2)
            cout << fp1->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp1 < *fp3)
            cout << fp1->price() << endl;
        else cout << fp3->price() << endl;

        if (*fp4 < *fp2)
            cout << fp4->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp3 < *fp4)
            cout << fp3->price() << endl;
        else cout << fp4->price() << endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name, 20);

                cin.getline(ingredients, 100);
                cin >> inPrice;
                int s;
                cin >> s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size) s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name, 20);
                cin.getline(ingredients, 100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza(name, ingredients, inPrice);
                if (j % 2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi, num_p);


    }
    return 0;
}
