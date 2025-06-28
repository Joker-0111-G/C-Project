#define _CRT_SECURE_NO_WARNINGS
#include "record_manager.h"
#include <stdio.h>
#include <stdlib.h>

#define DB_FILE "student_data.txt"

void display_main_interface() {
    puts("\n###### 学生档案管理系统 ######");
    puts("   [1] 新增学生档案");
    puts("   [2] 查找学生档案");
    puts("   [3] 更改学生档案");
    puts("   [4] 汇总档案数据");
    puts("   [5] 显示所有档案");
    puts("   [0] 退出系统");
    puts("##############################");
    printf("请输入操作代码 [0-5]: ");
}

int main(void) {
    Link_Node* database_head = load_records_from_disk(DB_FILE);
    int command;

    do {
        display_main_interface();
        scanf("%d", &command);
        while (getchar() != '\n'); // 清理

        switch (command) {
        case 1:
            create_new_record(database_head);
            persist_records_to_disk(database_head, DB_FILE); // 实时保存
            break;
        case 2:
            find_record_menu(database_head);
            break;
        case 3:
            alter_record_menu(database_head);
            // 保存操作在子菜单中完成
            break;
        case 4:
            summarize_data_menu(database_head);
            break;
        case 5:
            print_all_records(database_head);
            break;
        case 0:
            puts("系统正在退出...");
            break;
        default:
            puts("无效命令，请重新输入。");
            break;
        }
        if (command != 0) {
            puts("\n按回车键以继续...");
            getchar();
            system("cls"); // Windows/DOS a specific command
        }

    } while (command != 0);

    release_all_nodes(database_head);
    puts("感谢使用！");
    return 0;
}