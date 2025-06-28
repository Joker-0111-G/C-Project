#define _CRT_SECURE_NO_WARNINGS
#include "Operation.h"
#include <cassert>
#include <malloc.h>
#include <stdio.h>
#include <string.h>




//Medince 药品操作

//初始化药品数组
void MInit(med* pmarr) {
	pmarr->pmeds = (medince*)malloc(MEDINCE * sizeof(medince));
	assert(pmarr->pmeds != NULL);
	if (pmarr->pmeds == NULL) {
		return;
	}
	pmarr->medcapacity = MEDINCE;
	pmarr->m_size = 0;//有效卡数量0
	//printf("初始化数组成功\n");
	File_read_med(pmarr, "medince.txt");
}

//动态内存扩容
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

//通过名称查询药品
static medince* searchmedbyname(med* pmarr, const char name[]) {
	for (int i = 0; i < pmarr->m_size; i++) {
		if (strcmp(pmarr->pmeds[i].m_name, name)==0)
			return &pmarr->pmeds[i];
	}
	return NULL;
}

//添加药品 
void add_med(med* pmarr) {
	if (pmarr->m_size == pmarr->medcapacity) Grow(pmarr);
	char name[20];
	char manufacture[20];
	//如果将要输入的药品，名称和生产日期之前存在并相同，直接在库存量增加
	printf("请输入药品名称：");
	scanf("%s", &name);
	printf("请输入药品生产日期：");
	scanf("%s", &manufacture);
	if ((searchmedbyname(pmarr, name) != NULL) &&
		strcmp(searchmedbyname(pmarr, name)->m_manufacture , manufacture) ==0){
		searchmedbyname(pmarr, name)->m_inventory++;
		printf("当前药品已存在，且生产日期相同，已在库存量增加。\n");
	}

	else {
		strcpy(pmarr->pmeds[pmarr->m_size].m_name, name);
		strcpy(pmarr->pmeds[pmarr->m_size].m_manufacture, manufacture);

		float price;
		printf("请输入药品单价：");
		scanf("%f", &price);
		pmarr->pmeds[pmarr->m_size].m_price = price;

		int inventory;
		printf("请输入药品库存量：");
		scanf("%d", &inventory);
		pmarr->pmeds[pmarr->m_size].m_inventory = inventory;

		char brand[20];
		printf("请输入药品品牌：");
		/*fgets(brand, sizeof(brand), stdin);
		size_t len = strlen(brand);
		if (len > 0 && brand[len - 1] == '\n') brand[len - 1] = '\0';*/
		scanf("%s", &brand);
		strcpy(pmarr->pmeds[pmarr->m_size].m_brand, brand);

		char introduction[50];
		printf("请输入药品简介：");
		scanf("%s", &introduction);
		//fgets(introduction, sizeof(introduction), stdin);
		//size_t len_2 = strlen(introduction);
		//if (len_2 > 0 && introduction[len_2 - 1] == '\n') introduction[len_2 - 1] = '0';
		strcpy(pmarr->pmeds[pmarr->m_size].m_introduction, introduction);

		pmarr->m_size++;
		printf("药品添加成功，请进下下一步操作\n");
	}
	File_write_med(pmarr, "medince.txt");

}

//查询药品
 // 通过名称
void search_med_byname(med* pmarr) {
	char name[20];
	printf("请输入药品名称：");
	scanf("%s", &name);
	if (searchmedbyname(pmarr, name) != NULL) {
		//打印查询到的药品信息
		printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "药品名称", "药品单价", "药品品牌", "药品生产日期", "药品库存量", "药品简介");
		printf("%-15s%-15f%-15s%-15s%-15d%-15s\n", searchmedbyname(pmarr, name)->m_name,
			searchmedbyname(pmarr, name)->m_price, searchmedbyname(pmarr, name)->m_brand, searchmedbyname(pmarr, name)->m_manufacture,
			searchmedbyname(pmarr, name)->m_inventory, searchmedbyname(pmarr, name)->m_introduction);
	}
	else
		printf("当前药品不存在，请重新进行相关操作！");
}

//通过时间
void search_med_bytime(med* pmarr) {
	char manufacture[20];
	printf("请输入药品生产日期：");
	scanf("%s", &manufacture);
	int time = (manufacture[0]-'0') * 1000 + (manufacture[1] - '0') * 100 + (manufacture[2] - '0') * 10 +( manufacture[3] - '0');
	printf("将会查找%d年之前生产的药品\n", time);
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "药品名称", "药品单价", "药品品牌", "药品生产日期", "药品库存量", "药品简介");
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
		printf("抱歉未查询到相关药品\n");
	}
}


//更新药品 
 // 修改药品信息
