#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ա��������Ϣ�ṹ��
typedef struct Employee {
    char employee_id[20]; // ��Ա���
    char name[50];        // ����
    double base_salary;   // ��������
    double allowance;     // ����
    double bonus;         // ����
    double deductions;    // �۳� (�����Ը�����Ҫ���ӣ�������Ϊʾ��)
    double total_salary;  // �ܹ��� (����ó�)
    int month;            // �·�
    int year;             // ���
    // ���ݾ������������������ֶ�
} Employee;

// ����ڵ�ṹ��
typedef struct Node {
    Employee data;
    struct Node* next;
} Node;

// ȫ������ͷָ�루Ҳ������Ϊ�������ݣ�
Node* head = NULL; // ��ʼ��Ϊ�գ���ʾ����Ϊ��


// �����½ڵ㺯��
Node* createNode(Employee emp_data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        exit(1); // �ڴ����ʧ�ܣ������˳�
    }
    newNode->data = emp_data;
    newNode->next = NULL;
    return newNode;
}

// ���Ա�����ʼ�¼����
void addEmployeeRecord() {
    Employee emp;
    printf("\n--- ����Ա�����ʼ�¼ ---\n");
    printf("������Ա�����: ");
    scanf("%s", emp.employee_id);
    printf("����������: ");
    scanf("%s", emp.name);
    printf("�������������: ");
    scanf("%lf", &emp.base_salary);
    printf("���������: ");
    scanf("%lf", &emp.allowance);
    printf("�����뽱��: ");
    scanf("%lf", &emp.bonus);
    printf("������۳��� (���û��������0): ");
    scanf("%lf", &emp.deductions);
    printf("�������·� (1-12): ");
    scanf("%d", &emp.month);
    printf("���������: ");
    scanf("%d", &emp.year);

    // �����ܹ���
    emp.total_salary = emp.base_salary + emp.allowance + emp.bonus - emp.deductions;

    Node* newNode = createNode(emp);
    if (head == NULL) {
        head = newNode; // �������Ϊ�գ��½ڵ㼴Ϊͷ�ڵ�
    }
    else {
        Node* current = head;
        while (current->next != NULL) {
            current = current->next; // ����������ĩβ
        }
        current->next = newNode; // ���½ڵ���ӵ�����ĩβ
    }
    printf("Ա����¼��ӳɹ���\n");
}

// ���·���ʾ���м�¼
void displayAllRecordsByMonth(int month, int year) {
    if (head == NULL) {
        printf("Ŀǰû�й��ʼ�¼��\n");
        return;
    }
    printf("\n--- %d��%d�µĹ��ʼ�¼ ---\n", year, month);
    Node* current = head;
    int found = 0;
    while (current != NULL) {
        if (current->data.month == month && current->data.year == year) {
            printf("���: %s, ����: %s, �·�: %d/%d, ��������: %.2lf, ����: %.2lf, ����: %.2lf, �۳�: %.2lf, �ܹ���: %.2lf\n",
                current->data.employee_id, current->data.name, current->data.month, current->data.year,
                current->data.base_salary, current->data.allowance, current->data.bonus, current->data.deductions, current->data.total_salary);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("δ�ҵ�%d��%d�µļ�¼��\n", year, month);
    }
}

// ��ѯ����ʾ�ض�Ա���ļ�¼
void queryEmployeeRecords(char* employee_id) {
    if (head == NULL) {
        printf("Ŀǰû�й��ʼ�¼��\n");
        return;
    }
    printf("\n--- Ա�����: %s �Ĺ��ʼ�¼ ---\n", employee_id);
    Node* current = head;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->data.employee_id, employee_id) == 0) {
            printf("�·�: %d/%d, ��������: %.2lf, ����: %.2lf, ����: %.2lf, �۳�: %.2lf, �ܹ���: %.2lf\n",
                current->data.month, current->data.year, current->data.base_salary,
                current->data.allowance, current->data.bonus, current->data.deductions, current->data.total_salary);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("δ�ҵ�Ա�����: %s �ļ�¼��\n", employee_id);
    }
}

// ����Ա���ض��·ݵĹ��ʼ�¼
void updateEmployeeRecord(char* employee_id, int month, int year) {
    if (head == NULL) {
        printf("û�пɸ��µĹ��ʼ�¼��\n");
        return;
    }
    Node* current = head;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->data.employee_id, employee_id) == 0 &&
            current->data.month == month && current->data.year == year) {
            printf("\n--- ���ڸ���Ա�� %s (%d��%d��) �ļ�¼ ---\n", employee_id, year, month);
            printf("�����µĻ������� (��ǰ: %.2lf): ", current->data.base_salary);
            scanf("%lf", &current->data.base_salary);
            printf("�����µĽ��� (��ǰ: %.2lf): ", current->data.allowance);
            scanf("%lf", &current->data.allowance);
            printf("�����µĽ��� (��ǰ: %.2lf): ", current->data.bonus);
            scanf("%lf", &current->data.bonus);
            printf("�����µĿ۳��� (��ǰ: %.2lf): ", current->data.deductions);
            scanf("%lf", &current->data.deductions);

            current->data.total_salary = current->data.base_salary + current->data.allowance + current->data.bonus - current->data.deductions;
            printf("��¼���³ɹ���\n");
            found = 1;
            break;
        }
        current = current->next;
    }
    if (!found) {
        printf("δ�ҵ�Ա�� %s �� %d��%d�� �ļ�¼��\n", employee_id, year, month);
    }
}

