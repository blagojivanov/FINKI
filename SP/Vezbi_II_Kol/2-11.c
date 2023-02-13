//Да се напише програма во која од дадена датотека со име "input.txt" за секој ред ќе се отпечати бројот на цифри во тој ред
//знакот :, па самите цифри подредени според ASCII кодот во растечки редослед. Редовите во датотеката не се подолги од 100 знаци.

#include <stdio.h>
#include <ctype.h>
#include <string.h>
void wtf() {
    FILE *f = fopen("input.txt", "w");
    char c;
    while((c = getchar()) != '~') {
        fputc(c, f);
    }
    fclose(f);
}

int main() {
    wtf();
    FILE *f = fopen("input.txt", "r");
    while(1)
    {
        char str[101];
        int ct = 0;
        fgets(str,100,f);
        if (feof(f))
        {
            break;
        }
        for (int i = 0; i<strlen(str); i++)
        {
            if (isdigit(str[i]))
            {
                ct++;
            }
        }

        if (ct>0)
        {
            printf("%d:", ct);
            for (int i = 0; i<=9;i++)
            {
                for (int j = 0; j<strlen(str); j++)
                {
                    if (isdigit(str[j]) && str[j] - 48 == i)
                    {
                        printf("%d",i);
                    }
                }
            }
            printf("\n");
        }
    }
    fclose(f);
    return 0;
}
