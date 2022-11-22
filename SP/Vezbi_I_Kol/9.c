/*
 * Од стандарден влез се читаат непознат број на хексадецимални цифри се додека не се внесе точка (.).
 * Ваша задача е да го пресметате декадниот збир на внесените хексадецимални цифри.
 * Доколку добиениот декаден збир е делив со 16 се печати Pogodok.
 * Доколку истиот тој збир покрај што е делив со 16 плус завршува на 16 (последните цифри му се 1 и 6), се печати Poln pogodok инаку се печати самиот збир.
 * */
#include <stdio.h>

int main() {
    char c;
    int sum = 0;
    while (1)
    {
        char spacediscard;
        c = getchar(); //A = 10 B = 11 C = 12 D = 13 E = 14 F = 15

        if (c == '.')
        {
            break;
        }
        if (c>='A' && c<='F')
        {
            sum+=(c-55);
            //printf("UC %d", c-55);
        } else if (c>='a' && c<='f')
        {
            sum+=(c-87);
            //printf("LC %d", c-87);

        } else if (c>='0' && c<='9')
        {
            sum+=(c-'0');
            //printf("NUM");

        } else
        {
            //printf("SYM");
            continue;
        }
    }
    if (sum % 16 == 0 && (sum%10 == 6 && sum/10%10 == 1))
    {
        printf("Poln pogodok");
    } else if (sum % 16 == 0)
    {
        printf("Pogodok");
    } else
    {
        printf("%d", sum);
    }


    return 0;
}