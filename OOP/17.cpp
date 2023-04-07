//Фирмата FINKI Cloud има потреба од решение за управување со image датотеките од различните оперативни системи кои ги користат при сетирање на нови сервери. За таа цел потребно е да се дефинираат следниве класи:
//OperativenSistem
//Во класата OperativenSistem треба да се чуваат следниве податоци:
//
//име на оперативниот систем (динамички алоцирана низа од знаци)
//верзија (float)
//тип (енумерација со можни вредности LINUX, UNIX, WINDOWS)
//големина (во GB) (float)
//Дополнително, во рамките на класата потребно е да се дефинира:
//
//конструктори со и без параметри
//copy constructor
//destructor
//преоптоварување на операторот =
//метод за печатење на информациите - void pecati() (видете го излезот од тест примерите за структурата)
//метод за проверка на еднаквост помеѓу два оперативни системи (два оперативни системи се еднакви ако имаат исто име, верзија, тип и големина) - bool ednakviSe(const OperativenSistem &os)
//метод за споредба на верзии помеѓу два оперативни система - int sporediVerzija(const OperativenSistem &os), кој ќе враќа 0 доколку верзиите се исти, -1 доколку верзијата на оперативниот систем од аргументот е поголема и 1 во преостанатиот случај.
//метод за проверка дали два оперативни системи се од иста фамилија. Два оперативни системи се од иста фамилија доколку имаат исто име и се од ист тип. bool istaFamilija(const OperativenSistem &sporedba)
//Repozitorium
//Во класата Repozitorium треба да се чуваат следниве податоци:
//
//име на репозиториумот (низа од 20 знака)
//динамички алоцирана низа од OperativenSistem
//број на оперативни системи кои моментално се наоѓаат во репозиториумот (int)
//Дополнително, во рамките на класата потребно е да се дефинира:
//
//конструктор Repozitorium(const char *ime)
//деструктор
//метод void pecatiOperativniSistemi() кој ќе ги печати сите оперативни системи кои се дел од репозиториумот
//метод void izbrishi(const OperativenSistem &operativenSistem) кој ќе го избрише оперативниот систем проследен како аргумент, доколку тој се наоѓа во репозиториумот. Да се користи методот ednakviSe за споредба на два оперативни система.
//метод за додавање на оперативен систем (void dodadi(const OperativenSistem &nov)) кој ќе го има следново однесување:
//Доколку веќе постои оперативен систем од иста фамилија (да се користи методот за проверка на фамилија) кој е постар од проследениот оперативен систем, тогаш постоечкиот оперативен систем се заменува со новиот.
//Во секој друг случај, проследениот оперативен систем се додава како дополнителен во репозиториумот.
#include <iostream>
#include <cstring>

using namespace std;

enum Tip {
    LINUX = 1, UNIX, WINDOWS
};

class OperativenSistem {

private:
    char *name;
    float version;
    Tip t;
    float size;

public:

    //constructor without parameters
    OperativenSistem() {
        name = new char[2];
        strcpy(this->name, "");
        version = 0;
        t = LINUX;
        size = 0;
    }

    //constructor with parameters
    OperativenSistem(char *name, float version, Tip t, float size) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->version = version;
        this->t = t;
        this->size = size;
    }

    //copy constructor
    OperativenSistem(const OperativenSistem &os) {
        name = new char[strlen(os.name) + 1];
        strcpy(name, os.name);
        version = os.version;
        t = os.t;
        size = os.size;
    }

    //overloading operator =
    OperativenSistem &operator=(const OperativenSistem &os) {
        if (this != &os) {
            size = os.size;
            version = os.version;
            t = os.t;
            delete[] name;
            name = new char[strlen(os.name) + 1];
            strcpy(name, os.name);
        }
        return *this;
    }

    //print function
    void pecati() {
        cout << "Ime: " << name << " Verzija: " << version << " Tip: " << t << " Golemina:" << size << "GB" << endl;
    }

    //checking if other os is equal to current
    bool ednakviSe(const OperativenSistem &os) {
        if (strcmp(name, os.name) == 0 && version == os.version && t == os.t && size == os.size) return true;
        return false;
    }

    //version comparison  0 for equal, -1 if argument os version is lower, 1 if argument os version is bigger
    int sporediVerzija(const OperativenSistem &os) {
        if (version == os.version) {
            return 0;
        } else if (version > os.version) {
            return -1;
        } else {
            return 1;
        }
    }

    //type comparison
    bool istaFamilija(const OperativenSistem &sporedba) {
        if (t == sporedba.t && strcmp(sporedba.name, name) == 0) {
            return true;
        }
        return false;
    }

    ~OperativenSistem() {
        delete[] name;
    }

};

class Repozitorium {
private:
    char name[20];
    OperativenSistem *os;
    int n;

public:

    Repozitorium(const char *ime) {
        strcpy(this->name, ime);
        this->n = 0;
    }

    void pecatiOperativniSistemi() {
        cout << "Repozitorium: " << name << endl;
        for (int i = 0; i < n; i++) {
            os[i].pecati();
        }
    }

    void izbrishi(const OperativenSistem &operativenSistem) {
        for (int i = 0; i < n; i++) {
            if (os[i].ednakviSe(operativenSistem)) {
                int nov = 0;
                OperativenSistem *temp = new OperativenSistem[n - 1];
                for (int j = 0; j < n; j++) {
                    if (i == j)
                    {
                        continue;
                    } else
                    {
                        temp[nov++] = os[j];
                    }
                }
                delete[] os;
                os = temp;
                n--;
            }
        }
    }

    void dodadi(const OperativenSistem &nov) {
        if (n == 0) {
            this->os = new OperativenSistem[1];
            this->n = 1;
            os[0] = nov;
        } else {
            bool pass = false;
            for (int i = 0; i < n; i++) {
                if (os[i].istaFamilija(nov)) {
                    if (os[i].sporediVerzija(nov) == 1) {
                        os[i] = nov;
                        pass = true;
                    }
                }
            }
            if (pass == false)
            {
                OperativenSistem *temp;
                temp = new OperativenSistem[n + 1];
                for (int j = 0; j < n; j++) {
                    temp[j] = os[j];
                }
                temp[n] = nov;
                n++;
                delete[] os;
                os = temp;
            }
        }
    }

    ~Repozitorium() {
        delete[] os;
    }
};

int main() {
    char repoName[20];
    cin >> repoName;
    Repozitorium repozitorium = Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin >> brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i < brojOperativniSistemi; i++) {
        cin >> ime;
        cin >> verzija;
        cin >> tip;
        cin >> golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip) tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin >> ime;
    cin >> verzija;
    cin >> tip;
    cin >> golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip) tip, golemina);
    cout << "=====Brishenje na operativen sistem=====" << endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}