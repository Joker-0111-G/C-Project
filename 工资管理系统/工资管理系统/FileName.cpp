#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 员工工资信息结构体
typedef struct Employee {
    char employee_id[20]; // 人员编号
    char name[50];        // 姓名
    double base_salary;   // 基本工资
    double allowance;     // 津贴
    double bonus;         // 奖励
    double deductions;    // 扣除 (您可以根据需要增加，这里作为示例)
    double total_salary;  // 总工资 (计算得出)
    int month;            // 月份
    int year;             // 年份
    // 根据具体需求可以添加其他字段
} Employee;

// 链表节点结构体
typedef struct Node {
    Employee data;
    struct Node* next;
} Node;

// 全局链表头指针（也可以作为参数传递）
Node* head = NULL; // 初始化为空，表示链表为空


// 创建新节点函数
Node* createNode(Employee emp_data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        exit(1); // 内存分配失败，程序退出
    }
    newNode->data = emp_data;
    newNode->next = NULL;
    return newNode;
}

// 添加员工工资记录函数
void addEmployeeRecord() {
    Employee emp;
    printf("\n--- 输入员工工资记录 ---\n");
    printf("请输入员工编号: ");
    scanf("%s", emp.employee_id);
    printf("请输入姓名: ");
    scanf("%s", emp.name);
    printf("请输入基本工资: ");
    scanf("%lf", &emp.base_salary);
    printf("请输入津贴: ");
    scanf("%lf", &emp.allowance);
    printf("请输入奖励: ");
    scanf("%lf", &emp.bonus);
    printf("请输入扣除项 (如果没有请输入0): ");
    scanf("%lf", &emp.deductions);
    printf("请输入月份 (1-12): ");
    scanf("%d", &emp.month);
    printf("请输入年份: ");
    scanf("%d", &emp.year);

    // 计算总工资
    emp.total_salary = emp.base_salary + emp.allowance + emp.bonus - emp.deductions;

    Node* newNode = createNode(emp);
    if (head == NULL) {
        head = newNode; // 如果链表为空，新节点即为头节点
    }
    else {
        Node* current = head;
        while (current->next != NULL) {
            current = current->next; // 遍历到链表末尾
        }
        current->next = newNode; // 将新节点添加到链表末尾
    }
    printf("员工记录添加成功！\n");
}

// 按月份显示所有记录
void displayAllRecordsByMonth(int month, int year) {
    if (head == NULL) {
        printf("目前没有工资记录。\n");
        return;
    }
    printf("\n--- %d年%d月的工资记录 ---\n", year, month);
    Node* current = head;
    int found = 0;
    while (current != NULL) {
        if (current->data.month == month && current->data.year == year) {
            printf("编号: %s, 姓名: %s, 月份: %d/%d, 基本工资: %.2lf, 津贴: %.2lf, 奖励: %.2lf, 扣除: %.2lf, 总工资: %.2lf\n",
                current->data.employee_id, current->data.name, current->data.month, current->data.year,
                current->data.base_salary, current->data.allowance, current->data.bonus, current->data.deductions, current->data.total_salary);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("未找到%d年%d月的记录。\n", year, month);
    }
}

// 查询并显示特定员工的记录
void queryEmployeeRecords(char* employee_id) {
    if (head == NULL) {
        printf("目前没有工资记录。\n");
        return;
    }
    printf("\n--- 员工编号: %s 的工资记录 ---\n", employee_id);
    Node* current = head;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->data.employee_id, employee_id) == 0) {
            printf("月份: %d/%d, 基本工资: %.2lf, 津贴: %.2lf, 奖励: %.2lf, 扣除: %.2lf, 总工资: %.2lf\n",
                current->data.month, current->data.year, current->data.base_salary,
                current->data.allowance, current->data.bonus, current->data.deductions, current->data.total_salary);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("未找到员工编号: %s 的记录。\n", employee_id);
    }
}

