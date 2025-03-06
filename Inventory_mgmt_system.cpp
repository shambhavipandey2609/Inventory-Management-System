#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Product {
protected:
    int productId;
    char productName[50];
    int quantity;
    float price;

public:
    void setProductDetails(int id, const char* name, int qty, float pr) {
        productId = id;
        strcpy(productName, name);
        quantity = qty;
        price = pr;
    }

    void displayProductDetails() {
        cout << "Product ID: " << productId << "\n";
        cout << "Product Name: " << productName << "\n";
        cout << "Quantity: " << quantity << "\n";
        cout << "Price: ?" << price << "\n";
    }

    int getProductId() const {
        return productId;
    }

    const char* getProductName() const {
        return productName;
    }

    int getQuantity() const {
        return quantity;
    }

    float getPrice() const {
        return price;
    }
};

class Customer {
protected:
    int customerId;
    char customerName[50];
    char password[20];

public:
    void setCustomerDetails(int id, const char* name, const char* pass) {
        customerId = id;
        strcpy(customerName, name);
        strcpy(password, pass);
    }

    int getCustomerId() {
        return customerId;
    }
    const char* getCustomerName() const {
        return customerName;
    }
    const char* getPassword() {
        return password;
    }
    void setPassword(const char* pass) {
        strcpy(password, pass);
    }
};

class Order {
protected:
    int orderId;
    int customerId;
    int productId;
    int quantity;

public:
    void setOrderDetails(int id, int custId, int prodId, int qty) {
        orderId = id;
        customerId = custId;
        productId = prodId;
        quantity = qty;
    }

    void displayOrderDetails() {
        cout << "Order ID: " << orderId << "\n";
        cout << "Customer ID: " << customerId << "\n";
        cout << "Product ID: " << productId << "\n";
        cout << "Quantity: " << quantity << "\n";
    }

    int getOrderId() const {
        return orderId;
    }

    int getCustomerId() const {
        return customerId;
    }

    int getProductId() const {
        return productId;
    }

    int getQuantity() const {
        return quantity;
    }
};

class BusinessSystem {
protected:
    static const int MAX_PRODUCTS = 10;
    static const int MAX_CUSTOMERS = 5;
    static const int MAX_ORDERS = 20;

    Product products[MAX_PRODUCTS];
    Customer customers[MAX_CUSTOMERS];
    Order orders[MAX_ORDERS];

    int productCount;
    int customerCount;
    int orderCount;

public:
    BusinessSystem() {
        productCount = 0;
        customerCount = 0;
        orderCount = 0;
    }

    void ownerLogin() {
        string password;
        cout << "Enter authorization password: ";
        cin >> password;

        if (password == "ownerpass") {
            ownerMenu();
        } else {
            cout << "Invalid authorization password. Access denied.\n";
        }
    }

    void ownerMenu() {
        int choice;
        do {
            cout << "\nOwner Menu\n";
            cout << "1. Add new product\n";
            cout << "2. View Product Quantity\n";
            cout << "3. Edit Product Details\n";
            cout << "4. View Orders\n";
            cout << "5. View Customer List\n";
            cout << "6. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addNewProduct();
                    break;
                case 2:
                    viewProductQuantity();
                    break;
                case 3:
                    editProductDetails();
                    break;
                case 4:
                    viewOrders();
                    break;
                case 5:
                    viewCustomerList();
                    break;
                case 6:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 6);
    }

    void addNewProduct() {
        if (productCount < MAX_PRODUCTS) {
            Product newProduct;
            int newProductId, newQuantity;
            float newPrice;
            char newName[50];

            cout << "Enter new product ID: ";
            cin >> newProductId;

            if (findProductById(newProductId) == -1) {
                cout << "Enter new product name: ";
                cin.ignore();
                cin.getline(newName, sizeof(newName));

                cout << "Enter new quantity: ";
                cin >> newQuantity;

                cout << "Enter new price: ?";
                cin >> newPrice;

                newProduct.setProductDetails(newProductId, newName, newQuantity, newPrice);
                products[productCount++] = newProduct;

                cout << "New product added successfully.\n";
            } else {
                cout << "Product with the given ID already exists. Add operation aborted.\n";
            }
        } else {
            cout << "Cannot add more products. Maximum limit reached.\n";
        }
    }

    void viewProductQuantity() {
        cout << "\nProduct Quantities:\n";
        for (int i = 0; i < productCount; ++i) {
            cout << "Product ID " << products[i].getProductId() << ": " << products[i].getQuantity() << " units\n";
        }
    }

