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
    Node* prev = NULL;
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
        prev = current;
        current = current->next;
    }

    Node* newNode = createNode(type);
    newNode->top++;
    strcpy(newNode->stock[newNode->top].name, name);
    newNode->stock[newNode->top].quantity = quantity;
    newNode->stock[newNode->top].price = price;

    if (prev == NULL) {
        *head = newNode;
    } else {
        prev->next = newNode;
    }

    printf("Medicine type '%s' not found in the database. Created a new type and added medicine '%s'.\n", type, name);
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
            if (current-> top == -1) {
                printf("No stock available for medicine '%s'.\n", type);
                return;
            }

            printf("Stock for medicine '%s':\n", type);
            printf("%-20s %-10s %-10s\n", "Name", "Quantity", "Price");
            printf("---------------------------------------\n");
            for (int i = 0; i <= current->top; i++) {
                printf("%-20s %-10d $%.2f\n", current->stock[i].name, current->stock[i].quantity, current->stock[i].price);
            }
            return;
        }
        current = current->next;
    }
    printf("Medicine type '%s' not found in the database.\n", type);
}

void displayMedicines(Node* head) {
    if (head == NULL) {
        printf("No medicines in the database.\n");
        return;
    }

    printf("Medicine Database:\n");
    printf("%-20s %-20s %-10s %-10s\n", "Type", "Name", "Stock", "Price");
    printf("--------------------------------------------------\n");

    Node* current = head;
    while (current != NULL) {
        for (int i = 0; i <= current->top; i++) {
            printf("%-20s %-20s %-10d $%.2f\n", current->type, current->stock[i].name, current->stock[i].quantity, current->stock[i].price);
        }
        current = current->next;
    }
}

void generateBill(const char* medicineName, int quantity, float price) {
    float totalCost = quantity * price;
    printf("Bill:\n");
    printf("Medicine Name: %s\n", medicineName);
    printf("Quantity: %d\n", quantity);
    printf("Price per unit: $%.2f\n", price);
    printf("Total Cost: $%.2f\n", totalCost);
}

void processCustomerPurchase(Node* head) {
    int numMedicines;
    printf("Enter the number of medicines to purchase: ");
    scanf("%d", &numMedicines);

    char medicineType[50];
    char medicineName[50];
    int quantity;
    float price;
    float totalCost = 0.0;

    for (int i = 1; i <= numMedicines; i++) {
        printf("Enter details for Medicine %d:\n", i);
        printf("Medicine Type: ");
        scanf("%s", medicineType);
        printf("Medicine Name: ");
        scanf("%s", medicineName);
        printf("Quantity: ");
        scanf("%d", &quantity);
        printf("Price: ");
        scanf("%f", &price);

        Node* current = head;
        while (current != NULL) {
            if (strcmp(current->type, medicineType) == 0) {
                for (int j = 0; j <= current->top; j++) {
                    if (strcmp(current->stock[j].name, medicineName) == 0) {
                        if (current->stock[j].quantity >= quantity) {
                            totalCost += quantity * current->stock[j].price;
                            current->stock[j].quantity -= quantity;
                            break;
                                                    } else {
                            printf("Insufficient stock for Medicine '%s'. Available stock: %d\n", medicineName, current->stock[j].quantity);
                            break;
                        }
                    }
                }
                break;
            }
            current = current->next;
        }
    }

    printf("Purchase Summary:\n");
    printf("Total Cost: $%.2f\n", totalCost);
}

int main() {
    Node* head = NULL;
    int choice;
    int role = 0;

    while (choice != 3) {
        printf("Welcome to the Pharmacy Database System!\n");
        printf("Please select your role:\n");
        printf("1. Customer\n");
        printf("2. Seller\n");
        printf("3. Exit\n");
        printf("Enter your choice (1, 2, or 3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Welcome, Customer!\n");
                printf("Here, you can view the available stock of medicines.\n");
                printf("Please select a medicine type to view its stock.\n");

               
                displayMedicines(head);

                char medicineType[50];
                printf("Enter medicine type: ");
                scanf("%s", medicineType);
                displayStock(head, medicineType);

                processCustomerPurchase(head); 
                break;
            case 2:
                printf("Welcome, Seller!\n");
                printf("Here, you can add or remove stock of medicines.\n");
                printf("Please select an action:\n");
                printf("1. Add Medicine to Stock\n");
                printf("2. Remove Medicine from Stock\n");
                printf("3. View Medicine Database\n");
                printf("Enter your choice (1, 2, or 3): ");
                scanf("%d", &choice);
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
                        generateBill(medicineName, quantity, price); 
                    case 2:
                        printf("Enter medicine type: ");
                        scanf("%s", medicineType);
                        popMedicine(&head, medicineType);
                        break;
                    case 3:
                        printf("Medicine Database:\n");
                        displayMedicines(head);
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
                break;
            case 3:
                printf("Exiting the Pharmacy Database System...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}

