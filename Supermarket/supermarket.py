import heapq
import time
from collections import deque
import json
import os

# ==============================================================================
# 1. 数据模型定义 (Data Models)
# ==============================================================================

class Category:
    """商品分类类"""
    def __init__(self, category_id, name, parent_id=0):
        self.id = category_id
        self.name = name
        self.parent_id = parent_id

class Product:
    """商品类，包含所有商品属性"""
    def __init__(self, product_id, name, price, stock, category_id):
        self.id = product_id
        self.name = name
        self.price = price
        self.stock = stock
        self.category_id = category_id
        self.sales_count = 0
        self.price_history = [(time.time(), price)] # 用于价格趋势分析

    def __str__(self):
        return f"  ID: {self.id:<4} | 名称: {self.name:<15} | 价格: {self.price:<8.2f} | 库存: {self.stock:<5} | 销量: {self.sales_count}"

class Order:
    """订单类"""
    def __init__(self, order_id, items):
        self.id = order_id
        self.items = items # 格式: [{"product": Product, "quantity": int}]
        self.total_price = sum(item["product"].price * item["quantity"] for item in items)
        self.timestamp = time.time()

    def __str__(self):
        return f"订单 ID: {self.id}, 总价: {self.total_price:.2f}, 商品种类: {len(self.items)}"

# ==============================================================================
# 2. 核心功能模块 (Core Modules)
# ==============================================================================

class ProductManager:
    """商品管理模块，使用哈希表(dict)存储商品，实现O(1)查找。"""
    def __init__(self):
        self.products = {}  # dict 作为哈希表, key: product_id, value: Product object
        self.categories = {} # dict 存储分类
        self._next_product_id = 1
        self._next_category_id = 1
        
    def initialize_default_category(self):
        if not self.categories:
             self.add_category("所有商品") # 添加根分类

    def add_category(self, name, parent_id=0):
        category_id = self._next_category_id
        self.categories[category_id] = Category(category_id, name, parent_id)
        self._next_category_id += 1
        print(f"成功添加分类: '{name}' (ID: {category_id})")
        return category_id

    def add_product(self, name, price, stock, category_id):
        if category_id not in self.categories:
            print(f"错误: 分类ID {category_id} 不存在。")
            return None
        product_id = self._next_product_id
        self.products[product_id] = Product(product_id, name, price, stock, category_id)
        self._next_product_id += 1
        print(f"成功添加商品: '{name}' (ID: {product_id})")
        return self.products[product_id]

    def find_product(self, product_id):
        return self.products.get(product_id) # dict.get() 是O(1)操作

    def update_product(self, product_id, new_price=None, new_stock=None):
        product = self.find_product(product_id)
        if not product:
            print(f"错误: 未找到商品 ID {product_id}。")
            return False
        if new_price is not None:
            product.price = new_price
            product.price_history.append((time.time(), new_price))
        if new_stock is not None:
            product.stock = new_stock
        print(f"成功更新商品 ID {product_id}。")
        return True

    def delete_product(self, product_id):
        if product_id in self.products:
            del self.products[product_id]
            print(f"成功删除商品 ID {product_id}。")
            return True
        print(f"错误: 未找到商品 ID {product_id}。")
        return False
        
    def display_products(self):
        print("\n--- 所有商品列表 ---")
        if not self.products:
            print("  商品库为空。")
            return
        for product in self.products.values():
            print(product)
    
    def display_categories(self):
        print("\n--- 商品分类树 ---")
        def _display_tree(parent_id, depth):
            for cat_id, category in self.categories.items():
                if category.parent_id == parent_id:
                    print("  " * depth + f"|- {category.name} (ID: {cat_id})")
                    _display_tree(cat_id, depth + 1)
        _display_tree(0, 0) # 从根节点开始

class TransactionManager:
    """交易处理模块，使用双端队列(deque)作为循环队列。"""
    def __init__(self, product_manager):
        self.order_queue = deque()
        self.product_manager = product_manager
        self._next_order_id = 1

    def create_order(self, items_to_buy): # items_to_buy: {product_id: quantity}
        order_items = []
        # 1. 检查库存
        for pid, qty in items_to_buy.items():
            product = self.product_manager.find_product(pid)
            if not product or product.stock < qty:
                print(f"错误: 商品 '{product.name if product else pid}' 库存不足或不存在。")
                return None
            order_items.append({"product": product, "quantity": qty})

        # 2. 更新库存和销量
        for item in order_items:
            product = item["product"]
            product.stock -= item["quantity"]
            product.sales_count += item["quantity"]

        # 3. 创建订单并入队
        order = Order(self._next_order_id, order_items)
        self.order_queue.append(order)
        self._next_order_id += 1
        print(f"订单创建成功 (ID: {order.id})，已加入处理队列。")
        return order

    def process_next_order(self):
        if not self.order_queue:
            print("没有待处理的订单。")
            return None
        order = self.order_queue.popleft() 
        print(f"\n--- 正在处理订单 (FIFO) ---")
        print(order)
        print("订单处理完毕。")
        return order

