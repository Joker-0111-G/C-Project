#define _CRT_SECURE_NO_WARNINGS
#include "Operation.h"
#include <cassert>
#include <malloc.h>
#include <stdio.h>
#include <string.h>




//Medince ҩƷ����

//��ʼ��ҩƷ����
void MInit(med* pmarr) {
	pmarr->pmeds = (medince*)malloc(MEDINCE * sizeof(medince));
	assert(pmarr->pmeds != NULL);
	if (pmarr->pmeds == NULL) {
		return;
	}
	pmarr->medcapacity = MEDINCE;
	pmarr->m_size = 0;//��Ч������0
	//printf("��ʼ������ɹ�\n");
	File_read_med(pmarr, "medince.txt");
}

//��̬�ڴ�����
void Grow(med* pmarr) {
	medince* p = (medince*)realloc(pmarr->pmeds, 2 * pmarr->medcapacity * sizeof(medince));
	assert(p != NULL);
	if (p == NULL) {
		free(pmarr->pmeds);
		pmarr->pmeds = NULL;
		return;
	}
	pmarr->pmeds = p;
	pmarr->medcapacity *= 2;
}

//ͨ�����Ʋ�ѯҩƷ
static medince* searchmedbyname(med* pmarr, const char name[]) {
	for (int i = 0; i < pmarr->m_size; i++) {
		if (strcmp(pmarr->pmeds[i].m_name, name)==0)
			return &pmarr->pmeds[i];
	}
	return NULL;
}

//���ҩƷ 
void add_med(med* pmarr) {
	if (pmarr->m_size == pmarr->medcapacity) Grow(pmarr);
	char name[20];
	char manufacture[20];
	//�����Ҫ�����ҩƷ�����ƺ���������֮ǰ���ڲ���ͬ��ֱ���ڿ��������
	printf("������ҩƷ���ƣ�");
	scanf("%s", &name);
	printf("������ҩƷ�������ڣ�");
	scanf("%s", &manufacture);
	if ((searchmedbyname(pmarr, name) != NULL) &&
		strcmp(searchmedbyname(pmarr, name)->m_manufacture , manufacture) ==0){
		searchmedbyname(pmarr, name)->m_inventory++;
		printf("��ǰҩƷ�Ѵ��ڣ�������������ͬ�����ڿ�������ӡ�\n");
	}

	else {
		strcpy(pmarr->pmeds[pmarr->m_size].m_name, name);
		strcpy(pmarr->pmeds[pmarr->m_size].m_manufacture, manufacture);

		float price;
		printf("������ҩƷ���ۣ�");
		scanf("%f", &price);
		pmarr->pmeds[pmarr->m_size].m_price = price;

		int inventory;
		printf("������ҩƷ�������");
		scanf("%d", &inventory);
		pmarr->pmeds[pmarr->m_size].m_inventory = inventory;

		char brand[20];
		printf("������ҩƷƷ�ƣ�");
		/*fgets(brand, sizeof(brand), stdin);
		size_t len = strlen(brand);
		if (len > 0 && brand[len - 1] == '\n') brand[len - 1] = '\0';*/
		scanf("%s", &brand);
		strcpy(pmarr->pmeds[pmarr->m_size].m_brand, brand);

		char introduction[50];
		printf("������ҩƷ��飺");
		scanf("%s", &introduction);
		//fgets(introduction, sizeof(introduction), stdin);
		//size_t len_2 = strlen(introduction);
		//if (len_2 > 0 && introduction[len_2 - 1] == '\n') introduction[len_2 - 1] = '0';
		strcpy(pmarr->pmeds[pmarr->m_size].m_introduction, introduction);

		pmarr->m_size++;
		printf("ҩƷ��ӳɹ����������һ������\n");
	}
	File_write_med(pmarr, "medince.txt");

}

//��ѯҩƷ
 // ͨ������
