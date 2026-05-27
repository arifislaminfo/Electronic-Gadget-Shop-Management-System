#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ============================================================
//  STRUCT DEFINITION
// ============================================================
struct Product {
    int id;
    char name[50];
    char category[30];
    char brand[30];
    float price;
    int quantity;
};

// ============================================================
//  GLOBAL VARIABLES
// ============================================================
struct Product products[100];  // array to hold up to 100 products
int totalProducts = 0;         // tracks how many products exist
#define FILENAME "products.txt"

// ============================================================
//  FUNCTION DECLARATIONS
// ============================================================
void loadFromFile();
void saveToFile();
void displayMenu();
void viewProducts();
void addProduct();
void searchProduct();
void editProduct();
void deleteProduct();
void generateBill();
int  login();
void clearScreen();
void pressEnter();
void toLowerCase(char *str, char *result);

// ============================================================
//  MAIN FUNCTION
// ============================================================
int main() {
    if (login() == 0) {
        printf("\n  Access denied! Exiting...\n");
        return 0;
    }

    loadFromFile();

    int choice;
    do {
        displayMenu();
        printf("  Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1: viewProducts();   break;
            case 2: addProduct();     break;
            case 3: searchProduct();  break;
            case 4: editProduct();    break;
            case 5: deleteProduct();  break;
            case 6: generateBill();   break;
            case 0:
                printf("\n  Thank you for using Gadget Shop System. Goodbye!\n\n");
                break;
            default:
                printf("\n  Invalid choice! Please try again.\n");
                pressEnter();
        }
    } while (choice != 0);

    return 0;
}

// ============================================================
//  LOGIN FUNCTION
// ============================================================
int login() {
    char username[30], password[30];
    // predefined credentials
    char correctUser[30] = "admin";
    char correctPass[30] = "1234";
    int attempts = 3;

    clearScreen();
    printf("\n");
    printf("  =============================================\n");
    printf("   ELECTRONIC GADGET SHOP MANAGEMENT SYSTEM  \n");
    printf("  =============================================\n");
    printf("              ** USER LOGIN **\n\n");

    while (attempts > 0) {
        printf("  Username: ");
        scanf("%s", username);
        printf("  Password: ");
        scanf("%s", password);

        if (strcmp(username, correctUser) == 0 && strcmp(password, correctPass) == 0) {
            printf("\n  Login successful! Welcome, Admin!\n");
            pressEnter();
            return 1;
        } else {
            attempts--;
            if (attempts > 0)
                printf("\n  Wrong credentials! %d attempt(s) left.\n\n", attempts);
        }
    }
    return 0;
}

// ============================================================
//  DISPLAY MENU
// ============================================================
void displayMenu() {
    clearScreen();
    printf("\n");
    printf("  =============================================\n");
    printf("   ELECTRONIC GADGET SHOP MANAGEMENT SYSTEM  \n");
    printf("  =============================================\n");
    printf("   Total Products in Stock: %d\n", totalProducts);
    printf("  ---------------------------------------------\n");
    printf("   1. View All Products\n");
    printf("   2. Add New Product\n");
    printf("   3. Search Product\n");
    printf("   4. Edit Product\n");
    printf("   5. Delete Product\n");
    printf("   6. Generate Bill\n");
    printf("   0. Exit\n");
    printf("  ---------------------------------------------\n");
}

// ============================================================
//  LOAD FROM FILE
// ============================================================
void loadFromFile() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) return; // no file yet, that's okay

    totalProducts = 0;
    while (fscanf(fp, "%d|%49[^|]|%29[^|]|%29[^|]|%f|%d\n",
                  &products[totalProducts].id,
                  products[totalProducts].name,
                  products[totalProducts].category,
                  products[totalProducts].brand,
                  &products[totalProducts].price,
                  &products[totalProducts].quantity) == 6) {
        totalProducts++;
        if (totalProducts >= 100) break;
    }
    fclose(fp);
}

// ============================================================
//  SAVE TO FILE
// ============================================================
void saveToFile() {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        printf("\n  Error: Could not save data to file!\n");
        return;
    }
    for (int i = 0; i < totalProducts; i++) {
        fprintf(fp, "%d|%s|%s|%s|%.2f|%d\n",
                products[i].id,
                products[i].name,
                products[i].category,
                products[i].brand,
                products[i].price,
                products[i].quantity);
    }
    fclose(fp);
}

