#include <stdio.h>
#define MAX 100
int main()
{
    int a[MAX], n, i,j, k, atran[MAX] = {0};
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &k);


    for (i = 0; i<n; i++)
    {
        if (a[i] >=k)
        {
            for (j = i + 1; j<n; i++)
            {
                if (a[j] < k)
                {
                    int pom = a[i];
                    a[i] = a[j];
                    a[j] = a[i];
                }
            }
        }
    }
    for (i = 0; i<n; i++)
    {
        printf("%d", a[i]);
    }
    return 0;
}