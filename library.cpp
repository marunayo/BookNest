#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "library.h"

int memberCount = 1;

void displayBookMenu() {
    printf("=====================================\n");
    printf("              CARI BUKU              \n");
    printf("=====================================\n");

    printf("=====================================\n");
}

void displayBorrowBook() {
    system("cls");
    printf("=====================================\n");
    printf("           PEMINJAMAN BUKU           \n");
    printf("=====================================\n");
}

void doBorrowBook(char *choiceBook, char *userName) {
    FILE *ft;
    FILE *ft_user;
    char transactionID[10];

    if ((ft = fopen("transactions.txt", "a+")) == NULL) {
        fputs("File tidak dapat dibuka!", stderr);
        exit(1);
    }
    // if ((ft_user = fopen("tramsactions.txt", "a+")) == NULL) {
    //     fputs("File tidak dapat dibuka!", stderr);
    //     exit(1);
    // }


    sprintf(transactionID, "TRBK%05i", rand() % 100000);
    fflush(stdin);
    
	fprintf(ft, "%s %s %s\n", transactionID, userName, choiceBook);
	
    fclose(ft);

    printf("\nPinjam Buku Berhasil!\n");
    printf("Transaction ID pinjam buku kamu %s\n", transactionID);
}

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

void checkBorrowBook(book books[], char *choiceBook, int bookTotal) {
    // Checking if the bookID exist in DB
    for (int i = 0; i < bookTotal; i++) {
        if (strcmp(choiceBook, books[i].bookID) == 0) {
            printf("Buku tersedia :D");
            return;
        } 
    }

    printf("Maaf, Buku kamu tidak tersedia :(");
}

int containsIgnoreCase(const char *data, const char *keyword) {
    while (*data && *keyword) {
        if (tolower((unsigned char)*data) != tolower((unsigned char)*keyword)) {
            return 0; 
        }
        data++;
        keyword++;
    }

    return (*keyword == '\0');  
}

void searchBook(book *matchingBooks, int *matchCount) {
    char keyword[50];
    FILE *bookDB;
    book Book;

    system("cls");

    bookDB = fopen("bookDB.txt", "r");
    if (bookDB == NULL) {
        printf("Tidak dapat mengakses koleksi\n");
        return;
    }

    printf("=====================================\n");
    printf("        Cari Koleksi BookNest        \n");
    printf("=====================================\n");
    printf("Masukkan kata kunci pencarian: ");
    scanf(" %s", keyword);
    fflush(stdin);

    while (fscanf(bookDB, " '%[^']' '%[^']' '%[^']'", Book.bookID, Book.title, Book.author) != EOF) {
        printf("Processing Book: ID=%s, Title=%s, Author=%s\n", Book.bookID, Book.title, Book.author);
        if (containsIgnoreCase(Book.bookID, keyword) ||
            containsIgnoreCase(Book.title, keyword) ||
            containsIgnoreCase(Book.author, keyword)) {
            strcpy(matchingBooks[*matchCount].bookID, Book.bookID);
            strcpy(matchingBooks[*matchCount].title, Book.title);
            strcpy(matchingBooks[*matchCount].author, Book.author);
            (*matchCount)++;
        }
    }
    fclose(bookDB);
}

void searchResult(book *matchingBooks, int *matchCount) {
    system("cls");
    printf("=====================================\n");
    printf("        Hasil Pencarian Anda        \n");
    printf("=====================================\n");
    for (int i = 0; i < *matchCount; i++) {
        printf("Book ID: %s\n", matchingBooks[i].bookID);
        printf("Title: %s\n", matchingBooks[i].title);
        printf("Author: %s\n", matchingBooks[i].author);
        printf("=====================================\n");
    }
}

float calculatePenalty(int days) {
	int i;
	for(i = 0; i <= days; i++) {
		return 1000 * i;
	}
}

