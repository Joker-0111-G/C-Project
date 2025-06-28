#define _CRT_SECURE_NO_WARNINGS
#include "student.h"

#define FILENAME "student.txt"

void showMenu() {
    printf("\n========= 学生信息管理系统 =========\n");
    printf("||                                ||\n");
    printf("||    1. 录入学生信息             ||\n");
    printf("||    2. 查询学生信息             ||\n");
    printf("||    3. 更新学生信息             ||\n");
    printf("||    4. 统计学生信息             ||\n");
    printf("||    5. 显示所有信息             ||\n");
    printf("||                                ||\n");
    printf("||    0. 退出系统 (Exit)          ||\n");
    printf("||                                ||\n");
    printf("====================================\n");
    printf("请输入您的选择 [0-5]: ");
}

int main() {
    // 程序启动时，从文件加载数据
    Node* head = loadFromFile(FILENAME);
    int choice;

    do {
        showMenu();
        scanf("%d", &choice);
        clearInputBuffer(); // 吸收多余的换行符

        switch (choice) {
        case 1:
            addStudent(head);
            saveToFile(head, FILENAME);
            break;
        case 2:
            queryMenu(head);
            break;
        case 3:
            updateMenu(head);
            saveToFile(head, FILENAME);
            break;
        case 4:
            statisticsMenu(head);
            break;
        case 5:
            displayAllStudents(head);
            break;
        case 0:
        {   FILE* fp = fopen(FILENAME, "w"); }// 以写入模式打开文件，会直接清空内容
            printf("正在退出系统...感谢使用！\n");
            break;
        default:
            printf("无效的输入，请输入 0-5 之间的数字。\n");
            break;
        }
        printf("\n按 Enter 键继续...");
        getchar(); // 暂停程序，等待用户按键
        system("cls"); // 清屏

    } while (choice != 0);

    // 退出程序前，释放链表内存
    freeList(head);

    return 0;
}