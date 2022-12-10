//Да се напише рекурзивна функција која ќе го најде бројот на позитивни броеви од целобројна низа.
//Функцијата како аргумент ја прима низата, за која се бара бројот на позитивни броеви и вкупниот број на елементи, кои ги има таа низа.
//Функцијата е зададена со следниот прототип:
//int BrojPozitivni(int niza[], int n);
//Да се напише и функција main() за тестирање на функцијата BrojPozitivni.
//ЗАБЕЛЕШКА (од мене): читањето на елементите може и без функција, направена е функција само за проба.
#include <stdio.h>
int brpoz=0;
int BrojPozitivni(int niza[], int n);
void getArray(int *arr, int size)
{
    for (int i = 0; i < size; ++i) {
        scanf("%d", arr+i);
    }
}

int main() {
    int br;
    scanf("%d", &br);
    int a[br];
    getArray(a, br);
    printf("%d", BrojPozitivni(a,br));

}
int BrojPozitivni(int niza[], int n)
{
    if (niza[n-1] >=0) brpoz++;
    return (n>0) ? BrojPozitivni(niza, n-1) : brpoz-1;
}