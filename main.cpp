#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int main() {
    book books[100], *Book = NULL;
    int choice, matchCount, bookTotal = 0;
    char menu, choiceBook[7];

    for (;;) {
        system("cls");

        displayHome();
        printf("Silahkan pilih opsi 1-3: ");
        scanf(" %d", &choice);

        switch (choice) {
            case 1:
                registMember();
                break;
            case 2:
                if (loginMember()) {
                    do {
                        displayMainMenu();
                        printf("Silahkan pilih opsi 1-4: ");
                        scanf(" %d", &choice);

                        switch (choice) {
                            case 1:
                                break;
                            case 2:
                                break;
                            case 3:
                                Book = (book *)calloc(100, sizeof(book)); 
                                matchCount = 0;
                                searchBook(Book, &matchCount);
                                if (matchCount > 0) {
                                    searchResult(Book, &matchCount);
                                } else {
                                    printf("Hasil pencarian tidak ditemukan.\n");
                                }
                                free(Book);       
                                break;
                            case 4:
                                displayBookMenu();
                                showBookCollection(books, bookTotal);
                                break;
                            case 5:
                                exit(0);
                            default:
                                printf("Pilihan anda tidak valid, silahkan pilih 1-4\n");
                        }

                        printf("Kembali ke menu utama? (Y/N): ");
                        scanf(" %c", &menu);
                    } while (menu == 'Y' || menu == 'y');
                } else {
                    system("cls");
                    printf("Login gagal. Silahkan coba lagi atau kembali ke menu utama.\n");
                }
                break;
            case 3:
                exit(0);
            default:
                printf("Pilihan anda tidak valid, silahkan pilih 1-3\n");
                break;
        }

        printf("Kembali ke menu? (Y/N) \n");
        scanf(" %c", &menu);

        if (menu != 'Y' && menu != 'y') {
            break;
        }
    }

    printf("Terima kasih telah menggunakan program ini. Selamat tinggal!\n");
    return 0;
}
