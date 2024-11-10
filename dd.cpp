#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <algorithm>

class Product {
public:
    Product(int id, const std::string& name, double price, int stock)
        : id(id), name(name), price(price), stock(stock) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    void reduceStock(int quantity) {
        if (stock >= quantity) {
            stock -= quantity;
        } else {
            std::cout << "Недостаточно товара на складе!" << std::endl;
        }
    }

private:
    int id;
    std::string name;
    double price;
    int stock;
};

class User {
public:
    User(const std::string& username, const std::string& password)
        : username(username), password(password) {}

    std::string getUsername() const { return username; }
    bool checkPassword(const std::string& pass) const { return password == pass; }

private:
    std::string username;
    std::string password;
};

class Order {
public:
    void addProduct(const Product& product, int quantity) {
        items.push_back(std::make_pair(product, quantity));
    }

    void printOrder() const {
        std::cout << "Заказ:" << std::endl;
        double total = 0;
        for (const auto& item : items) {
            double itemTotal = item.first.getPrice() * item.second;
            total += itemTotal;
            std::cout << item.first.getName() << " x " << item.second 
                      << " - " << itemTotal << " руб." << std::endl;
        }
        std::cout << "Итого: " << total << " руб." << std::endl;
    }

private:
    std::vector<std::pair<Product, int>> items;
};

class Category {
public:
    Category(const std::string& name) : name(name) {}

    void addProduct(const Product& product) {
        products.push_back(product);
    }

    void printProducts() const {
        std::cout << "Категория: " << name << std::endl;
        for (const auto& product : products) {
            std::cout << "ID: " << product.getId() 
                      << ", Название: " << product.getName() 
                      << ", Цена: " << product.getPrice() 
                      << " руб., На складе: " << product.getStock() << std::endl;
        }
    }

    Product getProductById(int id) {
        for (const auto& product : products) {
            if (product.getId() == id) {
                return product;
            }
        }
        throw std::runtime_error("Товар не найден");
    }

private:
    std::string name;
    std::vector<Product> products;
};

class Store {
public:
    void addCategory(const Category& category) {
        categories.push_back(category);
    }

    void printCategories() const {
        for (const auto& category : categories) {
            category.printProducts();
        }
    }

    Product getProductById(int id) {
        for (const auto& category : categories) {
            try {
                return category.getProductById(id);
            } catch (const std::runtime_error&) {
            }
        }
        throw std::runtime_error("Товар не найден");
    }

    std::vector<Product> searchProducts(const std::string& query) const {
        std::vector<Product> results;
        for (const auto& category : categories) {
            for (const auto& product : category.getProducts()) {
                if (product.getName().find(query) != std::string::npos) {
                    results.push_back(product);
                }
            }
        }
        return results;
    }

private:
    std::vector<Category> categories;
};

class UserManager {
public:
    void registerUser (const std::string& username, const std::string& password) {
       
