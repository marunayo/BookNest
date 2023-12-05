#include <stdio.h>
#include "book.h"

void getBookCollection(book books[], int &bookTotal) {
    // Akses bookDB
    FILE *bookDB = fopen("bookDB.txt", "r");
    if (bookDB == NULL) {
        printf("Tidak dapat mengakses bookDB\n");
        return;
    }

    // Membaca data sampai akhir file (EOF)
    while (fscanf(bookDB, " '%[^']' '%[^']' '%[^']'", books[bookTotal].bookID, books[bookTotal].title, books[bookTotal].author) != EOF) {
        bookTotal++;

        // Cek agar tidak melebihi kapasitas array
        if (bookTotal >= 100) {
            printf("Batas maksimum buku tercapai\n");
            break;
        }
    }

    fclose(bookDB);
}

