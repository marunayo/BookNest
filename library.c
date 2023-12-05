//
// Created by Dhira on 28/11/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int memberCount = 1;

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

