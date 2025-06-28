#define _CRT_SECURE_NO_WARNINGS
#include "Operation.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void show1() {
	printf("******************************************\n");
	printf("*********欢迎来到药品销售管理系统*********\n");
	printf("* 1.管理员注册                           *\n");
	printf("* 2.管理员登录                           *\n");
	printf("* 3.管理员注销                           *\n");
	printf("* 4.管理员密码更改                       *\n");
	printf("* 5.退出                                 *\n");
	printf("******************************************\n");

}   //登录前页面展示

static void Clear() {
	//Sleep(3000);
	system("pause");
	system("cls");
}


int main() {

	int a = 0, b = 0;

	adm paarr[1];
	med pmarr[1];


	//初始化Administrator数组
	AInit(paarr);

	//初始化药品数组
	MInit(pmarr);

	int num, passwd, newpasswd;
	char name;
	
	while (1) {
		show1();   //登录前页面展示
		printf("请输入你想进行的操作（1,2,3,4,5）：");
		int n = 0;
		scanf("%d", &n);

		switch (n) {
		case 1:
			printf("请输入编号：");
			scanf("%d", &num);
			printf("请输入姓名：");
			scanf("%s", &name);
			printf("请输入密码：");
			scanf("%d", &passwd);
			enroll(paarr,num,&name,passwd );
			Clear();
			break;
		case 2:
			printf("请输入编号：");
			scanf("%d", &num);
			printf("请输入密码：");
			scanf("%d", &passwd);
			login(paarr,num, passwd,pmarr);
			Clear();
			break;
		case 3:
			printf("请输入编号：");
			scanf("%d", &num);
			printf("请输入姓名：");
			scanf("%s", &name);
			printf("请输入密码：");
			scanf("%d", &passwd);
			logout(paarr,num,&name, passwd);
			Clear();
			break;
		case 4:
			printf("请输入编号：");
			scanf("%d", &num);
			printf("请输入姓名：");
			scanf("%s", &name);
			printf("请输入密码：");
			scanf("%d", &passwd);
			printf("请输入新密码：");
			scanf("%d", &newpasswd);
			change_password(paarr,num,&name, passwd,newpasswd);
			Clear();
			break;
		case 5:
			return 0;
		default:
			printf("请重新输入你想进行的操作！\n");
			Clear();
			//show1();   //登录前页面展示
		}
	}


	return 0;
}

void show2() {
	printf("******************************************\n");
	printf("*********欢迎来到药品销售管理系统*********\n");
	printf("* 1.添加药品                             *\n");
	printf("* 2.按名称查药品                         *\n");
	printf("* 3.按年份查药品                         *\n");
	printf("* 4.修改药品信息                         *\n");
	printf("* 5.卖药品                               *\n");
	printf("* 6.统计价格大于30的药品                 *\n");
	printf("* 7.显示所有药                           *\n");
	printf("* 8.退出系统                             *\n");
	printf("******************************************\n");
}//药品操作目录显示

void OPIN(med *pmarr) {

	while (1) {
		show2();   //药品操作目录显示
		printf("请输入你想进行的操作（1,2,3,4,5,6,7）：");
		int n = 0;
		scanf("%d", &n);
		switch (n) {
		case 1:
			add_med(pmarr);//添加药品 
			Clear();
			break;
		case 2:
			search_med_byname( pmarr);// 通过名称
			Clear();
			break;
		case 3:
			search_med_bytime(pmarr);//通过时间
			Clear();
			break;
		case 4:
			revise_update_med(pmarr);  // 修改药品信息
			Clear();
			break;
		case 5:
			sell_update_med(pmarr); //卖药品
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
			printf("请重新输入你想进行的操作！\n");
			Clear();
			//show2();   //登录前页面展示
		}
	}
}
