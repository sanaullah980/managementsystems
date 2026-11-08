#include <iostream>
#include <map>
#include <iomanip>
#include <string>

struct Product { std::string name, category; double price{}; int quantity{}, reorder{}; };
class Inventory {
    std::map<std::string, Product> items;
public:
    bool add(const std::string& sku, Product p) {
        if (sku.empty() || p.price < 0 || p.quantity < 0 || p.reorder < 0) return false;
        return items.emplace(sku, p).second;
    }
    bool restock(const std::string& sku, int amount) {
        auto it = items.find(sku); if (it == items.end() || amount <= 0) return false;
        it->second.quantity += amount; return true;
    }
    bool sell(const std::string& sku, int amount, double& total) {
        auto it = items.find(sku); if (it == items.end() || amount <= 0 || amount > it->second.quantity) return false;
        it->second.quantity -= amount; total = amount * it->second.price; return true;
    }
    bool setPrice(const std::string& sku, double price) {
        auto it = items.find(sku); if (it == items.end() || price < 0) return false;
        it->second.price = price; return true;
    }
    void list() const {
        std::cout << std::fixed << std::setprecision(2);
        for (const auto& [sku, p] : items) std::cout << sku << " | " << p.name << " | " << p.category << " | $" << p.price << " | stock " << p.quantity << '\n';
        if (items.empty()) std::cout << "Inventory is empty.\n";
    }
    void lowStock() const {
        bool found = false;
        for (const auto& [sku, p] : items) if (p.quantity <= p.reorder) { std::cout << sku << " | " << p.name << " | " << p.quantity << " left\n"; found = true; }
        if (!found) std::cout << "No low-stock products.\n";
    }
    double value() const { double sum = 0; for (const auto& [sku, p] : items) sum += p.price * p.quantity; return sum; }
};
int main() {
    Inventory inventory; int choice;
    while (true) {
        std::cout << "\nBusiness Inventory\n1 Add product\n2 Sell\n3 Restock\n4 List\n5 Low stock\n6 Inventory value\n7 Change price\n0 Exit\nChoice: ";
        if (!(std::cin >> choice)) return 0;
        if (!choice) break;
        std::string sku;
        if (choice == 1) {
            Product p; std::cout << "SKU name category price quantity reorder-level(no spaces): ";
            std::cin >> sku >> p.name >> p.category >> p.price >> p.quantity >> p.reorder;
            std::cout << (inventory.add(sku, p) ? "Product added.\n" : "Invalid/duplicate product.\n");
        } else if (choice == 2) {
            int n; double total = 0; std::cout << "SKU quantity: "; std::cin >> sku >> n;
            if (inventory.sell(sku, n, total)) std::cout << "Sale total: $" << std::fixed << std::setprecision(2) << total << '\n'; else std::cout << "Sale failed; check stock and input.\n";
        } else if (choice == 3) {
            int n; std::cout << "SKU quantity: "; std::cin >> sku >> n;
            std::cout << (inventory.restock(sku, n) ? "Restocked.\n" : "Restock failed.\n");
        } else if (choice == 4) inventory.list();
        else if (choice == 5) inventory.lowStock();
        else if (choice == 6) std::cout << "Inventory value: $" << std::fixed << std::setprecision(2) << inventory.value() << '\n';
        else if (choice == 7) { double p; std::cout << "SKU new price: "; std::cin >> sku >> p; std::cout << (inventory.setPrice(sku, p) ? "Price updated.\n" : "Update failed.\n"); }
        else std::cout << "Unknown option.\n";
    }
}
