#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct student {
    int sid;
    char name[30];
    char branch[40];
    int semester;
    char address[100];
};

// Helper function to convert a string to lowercase
void toLowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Function to create a new file with student records
void create() {
    struct student *s;
    FILE *fp;
    fp = fopen("studentFile.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int n, i;
    printf("Enter number of students (Enter 0 if just creating table): ");
    scanf("%d", &n);

    if (n > 0) {
        s = (struct student*)malloc(n * sizeof(struct student));
        for (i = 0; i < n; i++) {
            printf("Enter SID: ");
            scanf("%d", &s[i].sid);
            printf("Enter name: ");
            scanf("%s", s[i].name);
            printf("Enter branch: ");
            scanf("%s", s[i].branch);
            printf("Enter semester: ");
            scanf("%d", &s[i].semester);
            printf("Enter address: ");
            scanf("%s", s[i].address);
            fprintf(fp, "%d\t%s\t%s\t%d\t%s\n", s[i].sid, s[i].name, s[i].branch, s[i].semester, s[i].address);
        }
        free(s);
    }
    fclose(fp);
}

// Function to insert new student records into the file
void insert() {
    struct student *s;
    FILE *fp;
    fp = fopen("studentFile.txt", "a");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int n, i;
    printf("Enter number of students: ");
    scanf("%d", &n);

    if (n > 0) {
        s = (struct student*)malloc(n * sizeof(struct student));
        for (i = 0; i < n; i++) {
            printf("Enter SID: ");
            scanf("%d", &s[i].sid);
            printf("Enter name: ");
            scanf("%s", s[i].name);
            printf("Enter branch: ");
            scanf("%s", s[i].branch);
            printf("Enter semester: ");
            scanf("%d", &s[i].semester);
            printf("Enter address: ");
            scanf("%s", s[i].address);
            fprintf(fp, "%d\t%s\t%s\t%d\t%s\n", s[i].sid, s[i].name, s[i].branch, s[i].semester, s[i].address);
        }
        free(s);
    }
    fclose(fp);
}

// Function to modify the address of a student based on SID
void modify() {
    struct student s;
    int sid, found = 0;
    char newAddress[100];
    FILE *fp, *temp;
    
    printf("Enter SID of the student to modify: ");
    scanf("%d", &sid);

    fp = fopen("studentFile.txt", "r");
    temp = fopen("tempFile.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fscanf(fp, "%d\t%s\t%s\t%d\t%s\n", &s.sid, s.name, s.branch, &s.semester, s.address) != EOF) {
        if (s.sid == sid) {
            found = 1;
            printf("Enter new address: ");
            scanf("%s", newAddress);
            strcpy(s.address, newAddress);
        }
        fprintf(temp, "%d\t%s\t%s\t%d\t%s\n", s.sid, s.name, s.branch, s.semester, s.address);
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("studentFile.txt");
        rename("tempFile.txt", "studentFile.txt");
        printf("Address updated successfully.\n");
    } else {
        printf("Student with SID %d not found.\n", sid);
        remove("tempFile.txt");
    }
}

void listCse() {
    struct student s;
    FILE *fp;
    fp = fopen("studentFile.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("List of CSE students:\n");
    printf("SID\tName\tBranch\tSemester\tAddress\n");
    printf("----------------------------------------------------\n");
    while (fscanf(fp, "%d\t%s\t%s\t%d\t%s\n", &s.sid, s.name, s.branch, &s.semester, s.address) != EOF) {
        // Convert the branch to lowercase for case-insensitive comparison
        char branchLower[40];
        strcpy(branchLower, s.branch);
        toLowercase(branchLower);

        // Check for accepted variants of "CSE"
        if (strcmp(branchLower, "cse") == 0 ||
            strcmp(branchLower, "computer science and engineering") == 0 ||
            strcmp(branchLower, "computer science") == 0) {
            printf("%d\t%s\t%s\t%d\t%s\n", s.sid, s.name, s.branch, s.semester, s.address);
        }
    }
    fclose(fp);
}

// Function to delete a student based on SID
void delete() {
    struct student s;
    int sid, found = 0;
    FILE *fp, *temp;

    printf("Enter SID of the student to delete: ");
    scanf("%d", &sid);

    fp = fopen("studentFile.txt", "r");
    temp = fopen("tempFile.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fscanf(fp, "%d\t%s\t%s\t%d\t%s\n", &s.sid, s.name, s.branch, &s.semester, s.address) != EOF) {
        if (s.sid != sid) {
            fprintf(temp, "%d\t%s\t%s\t%d\t%s\n", s.sid, s.name, s.branch, s.semester, s.address);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("studentFile.txt");
        rename("tempFile.txt", "studentFile.txt");
        printf("Student deleted successfully.\n");
    } else {
        printf("Student with SID %d not found.\n", sid);
        remove("tempFile.txt");
    }
}

// Function to list only CSE students from Kuvempunagar
void listCseK() {
    struct student s;
    FILE *fp;
    fp = fopen("studentFile.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("List of CSE students residing in Kuvempunagar:\n");
    printf("SID\tName\tBranch\tSemester\tAddress\n");
    printf("----------------------------------------------------\n");
    while (fscanf(fp, "%d\t%s\t%s\t%d\t%s\n", &s.sid, s.name, s.branch, &s.semester, s.address) != EOF) {
        char branchLower[40], addressLower[100];
        strcpy(branchLower, s.branch);
        strcpy(addressLower, s.address);
        toLowercase(branchLower);
        toLowercase(addressLower);

        if ((strcmp(branchLower, "cse") == 0 || strcmp(branchLower, "computer science and engineering") == 0 || strcmp(branchLower, "computer science") == 0) &&
            strstr(addressLower, "kuvempunagar") != NULL) {
            printf("%d\t%s\t%s\t%d\t%s\n", s.sid, s.name, s.branch, s.semester, s.address);
        }
    }
    fclose(fp);
}

// Function to list all students
void list() {
    struct student s;
    FILE *fp;
    fp = fopen("studentFile.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("List of CSE students:\n");
    printf("SID\tName\tBranch\tSemester\tAddress\n");
    printf("----------------------------------------------------\n");
    while (fscanf(fp, "%d\t%s\t%s\t%d\t%s\n", &s.sid, s.name, s.branch, &s.semester, s.address) != EOF) {
        printf("%d\t%s\t%s\t%d\t%s\n", s.sid, s.name, s.branch, s.semester, s.address);
    }
    fclose(fp);
}

int main() {
    int ch;
    create();
    while (1) {
        printf("Enter\n1 : Insert a new student\n2 : Modify the address of the student based on the SID\n3 : Delete a student\n4 : List all the students\n5 : List all the students of CSE branch\n6 : List all the students of CSE branch and reside in Kuvempunagar\n0 : Exit\n");
        scanf("%d", &ch);
        switch (ch) {
            case 1: insert(); break;
            case 2: modify(); break;
            case 3: delete(); break;
            case 4: list(); break;
            case 5: listCse(); break;
            case 6: listCseK(); break;
            case 0: exit(1); break;
            default: printf("Enter valid option\n");
        }
    }
}
