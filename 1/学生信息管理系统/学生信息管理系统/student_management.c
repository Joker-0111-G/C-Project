#define _CRT_SECURE_NO_WARNINGS
#include "student_management.h"

// 清理输入缓冲区
static void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 检查学号唯一性
static int is_id_unique(Node* head, const char* id) {
    Node* current = head->next;
    while (current != NULL) {
        if (strcmp(current->data.id, id) == 0) {
            return 0; // 不唯一
        }
        current = current->next;
    }
    return 1; // 唯一
}

// 1. 录入学生
void add_student(Node* head) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("内存分配失败！\n");
        return;
    }

    printf("请输入学号: ");
    scanf("%s", new_node->data.id);
    clear_buffer();

    if (!is_id_unique(head, new_node->data.id)) {
        printf("错误: 该学号已经存在！\n");
        free(new_node);
        return;
    }

    printf("请输入姓名: ");
    scanf("%s", new_node->data.name);
    clear_buffer();
    printf("请输入性别: ");
    scanf("%s", new_node->data.gender);
    clear_buffer();
    printf("请输入年龄: ");
    scanf("%d", &new_node->data.age);
    clear_buffer();
    printf("请输入班级: ");
    scanf("%s", new_node->data.className);
    clear_buffer();
    new_node->next = NULL;

    Node* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = new_node;
    printf("\n学生信息添加成功！\n");
}

// 2. 查询 (按ID)
static void search_by_id(Node* head) {
    char id[20];
    printf("请输入要查询的学号: ");
    scanf("%s", id);
    clear_buffer();

    Node* current = head->next;
    while (current != NULL) {
        if (strcmp(current->data.id, id) == 0) {
            printf("\n查询成功，信息如下:\n");
            printf("学号: %s, 姓名: %s, 性别: %s, 年龄: %d, 班级: %s\n",
                current->data.id, current->data.name, current->data.gender, current->data.age, current->data.className);
            return;
        }
        current = current->next;
    }
    printf("未找到学号为 %s 的学生。\n", id);
}

// 2. 查询 (按姓名)
static void search_by_name(Node* head) {
    char name[50];
    int count = 0;
    printf("请输入要查询的姓名: ");
    scanf("%s", name);
    clear_buffer();

    Node* current = head->next;
    printf("\n查询结果:\n");
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            printf("学号: %s, 姓名: %s, 性别: %s, 年龄: %d, 班级: %s\n",
                current->data.id, current->data.name, current->data.gender, current->data.age, current->data.className);
            count++;
        }
        current = current->next;
    }

    if (count == 0) {
        printf("未找到姓名为 %s 的学生。\n", name);
    }
    else {
        printf("共找到 %d 条记录。\n", count);
    }
}

void query_student_menu(Node* head) {
    int option;
    do {
        printf("\n--- 查询菜单 ---\n");
        printf("  1. 按学号查询\n");
        printf("  2. 按姓名查询\n");
        printf("  0. 返回上级\n");
        printf("------------------\n");
        printf("请输入选项: ");
        scanf("%d", &option);
        clear_buffer();
        switch (option) {
        case 1: search_by_id(head); break;
        case 2: search_by_name(head); break;
        case 0: break;
        default: printf("无效选项!\n"); break;
        }
    } while (option != 0);
}

// 3. 修改
static void modify_student(Node* head) {
    char id[20];
    printf("请输入要修改的学生的学号: ");
    scanf("%s", id);
    clear_buffer();

    Node* current = head->next;
    while (current) {
        if (strcmp(current->data.id, id) == 0) {
            printf("找到学生，请输入新信息:\n");
            printf("请输入新姓名: ");
            scanf("%s", current->data.name);
            clear_buffer();
            printf("请输入新性别: ");
            scanf("%s", current->data.gender);
            clear_buffer();
            printf("请输入新年龄: ");
            scanf("%d", &current->data.age);
            clear_buffer();
            printf("请输入新班级: ");
            scanf("%s", current->data.className);
            clear_buffer();
            printf("\n信息修改成功！\n");
            return;
        }
        current = current->next;
    }
    printf("未找到该学号的学生。\n");
}

