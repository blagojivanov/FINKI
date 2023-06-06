#include <iostream>
#include <cstring>

using namespace std;

class UserExistsException : public exception {
public:
    UserExistsException() {
        cout << "The user already exists in the list!" << endl;
    }
};

const int MAX = 50;
enum typeC {
    standard, loyal, vip
};

class Customer {
private:
    char ime[MAX];
    char email[MAX];
    typeC t;
    static int pop;
    const static int dpop;
    int n;

public:
    Customer(const char *ime = "", const char *email = "", int t = (typeC) 0, int n = 0) {
        strcpy(this->ime, ime);
        strcpy(this->email, email);
        this->t = (typeC) t;
        this->n = n;
    }

    static void setDiscount1(int pop) {
        Customer::pop = pop;
    }

    friend ostream &operator<<(ostream &os, Customer &c) {
        os << c.ime << endl;
        os << c.email << endl;
        os << c.n << endl;
        if (c.t == standard) os << "standard ";
        else if (c.t == loyal) os << "loyal ";
        else if (c.t == vip) os << "vip ";
        if (c.t == standard) os << 0 << endl;
        else if (c.t == loyal) os << c.pop << endl;
        else if (c.t == vip) os << c.pop + c.dpop << endl;

    }

    const char *getEmail() const {
        return email;
    }

    void setType(int type) {
        t = (typeC) type;
    }

    int getN() {
        return n;
    }

    typeC getType() {
        return t;
    }
};

class FINKI_bookstore {
private:
    Customer *users;
    int number;
public:
    FINKI_bookstore(Customer *users = 0, int number = 0) {
        if (number > 0) {
            this->number = number;
            this->users = new Customer[number];
            for (int i = 0; i < number; i++) {
                this->users[i] = users[i];
            }
        } else {
            this->number = 0;
            this->users = nullptr;
        }
    }

    FINKI_bookstore(const FINKI_bookstore &fb) {
        number = fb.number;
        users = new Customer[fb.number];
        for (int i = 0; i < number; i++) {
            users[i] = fb.users[i];
        }
    }

    FINKI_bookstore &operator=(const FINKI_bookstore &fb) {
        if (this == &fb) return *this;
        number = fb.number;
        delete[] users;
        users = new Customer[fb.number];
        for (int i = 0; i < number; i++) {
            users[i] = fb.users[i];
        }
        return *this;
    }

    ~FINKI_bookstore() {
        delete[] users;
    }

    FINKI_bookstore operator+=(const Customer &c) {
        for (int i = 0; i < number; i++) {
            if (strcmp(users[i].getEmail(), c.getEmail()) == 0) {
                throw UserExistsException();
            }
        }
        Customer *temp = new Customer[number + 1];
        for (int i = 0; i < number; i++) {
            temp[i] = users[i];
        }
        temp[number++] = c;
        delete[] users;
        users = temp;
    }

    void setCustomers(Customer *customers, int n) {
        number = n;

        users = new Customer[n];
        for (int i = 0; i < n; i++) {
            users[i] = customers[i];
        }
    }

    void update() {
        for (int i = 0; i < number; i++) {
            if (users[i].getN() > 10 && users[i].getType() == loyal) {
                users[i].setType(vip);
            } else if (users[i].getN() > 5 && users[i].getType() == standard) {
                users[i].setType(loyal);
            }
        }
    }

    friend ostream &operator<<(ostream &os, FINKI_bookstore &fb) {
        for (int i = 0; i < fb.number; i++) {
            os << fb.users[i];
        }
        return os;
    }

};

int Customer::pop = 10;
const int Customer::dpop = 20;


int main() {
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1) {
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2) {
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3) {
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc << endl;
    }

    if (testCase == 4) {
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc += c;

        cout << fc;
    }

    if (testCase == 5) {
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, tC, numProducts);
        try {
            fc += c;
        } catch (UserExistsException) {

        }

        cout << fc;
    }

    if (testCase == 6) {
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
