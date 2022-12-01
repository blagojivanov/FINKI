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