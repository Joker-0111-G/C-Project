#pragma once

//���Ԥ��ģ��ͷ�ļ�

#include <queue> // ����ʵ�����ȶ���(��)
#include <vector>
#include "ProductManager.h"

// ����С���ѵ��Զ���Ƚ���
struct CompareStock {
    bool operator()(const Product* p1, const Product* p2) const {
        return p1->stock > p2->stock;
    }
};

class InventoryManager {
private:
    // ʹ�����ȶ���ʵ��С���ѣ��洢������͵���Ʒָ��
    std::priority_queue<Product*, std::vector<Product*>, CompareStock> low_stock_heap;
    int alert_threshold;

public:
    InventoryManager(int threshold = 20) : alert_threshold(threshold) {}
    void check_and_update(ProductManager& pm);
    void show_alerts();
};