
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "UBUDEHE.txt"

typedef struct {
    char nationalID[20];
    char names[50];
    char gender;
    char phone[15];
    char cell[30];
    char village[30];
    char startDate[15];
} Person;

void addRecord();
void viewRecords();
void editRecord();
void deleteRecord();

int main() {
    int choice;

    while (1) {
        printf("\n=== UBUDEHE Records Management (Mayange Sector, Bugesera) ===\n");
        printf("1. Add New Record\n");
        printf("2. View all records\n");
        printf("3. Edit existing record\n");
        printf("4. Delete record\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1: addRecord(); break;
            case 2: viewRecords(); break;
            case 3: editRecord(); break;
            case 4: deleteRecord(); break;
            case 0: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}

void addRecord() {
    Person p;
    FILE *fp = fopen(FILE_NAME, "a");

    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter National ID: ");
    fgets(p.nationalID, sizeof(p.nationalID), stdin);
    p.nationalID[strcspn(p.nationalID, "\n")] = 0;

    printf("Enter Names: ");
    fgets(p.names, sizeof(p.names), stdin);
    p.names[strcspn(p.names, "\n")] = 0;

    printf("Enter Gender (M/F): ");
    scanf(" %c", &p.gender);
    getchar();

    printf("Enter phone: ");
    fgets(p.phone, sizeof(p.phone), stdin);
    p.phone[strcspn(p.phone, "\n")] = 0;

    printf("Enter cell: ");
    fgets(p.cell, sizeof(p.cell), stdin);
    p.cell[strcspn(p.cell, "\n")] = 0;

    printf("Enter Village: ");
    fgets(p.village, sizeof(p.village), stdin);
    p.village[strcspn(p.village, "\n")] = 0;

    printf("Enter Starting Date (YYYY-MM-DD): ");
    fgets(p.startDate, sizeof(p.startDate), stdin);
    p.startDate[strcspn(p.startDate, "\n")] = 0;

    fprintf(fp, "%s|%s|%c|%s|%s|%s|%s\n",
            p.nationalID, p.names, p.gender,
            p.phone, p.cell, p.village, p.startDate);

    fclose(fp);

    printf("Record added!\n");
}

void viewRecords() {
    FILE *fp = fopen(FILE_NAME, "r");
    char line[200];

    if (!fp) {
        printf("No records found.\n");
        return;
    }

    printf("\nNationalID | Names | Gender | Phone | Cell | Village | StartDate\n");
    printf("-------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}


void editRecord() {
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    char id[20];
    Person p;
    char line[200];
    int found = 0;

    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter National ID to edit: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%[^|\n]",
               p.nationalID, p.names, &p.gender,
               p.phone, p.cell, p.village, p.startDate);

        if (strcmp(p.nationalID, id) == 0) {
            found = 1;

            printf("Enter new Names: ");
            fgets(p.names, sizeof(p.names), stdin);
            p.names[strcspn(p.names, "\n")] = 0;

            printf("Enter new Gender (M/F): ");
            scanf(" %c", &p.gender);
            getchar();

            printf("Enter new phone: ");
            fgets(p.phone, sizeof(p.phone), stdin);
            p.phone[strcspn(p.phone, "\n")] = 0;

            printf("Enter new cell: ");
            fgets(p.cell, sizeof(p.cell), stdin);
            p.cell[strcspn(p.cell, "\n")] = 0;

            printf("Enter new Village: ");
            fgets(p.village, sizeof(p.village), stdin);
            p.village[strcspn(p.village, "\n")] = 0;

            printf("Enter new Starting Date: ");
            fgets(p.startDate, sizeof(p.startDate), stdin);
            p.startDate[strcspn(p.startDate, "\n")] = 0;
        }

        fprintf(temp, "%s|%s|%c|%s|%s|%s|%s\n",
                p.nationalID, p.names, p.gender,
                p.phone, p.cell, p.village, p.startDate);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Record updated successfully!\n");
    else
        printf("Record not found!\n");
}


void deleteRecord() {
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    char id[20];
    Person p;
    char line[200];
    int found = 0;

    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter National ID to delete: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%[^|\n]",
               p.nationalID, p.names, &p.gender,
               p.phone, p.cell, p.village, p.startDate);

        if (strcmp(p.nationalID, id) == 0) {
            found = 1;
            continue;
        }

        fprintf(temp, "%s|%s|%c|%s|%s|%s|%s\n",
                p.nationalID, p.names, p.gender,
                p.phone, p.cell, p.village, p.startDate);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Record deleted successfully!\n");
    else
        printf("Record not found!\n");
}
