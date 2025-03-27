#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[50];
    int roll;
    int age;
    char course[50];
};

int main() {
    FILE *file;
    struct Student s;
    int n, i;
    
    file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    printf("Enter the number of students: ");
    scanf("%d", &n);
    
    for (i = 0; i < n; i++) {
        printf("Enter details for student %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &s.id);
        printf("Name: ");
        scanf(" %s", s.name);
        printf("Roll: ");
        scanf("%d", &s.roll);
        printf("Age: ");
        scanf("%d", &s.age);
        printf("Course: ");
        scanf(" %s", s.course);
        
        fprintf(file, "%d %s %d %d %s\n", s.id, s.name, s.roll, s.age, s.course);
    }
    
    fclose(file);
    printf("Data successfully written to students.txt\n");
    
    return 0;
}
