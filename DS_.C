#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEDICINES 10
#define MAX_STOCK 100

typedef struct {
    char name[50];
    int quantity;
    float price;
} Medicine;

typedef struct Node {
    char type[50];
    Medicine stock[MAX_STOCK];
    int top;
    struct Node* next;
} Node;

Node* createNode(const char* type) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->type, type);
    newNode->top = -1;
    newNode->next = NULL;
    return newNode;
}

void pushMedicine(Node** head, const char* type, const char* name, int quantity, float price) {
    Node* current = *head;
    while (current != NULL) {
        if (strcmp(current->type, type) == 0) {
            if (current->top == MAX_STOCK - 1) {
                printf("Stack for medicine '%s' is full. Cannot add more stock.\n", type);
                return;
            }
            current->top++;
            strcpy(current->stock[current->top].name, name);
            current->stock[current->top].quantity = quantity;
            current->stock[current->top].price = price;
            printf("Medicine '%s' added to the stock.\n", name);
            return;
        }
        current = current->next;
    }
    printf("Medicine type '%s' not found in the database.\n", type);
}

void popMedicine(Node** head, const char* type) {
    Node* current = *head;
    while (current != NULL) {
        if (strcmp(current->type, type) == 0) {
            if (current->top == -1) {
                printf("No stock available for medicine '%s'.\n", type);
                return;
            }
            Medicine poppedMedicine = current->stock[current->top];
            current->top--;
            printf("Medicine '%s' popped from the stock.\n", poppedMedicine.name);
            return;
        }
        current = current->next;
    }
    printf("Medicine type '%s' not found in the database.\n", type);
}

void displayStock(Node* head, const char* type) {
    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->type, type) == 0) {
            if (current->top == -1) {
                printf("No stock available for medicine '%s'.\n", type);
                return;
            }
            printf("Stock for medicine '%s':\n", type);
            for (int i = 0; i <= current->top; i++) {
                printf("Medicine Name: %s\n", current->stock[i].name);
                printf("Quantity: %d\n", current->stock[i].quantity);
                printf("Price: $%.2f\n\n", current->stock[i].price);
            }
            return;
        }
        current = current->next;
    }
    printf("Medicine type '%s' not found in the database.\n", type);
}

int main() {
    Node* head = NULL;
    int choice;
    int role;

    printf("Welcome to the Pharmacy Database System!\n");
    printf("Are you a customer or a seller?\n");
    printf("1. Customer\n");
    printf("2. Seller\n");
    printf("Enter your role (1 or 2): ");
    scanf("%d", &role);

    if (role == 1) {
        printf("Welcome, Customer!\n");
        printf("Here, you can view the available stock of medicines.\n");
        printf("Please select a medicine type to view its stock.\n");

        Node* current = head;
        while (current != NULL) {
            printf("%s\n", current->type);
            current = current->next;
        }

        char medicineType[50];
        printf("Enter medicine type: ");
        scanf("%s", medicineType);
        displayStock(head, medicineType);
    } else if (role == 2) {
        printf("Welcome, Seller!\n");
        printf("Here, you can add or remove stock of medicines.\n");
        printf("Please select an action:\n");
        printf("1. Add Medicine to Stock\n");
        printf("2. Remove Medicine from Stock\n");
        printf("Enter your choice (1 or 2): ");
        scanf("%d", &choice);

        char medicineType[50];
        char medicineName[50];
        int quantity;
        float price;

        switch (choice) {
            case 1:
                printf("Enter medicine type: ");
                scanf("%s", medicineType);
                printf("Enter medicine name: ");
                scanf("%s", medicineName);
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                printf("Enter price: ");
                scanf("%f", &price);
                pushMedicine(&head, medicineType, medicineName, quantity, price);
                break;
            case 2:
                printf("Enter medicine type: ");
                scanf("%s", medicineType);
                popMedicine(&head, medicineType);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } else {
        printf("Invalid role. Please try again.\n");
    }

    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