class InventoryManager:
    """库存预警模块，使用小顶堆(heapq)实现。"""
    def __init__(self, product_manager, threshold=20):
        self.product_manager = product_manager
        self.threshold = threshold

    def get_low_stock_alerts(self):
        low_stock_heap = []
        for product in self.product_manager.products.values():
            if product.stock < self.threshold:
                heapq.heappush(low_stock_heap, (product.stock, product))
        return low_stock_heap

    def show_alerts(self):
        print(f"\n--- !!! 库存预警 (低于 {self.threshold}) !!! ---")
        alerts = self.get_low_stock_alerts()
        if not alerts:
            print("  库存状态良好，无预警。")
            return
        
        while alerts:
            stock, product = heapq.heappop(alerts)
            print(f"  紧急! 商品: {product.name} (ID: {product.id}) 仅剩库存: {stock}")

class StatisticsManager:
    """销售统计模块"""
    def __init__(self, product_manager):
        self.product_manager = product_manager

    def get_sales_ranking_top_k(self, k):
        print(f"\n--- 销售排行榜 Top {k} ---")
        all_products = list(self.product_manager.products.values())
        if not all_products or k <= 0:
            print("  无商品或K值无效。")
            return

        top_k_heap = []
        for product in all_products:
            if len(top_k_heap) < k:
                heapq.heappush(top_k_heap, (product.sales_count, product.id, product.name))
            elif product.sales_count > top_k_heap[0][0]:
                heapq.heapreplace(top_k_heap, (product.sales_count, product.id, product.name))
        
        if not top_k_heap:
            print("  暂无销售数据。")
            return
            
        top_k_list = sorted(top_k_heap, key=lambda item: item[0], reverse=True)
        
        for i, (sales, pid, name) in enumerate(top_k_list, 1):
            print(f"  排名 {i}: {name} (ID: {pid}), 销量: {sales}")


# ==============================================================================
# 3. 主程序 & UI (Main Application & UI with Full Menus)
# ==============================================================================

