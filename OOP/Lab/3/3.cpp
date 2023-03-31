//Да се дефинира класа Employee во која ќе се чуваат информации за:
//
//name(низа од максимум 100 карактери) -име на вработениот
//
//        surname(низа од максимум 100 карактери) - презиме
//
//salary(цел број) - колку му е платата
//
//методи кои што класата треба да ги има:
//
//print()
//
//-Принта во формат:
//Employee name:
//
//Employee surname:
//
//Employee salary:
//
//Да се дефинира класа TechCompany во која ќе се чуваат информации за:
//
//name(низа од максимум 100 карактери) -име на фирмата
//
//        employees(низа од вработени)
//
//numOfEmployees(цел број) - колку вработени има во фирмата
//
//        методи кои што класата треба да ги има:
//
//print()
//
//-Принта во формат:
//Tech company name:
//
//Number of employees:
//
//double getAverageOfEmployeeсSalary()
//
//-Враќа средна врендност од платите на секој вработен во таа фирма
//
//
//        Сите променливи внатре во класите треба да бидат приватни. Соодветно во рамките на класите да се дефинираат:
//
//конструктор (без и со параметри)
//
//деструктор
//
//        set методи
//
//        get методи
//
//        copy constructor
//
//        Функции надвор од класата:
//
//printCompanyWithHighestAverageSalary(TechCompany companies[], int numCompanies)
//
//-Го враќа TechCompany објектот што има најголема средна вредност за плати на неговите вработени
//printCompanyWithHighestStdSalary(TechCompany companies[], int numCompanies)
//
//-Го враќа TechCompany објектот што има најголема стандардна девијација за плати на неговите вработени
//-Помош: AVG е средната вредност на платите на сите вработен во таа фирма, STD е стандардна девијација, VAR  е помошна променлива. И прво квадрирајте го изразот па потоа додадете го во сумата!
//isSameCompany(TechCompany company1, TechCompany company2)
//
//-Враќа boolean вредност: две фирми се исти ако имаат исто име. Треба само да се првери дали им е исто името!
//ДА НЕ СЕ МЕНУВА MAIN ФУНКЦИЈАТА.

#include <iostream>
#include <cstring>
#include <cmath>


using namespace std;

class Employee
{
private:
    char name[100];
    char surname[100];
    int salary;
public:
    Employee()
    {
        strcpy(this->name, "");
        strcpy(this->surname, "");
        salary = 0;
    }

    Employee(char *name, char *surname, int salary)
    {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->salary = salary;
    }

    Employee(const Employee &e)
    {
        strcpy(this->name, e.name);
        strcpy(this->surname, e.surname);
        this->salary = e.salary;
    }

    void printEmployee()
    {
        cout<<"Employee name: "<<name<<endl;
        cout<<"Employee surname: "<<surname<<endl;
        cout<<"Employee salary: "<<salary<<endl;
    }

    int getSalary() {
        return salary;
    }

    ~Employee()
    {

    }
};

class TechCompany
{
private:
    char name[100];
    Employee employees[20];
    int numOfEmployees;

public:
    TechCompany()
    {
        strcpy(this->name, "");
        numOfEmployees = 0;
    }
    TechCompany(char *name)
    {
        strcpy(this->name, name);
        numOfEmployees =0;
    }

    ~TechCompany()
    {

    }

    void addEmployee(Employee e)
    {
        employees[numOfEmployees] = e;
        numOfEmployees++;
    }

    void setName(char *name)
    {
        strcpy(this->name, name);
    }

    const char *getName() {
        return name;
    }

    int getNumEmployees()
    {
        return numOfEmployees;
    }

    Employee getEmployee(int id)
    {
        return employees[id];
    }

};

bool isSameCompany(TechCompany company1, TechCompany company2)
{
    if (strcmp(company1.getName(), company2.getName()) == 0)
    {
        return true;
    }
    return false;
}


TechCompany printCompanyWithHighestAverageSalary(TechCompany companies[], int numCompanies)
{
    int avg, maxavg = 0;
    TechCompany maxT = companies[0];
    for (int i = 0; i<numCompanies; i++)
    {
        avg = 0;
        for (int j = 0; j<companies[i].getNumEmployees(); j++)
        {
            avg+=companies[i].getEmployee(j).getSalary();
        }
        avg/=companies[i].getNumEmployees();

        if (maxavg < avg)
        {
            maxavg = avg;
            maxT = companies[i];
        }

    }

    return maxT;
}

TechCompany printCompanyWithHighestStdSalary(TechCompany companies[], int numCompanies)
{
    TechCompany maxT = companies[0];
    double maxStd = 0;
    for (int i = 0; i<numCompanies; i++)
    {
        double avg = 0;
        for (int j = 0; j<companies[i].getNumEmployees(); j++)
        {
            avg+=companies[i].getEmployee(j).getSalary();
        }
        avg/=companies[i].getNumEmployees();

        double var = 0;

        for (int j = 0; j<companies[i].getNumEmployees();j++)
        {
            var += pow(companies[i].getEmployee(j).getSalary() - avg,2);
        }
        var/=(companies[i].getNumEmployees()-1);
        double std = sqrt(var);

        if (maxStd < std)
        {
            maxStd = std;
            maxT = companies[i];
        }
    }
    return maxT;
}

int main() {
    const int MAX_COMPANIES = 10;
    const int MAX_EMPLOYEES = 20;

    TechCompany companies[MAX_COMPANIES];

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        char name[100];
        std::cin >> name;

        TechCompany company(name);

        int m;
        std::cin >> m;

        for (int j = 0; j < m; j++) {
            char name[100];
            char surname[100];
            int salary;

            std::cin >> name;

            std::cin >> surname;

            std::cin >> salary;

            Employee employee(name, surname, salary);

            company.addEmployee(employee);
        }

        companies[i] = company;
    }

    TechCompany copy = companies[0];

    std::cout<<"-->Testing get and set methods for one object and copy constructor"<<std::endl;
    copy.setName("copy");
    std::cout << copy.getName() << std::endl;


    std::cout<<"-->Testing addEmployee function"<<std::endl;
    Employee newEmployee("John", "Doe", 5000);
    copy.addEmployee(newEmployee);
    std::cout << "Number of employees in copy: " << copy.getNumEmployees() << std::endl;


    std::cout<<"-->Testing copy of first employee"<<std::endl;
    Employee firstEmployee = copy.getEmployee(0);
    firstEmployee.printEmployee();


    std::cout<<"-->Testing methods"<<std::endl;
    TechCompany t = printCompanyWithHighestAverageSalary(companies, n);
    TechCompany t1 = printCompanyWithHighestStdSalary(companies, n);

    std::cout << "Tech company with the highest average salary: " << t.getName() << std::endl;
    std::cout << "Tech company with the highest standard deviation for salaries: " <<t1.getName() << std::endl;

    if (isSameCompany(t, t1)){
        std::cout<<"The tech company: "<<t.getName()<<" has the highest standard deviation and highest average salary"<<std::endl;
    }
    return 0;
}
