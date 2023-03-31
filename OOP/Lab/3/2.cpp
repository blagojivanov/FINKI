//Да се дефинира класа Subject  за која се чува:
//име (низа од карактери)
//број на кредити (цел број)
//За класата да се дефинира default конструктор, конструктор со аргументи и copy конструктор.
//
//Потоа да се дефинира класа Student за која се чува:
//име (низа од карактери)
//презиме (низа од карактери)
//индекс (низа од карактери)
//5 предмети што ги слуша (низа од објекти од класата Subject)
//метод total() што ќе го пресметува вкупниот број на кредити што ќе ги има студентот откако ќе ги положи предметите
//метод display() кој што ќе испечати информации во формат:
//Име презиме -> индекс -> кредити
//        За класата да се дефинира  default конструктор и конструктор со аргументи.
//
//По потреба може да се креираат get и set методи.
//
//Да не се менува main функцијата.

#include <iostream>
#include <cstring>

using namespace std;

class Subject
{
private:
    char name[30];
    int ects;

public:
    Subject()
    {
        strcpy(this->name, "");
        this->ects = 0;
    }

    Subject(char *name, int ects)
    {
        strcpy(this->name, name);
        this->ects = ects;
    }

    Subject(const Subject &sb)
    {
        strcpy(this->name, sb.name);
        this->ects = sb.ects;
    }

    int getEcts()
    {
        return ects;
    }
};

class  Student
{
private:
    char name[30];
    char surname [30];
    char id[10];
    Subject subjects[5];

public:

    Student()
    {
        strcpy(this->name, "");
        strcpy(this->surname, "");
        strcpy(this->id, "");
    }
    Student(char *name, char *surname, char *id, Subject *subjects)
    {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        strcpy(this->id, id);
        for (int i = 0; i < 5; ++i) {
            this->subjects[i] = subjects[i];
        }
    }

    int total()
    {
        int t = 0;
        for(auto e : subjects) {
            t+=e.getEcts();
        }
        return t;
    }

    void display()
    {
        cout<<name<<" "<<surname<<" -> "<<id<<" -> "<<total();
    }
};

//DO NOT CHANGE THE MAIN FUNCTION
int main()
{
    char stName[100], stSurname[100], stIndex[100];
    cin>>stName>>stSurname>>stIndex;
    //Testing default constructor for Subject
    Subject subjects[5];
    for(int i=0; i<5; i++)
    {
        char sbName[100];
        int c;
        cin>>sbName>>c;
        //Testing constructor with arguments for Subject
        subjects[i]=Subject(sbName, c);
    }
    //Testing default constructor for Student
    Student student;
    //Testing constructor with arguments for Student and copy constructor for Subject
    student=Student(stName, stSurname, stIndex, subjects);
    //Testing display() and total() methods
    student.display();
    return 0;
}
