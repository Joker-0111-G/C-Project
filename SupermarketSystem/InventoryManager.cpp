//���Ԥ��ģ��ʵ���ļ�

#include "InventoryManager.h"

// ���������Ʒ������Ԥ����
void InventoryManager::check_and_update(ProductManager& pm) {
    // ��վɵĶ�
    while (!low_stock_heap.empty()) {
        low_stock_heap.pop();
    }

    // ����������Ʒ����������ֵ�ļ����
    const auto& products = pm.get_products();
    for (const auto& pair : products) {
        Product* p = const_cast<Product*>(&pair.second);
        if (p->stock < alert_threshold) {
            low_stock_heap.push(p); // O(log n)
        }
    }
}

// ��ʾ���Ԥ����Ϣ
void InventoryManager::show_alerts() {
    if (low_stock_heap.empty()) {
        std::cout << "\n--- ���״̬���ã���Ԥ�� ---\n";
        return;
    }
    std::cout << "\n--- !!! ���Ԥ�� (���� " << alert_threshold << ") !!! ---" << std::endl;
    std::cout << "--- (�����ӵ͵�������) ---\n";

    // ��ʱ���ƶ�����ʾ�����ƻ�ԭ��
    auto temp_heap = low_stock_heap;
    while (!temp_heap.empty()) {
        Product* p = temp_heap.top(); // O(1)
        temp_heap.pop(); // O(log n)
        std::cout << "  ����! ��Ʒ: " << p->name << " (ID: " << p->id << ") ��ʣ���: " << p->stock << std::endl;
    }
}