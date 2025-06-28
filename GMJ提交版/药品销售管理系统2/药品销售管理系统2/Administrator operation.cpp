#define _CRT_SECURE_NO_WARNINGS
#include "Operation.h"
#include <cassert>
#include <stdio.h>
#include <string.h>

//��ʼ��Administrator
void AInit(adm* paarr) {
	assert(paarr != NULL);
	paarr->a_size = 0;
	File_read_adm( paarr, "administrator.txt");
}

//ע��
void enroll(adm* paarr, int num, const char *name, int passwd) {
	if (paarr->a_size == ADMSIZE) {
		printf("����Ա��λ������ע��ʧ�ܣ�\n");
		return;
	}
	else {
		paarr->a_arr[paarr->a_size ].a_num = num;
		strcpy(paarr->a_arr[paarr->a_size ].a_name , name);
		paarr->a_arr[paarr->a_size ].a_passwd = passwd;
		paarr->a_size++;
		printf("ע��ɹ�\n");
	}
	File_write_adm(paarr, "administrator.txt");
	
}

//��¼
void login(adm* paarr, int num, int passwd,med *pmarr) {
	int k = 0;
	for (int i = 0; i < paarr->a_size; i++) {
		if ((paarr->a_arr[i].a_num == num)
			&& (paarr->a_arr[i].a_passwd == passwd)) {
			printf("��½�ɹ�\n");
			printf("����ҩƷ���۹���ϵͳ��\n");
			OPIN(pmarr);
			k = 1;

		}
	}if (k == 0) printf("��¼ʧ��\n");
	
}

//ע��
void logout(adm* paarr, int num, const char* name, int passwd) {
	int k = 0;
	for (int i = 0; i < paarr->a_size; i++) {
		administrator* pca =& paarr->a_arr[i];
		if ((paarr->a_arr[i].a_num == num) && !strcmp(paarr->a_arr[i].a_name, name) 
			&& (paarr->a_arr[i].a_passwd == passwd)) {
			int n = paarr->a_size - i - 1;
			
			memmove(pca, pca + 1, n * sizeof(administrator));
			//memset(&(paarr->a_arr[paarr->a_size]), NULL, sizeof(administrator));
			
			printf("ע���ɹ�\n");
			paarr->a_size--;
			k = 1;
			//return;
			
		}
	}
	if (k == 0) {
		printf("ע��ʧ�ܣ���ǰ�û������ڻ����벻��ȷ\n");
	}
	File_write_adm(paarr,"administrator.txt");
}

//��������
void change_password(adm* paarr, int num, const char* name, int passwd,int newpasswd) {
	int k = 0;
	for (int i = 0; i < paarr->a_size; i++) {
		//administrator* pcm = &paarr->a_arr[i];
		if ((paarr->a_arr[i].a_num == num) && !strcmp(paarr->a_arr[i].a_name, name)
			&& (paarr->a_arr->a_passwd == passwd)) {
			paarr->a_arr[i].a_passwd = newpasswd;
			printf("���ĳɹ�\n");
			k = 1;
			//return ;
			
		}
	}
	if (k == 0) {
		printf("����ʧ�ܣ���ǰ�û������ڻ����벻��ȷ\n");
	}
	File_write_adm(paarr, "administrator.txt");
}

