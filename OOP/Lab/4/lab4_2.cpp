//Да се дефинира класа Student за која се чува:
//name(низа од карактери, динамички алоцирана) - неговото име
//age (цел број) - колку години има
//        major (низа од карактери, динамички алоцирана) - што студира
//За класата да се дефинира default конструктор, конструктор со аргументи и copy конструктор.
//
//Потоа да се дефинира класа Classroom за која се чува:
//students (динамички алоцирана низа од Студенти)
//numStudents(int)
//capacity(int)
//За класата да се дефинира  default конструктор и конструктор со аргументи.
//
//Треба за класата Classroom да се дефинираат следните методи:
//add - да се додаде нов студент
//        remove - да се отстрани некој студент со дадено име name
//        findMedianAge - наоѓа која е медијаната за години на стидентите во дадениот Classroom.
//Пример: 2 4 5 6 7 8 10
//Медијана: 6
//
//Пример: 2 4 5 7 8 10 12 20
//Медијана: (7 + 8)/2
//
//Мора да е растечки редослед!
//
//По потреба може да се креираат get и set методи.
//
//Сите студенти имаат уникатно име.
//Да не се менува main функцијата.

//DO NOT CHANGE

#include <iostream>
#include <cstring>

using namespace std;

class Student {
private:
    char *name;
    int age;
    char *major;
public:
    //same
    Student(const char *name = "\0", int age = 0,const char *major = "\0") {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->name[strlen(name)] = '\0';
        this->age = age;
        this->major = new char[strlen(major) + 1];
        strcpy(this->major, major);
        this->major[strlen(major)] = '\0';

    }
//same
    Student(const Student &o) {
        this->name = new char[strlen(o.name) + 1];
        strcpy(this->name, o.name);
        this->age = o.age;
        this->major = new char[strlen(o.major) + 1];
        strcpy(this->major, o.major);

    }
    Student &operator=(const Student &o) {
        if (this != &o) {
            this->age = o.age;
            delete[] name;
            delete[] major;
            this->name = new char[strlen(o.name) + 1];
            strcpy(this->name, o.name);
            this->major = new char[strlen(o.major) + 1];
            strcpy(this->major, o.major);
            return *this;
        }
        return *this;

    }

    const char *getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    ~Student() {
        delete[] name;
        delete[] major;
    }

    void print() {
        cout << name << " " << "(" << age << ", " << major << ")" << endl;
    }
};

class Classroom {
private:
    Student *students;
    int numStudents;
    int capacity;
public:
    Classroom(Student *students = nullptr, int numStudents = 0, int capacity = 0) {
        this->numStudents = numStudents;
        this->students = new Student[numStudents];
        this->capacity = capacity;
        for (int i = 0; i < numStudents; i++) {
            this->students[i] = students[i];
        }
    }

    Classroom(const Classroom &c) {
        this->numStudents = c.numStudents;
        this->capacity = c.capacity;

        this->students = new Student[c.numStudents];
        for (int i = 0; i < numStudents; i++) {
            this->students[i] = c.students[i];
        }
    }

    Classroom &operator=(const Classroom &c) {
        if (this != &c) {
            delete[] students;
            students = new Student[c.numStudents];

            for (int i = 0; i < c.numStudents; i++) {
                students[i] = c.students[i];
            }
            this->numStudents = c.numStudents;
            this->capacity = c.capacity;
        }
        return *this;
    }

    void add(const Student &s) {
        Student *temp = new Student[numStudents + 1];
        for (int i = 0; i < numStudents; i++) {
            temp[i] = students[i];
        }

        delete[] students;
        students = temp;
        students[numStudents] = s;
        numStudents++;
    }

    void remove(char *name) {
        Student *temp = new Student[numStudents - 1];
        int newNum = 0;
        for (int i = 0; i < numStudents; i++) {
            if (strcmp(students[i].getName(), name) != 0) {

                temp[newNum] = students[i];
                newNum++;
            }
        }
        delete[] students;
        students = new Student[numStudents - 1];
        numStudents--;
        students = temp;
    }

    int getNumStudents() const {
        return numStudents;
    }

    Student getStudent(int r) {
        return students[r];
    }

    ~Classroom() {
        delete[] students;
    }

    void printStudents() {
        for (int i = 0; i < numStudents; i++) {
            students[i].print();
        }
    }

};

float findMedianAge(Classroom classroom) {
    int array[100];
    for (int i = 0; i < classroom.getNumStudents(); i++) {
        array[i] = classroom.getStudent(i).getAge();
    }

    for (int i = 0; i < classroom.getNumStudents(); i++) {
        int min = array[i];
        int swapid = i;
        for (int j = i + 1; j < classroom.getNumStudents(); j++) {
            if (min > array[j]) {
                swapid = j;
                min = array[j];
            }
        }
        if (swapid != i) {
            swap(array[i], array[swapid]);
        }
    }
    int ids = classroom.getNumStudents() - 1;
    if (ids % 2 == 0) // neparen n/2
    {
        return float(classroom.getStudent(ids / 2).getAge());
    } else //paren br na studenti n/2 + (n/2)+1
    {
        return float(classroom.getStudent(ids / 2).getAge() + classroom.getStudent(ids / 2 + 1).getAge()) / 2;
    }
}


int main() {
    int numClassrooms, numStudents;
    cin >> numClassrooms;
    Classroom classrooms[10];
    Student students[20];

    // Testing add method
    for (int i = 0; i < numClassrooms; i++) {
        cin >> numStudents;
        for (int j = 0; j < numStudents; j++) {
            char name[100], major[100];
            int age;
            cin >> name >> age >> major;
            Student student(name, age, major);
            classrooms[i].add(student);
            students[i * numStudents + j] = student;
        }
        cout << "Classroom " << i << endl;
        classrooms[i].printStudents();
    }


    // Testing findMedianAge method
    int targetClassroom;
    cin >> targetClassroom;
    double medianAge = findMedianAge(classrooms[targetClassroom]);
    cout << "The median age in classroom " << targetClassroom << " is: " << medianAge << endl;
    cout << "After removing the elements:" << endl; /// Added

    // Testing remove method
    cin >> numStudents;
    for (int j = 0; j < numStudents; j++) {
        char name[100];
        cin >> name;
        for (int i = 0; i < numClassrooms; i++) {
            classrooms[i].remove(name);
        }
    }

    for (int i = 0; i < numClassrooms; i++) {
        cout << "Classroom " << i << endl;
        classrooms[i].printStudents();
    }

    return 0;
}

