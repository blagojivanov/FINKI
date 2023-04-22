//За да се овозможи прецизна контрола и евиденција за состојбата на книгите во една библиотека, потребно е да се имплементира модул со следниве класи и функционалности:
//
//Да се имплементира класа Book во која ќе се чуваат информации за:
//
//ISBN (низа од најмногу 13 знаци)
//Наслов (динамички алоцирана низа од знаци)
//Издавачка куќа (низа од најмногу 20 знаци)
//Состојба (една книга може да се најде во состојба НЕИЗНАЈМЕНА, СЕ_РЕПАРИРА или ИЗНАЈМЕНА)
//Вкупен број на изнајмувања (цел број)
//За класата да се имплементираат потребните конструктори, оператор = и методи за да функционира решението. (10 поени). Дополнително за класата да се имплементира метод void print() за печатење на информациите за книгата (според тест примерите). (5 поени)
//
//Да се имплементира класа BookService во која ќе се чуваат информации за:
//
//Име на библиотека каде се наоѓа сервисот (низа од најмногу 20 знаци)
//Листа на книги кои моментално се наоѓаат во сервисот (динимички алоцирана низа од објекти од класата Book, иницијално без елементи)
//Број на книги во сервисот (број на елементи во низата со книги - цел број, иницијално е 0)
//За класата да се имплементираат потребните конструктори и методи со цел да функционира решението. (5 поени) Дополнително во класата да се имплементираат:
//
//метод void addBook (Book book) - за додавање нoва книга во сервисот (5 поени). Една книга може да се додаде во сервисот само ако се наоѓа во состојба НЕИЗНАЈМЕНА. Дополнително, ако веќе во сервисот има книга со иста издавачка куќа како книгата која сакаме да ја додадеме, потребно е во сервисот да остане книгата со поголем број на изнајмувања. Кога книгата се додава во сервисот нејзината состојба преминува во состојба СЕ_РЕПАРИРА (10 поени).
//метод Book repairNewestBook() - за репарирање на најновата книга. За најнова книга се смета онаа книга од листата која има најмал број на изнајмувања. Репарирањето на една книга означува:
//
//Потребно е книгата да биде избришана од листата со книги во сервисот
//Книгата треба да премине од состојба СЕ_РЕПАРИРА во состојба НЕИЗНАЈМЕНА
//Доколку има повеќе книги со ист број на изнајмувања при одредувањето на најнова книга, тогаш потребно е да се избрише книгата чија што издавачка куќа е всушност библиотеката каде што се наоѓа сервисот. Во ваква ситуација, секогаш само една од книгите ќе има издавачка книга иста со библиотеката на сервисот. (15 поени)
//метод void print() - за печатење на информации за сите книги кои моментално се наоѓаат на репарирање во сервисот (формат во тест примери) (10 поени)

#include <iostream>
#include <cstring>

using namespace std;

enum Sostojba {
    NEIZNAJMENA, SE_REPARIRA, IZNAJMENA
};

class Book {
private:
    char ISBN[13];
    char *title;
    char publishing_house[20];
    Sostojba state;
    int rents;

public:
//    Book a(ISBN, title, publishing_house, total_rents, state);

    Book(char *ISBN = "", char *title = "", char *publishing_house = "", int rents = 0, int state = (Sostojba) 0) {
        strcpy(this->ISBN, ISBN);
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
        strcpy(this->publishing_house, publishing_house);
        this->rents = rents;
        this->state = (Sostojba) state;
    }

    Book(const Book &b) {
        strcpy(this->ISBN, b.ISBN);
        this->title = new char[strlen(b.title) + 1];
        strcpy(this->title, b.title);
        strcpy(this->publishing_house, b.publishing_house);
        this->rents = b.rents;
        this->state = b.state;
    }

    Book &operator=(const Book &b) {
        if (this == &b) return *this;
        strcpy(this->ISBN, b.ISBN);

        delete[] title;

        this->title = new char[strlen(b.title) + 1];
        strcpy(this->title, b.title);
        strcpy(this->publishing_house, b.publishing_house);
        this->rents = b.rents;
        this->state = b.state;
        return *this;
    }

    ~Book() {
        delete[] title;
    }

    void print() {
        cout << "ISBN: " << ISBN << " - ";
        if (state == SE_REPARIRA) cout << "REPAIRING";
        else if (state == IZNAJMENA) cout << "RENTED";
        else if (state == NEIZNAJMENA) cout << "AVAILABLE";
        cout << " " << title << ", " << rents << ", " << publishing_house << endl;
    }

    Sostojba getState() const {
        return state;
    }

    const char *getPublishingHouse() const {
        return publishing_house;
    }

    int getRents() const {
        return rents;

    }

    void setState(Sostojba s) {
        state = s;
    }

};

class BookService {
private:
    char name[20];
    Book *books;
    int n;

public:
    BookService(char *name = "", Book *books = nullptr, int n = 0) {
        strcpy(this->name, name);
        this->books = nullptr;
        this->n = n;
    }

    BookService(const BookService &bs) {
        strcpy(this->name, bs.name);
        this->n = bs.n;
        this->books = new Book[bs.n];
        for (int i = 0; i < n; i++) {
            books[i] = bs.books[i];
        }
    }

