#include <stdio.h>
#include "book.h"

int main() {
    book books[100]; // Misalnya, batasi jumlah maksimum buku
    int bookTotal = 0;

    // Panggil fungsi getBookCollection
    getBookCollection(books, bookTotal);

    // Menampilkan data yang telah disimpan dalam array of struct
    for (int i = 0; i < bookTotal; i++) {
        printf("Buku %d:\n", i + 1);
        printf("ID\t: %s\n", books[i].bookID);
        printf("Judul\t: %s\n", books[i].title);
        printf("Penulis\t: %s\n", books[i].author);
        printf("\n");
    }

    return 0;
}

