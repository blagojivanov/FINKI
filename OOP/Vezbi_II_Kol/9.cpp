#include <iostream>
#include <cstring>

using namespace std;

class Exception : public exception
{
public:
    Exception()
    {
        cout<<"Ne moze da se vnese dadeniot trud"<<endl;
    }
};

class Trud {
private:
    char c;
    int year;
    static int bC;
    static int bS;

public:
    Trud(char c = 'C', int year = 0) {
        this->c = c;
        this->year = year;
    }
    char getType()
    {
        return c;
    }
    static int getBc()
    {
        return bC;
    }

    static int getBs()
    {
        return bS;
    }
    int getYear()
    {
        return year;
    }
    friend istream &operator>>(istream &is, Trud &t)
    {
        is >> t.c >> t.year;
    }

    static void setBc(int v)
    {
        bC = v;
    }

    static void setBs(int v)
    {
        bS = v;
    }
};

class Student {
protected:
    char name[30];
    int id;
    int y;
    int *list;
    int n;

public:
    Student(const char *name = "", int id = 0, int y = 0, int *list = 0, int n = 0) {
        strcpy(this->name, name);
        this->id = id;
        this->y = y;
        this->n = n;
        this->list = new int[n];
        for (int i = 0; i < n; i++) {
            this->list[i] = list[i];
        }
    }

    Student(const Student &s) {
        strcpy(this->name, s.name);
        this->id = s.id;
        this->y = s.y;
        this->n = s.n;
        this->list = new int[s.n];
        for (int i = 0; i < s.n; i++) {
            this->list[i] = s.list[i];
        }
    }

    Student &operator=(const Student &s) {
        if (this == &s) return *this;
        strcpy(this->name, s.name);
        this->id = s.id;
        this->y = s.y;
        this->n = s.n;
        delete[] list;
        this->list = new int[s.n];
        for (int i = 0; i < s.n; i++) {
            this->list[i] = s.list[i];
        }
        return *this;
    }

    ~Student() {
        delete[] list;
    }

    virtual float rang() {
        float avg = 0;
        for (int i = 0; i < n; i++) {
            avg += list[i];
        }
        return avg / n;
    }

    friend ostream &operator<<(ostream &os, Student &s) {
        os << s.id << " " << s.name << " " << s.y << " " << s.rang() << endl;
    }

    int getId()
    {
        return id;
    }

};

class PhDStudent : public Student {
private:
    Trud *tr;
    int tn;
public:
    PhDStudent(const char *name = "", int id = 0, int y = 0, int *list = 0, int n = 0, Trud *tr = 0, int tn = 0)
            : Student(name, id, y, list, n) {
        this->tn = tn;
        this->tr = new Trud[tn];
        for (int i = 0; i < tn; i++) {
            this->tr[i] = tr[i];
        }
    }

    PhDStudent(const PhDStudent &s) : Student(s) {
        strcpy(this->name, s.name);
        this->id = s.id;
        this->y = s.y;
        this->n = s.n;
        this->list = new int[s.n];
        for (int i = 0; i < s.n; i++) {
            this->list[i] = s.list[i];
        }

        this->tn = s.tn;
        this->tr = new Trud[s.tn];
        for (int i = 0; i < s.tn; i++) {
            this->tr[i] = s.tr[i];
        }

    }

    PhDStudent &operator=(const PhDStudent &s) {
        if (this == &s) return *this;
        strcpy(this->name, s.name);
        this->id = s.id;
        this->y = s.y;
        this->n = s.n;
        delete[] list;
        this->list = new int[s.n];
        for (int i = 0; i < s.n; i++) {
            this->list[i] = s.list[i];
        }

        this->tn = s.tn;
        delete[] tr;
        this->tr = new Trud[s.tn];
        for (int i = 0; i < s.tn; i++) {
            this->tr[i] = s.tr[i];
        }
        return *this;
    }

    ~PhDStudent() {
        delete[] tr;
    }
    float rang() override
    {
        float nr = Student::rang();
        for (int i = 0; i<tn; i++)
        {
            nr += (tr[i].getType() == 'C' || tr[i].getType() == 'c') ? tr[i].getBc() : tr[i].getBs();
        }
        return nr;
    }
    PhDStudent &operator+=(Trud &t)
    {
        for (int i = 0; i<tn; i++)
        {
            if (y > t.getYear())
            {
                throw Exception();
            }
        }
        Trud *temp = new Trud[tn+1];
        for (int i = 0; i<tn; i++)
        {
            temp[i] = tr[i];
        }
        temp[tn++] = t;
        delete [] tr;
        tr = temp;
        return *this;
    }
};

int Trud::bC = 1;
int Trud::bS = 3;

int main() {
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        int found = false;
        for (int i = 0; i < m; i++)
        {
            if (niza[i]->getId() == indeks)
            {
                try
                {
                    PhDStudent *phd = dynamic_cast<PhDStudent *>(niza[i]);
                    if (phd != 0)
                    {
                        found = true;
                        *phd+=t;
                    }
                } catch (Exception)
                {

                }
            }
        }

        if (found == false)
        {
            cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2

        for (int i = 0; i < m; i++)
        {
            if (niza[i]->getId() == indeks)
            {
                try
                {
                    PhDStudent *phd = dynamic_cast<PhDStudent *>(niza[i]);
                    if (phd != 0)
                        *phd+=t;
                } catch (Exception)
                {

                }
            }
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        PhDStudent phd(ime, indeks, god, oceni, n, trud, 0);
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            try
            {
                phd+=t;
            } catch (Exception e)
            {

            }
        }
        cout << phd;

    }
    if (testCase == 5) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot

        for (int i = 0; i < m; i++)
        {
            if (niza[i]->getId() == indeks)
            {
                try
                {
                    PhDStudent *phd = dynamic_cast<PhDStudent *>(niza[i]);
                    if (phd != 0)
                        *phd+=t;
                } catch (Exception)
                {

                }
            }
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        Trud::setBc(conf);
        Trud::setBs(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}