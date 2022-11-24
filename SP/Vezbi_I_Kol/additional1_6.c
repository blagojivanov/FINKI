#include <stdio.h>
int main()
{
    int m, i, j;
    scanf("%d", &m);
    for (i = 1; i<=m; i++)
    {
        for (j = 1; j<=m; j++)
        {
            if (j == 1 || j == m)
            {
                printf("+");
            }
            else if ((j>1 && j<m)&& (i==1 || i == m))
            {
                printf("*");
            } else
            {
                printf("%%");
            }
        }
        printf("\n");
    }
}