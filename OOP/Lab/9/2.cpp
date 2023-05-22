//Да се имплементира класа Game за која се чува:
//title (низа од карактери)
//Во класата да се имплементира виртуелна функција void displayInfo() која на екран печати информации за дадената игра и виртуелна функција int complexity() која ја враќа комплексноста на играта.
//
//Потребно е да се имплементира класите BoardGame и CardGame кои што ќе наследуваат од класата Game.
//
//За класата BoardGame дополнително се чуваат:
//
//maxPlayers - максимален број на играчи (цел број)
//Доколку максималниот број на играчи е поголем од 6 тогаш комплексноста е 10, доколку  максималниот број на играчи е поголем од 3 а помал од 6 тогаш комплексноста е 5, а доколку е помал од 3, тогаш комплексноста е 3.
//
//Функцијата displayInfo() печати во формат:
//
//Game: [наслов на игра]
//
//Max players: [максимален број на играчи]
//
//Complexity: [комплексност]
//
//За класата CardGame дополнително се чуваат:
//
//numCards - број на карти (цел број)
//Доколку бројот на карти е поголем од 20 тогаш комплексноста е 10, доколку  бројот на карти е поголем од 10 а помал од 20 тогаш комплексноста е 5, а доколку е помал од 10, тогаш комплексноста е 3.
//
//Функцијата displayInfo() печати во формат:
//
//Game: [наслов на игра]
//
//Number of cards: [број на карти]
//
//Complexity: [комплексност]
//
//
//Потребно е да се имплементира класата BoardCardGame која што ќе наследува од класите BoardGame и CardGame.
//
//Комплексноста е пресметана на следниот начин: (комплексноста на CardGame + комплексноста на BoardGame)/2
//
//Функцијата displayInfo() печати во формат:
//
//Game: [наслов на игра]
//
//Complexity: [комплексност]
//
//Да се направи глобална функција Game *mostComplexCardGame(Game **games, int n) што ќе врати покажувач до најкомплексната игра со карти.

#include <iostream>
#include <cstring>

using namespace std;


class Game {
protected:
    char title[50];
public:
    Game(const char *title = "") {
        strcpy(this->title, title);
    }

    Game(const Game &g) {
        strcpy(this->title, g.title);
    }

    Game &operator=(const Game &g) {
        if (this == &g) return *this;
        strcpy(this->title, g.title);
        return *this;
    }

    virtual void displayInfo() = 0;

    virtual int complexity() = 0;
};

class BoardGame : virtual public Game {
protected:
    int maxPlayers;

public:
    BoardGame(const char *title = "", int maxPlayers = 0) : Game(title), maxPlayers(maxPlayers) {}

    BoardGame(const BoardGame &bg) : Game(bg), maxPlayers(bg.maxPlayers) {}

    BoardGame &operator=(const BoardGame &bg) {
        if (this == &bg) return *this;
        strcpy(this->title, bg.title);
        maxPlayers = bg.maxPlayers;
    }

    void displayInfo() {
        cout << "Game: " << title << endl;
        cout << "Max players: " << maxPlayers << endl;
        cout << "Complexity: " << complexity() << endl;
    }

    int complexity() {
        if (maxPlayers > 6) return 10;
        else if (maxPlayers > 3) return 5;
        else return 3;
    }
};

class CardGame : virtual public Game {
protected:
    int numCards;

public:
    CardGame(const char *title = "", int numCards = 0) : Game(title), numCards(numCards) {}

    CardGame(const CardGame &cg) : Game(cg), numCards(cg.numCards) {}

    CardGame &operator=(const CardGame &cg) {
        if (this == &cg) return *this;
        strcpy(this->title, cg.title);
        numCards = cg.numCards;
    }

    void displayInfo() override{
        cout << "Game: " << title << endl;
        cout << "Number of cards: " << numCards << endl;
        cout << "Complexity: " << complexity() << endl;
    }

    int complexity() override {
        if (numCards > 20) return 10;
        else if (numCards > 10) return 5;
        else return 3;
    }
};

class BoardCardGame : public BoardGame, public CardGame {
public:

    BoardCardGame(const char *title = "", int maxPlayers = 0, int numCards = 0) : Game(title), BoardGame(title, maxPlayers),
                                                                                  CardGame(title, numCards){}
    BoardCardGame(const BoardCardGame &bcg) : Game(bcg), BoardGame(bcg), CardGame(bcg) {}

    BoardCardGame &operator=(const BoardCardGame &bcg)
    {
        if (this == &bcg) return *this;
        strcpy(title, bcg.title);
        maxPlayers = bcg.maxPlayers;
        numCards = bcg.numCards;
        return *this;
    }

    void displayInfo() final {
        cout <<"Game: "<<title<<endl;
        cout <<"Complexity: "<<complexity();
    }

    int complexity() final {
        return (CardGame::complexity() + BoardGame::complexity()) / 2;
    }
};

Game *mostComplexCardGame(Game **games, int n)
{
    Game *mostComplex;
    bool f = false;
    for (int i = 0; i<n; i++)
    {
        CardGame *temp = dynamic_cast<CardGame *>(games[i]);
        if (!f && temp != 0)
        {
            f = true;
            mostComplex = temp;
        } else if (f && temp != 0)
        {
            if (mostComplex->complexity() < temp->complexity())
            {
                mostComplex = temp;
            }
        }
    }
    return mostComplex;
}

int main() {
    char title[50];
    int maxPlayers;
    int numCards;
    int n;
    int choice;

    cin >> choice;
    if (choice == 1) {
        cin >> title;
        BoardCardGame boardCardGame(title, 8, 15);
        boardCardGame.displayInfo();
    } else {

        cin >> n;

        Game **g = new Game *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> title >> maxPlayers;

                g[i] = new BoardGame(title, maxPlayers);
            } else {
                cin >> title >> numCards;

                g[i] = new CardGame(title, numCards);
            }

        }

        mostComplexCardGame(g, n)->displayInfo();

    }


    return 0;
}
