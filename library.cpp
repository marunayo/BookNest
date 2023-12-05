#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

int memberCount = 1;

// Menu Modules
//void displayHome() {
//    printf("=====================================\n");
//    printf("      Selamat Datang di BookNest     \n");
//    printf("=====================================\n");
//    printf("1. Registrasi Member\n");
//    printf("2. Masuk sebagai Member\n");
//    printf("3. Keluar\n");
//    printf("=====================================\n");
//}
//
//void displayMainMenu() {
//    printf("==============================\n");
//    printf("          MAIN MENU           \n");
//    printf("==============================\n");
//    printf("1. Peminjaman Buku\n");
//    printf("2. Pengembalian Buku\n");
//    printf("3. Cari Buku\n");
//    printf("4. Keluar\n");
//    printf("==============================\n");
//}

void displayBookMenu() {
    system("cls");
    printf("=====================================\n");
    printf("              CARI BUKU              \n");
    printf("=====================================\n");
}

void displayBorrowBook() {
    system("cls");
    printf("=====================================\n");
    printf("           PEMINJAMAN BUKU           \n");
    printf("=====================================\n");
}

// User Modules
//void registMember() {
//    FILE *f_member;
//    Member member;
//
//    system("cls");
//
//    if ((f_member = fopen("memberData.txt", "ab+")) == NULL) {
//        fputs("File tidak dapat dibuka!", stderr);
//        exit(1);
//    }
//
//    printf("=====================================\n");
//    printf("       MEMBER REGISTRATION FORM      \n");
//    printf("=====================================\n");
//
//    printf("Username: ");
//    scanf(" %s", member.userName);
//    fflush(stdin);
//
//    printf("Password: ");
//    scanf("%s", member.Password);
//    fflush(stdin);
//
//    sprintf(member.idMember, "BK%i", memberCount);
//    memberCount++;
//    fflush(stdin);
//    printf("%s", member.idMember);
//
//    if (fwrite(&member, sizeof(Member), 1, f_member) != 1) {
//        printf("Error writing to the file\n");
//        fclose(f_member);
//        exit(1);
//    }
//
//    fclose(f_member);
//
//    printf("\nRegistrasi Berhasil!\n");
//    printf("Member ID kamu %s\n", member.idMember);
//}

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
