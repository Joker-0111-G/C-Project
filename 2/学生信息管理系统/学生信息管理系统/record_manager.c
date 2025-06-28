#define _CRT_SECURE_NO_WARNINGS
#include "record_manager.h"

static void flush_stdin() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// ��
void create_new_record(Link_Node* list_head) {
    Link_Node* new_node = (Link_Node*)malloc(sizeof(Link_Node));
    if (new_node == NULL) {
        puts("�ڴ治�㣡");
        return;
    }

    printf("����ѧ��: ");
    scanf("%s", new_node->record.stu_id);
    flush_stdin();

    // ���ѧ���Ƿ����
    Link_Node* checker = list_head->p_next;
    while (checker) {
        if (strcmp(checker->record.stu_id, new_node->record.stu_id) == 0) {
            puts("���󣺴�ѧ���Ѵ��ڣ�");
            free(new_node);
            return;
        }
        checker = checker->p_next;
    }

    printf("��������: ");
    scanf("%s", new_node->record.stu_name);
    flush_stdin();
    printf("�����Ա�: ");
    scanf("%s", new_node->record.stu_gender);
    flush_stdin();
    printf("��������: ");
    scanf("%d", &new_node->record.stu_age);
    flush_stdin();
    printf("����༶: ");
    scanf("%s", new_node->record.stu_class);
    flush_stdin();
    new_node->p_next = NULL;

    Link_Node* current = list_head;
    while (current->p_next != NULL) {
        current = current->p_next;
    }
    current->p_next = new_node;
    puts("\n�¼�¼����ӡ�");
}

// �飨�Ӳ˵���
static void find_by_student_id(Link_Node* list_head) {
    char id[20];
    printf("����Ҫ���ҵ�ѧ��: ");
    scanf("%s", id);
    flush_stdin();

    Link_Node* ptr = list_head->p_next;
    while (ptr) {
        if (strcmp(ptr->record.stu_id, id) == 0) {
            printf("\n�ҵ���¼:\n");
            printf("ѧ��:%s, ����:%s, �Ա�:%s, ����:%d, �༶:%s\n",
                ptr->record.stu_id, ptr->record.stu_name, ptr->record.stu_gender, ptr->record.stu_age, ptr->record.stu_class);
            return;
        }
        ptr = ptr->p_next;
    }
    printf("���ݿ����޴�ѧ�� %s �ļ�¼��\n", id);
}

static void find_by_student_name(Link_Node* list_head) {
    char name[50];
    int found_count = 0;
    printf("����Ҫ���ҵ�����: ");
    scanf("%s", name);
    flush_stdin();

    Link_Node* ptr = list_head->p_next;
    puts("\n���ҽ��:");
    while (ptr) {
        if (strcmp(ptr->record.stu_name, name) == 0) {
            printf("ѧ��:%s, ����:%s, �Ա�:%s, ����:%d, �༶:%s\n",
                ptr->record.stu_id, ptr->record.stu_name, ptr->record.stu_gender, ptr->record.stu_age, ptr->record.stu_class);
            found_count++;
        }
        ptr = ptr->p_next;
    }
    printf("���ҵ� %d ����Ϊ %s ��ѧ����\n", found_count, name);
}

void find_record_menu(Link_Node* list_head) {
    int choice;
    do {
        puts("\n--- ���Ҽ�¼ ---");
        puts("  1. ��ѧ�Ų���");
        puts("  2. ����������");
        puts("  0. ����");
        printf("���ѡ��: ");
        scanf("%d", &choice);
        flush_stdin();

        if (choice == 1) find_by_student_id(list_head);
        else if (choice == 2) find_by_student_name(list_head);
        else if (choice != 0) puts("�������");
    } while (choice != 0);
}

// �ģ��Ӳ˵���
static void update_record(Link_Node* list_head) {
    char id[20];
    printf("������޸ļ�¼��ѧ��: ");
    scanf("%s", id);
    flush_stdin();

    Link_Node* target = list_head->p_next;
    while (target) {
        if (strcmp(target->record.stu_id, id) == 0) {
            puts("�ҵ���¼�������������ݡ�");
            printf("����������: "); scanf("%s", target->record.stu_name); flush_stdin();
            printf("�������Ա�: "); scanf("%s", target->record.stu_gender); flush_stdin();
            printf("����������: "); scanf("%d", &target->record.stu_age); flush_stdin();
            printf("�����°༶: "); scanf("%s", target->record.stu_class); flush_stdin();
            puts("\n��¼������ϡ�");
            return;
        }
        target = target->p_next;
    }
    printf("���ݿ����޴�ѧ�� %s �ļ�¼��\n", id);
}

// ɾ
static void remove_record(Link_Node* list_head) {
    char id[20];
    printf("�����ɾ����¼��ѧ��: ");
    scanf("%s", id);
    flush_stdin();

    Link_Node* prev = list_head;
    Link_Node* curr = list_head->p_next;
    while (curr) {
        if (strcmp(curr->record.stu_id, id) == 0) {
            prev->p_next = curr->p_next;
            free(curr);
            printf("ѧ��Ϊ %s �ļ�¼�ѱ��Ƴ���\n", id);
            return;
        }
        prev = curr;
        curr = curr->p_next;
    }
    printf("���ݿ����޴�ѧ�� %s �ļ�¼��\n", id);
}


