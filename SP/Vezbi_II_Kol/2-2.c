#include <stdio.h>
#include <string.h>
#define MAX 100

int scaleDown(int num)
{
    while(num >= 10)
    {
        num/=10;
    }
    return num;
}

//ne menuvaj!
void wtf() {
    FILE *f = fopen("broevi.txt", "w");
    char c;
    while((c = getchar()) != EOF) {
        fputc(c, f);
    }
    fclose(f);
}

int main()
{
    wtf();
    FILE *f = fopen("broevi.txt", "r");
    int num;
    int numbers[100];
    while(1)
    {
        fscanf(f, "%d", &num);
        if (num == 0)
        {
            break;
        } else
        {
            int max = 0, pos = 0;
            for (int i = 0; i<num; i++)
            {
                fscanf(f, "%d", &numbers[i]);
                int scaled = scaleDown(numbers[i]);
                if (scaled > max)
                {
                    max = scaled;
                    pos = i;
                }
            }
            printf("%d\n", numbers[pos]);
        }
    }
    return 0;
}