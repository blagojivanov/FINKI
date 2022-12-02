//Од тастатура се внесуваат димензиите на една матрица (m, n <= 100), а потоа и елементите од матрицата.
//Да се генерира низа (со најмногу m) така што секој елемент од низата се добива со наоѓање на елементот во
//секоја редица од матрицата што е најоддалечен од аритметичката средина во рамки на таа редица.
//Ако постојат повеќе елементи што се најоддалечени од аритметичката средина, тогаш се зема предвид првиот.
//Редоследот на запишување на елементите во низата одговара на редоследот на редиците.
//Пример:
//Влез:
//3 6
//1 2 2 3 4 5
//1 1 2 2 3 3
//1 2 3 4 5 6
//Излез: 5 1 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 1000

float average(int niza[], int size)
{
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum+=niza[i];
    }
    return sum/size;
}

int main()
{
    int m,n, mat[MAX][MAX];
    scanf("%d%d", &m,&n);
    for (int i = 0; i<m; i++)
    {
        for (int j = 0; j<n; j++)
        {
            scanf("%d", &mat[i][j]);
        }
    }

    int maxn[m];

    for (int i = 0; i<m; i++)
    {
        int max = 0;
        float avg = average(mat[i], n);
        float maxodd = fabs((float)mat[i][0] - avg);
        for (int j = 0; j<n; j++)
        {
            if ((fabs((float)mat[i][j] - avg) > maxodd))
            {
                maxodd = fabs((float)mat[i][j]-avg);
                max = j;
            }
        }
        maxn[i] = mat[i][max];

    }
    for (int i = 0; i<m; i++)
    {
        printf("%d ", maxn[i]);
    }
}