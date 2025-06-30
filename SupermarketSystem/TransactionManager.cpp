//���״���ģ��ʵ���ļ�

#include "TransactionManager.h"

bool TransactionManager::create_order(ProductManager& pm, const std::vector<OrderItem>& items) {
    Order new_order;
    new_order.id = next_order_id;
    new_order.items = items;
    new_order.total_price = 0;
    new_order.timestamp = time(0);

    // ����沢�����ܼ�
    for (const auto& item : items) {
        Product* p = pm.find_product(item.product_id);
        if (!p || p->stock < item.quantity) {
            std::cout << "����: ��Ʒ " << (p ? p->name : std::to_string(item.product_id)) << " ��治��!" << std::endl;
            return false;
        }
    }

    // ���¿��������������ܼ�
    for (const auto& item : items) {
        Product* p = pm.find_product(item.product_id);
        p->stock -= item.quantity;
        p->sales_count += item.quantity;
        new_order.total_price += p->price * item.quantity;
    }

    order_queue.push(new_order);
    std::cout << "���������ɹ� (ID: " << new_order.id << ")���Ѽ��봦����С�" << std::endl;
    next_order_id++;
    return true;
}

void TransactionManager::process_next_order() {
    if (order_queue.empty()) {
        std::cout << "û�д�����Ķ�����" << std::endl;
        return;
    }
    Order order_to_process = order_queue.front();
    order_queue.pop();
    std::cout << "\n--- ���ڴ����� ---" << std::endl;
    order_to_process.display();
    std::cout << "����������ϡ�" << std::endl;
}

void TransactionManager::view_pending_orders() {
    if (order_queue.empty()) {
        std::cout << "û�д�����Ķ�����" << std::endl;
        return;
    }
    std::cout << "\n--- ��ǰ������������ ---" << std::endl;
    // C++ queue��֧��ֱ�ӱ��������Ǹ���һ������ʾ
    std::queue<Order> temp_queue = order_queue;
    while (!temp_queue.empty()) {
        temp_queue.front().display();
        temp_queue.pop();
    }
}