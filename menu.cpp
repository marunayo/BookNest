#include <stdio.h>
#include <stdlib.h>
#include "library.h"

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
	system("cls");
    printf("==============================\n");
    printf("          MAIN MENU           \n");
    printf("==============================\n");
    printf("1. Peminjaman Buku\n");
    printf("2. Pengembalian Buku\n");
    printf("3. Cari Buku\n");
    printf("4. Lihat semua koleksi\n");
    printf("5. Keluar\n");
    printf("==============================\n");
}

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

void displaySearchMenu() {
    system("cls");
    printf("=====================================\n");
    printf("        Cari Koleksi BookNest        \n");
    printf("=====================================\n");
}

void displaySearch() {
    system("cls");
    printf("=====================================\n");
    printf("           HASIL PENCARIAN           \n");
    printf("=====================================\n");
}