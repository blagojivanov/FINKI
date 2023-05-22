//Да се напише класа Book во која се чуваат информации за името на книгата (динамички алоцирана низа од знаци), isbn на книгата (динамички алоцирана низа од 5 цели броја) и број на страници (цел број). За класата да се обезбедат set и get методите што се користат и да се преоптоварат следните оператори:
//
//оператор == за споредување на две книги според isbn-от
//
//        оператор << за печатење на податоци за книгата во формат Title: наслов ISBN:[x y z k l]
//
//Да се напише класа BorrowABook за библиотека за изнајмување книги  во која се чуваат информација за името на бибилиотеката (низа од 100 знци), низа од книги (динамички алоцирана низа од објекти од класата Book) и број на книги со кој располага (цел број). Во класата BorrowABook да се напише конструктор со еден аргумент за иницијализација на името на библиотеката. При секое додавање на нова книга во библиотеката, динамички алоцираната низа да го зголемува капацитетот за 1 елемент. Во оваа класа да се преоптоварат операторите:
//
//+= за додавање на нова книга во библиотеката и
//
//-= за отстранување на дадена книга од библиотеката (онаа со веќепостоечки ISBN кој се поклопува со ISBN-от на друга книга).
//
//На излез да се отпечатат името на библиотеката и листа на книги што таа ги изнајмува, а чиј број на страници е поголем од 150. Последново да се направи со функција printNumberOfPages(int max) што треба да се дефинира во класата BorrowABook.
//
//Појаснување на main функцијата: Информациите за книгите се читаат од тастатура со операторот +=. Во последниот ред од влезот дадени се информации за книгата која што се внесува грешно бидејќи има ист isbn како и друга книга. Потребно е истата да биде избришана.
//!!! ДА НЕ СЕ ПРАВАТ ПРОМЕНИ ВО MAIN() ФУНКЦИЈАТА !!!

/// Do NOT edit the main() function

#include <iostream>
#include <cstring>

using namespace std;

class Book
{
private:
    char *name;
    int *isbn;
    int pages;

public:
    Book(char *name = "", int *isbn = nullptr, int pages = 0)
    {
        this->name = new char[strlen(name) +1];
        strcpy(this->name, name);
        if (isbn != nullptr)
        {
            this->isbn = new int[5];
            for (int i = 0; i<5; i++)
            {
                this->isbn[i] = isbn[i];
            }
        } else
        {
            this->isbn = nullptr;
        }
        this->pages = pages;
    }

    Book(const Book &b)
    {
        this->name = new char[strlen(b.name) +1];
        strcpy(this->name, b.name);
        this->isbn = new int[5];
        for (int i = 0; i<5; i++)
        {
            this->isbn[i] = b.isbn[i];
        }
        pages = b.pages;
    }

    Book &operator=(const Book &b)
    {
        if (this == &b) return *this;
        delete [] name;
        delete [] isbn;
        this->name = new char[strlen(b.name) +1];
        strcpy(this->name, b.name);
        this->isbn = new int[5];
        for (int i = 0; i<5; i++)
        {
            this->isbn[i] = b.isbn[i];
        }
        pages = b.pages;
        return *this;
    }

    bool operator==(const Book &b)
    {
        for (int i = 0; i<5; i++)
        {
            if (isbn[i] != b.isbn[i])
            {
                return false;
            }
        }
        return true;
    }

        ~Book()
    {
        delete [] name;
        delete [] isbn;
    }

    int getPages()
    {
        return pages;
    }


};

class BorrowABook
{
private:
    char name[30];
    Book *books;
    int n;
public:
    BorrowABook(char *name = "")
    {
        strcpy(this->name, name);
        books = nullptr;
        n = 0;
    }

    BorrowABook(const BorrowABook &bb)
    {
        strcpy(this->name, bb.name);
        n = bb.n;
        books = new Book[n];
        for (int i = 0; i<n; i++)
        {
            books[i] = bb.books[i];
        }
    }

    BorrowABook &operator=(const BorrowABook &bb)
    {
        if (this == &bb) return *this;
        delete [] books;
        strcpy(this->name, bb.name);
        n = bb.n;
        books = new Book[n];
        for (int i = 0; i<n; i++)
        {
            books[i] = bb.books[i];
        }
        return *this;
    }

    BorrowABook operator+=(const Book &b)
    {
        Book *temp = new Book[n+1];
        for (int i = 0; i<n; i++)
        {
            temp[i] = books[i];
        }
        temp[n++] = b;
        delete [] books;
        books = temp;
        return *this;
    }


    BorrowABook operator-=(const Book &b)
    {
        bool f = false;
        for (int i = 0; i<n; i++)
        {
            if (books[i] == b)
            {
                f = true;
                break;
            }
        }
        if (f)
        {
            int nc=0;
            Book *temp = new Book[n-1];
            for (int i = 0; i<n; i++)
            {
                if (!(books[i] == b))
                    temp[nc++] = books[i];
            }
            n = nc;
            delete [] books;
            books = temp;
        }
        return *this;
    }
    void printNumberOfPages(int max)
    {
        cout<<name<<endl;
        for (int i = 0; i<n; i++)
        if (books[i].getPages() > max)
        {
            cout<<books[i];
        }
    }
    ~BorrowABook()
    {
        delete [] books;
    }
};

int main()
{
    BorrowABook library("FINKI-Library");
    int n;
    cin>>n;

    for (int i=0;i<n;i++)
    {
        char title[100];
        int isbn[5];
        int pages;

        cin>>title;

        for (int j=0;j<5;j++)
            cin>>isbn[j];

        cin>>pages;

        Book nov=Book(title,isbn,pages);

        //adding a new book
        library+=nov;

    }
    //the book which has the same isbn as some previous one
    char title[100];
    int isbn[5];
    int pages;
    cin>>title;
    for (int i=0;i<5;i++)
        cin>>isbn[i];
    cin>>pages;

    Book greshka=Book(title,isbn,pages);

    //deleting a book
    library-=greshka;

    library.printNumberOfPages(150);

    return 0;
}
