//Да се напише програма која вчитува матрица со димензии MxN (макс. 100x100).
//На почетокот се внесуваат димензиите на матрицата, а потоа и елементите на матрицата кои се само вредностите 1 и 0.
//Програмата треба да изброи и отпечати на СИ во колку од редиците и колоните има барем 3 последователни елементи со вредност 1.



#include <stdio.h>

#define MAX 100

int main() {
    int mat[MAX][MAX], m, n, ct = 0, i, j;
    scanf("%d%d", &m, &n);
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%d",&mat[i][j]);

    for(i = 0; i<m;i++)
    {
        int privct = 0;
        for (j = 0; j<n; j++)
        {
            if (mat[i][j]) {
                privct++;
                if (privct >= 3) {
                    ct++;
                    break;
                }
            } else
            {
                privct = 0;
            }
        }
    }
    for(i = 0; i<n;i++)
    {
        int privct = 0;
        for (j = 0; j<m; j++)
        {
            if (mat[j][i]) {
                privct++;
                if (privct >= 3) {
                    ct++;
                    break;
                }
            } else
            {
                privct = 0;
            }
        }
    }
    printf("%d", ct);
}