class SupermarketSystem:
    def __init__(self, data_file="s.txt"):
        self.data_file = data_file
        self.pm = ProductManager()
        self.tm = TransactionManager(self.pm)
        self.im = InventoryManager(self.pm, threshold=30)
        self.sm = StatisticsManager(self.pm)
        self.load_data()

    def save_data(self):
        """将核心数据转换为可序列化的字典并保存为JSON文件"""
        data = {
            "products": {pid: p.__dict__ for pid, p in self.pm.products.items()},
            "categories": {cid: c.__dict__ for cid, c in self.pm.categories.items()},
            "_next_product_id": self.pm._next_product_id,
            "_next_category_id": self.pm._next_category_id,
        }
        try:
            with open(self.data_file, 'w', encoding='utf-8') as f:
                json.dump(data, f, indent=4, ensure_ascii=False)
            print(f"\n数据已成功保存到 {self.data_file}")
        except Exception as e:
            print(f"\n保存数据时发生错误: {e}")
        
    def load_data(self):
        """从JSON文件加载数据并重建对象"""
        if not os.path.exists(self.data_file):
            print(f"未找到数据文件 {self.data_file}，将创建初始数据。")
            self._populate_initial_data()
            return
            
        try:
            with open(self.data_file, 'r', encoding='utf-8') as f:
                data = json.load(f)
            
            for cid, c_data in data["categories"].items():
                self.pm.categories[int(cid)] = Category(**c_data)

            for pid, p_data in data["products"].items():
                self.pm.products[int(pid)] = Product(
                    p_data['id'], p_data['name'], p_data['price'], 
                    p_data['stock'], p_data['category_id']
                )
                # 兼容旧数据，安全地加载附加属性
                self.pm.products[int(pid)].sales_count = p_data.get('sales_count', 0)
                self.pm.products[int(pid)].price_history = p_data.get('price_history', [])

            self.pm._next_product_id = data.get("_next_product_id", 1)
            self.pm._next_category_id = data.get("_next_category_id", 1)

            print(f"数据已从 {self.data_file} 成功加载")
        except Exception as e:
            print(f"加载数据时发生错误: {e}。将使用初始数据。")
            self._populate_initial_data()
            
    def _populate_initial_data(self):
        """如果无法加载数据，则创建一组初始数据用于演示"""
        print("--- 正在创建初始演示数据 ---")
        self.pm.initialize_default_category()
        cat1 = self.pm.add_category("饮料", 1)
        cat2 = self.pm.add_category("零食", 1)
        self.pm.add_product("可口可乐", 3.5, 100, cat1)
        self.pm.add_product("薯片", 5.0, 50, cat2)
        self.pm.add_product("矿泉水", 2.0, 25, cat1)
        print("--------------------------\n")

    def run(self):
        while True:
            print("\n===== 欢迎使用Python超市管理系统 =====")
            print("1. 商品管理")
            print("2. 交易处理")
            print("3. 报告与统计")
            print("4. 手动保存数据")
            print("0. 退出系统 (自动保存)")
            choice = input("请输入您的选择: ")

            if choice == '1':
                self.menu_product()
            elif choice == '2':
                self.menu_transaction()
            elif choice == '3':
                self.menu_report()
            elif choice == '4':
                self.save_data()
            elif choice == '0':
                self.save_data()
                print("感谢使用，系统退出。")
                break
            else:
                print("无效的选择，请重新输入。")

    def menu_product(self):
        while True:
            print("\n--- 商品管理菜单 ---")
            print("1. 添加商品")
            print("2. 更新商品")
            print("3. 删除商品")
            print("4. 查找商品")
            print("5. 显示所有商品")
            print("6. 添加分类")
            print("7. 显示分类树")
            print("0. 返回主菜单")
            choice = input("请输入选择: ")
            try:
                if choice == '1':
                    name = input("输入商品名称: ")
                    price = float(input("输入价格: "))
                    stock = int(input("输入库存: "))
                    cat_id = int(input("输入分类ID: "))
                    self.pm.add_product(name, price, stock, cat_id)
                elif choice == '2':
                    pid = int(input("输入要更新的商品ID: "))
                    price_str = input("输入新价格 (直接回车则不修改): ")
                    stock_str = input("输入新库存 (直接回车则不修改): ")
                    new_price = float(price_str) if price_str else None
                    new_stock = int(stock_str) if stock_str else None
                    self.pm.update_product(pid, new_price, new_stock)
                elif choice == '3':
                    pid = int(input("输入要删除的商品ID: "))
                    self.pm.delete_product(pid)
                elif choice == '4':
                    pid = int(input("输入要查找的商品ID: "))
                    product = self.pm.find_product(pid)
                    if product:
                        print("找到商品:")
                        print(product)
                    else:
                        print("未找到该商品。")
                elif choice == '5':
                    self.pm.display_products()
                elif choice == '6':
                    name = input("输入分类名称: ")
                    parent_id = int(input("输入父分类ID (根分类输入0): "))
                    self.pm.add_category(name, parent_id)
                elif choice == '7':
                    self.pm.display_categories()
                elif choice == '0':
                    break
                else:
                    print("无效选择。")
            except ValueError:
                print("输入格式错误，请输入有效的数字。")
            except Exception as e:
                print(f"发生未知错误: {e}")

    def menu_transaction(self):
        print("\n--- 交易处理菜单 ---")
        print("1. 创建新订单")
        print("2. 处理下一笔订单")
        print("0. 返回主菜单")
        choice = input("请输入选择: ")
        if choice == '1':
            try:
                items_to_buy = {}
                while True:
                    pid_str = input("输入商品ID (输入'f'完成添加): ")
                    if pid_str.lower() == 'f':
                        break
                    pid = int(pid_str)
                    if not self.pm.find_product(pid):
                        print("商品ID不存在，请重新输入。")
                        continue
                    qty = int(input(f"输入商品 {pid} 的数量: "))
                    items_to_buy[pid] = items_to_buy.get(pid, 0) + qty
                
                if items_to_buy:
                    self.tm.create_order(items_to_buy)
                else:
                    print("未添加任何商品。")
            except ValueError:
                print("输入格式错误，请输入有效的数字。")
        elif choice == '2':
            self.tm.process_next_order()
        elif choice == '0':
            return
        else:
            print("无效选择。")

    def menu_report(self):
        print("\n--- 报告与统计菜单 ---")
        print("1. 显示库存预警")
        print("2. 显示销售排行榜")
        print("0. 返回主菜单")
        choice = input("请输入选择: ")
        if choice == '1':
            self.im.show_alerts()
        elif choice == '2':
            try:
                k = int(input("请输入要查看的销售排行榜Top K: "))
                self.sm.get_sales_ranking_top_k(k)
            except ValueError:
                print("请输入有效的数字K。")
        elif choice == '0':
            return
        else:
            print("无效选择。")

if __name__ == "__main__":
    system = SupermarketSystem()
    system.run()