//����ͳ��ģ��ʵ���ļ�

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
    std::cout << "\n--- �������а� Top " << k << " ---\n";
    if (sales_rank.empty()) {
        std::cout << "  �����������ݡ�\n";
        return;
    }

    int count = 0;
    // �������map����Ȼ�õ���������
    for (const auto& pair : sales_rank) {
        for (int product_id : pair.second) {
            if (count >= k) break;
            // ��Ϊpm���ǳ�Ա��������Ҫһ�ַ�ʽ�ҵ���Ʒ��Ϣ��
            // ��ʵ��Ӧ���У�������Ҫ����ProductManager�����á�
            // ����Ϊ����ʾ������ֻ��ʾID��������
            std::cout << "  ���� " << count + 1 << ": ��ƷID " << product_id
                << ", ����: " << pair.first << std::endl;
            count++;
        }
        if (count >= k) break;
    }
}