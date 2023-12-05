#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int main() {
    book books[100];
    int choice;
    char menu;

    int bookTotal = 0;

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
                    displayMainMenu();
                } else {
                    printf("Login gagal. Silahkan coba lagi atau kembali ke menu utama.\n");
                }
                break;
            case 3:
                showBookCollection(books, bookTotal);
                break;
            case 4:
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

