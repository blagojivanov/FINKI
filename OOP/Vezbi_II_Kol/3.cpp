#include <iostream>
#include <cstring>

using namespace std;

class NoCourseException : public exception {
private:
    int index;
public:
    NoCourseException(int index) {
        this->index = index;
    }

    void print() {
        cout << "Demonstratorot so indeks " << index << " ne drzi laboratoriski vezbi" << endl;
    }

    void setIndex(int id) {
        index = id;
    }
};

class Kurs {
protected:
    char *name;
    int kred;

public:
    Kurs(const char *name = "", int kred = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->kred = kred;
    }

    Kurs(const Kurs &k) {
        this->name = new char[strlen(k.name) + 1];
        strcpy(this->name, k.name);
        this->kred = k.kred;
    }

    Kurs &operator=(const Kurs &k) {
        if (this == &k) return *this;
        delete[] name;
        this->name = new char[strlen(k.name) + 1];
        strcpy(this->name, k.name);
        this->kred = k.kred;
        return *this;
    }

    ~Kurs() {
        delete[] name;
    }

    const char *getName() {
        return name;
    }

    int getKrediti() const {
        return kred;
    }

};

class Student {
protected:
    int index;
    int *ocenki;
    int n;
public:
    Student(int index = 0, int *ocenki = 0, int n = 0) {
        this->index = index;
        this->ocenki = new int[n];
        this->n = n;
        for (int i = 0; i < n; i++) {
            this->ocenki[i] = ocenki[i];
        }
    }

    Student(const Student &s) {
        this->index = s.index;
        this->ocenki = new int[s.n];
        this->n = s.n;
        for (int i = 0; i < s.n; i++) {
            this->ocenki[i] = s.ocenki[i];
        }
    }

    Student &operator=(const Student &s) {
        if (this == &s) return *this;
        delete[] ocenki;
        this->index = s.index;
        this->ocenki = new int[s.n];
        this->n = s.n;
        for (int i = 0; i < s.n; i++) {
            this->ocenki[i] = s.ocenki[i];
        }
        return *this;
    }

    virtual void pecati() {
        cout << index;
    }

    virtual int getBodovi() {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (ocenki[i] >= 6) count++;
        }
        return ((float) count / n) * 100;
    }

    int getIndex() {
        return index;
    }

    ~Student() {
        delete[] ocenki;
    }
};

class Predavach {
protected:
    char *name;
    Kurs *kursevi;
    int brK;

public:
    Predavach(const char *name = "", Kurs *kursevi = 0, int brK = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->brK = brK;
        this->kursevi = new Kurs[brK];
        for (int i = 0; i < brK; i++) {
            this->kursevi[i] = kursevi[i];
        }
    }

    Predavach(const Predavach &p) {
        this->name = new char[strlen(p.name) + 1];
        strcpy(this->name, p.name);
        this->brK = p.brK;
        this->kursevi = new Kurs[p.brK];
        for (int i = 0; i < p.brK; i++) {
            this->kursevi[i] = p.kursevi[i];
        }
    }

    Predavach &operator=(const Predavach &p) {
        if (this == &p) return *this;
        delete[] name;
        delete[] kursevi;
        this->name = new char[strlen(p.name) + 1];
        strcpy(this->name, p.name);
        this->brK = p.brK;
        this->kursevi = new Kurs[p.brK];
        for (int i = 0; i < p.brK; i++) {
            this->kursevi[i] = p.kursevi[i];
        }
        return *this;
    }

};

class Demonstrator : public Student, public Predavach {
private:
    int chasovi;

public:
    Demonstrator(int index = 0, int *ocenki = 0, int n = 0, const char *name = "", Kurs *kursevi = 0, int brK = 0,
                 int chasovi = 0)
            : Student(index, ocenki, n), Predavach(name, kursevi, brK) {
        this->chasovi = chasovi;
    }