    BookService &operator=(const BookService &bs) {
        if (this == &bs) return *this;
        strcpy(this->name, bs.name);
        this->n = bs.n;
        delete[] books;
        this->books = new Book[bs.n];
        for (int i = 0; i < n; i++) {
            books[i] = bs.books[i];
        }
        return *this;
    }

    ~BookService() {
        delete[] books;
    }

    void addBook(Book &book) {
        bool bta = false;
        if ((Sostojba) book.getState() == NEIZNAJMENA) {
            for (int i = 0; i < n; i++) {
                if (strcmp(book.getPublishingHouse(), books[i].getPublishingHouse()) == 0) {
                    if (book.getRents() > books[i].getRents()) {
                        book.setState(SE_REPARIRA);
                        books[i] = book;
                        return;
                    }
                } else
                {
                    bta = true;
                }
            }
        }
        if (bta || n == 0) {
            Book *temp = new Book[n + 1];
            for (int i = 0; i < n; i++) {
                temp[i] = books[i];
            }
            book.setState((Sostojba) SE_REPARIRA);
            temp[n++] = book;
            delete[] books;
            books = temp;
        }
    }

    Book repairNewestBook() {
        Book min = books[0];
        int bloc = 0;
        for (int i = 0; i < n; i++) {
            if (min.getRents() > books[i].getRents()) {
                min = books[i];
                bloc = i;
            } else if (min.getRents() == books[i].getRents())
            {
                if (strncmp(books[i].getPublishingHouse(), name, 20) == 0)
                {
                    min = books[i];
                    bloc = i;
                }
            }
        }
        min.setState(NEIZNAJMENA);

        int nc =0;
        Book *temp = new Book[n-1];
        for (int i = 0; i<n; i++)
        {
            if (bloc == i)
            {
                continue;
            }
            temp[nc++] = books[i];
        }
        books = temp;
        n = nc;
        return min;
    }

    void print() {
        cout << name << endl;
        for (int i = 0; i < n; i++) {
            books[i].print();
        }
    }

};


//your code here

int main() {
    int testCase;
    cin >> testCase;
    char ISBN[13];
    char title[20];
    char publishing_house[20];
    int total_rents;
    int state;
    if (testCase == 1) {
        cout << "TESTING CONSTRUCTOR FOR BOOK" << endl;
        Book a;
        cout << "TEST FOR DEFAULT CONSTRUCTOR PASSED" << endl;
        Book a1("966-13-43-72", "FINKI-ONWD", "FINKI", 25);
        cout << "TEST FOR CONSTRUCTOR WITH 3 ARGUMENTS PASSED" << endl;
        Book a2("966-13-43-11", "FINKI-OOP", "FINKI", 20, 0);
        cout << "TEST FOR CONSTRUCTOR WITH 4 ARGUMENTS PASSED" << endl;
    } else if (testCase == 2) {
        cout << "TESTING COPY-CONSTRUCTOR AND OPERATOR = (ASSIGNMENT) FOR BOOK" << endl;
        Book a("966-13-43-11", "FINKI-OOP", "FINKI", 20, 0);
        Book a1(a);
        cout << "TEST FOR COPY CONSTRUCTOR PASSED" << endl;
        Book a2;
        a2 = a;
        cout << "TEST FOR OPERATOR = (ASSIGNMENT) PASSED" << endl;
    } else if (testCase == 3) {
        cout << "TESTING PRINT() FOR BOOK" << endl;
        cin >> ISBN >> title >> publishing_house >> total_rents >> state;
        Book a(ISBN, title, publishing_house, total_rents, state);
        a.print();
    } else if (testCase == 4) {
        cout << "TESTING CONSTRUCTOR FOR BOOKSERVICE" << endl;
        BookService as("FINKI");
        cout << "TEST PASSED" << endl;
    } else if (testCase == 5) {
        cout << "TESTING ADD() AND PRINT() FOR BOOKSERVICE" << endl;
        BookService as("FINKI");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ISBN >> title >> publishing_house >> total_rents >> state;
            Book a(ISBN, title, publishing_house, total_rents, state);
            as.addBook(a);
        }
        as.print();
    } else if (testCase == 6) {
        cout << "TESTING repairNewestBook() AND PRINT() FOR BOOKSERVICE" << endl;
        BookService as("FINKI");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ISBN >> title >> publishing_house >> total_rents >> state;
            Book a(ISBN, title, publishing_house, total_rents, state);
            as.addBook(a);
        }
        Book p = as.repairNewestBook();
        cout << "Repaired book:" << endl;
        p.print();
        cout << "-----------------" << endl;
        as.print();
    } else if (testCase == 7) {
        cout << "TESTING COPY CONSTRUCTOR AND OPERATOR = FOR BOOKSERVICE" << endl;
        BookService as("FINKI");
        Book a2("966-13-43-11", "FINKI-OOP", "FINKI", 20, 0);
        as.addBook(a2);

        BookService s1 = as; //copy constructor
        BookService s2;
        s2 = s1; //operator =
        s1.print();
        s2.print();
    }
    return 0;
}