    void editProductDetails() {
        int productId, quantity;
        cout << "Enter the product ID to edit: ";
        cin >> productId;

        int index = findProductById(productId);

        if (index != -1) {
            int subMenuChoice;
            do {
                cout << "\nEdit Product Menu\n";
                cout << "1. Delete Product\n";
                cout << "2. Update Quantity\n";
                cout << "3. Go Back\n";
                cout << "Enter your choice: ";
                cin >> subMenuChoice;

                switch (subMenuChoice) {
                    case 1:
                        deleteProduct(productId);
                        break;
                    case 2:
                        cout << "Enter the new quantity: ";
                        cin >> quantity;
                        products[index].setProductDetails(products[index].getProductId(),
                                                          products[index].getProductName(), quantity,
                                                          products[index].getPrice());
                        cout << "Product quantity updated.\n";
                        break;
                    case 3:
                        cout << "Going back to the main menu...\n";
                        break;
                    default:
                        cout << "Invalid choice. Try again.\n";
                }
            } while (subMenuChoice != 3);
        } else {
            cout << "Product not found.\n";
        }
    }

    void customerMenu() {
        int choice;
        int customerId = -1;

        do {
            cout << "\nCustomer Menu\n";
            cout << "1. Login\n";
            cout << "2. Register\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    customerId = customerLogin();
                    if (customerId != -1) {
                        customerOptionsMenu(customerId);
                    } else {
                        cout << "Login failed. Try again or register a new account.\n";
                    }
                    break;
                case 2:
                    registerCustomer();
                    break;
                case 3:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 3);
    }

    int customerLogin() {
        int id;
        char pass[20];
        cout << "Enter customer ID: ";
        cin >> id;

        int index = findCustomerById(id);
        if (index != -1) {
            cout << "Enter password: ";
            cin >> pass;
            if (strcmp(customers[index].getPassword(), pass) == 0) {
                cout << "Login successful.\n";
                return id;
            } else {
                cout << "Incorrect password.\n";
            }
        } else {
            cout << "Customer not found.\n";
        }
        return -1;
    }

    void registerCustomer() {
        int id;
        char name[50];
        char pass[20];

        cout << "Enter customer ID: ";
        cin >> id;

        if (findCustomerById(id) != -1) {
            cout << "Customer ID already exists. Registration failed.\n";
            return;
        }

        cout << "Enter customer name: ";
        cin.ignore();
        cin.getline(name, sizeof(name));

        cout << "Set password: ";
        cin >> pass;

        customers[customerCount].setCustomerDetails(id, name, pass);
        cout << "Registration successful. You can now login.\n";
        customerCount++;
    }

    void customerOptionsMenu(int customerId) {
        int choice;

        do {
            cout << "\nCustomer Options Menu\n";
            cout << "1. View Products\n";
            cout << "2. Place Order\n";
            cout << "3. View My Orders\n";
            cout << "4. Change Password\n";
            cout << "5. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    viewProducts();
                    break;
                case 2:
                    placeOrder(customerId);
                    break;
                case 3:
                    viewMyOrders(customerId);
                    break;
                case 4:
                    changePassword(customerId);
                    break;
                case 5:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 5);
    }

    void viewProducts() {
        cout << "\nProducts List:\n";
        for (int i = 0; i < productCount; ++i) {
            products[i].displayProductDetails();
            cout << "-------------------\n";
        }
    }

    void placeOrder(int customerId) {
        int productId, quantity;

        int customerIndex = findCustomerById(customerId);
        if (customerIndex == -1) {
            cout << "Customer not found.\n";
            return;
        }

        cout << "Enter product ID: ";
        cin >> productId;

        int productIndex = findProductById(productId);
        if (productIndex == -1) {
            cout << "Product not found.\n";
            return;
        }

        cout << "Enter quantity: ";
        cin >> quantity;

        if (products[productIndex].getQuantity() < quantity) {
            cout << "Insufficient quantity available.\n";
            return;
        }

        Order newOrder;
        newOrder.setOrderDetails(orderCount + 1, customerId, productId, quantity);
        orders[orderCount++] = newOrder;
        cout << "Order placed successfully.\n";
    }

    void viewMyOrders(int customerId) {
        cout << "\nYour Orders:\n";
        bool foundOrder = false;
        for (int i = 0; i < orderCount; ++i) {
            if (orders[i].getCustomerId() == customerId) {
                orders[i].displayOrderDetails();
                cout << "-------------------\n";
                foundOrder = true;
            }
        }

        if (!foundOrder) {
            cout << "No orders found for this customer.\n";
        }
    }

