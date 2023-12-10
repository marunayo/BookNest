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
    char status[12];
} book;

typedef struct
{
    char transactionID[10];
    char userName[50];
    char bookID[7];
    char transactionDate[11];  // Format: yyyy-mm-dd
    char dueDate[11];           // Format: yyyy-mm-dd
} transaction;

// Menu Modules
void displayMainMenu();
void displayHome();
void displayBookMenu();
void displayBorrowBook();
void displaySearchMenu();
void displaySearch();
void displayReturnBook();

// User Modules
void registMember();
bool loginMember();

// Book Modules
void getBookCollection(book books[], int &bookTotal);
void showBookCollection(book books[], int bookTotal);
int checkBorrowBook(book books[], const char *choiceBook, int bookTotal);
void doBorrowBook(char *choiceBook, char *userName);
void updateBookStatus(const char *bookID);
float calculatePenalty(int days);
void searchBook(book *matchingBooks, int *matchCount, const char *keyword);
void searchResult(book *matchingBooks, int *matchCount);
void returnBook();

#endif //BOOKNEST_LIBRARY_H
