#pragma once
#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ѧ����Ŀ
typedef struct {
    char entry_id[20];
    char entry_name[50];
    char entry_gender[10];
    int entry_age;
    char entry_class[50];
} StudentEntry;

// ����ڵ�
typedef struct ListNode {
    StudentEntry content;
    struct ListNode* next_node;
} ListNode;

// --- �ӿں������� ---

// ���ݳ־û�
ListNode* load_entries_from_file(const char* file_path);
void save_entries_to_file(ListNode* list_head, const char* file_path);

// ���ܽӿ�
void insert_new_entry(ListNode* list_head);
void access_entry_submenu(ListNode* list_head);
void modify_entry_submenu(ListNode* list_head);
void analyze_data_submenu(ListNode* list_head);
void list_all_entries(ListNode* list_head);

// �ڴ����
void deallocate_list(ListNode* list_head);

#endif // DATA_MANAGER_H