    void changePassword(int customerId) {
        int index = findCustomerById(customerId);
        if (index != -1) {
            char newPassword[20];
            cout << "Enter the new password: ";
            cin >> newPassword;
            customers[index].setPassword(newPassword);
            cout << "Password changed successfully.\n";
        } else {
            cout << "Customer not found.\n";
        }
    }

    void deleteProduct(int productId) {
        int index = findProductById(productId);
        if (index != -1) {
            for (int i = index; i < productCount - 1; ++i) {
                products[i] = products[i + 1];
            }
            --productCount;
            cout << "Product deleted successfully.\n";
        } else {
            cout << "Product not found.\n";
        }
    }

    void viewOrders() {
        cout << "\nOrder Details:\n";
        for (int i = 0; i < orderCount; ++i) {
            orders[i].displayOrderDetails();
            cout << "-------------------\n";
        }
    }

    void viewCustomerList() {
        cout << "\nCustomer List:\n";
        for (int i = 0; i < customerCount; ++i) {
            cout << "Customer ID " << customers[i].getCustomerId() << ": " << customers[i].getPassword() << "\n";
        }
    }

    int findProductById(int productId) {
        for (int i = 0; i < productCount; ++i) {
            if (products[i].getProductId() == productId) {
                return i;
            }
        }
        return -1;
    }

    int findCustomerById(int customerId) {
        for (int i = 0; i < customerCount; ++i) {
            if (customers[i].getCustomerId() == customerId) {
                return i;
            }
        }
        return -1;
    }

    void saveData(const char* data) {
        ofstream file(data);

        if (file.is_open()) {
            file << "ProductCount: " << productCount << endl;
            for (int i = 0; i < productCount; ++i) {
                file << products[i].getProductId() << " "
                     << products[i].getProductName() << " "
                     << products[i].getQuantity() << " "
                     << products[i].getPrice() << endl;
            }

            file << "CustomerCount: " << customerCount << endl;
            for (int i = 0; i < customerCount; ++i) {
                file << customers[i].getCustomerId() << " "
                     << customers[i].getCustomerName() << " "
                     << customers[i].getPassword() << endl;
            }

            file << "OrderCount: " << orderCount << endl;
            for (int i = 0; i < orderCount; ++i) {
                file << orders[i].getOrderId() << " "
                     << orders[i].getCustomerId() << " "
                     << orders[i].getProductId() << " "
                     << orders[i].getQuantity() << endl;
            }

            file.close();
            cout << "Data saved successfully.\n";
        } else {
            cout << "Unable to open file for writing.\n";
        }
    }

    void loadData(const char* data) {
        ifstream file(data);
        if (!file.is_open()) {
            cout << "Unable to open file for reading.\n";
            return;
        }

        string line;
        getline(file, line);
        while (getline(file, line)) {
            if (line == "ProductCount:") {
                int count;
                file >> count;
                productCount = 0;
                for (int i = 0; i < count; ++i) {
                    int id, qty;
                    float pr;
                    char name[50];
                    file >> id >> name >> qty >> pr;
                    products[productCount++].setProductDetails(id, name, qty, pr);
                }
            } else if (line == "CustomerCount:") {
                int count;
                file >> count;
                customerCount = 0;
                for (int i = 0; i < count; ++i) {
                    int id;
                    char name[50], password[20];
                    file >> id >> name >> password;
                    customers[customerCount++].setCustomerDetails(id, name, password);
                }
            } else if (line == "OrderCount:") {
                int count;
                file >> count;
                orderCount = 0;
                for (int i = 0; i < count; ++i) {
                    int orderId, customerId, productId, quantity;
                    file >> orderId >> customerId >> productId >> quantity;
                    orders[orderCount++].setOrderDetails(orderId, customerId, productId, quantity);
                }
            }
        }

        file.close();
        cout << "Data loaded successfully.\n";
    }
};

int main() {
    BusinessSystem businessSystem;

    int userType;

    do {
        cout << "\nUser Type Menu\n";
        cout << "1. Customer\n";
        cout << "2. Owner\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> userType;

        switch (userType) {
            case 1:
                businessSystem.customerMenu();
                break;
            case 2:
                businessSystem.ownerLogin();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (userType != 3);

    const char* filename = "data.txt";

    businessSystem.loadData("data.txt");

    cout << "Data loaded successfully.\n";

    businessSystem.saveData("data.txt");

    return 0;
}
