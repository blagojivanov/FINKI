#include <stdio.h>
#include <ctype.h>
#include <string.h>

int explore(char *str, char a, int n) {
    int tempct = 0;
    for (int j = 0; j < strlen(str); j++) {
        if (str[j] == a) {
            tempct++;
        }
    }
    if (tempct == n) {
        return 1;
    }
    return 0;
}

int main() {
    char a;
    int n, i = 0;
    scanf("%c\n%d", &a, &n);
    char s[80], smax[3][80];
    int ct = 0;

    while (fgets(s, 80, stdin)) {
        i++;
        if (s[0] == '#') {
            break;
        }
        int isfound = explore(s, a, n);
        if (isfound == 1) {
            ct++;

            if (strlen(s) > strlen(smax[0])) {
                strcpy(smax[2],smax[1]);
                strcpy(smax[1],smax[0]);
                strcpy(smax[0],s);
            }
            else if (strlen(s) > strlen(smax[1])){
                strcpy(smax[2],smax[1]);
                strcpy(smax[1],s);
            }
            else if (strlen(s) > strlen(smax[2])){
                strcpy(smax[2],s);
            }
        }
    }

    for (int z = 0; z<ct && z<3; z++)
    {
        printf("%s", smax[z]);
    }
}