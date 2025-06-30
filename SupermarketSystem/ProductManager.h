#pragma once

//(��Ʒ����ģ��ͷ�ļ�)

#include "DataModels.h"
#include <unordered_map> // C++�еĹ�ϣ��ʵ��

class ProductManager {
private:
    std::unordered_map<int, Product> products; // ��ϣ������O(1)������Ʒ
    std::map<int, Category> categories; // ����������ڷ������
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

    // ��������ģ�������Ʒ���ݣ��������޸�map����
    const std::unordered_map<int, Product>& get_products() const { return products; }
};