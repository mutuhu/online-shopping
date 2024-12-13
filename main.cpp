#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// Product Class
class Product {
private:
    int id;
    string name;
    string description;
    double price;

public:
    Product(int pid, string pname, string pdesc, double pprice)
        : id(pid), name(pname), description(pdesc), price(pprice) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getDescription() const { return description; }
    double getPrice() const { return price; }

    void display() const {
        cout << setw(5) << id << setw(20) << name << setw(30) << description
             << setw(10) << fixed << setprecision(2) << price << endl;
    }
};

// Cart Item Class
class CartItem {
private:
    Product product;
    int quantity;

public:
    CartItem(Product p, int qty) : product(p), quantity(qty) {}

    int getProductId() const { return product.getId(); }
    string getProductName() const { return product.getName(); }
    double getPrice() const { return product.getPrice(); }
    int getQuantity() const { return quantity; }
    double getTotalPrice() const { return product.getPrice() * quantity; }

    void incrementQuantity(int qty) { quantity += qty; }

    void display() const {
        cout << setw(20) << product.getName() << setw(10) << quantity
             << setw(15) << fixed << setprecision(2) << getTotalPrice() << endl;
    }
};

// Cart Class
class Cart {
public:
    vector<CartItem> items;

public:
    void addItem(const Product& product, int quantity) {
        for (auto& item : items) {
            if (item.getProductId() == product.getId()) {
                item.incrementQuantity(quantity);
                return;
            }
        }
        items.push_back(CartItem(product, quantity));
    }

    void displayCart() const {
        if (items.empty()) {
            cout << "Your cart is empty!" << endl;
            return;
        }

        cout << setw(20) << "Product Name" << setw(10) << "Quantity"
             << setw(15) << "Total Price" << endl;
        cout << string(45, '-') << endl;

        for (const auto& item : items) {
            item.display();
        }
    }

    double calculateTotal() const {
        double total = 0;
        for (const auto& item : items) {
            total += item.getTotalPrice();
        }
        return total;
    }

    void clearCart() {
        items.clear();
    }
};

// Utility Functions
void displayProducts(const vector<Product>& products) {
    cout << setw(5) << "ID" << setw(20) << "Name" << setw(30) << "Description"
         << setw(10) << "Price" << endl;
    cout << string(65, '-') << endl;

    for (const auto& product : products) {
        product.display();
    }
}

void saveOrderToFile(const Cart& cart) {
    ofstream file("order_summary.txt");

    file << setw(20) << "Product Name" << setw(10) << "Quantity"
         << setw(15) << "Total Price" << endl;
    file << string(45, '-') << endl;

    double total = cart.calculateTotal();

    for (const auto& item : cart.items) {
        file << setw(20) << item.getProductName() << setw(10) << item.getQuantity()
             << setw(15) << fixed << setprecision(2) << item.getTotalPrice() << endl;
    }

    file << "\nTotal: " << fixed << setprecision(2) << total << " Ksh" << endl;
    file.close();

    cout << "Order saved to 'order_summary.txt'." << endl;
}

// Main Function
int main() {
    vector<Product> products = {
        Product(1, "Laptop", "High-performance laptop", 70000),
        Product(2, "Smartphone", "Latest model smartphone", 50000),
        Product(3, "Headphones", "Noise-cancelling headphones", 15000),
        Product(4, "Smartwatch", "Stylish smartwatch", 20000),
    };

    Cart cart;
    int choice;

    while (true) {
        cout << "\n--- Online Shopping System ---\n";
        cout << "1. View Products\n";
        cout << "2. Add to Cart\n";
        cout << "3. View Cart\n";
        cout << "4. Checkout\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), ');
        cerr << "Invalid input! Please enter valid numbers." << endl;
  continue;
  }
        if (choice == 1) {
            displayProducts(products);
        } else if (choice == 2) {
            int productId, quantity;
            cout << "Enter Product ID: ";
            cin >> productId;
            cout << "Enter Quantity: ";
            cin >> quantity;

            bool found = false;
            for (const auto& product : products) {
                if (product.getId() == productId) {
                    cart.addItem(product, quantity);
                    cout << "Product added to cart!" << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Invalid Product ID!" << endl;
            }
        } else if (choice == 3) {
            cart.displayCart();
        } else if (choice == 4) {
            cart.displayCart();
            cout << "Total Amount: " << fixed << setprecision(2) << cart.calculateTotal()
                 << " Ksh" << endl;

            saveOrderToFile(cart);
            cart.clearCart();
            cout << "Thank you for shopping with us!" << endl;
        } else if (choice == 5) {
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
