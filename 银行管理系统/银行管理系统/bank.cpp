#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Bank.h"
#include <cassert>
#include <string.h>
#include <ctype.h>
#include <corecrt_malloc.h>
#include <stdlib.h>
#include <time.h>


//����Ա������   msize mlimit����ʼֵ
void MInitArray(ManagerArry* pmarr) {//��ʼ��
	//����У�� 
	assert(pmarr != NULL);
	pmarr->_msize = 0;//��Ч����
	pmarr->_mlimit = MANAGERLIMIT;
	MFileMessageOperate(pmarr, "manager.txt");//����Ա0�±�����
}

//��������Ա    1��  ���ļ���ȡ    ��������Ա��½�ɹ�
//���ļ�������  ���� ����Ա0�±�����
void MFileMessageOperate(ManagerArry* pmarr, const char* filepath) {  //���� r  �򿪣����ô���
	assert(pmarr && filepath);
	FILE* fp = fopen(filepath,"r");
	// �˺� ���� ���֤ ����
	if (fp == NULL) {//�ļ�������Ӧ�����ļ���д��
		fp = fopen(filepath, "w");
		if (fp == NULL) {
			printf("�ļ���д��ʽ��ʧ��\n");
			return;
		}
		fprintf(fp, "%d %d idcard super", 123, 123);
	}
	
	unsigned int id, passwd;
	scanf("%d %d %s %s", &id, &passwd, &pmarr->marr[0]._midcard, &pmarr->marr[0]._mname);
	pmarr->marr[0]._mid = id;
	pmarr->marr[0]._mpasswd = passwd;
	printf("��ȡ���ݳɹ�\n");
	pmarr->marr[0]._merrtimes = 0;
	pmarr->marr[0]._mstate = normal;//����״̬
	fclose(fp);
}

//����Ա��¼ suprt
//����ֵ  bool 
//��½�ɹ�  ���ع���Ա ��ַ  ����NULL
Manager* Mlogin(ManagerArry* pmarr, int id, int passwd, const char* name, Identity identity) {
	int index = identity == super ? 0:( isupper(name[0]) ? name[0] - 64 : name[0] - 96);
	////��������Ա
	//if (identity == super && pmarr->marr[0]._mid == id && pmarr->marr[0]._mpasswd==passwd && !strcmp(pmarr->marr[0]._mname, name)) {
	//	printf("��������Ա��¼�ɹ�\n");
	//	return &pmarr->marr[0];
	//}
	////��ͨ����Ա
	////name ����ĸ  "zs"   ->  26�±�
	///*int index = isupper(name[0]) ? name[0] - 64 : name[0] - 96;*/
	//if (pmarr->marr[index]._mid == id && pmarr->marr[index]._mpasswd == passwd && !strcmp(pmarr->marr[index]._mname, name)) {
	//	printf("��½�ɹ�");
	//}
	if (pmarr->marr[index]._mid == id && pmarr->marr[index]._mpasswd == passwd 
		&& !strcmp(pmarr->marr[index]._mname, name)&&pmarr->marr[index]._mstate==normal) {
		printf("����Ա��½�ɹ�\n");
		return &pmarr->marr[0];
	}
#ifdef NDEBUG

#else   //debug  �汾   ������Ч
	if (pmarr->marr[index]._mstate != normal) printf("״̬��������¼ʧ��\n");
	else printf("����Ա�˺ţ����룬��������\n");
#endif 
	return NULL;
}

//ע����ͨ����Ա   ��һ����
bool MRegister(ManagerArry* pmarr, int id, int passwd, const char* name, const char* idcard) {
	if (pmarr->_msize == pmarr->_mlimit) {
		printf("����Ա��λ������ע��ʧ��\n");
		return false;
	}
	int index = isupper(name[0]) ? name[0] - 64 : name[0] - 96;
	//��index�±�  ��ֵ
	pmarr->marr[index]._merrtimes = 0;
	pmarr->marr[index]._mid = id;
	pmarr->marr[index]._mpasswd = passwd;
	strcpy(pmarr->marr[index]._mname, name);
	strcpy(pmarr->marr[index]._midcard, idcard);
	pmarr->marr[index]._mstate = normal;
	pmarr->_mlimit++;
	printf("ע��ɹ�\n");
	return true;

}

