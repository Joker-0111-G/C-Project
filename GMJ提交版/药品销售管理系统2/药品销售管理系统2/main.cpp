#define _CRT_SECURE_NO_WARNINGS
#include "Operation.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void show1() {
	printf("******************************************\n");
	printf("*********��ӭ����ҩƷ���۹���ϵͳ*********\n");
	printf("* 1.����Աע��                           *\n");
	printf("* 2.����Ա��¼                           *\n");
	printf("* 3.����Աע��                           *\n");
	printf("* 4.����Ա�������                       *\n");
	printf("* 5.�˳�                                 *\n");
	printf("******************************************\n");

}   //��¼ǰҳ��չʾ

static void Clear() {
	//Sleep(3000);
	system("pause");
	system("cls");
}


int main() {

	int a = 0, b = 0;

	adm paarr[1];
	med pmarr[1];


	//��ʼ��Administrator����
	AInit(paarr);

	//��ʼ��ҩƷ����
	MInit(pmarr);

	int num, passwd, newpasswd;
	char name;
	
	while (1) {
		show1();   //��¼ǰҳ��չʾ
		printf("������������еĲ�����1,2,3,4,5����");
		int n = 0;
		scanf("%d", &n);

		switch (n) {
		case 1:
			printf("�������ţ�");
			scanf("%d", &num);
			printf("������������");
			scanf("%s", &name);
			printf("���������룺");
			scanf("%d", &passwd);
			enroll(paarr,num,&name,passwd );
			Clear();
			break;
		case 2:
			printf("�������ţ�");
			scanf("%d", &num);
			printf("���������룺");
			scanf("%d", &passwd);
			login(paarr,num, passwd,pmarr);
			Clear();
			break;
		case 3:
			printf("�������ţ�");
			scanf("%d", &num);
			printf("������������");
			scanf("%s", &name);
			printf("���������룺");
			scanf("%d", &passwd);
			logout(paarr,num,&name, passwd);
			Clear();
			break;
		case 4:
			printf("�������ţ�");
			scanf("%d", &num);
			printf("������������");
			scanf("%s", &name);
			printf("���������룺");
			scanf("%d", &passwd);
			printf("�����������룺");
			scanf("%d", &newpasswd);
			change_password(paarr,num,&name, passwd,newpasswd);
			Clear();
			break;
		case 5:
			return 0;
		default:
			printf("����������������еĲ�����\n");
			Clear();
			//show1();   //��¼ǰҳ��չʾ
		}
	}


	return 0;
}

void show2() {
	printf("******************************************\n");
	printf("*********��ӭ����ҩƷ���۹���ϵͳ*********\n");
	printf("* 1.���ҩƷ                             *\n");
	printf("* 2.�����Ʋ�ҩƷ                         *\n");
	printf("* 3.����ݲ�ҩƷ                         *\n");
	printf("* 4.�޸�ҩƷ��Ϣ                         *\n");
	printf("* 5.��ҩƷ                               *\n");
	printf("* 6.ͳ�Ƽ۸����30��ҩƷ                 *\n");
	printf("* 7.��ʾ����ҩ                           *\n");
	printf("* 8.�˳�ϵͳ                             *\n");
	printf("******************************************\n");
}//ҩƷ����Ŀ¼��ʾ

void OPIN(med *pmarr) {

	while (1) {
		show2();   //ҩƷ����Ŀ¼��ʾ
		printf("������������еĲ�����1,2,3,4,5,6,7����");
		int n = 0;
		scanf("%d", &n);
		switch (n) {
		case 1:
			add_med(pmarr);//���ҩƷ 
			Clear();
			break;
		case 2:
			search_med_byname( pmarr);// ͨ������
			Clear();
			break;
		case 3:
			search_med_bytime(pmarr);//ͨ��ʱ��
			Clear();
			break;
		case 4:
			revise_update_med(pmarr);  // �޸�ҩƷ��Ϣ
			Clear();
			break;
		case 5:
			sell_update_med(pmarr); //��ҩƷ
			Clear();
			break;
		case 6:
			statistics_med(pmarr);
			Clear();
			break;
		case 7:
			show_med(pmarr);
			Clear();
			break;
		case 8:
			return ;
			Clear();
		default:
			printf("����������������еĲ�����\n");
			Clear();
			//show2();   //��¼ǰҳ��չʾ
		}
	}
}
