  //Да се дефинира класа Film во која ќе се чуваат информации за:
//name(низа од максимум 100 карактери) -име на филмот
//rating (децимален број) - рејтинг на филмот
//revenue(децимален број) - колку заработил филмот во милиони долари
//Сите променливи внатре во класата треба да бидат приватни. Соодветно во рамките на класата да се дефинираат:
//конструктор (без и со параметри)
//деструктор
//        set методи
//        get методи
//        Да се дефинираат следните методи во класата:
//display() која што ќе ги печати информациите за сметката во следниот формат:
//Name of film: …
//Rating: …
//Revenue: …
//Надвор од класата:
//printMostPopularFilm(Film *films, int n) која што ќе го најде филмот со најголема заработувачка,
//ДА НЕ СЕ МЕНУВА MAIN ФУНКЦИЈАТА.

#include <iostream>
#include <cstring>

using namespace std;

class Film {
private:
    char name[100];
    double rating;
    double revenue;

public:
    Film() {
        strcpy(this->name, "");
        this->rating = 0;
        this->revenue = 0;
    }

    Film(char *name, double rating, double revenue) {
        strcpy(this->name, name);
        this->rating = rating;
        this->revenue = revenue;
    }

    ~Film() {}

    void setName(char *name) {
        strcpy(this->name, name);
    }

    char *getName() {
        return name;
    }

    double getRating() {
        return rating;
    }

    void setRating(double rating) {
        this->rating = rating;
    }

    double getRevenue() {
        return revenue;
    }

    void setRevenue(double revenue) {
        this->revenue = revenue;
    }

    void display() {
        cout << "Name of film: " << name << endl;
        cout << "Rating: " << rating << endl;
        cout << "Revenue: " << revenue << endl;
    }
};

void printMostPopularFilm(Film *films, int n) {
    Film maxf = films[0];
    for (int i = 1; i < n; i++) {
        if (maxf.getRevenue() < films[i].getRevenue()) {
            maxf = films[i];
        }
    }

    maxf.display();
}


// DO NOT CHANGE THE MAIN FUNCTION
int main() {
    int n;
    cin >> n;
    Film films[100];

    char name[100];
    double rating;
    double revenue;

    for (int i = 0; i < n - 1; i++) {
        cin >> name;
        cin >> rating;
        cin >> revenue;

        // testing constructor with arguments
        films[i] = Film(name, rating, revenue);

    }


    // testing set methods and display for last element
    cin >> name;
    cin >> rating;
    cin >> revenue;
    films[n - 1].setName(name);
    films[n - 1].setRating(rating);
    films[n - 1].setRevenue(revenue);

    cout << "-->Testing set methods and display()" << endl;
    films[n - 1].display();
    cout << endl;

    cout << "-->Testing printMostPopularFilm()" << endl;
    printMostPopularFilm(films, n);
    return 0;
}
