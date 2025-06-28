#define _CRT_SECURE_NO_WARNINGS
#include "record_manager.h"

static void flush_stdin() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// 增
void create_new_record(Link_Node* list_head) {
    Link_Node* new_node = (Link_Node*)malloc(sizeof(Link_Node));
    if (new_node == NULL) {
        puts("内存不足！");
        return;
    }

    printf("输入学号: ");
    scanf("%s", new_node->record.stu_id);
    flush_stdin();

    // 检查学号是否存在
    Link_Node* checker = list_head->p_next;
    while (checker) {
        if (strcmp(checker->record.stu_id, new_node->record.stu_id) == 0) {
            puts("错误：此学号已存在！");
            free(new_node);
            return;
        }
        checker = checker->p_next;
    }

    printf("输入姓名: ");
    scanf("%s", new_node->record.stu_name);
    flush_stdin();
    printf("输入性别: ");
    scanf("%s", new_node->record.stu_gender);
    flush_stdin();
    printf("输入年龄: ");
    scanf("%d", &new_node->record.stu_age);
    flush_stdin();
    printf("输入班级: ");
    scanf("%s", new_node->record.stu_class);
    flush_stdin();
    new_node->p_next = NULL;

    Link_Node* current = list_head;
    while (current->p_next != NULL) {
        current = current->p_next;
    }
    current->p_next = new_node;
    puts("\n新记录已添加。");
}

// 查（子菜单）
static void find_by_student_id(Link_Node* list_head) {
    char id[20];
    printf("输入要查找的学号: ");
    scanf("%s", id);
    flush_stdin();

    Link_Node* ptr = list_head->p_next;
    while (ptr) {
        if (strcmp(ptr->record.stu_id, id) == 0) {
            printf("\n找到记录:\n");
            printf("学号:%s, 姓名:%s, 性别:%s, 年龄:%d, 班级:%s\n",
                ptr->record.stu_id, ptr->record.stu_name, ptr->record.stu_gender, ptr->record.stu_age, ptr->record.stu_class);
            return;
        }
        ptr = ptr->p_next;
    }
    printf("数据库中无此学号 %s 的记录。\n", id);
}

static void find_by_student_name(Link_Node* list_head) {
    char name[50];
    int found_count = 0;
    printf("输入要查找的姓名: ");
    scanf("%s", name);
    flush_stdin();

    Link_Node* ptr = list_head->p_next;
    puts("\n查找结果:");
    while (ptr) {
        if (strcmp(ptr->record.stu_name, name) == 0) {
            printf("学号:%s, 姓名:%s, 性别:%s, 年龄:%d, 班级:%s\n",
                ptr->record.stu_id, ptr->record.stu_name, ptr->record.stu_gender, ptr->record.stu_age, ptr->record.stu_class);
            found_count++;
        }
        ptr = ptr->p_next;
    }
    printf("共找到 %d 个名为 %s 的学生。\n", found_count, name);
}

void find_record_menu(Link_Node* list_head) {
    int choice;
    do {
        puts("\n--- 查找记录 ---");
        puts("  1. 按学号查找");
        puts("  2. 按姓名查找");
        puts("  0. 返回");
        printf("你的选择: ");
        scanf("%d", &choice);
        flush_stdin();

        if (choice == 1) find_by_student_id(list_head);
        else if (choice == 2) find_by_student_name(list_head);
        else if (choice != 0) puts("输入错误。");
    } while (choice != 0);
}

// 改（子菜单）
static void update_record(Link_Node* list_head) {
    char id[20];
    printf("输入待修改记录的学号: ");
    scanf("%s", id);
    flush_stdin();

    Link_Node* target = list_head->p_next;
    while (target) {
        if (strcmp(target->record.stu_id, id) == 0) {
            puts("找到记录，请输入新数据。");
            printf("输入新姓名: "); scanf("%s", target->record.stu_name); flush_stdin();
            printf("输入新性别: "); scanf("%s", target->record.stu_gender); flush_stdin();
            printf("输入新年龄: "); scanf("%d", &target->record.stu_age); flush_stdin();
            printf("输入新班级: "); scanf("%s", target->record.stu_class); flush_stdin();
            puts("\n记录更新完毕。");
            return;
        }
        target = target->p_next;
    }
    printf("数据库中无此学号 %s 的记录。\n", id);
}

// 删
static void remove_record(Link_Node* list_head) {
    char id[20];
    printf("输入待删除记录的学号: ");
    scanf("%s", id);
    flush_stdin();

    Link_Node* prev = list_head;
    Link_Node* curr = list_head->p_next;
    while (curr) {
        if (strcmp(curr->record.stu_id, id) == 0) {
            prev->p_next = curr->p_next;
            free(curr);
            printf("学号为 %s 的记录已被移除。\n", id);
            return;
        }
        prev = curr;
        curr = curr->p_next;
    }
    printf("数据库中无此学号 %s 的记录。\n", id);
}