// ============================================================
//  VIEW ALL PRODUCTS
// ============================================================
void viewProducts() {
    clearScreen();
    printf("\n  ========== ALL PRODUCTS ==========\n\n");

    if (totalProducts == 0) {
        printf("  No products found in the system.\n");
        pressEnter();
        return;
    }

    printf("  %-5s %-20s %-15s %-15s %-10s %-8s\n",
           "ID", "Name", "Category", "Brand", "Price(BDT)", "Stock");
    printf("  -----------------------------------------------------------------------\n");

    for (int i = 0; i < totalProducts; i++) {
        printf("  %-5d %-20s %-15s %-15s %-10.2f %-8d\n",
               products[i].id,
               products[i].name,
               products[i].category,
               products[i].brand,
               products[i].price,
               products[i].quantity);
    }
    printf("  -----------------------------------------------------------------------\n");
    printf("  Total: %d product(s)\n", totalProducts);
    pressEnter();
}

// ============================================================
//  ADD PRODUCT
// ============================================================
void addProduct() {
    clearScreen();
    printf("\n  ========== ADD NEW PRODUCT ==========\n\n");

    if (totalProducts >= 100) {
        printf("  Storage full! Cannot add more products.\n");
        pressEnter();
        return;
    }

    struct Product p;

    // auto generate ID
    p.id = (totalProducts == 0) ? 1 : products[totalProducts - 1].id + 1;

    printf("  Product ID   : %d (auto-assigned)\n", p.id);

    printf("  Product Name : ");
    fgets(p.name, 50, stdin);
    p.name[strcspn(p.name, "\n")] = 0; // remove newline

    printf("  Category     : ");
    fgets(p.category, 30, stdin);
    p.category[strcspn(p.category, "\n")] = 0;

    printf("  Brand        : ");
    fgets(p.brand, 30, stdin);
    p.brand[strcspn(p.brand, "\n")] = 0;

    printf("  Price (BDT)  : ");
    scanf("%f", &p.price);

    printf("  Quantity     : ");
    scanf("%d", &p.quantity);
    getchar();

    products[totalProducts] = p;
    totalProducts++;
    saveToFile(); // save immediately

    printf("\n  Product added successfully!\n");
    pressEnter();
}

// ============================================================
//  SEARCH PRODUCT (partial search)
// ============================================================
void searchProduct() {
    clearScreen();
    printf("\n  ========== SEARCH PRODUCT ==========\n\n");

    if (totalProducts == 0) {
        printf("  No products available to search.\n");
        pressEnter();
        return;
    }

    char key[50];
    printf("  Enter product name or brand to search: ");
    fgets(key, 50, stdin);
    key[strcspn(key, "\n")] = 0;

    // convert search key to lowercase
    char lowerKey[50];
    toLowerCase(key, lowerKey);

    int found = 0;
    printf("\n  %-5s %-20s %-15s %-15s %-10s %-8s\n",
           "ID", "Name", "Category", "Brand", "Price(BDT)", "Stock");
    printf("  -----------------------------------------------------------------------\n");

    for (int i = 0; i < totalProducts; i++) {
        char lowerName[50], lowerBrand[50];
        toLowerCase(products[i].name, lowerName);
        toLowerCase(products[i].brand, lowerBrand);

        // partial match on name OR brand
        if (strstr(lowerName, lowerKey) != NULL || strstr(lowerBrand, lowerKey) != NULL) {
            printf("  %-5d %-20s %-15s %-15s %-10.2f %-8d\n",
                   products[i].id,
                   products[i].name,
                   products[i].category,
                   products[i].brand,
                   products[i].price,
                   products[i].quantity);
            found++;
        }
    }

    if (found == 0)
        printf("  No products found matching \"%s\".\n", key);
    else
        printf("  -----------------------------------------------------------------------\n");

    printf("\n  %d result(s) found.\n", found);
    pressEnter();
}

