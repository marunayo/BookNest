#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int memberCount = 1;

// Menu Modules
void displayHome() {
    printf("=====================================\n");
    printf("      Selamat Datang di BookNest     \n");
    printf("=====================================\n");
    printf("1. Registrasi Member\n");
    printf("2. Masuk sebagai Member\n");
    printf("3. Keluar\n");
    printf("=====================================\n");
}

void displayMainMenu() {
    printf("==============================\n");
    printf("          MAIN MENU           \n");
    printf("==============================\n");
    printf("1. Peminjaman Buku\n");
    printf("2. Pengembalian Buku\n");
    printf("3. Cari Buku\n");
    printf("4. Keluar\n");
    printf("==============================\n");
}

void displayBook() {
    printf("=====================================\n");
    printf("              CARI BUKU              \n");
    printf("=====================================\n");

    printf("=====================================\n");
}

// User Modules
void registMember() {
    FILE *f_member;
    Member member;

    system("cls");

    if ((f_member = fopen("memberData.txt", "ab+")) == NULL) {
        fputs("File tidak dapat dibuka!", stderr);
        exit(1);
    }

    printf("=====================================\n");
    printf("       MEMBER REGISTRATION FORM      \n");
    printf("=====================================\n");

    printf("Username: ");
    scanf(" %s", member.userName);
    fflush(stdin);

    printf("Password: ");
    scanf("%s", member.Password);
    fflush(stdin);

    sprintf(member.idMember, "BK%i", memberCount);
    memberCount++;
    fflush(stdin);
    printf("%s", member.idMember);

    if (fwrite(&member, sizeof(Member), 1, f_member) != 1) {
        printf("Error writing to the file\n");
        fclose(f_member);
        exit(1);
    }

    fclose(f_member);

    printf("\nRegistrasi Berhasil!\n");
    printf("Member ID kamu %s\n", member.idMember);
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