void search_med_byname(med* pmarr) {
	char name[20];
	printf("������ҩƷ���ƣ�");
	scanf("%s", &name);
	if (searchmedbyname(pmarr, name) != NULL) {
		//��ӡ��ѯ����ҩƷ��Ϣ
		printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "ҩƷ����", "ҩƷ����", "ҩƷƷ��", "ҩƷ��������", "ҩƷ�����", "ҩƷ���");
		printf("%-15s%-15f%-15s%-15s%-15d%-15s\n", searchmedbyname(pmarr, name)->m_name,
			searchmedbyname(pmarr, name)->m_price, searchmedbyname(pmarr, name)->m_brand, searchmedbyname(pmarr, name)->m_manufacture,
			searchmedbyname(pmarr, name)->m_inventory, searchmedbyname(pmarr, name)->m_introduction);
	}
	else
		printf("��ǰҩƷ�����ڣ������½�����ز�����");
}

//ͨ��ʱ��
void search_med_bytime(med* pmarr) {
	char manufacture[20];
	printf("������ҩƷ�������ڣ�");
	scanf("%s", &manufacture);
	int time = (manufacture[0]-'0') * 1000 + (manufacture[1] - '0') * 100 + (manufacture[2] - '0') * 10 +( manufacture[3] - '0');
	printf("�������%d��֮ǰ������ҩƷ\n", time);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "ҩƷ����", "ҩƷ����", "ҩƷƷ��", "ҩƷ��������", "ҩƷ�����", "ҩƷ���");
	int k = 0;
	for (int i = 0; i < pmarr->m_size; i++) {
		int time2 = (pmarr->pmeds[i].m_manufacture[0] - '0') * 1000 + (pmarr->pmeds[i].m_manufacture[1] - '0') * 100
			+ (pmarr->pmeds[i].m_manufacture[2] - '0') * 10 + (pmarr->pmeds[i].m_manufacture[3] - '0');
		if (time2 < time) {
			k = 1;
			
			printf("%-15s%-15f%-15s%-15s%-15d%-15s\n", pmarr->pmeds[i].m_name, pmarr->pmeds[i].m_price,
				pmarr->pmeds[i].m_brand, pmarr->pmeds[i].m_manufacture, pmarr->pmeds[i].m_inventory, pmarr->pmeds[i].m_introduction);
		}
	}
	if (k == 0) {
		printf("��Ǹδ��ѯ�����ҩƷ\n");
	}
}


//����ҩƷ 
 // �޸�ҩƷ��Ϣ
void revise_update_med(med* pmarr) {
	char name[20];
	printf("������ҩƷ���ƣ�");
	scanf("%s", &name);
	if (searchmedbyname(pmarr, name) != NULL) {
		printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "ҩƷ����", "ҩƷ����", "ҩƷƷ��", "ҩƷ��������", "ҩƷ�����", "ҩƷ���");
		printf("%-15s%-15f%-15s%-15s%-15d%-15s\n", searchmedbyname(pmarr, name)->m_name,
			searchmedbyname(pmarr, name)->m_price, searchmedbyname(pmarr, name)->m_brand, searchmedbyname(pmarr, name)->m_manufacture,
			searchmedbyname(pmarr, name)->m_inventory, searchmedbyname(pmarr, name)->m_introduction);
		/*printf("������ҩƷ���ƣ�");
		scanf("%s", &searchmedbyname(pmarr, name)->m_name);
		printf("������ҩƷ�������ڣ�");
		scanf("%s", &searchmedbyname(pmarr, name)->m_manufacture);
		printf("������ҩƷ���ۣ�");
		scanf("%f", &searchmedbyname(pmarr, name)->m_price);
		printf("������ҩƷ�������");
		scanf("%d", &searchmedbyname(pmarr, name)->m_inventory);
		printf("������ҩƷƷ�ƣ�");
		scanf("%s", &searchmedbyname(pmarr, name)->m_brand);
		printf("������ҩƷ��飺");
		scanf("%s", &searchmedbyname(pmarr, name)->m_introduction);*/

		char name[20];
		char manufacture[20];
		printf("������ҩƷ���ƣ�");
		scanf("%s", &name);
		printf("������ҩƷ�������ڣ�");
		scanf("%s", &manufacture);

		strcpy(searchmedbyname(pmarr, name)->m_name, name);
		strcpy(searchmedbyname(pmarr, name)->m_manufacture, manufacture);

		float price;
		printf("������ҩƷ���ۣ�");
		scanf("%f", &price);
		searchmedbyname(pmarr, name)->m_price = price;

		int inventory;
		printf("������ҩƷ�������");
		scanf("%d", &inventory);
		searchmedbyname(pmarr, name)->m_inventory = inventory;

		char brand[20];
		printf("������ҩƷƷ�ƣ�");
		//fgets(brand, sizeof(brand), stdin);
		//size_t len = strlen(brand);
		//if (len > 0 && brand[len - 1] == '\n') brand[len - 1] = '\0';
		scanf("%s", &brand);
		strcpy(searchmedbyname(pmarr, name)->m_brand, brand);

		char introduction[50];
		printf("������ҩƷ��飺");
		scanf("%s", &introduction);
		/*fgets(introduction, sizeof(introduction), stdin);
		size_t len_2 = strlen(introduction);
		if (len_2 > 0 && introduction[len_2 - 1] == '\n') introduction[len_2 - 1] = '\0';*/
		strcpy(searchmedbyname(pmarr, name)->m_introduction, introduction);


	}
	else
		printf("��ǰҩƷ�����ڣ������½�����ز�����");


	File_write_med(pmarr, "medince.txt");
}