// ============================================================
//  EDIT PRODUCT
// ============================================================
void editProduct() {
    clearScreen();
    printf("\n  ========== EDIT PRODUCT ==========\n\n");

    if (totalProducts == 0) {
        printf("  No products available to edit.\n");
        pressEnter();
        return;
    }

    char key[50];
    printf("  Enter product name or brand to search: ");
    fgets(key, 50, stdin);
    key[strcspn(key, "\n")] = 0;

    char lowerKey[50];
    toLowerCase(key, lowerKey);

    // show matching records
    int matchIdx[100], matchCount = 0;
    printf("\n  %-5s %-5s %-20s %-15s %-15s %-10s\n",
           "No.", "ID", "Name", "Category", "Brand", "Price(BDT)");
    printf("  -----------------------------------------------------------------------\n");

    for (int i = 0; i < totalProducts; i++) {
        char lowerName[50], lowerBrand[50];
        toLowerCase(products[i].name, lowerName);
        toLowerCase(products[i].brand, lowerBrand);

        if (strstr(lowerName, lowerKey) != NULL || strstr(lowerBrand, lowerKey) != NULL) {
            printf("  %-5d %-5d %-20s %-15s %-15s %-10.2f\n",
                   matchCount + 1,
                   products[i].id,
                   products[i].name,
                   products[i].category,
                   products[i].brand,
                   products[i].price);
            matchIdx[matchCount++] = i;
        }
    }

    if (matchCount == 0) {
        printf("  No products found matching \"%s\".\n", key);
        pressEnter();
        return;
    }

    printf("\n  Enter the No. of the product you want to edit: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice < 1 || choice > matchCount) {
        printf("  Invalid choice!\n");
        pressEnter();
        return;
    }

    int idx = matchIdx[choice - 1];
    printf("\n  Editing Product ID: %d\n", products[idx].id);
    printf("  (Press ENTER to keep current value)\n\n");

    char temp[50];

    printf("  Current Name [%s]: ", products[idx].name);
    fgets(temp, 50, stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) strcpy(products[idx].name, temp);

    printf("  Current Category [%s]: ", products[idx].category);
    fgets(temp, 30, stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) strcpy(products[idx].category, temp);

    printf("  Current Brand [%s]: ", products[idx].brand);
    fgets(temp, 30, stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) strcpy(products[idx].brand, temp);

    printf("  Current Price [%.2f]: ", products[idx].price);
    fgets(temp, 20, stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) products[idx].price = atof(temp);

    printf("  Current Quantity [%d]: ", products[idx].quantity);
    fgets(temp, 10, stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) products[idx].quantity = atoi(temp);

    saveToFile(); // save immediately
    printf("\n  Product updated successfully!\n");
    pressEnter();
}

// ============================================================
//  DELETE PRODUCT
// ============================================================
void deleteProduct() {
    clearScreen();
    printf("\n  ========== DELETE PRODUCT ==========\n\n");

    if (totalProducts == 0) {
        printf("  No products available to delete.\n");
        pressEnter();
        return;
    }

    char key[50];
    printf("  Enter product name or brand to search: ");
    fgets(key, 50, stdin);
    key[strcspn(key, "\n")] = 0;

    char lowerKey[50];
    toLowerCase(key, lowerKey);

    int matchIdx[100], matchCount = 0;
    printf("\n  %-5s %-5s %-20s %-15s %-15s\n",
           "No.", "ID", "Name", "Category", "Brand");
    printf("  -------------------------------------------------------\n");

    for (int i = 0; i < totalProducts; i++) {
        char lowerName[50], lowerBrand[50];
        toLowerCase(products[i].name, lowerName);
        toLowerCase(products[i].brand, lowerBrand);

        if (strstr(lowerName, lowerKey) != NULL || strstr(lowerBrand, lowerKey) != NULL) {
            printf("  %-5d %-5d %-20s %-15s %-15s\n",
                   matchCount + 1,
                   products[i].id,
                   products[i].name,
                   products[i].category,
                   products[i].brand);
            matchIdx[matchCount++] = i;
        }
    }

    if (matchCount == 0) {
        printf("  No products found matching \"%s\".\n", key);
        pressEnter();
        return;
    }

    printf("\n  Enter the No. of the product you want to delete: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice < 1 || choice > matchCount) {
        printf("  Invalid choice!\n");
        pressEnter();
        return;
    }

    int idx = matchIdx[choice - 1];
    printf("\n  Are you sure you want to delete \"%s\"? (y/n): ", products[idx].name);
    char confirm;
    scanf("%c", &confirm);
    getchar();

    if (confirm == 'y' || confirm == 'Y') {
        // shift all products after idx one step back
        for (int i = idx; i < totalProducts - 1; i++) {
            products[i] = products[i + 1];
        }
        totalProducts--;
        saveToFile(); // save immediately
        printf("\n  Product deleted successfully!\n");
    } else {
        printf("\n  Delete cancelled.\n");
    }
    pressEnter();
}

