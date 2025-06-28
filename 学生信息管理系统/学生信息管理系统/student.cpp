#define _CRT_SECURE_NO_WARNINGS
#include "student.h"

// 清空输入缓冲区
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 检查学号是否唯一
int isIdUnique(Node* head, const char* id) {
    Node* p = head->next;
    while (p != NULL) {
        if (strcmp(p->data.id, id) == 0) {
            return 0; // 不唯一
        }
        p = p->next;
    }
    return 1; // 唯一
}

// 1. 输入记录模块
void addStudent(Node* head) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        return;
    }

    printf("请输入学号: ");
    scanf("%s", newNode->data.id);
    clearInputBuffer();

    if (!isIdUnique(head, newNode->data.id)) {
        printf("错误：该学号已存在！\n");
        free(newNode);
        return;
    }

    printf("请输入姓名: ");
    scanf("%s", newNode->data.name);
    clearInputBuffer();
    printf("请输入性别: ");
    scanf("%s", newNode->data.gender);
    clearInputBuffer();
    printf("请输入年龄: ");
    scanf("%d", &newNode->data.age);
    clearInputBuffer();
    printf("请输入班级: ");
    scanf("%s", newNode->data.className);
    clearInputBuffer();

    newNode->next = NULL;

    // 找到链表尾部并插入
    Node* p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = newNode;

    printf("\n学生信息添加成功！\n");
}

// 2. 查询记录模块
void searchStudentById(Node* head) {
    if (head->next == NULL) {
        printf("当前无任何学生信息。\n");
        return;
    }
    char id[20];
    printf("请输入要查询的学号: ");
    scanf("%s", id);
    clearInputBuffer();

    Node* p = head->next;
    int found = 0;
    while (p != NULL) {
        if (strcmp(p->data.id, id) == 0) {
            printf("\n查询成功，学生信息如下:\n");
            printf("学号: %s, 姓名: %s, 性别: %s, 年龄: %d, 班级: %s\n",
                p->data.id, p->data.name, p->data.gender, p->data.age, p->data.className);
            found = 1;
            break;
        }
        p = p->next;
    }

    if (!found) {
        printf("未找到学号为 %s 的学生。\n", id);
    }
}

void searchStudentByName(Node* head) {
    if (head->next == NULL) {
        printf("当前无任何学生信息。\n");
        return;
    }
    char name[50];
    printf("请输入要查询的姓名: ");
    scanf("%s", name);
    clearInputBuffer();

    Node* p = head->next;
    int found = 0;
    printf("\n查询结果如下:\n");
    while (p != NULL) {
        if (strcmp(p->data.name, name) == 0) {
            printf("学号: %s, 姓名: %s, 性别: %s, 年龄: %d, 班级: %s\n",
                p->data.id, p->data.name, p->data.gender, p->data.age, p->data.className);
            found++;
        }
        p = p->next;
    }

    if (found == 0) {
        printf("未找到姓名为 %s 的学生。\n", name);
    }
    else {
        printf("共找到 %d 条记录。\n", found);
    }
}

void queryMenu(Node* head) {
    int choice;
    do {
        printf("\n--- 查询记录模块 ---\n");
        printf("  1. 按学号查询\n");
        printf("  2. 按姓名查询\n");
        printf("  0. 返回主菜单\n");
        printf("---------------------\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
        case 1: searchStudentById(head); break;
        case 2: searchStudentByName(head); break;
        case 0: break;
        default: printf("无效选择，请重新输入。\n");
        }
    } while (choice != 0);
}


// 3. 更新记录模块
void modifyStudent(Node* head) {
    if (head->next == NULL) {
        printf("当前无任何学生信息。\n");
        return;
    }
    char id[20];
    printf("请输入要修改的学生的学号: ");
    scanf("%s", id);
    clearInputBuffer();

    Node* p = head->next;
    int found = 0;
    while (p != NULL) {
        if (strcmp(p->data.id, id) == 0) {
            printf("已找到该学生，请输入新信息:\n");
            printf("请输入新姓名: ");
            scanf("%s", p->data.name);
            clearInputBuffer();
            printf("请输入新性别: ");
            scanf("%s", p->data.gender);
            clearInputBuffer();
            printf("请输入新年龄: ");
            scanf("%d", &p->data.age);
            clearInputBuffer();
            printf("请输入新班级: ");
            scanf("%s", p->data.className);
            clearInputBuffer();
            printf("\n学生信息修改成功！\n");
            found = 1;
            break;
        }
        p = p->next;
    }

    if (!found) {
        printf("未找到学号为 %s 的学生。\n", id);
    }
}

