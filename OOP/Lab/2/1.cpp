//Да се креира класа BasketballPlayer која ќе ги чува следните информации:
//име на кошаркарот (низа од знаци не подолга од 20 карактери)
//презиме на кошаркарот (низа од знаци не подолга од 20 карактери)
//број на дрес (цел број)
//поени од прв натпревар (цел број)
//поени од втор натпревар (цел број)
//поени од трет натпревар (цел број)
//Да се направат потребните методи за класата, како и метод за печатење на информации за кошаркарот во следен формат
//"Player: name surname with number: number has avg_pts points on average".
//Од стандарден влез се внесуваат име, презиме, број на дрес и поени за сите три натпревари за еден кошаркар.
//На стандарден излез се печатат информациите за кошаркарот.

#include <iostream>
#include <cstring>

using namespace std;

class BasketballPlayer {

private:
    char FN[20];
    char LN[20];
    int num;
    int p1, p2, p3;

public:

    void setFN(char FN[20]) {
        strcpy(this->FN, FN);
    }

    void setLN(char LN[20]) {
        strcpy(this->LN, LN);
    }

    void setNum(int num) {
        this->num = num;
    }

    void setP1(int p1) {
        this->p1 = p1;
    }

    void setP2(int p2) {
        this->p2 = p2;
    }

    void setP3(int p3) {
        this->p3 = p3;
    }

    void print() {
        printf("Player: %s %s with number: %d has %g points on average", FN, LN, num, (float) (p1 + p2 + p3) / 3);
    }
};

int main() {
    char name[20], surname[20];
    int num, p1, p2, p3;

    BasketballPlayer player;

    cin >> name >> surname >> num >> p1 >> p2 >> p3;

    player.setFN(name);
    player.setLN(surname);
    player.setNum(num);
    player.setP1(p1);
    player.setP2(p2);
    player.setP3(p3);

    player.print();
    return 0;

}
