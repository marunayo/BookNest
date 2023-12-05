//
// Created by Dhira on 28/11/2023.
//

#ifndef library_h
#define library_h
typedef struct {
    char idMember[5];
    char userName[50];
    char Password[8];
} Member;

void displayMainMenu();

void registMember();

void displayHome();

#endif //BOOKNEST_LIBRARY_H
