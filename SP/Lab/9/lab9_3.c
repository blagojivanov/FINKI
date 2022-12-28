// so rekurzivna f-ja triagolnik(int n) da se ispechate triagolnik so forma
// za triagolnik(6)
//1 2 3 4 5 6
//1 2 3 4 5
//1 2 3 4
//1 2 3
//1 2
//1

#include <stdio.h>

void triagolnik(int n)
{
    int i = 1;
    if (n == 1)
    {
        printf("1");
    } else
    {
        for (; i<=n; i++)
        {
            printf("%d ", i);
        }
        printf("\n");
        return triagolnik(n-1);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    triagolnik(n);
    return 0;
}