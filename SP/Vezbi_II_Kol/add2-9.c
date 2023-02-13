//Од стандарден влез се внесуваат непознат број на реченици претставени преку текстуални низи (стрингови)
//секоја не подолга од 100 знаци и секоја во нов ред.
//Програмата треба да го најде стрингот кој содржи најмногу сврзници и да го испечати заедно со бројот на најдените сврзници.
//За сврзници се сметаат сите зборови составени од една, две или три букви.
//Зборовите во текстуалната низа се одделени со едно или повеќе прзани места и/или интерпункциски знак.
//Броењето на сврзници во дадена текстуална низа треба да се реализира во посебна функција.
//Решенијата без користење функција ќе бидат оценети со најмногу 40% од поените.
//Ако има повеќе реченици со ист максимален број на сврзници, се печати прво најдената.
//Објаснување на тест примерот:
//Бројот на сврзници по реченици е 2, 3, 4, 2, 4 и 7 соодветно.
// Најмногу сврзници има по последната реченица па се печати бројот 7 и содржината на таа реченица.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int svrznici(char *str)
{
    int ct = 0, tempct = 0;
    for (int i = 0; i< strlen(str); i++)
    {
        if (isalpha(*(str+i)))
        {
            tempct++;
        } else
        {
            if (tempct <=3 && tempct > 0)
            {
                ct++;
            }
            tempct = 0;
        }
    }
    return ct;
}

int main()
{
    char str[100][100];
    int br[100], max = 0, max_pos = 0, i=0;;
    while (fgets(str[i],100,stdin))
    {
        br[i] = svrznici(str[i]);
        if (br[i] > max)
        {
            max_pos = i;
            max = br[i];
        }
        i++;
//        printf("%d", svrznici(str[i]));
    }
    printf("%d: %s", br[max_pos], str[max_pos]);
    return 0;
}