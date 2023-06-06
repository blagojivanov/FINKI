#include <iostream>
#include <cstring>

using namespace std;

class ExistingGame : public exception
{
public:
    ExistingGame(){

    }
    void message()
    {
        cout<<"The game is already in the collection"<<endl;
    }
};

class Game
{
protected:
    char name[100];
    float price;
    bool sale;

public:
    Game(const char *name = "", float price = 0, bool sale = false)
    {
        strcpy(this->name, name);
        this->price = price;
        this->sale = sale;
    }
    friend ostream &operator<<(ostream &os, Game &g)
    {
        os << "Game: "<< g.name << ", regular price: $"<<g.price;
        if (g.sale == 1) os << ", bought on sale";
        os<<endl;
        return os;
    }

    friend istream &operator>>(istream &is, Game &g)
    {
        is.get();
        is.getline(g.name,100);
        is>> g.price >> g.sale;
        return is;
    }
    bool operator==(const Game &g)
    {
        if (strcmp(name, g.name) == 0)
        {
            return true;
        }
        return false;
    }

    virtual bool isSale()
    {
        return sale;
    }
    float getPrice()
    {
        return price;
    }
};

class SubscriptionGame : public Game
{
private:
    float fee;
    int m,y;
public:
    SubscriptionGame(const char *name = "", float price = 0, bool sale = false, float fee = 0, int m = 0, int y=0)
            : Game(name, price, sale), fee(fee), m(m), y(y)
    {
    }

    friend ostream &operator<<(ostream &os, SubscriptionGame &g)
    {
        os << "Game: "<< g.name << ", regular price: $"<<g.price;
        if (g.sale) os << ", bought on sale";
        os << ", monthly fee: $"<<g.fee<<", purchased: "<<g.m<<"-"<<g.y<<endl;
        return os;
    }

    friend istream &operator>>(istream &is, SubscriptionGame &g)
    {
        is.get();
        is.getline(g.name,100);

        is >> g.price >> g.sale >> g.fee >> g.m >> g.y;
        return is;
    }
    int getY()
    {
        return y;
    }
    int getM()
    {
        return m;
    }
    int mfee()
    {
        return fee;
    }
};

class User
{
private:
    char ime[100];
    Game **niza;
    int n;

public:
    User(const char *ime = "", Game **niza = 0, int n = 0)
    {
        strcpy(this->ime,ime);
        this->n = n;
        this->niza = new Game*[n];
        for (int i = 0; i<n; i++)
        {
            this->niza[i] = niza[i];
        }
    }

    User(const User &u)
    {
        strcpy(this->ime,u.ime);
        this->n = u.n;
        this->niza = new Game*[u.n];
        for (int i = 0; i<u.n; i++)
        {
            this->niza[i] = u.niza[i];
        }
    }

    User &operator=(const User &u)
    {
        if (this == &u) return *this;
        strcpy(this->ime,u.ime);
        this->n = u.n;
        delete [] niza;
        this->niza = new Game*[u.n];
        for (int i = 0; i<u.n; i++)
        {
            this->niza[i] = u.niza[i];
        }
        return *this;
    }

    User &operator+=(Game &g)
    {
        for (int i = 0; i<n; i++)
        {
            if (*niza[i] == g)
            {
                throw ExistingGame();
            }
        }

        Game **temp = new Game*[n+1];
        for (int i = 0; i<n; i++)
        {
            temp[i] = niza[i];
        }
        temp[n++] = &g;
        delete [] niza;
        niza = temp;
        return *this;
    }

    ~User()
    {
        for (int i = 0; i<n; i++) delete niza[i];
        delete [] niza;
    }
    int total_spent()
    {
        int tot = 0;
        for (int i = 0; i<n; i++)
        {
            if (niza[i]->isSale())
            {
                tot+=niza[i]->getPrice() * 0.3;
            } else
            {
                tot+=niza[i]->getPrice();
            }

            SubscriptionGame *sg = dynamic_cast<SubscriptionGame *>(niza[i]);
            if (sg !=0)
            {
                tot+= sg->mfee()*((2018*12) + 5 - ((sg->getY()*12) + sg->getM()));
            }
        }
        return tot;
    }
    int get_games_number()
    {
        return n;
    }
    const char *get_name()
    {
        return ime;
    }

    friend ostream &operator<<(ostream &os, User &u)
    {
        os<<endl;
        os << "User: "<<u.ime<<endl;
        for (int i = 0; i<u.n; i++)
        {
            os<<"- ";
            SubscriptionGame *sg = dynamic_cast<SubscriptionGame *>(u.niza[i]);
            if (sg != 0)
            {
                os<<*sg;
            } else
            {
                os<<*u.niza[i];
            }
        }
        os<<endl;
        return os;
    }

};

int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1){
        cout<<"Testing class Game and operator<< for Game"<<std::endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    }
    else if (test_case_num == 2){
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin>>game_price>>game_on_sale;

        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator>> for Game"<<std::endl;
        Game g;

        cin>>g;

        cout<<g;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
        SubscriptionGame sg;

        cin>>sg;

        cout<<sg;
    }
    else if (test_case_num == 5){
        cout<<"Testing class User and operator+= for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        try {

            for (int i=0; i<num_user_games; ++i){

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingGame &ex){
            ex.message();
        }

        cout<<u;

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingGame for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            try {
                u+=(*g);
            }
            catch(ExistingGame &ex){
                ex.message();
            }
        }

        cout<<u;

    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            u+=(*g);
        }

        cout<<u;

        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}