//ע������Ա  name��λ   idcard �ж��Ƿ���
bool Mdelete(ManagerArry* pmarr, const char* name, const char* idcard) {
	bool res = true;
	int index = isupper(name[0]) ? name[0] - 64 : name[0] - 96;
	if (!strcmp(pmarr->marr[index]._mname, name) &&
		!strcmp(pmarr->marr[index]._midcard, idcard))
	{
		pmarr->_msize--;
		printf("ɾ���ɹ�\n");
	}
	else
	{
		printf("�����ڹ���Ա, ɾ��ʧ��\n");
		res = false;
	}
	return res;
}

//�޸ĳ�������Ա�Լ�����     �����ļ�������
bool MChangePasswd(Manager* pm, Identity identity, int newpasswd);

//������ͨ����Ա
bool Mactive(ManagerArry* pmarr, const char* name, const char* idcard);

//��ʼ����
void CInitArray(CardArray* pcarr) {
	pcarr->pcards = (BankCard*)malloc(CINITSIZE * sizeof(BankCard));
	assert(pcarr->pcards != NULL);
	if (pcarr->pcards == NULL){
		return;

	}
	pcarr->_ccapacity = CINITSIZE;
	pcarr->_csize = 0; //��Ч������  0
	printf("��ʼ��������ɹ�\n");
}

static void Grow(CardArray* pcarr)
{
	BankCard* p = (BankCard*)realloc(pcarr->pcards, 2 * pcarr->_ccapacity * sizeof(BankCard));
	assert(p != NULL);
	if (p == NULL)
	{
		free(pcarr->pcards);
		pcarr->pcards = NULL;
		return;
	}
	pcarr->pcards = p;
	pcarr->_ccapacity *= 2;
}

//ȱ��:  ��Ŀ��ֹ  ���п� �ļ�¼��Ϣ  ��� δ�洢���ļ���
//ע�Ῠ   pm   --- �ļ��л�ȡid passwd  ���֤...��ʼ�����п�����.
static void ReadFileToInitCardsMessage(CardArray* pcarr) {
	FILE* fp = fopen("card.txt", "w");
	if (fp == NULL) {
		fp = fopen("card.txt", "w");
		assert(fp != NULL);
		fclose(fp);
		return;
	}
	int i = 0;
	unsigned short id, passwd, state;
	BankCard* pc;
	while (feof(fp) != EOF) { 
		//��ȡ���ļ�ĩβ �˺� ���� Ǯ ״̬ ������ ��ַ ������� �������� ���֤ �绰
		pc = &pcarr->pcards[i];
		fscanf(fp, "%d %d %f %d %d %d %s %s %s %lld\n",
			&id, &passwd, &pc->_money, &state, pc->_bname,
			pc->_baddress, pc->_reviewedname, pc->_user._uname,
			pc->_user._uidcard, &pc->_user._uipnone);
		pc->_cid = id;
		pc->_cpasswd = passwd;
		pc->_cstate = (enum State)state;
		//��������ǰ��¼������
		//һ�ſ�  ��Ӧһ����ˮ��¼���� --   �¼�¼������
		pc->records._precord = (Record*)malloc(RECORDSIZE * sizeof(Record));
		assert(pc->records._precord != NULL);
		pc->records._rsize = 0;// ��¼��Ч����
		pc->records._rcapacity = RECORDSIZE; //��¼����

		i++;
		if (pcarr->_csize == pcarr->_ccapacity)
			Grow(pcarr);  //��������  
	}
}

static BankCard* CSearchByIdCard(CardArray* pcarr, const char* idcard)
{
	for (int i = 0; i < pcarr->_csize; i++)
	{
		if (strcmp(pcarr->pcards[i]._user._uidcard, idcard) == 0)
		{
			return &pcarr->pcards[i]; //pcarr->pcards+i
		}
	}
	return NULL;
}


