#pragma once

//���״���ģ��ͷ�ļ�

#include "DataModels.h"
#include <queue> // C++�еĶ���ʵ��
#include "ProductManager.h" // ��Ҫ������Ʒ��Ϣ

class TransactionManager {
private:
    std::queue<Order> order_queue; // ѭ�����У����ڴ�����
    int next_order_id = 1;

public:
    bool create_order(ProductManager& pm, const std::vector<OrderItem>& items);
    void process_next_order();
    void view_pending_orders();
};