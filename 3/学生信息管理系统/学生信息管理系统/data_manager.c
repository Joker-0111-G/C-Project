#define _CRT_SECURE_NO_WARNINGS
#include "data_manager.h"

// 内部辅助函数：清空标准输入
static void clean_input_stream() {
    while (getchar() != '\n');
}

// 增
void insert_new_entry(ListNode* list_head) {
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    if (!new_node) {
        puts("Error: Memory allocation failed.");
        return;
    }

    printf("Enter ID: ");
    scanf("%s", new_node->content.entry_id);
    clean_input_stream();

    // 唯一性检查
    for (ListNode* p = list_head->next_node; p; p = p->next_node) {
        if (strcmp(p->content.entry_id, new_node->content.entry_id) == 0) {
            puts("Error: This ID already exists.");
            free(new_node);
            return;
        }
    }

    printf("Enter Name: "); scanf("%s", new_node->content.entry_name); clean_input_stream();
    printf("Enter Gender: "); scanf("%s", new_node->content.entry_gender); clean_input_stream();
    printf("Enter Age: "); scanf("%d", &new_node->content.entry_age); clean_input_stream();
    printf("Enter Class: "); scanf("%s", new_node->content.entry_class); clean_input_stream();
    new_node->next_node = NULL;

    ListNode* walker = list_head;
    while (walker->next_node) {
        walker = walker->next_node;
    }
    walker->next_node = new_node;
    puts("\nNew entry added successfully.");
}

// 查
static void search_by_entry_id(ListNode* list_head) {
    char id[20];
    printf("Enter ID to search for: ");
    scanf("%s", id);
    clean_input_stream();
    for (ListNode* p = list_head->next_node; p; p = p->next_node) {
        if (strcmp(p->content.entry_id, id) == 0) {
            printf("\nEntry found:\nID: %s, Name: %s, Gender: %s, Age: %d, Class: %s\n",
                p->content.entry_id, p->content.entry_name, p->content.entry_gender, p->content.entry_age, p->content.entry_class);
            return;
        }
    }
    printf("No entry found with ID %s.\n", id);
}

static void search_by_entry_name(ListNode* list_head) {
    char name[50];
    int results = 0;
    printf("Enter Name to search for: ");
    scanf("%s", name);
    clean_input_stream();
    puts("\nSearch Results:");
    for (ListNode* p = list_head->next_node; p; p = p->next_node) {
        if (strcmp(p->content.entry_name, name) == 0) {
            printf("ID: %s, Name: %s, Gender: %s, Age: %d, Class: %s\n",
                p->content.entry_id, p->content.entry_name, p->content.entry_gender, p->content.entry_age, p->content.entry_class);
            results++;
        }
    }
    printf("Found %d record(s).\n", results);
}

void access_entry_submenu(ListNode* list_head) {
    int sel;
    do {
        puts("\n--- Access Menu ---\n  1. By ID\n  2. By Name\n  0. Back");
        printf("Selection: ");
        scanf("%d", &sel);
        clean_input_stream();
        if (sel == 1) search_by_entry_id(list_head);
        else if (sel == 2) search_by_entry_name(list_head);
    } while (sel != 0);
}

// 改
static void edit_entry(ListNode* list_head) {
    char id[20];
    printf("Enter ID of entry to edit: ");
    scanf("%s", id);
    clean_input_stream();
    for (ListNode* p = list_head->next_node; p; p = p->next_node) {
        if (strcmp(p->content.entry_id, id) == 0) {
            puts("Entry found. Enter new data:");
            printf("New Name: "); scanf("%s", p->content.entry_name); clean_input_stream();
            printf("New Gender: "); scanf("%s", p->content.entry_gender); clean_input_stream();
            printf("New Age: "); scanf("%d", &p->content.entry_age); clean_input_stream();
            printf("New Class: "); scanf("%s", p->content.entry_class); clean_input_stream();
            puts("\nEntry updated successfully.");
            return;
        }
    }
    printf("No entry found with ID %s.\n", id);
}

