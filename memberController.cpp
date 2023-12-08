#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void registMember() {
    FILE *f_member;
    Member member;

    system("cls");

    if ((f_member = fopen("memberData.txt", "a+")) == NULL) {
        fputs("File tidak dapat dibuka!", stderr);
        exit(1);
    }

    printf("=====================================\n");
    printf("      Registrasi Member BookNest     \n");
    printf("=====================================\n");

    printf("Username: ");
    scanf(" %s", member.userName);
    fflush(stdin);

    printf("Password: ");
    scanf("%s", member.Password);
    fflush(stdin);

    sprintf(member.idMember, "BK%i", rand());
    fflush(stdin);
    printf("%s", member.idMember);
    
	fprintf(f_member, "%s %s %s\n", member.idMember, member.userName, member.Password);
	
    fclose(f_member);

    printf("\nRegistrasi Berhasil!\n");
    printf("Member ID kamu %s\n", member.idMember);

}

bool loginMember() {
    char username[50], password[8];
    FILE *f_member;
    Member member;
    bool found;

    if ((f_member = fopen("memberData.txt", "r")) == NULL) {
        fputs("File tidak dapat dibuka!", stderr);
        exit(1);
    }

    for (;;) {
        system("cls");

        printf("=====================================\n");
        printf("           Masuk ke BookNest         \n");
        printf("=====================================\n");
        printf("Username: ");
        scanf(" %s", username);
        while (getchar() != '\n');
        printf("Password: ");
        scanf(" %s", password);
        while (getchar() != '\n');

        found = false;

        rewind(f_member);

        while (fscanf(f_member, " %s %s %s", member.idMember, member.userName, member.Password) != EOF) {
            if (strcmp(username, member.userName) == 0 && strcmp(password, member.Password) == 0) {
                printf("\nBerhasil masuk!\n");
                found = true;
                break;
            }
        }

        if (found) {
            break;
        } else {
            printf("\nTerjadi kesalahan\nTolong periksa inputan anda!\n");

            char choice;
            printf("Apakah Anda ingin mencoba lagi? (Y/N): ");
            scanf(" %c", &choice);

            if (choice != 'Y' && choice != 'y') {
                break;
            }
        }
    }

    fclose(f_member);

    return found;
}
