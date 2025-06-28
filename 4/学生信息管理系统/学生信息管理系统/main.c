#define _CRT_SECURE_NO_WARNINGS
#include "student_db.h"
#include <stdio.h>
#include <stdlib.h>

#define DATABASE_FILE "student_records.txt"

void print_interface() {
    puts("\n===============================");
    puts("  Student Database Mainframe");
    puts("===============================");
    puts("  1. Add New Record");
    puts("  2. Query Records");
    puts("  3. Update Records");
    puts("  4. View Statistics");
    puts("  5. Display All Records");
    puts("  0. Exit");
    puts("===============================");
    printf("Command > ");
}

int main() {
    StudentNode* db_head = StudentDB_Init(DATABASE_FILE);
    int op_code;
    int needs_saving = 0; // Flag to check if changes were made

    do {
        print_interface();
        scanf("%d", &op_code);
        while (getchar() != '\n'); // clean

        switch (op_code) {
        case 1: StudentDB_AddRecord(db_head); needs_saving = 1; break;
        case 2: StudentDB_QueryMenu(db_head); break;
        case 3: StudentDB_UpdateMenu(db_head); needs_saving = 1; break;
        case 4: StudentDB_StatsMenu(db_head); break;
        case 5: StudentDB_ShowAll(db_head); break;
        case 0:
            if (needs_saving) {
                StudentDB_Commit(db_head, DATABASE_FILE);
            }
            puts("Shutting down mainframe.");
            break;
        default: puts("Error: Invalid operation code."); break;
        }

        if (op_code != 0) {
            printf("\n... (Press Enter to return to menu) ...");
            getchar();
        }

    } while (op_code != 0);

    StudentDB_Destroy(db_head);
    return 0;
}