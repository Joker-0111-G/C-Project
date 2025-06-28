#pragma once
#ifndef STUDENT_DB_H
#define STUDENT_DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// API-style header

// Data structure for a student
typedef struct {
    char id[20];
    char name[50];
    char gender[10];
    int age;
    char class_id[50];
} StudentInfo;

// Node for the linked list
typedef struct StudentNode {
    StudentInfo info;
    struct StudentNode* next;
} StudentNode;

// --- Database API ---

// Initialize the database from a file, returns the list head
StudentNode* StudentDB_Init(const char* db_path);

// Commit all in-memory changes to the database file
void StudentDB_Commit(StudentNode* head, const char* db_path);

// Free all resources used by the database
void StudentDB_Destroy(StudentNode* head);

// --- Record Operations API ---

// Add a new record to the database
void StudentDB_AddRecord(StudentNode* head);

// Display functions
void StudentDB_ShowAll(StudentNode* head);

// Sub-menu controllers
void StudentDB_QueryMenu(StudentNode* head);
void StudentDB_UpdateMenu(StudentNode* head);
void StudentDB_StatsMenu(StudentNode* head);

#endif // STUDENT_DB_H