//Да се имплементира класа Employee за која се чува:
//име (низа од карактери)
//години (цел број)
//Во класата да се имплементира виртуелна функција displayInfo() која на екран печати информации за вработениот.
//
//Потоа да се имплементира класа Payable за која се чува:
//
//плата (децимален број)
//За класата да се креира чисто виртуелна функција calculateSalary()
//
//Од овие класи потребно е да се изведат Developer и Manager.
//
//За класата Developer дополнително се чува и програмскиот јазик (низа од карактери). Потребно е да се препокријат соодветните функции. Платата се пресметува така што од основната плата се одзема данок од 10%.
//
//За класата Manager дополнително се чува и број на оддели за кои е одговорен. Потребно е да се препокријат соодветните функции. Платата се пресметува така што на основната плата се додава бонус од 5% за секој еден оддел.
#include <iostream>
#include <cstring>

using namespace std;

class Employee
{
protected:
    char name[50];
    int age;

public:
    Employee(const char *name = "", int age = 0) : age(age) {
        strcpy(this->name, name);
    }

    Employee(const Employee &e) : age(e.age) {
        strcpy(this->name, e.name);
    }

    Employee &operator=(const Employee &e){
        if (this == &e) return *this;
        age = e.age;
        strcpy(this->name, e.name);
        return *this;
    }

    virtual void displayInfo()=0;

};

class Payable
{
protected:
    double salary;

public:
    Payable(double salary = 0) : salary(salary){}
    virtual double calculateSalary()=0;
};

class Developer : public Employee, public Payable
{
private:
    char programmingLanguage[50];
public:
    Developer(const char *name = "", int age = 0,double salary = 0, char *programmingLanguage = "") : Employee(name, age){
        this->salary = salary;
        strcpy(this->programmingLanguage, programmingLanguage);
    }

    Developer(const Developer &d) : Employee(d)
    {
        this->salary = d.salary;
        strcpy(this->programmingLanguage, d.programmingLanguage);
    }

    Developer &operator=(const Developer &d)
    {
        if (this == &d) return *this;
        strcpy(this->programmingLanguage, d.programmingLanguage);
        strcpy(this->name, d.name);
        this->salary = d.salary;
        this->age = d.age;
        return *this;
    }
    double calculateSalary() override
    {
        return salary*0.9;
    }
    void displayInfo()
    {
        cout<<"-- Developer Information --"<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Salary: $"<<calculateSalary()<<endl;
        cout<<"Programming Language: "<<programmingLanguage<<endl;
    }
};

class Manager : public Employee, public Payable
{
private:
    int num;

public:
    Manager(const char *name = "", int age = 0, double salary = 0, int num = 0) : Employee(name, age), Payable(salary), num(num){}
    Manager(const Manager &m) : Employee(m), Payable(m.salary), num(m.num){}
    Manager &operator=(const Manager &m)
    {
        if (this == &m) return *this;
        strcpy(name, m.name);
        age = m.age;
        salary = m.salary;
        num = m.num;
        return *this;
    }

    double calculateSalary() override
    {
        return salary + salary*0.05*num;
    }

    void displayInfo()
    {
        cout<<"-- Manager Information --"<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Salary: $"<<calculateSalary()<<endl;
        cout<<"Number of Departments: "<<num<<endl;
    }
};

double biggestSalary(Payable* payable[], int n) {
    Payable* maxSalaryEmployee = payable[0];

    for (int i = 1; i < n; i++) {
        if (payable[i]->calculateSalary() > maxSalaryEmployee->calculateSalary()) {
            maxSalaryEmployee = payable[i];
        }
    }

    return maxSalaryEmployee->calculateSalary();
}

int main()
{
    Payable* payable[5];
    Developer developers[5];
    Manager managers[5];
    int j=0, k=0;
    for(int i=0; i<5; i++)
    {
        char name[50];
        int age;
        double salary;
        cin>>name>>age>>salary;
        if(i%2==0)
        {
            char programmingLanguage[50];
            cin>>programmingLanguage;
            developers[j]=Developer(name, age, salary, programmingLanguage);
            developers[j].displayInfo();
            payable[i]=&developers[j];
            j++;
        }
        else {
            int numberOfDepartments;
            cin>>numberOfDepartments;
            managers[k]=Manager(name, age, salary, numberOfDepartments);
            managers[k].displayInfo();
            payable[i]=&managers[k];
            k++;
        }
    }
    cout<<endl<<"Biggest Salary: "<<biggestSalary(payable, 5);
    return 0;
}
