#define _CRT_SECURE_NO_WARNINGS
#include "record_manager.h"
#include <stdio.h>
#include <stdlib.h>

#define DB_FILE "student_data.txt"

void display_main_interface() {
    puts("\n###### ѧ����������ϵͳ ######");
    puts("   [1] ����ѧ������");
    puts("   [2] ����ѧ������");
    puts("   [3] ����ѧ������");
    puts("   [4] ���ܵ�������");
    puts("   [5] ��ʾ���е���");
    puts("   [0] �˳�ϵͳ");
    puts("##############################");
    printf("������������� [0-5]: ");
}

int main(void) {
    Link_Node* database_head = load_records_from_disk(DB_FILE);
    int command;

    do {
        display_main_interface();
        scanf("%d", &command);
        while (getchar() != '\n'); // ����

        switch (command) {
        case 1:
            create_new_record(database_head);
            persist_records_to_disk(database_head, DB_FILE); // ʵʱ����
            break;
        case 2:
            find_record_menu(database_head);
            break;
        case 3:
            alter_record_menu(database_head);
            // ����������Ӳ˵������
            break;
        case 4:
            summarize_data_menu(database_head);
            break;
        case 5:
            print_all_records(database_head);
            break;
        case 0:
            puts("ϵͳ�����˳�...");
            break;
        default:
            puts("��Ч������������롣");
            break;
        }
        if (command != 0) {
            puts("\n���س����Լ���...");
            getchar();
            system("cls"); // Windows/DOS a specific command
        }

    } while (command != 0);

    release_all_nodes(database_head);
    puts("��лʹ�ã�");
    return 0;
}