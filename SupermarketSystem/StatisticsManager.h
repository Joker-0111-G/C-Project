#pragma once

//销售统计模块头文件

#include "ProductManager.h"
#include <map>
#include <vector>

class StatisticsManager {
private:
    // 使用map(红黑树)实现排行榜，键为销量，值为商品ID列表
    // 使用 std::greater 使其按销量从高到低排序
    using SalesRankMap = std::map<int, std::vector<int>, std::greater<int>>;
    SalesRankMap sales_rank;

public:
    void update_ranking(const ProductManager& pm);
    void display_top_k_sales(int k);
};