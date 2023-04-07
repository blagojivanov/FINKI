//Да се креира структура Воз во која се чуваат податоци за релацијата по која се движи возот (низа од најмногу 50 знаци), предвиден бројот на километри што треба да се поминат (реален број), како и бројот на патници во возот (цел број).
//
//Потоа да се креирa структура ZeleznickaStanica во која се чуваат податоци за градот во кој се наоѓа (низа од 20 знаци), низа од возови што поаѓаат од станицата (најмногу 30) и бројот на возови (цел број).
//
//Треба да се направи функција со потпис
//
//void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
//во која се печати релацијата и бројот на километри на возот што поминува најкратка релација (најмалку километри), а поаѓа од железничката станица од градот што се проследува како влезен аргумент. Ако има повеќе возови со ист најмал број на километри, да се испечати релацијата на последниот таков.
//
//Забелешка: Задачата да се реши во програмскиот јазик C++
#include<iostream>
#include <cstring>

using namespace std;

struct Voz
{
    char dest[50];
    int km, cap;
};

struct ZeleznickaStanica
{
    char place[20];
    Voz vozovi[30];
    int nr;
};

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char * grad)
{
    for (int j = 0; j<n; j++)
    {
        if (strcmp(zs[j].place, grad) == 0) {
            Voz shortest = zs[j].vozovi[0];
            for (int i = 1; i < zs[j].nr; i++) {
                if (zs[j].vozovi[i].km <= shortest.km) {
                    shortest = zs[j].vozovi[i];
                }
            }
            cout<<"Najkratka relacija: "<<shortest.dest<<" ("<<shortest.km<<" km)";
        }
    }
}

int main(){

    int n;
    cin>>n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        cin>>zStanica[i].place>>zStanica[i].nr;
        for (int j = 0; j<zStanica[i].nr; j++)
        {
            cin>>zStanica[i].vozovi[j].dest>>zStanica[i].vozovi[j].km>>zStanica[i].vozovi[j].cap;
        }
    }

    char grad[25];
    cin>>grad;

    najkratkaRelacija(zStanica,n,grad);
    return 0;
}