void alter_record_menu(Link_Node* list_head) {
    int choice;
    do {
        puts("\n--- ���ļ�¼ ---");
        puts("  1. �޸ļ�¼");
        puts("  2. �Ƴ���¼");
        puts("  0. ����");
        printf("���ѡ��: ");
        scanf("%d", &choice);
        flush_stdin();

        if (choice == 1) { update_record(list_head); persist_records_to_disk(list_head, "student_data.db"); }
        else if (choice == 2) { remove_record(list_head); persist_records_to_disk(list_head, "student_data.db"); }
        else if (choice != 0) puts("�������");
    } while (choice != 0);
}


// ͳ��
static void summarize_by_class(Link_Node* list_head) {
    char class_name[50];
    int total = 0;
    printf("����Ҫͳ�Ƶİ༶��: ");
    scanf("%s", class_name);
    flush_stdin();

    for (Link_Node* p = list_head->p_next; p != NULL; p = p->p_next) {
        if (strcmp(p->record.stu_class, class_name) == 0) {
            total++;
        }
    }
    printf("�༶ [%s] ��ѧ������Ϊ: %d\n", class_name, total);
}

static void summarize_by_gender(Link_Node* list_head) {
    int males = 0, females = 0;
    for (Link_Node* p = list_head->p_next; p != NULL; p = p->p_next) {
        if (strcmp(p->record.stu_gender, "��") == 0) males++;
        else if (strcmp(p->record.stu_gender, "Ů") == 0) females++;
    }
    printf("��ǰ��¼�У�����: %d ��, Ů��: %d �ˡ�\n", males, females);
}

void summarize_data_menu(Link_Node* list_head) {
    int choice;
    do {
        puts("\n--- ���ݻ��� ---");
        puts("  1. ���༶����");
        puts("  2. ���Ա����");
        puts("  0. ����");
        printf("���ѡ��: ");
        scanf("%d", &choice);
        flush_stdin();

        if (choice == 1) summarize_by_class(list_head);
        else if (choice == 2) summarize_by_gender(list_head);
        else if (choice != 0) puts("�������");
    } while (choice != 0);
}


// ��ʾȫ��
void print_all_records(Link_Node* list_head) {
    if (!list_head->p_next) {
        puts("��ǰû���κμ�¼��");
        return;
    }
    puts("\n=============== ȫ��ѧ����¼ ================");
    printf("%-12s | %-12s | %-8s | %-8s | %-12s\n", "ѧ��", "����", "�Ա�", "����", "�༶");
    puts("-------------------------------------------------");

    for (Link_Node* p = list_head->p_next; p != NULL; p = p->p_next) {
        printf("%-12s | %-12s | %-8s | %-8d | %-12s\n",
            p->record.stu_id, p->record.stu_name, p->record.stu_gender, p->record.stu_age, p->record.stu_class);
    }
    puts("=================================================");
}

// �ļ�IO
void persist_records_to_disk(Link_Node* list_head, const char* filepath) {
    FILE* file_ptr = fopen(filepath, "w");
    if (!file_ptr) {
        printf("��������: �޷�д�뵽�ļ� %s\n", filepath);
        return;
    }
    for (Link_Node* p = list_head->p_next; p; p = p->p_next) {
        fprintf(file_ptr, "%s %s %s %d %s\n",
            p->record.stu_id, p->record.stu_name, p->record.stu_gender, p->record.stu_age, p->record.stu_class);
    }
    fclose(file_ptr);
}

Link_Node* load_records_from_disk(const char* filepath) {
    Link_Node* head = (Link_Node*)malloc(sizeof(Link_Node));
    if (!head) exit(1);
    head->p_next = NULL;

    FILE* file_ptr = fopen(filepath, "r");
    if (!file_ptr) {
        printf("�����ļ� %s δ�ҵ�, ϵͳ���Կռ�¼������\n", filepath);
        return head;
    }

    Info_Student buffer;
    Link_Node* tail = head;
    while (fscanf(file_ptr, "%s %s %s %d %s", buffer.stu_id, buffer.stu_name, buffer.stu_gender, &buffer.stu_age, buffer.stu_class) == 5) {
        Link_Node* new_node = (Link_Node*)malloc(sizeof(Link_Node));
        if (!new_node) {
            puts("����ʱ�ڴ����ʧ��!");
            break;
        }
        new_node->record = buffer;
        new_node->p_next = NULL;
        tail->p_next = new_node;
        tail = new_node;
    }
    fclose(file_ptr);
    printf("�Ѵ� %s �ɹ����ؼ�¼��\n", filepath);
    return head;
}

// �ͷ��ڴ�
void release_all_nodes(Link_Node* list_head) {
    Link_Node* p = list_head;
    while (p) {
        Link_Node* to_delete = p;
        p = p->p_next;
        free(to_delete);
    }
}