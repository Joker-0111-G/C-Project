#pragma once
#ifndef RECORD_MANAGER_H
#define RECORD_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ѧ����Ϣ
typedef struct Info_Student {
    char stu_id[20];
    char stu_name[50];
    char stu_gender[10];
    int stu_age;
    char stu_class[50];
} Info_Student;

// ����ڵ�
typedef struct Link_Node {
    Info_Student record;
    struct Link_Node* p_next;
} Link_Node;

// --- �ӿ����� ---

// �ļ�����
Link_Node* load_records_from_disk(const char* filepath);
void persist_records_to_disk(Link_Node* list_head, const char* filepath);

// ���Ĺ���
void create_new_record(Link_Node* list_head);
void find_record_menu(Link_Node* list_head);
void alter_record_menu(Link_Node* list_head);
void summarize_data_menu(Link_Node* list_head);
void print_all_records(Link_Node* list_head);

// ��Դ����
void release_all_nodes(Link_Node* list_head);

#endif // RECORD_MANAGER_H