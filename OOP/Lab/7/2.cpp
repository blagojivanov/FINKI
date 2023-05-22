//Да се дефинира класа MarathonRunner за која ќе се чуваат:
//
//динамички алоцирана низа од карактери за името на тркачот
//        низа од максимум 40 карактери за земјата во која тркачот живее
//        просечна брзина на трчање на тркачот на маратоните оваа година (double)
//вкупна должина (во километри) на маратоните на кои учествувал тркачот оваа година (double)
//вкупно време (во часови) потребно за завршување на маратоните на кои учествувал тркачот оваа година (double)
//За потребите на класата да се дефинираат:
//
//default конструктор и конструктор со аргументи
//        copy constructor и оператор =
//деструктор
//метод rating() кој го враќа рејтингот на тркачот кој се пресметува како:
//
//
//((brzina*0.45) + (dolzina*0.3) + (vreme*0.25))
//метод print() кој го печати тркачот во следниот формат:
//
//Име - земја
//
//        Average speed: просечна брзина на трчање
//
//Total distance: вкупна должина на маратоните на кои учествувал
//
//        Тotal time: вкупно време потребно за завршување на маратоните
//
//        Rating: рејтинг
//
//        Од претходната класа MarathonRunner да се изведе класата EliteMarathonRunner за која дополнително ќе се чуваат и:
//
//просечна брзина на трчање на тркачот EliteInternational маратоните  (double)
//вкупна должина (во километри) на EliteInternational маратоните на кои учествувал тркачот  (double)
//вкупно време (во часови) потребно за завршување на EliteInternational маратоните на кои учествувал тркачот (double)
//За потребите на класата да се дефинираат:
//
//default конструктор
//        конструктор кој прима објект од MarathonRunner и плус додатните информации (погледни main)
//конструктор кој ги прима сите аргументи (погледни main)
//copy constructor, оператор =, деструктор
//метод eliteRating() кој го враќа рејтингот на тркачот од EliteInternational маратоните и кој се пресметува како:
//
//70% од просечната брзина + 10% од вкупната должина + 30% од вкупното време
//
//        Да се препокријат методите:
//
//rating() кој го враќа просекот од обичниот рејтинг на тркачот и неговиот Elite рејтинг
//print() кој покрај основните информации за тркачот печати и:
//
//Elite Rating: рејтингот од EliteInternational маратоните
//
//New Rating: просечниот рејтинг

#include <iostream>
#include <cstring>

using namespace std;

class MarathonRunner {
protected:
    char *name;
    char zemja[40];
    double brzina;
    double km;
    double time;
public:
    MarathonRunner(char *name = "", char *zemja = "", double brzina = 0, double km = 0, double time = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->zemja, zemja);
        this->brzina = brzina;
        this->km = km;
        this->time = time;

    }

    MarathonRunner(const MarathonRunner &mr) {
        this->name = new char[strlen(mr.name) + 1];
        strcpy(this->name, mr.name);
        strcpy(this->zemja, mr.zemja);
        this->brzina = mr.brzina;
        this->km = mr.km;
        this->time = mr.time;

    }

    MarathonRunner &operator=(const MarathonRunner &mr) {
        if (this == &mr) return *this;
        delete [] name;
        this->name = new char[strlen(mr.name) + 1];
        strcpy(this->name, mr.name);
        strcpy(this->zemja, mr.zemja);
        this->brzina = mr.brzina;
        this->km = mr.km;
        this->time = mr.time;
        return *this;
    }

    ~MarathonRunner()
    {
        delete []name;
    }

    double rating()
    {
        return brzina*0.45 + km*0.3+ time*0.25;
    }
    void print()
    {
        cout<<name<<" - "<<zemja<<endl;
        cout<<"Average speed: "<< brzina<<endl;
        cout<<"Total distance: "<< km<<endl;
        cout<<"Total time: "<< time<<endl;
        cout<<"Rating: "<< rating() <<endl;
    }

};

class EliteMarathonRunner: public MarathonRunner {
private:
    double avgspeed;
    double elkm;
    double eltime;

public:

    EliteMarathonRunner(char *name = "", char *zemja = "", double brzina = 0, double km = 0,
                        double time = 0, double avgspeed = 0, double elkm = 0, double eltime = 0)
            : MarathonRunner(name, zemja, brzina, km, time) {
        this->avgspeed = avgspeed;
        this->elkm = elkm;
        this->eltime = eltime;
    }

    EliteMarathonRunner(MarathonRunner marathonRunner, double avgspeed = 0, double elkm = 0, double eltime = 0)
            : MarathonRunner(marathonRunner) {
        this->avgspeed = avgspeed;
        this->elkm = elkm;
        this->eltime = eltime;
    }

    EliteMarathonRunner(const EliteMarathonRunner &emr) : MarathonRunner(emr)
    {
        avgspeed = emr.avgspeed;
        elkm = emr.elkm;
        eltime = emr.eltime;
    }

    EliteMarathonRunner &operator=(const EliteMarathonRunner &emr)
    {
        if (this == &emr) return *this;
        delete [] name;
        this->name = new char[strlen(emr.name) + 1];
        strcpy(this->name, emr.name);
        strcpy(this->zemja, emr.zemja);
        this->brzina = emr.brzina;
        this->km = emr.km;
        this->time = emr.time;
        avgspeed = emr.avgspeed;
        elkm = emr.elkm;
        eltime = emr.eltime;
        return *this;
    }

    double eliteRating()
    {
        return avgspeed * 0.7 + eltime * 0.3 + elkm * 0.1;
    }

    double rating()
    {
        return (MarathonRunner::rating() + eliteRating()) / 2;
    }

    double print()
    {
        MarathonRunner::print();
        cout<<"Elite Rating: "<<eliteRating()<<endl;
        cout<<"New Rating: "<<rating()<<endl;
    }
};
int main() {

    char name[50];
    char country[40];
    double avgSpeed;
    double distance;
    double time;
    double EliteavgSpeed;
    double Elitedistance;
    double Elitetime;

    MarathonRunner * RUNNERs = new MarathonRunner[5];
    EliteMarathonRunner * elRUNNERs = new EliteMarathonRunner[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "MARATHON RUNNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> country >> avgSpeed >> distance >> time;
            RUNNERs[i] = MarathonRunner(name,country,avgSpeed,distance,time);
            RUNNERs[i].print();
        }
    }
    else if (n == 2) {

        for (int i=0; i < 5; ++i){
            cin >> name >> country >> avgSpeed >> distance >> time;
            cin >> EliteavgSpeed >> Elitedistance >> Elitetime;
            RUNNERs[i] = MarathonRunner(name,country,avgSpeed,distance,time);
            elRUNNERs[i] = EliteMarathonRunner(RUNNERs[i],EliteavgSpeed,Elitedistance,Elitetime);
        }

        cout << "NBA RUNNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            RUNNERs[i].print();

        cout << "ELITE RUNNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            elRUNNERs[i].print();

    }
    else if (n == 3) {

        for (int i=0; i < 5; ++i){
            cin >> name >> country >> avgSpeed >> distance >> time;
            cin >> EliteavgSpeed >> Elitedistance >> Elitetime;
            elRUNNERs[i] = EliteMarathonRunner(name, country, avgSpeed, distance, time,
                                               EliteavgSpeed,Elitedistance,Elitetime);
        }
        cout << "ELITE RUNNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            elRUNNERs[i].print();

    }

    delete [] RUNNERs;
    delete [] elRUNNERs;
}