    Demonstrator(const Demonstrator &d) : Student(d), Predavach(d) {
        this->chasovi = d.chasovi;
    }

    Demonstrator &operator=(const Demonstrator &d) {
        if (this == &d) return *this;
        delete[] ocenki;
        delete[] name;
        delete[] kursevi;

        this->chasovi = d.chasovi;
        this->index = d.index;

        this->name = new char[strlen(d.name) + 1];
        strcpy(this->name, d.name);

        this->ocenki = new int[d.n];
        for (int i = 0; i < d.n; i++) {
            this->ocenki[i] = d.ocenki[i];
        }

        this->n = d.n;
        this->brK = d.brK;
        this->kursevi = new Kurs[d.brK];

        for (int i = 0; i < d.brK; i++) {
            this->kursevi[i] = d.kursevi[i];
        }
        return *this;
    }

    void pecati() override {
        cout << index << ": " << name;

        cout << " (";
        for (int i = 0; i < brK; i++) {
            cout << kursevi[i].getName() << " " << kursevi[i].getKrediti() << "ECTS";
            if (i < brK - 1) {
                cout << ", ";
            }
        }
        cout << ")";

    }

    int getBodovi() override {
        if (chasovi == 0) {
            throw NoCourseException(index);
        } else {

            int bod = Student::getBodovi();
            bod += (20 * chasovi) / brK;
            return bod;
        }
    }

    int getNum() {
        if (brK == 0) throw(NoCourseException(index));
        return brK;
    }

    Kurs getKursevi(int id) {
        return kursevi[id];
    }
};

Student &vratiNajdobroRangiran(Student **studenti, int n) {
    Student *najdobar = studenti[0];

    for (int i = 0; i < n; i++) {
        Demonstrator *temp = dynamic_cast<Demonstrator *>(studenti[i]);
        try {
            if (najdobar->getBodovi() < studenti[i]->getBodovi()) {
                najdobar = studenti[i];
            }
        } catch (NoCourseException e) {
            e.print();
        }
    }

    return *najdobar;
}

void pecatiDemonstratoriKurs(char *kurs, Student **studenti, int n) {
    for (int i = 0; i < n; i++) {
        Demonstrator *temp = dynamic_cast<Demonstrator *>(studenti[i]);
        if (temp != 0) {
            for (int j = 0; j < temp->getNum(); j++) {
                if (strcmp(temp->getKursevi(j).getName(), kurs) == 0) {
                    temp->pecati();
                    cout << endl;
                }
            }
        }
    }
}