void deleteStudent(Node* head) {
    if (head->next == NULL) {
        printf("当前无任何学生信息。\n");
        return;
    }
    char id[20];
    printf("请输入要删除的学生的学号: ");
    scanf("%s", id);
    clearInputBuffer();

    Node* prev = head;
    Node* curr = head->next;
    int found = 0;

    while (curr != NULL) {
        if (strcmp(curr->data.id, id) == 0) {
            prev->next = curr->next;
            free(curr);
            printf("学号为 %s 的学生信息已删除。\n", id);
            found = 1;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    if (!found) {
        printf("未找到学号为 %s 的学生。\n", id);
    }
}

void updateMenu(Node* head) {
    int choice;
    do {
        printf("\n--- 更新记录模块 ---\n");
        printf("  1. 修改学生信息\n");
        printf("  2. 删除学生信息\n");
        printf("  0. 返回主菜单\n");
        printf("---------------------\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
        case 1: modifyStudent(head); break;
        case 2: deleteStudent(head); break;
        case 0: break;
        default: printf("无效选择，请重新输入。\n");
        }
    } while (choice != 0);
}

// 4. 统计记录模块
void statisticsByClass(Node* head) {
    if (head->next == NULL) {
        printf("当前无任何学生信息。\n");
        return;
    }
    char className[50];
    printf("请输入要统计的班级名称: ");
    scanf("%s", className);
    clearInputBuffer();

    Node* p = head->next;
    int count = 0;
    while (p != NULL) {
        if (strcmp(p->data.className, className) == 0) {
            count++;
        }
        p = p->next;
    }
    printf("班级 %s 共有 %d 名学生。\n", className, count);
}

void statisticsByGender(Node* head) {
    if (head->next == NULL) {
        printf("当前无任何学生信息。\n");
        return;
    }
    int male_count = 0;
    int female_count = 0;
    Node* p = head->next;
    while (p != NULL) {
        if (strcmp(p->data.gender, "男") == 0) {
            male_count++;
        }
        else if (strcmp(p->data.gender, "女") == 0) {
            female_count++;
        }
        p = p->next;
    }
    printf("学生总数中，男生有 %d 人，女生有 %d 人。\n", male_count, female_count);
}

void statisticsMenu(Node* head) {
    int choice;
    do {
        printf("\n--- 统计记录模块 ---\n");
        printf("  1. 按班级统计\n");
        printf("  2. 按性别统计\n");
        printf("  0. 返回主菜单\n");
        printf("---------------------\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
        case 1: statisticsByClass(head); break;
        case 2: statisticsByGender(head); break;
        case 0: break;
        default: printf("无效选择，请重新输入。\n");
        }
    } while (choice != 0);
}


// 5. 输出记录模块
void displayAllStudents(Node* head) {
    if (head->next == NULL) {
        printf("当前无任何学生信息。\n");
        return;
    }
    printf("\n======================= 所有学生信息 =======================\n");
    printf("%-15s %-15s %-10s %-10s %-15s\n", "学号", "姓名", "性别", "年龄", "班级");
    printf("------------------------------------------------------------\n");
    Node* p = head->next;
    while (p != NULL) {
        printf("%-15s %-15s %-10s %-10d %-15s\n",
            p->data.id, p->data.name, p->data.gender, p->data.age, p->data.className);
        p = p->next;
    }
    printf("============================================================\n");
}

// 6. 文件操作模块
void saveToFile(Node* head, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("打开文件 %s 失败！\n", filename);
        return;
    }

    Node* p = head->next;
    while (p != NULL) {
        fprintf(fp, "%s %s %s %d %s\n",
            p->data.id, p->data.name, p->data.gender, p->data.age, p->data.className);
        p = p->next;
    }

    fclose(fp);
    printf("数据已成功保存到 %s 文件中。\n", filename);
}

Node* loadFromFile(const char* filename) {
    // 创建一个带头节点的空链表
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    head->next = NULL;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("未找到数据文件 %s，将创建一个新系统。\n", filename);
        return head;
    }

    Student temp;
    while (fscanf(fp, "%s %s %s %d %s", temp.id, temp.name, temp.gender, &temp.age, temp.className) != EOF) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("内存分配失败！\n");
            continue;
        }
        newNode->data = temp;
        newNode->next = NULL;

        // 插入到链表尾部
        Node* p = head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newNode;
    }

    fclose(fp);
    printf("已从 %s 文件加载数据。\n", filename);
    return head;
}

// 辅助函数：释放链表
void freeList(Node* head) {
    Node* p = head;
    Node* temp;
    while (p != NULL) {
        temp = p;
        p = p->next;
        free(temp);
    }
}