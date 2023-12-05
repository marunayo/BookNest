#include <stdio.h>
#include "library.h"

int main() {
    book books[100]; // Misalnya, batasi jumlah maksimum buku
    int choice;
    int bookTotal = 0;

    // Panggil fungsi getBookCollection
    getBookCollection(books, bookTotal);

    // Menampilkan data yang telah disimpan dalam array of struct
    showBookCollection(books, bookTotal);

    displayHome();
    printf("Silahkan pilih opsi 1-3: ");
    scanf(" %d", &choice);

    switch (choice) {
        case 1:
            registMember();
            break;
        case 2:
            displayMainMenu();
            break;
        case 3:
            showBookCollection(books, bookTotal);
            break;
        default:
            printf("Pilihan anda tidak valid, silahkan pilih 1-3");
            break;
    }

    return 0;
}