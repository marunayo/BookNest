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
    printf("4. Keluar\n");
    printf("==============================\n");
}