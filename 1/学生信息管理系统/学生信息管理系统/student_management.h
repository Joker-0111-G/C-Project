#pragma once
#ifndef STUDENT_MANAGEMENT_H
#define STUDENT_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 学生信息结构体
typedef struct Student {
    char id[20];
    char name[50];
    char gender[10];
    int age;
    char className[50];
} Student;

// 链表节点
typedef struct Node {
    Student data;
    struct Node* next;
} Node;

// --- 函数原型 ---
// 加载数据
Node* load_from_file(const char* filename);
// 保存数据
void save_to_file(Node* head, const char* filename);
// 释放链表
void free_list(Node* head);

// 功能模块
void add_student(Node* head);
void query_student_menu(Node* head);
void update_student_menu(Node* head);
void statistics_menu(Node* head);
void display_all_students(Node* head);

#endif // STUDENT_MANAGEMENT_H