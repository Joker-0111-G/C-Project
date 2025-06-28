#define _CRT_SECURE_NO_WARNINGS
#include "student_management.h"
#include <stdio.h>

#define DATA_FILE "students.txt"

void show_main_menu() {
    printf("\n========= ѧ����Ϣ����ϵͳ =========\n");
    printf("||                                ||\n");
    printf("||    1. ¼��ѧ����Ϣ             ||\n");
    printf("||    2. ��ѯѧ����Ϣ             ||\n");
    printf("||    3. ����ѧ����Ϣ             ||\n");
    printf("||    4. ͳ��ѧ����Ϣ             ||\n");
    printf("||    5. ��ʾ������Ϣ             ||\n");
    printf("||                                ||\n");
    printf("||    0. ���沢�˳�               ||\n");
    printf("||                                ||\n");
    printf("====================================\n");
    printf("����������ѡ�� [0-5]: ");
}

int main() {
    Node* student_list_head = load_from_file(DATA_FILE);
    int user_choice;

    do {
        show_main_menu();
        scanf("%d", &user_choice);
        while (getchar() != '\n'); // ��������

        switch (user_choice) {
        case 1:
            add_student(student_list_head);
            break;
        case 2:
            query_student_menu(student_list_head);
            break;
        case 3:
            update_student_menu(student_list_head);
            break;
        case 4:
            statistics_menu(student_list_head);
            break;
        case 5:
            display_all_students(student_list_head);
            break;
        case 0:
            save_to_file(student_list_head, DATA_FILE);
            printf("�����˳�ϵͳ...��лʹ�ã�\n");
            break;
        default:
            printf("��Ч�����룬������ 0-5 ֮������֡�\n");
            break;
        }
        if (user_choice != 0) {
            printf("\n�� Enter ���������˵�...");
            getchar();
        }
    } while (user_choice != 0);

    free_list(student_list_head);
    return 0;
}