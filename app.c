#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== STRUCTURE DEFINITION ====================
struct Customer {
    int roomNumber;
    char name[50];
    char address[100];
    char phone[20];
    int days;
    float totalBill;
    struct Customer *next;
};

struct Customer *head = NULL;

// ==================== FUNCTION DECLARATIONS ====================
void addCustomer();
void displayCustomers();
void searchCustomer();
void deleteCustomer();
void saveToFile();
void loadFromFile();

// ==================== ADD CUSTOMER ====================
void addCustomer() {
    struct Customer *newCust = (struct Customer*)malloc(sizeof(struct Customer));

    printf("\nEnter Room Number: ");
    scanf("%d", &newCust->roomNumber);

    printf("Enter Name: ");
    scanf("%s", newCust->name);

    printf("Enter Address: ");
    scanf("%s", newCust->address);

    printf("Enter Phone: ");
    scanf("%s", newCust->phone);

    printf("Enter Days Stayed: ");
    scanf("%d", &newCust->days);

    newCust->totalBill = newCust->days * 1000; // Example billing calculation

    newCust->next = head;
    head = newCust;

    printf("\nCustomer added successfully!\n");
}

// ==================== DISPLAY CUSTOMERS ====================
void displayCustomers() {
    struct Customer *temp = head;

    if (temp == NULL) {
        printf("\nNo customer records found!\n");
        return;
    }

    printf("\n%-10s %-20s %-20s %-12s %-6s %-10s\n",
           "Room", "Name", "Address", "Phone", "Days", "Bill");
    printf("-------------------------------------------------------------------------------\n");

    while (temp != NULL) {
        printf("%-10d %-20s %-20s %-12s %-6d ₹%-10.2f\n",
               temp->roomNumber, temp->name, temp->address,
               temp->phone, temp->days, temp->totalBill);
        temp = temp->next;
    }
}

// ==================== SEARCH CUSTOMER ====================
void searchCustomer() {
    int room;
    printf("\nEnter Room Number to search: ");
    scanf("%d", &room);

    struct Customer *temp = head;

    while (temp != NULL) {
        if (temp->roomNumber == room) {
            printf("\nCustomer Found!\n");
            printf("-----------------------\n");
            printf("Name: %s\n", temp->name);
            printf("Address: %s\n", temp->address);
            printf("Phone: %s\n", temp->phone);
            printf("Days Stayed: %d\n", temp->days);
            printf("Total Bill: ₹%.2f\n", temp->totalBill);
            return;
        }
        temp = temp->next;
    }
    printf("\nNo record found for Room %d\n", room);
}

// ==================== DELETE CUSTOMER ====================
void deleteCustomer() {
    int room;
    printf("\nEnter Room Number to delete: ");
    scanf("%d", &room);

    struct Customer *temp = head, *prev = NULL;

    while (temp != NULL && temp->roomNumber != room) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\nCustomer not found!\n");
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("\nRecord deleted successfully!\n");
}

// ==================== SAVE TO FILE ====================
void saveToFile() {
    FILE *fp = fopen("hotel_data.txt", "w");
    if (!fp) {
        printf("\nError opening file for saving!\n");
        return;
    }

    struct Customer *temp = head;

    while (temp != NULL) {
        fprintf(fp, "%d,%s,%s,%s,%d,%.2f\n",
                temp->roomNumber, temp->name, temp->address,
                temp->phone, temp->days, temp->totalBill);
        temp = temp->next;
    }

    fclose(fp);
}

// ==================== LOAD FROM FILE ====================
void loadFromFile() {
    FILE *fp = fopen("hotel_data.txt", "r");
    if (!fp) return;

    struct Customer cust;

    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%d,%f\n",
                  &cust.roomNumber, cust.name, cust.address,
                  cust.phone, &cust.days, &cust.totalBill) != EOF) {

        struct Customer *newCust = (struct Customer*)malloc(sizeof(struct Customer));
        *newCust = cust;
        newCust->next = head;
        head = newCust;
    }
    fclose(fp);
}

// ==================== MAIN FUNCTION ====================
int main() {
    int choice;

    loadFromFile();

    while (1) {
        printf("\n========== HOTEL MANAGEMENT SYSTEM ==========\n");
        printf("1. Add Customer\n");
        printf("2. Display All Customers\n");
        printf("3. Search Customer\n");
        printf("4. Delete Customer\n");
        printf("5. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addCustomer(); break;
            case 2: displayCustomers(); break;
            case 3: searchCustomer(); break;
            case 4: deleteCustomer(); break;
            case 5: saveToFile();
                    printf("\nData saved. Exiting...\n");
                    exit(0);
            default: printf("\nInvalid Choice!\n");
        }
    }
}
