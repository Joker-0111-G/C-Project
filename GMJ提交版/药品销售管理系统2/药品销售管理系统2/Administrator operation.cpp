#define _CRT_SECURE_NO_WARNINGS
#include "Operation.h"
#include <cassert>
#include <stdio.h>
#include <string.h>

//初始化Administrator
void AInit(adm* paarr) {
	assert(paarr != NULL);
	paarr->a_size = 0;
	File_read_adm( paarr, "administrator.txt");
}

//注册
void enroll(adm* paarr, int num, const char *name, int passwd) {
	if (paarr->a_size == ADMSIZE) {
		printf("管理员岗位已满，注册失败！\n");
		return;
	}
	else {
		paarr->a_arr[paarr->a_size ].a_num = num;
		strcpy(paarr->a_arr[paarr->a_size ].a_name , name);
		paarr->a_arr[paarr->a_size ].a_passwd = passwd;
		paarr->a_size++;
		printf("注册成功\n");
	}
	File_write_adm(paarr, "administrator.txt");
	
}

//登录
void login(adm* paarr, int num, int passwd,med *pmarr) {
	int k = 0;
	for (int i = 0; i < paarr->a_size; i++) {
		if ((paarr->a_arr[i].a_num == num)
			&& (paarr->a_arr[i].a_passwd == passwd)) {
			printf("登陆成功\n");
			printf("进入药品销售管理系统！\n");
			OPIN(pmarr);
			k = 1;

		}
	}if (k == 0) printf("登录失败\n");
	
}

//注销
void logout(adm* paarr, int num, const char* name, int passwd) {
	int k = 0;
	for (int i = 0; i < paarr->a_size; i++) {
		administrator* pca =& paarr->a_arr[i];
		if ((paarr->a_arr[i].a_num == num) && !strcmp(paarr->a_arr[i].a_name, name) 
			&& (paarr->a_arr[i].a_passwd == passwd)) {
			int n = paarr->a_size - i - 1;
			
			memmove(pca, pca + 1, n * sizeof(administrator));
			//memset(&(paarr->a_arr[paarr->a_size]), NULL, sizeof(administrator));
			
			printf("注销成功\n");
			paarr->a_size--;
			k = 1;
			//return;
			
		}
	}
	if (k == 0) {
		printf("注销失败，当前用户不存在或密码不正确\n");
	}
	File_write_adm(paarr,"administrator.txt");
}

//更改密码
void change_password(adm* paarr, int num, const char* name, int passwd,int newpasswd) {
	int k = 0;
	for (int i = 0; i < paarr->a_size; i++) {
		//administrator* pcm = &paarr->a_arr[i];
		if ((paarr->a_arr[i].a_num == num) && !strcmp(paarr->a_arr[i].a_name, name)
			&& (paarr->a_arr->a_passwd == passwd)) {
			paarr->a_arr[i].a_passwd = newpasswd;
			printf("更改成功\n");
			k = 1;
			//return ;
			
		}
	}
	if (k == 0) {
		printf("更改失败，当前用户不存在或密码不正确\n");
	}
	File_write_adm(paarr, "administrator.txt");
}

