#pragma once // 防止头文件被重复包含

//核心数据结构

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

// 商品分类结构体
struct Category {
    int id;
    std::string name;
    int parent_id; // 0 表示根分类

    Category(int i = 0, std::string n = "", int p_id = 0) : id(i), name(n), parent_id(p_id) {}
};

// 商品结构体
struct Product {
    int id;
    std::string name;
    double price;
    int stock;
    int category_id;
    int sales_count = 0; // 销售数量

    Product(int i = 0, std::string n = "", double p = 0.0, int s = 0, int cat_id = 0)
        : id(i), name(n), price(p), stock(s), category_id(cat_id) {}

    void display() const {
        std::cout << "  ID: " << id << ", 名称: " << name << ", 价格: " << price
            << ", 库存: " << stock << ", 销量: " << sales_count << std::endl;
    }
};

// 订单项
struct OrderItem {
    int product_id;
    int quantity;
};

// 订单结构体
struct Order {
    int id;
    std::vector<OrderItem> items;
    double total_price;
    time_t timestamp;

    void display() const {
        std::cout << "订单 ID: " << id << ", 总价: " << total_price << ", 商品数量: " << items.size() << std::endl;
    }
};