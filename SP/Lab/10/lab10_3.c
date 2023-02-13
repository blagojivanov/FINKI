#include <ctype.h>
#include <stdio.h>
#include <string.h>

void writeToFile()
{
    FILE *f = fopen("text.txt", "w");
    char c;
    while ((c = getchar()) != '#')
    {
        fputc(c,f);
    }
    fclose(f);
}

int main()
{
    writeToFile();
    char c;
    int freq_s = 0, freq_u = 0, tot = 0;

    FILE *f = fopen("text.txt", "r");
    while ((c = fgetc(f)) != EOF)
    {
        if (isalpha(c))
        {
            tot++;
            if (islower(c))
            {
                freq_s++;
            } else
            {
                freq_u++;
            }
        }
    }
    printf("%.4f\n", (float) freq_u/tot);
    printf("%.4f", (float) freq_s/tot);
    fclose(f);
    return 0;
}