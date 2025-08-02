#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

void addStudent();
void viewStudents();
void searchStudent();
void deleteStudent();

int main() {
    int choice;

    for (;;) {  // Infinite loop using for
        printf("\n--- Student Record Management ---\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student by Roll No\n");
        printf("4. Delete Student by Roll No\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        if (choice == 5) {
            printf("Exiting...\n");
            break;
        }

        if (choice == 1) addStudent();
        else if (choice == 2) viewStudents();
        else if (choice == 3) searchStudent();
        else if (choice == 4) deleteStudent();
        else printf("Invalid choice!\n");
    }

    return 0;
}

void addStudent() {
    FILE *fp = fopen("students.txt", "a");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Student s;
    printf("Enter roll number: ");
    scanf("%d", &s.rollNo);
    getchar();

    printf("Enter name: ");
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.rollNo, s.name, s.marks);
    fclose(fp);

    printf("Student added successfully!\n");
}

void viewStudents() {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    Student s;
    int i;
    printf("\n--- All Students ---\n");
    for (i = 0; fscanf(fp, "%d %s %f", &s.rollNo, s.name, &s.marks) == 3; i++) {
        printf("Roll No: %d | Name: %s | Marks: %.2f\n", s.rollNo, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    int targetRoll, found = 0;
    Student s;

    printf("Enter roll number to search: ");
    scanf("%d", &targetRoll);

    int i;
    for (i = 0; fscanf(fp, "%d %s %f", &s.rollNo, s.name, &s.marks) == 3; i++) {
        if (s.rollNo == targetRoll) {
            printf("Found: Roll No: %d | Name: %s | Marks: %.2f\n", s.rollNo, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");

    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error processing file.\n");
        return;
    }

    int targetRoll, found = 0;
    Student s;

    printf("Enter roll number to delete: ");
    scanf("%d", &targetRoll);

    int i;
    for (i = 0; fscanf(fp, "%d %s %f", &s.rollNo, s.name, &s.marks) == 3; i++) {
        if (s.rollNo != targetRoll)
            fprintf(temp, "%d %s %.2f\n", s.rollNo, s.name, s.marks);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        printf("Student deleted successfully.\n");
    else
        printf("Student not found.\n");
}
