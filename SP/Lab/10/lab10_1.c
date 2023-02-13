//Од стандарден влез се вчитува бројот N, бројот K и знакот C. Потоа се вчитуваат N текстуални низи (секоја во нов ред).
//Да се испечатат на екран текстуалните низи кои го содржат знакот C точно K пати без разлика на големината на буквата.
//Ако нема такви низи, да се испечати порака NONE.

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    int n, k, ct = 0;
    char c;
    char strings[100][100];
    scanf("%d %d %c\n", &n, &k, &c);
    for(int i = 0; i<n; i++)
    {
        int tempct = 0;
        char nc;
        while((nc = getchar())!='\n')
        {
            strings[i][tempct] = nc;
            tempct++;
        }
    }
    for (int i = 0; i<n; i++)
    {
        int privct=0;
        char *momst = strings[i];
        for (int j = 0; j<strlen(momst); j++)
        {
            if (tolower(momst[j]) == tolower(c))
            {
                privct++;
            }
            if (privct > k) {
                break;
            }
        }
        if (privct == k)
        {
            printf("%s\n", momst);
            ct++;
        }
    }
    if (ct == 0)
    {
        printf("NONE");
    }
    return 0;
}