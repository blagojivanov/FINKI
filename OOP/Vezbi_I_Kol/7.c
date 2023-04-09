//Во програмскиот јазик C да се креира структура Vozenje за опишување на адреналински возења во забавен парк. Структурата треба да содржи: (5 поени)
//
//Име на возењето ( низа од 100 знаци)
//Времетраење во минути (цел број)
//Цена (децимален број)
//Дали има студентски попуст (1-да, 0-не)
//Да се креира структура ZabavenPark, што содржи: (10 поени)
//
//Име на забавниот парк (низа од 100 знаци)
//Локација (низа од 100 знаци)
//Низа од адреналински возења во паркот (низа од максимум 100 елементи од структурата Vozenje)
//Број на елементи во низата (цел број)
//Да се креира функција print за печатење на информациите за сите возења во забавниот парк во формат: (10 поени)
//
//[Ime na parkot] [Lokacija]
//[Ime1] [Vremetraenje1] [Cena1]
//[Ime2] [Vremetraenje2] [Cena2]
//[Ime3] [Vremetraenje3] [Cena3]
//...
//Да се креира функција najdobar_park, што прима низа од променливи од типот ZabavenPark и го печати името и локацијата на паркот кој е најефтин за посета од страна на студенти. Најефтин парк е оној што содржи најголем број возења со студентски попуст. Ако повеќе паркови ги делат овие карактеристики, да се испечати паркот со најголемото времетраење од сите возења.* (20 поени)*
//
//Да се дополни функцијата main (5 поени).

#include <stdio.h>
#include <string.h>

typedef struct Vozenje
{
    char name[20];
    int duration;
    float price;
    int studpop;
} Vozenje;

typedef struct ZabavenPark
{
    char name[20];
    char location[30];
    Vozenje vozenja[20];
    int n;
}ZabavenPark;


void print(ZabavenPark *park, int n)
{
    int i, j;
    for (i = 0; i<n; i++)
    {
        printf("%s %s\n", park[i].name, park[i].location);
        for (j = 0; j<park[i].n; j++)
        {
            printf("%s %d %.2f\n", park[i].vozenja[j].name, park[i].vozenja[j].duration, park[i].vozenja[j].price);
        }
    }

}

void najdobar_park(ZabavenPark niza[], int n)
{
    int i, j, vozstudpop = 0, vozvrempop = 0;
    ZabavenPark najdobar = niza[0];
    for (i = 0; i<n; i++)
    {
        int vozstud = 0, vozvrem = 0;
        for (j = 0; j<niza[i].n; j++)
        {
            vozvrem+=niza[i].vozenja[j].duration;
            if (niza[i].vozenja[j].studpop == 1)
            {
                vozstud++;
            }
        }
        if (vozstud > vozstudpop)
        {
            vozvrempop = vozvrem;
            vozstudpop = vozstud;
            najdobar = niza[i];
        } else if (vozstud == vozstudpop)
        {
            if (vozvrem > vozvrempop)
            {
                najdobar = niza[i];
            }
        }
    }

    printf("Najdobar park: %s %s", najdobar.name, najdobar.location);

}

int main()
{

    int n, i,j;
    ZabavenPark parkovi[20];
    scanf("%d", &n);
    for (i = 0; i<n; i++)
    {
        scanf("%s %s %d", parkovi[i].name, parkovi[i].location, &parkovi[i].n);
        for (j = 0; j<parkovi[i].n; j++)
        {
            scanf("%s %d %f %d", parkovi[i].vozenja[j].name, &parkovi[i].vozenja[j].duration, &parkovi[i].vozenja[j].price, &parkovi[i].vozenja[j].studpop);
        }
    }
    print(parkovi, n);
    najdobar_park(parkovi, n);
    return 0;
}