//Како успешен студент на ФИНКИ вие сте повикани да работите на подобрување на IKnow системот. Како дел од системот треба да се додаде нов дел кој ќе биде одговорен за обработување на дисциплински мерки, па како дел од тимот за развивање на софтверот ќе треба да ја имплементирате класата DisciplinaryAction која ќе ги чува следните информации:
//
//Името на студентот (динамички алоцирана низа од карактери)
//Индексот на студентот (int)
//Причината за дисциплинската мерка (динамички алоцирана низа од карактери)
//бројот на сесии во кои студентот нема право да полага (int)
//
//Класата треба да ги има следните методи и конструктори:
//
//Default конструктор
//Copy конструктор
//Конструктор со аргументи
//        Деструктор
//Set и Get методи за индексот
//Оператор =
//оператор << за печатење на информации за студентот
//        оператор ++ за зголемување на бројот на сесии во кои студентот е казнет (во префикс нотација)
//оператор >= за споредба на дисциплински постапки според бројот на сесии во кои студентот е казнет
//
//Операторот << треба да печати според следниот формат:
//Student: [Name]
//Student's index: [Index]
//Reason: [Reason]
//Sessions: [Sessions]
//
//
//При што вредностите во [] треба да се заменат со вредностите во класата!
//
//!!! ДА НЕ СЕ ПРАВАТ ПРОМЕНИ ВО MAIN() ФУНКЦИЈАТА !!!


#include <iostream>
#include <cstring>

using namespace std;

class DisciplinaryAction
{
private:
    char *name;
    int id;
    char *reason;
    int num;

public:
    DisciplinaryAction(char *name = "", int id = 0, char *reason ="", int num = 0)
    {
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);

        this->id = id;
        this->num = num;
        this->reason = new char[strlen(reason)+1];
        strcpy(this->reason, reason);
    }

    DisciplinaryAction(const DisciplinaryAction &dc)
    {
        this->name = new char[strlen(dc.name)+1];
        strcpy(this->name, dc.name);
        this->id = dc.id;
        this->num = dc.num;
        this->reason = new char[strlen(dc.reason)+1];
        strcpy(this->reason, dc.reason);
    }

    DisciplinaryAction &operator=(const DisciplinaryAction &dc)
    {
        if (this == &dc) return *this;
        delete [] name;
        delete [] reason;
        this->name = new char[strlen(dc.name)+1];
        strcpy(this->name, dc.name);
        this->id = dc.id;
        this->num = dc.num;
        this->reason = new char[strlen(dc.reason)+1];
        strcpy(this->reason, dc.reason);
        return *this;
    }

    int getId() const
    {
        return id;
    }
    void setIndex(int id)
    {
        this->id = id;
    }

    friend ostream &operator<<(ostream &os, const DisciplinaryAction &action) {
        os << "Student: " << action.name <<endl << "Student's index: " << action.id << endl <<"Reason: " << action.reason << endl << "Sessions: " << action.num<< endl;
        return os;
    }

    DisciplinaryAction operator++()
    {
        num++;
        return *this;
    }

    bool operator>=(const DisciplinaryAction &dc)
    {
        if (num >= dc.num)
        {
            return true;
        }
        return false;
    }

    ~DisciplinaryAction()
    {
        delete [] name;
        delete [] reason;
    }

};

int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for (int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;
        int sessions;

        cin >> name >> index >> reason >> sessions;

        arr[i] = DisciplinaryAction(name, index, reason, sessions);
    }

    cout << "-- Testing operator = & operator <<  --\n";
    cout << arr[0];

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    cout << arr[0];

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    cout << merka;

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for (int i = 0; i < n; i++)
        cout << arr[i];


    cout << "\nTesting operator ++ and <<" << endl;
    for (int i = 0; i < n; i++)
        cout << (++arr[i]);


    cout << "\nTesting operator >=" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << i << " " << ((arr[i] >= arr[j]) ? ">= " : "< ") << j << endl;
            }
        }
    }

    return 0;
}