// 更新员工特定月份的工资记录
void updateEmployeeRecord(char* employee_id, int month, int year) {
    if (head == NULL) {
        printf("没有可更新的工资记录。\n");
        return;
    }
    Node* current = head;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->data.employee_id, employee_id) == 0 &&
            current->data.month == month && current->data.year == year) {
            printf("\n--- 正在更新员工 %s (%d年%d月) 的记录 ---\n", employee_id, year, month);
            printf("输入新的基本工资 (当前: %.2lf): ", current->data.base_salary);
            scanf("%lf", &current->data.base_salary);
            printf("输入新的津贴 (当前: %.2lf): ", current->data.allowance);
            scanf("%lf", &current->data.allowance);
            printf("输入新的奖励 (当前: %.2lf): ", current->data.bonus);
            scanf("%lf", &current->data.bonus);
            printf("输入新的扣除项 (当前: %.2lf): ", current->data.deductions);
            scanf("%lf", &current->data.deductions);

            current->data.total_salary = current->data.base_salary + current->data.allowance + current->data.bonus - current->data.deductions;
            printf("记录更新成功！\n");
            found = 1;
            break;
        }
        current = current->next;
    }
    if (!found) {
        printf("未找到员工 %s 在 %d年%d月 的记录。\n", employee_id, year, month);
    }
}

// 删除员工特定月份的工资记录
void deleteEmployeeRecord(char* employee_id, int month, int year) {
    if (head == NULL) {
        printf("没有可删除的工资记录。\n");
        return;
    }

    Node* current = head;
    Node* prev = NULL;
    int found = 0;

    // 特殊情况：删除头节点
    if (current != NULL && strcmp(current->data.employee_id, employee_id) == 0 &&
        current->data.month == month && current->data.year == year) {
        head = current->next; // 头节点指向下一个节点
        free(current); // 释放原头节点内存
        printf("记录删除成功！\n");
        return;
    }

    // 遍历链表查找要删除的节点
    while (current != NULL && (strcmp(current->data.employee_id, employee_id) != 0 ||
        current->data.month != month || current->data.year != year)) {
        prev = current; // 记录当前节点的前一个节点
        current = current->next; // 移动到下一个节点
    }

    // 如果 current 为空，表示未找到
    if (current == NULL) {
        printf("未找到员工 %s 在 %d年%d月 的记录。\n", employee_id, year, month);
        return;
    }

    // 找到节点，进行删除操作
    prev->next = current->next; // 前一个节点的next指向当前节点的next
    free(current); // 释放当前节点内存
    printf("记录删除成功！\n");
}

// 生成特定员工的统计信息
void generateEmployeeStatistics(char* employee_id) {
    if (head == NULL) {
        printf("目前没有工资记录。\n");
        return;
    }
    double total_salary_employee = 0.0;
    int found = 0;
    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->data.employee_id, employee_id) == 0) {
            total_salary_employee += current->data.total_salary;
            found = 1;
        }
        current = current->next;
    }
    if (found) {
        printf("\n--- 员工编号: %s 的统计信息 ---\n", employee_id);
        printf("所有记录月份的总工资: %.2lf\n", total_salary_employee);
    }
    else {
        printf("未找到员工编号: %s 的记录。\n", employee_id);
    }
}

// 生成特定月份的统计信息
void generateMonthlyStatistics(int month, int year) {
    if (head == NULL) {
        printf("目前没有工资记录。\n");
        return;
    }
    double total_payroll_month = 0.0;
    int found = 0;
    Node* current = head;
    while (current != NULL) {
        if (current->data.month == month && current->data.year == year) {
            total_payroll_month += current->data.total_salary;
            found = 1;
        }
        current = current->next;
    }
    if (found) {
        printf("\n--- %d年%d月的月度统计信息 ---\n", year, month);
        printf("该月的总工资支出: %.2lf\n", total_payroll_month);
    }
    else {
        printf("未找到%d年%d月的记录。\n", year, month);
    }
}

// 显示所有员工工资记录
void displayAllRecords() {
    if (head == NULL) {
        printf("目前没有工资记录。\n");
        return;
    }
    printf("\n--- 所有员工工资记录 ---\n");
    Node* current = head;
    while (current != NULL) {
        printf("编号: %s, 姓名: %s, 月份: %d/%d, 基本工资: %.2lf, 津贴: %.2lf, 奖励: %.2lf, 扣除: %.2lf, 总工资: %.2lf\n",
            current->data.employee_id, current->data.name, current->data.month, current->data.year,
            current->data.base_salary, current->data.allowance, current->data.bonus, current->data.deductions, current->data.total_salary);
        current = current->next;
    }
}

// 将工资记录保存到文件
void saveRecordsToFile(char* filename) {
    FILE* fp = fopen(filename, "wb"); // 使用 "wb" 进行二进制写入
    if (fp == NULL) {
        printf("打开文件 %s 写入失败！\n", filename);
        return;
    }
    Node* current = head;
    while (current != NULL) {
        fwrite(&(current->data), sizeof(Employee), 1, fp); // 写入Employee结构体数据
        current = current->next;
    }
    fclose(fp);
    printf("工资记录已成功保存到 %s！\n", filename);
}

