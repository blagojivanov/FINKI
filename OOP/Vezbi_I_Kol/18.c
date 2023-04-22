#include<stdio.h>
#include<string.h>

typedef struct SkiLift
{
    char name[15];
    int max;
    int pus;
}SkiLift;

typedef struct SkiCenter
{
    char name[15];
    char country[20];
    SkiLift lifts[20];
    int n;
} SkiCenter;

void najgolemKapacitet(SkiCenter *sc, int n)
{
    SkiCenter m = sc[0];
    int max=0;
    for (int i = 0; i<n; i++)
    {
        int capacity = 0;
        for (int j = 0; j<sc[i].n; j++)
        {
            if (sc[i].lifts[j].pus)
            {
                capacity+=sc[i].lifts[j].max;
            }
        }
        if (capacity > max)
        {
            max = capacity;
            m = sc[i];
        } else if (capacity == max)
        {
            int p1=0, p2=0;
            for (int k = 0; k<m.n; k++)
            {
                p1+=m.lifts[k].pus;
            }
            for (int k = 0; k<sc[i].n; k++)
            {
                p2+=sc[i].lifts[k].pus;
            }

            if (p1 < p2)
            {
                max = capacity;
                m = sc[i];
            }
        }
    }
    printf("%s\n%s\n%d", m.name, m.country, max);
}

int main()
{
    int n, i,j;
	scanf("%d", &n);
    SkiCenter skiCentri[10];
	for (i = 0; i < n; i++){
		scanf("%s", skiCentri[i].name);
		scanf("%s", skiCentri[i].country);
		scanf("%d", &skiCentri[i].n);

        for (j = 0; j<skiCentri[i].n; j++)
        {
            scanf("%s", skiCentri[i].lifts[j].name);
            scanf("%d", &skiCentri[i].lifts[j].max);
            scanf("%d", &skiCentri[i].lifts[j].pus);
        }

	}

    najgolemKapacitet(skiCentri, n);
	return 0;
}
