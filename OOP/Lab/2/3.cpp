 //Да се дефинира класа Country во која ќе се чуваат информации за:
//name(низа од максимум 100 карактери) име на државата
//        capital(низа од максимум 100 карактери) главен град
//area(децимален број) - површина во илјада km2
//population(децимален број) - популација во милиони.
//Сите променливи внатре во класата треба да бидат приватни. Соодветно во рамките на класата да се дефинираат:
//конструктор (без и со параметри)
//деструктор
//        set методи
//        get методи
//        Да се дефинираат следните методи во класата:
//display() која што ќе ги печати информациите за сметката во следниот формат:
//Country: Guyana
//        Capital: Georgetown
//        Area: 214
//Population: 0.8
//Надвор од класата:
//sortCountries(Country *countries, int n) која што ќе ги сортира државите растечки по нивната површина.
//ДА НЕ СЕ МЕНУВА MAIN ФУНКЦИЈАТА.

#include <iostream>
#include <cstring>

using namespace std;

class Country {
private:
    char name[100];
    char capital[100];
    float area, population;
public:
    Country() {
        strcpy(this->name, "");
        strcpy(this->capital, "");
        this->area = 0;
        this->population = 0;
    }

    Country(char *name, char *capital, float area = 0, float population = 0) {
        strcpy(this->name, name);
        strcpy(this->capital, capital);
        this->area = area;
        this->population = population;
    }

    ~Country() {}

    void setName(char *n) {
        strcpy(name, n);
    }

    void setCapital(char *c) {
        strcpy(capital, c);
    }

    void setArea(float a) {
        area = a;
    }

    void setPopulation(float pop) {
        population = pop;
    }

    float getPopulation() {
        return population;
    }

    float getArea() {
        return area;
    }

    void display() {
        cout << "Country: " << name << endl;
        cout << "Capital: " << capital << endl;
        cout << "Area: " << area << endl;
        cout << "Population: " << population << endl;
    }
};


void sortCountries(Country *countries, int n) {
    for (int i = 0; i < n; i++) {
        Country currMin = countries[i];
        int currId = i;
        for (int j = i + 1; j < n; j++) {
            if (currMin.getArea() > countries[j].getArea()) {
                currMin = countries[j];
                currId = j;
            }
        }

        if (i != currId) {
            swap(countries[i], countries[currId]);
        }
    }

    for (int i = 0; i < n; i++) {
        countries[i].display();
    }

}

int main() {
    int n;
    cin >> n;
    Country countries[100];

    char name[100];
    char capital[100];
    double area;
    double population;

    for (int i = 0; i < n - 1; i++) {
        cin >> name;
        cin >> capital;
        cin >> area;
        cin >> population;

        // testing constructor with arguments
        countries[i] = Country(name, capital, area, population);

    }


    // testing set methods and display for last element
    cin >> name;
    cin >> capital;
    cin >> area;
    cin >> population;
    countries[n - 1].setName(name);
    countries[n - 1].setCapital(capital);
    countries[n - 1].setArea(area);
    countries[n - 1].setPopulation(population);

    cout << "-->Testing set methods and display()" << endl;
    countries[n - 1].display();
    cout << endl;

    cout << "-->Testing sortCountries()" << endl;
    sortCountries(countries, n);
    return 0;
}
