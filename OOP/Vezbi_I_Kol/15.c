#include <stdio.h>

typedef struct RabotnaNedela
{
    int workingHrs[5];
    int number;
}RabotnaNedela;

typedef struct Rabotnik
{
    char name[50];
    RabotnaNedela weeks[4];
}Rabotnik;

int maxNedela(Rabotnik *r)
{
    int workingHours[4]={0};
    for (int i = 0; i<4; i++)
    {
        for (int j = 0; j<5; j++)
        {
            workingHours[i]+=r->weeks[i].workingHrs[j];
        }
    }

    int maxWeek = 0, maxHours=workingHours[0];
    for (int i = 1; i<4; i++)
    {
        if (workingHours[i] > maxHours)
        {
            maxWeek = i;
            maxHours = workingHours[i];
        }
    }

    return maxWeek+1;
}

void table(Rabotnik *r, int n)
{
    printf("Rab\t1\t2\t3\t4\tVkupno\n");
    for (int i = 0; i<n; i++)
    {
        int total = 0;
        printf("%s\t",r[i].name);
        for (int j = 0; j<4; j++)
        {
            int workingHoursWeekly = 0;
            for (int k = 0; k<5; k++)
            {
                workingHoursWeekly+=r[i].weeks[j].workingHrs[k];
                total+=r[i].weeks[j].workingHrs[k];
            }
            printf("%d\t",workingHoursWeekly);

        }
        printf("%d\n", total);
    }
}


int main() {
    int n;
    scanf("%d", &n);
    Rabotnik rabotnici[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", rabotnici[i].name);
        int j;
        for (j = 0; j < 4; ++j) {
            int k;
            for (k = 0; k < 5; ++k) {
                scanf("%d", &rabotnici[i].weeks[j].workingHrs[k]);
            }

        }
    }
    printf("TABLE\n");
    table(rabotnici, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", rabotnici[n / 2].name);
    printf("%d\n", maxNedela(&rabotnici[n / 2]));
    return 0;
}