static int GetAge(const char* idcard)
{ //7λ 8λ 9λ 10λ     2006  -->  2024
	char buff[5] = { 0 };
	for (int i = 0; i < 4; i++)    //��ȡ���֤�����
		buff[i] = idcard[i + 6];  //2002
	int year = atoi(buff); //�ַ���ת���� -> int 2002
	//��ȡϵͳʱ��
	time_t t;  	time(&t);
	tm* ptm = localtime(&t);
	return ptm->tm_year + 1900 - year;
}


//��ҵ���߼����ú���˳��: 
//   1. CInitArray(); 2. ReadFileToInitCardsMessage 3. CRegister
//ע���߼�: 1.���֤�ظ�������<18 ע��ʧ�� 
//          2. �ڴ��Ƿ�����  
//          3.����size�±������  size++   ע��ɹ�
bool  CRegister(CardArray* pcarr, Manager* pm)
{
	char idcard[20];
	printf("�����뿨�������֤: ");   scanf("%s", idcard);
	if (CSearchByIdCard(pcarr, idcard) != NULL)
	{
		printf("�������֤���ظ���ע��ʧ��\n");   //strcpy(pc->_user.idcard,idcard)
		return false;
	}
	if (GetAge(idcard) < 18)
	{
		printf("δ����age<18��ע��ʧ��\n");
		return false;
	}
	if (pcarr->_csize == pcarr->_ccapacity)
		Grow(pcarr);
	//��������  -- ����

	//�ڿ������� ��Ӧ size�±��� ��� ����Ϣ  ���������ԣ�
	// �Ӽ��̻�ȡ ����Ϣ  ����� card[size] ��
	unsigned short id, passwd;
	BankCard* pc = &pcarr->pcards[pcarr->_csize];
	printf("�����뿨�˺�: ");	scanf("%d", &id); pc->_cid = id;
	printf("�����뿨����: "); scanf("%d", &passwd); pc->_cpasswd = passwd;
	printf("�����뿨�洢���: "); scanf("%f", &pc->_money);
	int choice;
	do {
		printf("���������б��:0.���� 1.���� 2���� : ");
		scanf("%d", &choice);
	} while (choice > 2 || choice < 0);
	pc->_bname = (enum BankName)choice;
	pc->_baddress = (enum BankAddress)choice;  //������ ö��    �� ���е�ַ һһ��Ӧ��ϵ
	strcpy(pc->_reviewedname, pm->_mname);
	printf("�����뿨��������: "); scanf("%s", &pc->_user._uname);
	printf("�����뿨�����绰: "); scanf("%lld", &pc->_user._uipnone);
	pc->_cerrtimes = 0;//�¿���¼ʧ�ܴ���0
	pc->_cstate = normal;
	strcpy(pc->_user._uidcard, idcard);

	//һ�ſ�  ��Ӧһ����ˮ��¼���� -- 
	pc->records._precord = (Record*)malloc(RECORDSIZE * sizeof(Record));
	assert(pc->records._precord != NULL);
	pc->records._rsize = 0;// ��¼��Ч����
	pc->records._rcapacity = RECORDSIZE; //��¼����

	pcarr->_csize++;
	printf("ע��ɹ�\n");
}

//��ʧ
bool CGetlost(CardArray* pearr, const char* idcard);

//����
bool CActive(CardArray* pearr, const char* idcard);

//����ˮ��Ϣ
void GetRecords(BankCard* pc, int month);

//ע����
bool CDelete(CardArry* pcarr, const char* idcard);

//�޸���ͨ����Ա����

//��ͨ����Ա��½�ɹ����޸Ŀ�  �����ֻ��� 
void MChangePhone(CardArry* pcarr, const char* idcard, long long newphone) {
	BankCard* pc = CSearchByIdCard(pcarr, idcard);
	if (pc == NULL)
	{
	}
	pc->_user._uipnone = newphone;
}
