#define _CRT_SECURE_NO_WARNINGS
#include "Bank.h"
#include <stdio.h>

void MAfterSuccess(ManagerArray* pmarr, Manager* pm)
{
	int choice, id, passwd;
	char name[10], idcard[20];
	while (1)
	{
		printf("1. ע�����Ա 2.������ͨ����Ա  3.��ʧ�� 4.�޸����� 5.�˳�\n");
		scanf("%d", &choice);
		if (choice == 5)  break;
		printf("����������:"); scanf("%s", name);
		printf("���������֤:"); scanf("%s", idcard);
		switch (choice)
		{
		case 1:
			printf("�������˺�:"); scanf("%d", &id);
			printf("����������:"); scanf("%d", &passwd);
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
		printf("1. ����Ա��¼  2. ע��\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("�������¼�˺�:"); scanf("%d", &id);
			printf("�������¼����:"); scanf("%d", &passwd);
			printf("�������¼����:"); scanf("%s", name);
			printf("�������¼���0 ��ͨ 1 ����:"); scanf("%d", &identity);
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