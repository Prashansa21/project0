#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "students.txt"

struct Student {
    int id;
    char name[50];
    int roll;
    int age;
    char course[50];
};

void addStudent() {
    struct Student s;
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter roll:");
    scanf("%d", &s.roll);
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Course: ");
    scanf("%s", s.course);
    
    fprintf(file, "%d %s %d %d %s\n", s.id, s.name, s.roll, s.age, s.course);
    fclose(file);
    printf("Student added successfully!\n");
    getchar();
}

void viewStudents() {
    struct Student s;
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No records found!\n");
        return;
    }
    printf("\nStudent Records:\n");
    while (fscanf(file, "%d %s %d %d %s", &s.id, s.name, &s.roll, &s.age, s.course) != EOF) {
        printf("ID: %d, Name: %s, Roll: %d, Age: %d, Course: %s\n", s.id, s.name, s.roll, s.age, s.course);
    }
    fclose(file);
    getchar();
}

void searchStudent() {
    struct Student s;
    int id, found = 0;
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No records found!\n");
        return;
    }
    printf("Enter Student ID to search: ");
    scanf("%d", &id);
    while (fscanf(file, "%d %s %d %d %s", &s.id, s.name, &s.roll, &s.age, s.course) != EOF) {
        if (s.id == id) {
            printf("ID: %d, Name: %s, Roll: %d, Age: %d, Course: %s\n", s.id, s.name, s.roll, s.age, s.course);
            found = 1;
            break;
        }
    }
    fclose(file);
    if (!found) printf("Student not found!\n");
    getchar();
}

void updateStudent() {
    struct Student s;
    int id, found = 0;
    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter Student ID to update: ");
    scanf("%d", &id);
    while (fscanf(file, "%d %s %d %d %s", &s.id, s.name, &s.roll, &s.age, s.course) != EOF) {
        if (s.id == id) {
            printf("Enter New Name: ");
            scanf("%s", s.name);
            printf("Enter new roll:");
            scanf("%d", &s.roll);
            printf("Enter New Age: ");
            scanf("%d", &s.age);
            printf("Enter New Course: ");
            scanf("%s", s.course);
            found = 1;
        }
        fprintf(temp, "%d %s %d %d %s\n", s.id, s.name, s.roll, s.age, s.course);
    }
    fclose(file);
    fclose(temp);
    remove(FILENAME);
    rename("temp.txt", FILENAME);
    if (found)
        printf("Student updated successfully!\n");
    else
        printf("Student not found!\n");
    getchar();
}

void deleteStudent() {
    struct Student s;
    int id, found = 0;
    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);
    while (fscanf(file, "%d %s %d %d %s", &s.id, s.name, &s.roll, &s.age, s.course) != EOF) {
        if (s.id != id) {
            fprintf(temp, "%d %s %d %d %s\n", s.id, s.name, s.roll, s.age, s.course);
        } else {
            found = 1;
        }
    }
    fclose(file);
    fclose(temp);
    remove(FILENAME);
    rename("temp.txt", FILENAME);
    if (found)
        printf("Student deleted successfully!\n");
    else
        printf("Student not found!\n");
    getchar();
}

int main() {
    int choice;
    do {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);
    return 0;
}
