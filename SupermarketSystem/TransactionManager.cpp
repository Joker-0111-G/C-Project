//交易处理模块实现文件

#include "TransactionManager.h"

bool TransactionManager::create_order(ProductManager& pm, const std::vector<OrderItem>& items) {
    Order new_order;
    new_order.id = next_order_id;
    new_order.items = items;
    new_order.total_price = 0;
    new_order.timestamp = time(0);

    // 检查库存并计算总价
    for (const auto& item : items) {
        Product* p = pm.find_product(item.product_id);
        if (!p || p->stock < item.quantity) {
            std::cout << "错误: 商品 " << (p ? p->name : std::to_string(item.product_id)) << " 库存不足!" << std::endl;
            return false;
        }
    }

    // 更新库存和销量并计算总价
    for (const auto& item : items) {
        Product* p = pm.find_product(item.product_id);
        p->stock -= item.quantity;
        p->sales_count += item.quantity;
        new_order.total_price += p->price * item.quantity;
    }

    order_queue.push(new_order);
    std::cout << "订单创建成功 (ID: " << new_order.id << ")，已加入处理队列。" << std::endl;
    next_order_id++;
    return true;
}

void TransactionManager::process_next_order() {
    if (order_queue.empty()) {
        std::cout << "没有待处理的订单。" << std::endl;
        return;
    }
    Order order_to_process = order_queue.front();
    order_queue.pop();
    std::cout << "\n--- 正在处理订单 ---" << std::endl;
    order_to_process.display();
    std::cout << "订单处理完毕。" << std::endl;
}

void TransactionManager::view_pending_orders() {
    if (order_queue.empty()) {
        std::cout << "没有待处理的订单。" << std::endl;
        return;
    }
    std::cout << "\n--- 当前待处理订单队列 ---" << std::endl;
    // C++ queue不支持直接遍历，我们复制一份来显示
    std::queue<Order> temp_queue = order_queue;
    while (!temp_queue.empty()) {
        temp_queue.front().display();
        temp_queue.pop();
    }
}