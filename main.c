//
// Created by Dhira on 28/11/2023.
//

#include <stdio.h>
#include "library.h"

int main() {
    int choice;

    displayHome();
    printf("Silahkan pilih opsi 1-3: ");
    scanf(" %d", &choice);

    switch (choice) {
        case 1:
            registMember();
            break;
        case 2:
            displayMainMenu();
            break;
        case 3:
            break;
        default:
            printf("Pilihan anda tidak valid, silahkan pilih 1-3");
            break;
    }

    return 0;
}
