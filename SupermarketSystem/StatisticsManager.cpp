//销售统计模块实现文件

#include "StatisticsManager.h"
#include <algorithm>

void StatisticsManager::update_ranking(const ProductManager& pm) {
    sales_rank.clear();
    const auto& products = pm.get_products();
    for (const auto& pair : products) {
        if (pair.second.sales_count > 0) {
            sales_rank[pair.second.sales_count].push_back(pair.second.id);
        }
    }
}

void StatisticsManager::display_top_k_sales(int k) {
    std::cout << "\n--- 销售排行榜 Top " << k << " ---\n";
    if (sales_rank.empty()) {
        std::cout << "  暂无销售数据。\n";
        return;
    }

    int count = 0;
    // 中序遍历map会自然得到有序序列
    for (const auto& pair : sales_rank) {
        for (int product_id : pair.second) {
            if (count >= k) break;
            // 因为pm不是成员，我们需要一种方式找到产品信息。
            // 在实际应用中，可能需要传递ProductManager的引用。
            // 这里为了演示，我们只显示ID和销量。
            std::cout << "  排名 " << count + 1 << ": 商品ID " << product_id
                << ", 销量: " << pair.first << std::endl;
            count++;
        }
        if (count >= k) break;
    }
}