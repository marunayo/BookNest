#include <stdio.h>
#include "library.h"

int main() {
    book books[100]; // Misalnya, batasi jumlah maksimum buku
    int choice;
    char choiceBook[7];
    int bookTotal = 0;

    displayHome();
    getBookCollection(books, bookTotal);
    printf("Silahkan pilih opsi 1-3: ");
    scanf(" %d", &choice);

    switch (choice) {
        case 1:
            registMember();
            break;
        case 2:
            displayMainMenu();
            printf("Silahkan pilih opsi 1-3: ");
            scanf(" %d", &choice);

            switch (choice)
            {
            case 1:
                displayBorrowBook();
                showBookCollection(books, bookTotal);
                printf("=====================================\n");
                printf("Masukan ID buku untuk meminjam: ");
                scanf(" %6s", choiceBook);

                checkBorrowBook(books, choiceBook, bookTotal);
                break;
            case 2:
                break;
            case 3:
                displayBookMenu();
                showBookCollection(books, bookTotal);
                break;
            default:
                break;
            }
            break;
        case 3:
            break;
        default:
            printf("Pilihan anda tidak valid, silahkan pilih 1-3");
            break;
    }

    return 0;
}