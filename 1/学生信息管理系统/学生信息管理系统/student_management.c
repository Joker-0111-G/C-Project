#define _CRT_SECURE_NO_WARNINGS
#include "student_management.h"

// �������뻺����
static void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ���ѧ��Ψһ��
static int is_id_unique(Node* head, const char* id) {
    Node* current = head->next;
    while (current != NULL) {
        if (strcmp(current->data.id, id) == 0) {
            return 0; // ��Ψһ
        }
        current = current->next;
    }
    return 1; // Ψһ
}

// 1. ¼��ѧ��
void add_student(Node* head) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }

    printf("������ѧ��: ");
    scanf("%s", new_node->data.id);
    clear_buffer();

    if (!is_id_unique(head, new_node->data.id)) {
        printf("����: ��ѧ���Ѿ����ڣ�\n");
        free(new_node);
        return;
    }

    printf("����������: ");
    scanf("%s", new_node->data.name);
    clear_buffer();
    printf("�������Ա�: ");
    scanf("%s", new_node->data.gender);
    clear_buffer();
    printf("����������: ");
    scanf("%d", &new_node->data.age);
    clear_buffer();
    printf("������༶: ");
    scanf("%s", new_node->data.className);
    clear_buffer();
    new_node->next = NULL;

    Node* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = new_node;
    printf("\nѧ����Ϣ��ӳɹ���\n");
}

// 2. ��ѯ (��ID)
static void search_by_id(Node* head) {
    char id[20];
    printf("������Ҫ��ѯ��ѧ��: ");
    scanf("%s", id);
    clear_buffer();

    Node* current = head->next;
    while (current != NULL) {
        if (strcmp(current->data.id, id) == 0) {
            printf("\n��ѯ�ɹ�����Ϣ����:\n");
            printf("ѧ��: %s, ����: %s, �Ա�: %s, ����: %d, �༶: %s\n",
                current->data.id, current->data.name, current->data.gender, current->data.age, current->data.className);
            return;
        }
        current = current->next;
    }
    printf("δ�ҵ�ѧ��Ϊ %s ��ѧ����\n", id);
}

// 2. ��ѯ (������)
static void search_by_name(Node* head) {
    char name[50];
    int count = 0;
    printf("������Ҫ��ѯ������: ");
    scanf("%s", name);
    clear_buffer();

    Node* current = head->next;
    printf("\n��ѯ���:\n");
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            printf("ѧ��: %s, ����: %s, �Ա�: %s, ����: %d, �༶: %s\n",
                current->data.id, current->data.name, current->data.gender, current->data.age, current->data.className);
            count++;
        }
        current = current->next;
    }

    if (count == 0) {
        printf("δ�ҵ�����Ϊ %s ��ѧ����\n", name);
    }
    else {
        printf("���ҵ� %d ����¼��\n", count);
    }
}

void query_student_menu(Node* head) {
    int option;
    do {
        printf("\n--- ��ѯ�˵� ---\n");
        printf("  1. ��ѧ�Ų�ѯ\n");
        printf("  2. ��������ѯ\n");
        printf("  0. �����ϼ�\n");
        printf("------------------\n");
        printf("������ѡ��: ");
        scanf("%d", &option);
        clear_buffer();
        switch (option) {
        case 1: search_by_id(head); break;
        case 2: search_by_name(head); break;
        case 0: break;
        default: printf("��Чѡ��!\n"); break;
        }
    } while (option != 0);
}

// 3. �޸�
static void modify_student(Node* head) {
    char id[20];
    printf("������Ҫ�޸ĵ�ѧ����ѧ��: ");
    scanf("%s", id);
    clear_buffer();

    Node* current = head->next;
    while (current) {
        if (strcmp(current->data.id, id) == 0) {
            printf("�ҵ�ѧ��������������Ϣ:\n");
            printf("������������: ");
            scanf("%s", current->data.name);
            clear_buffer();
            printf("���������Ա�: ");
            scanf("%s", current->data.gender);
            clear_buffer();
            printf("������������: ");
            scanf("%d", &current->data.age);
            clear_buffer();
            printf("�������°༶: ");
            scanf("%s", current->data.className);
            clear_buffer();
            printf("\n��Ϣ�޸ĳɹ���\n");
            return;
        }
        current = current->next;
    }
    printf("δ�ҵ���ѧ�ŵ�ѧ����\n");
}

