#define _CRT_SECURE_NO_WARNINGS
#include "Operation.h"
#include <cassert>
#include <stdio.h>


// File �ļ����� 

//ҩƷ�ļ�����
void File_read_med(med* pmarr, const char* filepath) {
	assert(pmarr && filepath);
	FILE* fp = fopen(filepath, "r");
	if (fp == NULL) {
		fp = fopen(filepath, "w");
		if (fp == NULL) {
			printf("�ļ���дģʽ��ʧ��\n");
			fclose(fp);
			return;
		}
	}
	int i = 0;
	medince* pc;
	while (1) {
		pc = &pmarr->pmeds[i];
		if (fscanf(fp, "%f,%d,%[^,],%[^,],%[^,],%[^\n]\n", &pc->m_price, &pc->m_inventory,
			&pc->m_name, &pc->m_brand, &pc->m_manufacture, &pc->m_introduction) == 6) {
			i++;
			pmarr->m_size++;
		}
		else break;
		if (pmarr->m_size == pmarr->medcapacity) Grow(pmarr);
	}
	
	fclose(fp);
}

//ҩƷ�ļ�д��
void File_write_med(med* pmarr, const char* filepath) {
	assert(pmarr && filepath);
	FILE* fp = fopen(filepath, "w");
	if (fp == NULL) {
		printf("�ļ���д��ʽ��ʧ��\n");
		return;
	}
	for (int i = 0; i < pmarr->m_size; i++) {
		
		medince *pc= &pmarr->pmeds[i];
		fprintf(fp, "%f,%d,%s,%s,%s,%s\n", pc->m_price, pc->m_inventory,
			pc->m_name, pc->m_brand, pc->m_manufacture, pc->m_introduction);
		

	}
	fclose(fp);
}

//����Ա�ļ�����
void File_read_adm(adm* paarr, const char* filepath) {
	assert(paarr && filepath);
	FILE* fp = fopen(filepath, "r");
	if (fp == NULL) {
		fp = fopen(filepath, "w");
		if (fp == NULL) {
			printf("�ļ���дģʽ��ʧ��\n");
			fclose(fp);
			return;
		}
	}
	int i = 0;
	administrator* pc;                                                                                                                                                                                                                       
	while (1) {   //��ȡ���ļ�ĩβ   feof(fp)!= EOF
		pc = &paarr->a_arr[i];
		if (fscanf(fp, "%d %s %d\n", &pc->a_num, &pc->a_name, &pc->a_passwd) == 3) {
			i++;
			paarr->a_size++;
		}
		else break;
	}
	fclose(fp);
}

//����Ա�ļ�д��
void File_write_adm(adm* paarr, const char* filepath){
	assert(paarr && filepath);
	FILE* fp = fopen(filepath, "w");
	if (fp == NULL) {
		printf("�ļ���д��ʽ��ʧ��\n");
		return;
	}
	for (int i = 0; i < paarr->a_size; i++) {
		//fwrite(&paarr->a_arr[i], sizeof(administrator), 1, fp);
		fprintf(fp, "%d %s %d\n", paarr->a_arr[i].a_num, paarr->a_arr[i].a_name, paarr->a_arr[i].a_passwd);
		
	}
	fclose(fp);
}