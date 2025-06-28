#define _CRT_SECURE_NO_WARNINGS
#include "data_manager.h"
#include <stdio.h>

#define DATA_SOURCE "students.txt"

void print_main_menu() {
    puts("\n*** Student Information System ***");
    puts("  1 -> Add Student");
    puts("  2 -> Query Student");
    puts("  3 -> Update Student");
    puts("  4 -> Analyze Students");
    puts("  5 -> List All Students");
    puts("  0 -> Save & Exit");
    printf("Enter command: ");
}

int main(int argc, char* argv[]) {
    ListNode* data_head = load_entries_from_file(DATA_SOURCE);
    int command_code;

    do {
        print_main_menu();
        scanf("%d", &command_code);
        while (getchar() != '\n'); // flush

        switch (command_code) {
        case 1:
            insert_new_entry(data_head);
            break;
        case 2:
            access_entry_submenu(data_head);
            break;
        case 3:
            modify_entry_submenu(data_head);
            break;
        case 4:
            analyze_data_submenu(data_head);
            break;
        case 5:
            list_all_entries(data_head);
            break;
        case 0:
            save_entries_to_file(data_head, DATA_SOURCE);
            puts("Data saved. Exiting...");
            break;
        default:
            puts("Invalid command code.");
        }
        if (command_code != 0) {
            printf("\nPress ENTER to continue...");
            getchar();
        }

    } while (command_code != 0);

    deallocate_list(data_head);
    return 0;
}