void alter_record_menu(Link_Node* list_head) {
    int choice;
    do {
        puts("\n--- 更改记录 ---");
        puts("  1. 修改记录");
        puts("  2. 移除记录");
        puts("  0. 返回");
        printf("你的选择: ");
        scanf("%d", &choice);
        flush_stdin();

        if (choice == 1) { update_record(list_head); persist_records_to_disk(list_head, "student_data.db"); }
        else if (choice == 2) { remove_record(list_head); persist_records_to_disk(list_head, "student_data.db"); }
        else if (choice != 0) puts("输入错误。");
    } while (choice != 0);
}


// 统计
static void summarize_by_class(Link_Node* list_head) {
    char class_name[50];
    int total = 0;
    printf("输入要统计的班级名: ");
    scanf("%s", class_name);
    flush_stdin();

    for (Link_Node* p = list_head->p_next; p != NULL; p = p->p_next) {
        if (strcmp(p->record.stu_class, class_name) == 0) {
            total++;
        }
    }
    printf("班级 [%s] 的学生人数为: %d\n", class_name, total);
}

static void summarize_by_gender(Link_Node* list_head) {
    int males = 0, females = 0;
    for (Link_Node* p = list_head->p_next; p != NULL; p = p->p_next) {
        if (strcmp(p->record.stu_gender, "男") == 0) males++;
        else if (strcmp(p->record.stu_gender, "女") == 0) females++;
    }
    printf("当前记录中，男生: %d 人, 女生: %d 人。\n", males, females);
}

void summarize_data_menu(Link_Node* list_head) {
    int choice;
    do {
        puts("\n--- 数据汇总 ---");
        puts("  1. 按班级汇总");
        puts("  2. 按性别汇总");
        puts("  0. 返回");
        printf("你的选择: ");
        scanf("%d", &choice);
        flush_stdin();

        if (choice == 1) summarize_by_class(list_head);
        else if (choice == 2) summarize_by_gender(list_head);
        else if (choice != 0) puts("输入错误。");
    } while (choice != 0);
}


// 显示全部
void print_all_records(Link_Node* list_head) {
    if (!list_head->p_next) {
        puts("当前没有任何记录。");
        return;
    }
    puts("\n=============== 全部学生记录 ================");
    printf("%-12s | %-12s | %-8s | %-8s | %-12s\n", "学号", "姓名", "性别", "年龄", "班级");
    puts("-------------------------------------------------");

    for (Link_Node* p = list_head->p_next; p != NULL; p = p->p_next) {
        printf("%-12s | %-12s | %-8s | %-8d | %-12s\n",
            p->record.stu_id, p->record.stu_name, p->record.stu_gender, p->record.stu_age, p->record.stu_class);
    }
    puts("=================================================");
}

// 文件IO
void persist_records_to_disk(Link_Node* list_head, const char* filepath) {
    FILE* file_ptr = fopen(filepath, "w");
    if (!file_ptr) {
        printf("致命错误: 无法写入到文件 %s\n", filepath);
        return;
    }
    for (Link_Node* p = list_head->p_next; p; p = p->p_next) {
        fprintf(file_ptr, "%s %s %s %d %s\n",
            p->record.stu_id, p->record.stu_name, p->record.stu_gender, p->record.stu_age, p->record.stu_class);
    }
    fclose(file_ptr);
}

Link_Node* load_records_from_disk(const char* filepath) {
    Link_Node* head = (Link_Node*)malloc(sizeof(Link_Node));
    if (!head) exit(1);
    head->p_next = NULL;

    FILE* file_ptr = fopen(filepath, "r");
    if (!file_ptr) {
        printf("数据文件 %s 未找到, 系统将以空记录启动。\n", filepath);
        return head;
    }

    Info_Student buffer;
    Link_Node* tail = head;
    while (fscanf(file_ptr, "%s %s %s %d %s", buffer.stu_id, buffer.stu_name, buffer.stu_gender, &buffer.stu_age, buffer.stu_class) == 5) {
        Link_Node* new_node = (Link_Node*)malloc(sizeof(Link_Node));
        if (!new_node) {
            puts("加载时内存分配失败!");
            break;
        }
        new_node->record = buffer;
        new_node->p_next = NULL;
        tail->p_next = new_node;
        tail = new_node;
    }
    fclose(file_ptr);
    printf("已从 %s 成功加载记录。\n", filepath);
    return head;
}

// 释放内存
void release_all_nodes(Link_Node* list_head) {
    Link_Node* p = list_head;
    while (p) {
        Link_Node* to_delete = p;
        p = p->p_next;
        free(to_delete);
    }
}