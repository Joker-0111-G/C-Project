#ifndef STUDENT_H
#define STUDENT_H

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

// 链表节点结构体
typedef struct Node {
    Student data;
    struct Node* next;
} Node;


// 1. 输入模块
void addStudent(Node* head);

// 2. 查询模块
void queryMenu(Node* head);

// 3. 更新模块
void updateMenu(Node* head);

// 4. 统计模块
void statisticsMenu(Node* head);

// 5. 输出模块
void displayAllStudents(Node* head);

// 6. 文件操作模块 (数据持久化)
void saveToFile(Node* head, const char* filename); // 保存数据到文件
Node* loadFromFile(const char* filename);         // 从文件加载数据

// 辅助函数
void clearInputBuffer();
void freeList(Node* head);

#endif // STUDENT_H