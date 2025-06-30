#pragma once // ��ֹͷ�ļ����ظ�����

//�������ݽṹ

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

// ��Ʒ����ṹ��
struct Category {
    int id;
    std::string name;
    int parent_id; // 0 ��ʾ������

    Category(int i = 0, std::string n = "", int p_id = 0) : id(i), name(n), parent_id(p_id) {}
};

// ��Ʒ�ṹ��
struct Product {
    int id;
    std::string name;
    double price;
    int stock;
    int category_id;
    int sales_count = 0; // ��������

    Product(int i = 0, std::string n = "", double p = 0.0, int s = 0, int cat_id = 0)
        : id(i), name(n), price(p), stock(s), category_id(cat_id) {}

    void display() const {
        std::cout << "  ID: " << id << ", ����: " << name << ", �۸�: " << price
            << ", ���: " << stock << ", ����: " << sales_count << std::endl;
    }
};

// ������
struct OrderItem {
    int product_id;
    int quantity;
};

// �����ṹ��
struct Order {
    int id;
    std::vector<OrderItem> items;
    double total_price;
    time_t timestamp;

    void display() const {
        std::cout << "���� ID: " << id << ", �ܼ�: " << total_price << ", ��Ʒ����: " << items.size() << std::endl;
    }
};