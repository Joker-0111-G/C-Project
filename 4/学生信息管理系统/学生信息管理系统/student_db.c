#define _CRT_SECURE_NO_WARNINGS
#include "student_db.h"

static void consume_newline() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Record Operations Implementation ---
void StudentDB_AddRecord(StudentNode* head) {
    StudentNode* new_node = (StudentNode*)malloc(sizeof(StudentNode));
    if (!new_node) {
        perror("Failed to allocate memory for new record");
        return;
    }

    printf("Enter student ID: ");
    scanf("%19s", new_node->info.id);
    consume_newline();

    StudentNode* current = head->next;
    while (current) {
        if (strcmp(current->info.id, new_node->info.id) == 0) {
            printf("Error: A record with this ID already exists.\n");
            free(new_node);
            return;
        }
        current = current->next;
    }

    printf("Enter name: "); scanf("%49s", new_node->info.name); consume_newline();
    printf("Enter gender: "); scanf("%9s", new_node->info.gender); consume_newline();
    printf("Enter age: "); scanf("%d", &new_node->info.age); consume_newline();
    printf("Enter class ID: "); scanf("%49s", new_node->info.class_id); consume_newline();
    new_node->next = NULL;

    StudentNode* tail = head;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = new_node;
    printf("\nRecord added to memory.\n");
}

static void find_by_id(StudentNode* head) {
    char search_id[20];
    printf("Enter ID to find: ");
    scanf("%19s", search_id);
    consume_newline();
    for (StudentNode* p = head->next; p; p = p->next) {
        if (strcmp(p->info.id, search_id) == 0) {
            printf("\nFound: ID=%s, Name=%s, Gender=%s, Age=%d, Class=%s\n", p->info.id, p->info.name, p->info.gender, p->info.age, p->info.class_id);
            return;
        }
    }
    printf("Record with ID %s not found.\n", search_id);
}

static void find_by_name(StudentNode* head) {
    char search_name[50];
    int count = 0;
    printf("Enter name to find: ");
    scanf("%49s", search_name);
    consume_newline();
    printf("\nSearch results for '%s':\n", search_name);
    for (StudentNode* p = head->next; p; p = p->next) {
        if (strcmp(p->info.name, search_name) == 0) {
            printf("  ID=%s, Name=%s, Gender=%s, Age=%d, Class=%s\n", p->info.id, p->info.name, p->info.gender, p->info.age, p->info.class_id);
            count++;
        }
    }
    printf("%d record(s) found.\n", count);
}

void StudentDB_QueryMenu(StudentNode* head) {
    int opt;
    do {
        printf("\n[Query Menu]\n 1-By ID, 2-By Name, 0-Back\nChoice: ");
        scanf("%d", &opt);
        consume_newline();
        switch (opt) {
        case 1: find_by_id(head); break;
        case 2: find_by_name(head); break;
        }
    } while (opt != 0);
}


static void edit_record(StudentNode* head) {
    char id[20];
    printf("Enter ID of record to edit: ");
    scanf("%19s", id);
    consume_newline();
    for (StudentNode* p = head->next; p; p = p->next) {
        if (strcmp(p->info.id, id) == 0) {
            printf("Record found. Enter new information.\n");
            printf("New Name: "); scanf("%49s", p->info.name); consume_newline();
            printf("New Gender: "); scanf("%9s", p->info.gender); consume_newline();
            printf("New Age: "); scanf("%d", &p->info.age); consume_newline();
            printf("New Class ID: "); scanf("%49s", p->info.class_id); consume_newline();
            printf("\nRecord updated in memory.\n");
            return;
        }
    }
    printf("Record with ID %s not found.\n", id);
}

static void delete_record(StudentNode* head) {
    char id[20];
    printf("Enter ID of record to delete: ");
    scanf("%19s", id);
    consume_newline();
    StudentNode* prev = head;
    for (StudentNode* curr = head->next; curr; prev = curr, curr = curr->next) {
        if (strcmp(curr->info.id, id) == 0) {
            prev->next = curr->next;
            free(curr);
            printf("Record %s deleted from memory.\n", id);
            return;
        }
    }
    printf("Record with ID %s not found.\n", id);
}


