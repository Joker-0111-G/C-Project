#define _CRT_SECURE_NO_WARNINGS
#include "student.h"

// ������뻺����
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ���ѧ���Ƿ�Ψһ
int isIdUnique(Node* head, const char* id) {
    Node* p = head->next;
    while (p != NULL) {
        if (strcmp(p->data.id, id) == 0) {
            return 0; // ��Ψһ
        }
        p = p->next;
    }
    return 1; // Ψһ
}

// 1. �����¼ģ��
void addStudent(Node* head) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }

    printf("������ѧ��: ");
    scanf("%s", newNode->data.id);
    clearInputBuffer();

    if (!isIdUnique(head, newNode->data.id)) {
        printf("���󣺸�ѧ���Ѵ��ڣ�\n");
        free(newNode);
        return;
    }

    printf("����������: ");
    scanf("%s", newNode->data.name);
    clearInputBuffer();
    printf("�������Ա�: ");
    scanf("%s", newNode->data.gender);
    clearInputBuffer();
    printf("����������: ");
    scanf("%d", &newNode->data.age);
    clearInputBuffer();
    printf("������༶: ");
    scanf("%s", newNode->data.className);
    clearInputBuffer();

    newNode->next = NULL;

    // �ҵ�����β��������
    Node* p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = newNode;

    printf("\nѧ����Ϣ��ӳɹ���\n");
}

// 2. ��ѯ��¼ģ��
void searchStudentById(Node* head) {
    if (head->next == NULL) {
        printf("��ǰ���κ�ѧ����Ϣ��\n");
        return;
    }
    char id[20];
    printf("������Ҫ��ѯ��ѧ��: ");
    scanf("%s", id);
    clearInputBuffer();

    Node* p = head->next;
    int found = 0;
    while (p != NULL) {
        if (strcmp(p->data.id, id) == 0) {
            printf("\n��ѯ�ɹ���ѧ����Ϣ����:\n");
            printf("ѧ��: %s, ����: %s, �Ա�: %s, ����: %d, �༶: %s\n",
                p->data.id, p->data.name, p->data.gender, p->data.age, p->data.className);
            found = 1;
            break;
        }
        p = p->next;
    }

    if (!found) {
        printf("δ�ҵ�ѧ��Ϊ %s ��ѧ����\n", id);
    }
}

void searchStudentByName(Node* head) {
    if (head->next == NULL) {
        printf("��ǰ���κ�ѧ����Ϣ��\n");
        return;
    }
    char name[50];
    printf("������Ҫ��ѯ������: ");
    scanf("%s", name);
    clearInputBuffer();

    Node* p = head->next;
    int found = 0;
    printf("\n��ѯ�������:\n");
    while (p != NULL) {
        if (strcmp(p->data.name, name) == 0) {
            printf("ѧ��: %s, ����: %s, �Ա�: %s, ����: %d, �༶: %s\n",
                p->data.id, p->data.name, p->data.gender, p->data.age, p->data.className);
            found++;
        }
        p = p->next;
    }

    if (found == 0) {
        printf("δ�ҵ�����Ϊ %s ��ѧ����\n", name);
    }
    else {
        printf("���ҵ� %d ����¼��\n", found);
    }
}

void queryMenu(Node* head) {
    int choice;
    do {
        printf("\n--- ��ѯ��¼ģ�� ---\n");
        printf("  1. ��ѧ�Ų�ѯ\n");
        printf("  2. ��������ѯ\n");
        printf("  0. �������˵�\n");
        printf("---------------------\n");
        printf("����������ѡ��: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
        case 1: searchStudentById(head); break;
        case 2: searchStudentByName(head); break;
        case 0: break;
        default: printf("��Чѡ�����������롣\n");
        }
    } while (choice != 0);
}


// 3. ���¼�¼ģ��
void modifyStudent(Node* head) {
    if (head->next == NULL) {
        printf("��ǰ���κ�ѧ����Ϣ��\n");
        return;
    }
    char id[20];
    printf("������Ҫ�޸ĵ�ѧ����ѧ��: ");
    scanf("%s", id);
    clearInputBuffer();

    Node* p = head->next;
    int found = 0;
    while (p != NULL) {
        if (strcmp(p->data.id, id) == 0) {
            printf("���ҵ���ѧ��������������Ϣ:\n");
            printf("������������: ");
            scanf("%s", p->data.name);
            clearInputBuffer();
            printf("���������Ա�: ");
            scanf("%s", p->data.gender);
            clearInputBuffer();
            printf("������������: ");
            scanf("%d", &p->data.age);
            clearInputBuffer();
            printf("�������°༶: ");
            scanf("%s", p->data.className);
            clearInputBuffer();
            printf("\nѧ����Ϣ�޸ĳɹ���\n");
            found = 1;
            break;
        }
        p = p->next;
    }

    if (!found) {
        printf("δ�ҵ�ѧ��Ϊ %s ��ѧ����\n", id);
    }
}

