//Да се имплементира класа List во којашто ќе се чуваат информации за:
//броеви што се дел од листата (динамички алоцирана низа од цели броеви)
//бројот на броеви што се дел од листата
//За класата да се дефинираат следните методи:
//
//конструктор (со аргументи), copy-конструктор, деструктор, оператор =
//void pecati()метод што ќе ги печати информациите за листата во форматот: [број на елементи во листата]: x1 x2 .. xn sum: [сума] average: [просек]
//int sum() метод што ја враќа сумата на елементите во листата
//double average() метод што ќе го враќа просекот на броевите во листата
//Дополнително, креирајте класата ListContainer, во која што ќе се чуваат информации за:
//
//низа од листи (динамички алоцирана низа од објекти од класата List)
//број на елементи во низата од листи (цел број)
//број на обиди за додавање на листа во контејнерот (цел број првично поставен на нула)
//За класата потребно е да ги дефинирате следните методи:
//
//конструктор (default), copy-конструктор, деструктор, оператор =
//void pecati() метод што ќе ги печати информациите за контејнерот во форматот: List number: [реден број на листата] List info: [испечатени информации за листата со методот List::pecati()] \n sum: [сума] average: [просек]
//доколку контејнерот е празен се печати само порака The list is empty.
//void addNewList(List l) метод со којшто се додава листа во контејнерот
//Напомена: една листа се додава во контејнерот ако и само ако има различна сума од сите листи што се веќе додадени во контејнерот
//int sum() метод што ја враќа сумата на сите елементи во сите листи
//double average() метод што го враќа просекот на сите елементи во сите листи во контејнерот
#include <iostream>
using namespace std;

class List
{
private:
    int *arr;
    int n;

public:
    List(int *arr = nullptr, int n = 0)
    {
        this->n = n;
        this->arr = new int[n];
        for (int i = 0; i<n; i++)
        {
            this->arr[i] = arr[i];
        }
    }
    List (const List &l)
    {
        this->n = l.n;
        this->arr = new int[l.n];
        for (int i = 0; i<l.n; i++)
        {
            this->arr[i] = l.arr[i];
        }
    }
    List &operator=(const List &l)
    {
        if (this == &l) return *this;
        this->n = l.n;
        delete [] arr;
        this->arr = new int[l.n];
        for (int i = 0; i<l.n; i++)
        {
            this->arr[i] = l.arr[i];
        }

        return *this;
    }

    ~List()
    {
        delete [] arr;
    }

    int sum()
    {
        int s = 0;
        for (int i = 0; i<n; i++)
        {
            s+=arr[i];
        }
        return s;
    }

    double average()
    {
        return ((double)sum()/n);
    }

    void pecati()
    {
        cout<<n<<": ";
        for (int i = 0; i<n; i++)
        {
            cout<<arr[i]<<" ";
        }
        cout<<"sum: "<<sum()<<" average: "<<average();
    }
    int getEl()
    {
        return n;
    }
};

class ListContainer
{
private:
    List *lists;
    int n;
    int attempts = 0;
    int fattempts = 0;

public:
    ListContainer(List *lists = nullptr, int n = 0, int attempts = 0, int fattempts=0)
    {
        this->n = n;
        this->attempts = attempts;
        this->fattempts = fattempts;
        this->lists = new List[n];
        for (int i = 0; i<n; i++)
        {
            this->lists[i] = lists[i];
        }
    }
    ListContainer(const ListContainer &lc)
    {
        this->n = lc.n;
        this->attempts = lc.attempts;
        this->fattempts = lc.fattempts;
        this->lists = new List[lc.n];
        for (int i = 0; i<n; i++)
        {
            this->lists[i] = lc.lists[i];
        }
    }

    ListContainer &operator=(const ListContainer &lc)
    {
        if (this == &lc) return *this;
        this->n = lc.n;
        this->attempts = lc.attempts;
        this->fattempts = lc.fattempts;

        delete [] lists;

        this->lists = new List[lc.n];
        for (int i = 0; i<n; i++)
        {
            this->lists[i] = lc.lists[i];
        }
        return *this;
    }

    ~ListContainer()
    {
        delete [] lists;
    }

    int sum()
    {
        int sums = 0;
        for (int i = 0; i<n; i++)
        {
            sums+=lists[i].sum();
        }
        return sums;
    }

    double average()
    {
        double avg = 0;
        int sumofelements = 0;
        for (int i = 0; i<n; i++)
        {
            avg+=lists[i].sum();
            sumofelements += lists[i].getEl();
        }

        return avg/sumofelements;
    }

    void print()
    {
        if (n == 0)
        {
            cout<<"The list is empty"<<endl;
            return;
        }
        for (int i = 0; i<n; i++)
        {
            cout<<"List number: "<<i+1<<" List info: ";
            lists[i].pecati();
            cout<<endl;
        }
        cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
        cout<<"Successful attempts: "<<attempts<<" Failed attempts: "<<fattempts<<endl;

    }

    void addNewList(List l)
    {
        bool same = false;
        for (int i = 0; i<n; i++)
        {
            if (l.sum() == lists[i].sum())
            {
                fattempts++;
                same = true;
                break;
            }
        }
        if (!same)
        {
            attempts++;
            List *temp = new List[n+1];
            for (int i = 0; i<n; i++)
            {
                temp[i] = lists[i];
            }
            temp[n++] = l;
            lists = temp;
        }
    }

};

int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}