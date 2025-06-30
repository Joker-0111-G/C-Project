# 超市管理系统（Supermarket System）

## 项目简介

本项目为一个基于C++的超市管理系统，旨在实现商品管理、库存管理、交易管理和统计分析等功能，适用于中小型超市的信息化管理需求。

## 功能介绍

- 商品管理：添加、删除、修改、查询商品信息
- 库存管理：进货、出库、库存查询与预警
- 交易管理：销售记录、交易查询
- 统计分析：销售统计、库存统计等

## 编译与运行方法

1. **环境要求**：
   - Windows 10 及以上
   - Visual Studio 2019 或更高版本
   - 支持C++17标准
2. **编译步骤**：
   - 使用 Visual Studio 打开 `SupermarketSystem.sln` 解决方案文件。
   - 选择"生成"菜单下的"生成解决方案"进行编译。
3. **运行方法**：
   - 编译成功后，在 `x64/Debug/` 目录下找到 `SupermarketSystem.exe`，双击运行即可。

## 主要文件说明

- `SupermarketSystem/`
  - `SupermarketSystem.cpp`：主程序入口
  - `ProductManager.*`：商品管理模块
  - `InventoryManager.*`：库存管理模块
  - `TransactionManager.*`：交易管理模块
  - `StatisticsManager.*`：统计分析模块
  - `DataModels.h`：数据模型定义
- `SupermarketSystem.sln`：Visual Studio 解决方案文件

---

如有问题或建议，欢迎联系作者。 