void StudentDB_UpdateMenu(StudentNode* head) {
    int opt;
    do {
        printf("\n[Update Menu]\n 1-Edit Record, 2-Delete Record, 0-Back\nChoice: ");
        scanf("%d", &opt);
        consume_newline();
        if (opt == 1) edit_record(head);
        else if (opt == 2) delete_record(head);
    } while (opt != 0);
}

static void stats_class(StudentNode* head) {
    char class_id[50];
    int count = 0;
    printf("Enter class ID for statistics: ");
    scanf("%49s", class_id);
    consume_newline();
    for (StudentNode* p = head->next; p; p = p->next) {
        if (strcmp(p->info.class_id, class_id) == 0) count++;
    }
    printf("There are %d students in class '%s'.\n", count, class_id);
}

static void stats_gender(StudentNode* head) {
    int m = 0, f = 0;
    for (StudentNode* p = head->next; p; p = p->next) {
        if (strcmp(p->info.gender, "ÄÐ") == 0) m++;
        else if (strcmp(p->info.gender, "Å®") == 0) f++;
    }
    printf("Gender statistics: Male=%d, Female=%d.\n", m, f);
}

void StudentDB_StatsMenu(StudentNode* head) {
    int opt;
    do {
        printf("\n[Statistics Menu]\n 1-By Class, 2-By Gender, 0-Back\nChoice: ");
        scanf("%d", &opt);
        consume_newline();
        if (opt == 1) stats_class(head);
        else if (opt == 2) stats_gender(head);
    } while (opt != 0);
}


void StudentDB_ShowAll(StudentNode* head) {
    if (!head->next) {
        printf("Database is empty.\n");
        return;
    }
    printf("\n--- All Student Records ---\n");
    printf("%-20s%-20s%-10s%-5s%-20s\n", "ID", "Name", "Gender", "Age", "Class ID");
    printf("--------------------------------------------------------------------\n");
    for (StudentNode* p = head->next; p; p = p->next) {
        printf("%-20s%-20s%-10s%-5d%-20s\n", p->info.id, p->info.name, p->info.gender, p->info.age, p->info.class_id);
    }
    printf("--------------------------------------------------------------------\n");
}


// --- Database I/O and Lifecycle ---
StudentNode* StudentDB_Init(const char* db_path) {
    StudentNode* head = (StudentNode*)malloc(sizeof(StudentNode));
    if (!head) {
        perror("Failed to initialize database");
        exit(EXIT_FAILURE);
    }
    head->next = NULL;

    FILE* file = fopen(db_path, "r");
    if (!file) {
        printf("NOTICE: Database file '%s' not found. A new one will be created on exit.\n", db_path);
        return head;
    }

    StudentInfo temp_info;
    while (fscanf(file, "%s %s %s %d %s", temp_info.id, temp_info.name, temp_info.gender, &temp_info.age, temp_info.class_id) == 5) {
        StudentNode* new_node = (StudentNode*)malloc(sizeof(StudentNode));
        if (!new_node) continue;
        new_node->info = temp_info;
        new_node->next = NULL;

        StudentNode* tail = head;
        while (tail->next) tail = tail->next;
        tail->next = new_node;
    }
    fclose(file);
    printf("Database '%s' loaded successfully.\n", db_path);
    return head;
}

void StudentDB_Commit(StudentNode* head, const char* db_path) {
    FILE* file = fopen(db_path, "w");
    if (!file) {
        perror("FATAL: Could not commit changes to database file");
        return;
    }
    for (StudentNode* p = head->next; p; p = p->next) {
        fprintf(file, "%s %s %s %d %s\n", p->info.id, p->info.name, p->info.gender, p->info.age, p->info.class_id);
    }
    fclose(file);
    printf("All changes have been committed to '%s'.\n", db_path);
}

void StudentDB_Destroy(StudentNode* head) {
    StudentNode* p = head;
    while (p) {
        StudentNode* temp = p;
        p = p->next;
        free(temp);
    }
}