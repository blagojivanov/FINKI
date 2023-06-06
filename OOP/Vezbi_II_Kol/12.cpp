#include <iostream>
#include <cstring>

using namespace std;

class InvalidProductionDate {
public:
    InvalidProductionDate() {
        cout << "Невалидна година на производство" << endl;
    }
};

enum tip {
    smartfon, kompjuter
};

class Device {
private:
    char model[100];
    tip t;
    static float hrs;
    int year;

public:
    Device(const char *model = "", int t = (tip) 0, int year = 0) {
        strcpy(this->model, model);
        this->t = (tip) t;
        this->year = year;
    }

    float proverka() {
        float retval = Device::hrs;
        if (year > 2015) {
            retval += 2;
        }
        if (t == kompjuter) {
            retval += 2;
        }
    }

    friend ostream &operator<<(ostream &os, Device &d) {
        os << d.model << endl;
        if (d.t == smartfon) {
            os << "Mobilen ";
        } else {
            os << "Laptop ";
        }
        os << d.proverka() << endl;
        return os;
    }

    static void setPocetniCasovi(int hrs) {
        Device::hrs = hrs;
    }

    int getYear() const {
        return year;
    }
};

class MobileServis {
private:
    char address[100];
    Device *devices;
    int n;
public:
    MobileServis(const char *address = "", Device *devices = nullptr, int n = 0) {
        strcpy(this->address, address);
        this->n = n;
        this->devices = new Device[n];
        for (int i = 0; i < n; i++) {
            this->devices[i] = devices[i];
        }
    }

    MobileServis(const MobileServis &ms) {
        strcpy(this->address, ms.address);
        this->n = ms.n;
        this->devices = new Device[ms.n];
        for (int i = 0; i < ms.n; i++) {
            this->devices[i] = ms.devices[i];
        }
    }

    MobileServis &operator=(const MobileServis &ms) {
        if (this == &ms) return *this;
        strcpy(this->address, ms.address);
        this->n = ms.n;
        delete[] devices;
        this->devices = new Device[ms.n];
        for (int i = 0; i < ms.n; i++) {
            this->devices[i] = ms.devices[i];
        }
        return *this;
    }

    ~MobileServis() {
        delete[] devices;
    }

    MobileServis &operator+=(Device &d) {
        if (d.getYear() > 2019 || d.getYear() < 2000) {
            throw InvalidProductionDate();
        } else {
            Device *temp = new Device[n + 1];
            for (int i = 0; i < n; i++) {
                temp[i] = devices[i];
            }
            temp[n++] = d;
            delete[] devices;
            devices = temp;
        }
        return *this;
    }

    void pecatiCasovi() {
        cout<<"Ime: "<<address<<endl;
        for (int i = 0; i < n; i++) {
            cout << devices[i];
        }
    }
};

float Device::hrs = 1;


int main() {
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime, (tip) tipDevice, godina);
        cin >> ime;
        MobileServis t(ime);
        cout << ig;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate) {

            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate) {

            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4) {
        cout << "===== Testiranje na konstruktori ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate) {

            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate) {

            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6) {
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate) {

            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