// ============================================================
//  GENERATE BILL (system-specific function)
// ============================================================
void generateBill() {
    clearScreen();
    printf("\n  ========== GENERATE BILL ==========\n\n");

    if (totalProducts == 0) {
        printf("  No products available.\n");
        pressEnter();
        return;
    }

    char customerName[50];
    printf("  Customer Name: ");
    fgets(customerName, 50, stdin);
    customerName[strcspn(customerName, "\n")] = 0;

    // bill items
    int billIDs[20];
    int billQtys[20];
    int billCount = 0;
    float totalAmount = 0;

    char cont = 'y';
    while ((cont == 'y' || cont == 'Y') && billCount < 20) {
        // show available products
        printf("\n  Available Products:\n");
        printf("  %-5s %-20s %-10s %-8s\n", "ID", "Name", "Price", "Stock");
        printf("  -----------------------------------------\n");
        for (int i = 0; i < totalProducts; i++) {
            printf("  %-5d %-20s %-10.2f %-8d\n",
                   products[i].id, products[i].name,
                   products[i].price, products[i].quantity);
        }

        printf("\n  Enter Product ID to add to bill: ");
        int pid;
        scanf("%d", &pid);
        getchar();

        // find product
        int found = -1;
        for (int i = 0; i < totalProducts; i++) {
            if (products[i].id == pid) { found = i; break; }
        }

        if (found == -1) {
            printf("  Product not found!\n");
        } else {
            printf("  Enter quantity: ");
            int qty;
            scanf("%d", &qty);
            getchar();

            if (qty > products[found].quantity) {
                printf("  Not enough stock! Available: %d\n", products[found].quantity);
            } else {
                billIDs[billCount]  = found;
                billQtys[billCount] = qty;
                billCount++;
                totalAmount += products[found].price * qty;
                printf("  Added: %s x%d\n", products[found].name, qty);
            }
        }

        printf("\n  Add another item? (y/n): ");
        scanf("%c", &cont);
        getchar();
    }

    if (billCount == 0) {
        printf("\n  No items in bill.\n");
        pressEnter();
        return;
    }

    // discount logic
    float discount = 0;
    if (totalAmount >= 50000)       discount = 0.15; // 15% off for 50000+ BDT
    else if (totalAmount >= 20000)  discount = 0.10; // 10% off for 20000+ BDT
    else if (totalAmount >= 10000)  discount = 0.05; //  5% off for 10000+ BDT

    float discountAmount = totalAmount * discount;
    float finalAmount    = totalAmount - discountAmount;

    // print invoice
    printf("\n\n");
    printf("  =============================================\n");
    printf("        ELECTRONIC GADGET SHOP\n");
    printf("             --- INVOICE ---\n");
    printf("  =============================================\n");
    printf("  Customer: %s\n", customerName);
    printf("  ---------------------------------------------\n");
    printf("  %-20s %-6s %-10s %-10s\n", "Product", "Qty", "Price", "Subtotal");
    printf("  ---------------------------------------------\n");

    for (int i = 0; i < billCount; i++) {
        int idx = billIDs[i];
        float subtotal = products[idx].price * billQtys[i];
        printf("  %-20s %-6d %-10.2f %-10.2f\n",
               products[idx].name, billQtys[i],
               products[idx].price, subtotal);

        // reduce stock
        products[idx].quantity -= billQtys[i];
    }

    printf("  ---------------------------------------------\n");
    printf("  Total Amount   : BDT %.2f\n", totalAmount);
    if (discount > 0)
        printf("  Discount (%.0f%%) : BDT -%.2f\n", discount * 100, discountAmount);
    printf("  Final Amount   : BDT %.2f\n", finalAmount);
    printf("  =============================================\n");
    printf("       Thank you for shopping with us!\n");
    printf("  =============================================\n");

    saveToFile(); // update stock in file
    pressEnter();
}

// ============================================================
//  HELPER FUNCTIONS
// ============================================================
void toLowerCase(char *str, char *result) {
    int i = 0;
    while (str[i]) {
        result[i] = tolower((unsigned char)str[i]);
        i++;
    }
    result[i] = '\0';
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pressEnter() {
    printf("\n  Press ENTER to continue...");
    getchar();
}