// 3. ɾ��
static void delete_student(Node* head) {
    char id[20];
    printf("������Ҫɾ����ѧ����ѧ��: ");
    scanf("%s", id);
    clear_buffer();

    Node* prev = head;
    Node* curr = head->next;
    while (curr) {
        if (strcmp(curr->data.id, id) == 0) {
            prev->next = curr->next;
            free(curr);
            printf("ѧ��Ϊ %s ��ѧ����ɾ����\n", id);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("δ�ҵ���ѧ�ŵ�ѧ����\n");
}

void update_student_menu(Node* head) {
    int option;
    do {
        printf("\n--- ���²˵� ---\n");
        printf("  1. �޸�ѧ����Ϣ\n");
        printf("  2. ɾ��ѧ����Ϣ\n");
        printf("  0. �����ϼ�\n");
        printf("------------------\n");
        printf("������ѡ��: ");
        scanf("%d", &option);
        clear_buffer();
        switch (option) {
        case 1: modify_student(head); break;
        case 2: delete_student(head); break;
        case 0: break;
        default: printf("��Чѡ��!\n"); break;
        }
    } while (option != 0);
}

// 4. ͳ�� (���༶)
static void stats_by_class(Node* head) {
    char class_name[50];
    int count = 0;
    printf("������Ҫͳ�Ƶİ༶: ");
    scanf("%s", class_name);
    clear_buffer();

    Node* current = head->next;
    while (current) {
        if (strcmp(current->data.className, class_name) == 0) {
            count++;
        }
        current = current->next;
    }
    printf("�༶ %s ���� %d ��ѧ����\n", class_name, count);
}

// 4. ͳ�� (���Ա�)
static void stats_by_gender(Node* head) {
    int male = 0, female = 0;
    Node* current = head->next;
    while (current) {
        if (strcmp(current->data.gender, "��") == 0) {
            male++;
        }
        else if (strcmp(current->data.gender, "Ů") == 0) {
            female++;
        }
        current = current->next;
    }
    printf("ѧ�������У����� %d �ˣ�Ů�� %d �ˡ�\n", male, female);
}


void statistics_menu(Node* head) {
    int option;
    do {
        printf("\n--- ͳ�Ʋ˵� ---\n");
        printf("  1. ���༶ͳ��\n");
        printf("  2. ���Ա�ͳ��\n");
        printf("  0. �����ϼ�\n");
        printf("------------------\n");
        printf("������ѡ��: ");
        scanf("%d", &option);
        clear_buffer();
        switch (option) {
        case 1: stats_by_class(head); break;
        case 2: stats_by_gender(head); break;
        case 0: break;
        default: printf("��Чѡ��!\n"); break;
        }
    } while (option != 0);
}


// 5. ��ʾ����
void display_all_students(Node* head) {
    if (head->next == NULL) {
        printf("ϵͳ��û��ѧ����Ϣ��\n");
        return;
    }
    printf("\n======================= ����ѧ����Ϣ =======================\n");
    printf("%-15s %-15s %-10s %-10s %-15s\n", "ѧ��", "����", "�Ա�", "����", "�༶");
    printf("------------------------------------------------------------\n");

    Node* current = head->next;
    while (current != NULL) {
        printf("%-15s %-15s %-10s %-10d %-15s\n",
            current->data.id, current->data.name, current->data.gender, current->data.age, current->data.className);
        current = current->next;
    }
    printf("============================================================\n");
}


// 6. �ļ�����
void save_to_file(Node* head, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("����: �޷����ļ� %s ����д�롣\n", filename);
        return;
    }
    Node* current = head->next;
    while (current) {
        fprintf(fp, "%s %s %s %d %s\n",
            current->data.id, current->data.name, current->data.gender, current->data.age, current->data.className);
        current = current->next;
    }
    fclose(fp);
    printf("�����ѱ��浽 %s\n", filename);
}

Node* load_from_file(const char* filename) {
    Node* head = (Node*)malloc(sizeof(Node));
    if (!head) {
        printf("�ؼ��ڴ����ʧ�ܣ�\n");
        exit(1);
    }
    head->next = NULL;

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("δ�ҵ������ļ� %s, ��������ϵͳ��\n", filename);
        return head;
    }

    Student temp_stu;
    while (fscanf(fp, "%s %s %s %d %s", temp_stu.id, temp_stu.name, temp_stu.gender, &temp_stu.age, temp_stu.className) != EOF) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (!new_node) {
            printf("��������ʱ�ڴ����ʧ�ܣ�\n");
            break;
        }
        new_node->data = temp_stu;
        new_node->next = NULL;

        Node* tail = head;
        while (tail->next) {
            tail = tail->next;
        }
        tail->next = new_node;
    }
    fclose(fp);
    printf("�Ѵ� %s �ļ��������ݡ�\n", filename);
    return head;
}

// �ͷ�����
void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}