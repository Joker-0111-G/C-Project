#include <iostream>
#include <limits>
#include "ProductManager.h"
#include "TransactionManager.h"
#include "InventoryManager.h"
#include "StatisticsManager.h"

void display_menu() {
    std::cout << "\n===== 超市管理系统 =====\n";
    std::cout << "1.  商品管理\n";
    std::cout << "2.  交易处理\n";
    std::cout << "3.  库存与销售报告\n";
    std::cout << "0.  退出系统\n";
    std::cout << "========================\n";
    std::cout << "请输入您的选择: ";
}

void product_menu(ProductManager& pm) {
    int choice;
    while (true) {
        std::cout << "\n--- 商品管理菜单 ---\n";
        std::cout << "1. 添加商品\n";
        std::cout << "2. 删除商品\n";
        std::cout << "3. 更新商品\n";
        std::cout << "4. 查找商品\n";
        std::cout << "5. 显示所有商品\n";
        std::cout << "6. 添加分类\n";
        std::cout << "7. 显示分类树\n";
        std::cout << "0. 返回主菜单\n";
        std::cout << "请输入您的选择: ";
        std::cin >> choice;

        if (choice == 0) break;

        // 处理非数字输入
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入无效，请输入数字。\n";
            continue;
        }

        if (choice == 1) {
            std::string name;
            double price;
            int stock, cat_id;
            std::cout << "输入商品名称: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "输入价格: ";
            std::cin >> price;
            std::cout << "输入库存: ";
            std::cin >> stock;
            std::cout << "输入分类ID: ";
            std::cin >> cat_id;
            pm.add_product(name, price, stock, cat_id);
        }
        else if (choice == 5) {
            pm.display_all_products();
        }
        else if (choice == 7) {
            pm.display_categories();
        }
        // ... 其他选项的实现 ...
    }
}

void transaction_menu(TransactionManager& tm, ProductManager& pm) {
    int choice;
    while (true) {
        std::cout << "\n--- 交易处理菜单 ---\n";
        std::cout << "1. 创建新订单\n";
        std::cout << "2. 处理下一笔订单\n";
        std::cout << "3. 查看待处理订单\n";
        std::cout << "0. 返回主菜单\n";
        std::cout << "请输入您的选择: ";
        std::cin >> choice;

        if (choice == 0) break;
        // ... 实现交易菜单逻辑 ...
        if (choice == 1) {
            std::vector<OrderItem> items;
            int product_id, quantity;
            while (true) {
                std::cout << "输入商品ID (输入0完成): ";
                std::cin >> product_id;
                if (product_id == 0) break;
                std::cout << "输入数量: ";
                std::cin >> quantity;
                items.push_back({ product_id, quantity });
            }
            if (!items.empty()) {
                tm.create_order(pm, items);
            }
        }
        else if (choice == 2) {
            tm.process_next_order();
        }
        else if (choice == 3) {
            tm.view_pending_orders();
        }
    }
}

void report_menu(InventoryManager& im, StatisticsManager& sm, ProductManager& pm) {
    // 每次进入报告菜单都更新数据
    im.check_and_update(pm);
    sm.update_ranking(pm);

    int choice;
    while (true) {
        std::cout << "\n--- 报告菜单 ---\n";
        std::cout << "1. 显示库存预警\n";
        std::cout << "2. 显示销售排行榜\n";
        std::cout << "0. 返回主菜单\n";
        std::cout << "请输入您的选择: ";
        std::cin >> choice;
        if (choice == 0) break;

        if (choice == 1) {
            im.show_alerts();
        }
        else if (choice == 2) {
            int k;
            std::cout << "输入要查看的Top K排名: ";
            std::cin >> k;
            sm.display_top_k_sales(k);
        }
    }
}


int main() {
    // 设置本地化，以正确显示中文
    setlocale(LC_ALL, "");

    ProductManager pm;
    TransactionManager tm;
    InventoryManager im(30); // 设置库存预警阈值为30
    StatisticsManager sm;

    // 添加一些初始数据用于测试
    pm.add_category("饮料", 1);
    pm.add_category("零食", 1);
    pm.add_product("可口可乐", 3.5, 100, 2);
    pm.add_product("薯片", 5.0, 50, 3);
    pm.add_product("矿泉水", 2.0, 25, 2);


    int choice;
    while (true) {
        display_menu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入无效，请输入数字。\n";
            continue;
        }

        switch (choice) {
        case 1:
            product_menu(pm);
            break;
        case 2:
            transaction_menu(tm, pm);
            break;
        case 3:
            report_menu(im, sm, pm);
            break;
        case 0:
            std::cout << "感谢使用，系统退出。\n";
            return 0;
        default:
            std::cout << "无效的选择，请重新输入。\n";
        }
    }

    return 0;
}