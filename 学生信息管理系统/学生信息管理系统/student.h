#ifndef STUDENT_H
#define STUDENT_H

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

// ����ڵ�ṹ��
typedef struct Node {
    Student data;
    struct Node* next;
} Node;


// 1. ����ģ��
void addStudent(Node* head);

// 2. ��ѯģ��
void queryMenu(Node* head);

// 3. ����ģ��
void updateMenu(Node* head);

// 4. ͳ��ģ��
void statisticsMenu(Node* head);

// 5. ���ģ��
void displayAllStudents(Node* head);

// 6. �ļ�����ģ�� (���ݳ־û�)
void saveToFile(Node* head, const char* filename); // �������ݵ��ļ�
Node* loadFromFile(const char* filename);         // ���ļ���������

// ��������
void clearInputBuffer();
void freeList(Node* head);

#endif // STUDENT_H