//��ҩƷ
void sell_update_med(med* pmarr) {
	char name[20];
	printf("������ҩƷ���ƣ�");
	scanf("%s", &name);
	int k = 0;
	for (int i = 0; i < pmarr->m_size; i++) {
		medince* pcm = &pmarr->pmeds[i];
		if (strcmp(pmarr->pmeds[i].m_name, name) == 0) {
			if (pmarr->pmeds[i].m_inventory == 1) {
				int n = pmarr->m_size - i + 1;
				memmove(pcm, pcm + 1, n * sizeof(medince));
				pmarr->m_size--;
			}
			else pmarr->pmeds[i].m_inventory--;
			k = 1;
		}
	}
	if(k==0)
		printf("��ǰҩƷ�����ڣ������½�����ز�����");
	File_write_med(pmarr, "medince.txt");

}


// ͳ�Ƽ۸�����ͳ�ƴ���30ԪҩƷ��
void statistics_med(med* pmarr) {
	float price = 0;
	printf("������۸�");
	scanf("%f", &price);
	printf("�������%f�۸�֮�ϵ�ҩƷ\n");
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "ҩƷ����", "ҩƷ����", "ҩƷƷ��", "ҩƷ��������", "ҩƷ�����", "ҩƷ���");
	int k = 0;
	for (int i = 0; i < pmarr->m_size; i++) {
		
		if (pmarr->pmeds[i].m_price>price) {
			printf("%-15s%-15f%-15s%-15s%-15d%-15s\n", pmarr->pmeds[i].m_name, pmarr->pmeds[i].m_price,
				pmarr->pmeds[i].m_brand, pmarr->pmeds[i].m_manufacture, pmarr->pmeds[i].m_inventory, pmarr->pmeds[i].m_introduction);
			k = 1;
		}
	}
	if (k == 0) {
		printf("δ�ҵ��۸����30��ҩƷ\n");
	}


}

//��ʾҩƷ��Ϣ
void show_med(med* pmarr) {
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "ҩƷ����", "ҩƷ����", "ҩƷƷ��", "ҩƷ��������", "ҩƷ�����", "ҩƷ���");
	for (int i = 0; i < pmarr->m_size; i++) {
		printf("%-15s%-15f%-15s%-15s%-15d%-15s\n", pmarr->pmeds[i].m_name, pmarr->pmeds[i].m_price, 
			pmarr->pmeds[i].m_brand, pmarr->pmeds[i].m_manufacture, pmarr->pmeds[i].m_inventory, pmarr->pmeds[i].m_introduction);
	}
}