// 3. 删除
static void delete_student(Node* head) {
    char id[20];
    printf("请输入要删除的学生的学号: ");
    scanf("%s", id);
    clear_buffer();

    Node* prev = head;
    Node* curr = head->next;
    while (curr) {
        if (strcmp(curr->data.id, id) == 0) {
            prev->next = curr->next;
            free(curr);
            printf("学号为 %s 的学生已删除。\n", id);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("未找到该学号的学生。\n");
}

void update_student_menu(Node* head) {
    int option;
    do {
        printf("\n--- 更新菜单 ---\n");
        printf("  1. 修改学生信息\n");
        printf("  2. 删除学生信息\n");
        printf("  0. 返回上级\n");
        printf("------------------\n");
        printf("请输入选项: ");
        scanf("%d", &option);
        clear_buffer();
        switch (option) {
        case 1: modify_student(head); break;
        case 2: delete_student(head); break;
        case 0: break;
        default: printf("无效选项!\n"); break;
        }
    } while (option != 0);
}

// 4. 统计 (按班级)
static void stats_by_class(Node* head) {
    char class_name[50];
    int count = 0;
    printf("请输入要统计的班级: ");
    scanf("%s", class_name);
    clear_buffer();

    Node* current = head->next;
    while (current) {
        if (strcmp(current->data.className, class_name) == 0) {
            count++;
        }
        current = current->next;
    }
    printf("班级 %s 共有 %d 名学生。\n", class_name, count);
}

// 4. 统计 (按性别)
static void stats_by_gender(Node* head) {
    int male = 0, female = 0;
    Node* current = head->next;
    while (current) {
        if (strcmp(current->data.gender, "男") == 0) {
            male++;
        }
        else if (strcmp(current->data.gender, "女") == 0) {
            female++;
        }
        current = current->next;
    }
    printf("学生总数中，男生 %d 人，女生 %d 人。\n", male, female);
}


void statistics_menu(Node* head) {
    int option;
    do {
        printf("\n--- 统计菜单 ---\n");
        printf("  1. 按班级统计\n");
        printf("  2. 按性别统计\n");
        printf("  0. 返回上级\n");
        printf("------------------\n");
        printf("请输入选项: ");
        scanf("%d", &option);
        clear_buffer();
        switch (option) {
        case 1: stats_by_class(head); break;
        case 2: stats_by_gender(head); break;
        case 0: break;
        default: printf("无效选项!\n"); break;
        }
    } while (option != 0);
}


// 5. 显示所有
void display_all_students(Node* head) {
    if (head->next == NULL) {
        printf("系统中没有学生信息。\n");
        return;
    }
    printf("\n======================= 所有学生信息 =======================\n");
    printf("%-15s %-15s %-10s %-10s %-15s\n", "学号", "姓名", "性别", "年龄", "班级");
    printf("------------------------------------------------------------\n");

    Node* current = head->next;
    while (current != NULL) {
        printf("%-15s %-15s %-10s %-10d %-15s\n",
            current->data.id, current->data.name, current->data.gender, current->data.age, current->data.className);
        current = current->next;
    }
    printf("============================================================\n");
}


// 6. 文件操作
void save_to_file(Node* head, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("错误: 无法打开文件 %s 进行写入。\n", filename);
        return;
    }
    Node* current = head->next;
    while (current) {
        fprintf(fp, "%s %s %s %d %s\n",
            current->data.id, current->data.name, current->data.gender, current->data.age, current->data.className);
        current = current->next;
    }
    fclose(fp);
    printf("数据已保存到 %s\n", filename);
}

Node* load_from_file(const char* filename) {
    Node* head = (Node*)malloc(sizeof(Node));
    if (!head) {
        printf("关键内存分配失败！\n");
        exit(1);
    }
    head->next = NULL;

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("未找到数据文件 %s, 将创建新系统。\n", filename);
        return head;
    }

    Student temp_stu;
    while (fscanf(fp, "%s %s %s %d %s", temp_stu.id, temp_stu.name, temp_stu.gender, &temp_stu.age, temp_stu.className) != EOF) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (!new_node) {
            printf("加载数据时内存分配失败！\n");
            break;
        }
        new_node->data = temp_stu;
        new_node->next = NULL;

        Node* tail = head;
        while (tail->next) {
            tail = tail->next;
        }
        tail->next = new_node;
    }
    fclose(fp);
    printf("已从 %s 文件加载数据。\n", filename);
    return head;
}

// 释放链表
void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}