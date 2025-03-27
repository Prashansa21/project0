#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FILENAME "loans.txt"

struct Loan {
    char name[50];
    char type[50];
    float principal;
    float rate;
    int tenure;
};

float calculateEMI(float principal, float rate, int tenure) {
    float monthlyRate = rate / (12 * 100);
    int months = tenure * 12;
    return (principal * monthlyRate * pow(1 + monthlyRate, months)) / (pow(1 + monthlyRate, months) - 1);
}

void addLoan() {
    FILE *file = fopen(FILENAME, "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    struct Loan loan;
    printf("Enter Loan Name: ");
    scanf(" %s", loan.name);
    printf("Enter Loan Type: ");
    scanf(" %s", loan.type);
    printf("Enter Principal Amount: ");
    scanf("%f", &loan.principal);
    printf("Enter Annual Interest Rate (%%): ");
    scanf("%f", &loan.rate);
    printf("Enter Tenure (years): ");
    scanf("%d", &loan.tenure);
    
    float emi = calculateEMI(loan.principal, loan.rate, loan.tenure);
    fprintf(file, "%s,%s,%.2f,%.2f,%d\n", loan.name, loan.type, loan.principal, loan.rate, loan.tenure);
    fclose(file);
    printf("Loan record added successfully!\n");
}

void viewLoans() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("No loan records found!\n");
        return;
    }
    struct Loan loan;
    printf("\n%s %s %s %s %s %s\n", "Name", "Type", "Principal", "Rate", "Tenure", "EMI");
    while (fscanf(file, "%s,%s,%f,%f,%d,%f\n", loan.name, loan.type, &loan.principal, &loan.rate, &loan.tenure, &loan.rate) != EOF) {
        printf("%s %s %.2f %.2f %d %.2f\n", loan.name, loan.type, loan.principal, loan.rate, loan.tenure, calculateEMI(loan.principal, loan.rate, loan.tenure));
    }
    fclose(file);
}

void modifyLoan() {
    char name[50];
    printf("Enter Loan Name to modify: ");
    scanf(" %s", name);
    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        printf("Error opening file!\n");
        return;
    }
    struct Loan loan;
    int found = 0;
    while (fscanf(file, "%s,%s,%f,%f,%d,%f\n", loan.name, loan.type, &loan.principal, &loan.rate, &loan.tenure, &loan.rate) != EOF) {
        if (strcmp(loan.name, name) == 0) {
            printf("Enter new Loan Type: ");
            scanf(" %s", loan.type);
            printf("Enter new Principal Amount: ");
            scanf("%f", &loan.principal);
            printf("Enter new Annual Interest Rate (%%): ");
            scanf("%f", &loan.rate);
            printf("Enter new Tenure (years): ");
            scanf("%d", &loan.tenure);
            found = 1;
        }
        fprintf(temp, "%s,%s,%.2f,%.2f,%d,%.2f\n", loan.name, loan.type, loan.principal, loan.rate, loan.tenure, calculateEMI(loan.principal, loan.rate, loan.tenure));
    }
    fclose(file);
    fclose(temp);
    remove(FILENAME);
    rename("temp.txt", FILENAME);
    if (found)
        printf("Loan record modified successfully!\n");
    else
        printf("Loan record not found!\n");
}

void deleteLoan() {
    char name[50];
    printf("Enter Loan Name to delete: ");
    scanf(" %s", name);
    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        printf("Error opening file!\n");
        return;
    }
    struct Loan loan;
    int found = 0;
    while (fscanf(file, "%s,%s,%f,%f,%d,%f\n", loan.name, loan.type, &loan.principal, &loan.rate, &loan.tenure, &loan.rate) != EOF) {
        if (strcmp(loan.name, name) != 0) {
            fprintf(temp, "%s,%s,%2f,%2f,%d,%2f\n", loan.name, loan.type, loan.principal, loan.rate, loan.tenure, calculateEMI);
        } else {
            found = 1;
        }
    }
    fclose(file);
    fclose(temp);
    remove(FILENAME);
    rename("temp.txt", FILENAME);
    if (found)
        printf("Loan record deleted successfully!\n");
    else
        printf("Loan record not found!\n");
}

int main() {
    int choice;
    do {
        printf("\nLoan Management System\n");
        printf("1. Add Loan\n2. View Loans\n3. Modify Loan\n4. Delete Loan\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addLoan(); break;
            case 2: viewLoans(); break;
            case 3: modifyLoan(); break;
            case 4: deleteLoan(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);
    return 0;
}
