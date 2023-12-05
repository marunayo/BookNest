#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int main() {
    Member member[10];
    book books[100]; // Misalnya, batasi jumlah maksimum buku
    int choice;
    char choiceBook[7];
    int bookTotal = 0;
    char menu;
    char userName[10] = "Raihan";

    displayHome();
    getBookCollection(books, bookTotal);
    printf("Silahkan pilih opsi 1-3: ");
    scanf(" %d", &choice);

    switch (choice) {
        case 1:
            registMember();
            break;
        case 2:
            if (loginMember()) {
                displayMainMenu();
                do {
                    displayMainMenu();
                    printf("Silahkan pilih opsi 1-4: ");
                    scanf(" %d", &choice);

                    switch (choice) {
                        case 1:
                            displayBorrowBook();
                            showBookCollection(books, bookTotal);
                            printf("=====================================\n");
                            printf("Masukan ID buku untuk meminjam: ");
                            scanf(" %6s", choiceBook);

                            checkBorrowBook(books, choiceBook, bookTotal);
                            // printf("\n %s", member[0].userName);
                            doBorrowBook(choiceBook, userName);
                            break;
                        case 2:
                            break;
                        case 3:
                            searchBook();
                            break;
                        case 4:
                            exit(0);
                        default:
                            printf("Pilihan anda tidak valid, silahkan pilih 1-4\n");
                    }

                    printf("Kembali ke menu utama? (Y/N): ");
                    scanf(" %c", &menu);
                } while (menu == 'Y' || menu == 'y');
            } else {
                printf("Login gagal. Silahkan coba lagi atau kembali ke menu utama.\n");
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