#pragma once

//交易处理模块头文件

#include "DataModels.h"
#include <queue> // C++中的队列实现
#include "ProductManager.h" // 需要访问商品信息

class TransactionManager {
private:
    std::queue<Order> order_queue; // 循环队列，用于处理订单
    int next_order_id = 1;

public:
    bool create_order(ProductManager& pm, const std::vector<OrderItem>& items);
    void process_next_order();
    void view_pending_orders();
};