// 删
static void delete_entry(ListNode* list_head) {
    char id[20];
    printf("Enter ID of entry to delete: ");
    scanf("%s", id);
    clean_input_stream();

    ListNode* prev = list_head;
    ListNode* curr = list_head->next_node;
    while (curr) {
        if (strcmp(curr->content.entry_id, id) == 0) {
            prev->next_node = curr->next_node;
            free(curr);
            printf("Entry with ID %s has been deleted.\n", id);
            return;
        }
        prev = curr;
        curr = curr->next_node;
    }
    printf("No entry found with ID %s.\n", id);
}


void modify_entry_submenu(ListNode* list_head) {
    int sel;
    do {
        puts("\n--- Modify Menu ---\n  1. Edit Entry\n  2. Delete Entry\n  0. Back");
        printf("Selection: ");
        scanf("%d", &sel);
        clean_input_stream();
        if (sel == 1) edit_entry(list_head);
        else if (sel == 2) delete_entry(list_head);
    } while (sel != 0);
}

// 统计
static void analyze_by_class(ListNode* list_head) {
    char class_id[50];
    int num = 0;
    printf("Enter class name to analyze: ");
    scanf("%s", class_id);
    clean_input_stream();
    for (ListNode* p = list_head->next_node; p; p = p->next_node) {
        if (strcmp(p->content.entry_class, class_id) == 0) num++;
    }
    printf("There are %d students in class %s.\n", num, class_id);
}

static void analyze_by_gender(ListNode* list_head) {
    int males = 0, females = 0;
    for (ListNode* p = list_head->next_node; p; p = p->next_node) {
        if (strcmp(p->content.entry_gender, "男") == 0) males++;
        else if (strcmp(p->content.entry_gender, "女") == 0) females++;
    }
    printf("Gender distribution: %d male(s), %d female(s).\n", males, females);
}

void analyze_data_submenu(ListNode* list_head) {
    int sel;
    do {
        puts("\n--- Analyze Menu ---\n  1. By Class\n  2. By Gender\n  0. Back");
        printf("Selection: ");
        scanf("%d", &sel);
        clean_input_stream();
        if (sel == 1) analyze_by_class(list_head);
        else if (sel == 2) analyze_by_gender(list_head);
    } while (sel != 0);
}


// 显示全部
void list_all_entries(ListNode* list_head) {
    if (!list_head->next_node) {
        puts("No entries to display.");
        return;
    }
    puts("\n---------- All Student Entries ----------");
    printf("%-15s%-15s%-10s%-10s%-15s\n", "ID", "Name", "Gender", "Age", "Class");
    puts("-------------------------------------------");
    for (ListNode* p = list_head->next_node; p; p = p->next_node) {
        printf("%-15s%-15s%-10s%-10d%-15s\n", p->content.entry_id, p->content.entry_name, p->content.entry_gender, p->content.entry_age, p->content.entry_class);
    }
    puts("-------------------------------------------");
}

// 文件IO
void save_entries_to_file(ListNode* list_head, const char* file_path) {
    FILE* f_out = fopen(file_path, "w");
    if (!f_out) {
        printf("Critical Error: Cannot open %s for writing.\n", file_path);
        return;
    }
    for (ListNode* p = list_head->next_node; p; p = p->next_node) {
        fprintf(f_out, "%s %s %s %d %s\n", p->content.entry_id, p->content.entry_name, p->content.entry_gender, p->content.entry_age, p->content.entry_class);
    }
    fclose(f_out);
}

ListNode* load_entries_from_file(const char* file_path) {
    ListNode* head = (ListNode*)malloc(sizeof(ListNode));
    if (!head) exit(1);
    head->next_node = NULL;

    FILE* f_in = fopen(file_path, "r");
    if (!f_in) {
        printf("Data file '%s' not found. Starting with an empty database.\n", file_path);
        return head;
    }

    StudentEntry temp;
    while (fscanf(f_in, "%s %s %s %d %s", temp.entry_id, temp.entry_name, temp.entry_gender, &temp.entry_age, temp.entry_class) != EOF) {
        ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
        if (!new_node) continue;
        new_node->content = temp;
        new_node->next_node = NULL;

        ListNode* tail = head;
        while (tail->next_node) {
            tail = tail->next_node;
        }
        tail->next_node = new_node;
    }
    fclose(f_in);
    printf("Data loaded from '%s'.\n", file_path);
    return head;
}


void deallocate_list(ListNode* list_head) {
    ListNode* current = list_head;
    while (current) {
        ListNode* next = current->next_node;
        free(current);
        current = next;
    }
}