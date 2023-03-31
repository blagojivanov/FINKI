//За програмски јазик да се употреби C.
//
//Да се напише програма во која од стандарден влез се внесува бројот N (бројот на трансакции),
//а потоа N трансакциски сметки и како резултат ги печати идентификацискиот број
//и вкупната сума (со провизија) на сите трансакции платени со кредитна картичка.
//Во случај да нема трансакција платена со кредитна картичка да се испечати "No credit card transaction".
//
//Во структурата Трансакција (Transaction) треба да се чуваат следните информации:
//- Идентификациски број (int)
//- Платена сума (int)
//- Провизија (int)
//- Дали е платено со дебитна или кредитна картичка (0 - дебитна, 1 - кредитна)
//
//Ограничување: 0 < N < 100

#include <stdio.h>

typedef struct Transaction
{

    int id;
    int sum;
    int provision;
    int crdeb;

} Transaction;

int main() {

    int n, i = 0, ct = 0;
    scanf("%d", &n);
    Transaction list[100];

    for (; i<n; i++)
    {
        scanf("%d %d %d %d", &list[i].id, &list[i].sum, &list[i].provision, &list[i].crdeb);
        if (list[i].crdeb == 1)
        {
            ct++;
        }

    }

    if (ct == 0)
    {
        printf( "No credit card transaction");
        return 0;
    }


    for (i = 0; i<n; i++)
    {
        if (list[i].crdeb == 1)
        {
            printf("%d %d\n", list[i].id, (int) list[i].sum + list[i].provision);
        }
    }
    return 0;
}
