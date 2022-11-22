//Да се напише програма во која од тастатура се внесуваат непознат број мали
//букви сѐ додека не се внесе знак што не е мала буква. За секој пар
//последователни букви, во нов ред треба да се испечати секвенца од буквите во
//абецеден редослед што се наоѓаат меѓу нив (без нив) проследено со вкупниот
//број на вакви букви. Секогаш печатењето се почнува од буквата што се наоѓа
//понапред во азбуката кон таа што е поназад. Ако парот букви е составен од две
//соседни букви во азбуката, не се печати ништо. На крај да се испечати
//вкупниот број на испечатени секвенци од букви.

//bcjfmbX //abcdefghijklmnopqrstuvwxyz
//
//defghi 6
//ghi 3
//ghijkl 6
//cdefghijkl 10
//4

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int flag = 0, dir = 0; // 0 - 1 +
    int tot = 0;
    char prevchar;
    while (1)
    {
        int counter = 0;
        char c;
        scanf("%c", &c);
        if (c >= 'A' && c<='Z')
        {
            break;
        } else
        {
            if (flag == 0)
            {
                flag = 1;
                prevchar = c;
            } else {

                if (c > prevchar)
                {
                    dir = 1;
                } else
                {
                    dir = 0;
                }

                int dist = abs(prevchar - c);
                if (dist == 1)
                {
                    prevchar = c;
                    continue;
                }
                if (dir == 1)
                {
                    for (int k = 1; k<dist; k++)
                    {
                        printf("%c", prevchar+k);
                        counter++;
                    }
                    printf(" %d\n", counter);

                } else
                {
                    for (int k = 1; k<dist; k++)
                    {
                        printf("%c",c+k);
                        counter++;
                    }
                    printf(" %d\n", counter);
                }
                prevchar = c;
                tot++;
            }
        }
    }
    printf("%d", tot);
    return 0;
}