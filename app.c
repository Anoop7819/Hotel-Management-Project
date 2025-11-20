/*
---------------------------------------------------------------
    HOTEL MANAGEMENT SYSTEM
    Developed by: Yash Tripathi, Anoop, Sumit, Arhaan, Sajid
    Language: C
    Concepts Used: Structures, Linked List, File Handling (DSA)
---------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== STRUCTURE DEFINITION ====================
struct Customer {
    int roomNumber;
    char name[50];
    char address[100];
    char phone[15];
    int days;
    float totalBill;
    struct Customer *next;  // pointer to next node (for linked list)
};

// Global pointer to the first node
struct Customer *head = NULL;

// ==================== FUNCTION DECLARATIONS ====================
void addCustomer();
void displayCustomers();
void searchCustomer();
void deleteCustomer();
void saveToFile();
void loadFromFile();
float calculateBill(int days);
void header();

// ==================== MAIN FUNCTION ====================
int main() {
    int choice;
    loadFromFile();  // Load previous data from file (if any)

    do {
        header();
        printf("\n1. Add New Customer");
        printf("\n2. Display All Customers");
        printf("\n3. Search Customer by Room");
        printf("\n4. Delete Customer Record");
        printf("\n5. Save & Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addCustomer(); break;
            case 2: displayCustomers(); break;
            case 3: searchCustomer(); break;
            case 4: deleteCustomer(); break;
            case 5: saveToFile(); printf("\nData saved successfully. Exiting...\n"); break;
            default: printf("\n❌ Invalid choice! Please try again.\n");
        }

        if(choice != 5) {
            printf("\nPress Enter to continue...");
            getchar(); getchar(); // pause before showing menu again
        }

    } while(choice != 5);

    return 0;
}

// ==================== FUNCTION DEFINITIONS ====================

// Prints a fancy header
void header() {
    system("cls");  // clear console (use "clear" for Linux)
    printf("===============================================================\n");
    printf("           HOTEL MANAGEMENT SYSTEM (DSA PROJECT)              \n");
    printf("===============================================================\n");
}

// Calculate bill based on number of days
float calculateBill(int days) {
    float ratePerDay = 1500.0;  // base rate per day
    return days * ratePerDay;
}

// Add new customer record (inserts at beginning of linked list)
void addCustomer() {
    struct Customer *newCust = (struct Customer*)malloc(sizeof(struct Customer));
    if(!newCust) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("\nEnter Room Number: ");
    scanf("%d", &newCust->roomNumber);

    // Check if room already exists
    struct Customer *temp = head;
    while(temp != NULL) {
        if(temp->roomNumber == newCust->roomNumber) {
            printf("\n Room already booked! Please choose another room.\n");
            free(newCust);
            return;
        }
        temp = temp->next;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", newCust->name);

    printf("Enter Address: ");
    scanf(" %[^\n]", newCust->address);

    printf("Enter Phone Number: ");
    scanf(" %[^\n]", newCust->phone);

    printf("Enter Number of Days: ");
    scanf("%d", &newCust->days);

    newCust->totalBill = calculateBill(newCust->days);
    newCust->next = head;  // insert at head
    head = newCust;

    printf("\n Customer added successfully!");
}

// Display all customers (traverse linked list)
void displayCustomers() {
    struct Customer *temp = head;

    if(temp == NULL) {
        printf("\nNo customer records found!\n");
        return;
    }

    printf("\n%-10s %-20s %-15s %-6s %-10s\n", "Room", "Name", "Phone", "Days", "Bill");
    printf("---------------------------------------------------------------\n");

    while(temp != NULL) {
        printf("%-10d %-20s %-15s %-6d ₹%-10.2f\n",
               temp->roomNumber, temp->name, temp->phone, temp->days, temp->totalBill);
        temp = temp->next;
    }
}

// Search for a customer by room number
void searchCustomer() {
    int room;
    printf("\nEnter Room Number to search: ");
    scanf("%d", &room);

    struct Customer *temp = head;
    while(temp != NULL) {
        if(temp->roomNumber == room) {
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
    printf("\n No record found for Room %d\n", room);
}

// Delete a customer record
void deleteCustomer() {
    int room;
    printf("\nEnter Room Number to delete: ");
    scanf("%d", &room);

    struct Customer *temp = head, *prev = NULL;

    while(temp != NULL && temp->roomNumber != room) {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL) {
        printf("\n Customer not found!\n");
        return;
    }

    // If deleting first node
    if(prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("\n Record deleted successfully!");
}

// Save data to file (persistent storage)
void saveToFile() {
    FILE *fp = fopen("hotel_data.txt", "w");
    if(!fp) {
        printf("\nError opening file for saving!\n");
        return;
    }

    struct Customer *temp = head;
    while(temp != NULL) {
        fprintf(fp, "%d,%s,%s,%s,%d,%.2f\n",
                temp->roomNumber, temp->name, temp->address,
                temp->phone, temp->days, temp->totalBill);
        temp = temp->next;
    }
    fclose(fp);
}

// Load data from file into linked list (runs at start)
void loadFromFile() {
    FILE *fp = fopen("hotel_data.txt", "r");
    if(!fp) return; // no file yet (first run)

    struct Customer cust;
    while(fscanf(fp, "%d,%[^,],%[^,],%[^,],%d,%f\n",
          &cust.roomNumber, cust.name, cust.address, cust.phone,
          &cust.days, &cust.totalBill) != EOF) {
        struct Customer *newCust = (struct Customer*)malloc(sizeof(struct Customer));
        *newCust = cust;
        newCust->next = head;
        head = newCust;
    }
    fclose(fp);
}
