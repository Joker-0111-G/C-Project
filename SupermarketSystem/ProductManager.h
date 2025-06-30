#pragma once

//(商品管理模块头文件)

#include "DataModels.h"
#include <unordered_map> // C++中的哈希表实现

class ProductManager {
private:
    std::unordered_map<int, Product> products; // 哈希表，用于O(1)查找商品
    std::map<int, Category> categories; // 红黑树，用于分类管理
    int next_product_id = 1;
    int next_category_id = 1;

    void display_category_tree(int parent_id, int depth);

public:
    ProductManager();
    void add_product(const std::string& name, double price, int stock, int category_id);
    bool update_product(int id, double new_price, int new_stock);
    bool delete_product(int id);
    Product* find_product(int id);
    void display_all_products();

    void add_category(const std::string& name, int parent_id = 0);
    void display_categories();

    // 允许其他模块访问商品数据，但不能修改map本身
    const std::unordered_map<int, Product>& get_products() const { return products; }
};