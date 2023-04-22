//Да се дефинира класа Ucesnik за учесник во маратон за кој ќе се чуваат информации за:
//
//име (динамички алоцирана низа од знаци)
//пол (bool)
//возраст (цел број) (5 поени).
//За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени)
//
//Дополнително за оваа класа да се преоптоварат:
//
//оператор за споредување > (споредува двајца учесници според возраста) (5 поени)
//операторот за проследување на излезен тек << кој ќе ги печати името, полот (машки/женски) и возраста, секој во посебен ред. (5 поени)
//Да се дефинира класа Maraton за кој се чуваат:
//
//локација (низа од максимум 100 знаци)
//низа од Ucesnik објекти (динмички алоцирана низа од објекти од класата Ucesnik)
//број на учесници (цел број) (5 поени).
//За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени) Исто така да се имплементираат следните методи:
//
//оператор += за додавање нов Ucesnik на маратонот Maraton. (10 поени)
//prosecnoVozrast() вреќа просечена возраст на учесниците на маратонот (5 поени)
//pecatiPomladi(Ucesnik &u) ги печати сите учесници помлади од учесникот проследен како аргумент на методот. (5 поени)

#include <iostream>
#include <cstring>

using namespace std;

class Ucesnik
{
private:
    char *name;
    bool gender;
    int age;
public:
    Ucesnik(char *name = "", bool gender = false, int age = 0)
    {
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
        this->gender = gender;
        this->age = age;
    }

    Ucesnik(const Ucesnik &u)
    {
        this->name = new char[strlen(u.name)+1];
        strcpy(this->name, u.name);
        this->gender = u.gender;
        this->age = u.age;
    }

    Ucesnik &operator=(const Ucesnik &u)
    {
        if (this == &u) return *this;
        delete [] name;
        this->name = new char[strlen(u.name)+1];
        strcpy(this->name, u.name);
        this->gender = u.gender;
        this->age = u.age;
        return *this;
    }

    int getAge() {
        return age;
    }

    bool operator>(const Ucesnik &u) const
    {
        if (age >= u.age)
        {
            return true;
        } else
        {
            return false;
        }
    }

    friend ostream &operator<<(ostream &out, const Ucesnik &u)
    {
            out<<u.name<<endl;
            if (u.gender == 0) out<< "zhenski";
            else out<<"mashki";
            out<<"\n"<<u.age<<endl;
    }
    ~Ucesnik()
    {
        delete [] name;
    }
};

class Maraton
{
private:
    char location[30];
    Ucesnik *ucesnici;
    int n;
public:
    Maraton(char *location = "", int n = 0, Ucesnik *ucesnici = nullptr)
    {
        strcpy(this->location, location);
        this->n = n;
        this->ucesnici = new Ucesnik[n];
        for (int i = 0; i<n; i++)
        {
            this->ucesnici[i] = ucesnici[i];
        }
    }

    Maraton(const Maraton &m)
    {
        strcpy(this->location, m.location);
        this->n = m.n;
        this->ucesnici = new Ucesnik[m.n];
        for (int i = 0; i<m.n; i++)
        {
            this->ucesnici[i] = m.ucesnici[i];
        }
    }


    Maraton &operator=(const Maraton &m)
    {
        if (this == &m) return *this;
        strcpy(this->location, m.location);
        this->n = m.n;
        delete [] ucesnici;
        this->ucesnici = new Ucesnik[m.n];
        for (int i = 0; i<m.n; i++)
        {
            this->ucesnici[i] = m.ucesnici[i];
        }
        return *this;
    }

    ~Maraton()
    {
        delete [] ucesnici;
    }

    Maraton &operator+=(const Ucesnik &u)
    {
        Ucesnik *temp = new Ucesnik[n+1];
        for (int i = 0; i < n; i++)
        {
            temp[i] = ucesnici[i];
        }
        temp[n++] = u;
        delete [] ucesnici;
        ucesnici = temp;
        return *this;
    }
    float prosecnoVozrast()
    {
        float avg = 0;
        for (int i = 0; i<n; i++)
        {
            avg+=(float) ucesnici[i].getAge();
        }
        return avg/n;
    }

    void pecatiPomladi(const Ucesnik &u)
    {
        for (int i = 0; i<n; i++)
        {
            if ((ucesnici[i]>u) == false)
            {
                cout<<ucesnici[i];
            }
        }
    }
};

int main() {char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}
