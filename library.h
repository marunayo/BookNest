#ifndef library_h
#define library_h

typedef struct {
    char idMember[8];
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
void displayBookMenu();
void displayBorrowBook();

// User Modules
void registMember();
bool loginMember();

// Book Modules
void getBookCollection(book books[], int &bookTotal);
void showBookCollection(book books[], int bookTotal);
void checkBorrowBook(book books[], char *choiceBook, int bookTotal);
void doBorrowBook(char *choiceBook, char *userName);
float calculatePenalty(int days);
void searchBook(book *matchingBooks, int *matchCount);
void searchResult(book *matchingBooks, int *matchCount);

#endif //BOOKNEST_LIBRARY_H
