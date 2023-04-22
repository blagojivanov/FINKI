#include<stdio.h>

typedef struct Pacient {
    char ime[50];
    int zdrastveno;
    int pregledi;
} Pacient;

typedef struct doktor {
    char ime[50];
    int br_pac;
    Pacient niza[50];
    float cena;
} doktor;

void najuspesen_doktor(doktor *md, int n)
{
    float max = 0;
    int maxp = 0;
    int maxi = 0;
    for(int i = 0; i<n; i++)
    {
        int p = 0;
        float sum = 0;
        for (int j =0; j<md[i].br_pac; j++)
        {
            if (md[i].niza[j].zdrastveno == 0)
            {
                sum+=md[i].cena*md[i].niza[j].pregledi;
            }
            p+=md[i].niza[j].pregledi;
        }

        if (sum > max)
        {
            maxp = p;
            max = sum;
            maxi = i;
        } else if (sum == max)
        {
            if (maxp < p)
            {
                maxp = p;
                max = sum;
                maxi = i;
            }
        }
    }
    printf("%s %.2f %d", md[maxi].ime, max, maxp);
}

int main() {
    int i, j, n, broj;
    doktor md[200];
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        //ime na doktor
        scanf("%s", &md[i].ime);
        //broj na pacienti
        scanf("%d", &md[i].br_pac);
        //cena na pregled
        scanf("%f", &md[i].cena);

        for (j = 0; j < md[i].br_pac; j++) {
            scanf("%s", &md[i].niza[j].ime);
            scanf("%d", &md[i].niza[j].zdrastveno);
            scanf("%d", &md[i].niza[j].pregledi);
        }
    }
    najuspesen_doktor(md, n);

    return 0;
}