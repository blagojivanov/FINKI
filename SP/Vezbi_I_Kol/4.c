/*
 * Од стандарден влез се читаат знаци се додека не се прочита извичник.
 * Во вака внесениот текст се скриени цели броеви (помали од 100).
 * Да се напише програма што ќе ги прочита сите знаци и на излез ќе го испечати збирот на сите броеви скриени во текстот.
 * */


#include <stdio.h>

int main() {
    char b;
    int zbir=0,privzbir = 0;
    while (b!='!') {
        scanf("%c", &b);
        if (b>='0' && b<='9')
        {
            if (privzbir == 0){
                privzbir += (int) b - '0';
            } else{
                privzbir *= 10;
                privzbir += (int) b - '0';
                zbir += privzbir;
                privzbir = 0;
            }
        } else if (privzbir != 0)
        {
            zbir += privzbir;
            privzbir = 0;
        }
    }
    printf("%d", zbir);
    return 0;
}

/*
 * TEST SLUCAI
 * ako34D neka12em bashka41mewr20! - 107
 * 1ako fdsfsfD ne 12 ka10em bashka10mewr5! - 38
 * Weiur23j sdlkj22lkadad 21kjs 20sdkjsd! - 86
 * ako34D neka12em bashka41mewr! - 87
 * ako3 1 4D4 ne 88 ka12em ba12shka41mewr! - 165
 * 9Ako D1me ima 12 evra, za 9 dena, kje kupi 10ka! - 41
 * */