// ɾ��Ա���ض��·ݵĹ��ʼ�¼
void deleteEmployeeRecord(char* employee_id, int month, int year) {
    if (head == NULL) {
        printf("û�п�ɾ���Ĺ��ʼ�¼��\n");
        return;
    }

    Node* current = head;
    Node* prev = NULL;
    int found = 0;

    // ���������ɾ��ͷ�ڵ�
    if (current != NULL && strcmp(current->data.employee_id, employee_id) == 0 &&
        current->data.month == month && current->data.year == year) {
        head = current->next; // ͷ�ڵ�ָ����һ���ڵ�
        free(current); // �ͷ�ԭͷ�ڵ��ڴ�
        printf("��¼ɾ���ɹ���\n");
        return;
    }

    // �����������Ҫɾ���Ľڵ�
    while (current != NULL && (strcmp(current->data.employee_id, employee_id) != 0 ||
        current->data.month != month || current->data.year != year)) {
        prev = current; // ��¼��ǰ�ڵ��ǰһ���ڵ�
        current = current->next; // �ƶ�����һ���ڵ�
    }

    // ��� current Ϊ�գ���ʾδ�ҵ�
    if (current == NULL) {
        printf("δ�ҵ�Ա�� %s �� %d��%d�� �ļ�¼��\n", employee_id, year, month);
        return;
    }

    // �ҵ��ڵ㣬����ɾ������
    prev->next = current->next; // ǰһ���ڵ��nextָ��ǰ�ڵ��next
    free(current); // �ͷŵ�ǰ�ڵ��ڴ�
    printf("��¼ɾ���ɹ���\n");
}

// �����ض�Ա����ͳ����Ϣ
void generateEmployeeStatistics(char* employee_id) {
    if (head == NULL) {
        printf("Ŀǰû�й��ʼ�¼��\n");
        return;
    }
    double total_salary_employee = 0.0;
    int found = 0;
    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->data.employee_id, employee_id) == 0) {
            total_salary_employee += current->data.total_salary;
            found = 1;
        }
        current = current->next;
    }
    if (found) {
        printf("\n--- Ա�����: %s ��ͳ����Ϣ ---\n", employee_id);
        printf("���м�¼�·ݵ��ܹ���: %.2lf\n", total_salary_employee);
    }
    else {
        printf("δ�ҵ�Ա�����: %s �ļ�¼��\n", employee_id);
    }
}

// �����ض��·ݵ�ͳ����Ϣ
void generateMonthlyStatistics(int month, int year) {
    if (head == NULL) {
        printf("Ŀǰû�й��ʼ�¼��\n");
        return;
    }
    double total_payroll_month = 0.0;
    int found = 0;
    Node* current = head;
    while (current != NULL) {
        if (current->data.month == month && current->data.year == year) {
            total_payroll_month += current->data.total_salary;
            found = 1;
        }
        current = current->next;
    }
    if (found) {
        printf("\n--- %d��%d�µ��¶�ͳ����Ϣ ---\n", year, month);
        printf("���µ��ܹ���֧��: %.2lf\n", total_payroll_month);
    }
    else {
        printf("δ�ҵ�%d��%d�µļ�¼��\n", year, month);
    }
}

// ��ʾ����Ա�����ʼ�¼
void displayAllRecords() {
    if (head == NULL) {
        printf("Ŀǰû�й��ʼ�¼��\n");
        return;
    }
    printf("\n--- ����Ա�����ʼ�¼ ---\n");
    Node* current = head;
    while (current != NULL) {
        printf("���: %s, ����: %s, �·�: %d/%d, ��������: %.2lf, ����: %.2lf, ����: %.2lf, �۳�: %.2lf, �ܹ���: %.2lf\n",
            current->data.employee_id, current->data.name, current->data.month, current->data.year,
            current->data.base_salary, current->data.allowance, current->data.bonus, current->data.deductions, current->data.total_salary);
        current = current->next;
    }
}

// �����ʼ�¼���浽�ļ�
void saveRecordsToFile(char* filename) {
    FILE* fp = fopen(filename, "wb"); // ʹ�� "wb" ���ж�����д��
    if (fp == NULL) {
        printf("���ļ� %s д��ʧ�ܣ�\n", filename);
        return;
    }
    Node* current = head;
    while (current != NULL) {
        fwrite(&(current->data), sizeof(Employee), 1, fp); // д��Employee�ṹ������
        current = current->next;
    }
    fclose(fp);
    printf("���ʼ�¼�ѳɹ����浽 %s��\n", filename);
}

