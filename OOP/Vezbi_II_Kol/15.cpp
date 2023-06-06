#include<iostream>
#include<string.h>
using namespace std;

class BadInputException {

public:
    BadInputException() {
        cout << "Greshna opisna ocenka" << endl;
    }

    char *clean(char *opisna) {
        char *otemp = new char[strlen(opisna) + 1];
        int opb = 0;
        for (int i = 0; i < strlen(opisna); i++) {
            if (isalpha(opisna[i])) {
                otemp[opb++] = opisna[i];
            }
        }
        strcpy(opisna, otemp);
        delete[] otemp;
        return opisna;
    }

};

class StudentKurs {
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;
    static int MAX;

public:
    StudentKurs(char *ime, int finalenIspit) {
        strcpy(this->ime, ime);
        this->ocenka = finalenIspit;
        this->daliUsno = false;
    }

    static void setMAX(int m) {
        MAX = m;
    }

    virtual int _ocenka() {
        return ocenka;
    }

    bool getDaliUsno() {
        return daliUsno;
    };

    friend ostream &operator<<(ostream &os, StudentKurs &sk) {
        cout << sk.ime << " --- " << sk._ocenka() << endl;
    }

    char *getIme() {
        return ime;
    }
    //дополни ја класата
};

int StudentKurs::MAX = 10;
//вметни го кодот за StudentKursUsno

class StudentKursUsno : public StudentKurs {
private:
    char *usna;
public:
    StudentKursUsno(char *ime, int finalenIspit, char *usna = "odlicen")
            : StudentKurs(ime, finalenIspit) {
        this->usna = new char[strlen(usna) + 1];
        strcpy(this->usna, usna);
        this->daliUsno = true;
    }

    StudentKursUsno(const StudentKursUsno &sku) : StudentKurs(sku) {
        this->usna = new char[strlen(sku.usna) + 1];
        strcpy(this->usna, sku.usna);
        daliUsno = sku.daliUsno;
    }

    StudentKursUsno &operator=(const StudentKursUsno &sku) {
        if (this == &sku) return *this;
        strcpy(ime, sku.ime);
        ocenka = sku.ocenka;
        daliUsno = sku.daliUsno;
        delete[] usna;
        this->usna = new char[strlen(sku.usna) + 1];
        strcpy(this->usna, sku.usna);
        return *this;
    }

    ~StudentKursUsno() {
        delete[] usna;
    }

    int _ocenka() override {
        int add = StudentKurs::_ocenka();
        if (strcmp(usna, "odlicen") == 0) add += 2;
        else if (strcmp(usna, "dobro") == 0 && ocenka != 9) add += 1;
        else if (strcmp(usna, "losho") == 0) add -= 1;
        return add;
    }

    friend ostream &operator<<(ostream &os, StudentKursUsno &sku) {
        cout << sku.ime << " --- " << sku._ocenka() << endl;
    }

    StudentKursUsno &operator+=(const char *o) {
        for (int i = 0; i < strlen(o); i++) {
            if (!isalpha(o[i])) {
                throw BadInputException();
            }
        }
        delete[] usna;
        this->usna = new char[strlen(o) + 1];
        strcpy(usna, o);
        return *this;
    }

};

class KursFakultet {
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;
    const static int MINOCENKA = 6;
public:
    KursFakultet(char *naziv, StudentKurs **studenti, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++) {
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()) {
                this->studenti[i] = new StudentKursUsno(*dynamic_cast<StudentKursUsno *>(studenti[i]));
            } else this->studenti[i] = new StudentKurs(*studenti[i]);
        }
        this->broj = broj;
    }

    void postaviOpisnaOcenka(char *ime, char *opis) {
        for (int i = 0; i < broj; i++) {
            if (strcmp(studenti[i]->getIme(), ime) == 0) {
                StudentKursUsno *temp = dynamic_cast<StudentKursUsno *>(studenti[i]);
                if (temp) {
                    *temp += opis;
                }
            }
        }
    }

    void pecatiStudenti() {
        cout << "Kursot "<<naziv<< " go polozile:" <<endl;
        for (int i = 0; i < broj; i++)
            if (studenti[i]->_ocenka() >= MINOCENKA)
                cout << * studenti[i];
    }

    ~KursFakultet() {
        for (int i = 0; i < broj; i++) delete studenti[i];
    }

    //дополни ја класата
};

int main() {

    StudentKurs **niza;
    int n, m, ocenka;
    char ime[30], opisna[10];
    bool daliUsno;
    cin >> n;
    niza = new StudentKurs *[n];
    for (int i = 0; i < n; i++) {
        cin >> ime;
        cin >> ocenka;
        cin >> daliUsno;
        if (!daliUsno)
            niza[i] = new StudentKurs(ime, ocenka);
        else
            niza[i] = new StudentKursUsno(ime, ocenka);
    }

    KursFakultet programiranje("OOP", niza, n);
    for (int i = 0; i < n; i++) delete niza[i];
    delete[] niza;
    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> ime >> opisna;
        try {
            programiranje.postaviOpisnaOcenka(ime, opisna);
        } catch (BadInputException e) {
            char *opis = e.clean(opisna);
            programiranje.postaviOpisnaOcenka(ime, opisna);
        }
    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}
