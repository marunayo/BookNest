#ifndef library_h
#define library_h

typedef struct {
    char idMember[5];
    char userName[50];
    char Password[8];
} Member;

typedef struct
{
    char bookID[7];
    char title[50];
    char author[50];
} book;

// Menu Modules
void displayMainMenu();
void displayHome();

// User Modules
void registMember();

// Book Modules
void getBookCollection(book books[], int &bookTotal);
void showBookCollection(book books[], int bookTotal);

#endif //BOOKNEST_LIBRARY_H