// ���ļ����ع��ʼ�¼
void loadRecordsFromFile(char* filename) {
    FILE* fp = fopen(filename, "rb"); // ʹ�� "rb" ���ж����ƶ�ȡ
    if (fp == NULL) {
        printf("���ļ� %s ��ȡʧ�ܣ������ļ������ڡ����ӿռ�¼��ʼ��\n", filename);
        return;
    }

    // ����ǰ������м�¼�������ظ�
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL; // ȷ��ͷָ�����

    Employee emp_data;
    while (fread(&emp_data, sizeof(Employee), 1, fp) == 1) { // ѭ����ȡEmployee�ṹ������
        Node* newNode = createNode(emp_data);
        if (head == NULL) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    fclose(fp);
    printf("���ʼ�¼�ѳɹ��� %s ���أ�\n", filename);
}

// �ͷ����������нڵ���ڴ�
void freeLinkedList() {
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL; // ȷ��ͷָ�����
}

int main() {
    int choice;
    char emp_id[20];
    int month, year;
    char filename[] = "a.txt"; // Ĭ�����ڱ���/���ص��ļ���

    loadRecordsFromFile(filename); // ��������ʱ���Դ��ļ���������

    do {
        printf("\n--- ���ʹ���ϵͳ�˵� ---\n");
        printf("1. �����¼ (���Ա������)\n");
        printf("2. ��ѯ��¼ (���·ݻ�Ա�����)\n");
        printf("3. ����/ɾ����¼\n");
        printf("4. ͳ�� (��Ա�����·�)\n");
        printf("5. ������м�¼\n");
        printf("6. �����¼���ļ�\n");
        printf("7. ���ļ����ؼ�¼\n");
        printf("0. �˳�\n");
        printf("����������ѡ��: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addEmployeeRecord();
            break;
        case 2:
            printf("��ѯѡ��:\n");
            printf("  1. ��ʾ�ض��·ݵ����м�¼\n");
            printf("  2. ��ѯ�ض�Ա���ļ�¼\n");
            printf("�������ѯѡ��: ");
            int query_choice;
            scanf("%d", &query_choice);
            if (query_choice == 1) {
                printf("�������·� (1-12): ");
                scanf("%d", &month);
                printf("���������: ");
                scanf("%d", &year);
                displayAllRecordsByMonth(month, year);
            }
            else if (query_choice == 2) {
                printf("������Ҫ��ѯ��Ա�����: ");
                scanf("%s", emp_id);
                queryEmployeeRecords(emp_id);
            }
            else {
                printf("��Ч�Ĳ�ѯѡ�\n");
            }
            break;
        case 3:
            printf("����/ɾ��ѡ��:\n");
            printf("  1. ���¼�¼\n");
            printf("  2. ɾ����¼\n");
            printf("������ѡ��: ");
            int ud_choice;
            scanf("%d", &ud_choice);
            printf("������Ա�����: ");
            scanf("%s", emp_id);
            printf("�������·� (1-12): ");
            scanf("%d", &month);
            printf("���������: ");
            scanf("%d", &year);
            if (ud_choice == 1) {
                updateEmployeeRecord(emp_id, month, year);
            }
            else if (ud_choice == 2) {
                deleteEmployeeRecord(emp_id, month, year);
            }
            else {
                printf("��Ч��ѡ�\n");
            }
            break;
        case 4:
            printf("ͳ��ѡ��:\n");
            printf("  1. �����ض�Ա����ͳ����Ϣ\n");
            printf("  2. �����¶�ͳ����Ϣ\n");
            printf("������ͳ��ѡ��: ");
            int stats_choice;
            scanf("%d", &stats_choice);
            if (stats_choice == 1) {
                printf("������Ҫͳ�Ƶ�Ա�����: ");
                scanf("%s", emp_id);
                generateEmployeeStatistics(emp_id);
            }
            else if (stats_choice == 2) {
                printf("������Ҫͳ�Ƶ��·� (1-12): ");
                scanf("%d", &month);
                printf("���������: ");
                scanf("%d", &year);
                generateMonthlyStatistics(month, year);
            }
            else {
                printf("��Ч��ͳ��ѡ�\n");
            }
            break;
        case 5:
            displayAllRecords();
            break;
        case 6:
            saveRecordsToFile(filename);
            break;
        case 7:
            loadRecordsFromFile(filename);
            break;
        case 0:
            printf("�����˳����ʹ���ϵͳ���ټ���\n");
            break;
        default:
            printf("��Ч��ѡ�������ԡ�\n");
        }
    } while (choice != 0);

    freeLinkedList(); // �����˳�ǰ�ͷ����з�����ڴ�
    return 0;
}