void revise_update_med(med* pmarr) {
	char name[20];
	printf("请输入药品名称：");
	scanf("%s", &name);
	if (searchmedbyname(pmarr, name) != NULL) {
		printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "药品名称", "药品单价", "药品品牌", "药品生产日期", "药品库存量", "药品简介");
		printf("%-15s%-15f%-15s%-15s%-15d%-15s\n", searchmedbyname(pmarr, name)->m_name,
			searchmedbyname(pmarr, name)->m_price, searchmedbyname(pmarr, name)->m_brand, searchmedbyname(pmarr, name)->m_manufacture,
			searchmedbyname(pmarr, name)->m_inventory, searchmedbyname(pmarr, name)->m_introduction);
		/*printf("请输入药品名称：");
		scanf("%s", &searchmedbyname(pmarr, name)->m_name);
		printf("请输入药品生产日期：");
		scanf("%s", &searchmedbyname(pmarr, name)->m_manufacture);
		printf("请输入药品单价：");
		scanf("%f", &searchmedbyname(pmarr, name)->m_price);
		printf("请输入药品库存量：");
		scanf("%d", &searchmedbyname(pmarr, name)->m_inventory);
		printf("请输入药品品牌：");
		scanf("%s", &searchmedbyname(pmarr, name)->m_brand);
		printf("请输入药品简介：");
		scanf("%s", &searchmedbyname(pmarr, name)->m_introduction);*/

		char name[20];
		char manufacture[20];
		printf("请输入药品名称：");
		scanf("%s", &name);
		printf("请输入药品生产日期：");
		scanf("%s", &manufacture);

		strcpy(searchmedbyname(pmarr, name)->m_name, name);
		strcpy(searchmedbyname(pmarr, name)->m_manufacture, manufacture);

		float price;
		printf("请输入药品单价：");
		scanf("%f", &price);
		searchmedbyname(pmarr, name)->m_price = price;

		int inventory;
		printf("请输入药品库存量：");
		scanf("%d", &inventory);
		searchmedbyname(pmarr, name)->m_inventory = inventory;

		char brand[20];
		printf("请输入药品品牌：");
		//fgets(brand, sizeof(brand), stdin);
		//size_t len = strlen(brand);
		//if (len > 0 && brand[len - 1] == '\n') brand[len - 1] = '\0';
		scanf("%s", &brand);
		strcpy(searchmedbyname(pmarr, name)->m_brand, brand);

		char introduction[50];
		printf("请输入药品简介：");
		scanf("%s", &introduction);
		/*fgets(introduction, sizeof(introduction), stdin);
		size_t len_2 = strlen(introduction);
		if (len_2 > 0 && introduction[len_2 - 1] == '\n') introduction[len_2 - 1] = '\0';*/
		strcpy(searchmedbyname(pmarr, name)->m_introduction, introduction);


	}
	else
		printf("当前药品不存在，请重新进行相关操作！");


	File_write_med(pmarr, "medince.txt");
}

//卖药品
void sell_update_med(med* pmarr) {
	char name[20];
	printf("请输入药品名称：");
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
		printf("当前药品不存在，请重新进行相关操作！");
	File_write_med(pmarr, "medince.txt");

}


// 统计价格（例如统计大于30元药品）
void statistics_med(med* pmarr) {
	float price = 0;
	printf("请输入价格：");
	scanf("%f", &price);
	printf("将会输出%f价格之上的药品\n");
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "药品名称", "药品单价", "药品品牌", "药品生产日期", "药品库存量", "药品简介");
	int k = 0;
	for (int i = 0; i < pmarr->m_size; i++) {
		
		if (pmarr->pmeds[i].m_price>price) {
			printf("%-15s%-15f%-15s%-15s%-15d%-15s\n", pmarr->pmeds[i].m_name, pmarr->pmeds[i].m_price,
				pmarr->pmeds[i].m_brand, pmarr->pmeds[i].m_manufacture, pmarr->pmeds[i].m_inventory, pmarr->pmeds[i].m_introduction);
			k = 1;
		}
	}
	if (k == 0) {
		printf("未找到价格大于30的药品\n");
	}


}

//显示药品信息
void show_med(med* pmarr) {
	printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "药品名称", "药品单价", "药品品牌", "药品生产日期", "药品库存量", "药品简介");
	for (int i = 0; i < pmarr->m_size; i++) {
		printf("%-15s%-15f%-15s%-15s%-15d%-15s\n", pmarr->pmeds[i].m_name, pmarr->pmeds[i].m_price, 
			pmarr->pmeds[i].m_brand, pmarr->pmeds[i].m_manufacture, pmarr->pmeds[i].m_inventory, pmarr->pmeds[i].m_introduction);
	}
}




