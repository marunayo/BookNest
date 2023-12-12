#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "library.h"

// Book Modules
void getBookCollection(book books[], int &bookTotal) {
    // Akses bookDB
    FILE *bookDB = fopen("bookDB.txt", "r");
    if (bookDB == NULL) {
        printf("Tidak dapat mengakses bookDB\n");
        return;
    }

    // Membaca data sampai akhir file (EOF)
    while (fscanf(bookDB, " '%[^']' '%[^']' '%[^']' '%[^']' ", books[bookTotal].bookID, books[bookTotal].title, books[bookTotal].author, books[bookTotal].status) != EOF) {
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
        if (strcmp(books[i].status, "Status 0") == 0) {
            printf("Status\t: Tidak Tersedia");
        } else {
            printf("Status\t: Tersedia");
        }
        printf("\n");
    }
}

int checkBorrowBook(book books[], const char *choiceBook, int bookTotal) {
    for (int i = 0; i < bookTotal; i++) {
        if (strcmp(choiceBook, books[i].bookID) == 0) {
            if (strcmp(books[i].status, "Status 0") == 0) {
                printf("\n Buku sudah terpinjam \n");
                return 0;
            } else {
                return 1;
            }
        }
    }
    printf("\n Buku tidak ditemukan\n");
    return 0;
}

void doBorrowBook(char *choiceBook, char *userName) {
    FILE *ft;
    FILE *ft_user;
    FILE *bookDB = fopen("bookDB.txt", "r");
    char transactionID[10];

    if ((ft = fopen("transactions.txt", "a+")) == NULL) {
        fputs("File tidak dapat dibuka!", stderr);
        exit(1);
    }

    // Mendapatkan tanggal transaksi
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    char transactionDate[11];
    strftime(transactionDate, 11, "%d-%m-%Y", tm_info);

    // Mendapatkan tanggal jatuh tempo (5 hari setelah tanggal transaksi)
    struct tm tm_due = *tm_info;
    tm_due.tm_mday += 5;  // Menambah 5 hari
    time_t due_t = mktime(&tm_due);
    char dueDate[11];
    strftime(dueDate, 11, "%d-%m-%Y", localtime(&due_t));

	srand((unsigned int)time(NULL));
    sprintf(transactionID, "TRBK%05i", rand() %100000);
    fflush(stdin);

    fprintf(ft, "%s %s %s %s %s\n", transactionID, userName, choiceBook, transactionDate, dueDate);

    fclose(ft);

    srand((unsigned int)time(NULL));
    printf("\nPinjam Buku Berhasil!\n");
    printf("Transaction ID pinjam buku kamu %s\n", transactionID);
}

