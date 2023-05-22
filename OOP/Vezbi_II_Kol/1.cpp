#include <iostream>
#include <cstring>

using namespace std;

class Book {
protected:
    char ISBN[20], title[50], author[30];
    double price;

public:
    Book(char *ISBN = "", char *title = "", char *author = "", double price = 0) {
        strcpy(this->ISBN, ISBN);
        strcpy(this->title, title);
        strcpy(this->author, author);
        this->price = price;
    }

    Book(const Book &b) {
        strcpy(this->ISBN, b.ISBN);
        strcpy(this->title, b.title);
        strcpy(this->author, b.author);
        this->price = b.price;
    }

    Book &operator=(const Book &b) {
        if (this == &b) return *this;
        strcpy(this->ISBN, b.ISBN);
        strcpy(this->title, b.title);
        strcpy(this->author, b.author);
        this->price = b.price;
        return *this;
    }

    virtual ~Book(){

    };

    virtual void setPrice(int p)=0;
    virtual void setISBN(char *ISBN)
    {
        strcpy(this->ISBN, ISBN);
    }
    virtual double bookPrice()
    {
        return price;
    }
    bool operator>(const Book &b)
    {
        if (price > b.price)
        {
            return true;
        }
        return false;
    }

    friend ostream &operator<<(ostream &os, const Book &book) {
        os << book.ISBN << ": " << book.title << ", " << book.author << " "
           << book.price<<endl;
        return os;
    }
};

class OnlineBook : public Book
{
private:
    int size;
    char *url;

public:

    OnlineBook(char *ISBN = "", char *title = "", char *author = "", double price = 0, char *url = "", int size = 0)
    : Book(ISBN, title, author, price)
    {
        this->url = new char[strlen(url)+1];
        strcpy(this->url, url);
        this->size = size;
        this->price = bookPrice();
    }

    OnlineBook(const OnlineBook &ob)
            : Book(ob)
    {
        this->url = new char[strlen(ob.url)+1];
        strcpy(this->url, ob.url);
        this->size = ob.size;
    }

    OnlineBook &operator=(const OnlineBook &ob)
    {
        if (this == &ob) return *this;
        strcpy(this->ISBN, ob.ISBN);
        strcpy(this->title, ob.title);
        strcpy(this->author, ob.author);
        this->price = ob.price;

        delete [] url;
        this->url = new char[strlen(ob.url)+1];
        strcpy(this->url, ob.url);
        this->size = ob.size;

        return *this;
    }

    void setPrice(int price)
    {
        this->price = price;
    }

    ~OnlineBook()
    {
        delete [] url;
    }

    double bookPrice()
    {
        if (size >= 20)
        {
            return price*1.2;
        }
        return price;
    }

    friend ostream &operator<<(ostream &os, OnlineBook &book) {
        os << book.ISBN << ": " << book.title << ", " << book.author << " "
           << book.price<<endl;
        return os;
    }
};

class PrintBook : public Book
{
private:
    double weight;
    bool isA;

public:
    PrintBook(char *ISBN = "", char *title = "", char *author = "", double price = 0, double weight = 0, bool isA = false)
    :Book(ISBN, title, author, price){
        this->weight = weight;
        this->isA = isA;
        this->price = bookPrice();
    }
    PrintBook(const PrintBook &pb)
            :Book(pb){
        this->weight = pb.weight;
        this->isA = pb.isA;
    }
    void setPrice(int price)
    {
        this->price = price;
    }

    double bookPrice()
    {
        if (weight >= 0.7)
        {
            return price*1.15;
        }
        return price;
    }

    friend ostream &operator<<(ostream &os, PrintBook &book) {
        os << book.ISBN << ": " << book.title << ", " << book.author << " "
           << book.price<<endl;
        return os;
    }
};

void mostExpensiveBook (Book** books, int n)
{
    cout<<"FINKI-Education"<<endl;
    double max = 0;
    int id = 0, co = 0, cp = 0;
    for (int i = 0; i<n; i++)
    {
        OnlineBook *prob = dynamic_cast<OnlineBook *>(books[i]);
        PrintBook *prpb = dynamic_cast<PrintBook *>(books[i]);
        if (prob != 0)
        {
            if (max < prob->bookPrice())
            {
                max = prob->bookPrice();
                id = i;
            }
            co++;
        } else
        {
            if (max < prpb->bookPrice())
            {
                max = prpb->bookPrice();
                id = i;
            }
            cp++;

        }
    }
    cout<<"Total number of online books: "<< co<<endl;
    cout<<"Total number of print books: "<<cp<<endl;
    cout<<"The most expensive book is: "<<endl;
    cout<<*books[id];
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
