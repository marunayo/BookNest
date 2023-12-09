#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "library.h"

int memberCount = 1;

// Book Modules
void getBookCollection(book books[], int &bookTotal) {
    // Akses bookDB
    FILE *bookDB = fopen("bookDB.txt", "r");
    if (bookDB == NULL) {
        printf("Tidak dapat mengakses bookDB\n");
        return;
    }

    // Membaca data sampai akhir file (EOF)
    while (fscanf(bookDB, " '%[^']' '%[^']' '%[^']' '%c'", books[bookTotal].bookID, books[bookTotal].title, books[bookTotal].author, &books[bookTotal].status) != EOF) {
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
        if (books[i].status == '1') {
            printf("Status\t: Tersedia");
        } else {
            printf("Status\t: Tidak Tersedia");
        }
        printf("\n");
    }
}

void checkBorrowBook(book books[], char *choiceBook, int bookTotal) {
    // Checking if the bookID exist in DB
    for (int i = 0; i < bookTotal; i++) {
        if (strcmp(choiceBook, books[i].bookID) == 0) {
            printf("Buku tersedia :D");
            printf("\n %c", books->status);
            if (books[i].status == '0') {
                printf("\n Buku sudah terpinjam");
                exit(0);
            }
        }
    }
}

void doBorrowBook(char *choiceBook, char *userName) {
    FILE *ft;
    FILE *ft_user;
    FILE *bookDB = fopen("bookDB.txt", "r");
    char transactionID[10];

    if ((ft = fopen("transactions.txt", "a+")) == NULL) {
        fputs("File tidak dapat dibuka!", stderr);
        exit(1);
    }

    // Mendapatkan tanggal transaksi
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    char transactionDate[11];
    strftime(transactionDate, 11, "%d-%m-%Y", tm_info);

    // Mendapatkan tanggal jatuh tempo (5 hari setelah tanggal transaksi)
    struct tm tm_due = *tm_info;
    tm_due.tm_mday += 5;  // Menambah 5 hari
    time_t due_t = mktime(&tm_due);
    char dueDate[11];
    strftime(dueDate, 11, "%d-%m-%Y", localtime(&due_t));

    sprintf(transactionID, "TRBK%05i", rand() % 100000);
    fflush(stdin);

    fprintf(ft, "%s %s %s %s %s\n", transactionID, userName, choiceBook, transactionDate, dueDate);

    fclose(ft);

    printf("\nPinjam Buku Berhasil!\n");
    printf("Transaction ID pinjam buku kamu %s\n", transactionID);
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
    printf("        Hasil Pencarian Anda        \n");
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