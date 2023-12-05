#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

// Book Modules
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

void showBookCollection(book books[], int bookTotal) {
	for (int i = 0; i < bookTotal; i++) {
        printf("Buku %d:\n", i + 1);
        printf("ID\t: %s\n", books[i].bookID);
        printf("Judul\t: %s\n", books[i].title);
        printf("Penulis\t: %s\n", books[i].author);
        printf("\n");
    }
}

void searchBook() {
    char keyword[50];
    FILE *bookDB;
    book Book;
    book *matchingBooks;
    int matchCount;

    system("cls");

    bookDB = fopen("bookDB.txt", "r");
    if (bookDB == NULL) {
        printf("Tidak dapat mengakses koleksi\n");
        return;
    }

    printf("=====================================\n");
    printf("       ~Cari Koleksi BookNest~       \n");
    printf("=====================================\n");
    printf("Masukkan kata kunci pencarian: ");
    scanf(" %s", keyword);
    fflush(stdin);

    matchingBooks = (book *)calloc(100, sizeof(book));  // Adjust the size as needed
    matchCount = 0;

    while (fscanf(bookDB, " '%[^']' '%[^']' '%[^']'", Book.bookID, Book.title, Book.author) != EOF) {
        if (strstr(keyword, Book.bookID) != NULL || strstr(keyword, Book.author) != NULL || strstr(keyword, Book.title) != NULL) {
            strcpy(matchingBooks[matchCount].bookID, Book.bookID);
            strcpy(matchingBooks[matchCount].title, Book.title);
            strcpy(matchingBooks[matchCount].author, Book.author);
            matchCount++;
        }
    }

    fclose(bookDB);

    printf("=====================================\n");
    printf("       ~Hasil Pencarian Anda~       \n");
    printf("=====================================\n");
    for (int i = 0; i < matchCount; i++) {
        system("cls");
        printf("Book ID: %s\n", matchingBooks[i].bookID);
        printf("Title: %s\n", matchingBooks[i].title);
        printf("Author: %s\n", matchingBooks[i].author);
        printf("=====================================\n");
    }

    free(matchingBooks);
}

float calculatePenalty(int days) {
	int i;
	for(i = 0; i <= days; i++) {
		return 1000 * i;
	}
}