// 从文件加载工资记录
void loadRecordsFromFile(char* filename) {
    FILE* fp = fopen(filename, "rb"); // 使用 "rb" 进行二进制读取
    if (fp == NULL) {
        printf("打开文件 %s 读取失败，或者文件不存在。将从空记录开始。\n", filename);
        return;
    }

    // 加载前清空现有记录，避免重复
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL; // 确保头指针清空

    Employee emp_data;
    while (fread(&emp_data, sizeof(Employee), 1, fp) == 1) { // 循环读取Employee结构体数据
        Node* newNode = createNode(emp_data);
        if (head == NULL) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    fclose(fp);
    printf("工资记录已成功从 %s 加载！\n", filename);
}

// 释放链表中所有节点的内存
void freeLinkedList() {
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL; // 确保头指针清空
}

int main() {
    int choice;
    char emp_id[20];
    int month, year;
    char filename[] = "a.txt"; // 默认用于保存/加载的文件名

    loadRecordsFromFile(filename); // 程序启动时尝试从文件加载数据

    do {
        printf("\n--- 工资管理系统菜单 ---\n");
        printf("1. 输入记录 (添加员工工资)\n");
        printf("2. 查询记录 (按月份或按员工编号)\n");
        printf("3. 更新/删除记录\n");
        printf("4. 统计 (按员工或按月份)\n");
        printf("5. 输出所有记录\n");
        printf("6. 保存记录到文件\n");
        printf("7. 从文件加载记录\n");
        printf("0. 退出\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addEmployeeRecord();
            break;
        case 2:
            printf("查询选项:\n");
            printf("  1. 显示特定月份的所有记录\n");
            printf("  2. 查询特定员工的记录\n");
            printf("请输入查询选项: ");
            int query_choice;
            scanf("%d", &query_choice);
            if (query_choice == 1) {
                printf("请输入月份 (1-12): ");
                scanf("%d", &month);
                printf("请输入年份: ");
                scanf("%d", &year);
                displayAllRecordsByMonth(month, year);
            }
            else if (query_choice == 2) {
                printf("请输入要查询的员工编号: ");
                scanf("%s", emp_id);
                queryEmployeeRecords(emp_id);
            }
            else {
                printf("无效的查询选项。\n");
            }
            break;
        case 3:
            printf("更新/删除选项:\n");
            printf("  1. 更新记录\n");
            printf("  2. 删除记录\n");
            printf("请输入选项: ");
            int ud_choice;
            scanf("%d", &ud_choice);
            printf("请输入员工编号: ");
            scanf("%s", emp_id);
            printf("请输入月份 (1-12): ");
            scanf("%d", &month);
            printf("请输入年份: ");
            scanf("%d", &year);
            if (ud_choice == 1) {
                updateEmployeeRecord(emp_id, month, year);
            }
            else if (ud_choice == 2) {
                deleteEmployeeRecord(emp_id, month, year);
            }
            else {
                printf("无效的选项。\n");
            }
            break;
        case 4:
            printf("统计选项:\n");
            printf("  1. 生成特定员工的统计信息\n");
            printf("  2. 生成月度统计信息\n");
            printf("请输入统计选项: ");
            int stats_choice;
            scanf("%d", &stats_choice);
            if (stats_choice == 1) {
                printf("请输入要统计的员工编号: ");
                scanf("%s", emp_id);
                generateEmployeeStatistics(emp_id);
            }
            else if (stats_choice == 2) {
                printf("请输入要统计的月份 (1-12): ");
                scanf("%d", &month);
                printf("请输入年份: ");
                scanf("%d", &year);
                generateMonthlyStatistics(month, year);
            }
            else {
                printf("无效的统计选项。\n");
            }
            break;
        case 5:
            displayAllRecords();
            break;
        case 6:
            saveRecordsToFile(filename);
            break;
        case 7:
            loadRecordsFromFile(filename);
            break;
        case 0:
            printf("正在退出工资管理系统。再见！\n");
            break;
        default:
            printf("无效的选择。请重试。\n");
        }
    } while (choice != 0);

    freeLinkedList(); // 程序退出前释放所有分配的内存
    return 0;
}