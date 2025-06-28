#pragma once
#ifndef STUDENT_MANAGEMENT_H
#define STUDENT_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ѧ����Ϣ�ṹ��
typedef struct Student {
    char id[20];
    char name[50];
    char gender[10];
    int age;
    char className[50];
} Student;

// ����ڵ�
typedef struct Node {
    Student data;
    struct Node* next;
} Node;

// --- ����ԭ�� ---
// ��������
Node* load_from_file(const char* filename);
// ��������
void save_to_file(Node* head, const char* filename);
// �ͷ�����
void free_list(Node* head);

// ����ģ��
void add_student(Node* head);
void query_student_menu(Node* head);
void update_student_menu(Node* head);
void statistics_menu(Node* head);
void display_all_students(Node* head);

#endif // STUDENT_MANAGEMENT_H