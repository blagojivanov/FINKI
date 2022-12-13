//Дадена е текстуална датотека text.txt.
//Да се избројат и испечатат сите последнователни појавувања на соседни самогласки во датотеката.
//Појавата на големи и мали букви да се игнорира.
//Пронајдените парови самогласки да се испечатат на екран, секој во нов ред со мали букви.
//Потоа во нов ред се печати бројот на појавувања на паровите самогласки.

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void writeToFile() {
    FILE *f = fopen("text.txt", "w");
    char c;
    while((c = getchar()) != '#') {
        fputc(c, f);
    }
    fclose(f);
}

int main() {

    char *arr = "AEIOUaeiou";
    int gate1 = 0, gate2 = 0, ct = 0;
    writeToFile();
    FILE *f = fopen("text.txt", "r");
    // Vasiot kod zapocnuva od tuka
    int flag = 1;
    char nowch,prevch;
    while (!feof(f))
    {
        nowch = fgetc(f);
        nowch = tolower(nowch);
        if (nowch == '#')
        {
            break;
        }

        if (flag)
        {
            flag = 0;
            prevch = nowch;
            continue;
        }else
        {
            for (int i = 0; i<10; i++)
            {
                if (nowch == arr[i])
                {
                    gate1 = 1;
                }
                if (prevch == arr[i])
                {
                    gate2 = 1;
                }
            }
            if (gate1 && gate2)
            {

                printf("%c%c\n", prevch, nowch);
                ct++;
            }
            gate1 = gate2 = 0;
            prevch = nowch;
        }

    }

    printf("%d", ct);
    return 0;
}
