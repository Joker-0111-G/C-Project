//��Ʒ����ģ��ʵ���ļ�

#include "ProductManager.h"

ProductManager::ProductManager() {
    // ���Ĭ�Ϸ���
    add_category("������Ʒ"); // ������
}

void ProductManager::add_product(const std::string& name, double price, int stock, int category_id) {
    int id = next_product_id++;
    products[id] = Product(id, name, price, stock, category_id);
    std::cout << "�ɹ������Ʒ: " << name << " (ID: " << id << ")" << std::endl;
}

bool ProductManager::update_product(int id, double new_price, int new_stock) {
    auto it = products.find(id);
    if (it != products.end()) {
        it->second.price = new_price;
        it->second.stock = new_stock;
        std::cout << "�ɹ�������Ʒ ID: " << id << std::endl;
        return true;
    }
    std::cout << "����: δ�ҵ���Ʒ ID: " << id << std::endl;
    return false;
}

bool ProductManager::delete_product(int id) {
    if (products.erase(id)) {
        std::cout << "�ɹ�ɾ����Ʒ ID: " << id << std::endl;
        return true;
    }
    std::cout << "����: δ�ҵ���Ʒ ID: " << id << std::endl;
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
    std::cout << "\n--- ������Ʒ�б� ---\n";
    if (products.empty()) {
        std::cout << "  ��Ʒ��Ϊ�ա�\n";
        return;
    }
    for (const auto& pair : products) {
        pair.second.display();
    }
}

void ProductManager::add_category(const std::string& name, int parent_id) {
    int id = next_category_id++;
    categories[id] = Category(id, name, parent_id);
    std::cout << "�ɹ���ӷ���: " << name << " (ID: " << id << ")" << std::endl;
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
    std::cout << "\n--- ��Ʒ������ ---\n";
    display_category_tree(0, 0); // �Ӹ��ڵ㿪ʼ��ʾ
}