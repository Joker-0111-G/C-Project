#define _CRT_SECURE_NO_WARNINGS
#include "Bank.h"
#include <stdio.h>

void MAfterSuccess(ManagerArray* pmarr, Manager* pm)
{
	int choice, id, passwd;
	char name[10], idcard[20];
	while (1)
	{
		printf("1. 注册管理员 2.激活普通管理员  3.挂失卡 4.修改密码 5.退出\n");
		scanf("%d", &choice);
		if (choice == 5)  break;
		printf("请输入姓名:"); scanf("%s", name);
		printf("请输入身份证:"); scanf("%s", idcard);
		switch (choice)
		{
		case 1:
			printf("请输入账号:"); scanf("%d", &id);
			printf("请输入密码:"); scanf("%d", &passwd);
			MRegister(pmarr, id, passwd, name, idcard);
			break;
		case 2:
			MActive(pmarr, name, idcard);
			break;
		case 3: //////
			break;
		case 4:
			MChangePasswd(pm, (enum Identity)0, passwd);
			break;
		}
	}
}
int main()
{
	ManagerArray m;
	MInitArray(&m); //size  capacti --> [0]
	int choice, id, passwd, identity;
	char name[10];
	Manager* pm;
	while (1)
	{
		printf("1. 管理员登录  2. 注册\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("请输入登录账号:"); scanf("%d", &id);
			printf("请输入登录密码:"); scanf("%d", &passwd);
			printf("请输入登录姓名:"); scanf("%s", name);
			printf("请输入登录身份0 普通 1 超级:"); scanf("%d", &identity);
			pm = MLogin(&m, id, passwd, name, (enum Identity)identity);
			if (pm != NULL)
				MAfterSuccess(&m, pm);
			break;
		case 2:
			break;
		}

	}
	return 0;
}