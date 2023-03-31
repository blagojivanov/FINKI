//Во програмскиот јазик C да се креира структура Книга за која се чува името на книгата (низа од карактери), ISBN (низа од карактери), број на луѓе кои ја имаат прочитано книгата и рејтинг на книгата.
//
//Потоа да се дефинира структура Автор за која се чува името на авторот (низа од карактери), презиме (низа од карактери), број на книги што ги има напишано и низа од книги што ги има напишано.
//
//Да се надополни main функцијата така што ќе се прочитаат n автори заедно со книгите што ги имаат напишано.
//
//Потребно е да се креираат две функции:
//
//- void mostPopularAuthor(author authors[100], int n) која на екран ќе испечати Most popular author: ИМЕ
//
//- void mostPopularBookByAuthor(author authors[100], int n) која на екран ќе ја испечати најпопуларната книга на авторот кој има напишано најмалку книги во формат Author: ИМЕ ПРЕЗИМЕ, Most popular book: ИМЕ, ISBN на книгата
//
//        Напомена: најпопуларна книга е онаа со најголем рејтинг, најпопуларен автор е оној чии книги ги прочитале најголем број луѓе
#include <stdio.h>

typedef struct Book {
    char name[100];
    char ISBN[100];
    int number;
    float rating;
} Book;

typedef struct Author {

    char name[50];
    char surname[50];
    int numberOfBooks;
    Book books[20];

} author;

void mostPopularAuthor(author authors[100], int n) {
    int i, j, f = 0;
    int readMax, readMaxId;
    for (i=0; i < n; i++) {
        int readBy = 0;
        for (j=0; j < authors[i].numberOfBooks; j++) {
            readBy += authors[i].books[j].number;
        }
        if (f == 0) {
            f = 1;
            readMax = readBy;
            readMaxId = i;
        }
        if (readMax < readBy) {
            readMax = readBy;
            readMaxId = i;
        }
    }
    printf("Most popular author: %s %s\n", authors[readMaxId].name, authors[readMaxId].surname);
}

void mostPopularBookByAuthor(author authors[100], int n) {
    int i, popularAuthorId, popularBookId;
    author min = authors[0];
    float popular = 0;
    int leastBooks = authors[0].numberOfBooks;
    for (i = 0; i<n; i++)
    {
        if (authors[i].numberOfBooks < min.numberOfBooks)
        {
            min = authors[i];
            popularAuthorId = i;
        }
    }
    Book minb = min.books[0];
    for (i = 0; i < min.numberOfBooks; i++)
    {
        if (minb.rating < min.books[i].rating)
        {
            minb = min.books[i];
        }
    }

    printf("Author: %s %s, ", min.name, min.surname);
    printf("Most popular book: %s, %s", minb.name, minb.ISBN);
}

int main()
{
    int n, i, j;
    scanf("%d", &n);
    author authors[100];

    for (i = 0; i<n; i++)
    {
        scanf("%s %s", authors[i].name, authors[i].surname);
        scanf("%d", &authors[i].numberOfBooks);
        for (j = 0; j<authors[i].numberOfBooks;j++)
        {
            scanf("%s", authors[i].books[j].name);
            scanf("%s", authors[i].books[j].ISBN);
            scanf("%d", &authors[i].books[j].number);
            scanf("%f", &authors[i].books[j].rating);
        }
    }
    //dopolni
    mostPopularAuthor(authors, n);
    mostPopularBookByAuthor(authors, n);
    return 0;
}
