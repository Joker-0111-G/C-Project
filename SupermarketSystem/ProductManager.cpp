//商品管理模块实现文件

#include "ProductManager.h"

ProductManager::ProductManager() {
    // 添加默认分类
    add_category("所有商品"); // 根分类
}

void ProductManager::add_product(const std::string& name, double price, int stock, int category_id) {
    int id = next_product_id++;
    products[id] = Product(id, name, price, stock, category_id);
    std::cout << "成功添加商品: " << name << " (ID: " << id << ")" << std::endl;
}

bool ProductManager::update_product(int id, double new_price, int new_stock) {
    auto it = products.find(id);
    if (it != products.end()) {
        it->second.price = new_price;
        it->second.stock = new_stock;
        std::cout << "成功更新商品 ID: " << id << std::endl;
        return true;
    }
    std::cout << "错误: 未找到商品 ID: " << id << std::endl;
    return false;
}

bool ProductManager::delete_product(int id) {
    if (products.erase(id)) {
        std::cout << "成功删除商品 ID: " << id << std::endl;
        return true;
    }
    std::cout << "错误: 未找到商品 ID: " << id << std::endl;
    return false;
}

Product* ProductManager::find_product(int id) {
    auto it = products.find(id);
    if (it != products.end()) {
        return &(it->second);
    }
    return nullptr;
}

void ProductManager::display_all_products() {
    std::cout << "\n--- 所有商品列表 ---\n";
    if (products.empty()) {
        std::cout << "  商品库为空。\n";
        return;
    }
    for (const auto& pair : products) {
        pair.second.display();
    }
}

void ProductManager::add_category(const std::string& name, int parent_id) {
    int id = next_category_id++;
    categories[id] = Category(id, name, parent_id);
    std::cout << "成功添加分类: " << name << " (ID: " << id << ")" << std::endl;
}

void ProductManager::display_category_tree(int parent_id, int depth) {
    for (const auto& pair : categories) {
        if (pair.second.parent_id == parent_id) {
            std::cout << std::string(depth * 2, ' ') << "|- " << pair.second.name << " (ID: " << pair.first << ")" << std::endl;
            display_category_tree(pair.first, depth + 1);
        }
    }
}

void ProductManager::display_categories() {
    std::cout << "\n--- 商品分类树 ---\n";
    display_category_tree(0, 0); // 从根节点开始显示
}