#pragma once

//����ͳ��ģ��ͷ�ļ�

#include "ProductManager.h"
#include <map>
#include <vector>

class StatisticsManager {
private:
    // ʹ��map(�����)ʵ�����а񣬼�Ϊ������ֵΪ��ƷID�б�
    // ʹ�� std::greater ʹ�䰴�����Ӹߵ�������
    using SalesRankMap = std::map<int, std::vector<int>, std::greater<int>>;
    SalesRankMap sales_rank;

public:
    void update_ranking(const ProductManager& pm);
    void display_top_k_sales(int k);
};