int main() {

    Kurs kursevi[10];
    int indeks, brojKursevi, ocenki[20], ocenka, brojOcenki, tip, brojCasovi, krediti;
    char ime[20], imeIPrezime[50];

    cin >> tip;

    if (tip == 1) //test class Demonstrator
    {
        cout << "-----TEST Demonstrator-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> imeIPrezime >> brojKursevi;
        for (int i = 0; i < brojKursevi; i++) {
            cin >> ime >> krediti;
            kursevi[i] = Kurs(ime, krediti);
        }
        cin >> brojCasovi;

        Demonstrator d(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi, brojCasovi);
        cout << "Objekt od klasata Demonstrator e kreiran";

    } else if (tip == 2) //funkcija pecati vo Student
    {
        cout << "-----TEST pecati-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }

        Student s(indeks, ocenki, brojOcenki);
        s.pecati();

    } else if (tip == 3) //funkcija getVkupnaOcenka vo Student
    {
        cout << "-----TEST getVkupnaOcenka-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        Student s(indeks, ocenki, brojOcenki);
        cout << "Broj na bodovi: " << s.getBodovi() << endl;

    } else if (tip == 4) //funkcija getVkupnaOcenka vo Demonstrator
    {
        cout << "-----TEST getVkupnaOcenka-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> imeIPrezime >> brojKursevi;
        for (int i = 0; i < brojKursevi; i++) {
            cin >> ime >> krediti;
            kursevi[i] = Kurs(ime, krediti);
        }
        cin >> brojCasovi;

        Demonstrator d(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi, brojCasovi);
        cout << "Broj na bodovi: " << d.getBodovi() << endl;

    } else if (tip == 5) //funkcija pecati vo Demonstrator
    {
        cout << "-----TEST pecati -----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> imeIPrezime >> brojKursevi;
        for (int i = 0; i < brojKursevi; i++) {
            cin >> ime >> krediti;
            kursevi[i] = Kurs(ime, krediti);
        }
        cin >> brojCasovi;

        Demonstrator d(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi, brojCasovi);
        d.pecati();

    } else if (tip == 6) //site klasi
    {
        cout << "-----TEST Student i Demonstrator-----" << endl;
        cin >> indeks >> brojOcenki;
        for (int i = 0; i < brojOcenki; i++) {
            cin >> ocenka;
            ocenki[i] = ocenka;
        }
        cin >> imeIPrezime >> brojKursevi;
        for (int i = 0; i < brojKursevi; i++) {
            cin >> ime >> krediti;
            kursevi[i] = Kurs(ime, krediti);
        }
        cin >> brojCasovi;

        Student *s = new Demonstrator(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi, brojCasovi);
        s->pecati();
        cout << "\nBroj na bodovi: " << s->getBodovi() << endl;
        delete s;


    } else if (tip == 7) //funkcija vratiNajdobroRangiran
    {
        cout << "-----TEST vratiNajdobroRangiran-----" << endl;
        int k, opt;
        cin >> k;
        Student **studenti = new Student *[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 Student 2 Demonstrator
            cin >> indeks >> brojOcenki;
            for (int i = 0; i < brojOcenki; i++) {
                cin >> ocenka;
                ocenki[i] = ocenka;
            }
            if (opt == 1) {
                studenti[j] = new Student(indeks, ocenki, brojOcenki);
            } else {
                cin >> imeIPrezime >> brojKursevi;
                for (int i = 0; i < brojKursevi; i++) {
                    cin >> ime >> krediti;
                    kursevi[i] = Kurs(ime, krediti);
                }
                cin >> brojCasovi;
                studenti[j] = new Demonstrator(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi,
                                               brojCasovi);
            }
        }

        Student &najdobar = vratiNajdobroRangiran(studenti, k);
        cout << "Maksimalniot broj na bodovi e:" << najdobar.getBodovi();
        cout << "\nNajdobro rangiran:";
        najdobar.pecati();

        for (int j = 0; j < k; j++) delete studenti[j];
        delete[] studenti;
    } else if (tip == 8) //funkcija pecatiDemonstratoriKurs
    {
        cout << "-----TEST pecatiDemonstratoriKurs-----" << endl;
        int k, opt;
        cin >> k;
        Student **studenti = new Student *[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 Student 2 Demonstrator
            cin >> indeks >> brojOcenki;
            for (int i = 0; i < brojOcenki; i++) {
                cin >> ocenka;
                ocenki[i] = ocenka;
            }
            if (opt == 1) {
                studenti[j] = new Student(indeks, ocenki, brojOcenki);
            } else {
                cin >> imeIPrezime >> brojKursevi;
                for (int i = 0; i < brojKursevi; i++) {
                    cin >> ime >> krediti;
                    kursevi[i] = Kurs(ime, krediti);
                }
                cin >> brojCasovi;
                studenti[j] = new Demonstrator(indeks, ocenki, brojOcenki, imeIPrezime, kursevi, brojKursevi,
                                               brojCasovi);
            }
        }
        char kurs[20];
        cin >> kurs;
        cout << "Demonstratori na " << kurs << " se:" << endl;
        pecatiDemonstratoriKurs(kurs, studenti, k);
        for (int j = 0; j < k; j++) delete studenti[j];
        delete[] studenti;

    }


    return 0;
}