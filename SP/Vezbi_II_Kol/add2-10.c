//Во рамките на текстуална датотека matrica.txt се сместени елементите (целобројни вредности) од една матрица (A).
//Во првиот ред од датотеката се запишани бројот на редици n и бројот на колони m на матрицата (n, m < 120).
//Потоа, во секој ред од датотеката се запишани елементите од соодветната редица на матрицата.
//Да се испечати колку индексни броеви има во секоја колона поединечно.
//Индексен број е број чија вредност е идентична со вредноста што се добива со спојување на индексот од редицата и колоната на елементот.
//Помош:
//Индексен елемент: вредноста на елементот Aij е иста со ij како број
//- ако i=10, j=31, елементот Aij треба да има вредност 1031 за да биде индексен број

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include <stdlib.h>
int isIndex(int posx, int posy, int el)
{
    int coeff = 1, tempy = posy;
    if (posy == 0)
    {
        coeff*=10;
    }
    while(tempy != 0)
    {
        coeff*=10;
        tempy/=10;
    }

    if (posx*coeff + posy == el)
    {
        return 1;
    }
    return 0;
}

void wtf() {
    FILE *f = fopen("matrica.txt", "w");
    char c;
    while((c = getchar()) != '#') {
        fputc(c, f);
    }
    fclose(f);
}

int main() {
    wtf();
    //vasiot kod ovde
    FILE *f = fopen("matrica.txt", "r");
    int a[120][120];
    int n, m;
    fscanf(f, "%d %d\n", &n, &m);

    for (int i = 0; i<n; i++)
    {
        for (int j = 0; j<m; j++)
        {
            fscanf(f,"%d ", &a[i][j]);
        }
    }

    for (int j = 0; j<m; j++)
    {
        int indct = 0;
        for (int i = 0; i<n; i++)
        {
            if (isIndex(i,j,a[i][j]))
            {
                indct++;
            }
        }
        printf("%d\n", indct);
    }

//    for (int i = 0; i<n; i++)
//    {
//        for (int j = 0; j<m; j++)
//        {
//            printf("%d ", a[i][j]);
//        }
//        printf("\n");
//    }
    return 0;
}