void deleteStudent(Node* head) {
    if (head->next == NULL) {
        printf("��ǰ���κ�ѧ����Ϣ��\n");
        return;
    }
    char id[20];
    printf("������Ҫɾ����ѧ����ѧ��: ");
    scanf("%s", id);
    clearInputBuffer();

    Node* prev = head;
    Node* curr = head->next;
    int found = 0;

    while (curr != NULL) {
        if (strcmp(curr->data.id, id) == 0) {
            prev->next = curr->next;
            free(curr);
            printf("ѧ��Ϊ %s ��ѧ����Ϣ��ɾ����\n", id);
            found = 1;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    if (!found) {
        printf("δ�ҵ�ѧ��Ϊ %s ��ѧ����\n", id);
    }
}

void updateMenu(Node* head) {
    int choice;
    do {
        printf("\n--- ���¼�¼ģ�� ---\n");
        printf("  1. �޸�ѧ����Ϣ\n");
        printf("  2. ɾ��ѧ����Ϣ\n");
        printf("  0. �������˵�\n");
        printf("---------------------\n");
        printf("����������ѡ��: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
        case 1: modifyStudent(head); break;
        case 2: deleteStudent(head); break;
        case 0: break;
        default: printf("��Чѡ�����������롣\n");
        }
    } while (choice != 0);
}

// 4. ͳ�Ƽ�¼ģ��
void statisticsByClass(Node* head) {
    if (head->next == NULL) {
        printf("��ǰ���κ�ѧ����Ϣ��\n");
        return;
    }
    char className[50];
    printf("������Ҫͳ�Ƶİ༶����: ");
    scanf("%s", className);
    clearInputBuffer();

    Node* p = head->next;
    int count = 0;
    while (p != NULL) {
        if (strcmp(p->data.className, className) == 0) {
            count++;
        }
        p = p->next;
    }
    printf("�༶ %s ���� %d ��ѧ����\n", className, count);
}

void statisticsByGender(Node* head) {
    if (head->next == NULL) {
        printf("��ǰ���κ�ѧ����Ϣ��\n");
        return;
    }
    int male_count = 0;
    int female_count = 0;
    Node* p = head->next;
    while (p != NULL) {
        if (strcmp(p->data.gender, "��") == 0) {
            male_count++;
        }
        else if (strcmp(p->data.gender, "Ů") == 0) {
            female_count++;
        }
        p = p->next;
    }
    printf("ѧ�������У������� %d �ˣ�Ů���� %d �ˡ�\n", male_count, female_count);
}

void statisticsMenu(Node* head) {
    int choice;
    do {
        printf("\n--- ͳ�Ƽ�¼ģ�� ---\n");
        printf("  1. ���༶ͳ��\n");
        printf("  2. ���Ա�ͳ��\n");
        printf("  0. �������˵�\n");
        printf("---------------------\n");
        printf("����������ѡ��: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
        case 1: statisticsByClass(head); break;
        case 2: statisticsByGender(head); break;
        case 0: break;
        default: printf("��Чѡ�����������롣\n");
        }
    } while (choice != 0);
}


// 5. �����¼ģ��
void displayAllStudents(Node* head) {
    if (head->next == NULL) {
        printf("��ǰ���κ�ѧ����Ϣ��\n");
        return;
    }
    printf("\n======================= ����ѧ����Ϣ =======================\n");
    printf("%-15s %-15s %-10s %-10s %-15s\n", "ѧ��", "����", "�Ա�", "����", "�༶");
    printf("------------------------------------------------------------\n");
    Node* p = head->next;
    while (p != NULL) {
        printf("%-15s %-15s %-10s %-10d %-15s\n",
            p->data.id, p->data.name, p->data.gender, p->data.age, p->data.className);
        p = p->next;
    }
    printf("============================================================\n");
}

// 6. �ļ�����ģ��
void saveToFile(Node* head, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("���ļ� %s ʧ�ܣ�\n", filename);
        return;
    }

    Node* p = head->next;
    while (p != NULL) {
        fprintf(fp, "%s %s %s %d %s\n",
            p->data.id, p->data.name, p->data.gender, p->data.age, p->data.className);
        p = p->next;
    }

    fclose(fp);
    printf("�����ѳɹ����浽 %s �ļ��С�\n", filename);
}

Node* loadFromFile(const char* filename) {
    // ����һ����ͷ�ڵ�Ŀ�����
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        exit(1);
    }
    head->next = NULL;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("δ�ҵ������ļ� %s��������һ����ϵͳ��\n", filename);
        return head;
    }

    Student temp;
    while (fscanf(fp, "%s %s %s %d %s", temp.id, temp.name, temp.gender, &temp.age, temp.className) != EOF) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("�ڴ����ʧ�ܣ�\n");
            continue;
        }
        newNode->data = temp;
        newNode->next = NULL;

        // ���뵽����β��
        Node* p = head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newNode;
    }

    fclose(fp);
    printf("�Ѵ� %s �ļ��������ݡ�\n", filename);
    return head;
}

// �����������ͷ�����
void freeList(Node* head) {
    Node* p = head;
    Node* temp;
    while (p != NULL) {
        temp = p;
        p = p->next;
        free(temp);
    }
}