void updateBookStatus(book books[], int bookTotal, const char *bookID) {
    FILE *file = fopen("bookDB.txt", "r+");

    if (file == NULL) {
        fputs("File tidak dapat dibuka!", stderr);
        exit(1);
    }

    book currentBook;
    long currentPosition = 0;
    while (fscanf(file, " '%6[^']' '%49[^']' '%49[^']' '%11[^']' ", currentBook.bookID, currentBook.title, currentBook.author, currentBook.status) == 4) {
        if (strcmp(currentBook.bookID, bookID) == 0) {
            fseek(file, currentPosition + (strlen(currentBook.bookID) + strlen(currentBook.title) + strlen(currentBook.author) + 10), SEEK_SET);
            fprintf(file, "Status 0");
            break;
        }
        currentPosition = ftell(file);
    }

    for (int i = 0; i < bookTotal; i++) {
        if (strcmp(bookID, books[i].bookID) == 0) {
            strcpy(books[i].status, "Status 0");
        }
    }

    fclose(file);
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

void searchBook(book *matchingBooks, int *matchCount, const char *keyword) {
    FILE *bookDB;
    book Book;

    bookDB = fopen("bookDB.txt", "r");
    if (bookDB == NULL) {
        printf("Tidak dapat mengakses koleksi\n");
        return;
    }

    while (fscanf(bookDB, " '%[^']' '%[^']' '%[^']' '%c'", Book.bookID, Book.title, Book.author, &Book.status) != EOF) {
        if (containsIgnoreCase(Book.bookID, keyword) ||
            containsIgnoreCase(Book.title, keyword) ||
            containsIgnoreCase(Book.author, keyword)) {
            strcpy(matchingBooks[*matchCount].bookID, Book.bookID);
            strcpy(matchingBooks[*matchCount].title, Book.title);
            strcpy(matchingBooks[*matchCount].author, Book.author);
            strcpy(matchingBooks[*matchCount].status, Book.status);
            (*matchCount)++;
        }
    }
    fclose(bookDB);
}

void searchResult(book *matchingBooks, int *matchCount) {
    for (int i = 0; i < *matchCount; i++) {
        printf("ID Buku: %s\n", matchingBooks[i].bookID);
        printf("Judul: %s\n", matchingBooks[i].title);
        printf("Penulis: %s\n", matchingBooks[i].author);
        if (strcmp(matchingBooks[i].status, "Status 0") != 0) {
            printf("Status\t: Tersedia");
        } else {
            printf("Status\t: Tidak Tersedia");
        }
    }
}

bool checkTransaction(const char *keyword, transaction *Trans) {
    FILE *receipt;

    if ((receipt = fopen("transactions.txt", "a+")) == NULL) {
        fputs("File tidak dapat dibuka!", stderr);
        exit(1);
    }
    
    while (fscanf(receipt, "%s %s %s %s %s\n", Trans->transactionID, Trans->userName, Trans->bookID, Trans->transactionDate, Trans->dueDate) != EOF) {
        if (strcmp(Trans->transactionID, keyword) == 0) {
        	fclose(receipt);
            return true;
        }
    }
}

void showDetailTransaction(transaction *Trans) {
    printf("Detail Transaksi Anda:\n");
    printf("ID Transaksi: %s\n", Trans->transactionID);
    printf("Title: %s\n", Trans->userName);
    printf("Author: %s\n", Trans->bookID);
    printf("Transaction Date: %s\n", Trans->transactionDate);
    printf("Due Date: %s\n", Trans->dueDate);
    printf("=====================================\n");
}

long calculateOverdue(transaction *Trans) {
    char returnDate[11];
    int dueDay, dueMonth, dueYear, daysOverdue;

    // Get current date
    time_t currentTime;
    struct tm *tm_info;
    time(&currentTime);
    tm_info = localtime(&currentTime);
    strftime(returnDate, 11, "%d-%m-%Y", tm_info);

    // Extract day, month, and year from returnDate and Trans.dueDate
    int returnDay, returnMonth, returnYear;
    sscanf(returnDate, "%d-%d-%d", &returnDay, &returnMonth, &returnYear);

    sscanf(Trans->dueDate, "%d-%d-%d", &dueDay, &dueMonth, &dueYear);

    // Convert to time_t for comparison
    struct tm tm_returnDate = {0};
    tm_returnDate.tm_mday = returnDay;
    tm_returnDate.tm_mon = returnMonth - 1; // Month is zero-based
    tm_returnDate.tm_year = returnYear - 1900; // Years since 1900
    time_t returnDate_t = mktime(&tm_returnDate);

    struct tm tm_dueDate = {0};
    tm_dueDate.tm_mday = dueDay;
    tm_dueDate.tm_mon = dueMonth - 1; // Month is zero-based
    tm_dueDate.tm_year = dueYear - 1900; // Years since 1900
    time_t dueDate_t = mktime(&tm_dueDate);

    // Calculate days overdue
    daysOverdue = (returnDate_t - dueDate_t) / (60 * 60 * 24);
    return daysOverdue * -1;
}

float calculatePenalty(int days) {
	return -1000 * days;
}

void updateBook(book books[], int bookTotal, transaction *Trans) {
	for (int i = 0; i < bookTotal; i++) {
		if (strcmp(Trans->bookID, books[i].bookID) == 0) {
			strcpy(books[i].status, "Status 1");
		}
	}
}

void returnBook(long daysOverdue, float penalty, transaction *Trans) {
    FILE *bookDB;
    char paymentConfirmation;

    bookDB = fopen("bookDB.txt", "r+");
    if (bookDB == NULL) {
        printf("Tidak dapat mengakses koleksi\n");
        return;
    }

    printf("Hari telat: %ld\n", daysOverdue);
    printf("Denda yang harus dibayarkan: Rp.%.2f\n", penalty);

    printf("Konfirmasi pembayaran (Y/N): ");
    scanf(" %c", &paymentConfirmation);

    if (paymentConfirmation == 'Y' || paymentConfirmation == 'y') {
        system("cls");

        char line[256]; // Adjust the size as needed
        long currentPosition = 0;
        int found = 0;

        while (fgets(line, sizeof(line), bookDB) != NULL) {
            book currentBook;
            sscanf(line, " '%6[^']' '%49[^']' '%49[^']' '%11[^']' ", currentBook.bookID, currentBook.title, currentBook.author, currentBook.status);

            if (strcmp(currentBook.bookID, Trans->bookID) == 0) {
                found = 1;
                snprintf(line, sizeof(line), "'%s' '%s' '%s' 'Status 1'\n", currentBook.bookID, currentBook.title, currentBook.author);
                fseek(bookDB, currentPosition, SEEK_SET);
                fputs(line, bookDB);
                break;
            }
            currentPosition = ftell(bookDB);
        }

        if (!found) {
            printf("Buku tidak ditemukan dalam database!\n\n");
        }

        fclose(bookDB);
    } else {
        printf("Pembayaran dibatalkan.\n");
        fclose(bookDB);
    }
}

