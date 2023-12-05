#ifndef book_h
#define book_h

typedef struct
{
    char bookID[7];
    char title[50];
    char author[50];
} book;

void getBookCollection(book books[], int &bookTotal);

#endif
