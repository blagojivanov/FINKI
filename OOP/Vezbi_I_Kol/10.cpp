//Да се креира структура Igrac во која се чуваат податоци за еден играч на компјутерската игра. За играчот се чуваат информации за корисничкото име на играчот (низа од 15 знаци), број на ниво до кој играчот е стигнат (цел број) и број на освоени поени (цел број) (10 поени).
//
//Потоа да се креирa структура KompjuterskaIgra во која се чуваат податоци за името на играта (низа од 20 знаци), низа од играчи кои ја играат играта (најмногу 30) и бројот на играчи. (10 поени)
//
//Треба да се направи функција со потпис (15 поени)
//
//void najdobarIgrac(KompjuterskaIgra *lista, int n)
//Оваа функција треба да го испечати името на најдобриот играч на онаа игра која има најголема популарност (ја играат наjголем број на играчи). Најдобар играч е играчот кој има најголем број на освоени поени. Ако има повеќе играчи со ист максимален број на освоени поени, најдобар е играчот кој има достигнато најголемо ниво.
//
//Печатењето е во форматот: "Najdobar igrac e igracot so korisnicko ime XXXXX koj ja igra igrata YYYYYY". (XXXXXX е корисничкото име на најдобриот играч,а YYYYY е името на играта која ја играат најголем број на играчи)
//
//(Забелешка: секогаш ќе има точно еден најдобар играч)
//
//Функционалност на задачата и дополнување на main функцијата (10 поени)
//
//Забелешка: Задачата да се реши во програмскиот јазик C+
#include <iostream>
using namespace std;

typedef struct Igrac
{
    char user[15];
    int level;
    int points;
} Igrac;

typedef struct KompjuterskaIgra
{
    char name[20];
    Igrac players[30];
    int number;
} KompjuterskaIgra;

void najdobarIgrac(KompjuterskaIgra *lista, int n)
{
    KompjuterskaIgra mostPlayed = lista[0];
    for (int i = 1; i<n; i++)
    {
        if (mostPlayed.number < lista[i].number)
        {
            mostPlayed = lista[i];
        }
    }

    Igrac bestPlayer = mostPlayed.players[0];
    for (int i = 1; i<mostPlayed.number; i++)
    {
        if (bestPlayer.points < mostPlayed.players[i].points)
        {
            bestPlayer = mostPlayed.players[i];
        } else if (bestPlayer.points == mostPlayed.players[i].points)
        {
            if (bestPlayer.level < mostPlayed.players[i].level)
            {
                bestPlayer = mostPlayed.players[i];
            }
        }
    }

    cout << "Najdobar igrac e igracot so korisnicko ime "<<bestPlayer.user<<" koj ja igra igrata "<<mostPlayed.name;
}

int main() {
    int n,m;
    char ime[20];
    cin>>n;
    KompjuterskaIgra poleigri[100];
    for (int i=0; i<n; i++) {
        KompjuterskaIgra nova;
        cin>>nova.name>>nova.number;
        for (int j=0; j<nova.number; j++) {
            Igrac nov;
            cin>>nov.user>>nov.level>>nov.points;
            nova.players[j]=nov;
        }
        poleigri[i]=nova;
    }

    najdobarIgrac(poleigri,n);
    return 0;
}
