#define _CRT_SECURE_NO_WARNINGS
#include "student_management.h"
#include <stdio.h>

#define DATA_FILE "students.txt"

void show_main_menu() {
    printf("\n========= 学生信息管理系统 =========\n");
    printf("||                                ||\n");
    printf("||    1. 录入学生信息             ||\n");
    printf("||    2. 查询学生信息             ||\n");
    printf("||    3. 更新学生信息             ||\n");
    printf("||    4. 统计学生信息             ||\n");
    printf("||    5. 显示所有信息             ||\n");
    printf("||                                ||\n");
    printf("||    0. 保存并退出               ||\n");
    printf("||                                ||\n");
    printf("====================================\n");
    printf("请输入您的选择 [0-5]: ");
}

int main() {
    Node* student_list_head = load_from_file(DATA_FILE);
    int user_choice;

    do {
        show_main_menu();
        scanf("%d", &user_choice);
        while (getchar() != '\n'); // 清理缓冲区

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
            printf("正在退出系统...感谢使用！\n");
            break;
        default:
            printf("无效的输入，请输入 0-5 之间的数字。\n");
            break;
        }
        if (user_choice != 0) {
            printf("\n按 Enter 键返回主菜单...");
            getchar();
        }
    } while (user_choice != 0);

    free_list(student_list_head);
    return 0;
}