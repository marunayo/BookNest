#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "library.h"

bool checkPassword(char *password) {
    int i, length, digit_count, lower_case_count, upper_case_count;

    length = strlen(password);

    digit_count = 0;
    lower_case_count = 0;
    upper_case_count = 0;

    // check uppercase, lowercase, and number
    for (i = 0; i < length; i++) {
        if (password[i] >= 'a' && password[i] <= 'z') ++lower_case_count;
        if (password[i] >= 'A' && password[i] <= 'Z') ++upper_case_count;
        if (password[i] >= '0' && password[i] <= '9') ++digit_count;
    }

    if (length >= 8 && lower_case_count > 0 && upper_case_count > 0 && digit_count > 0) {
        return true;
    } else {
        return false;
    }
}


void registMember() {
    FILE *f_member;
    Member member, f_members;
    bool usernameExists;

    system("cls");

    if ((f_member = fopen("memberData.txt", "a+")) == NULL) {
        fputs("File tidak dapat dibuka!", stderr);
        exit(1);
    }

    for (;;) {
        printf("=====================================\n");
        printf("      Registrasi Member BookNest     \n");
        printf("=====================================\n");

        printf("Username: ");
        scanf(" %s", member.userName);
        fflush(stdin);

        printf("Password (panjang 1-8 karakter, minimal 1 kapital, 1 kecil, dan 1 angka): ");

        scanf(" %s", member.Password);
        while (getchar() != '\n');

        srand ( time(NULL) );
        sprintf(member.idMember, "BK%i", rand() %100);

        if(checkPassword(member.Password)) {
            fseek(f_member, 0, SEEK_SET);

            usernameExists = false;

            while (fscanf(f_member, " %s %s %s", f_members.idMember, f_members.userName, f_members.Password) != EOF) {
                if (strcmp(f_members.userName, member.userName) == 0) {
                    printf("\nUsername sudah ada!\n");
                    usernameExists = true;
                    break;
                }
            }

            if (!usernameExists) {
                fprintf(f_member, "%s %s %s\n", member.idMember, member.userName, member.Password);
                printf("\nRegistrasi Berhasil!\n");
                printf("Member ID kamu %s\n", member.idMember);
                break;
            }

        } else {
            printf("Password tidak valid. Pastikan memenuhi aturan kompleksitas.\n");
            break;
        }
    }

    fclose(f_member);
}


bool loginMember() {
    FILE *f_member;
    Member member, input;
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
        scanf(" %s", input.userName);
        while (getchar() != '\n');
        printf("Password: ");
        scanf(" %s", input.Password);
        while (getchar() != '\n');

        found = false;

        rewind(f_member);

        while (fscanf(f_member, " %s %s %s", member.idMember, member.userName, member.Password) != EOF) {
            if (strcmp(input.userName, member.userName) == 0 && strcmp(input.Password, member.Password) == 0) {
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
