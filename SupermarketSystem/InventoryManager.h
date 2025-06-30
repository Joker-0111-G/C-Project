#pragma once

//库存预警模块头文件

#include <queue> // 用于实现优先队列(堆)
#include <vector>
#include "ProductManager.h"

// 用于小顶堆的自定义比较器
struct CompareStock {
    bool operator()(const Product* p1, const Product* p2) const {
        return p1->stock > p2->stock;
    }
};

class InventoryManager {
private:
    // 使用优先队列实现小顶堆，存储库存量低的商品指针
    std::priority_queue<Product*, std::vector<Product*>, CompareStock> low_stock_heap;
    int alert_threshold;

public:
    InventoryManager(int threshold = 20) : alert_threshold(threshold) {}
    void check_and_update(ProductManager& pm);
    void show_alerts();
};