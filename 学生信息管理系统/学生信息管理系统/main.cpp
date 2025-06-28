#define _CRT_SECURE_NO_WARNINGS
#include "student.h"

#define FILENAME "student.txt"

void showMenu() {
    printf("\n========= ѧ����Ϣ����ϵͳ =========\n");
    printf("||                                ||\n");
    printf("||    1. ¼��ѧ����Ϣ             ||\n");
    printf("||    2. ��ѯѧ����Ϣ             ||\n");
    printf("||    3. ����ѧ����Ϣ             ||\n");
    printf("||    4. ͳ��ѧ����Ϣ             ||\n");
    printf("||    5. ��ʾ������Ϣ             ||\n");
    printf("||                                ||\n");
    printf("||    0. �˳�ϵͳ (Exit)          ||\n");
    printf("||                                ||\n");
    printf("====================================\n");
    printf("����������ѡ�� [0-5]: ");
}

int main() {
    // ��������ʱ�����ļ���������
    Node* head = loadFromFile(FILENAME);
    int choice;

    do {
        showMenu();
        scanf("%d", &choice);
        clearInputBuffer(); // ���ն���Ļ��з�

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
        {   FILE* fp = fopen(FILENAME, "w"); }// ��д��ģʽ���ļ�����ֱ���������
            printf("�����˳�ϵͳ...��лʹ�ã�\n");
            break;
        default:
            printf("��Ч�����룬������ 0-5 ֮������֡�\n");
            break;
        }
        printf("\n�� Enter ������...");
        getchar(); // ��ͣ���򣬵ȴ��û�����
        system("cls"); // ����

    } while (choice != 0);

    // �˳�����ǰ���ͷ������ڴ�
    freeList(head);

    return 0;
}