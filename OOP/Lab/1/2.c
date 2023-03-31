//Да се креира структура Vehicle во која што ќе се чуваат следните податоци:
//
//модел (максимум 100 карактери)
//марка (максимум 100 карактери)
//година на производство (цел број)
//поминати километри (цел број)
//Од стандарден влез се внесуваат најпрво број на возила, па потоа возилата со сите нивни податоци по редлоследот даден погоре.
//
//Да се креира функција getNewestVehicle() која што ќе го испечати на екран моделот и марката на возилото што што е најново.
//Доколку постојат повеќе такви возила, да се испечати возилото со помалку поминати километри.

#include <stdio.h>

typedef struct Vehicle
{
    char model[100];
    char marka[100];
    int prodyear;
    int km;
} Vehicle;

void getNewestVehicle(Vehicle *vehicles, int n)
{
    int i = 0;
    Vehicle newest = vehicles[0];
    for (; i<n; i++)
    {
        if (vehicles[i].prodyear > newest.prodyear)
        {
            newest = vehicles[i];
        }
    }
    printf("%s %s", newest.marka, newest.model);
}

int main()
{
    int n, i = 0;
    scanf("%d", &n);
    Vehicle vehicles[100];

    for (; i<n; i++)
    {
        scanf("%s\n%s\n%d %d", vehicles[i].marka, vehicles[i].model, &vehicles[i].prodyear, &vehicles[i].km);
    }
    getNewestVehicle(vehicles, n);
    return 0;
}
