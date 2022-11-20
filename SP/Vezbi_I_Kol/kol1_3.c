//Од тастатура се внесуваат два природни броја M (M > 2) и N.
//Да се напише програма која ќе го најде и испечати првиот број помал од N кој има помалку од M делители (1 и N се делители на N)

#include <stdio.h>
int main()
{
    int m,n,i;
    scanf("%d%d", &m, &n);
    for (i = n-1; i>0; i--)
    {
        int brojac = 2, j;
        for (j = 2; j<=i/2 + 1; j++)
        {
            if (i%j == 0) {
                brojac++;
                if (brojac > m)
                {
                    break;
                }
            }
        }
        if (brojac < m)
        {
            printf("%d", i);
            break;
        }
    }
    return 0;
}
