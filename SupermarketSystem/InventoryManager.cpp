//库存预警模块实现文件

#include "InventoryManager.h"

// 检查所有商品并更新预警堆
void InventoryManager::check_and_update(ProductManager& pm) {
    // 清空旧的堆
    while (!low_stock_heap.empty()) {
        low_stock_heap.pop();
    }

    // 遍历所有商品，将低于阈值的加入堆
    const auto& products = pm.get_products();
    for (const auto& pair : products) {
        Product* p = const_cast<Product*>(&pair.second);
        if (p->stock < alert_threshold) {
            low_stock_heap.push(p); // O(log n)
        }
    }
}

// 显示库存预警信息
void InventoryManager::show_alerts() {
    if (low_stock_heap.empty()) {
        std::cout << "\n--- 库存状态良好，无预警 ---\n";
        return;
    }
    std::cout << "\n--- !!! 库存预警 (低于 " << alert_threshold << ") !!! ---" << std::endl;
    std::cout << "--- (按库存从低到高排序) ---\n";

    // 临时复制堆以显示，不破坏原堆
    auto temp_heap = low_stock_heap;
    while (!temp_heap.empty()) {
        Product* p = temp_heap.top(); // O(1)
        temp_heap.pop(); // O(log n)
        std::cout << "  紧急! 商品: " << p->name << " (ID: " << p->id << ") 仅剩库存: " << p->stock << std::endl;
    }
}