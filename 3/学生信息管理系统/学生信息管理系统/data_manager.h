#pragma once
#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 学生条目
typedef struct {
    char entry_id[20];
    char entry_name[50];
    char entry_gender[10];
    int entry_age;
    char entry_class[50];
} StudentEntry;

// 链表节点
typedef struct ListNode {
    StudentEntry content;
    struct ListNode* next_node;
} ListNode;

// --- 接口函数声明 ---

// 数据持久化
ListNode* load_entries_from_file(const char* file_path);
void save_entries_to_file(ListNode* list_head, const char* file_path);

// 功能接口
void insert_new_entry(ListNode* list_head);
void access_entry_submenu(ListNode* list_head);
void modify_entry_submenu(ListNode* list_head);
void analyze_data_submenu(ListNode* list_head);
void list_all_entries(ListNode* list_head);

// 内存管理
void deallocate_list(ListNode* list_head);

#endif // DATA_MANAGER_H