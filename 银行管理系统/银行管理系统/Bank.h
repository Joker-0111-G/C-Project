#pragma once //��ֹ�ظ�����
#ifndef _BANK_H
#define MINITSIZE 27     //����Ա��   0�±꣬��������Ա
#define CINITSIZE 10     //������ ��ʼ��
#define MANAGERLIMIT 5
#define RECORDSIZE  10  //��ʼ��ÿ�ſ� ��Ӧ�ļ�¼�����С
//����Ա���
typedef enum Identity {ordinary,super}Identity;
typedef enum State{normal,islocked,sleep}State;//����   ����    ˯��

//����Ա����
//�˺�6λʮ����     ����6λʮ����   ʧ�ܴ���������� 
typedef struct Manager {
	unsigned long long _mid : 20;
	unsigned long long _mpasswd : 20;
	unsigned long long _merrtimes : 2;   //����Ա״̬
	State _mstate ; 
	char _midcard[20];
	char _mname[10];

}Manager;      //8+4+20+10+6======48�ֽ�


//������п�����

typedef enum BankName { JH, ZS, GS }BankName;
typedef enum BankAddress { BDJ, XDJ, NDJ }BankAddress;
typedef enum OperateType { _rsave, rwithdraw, _transferin, _transferout }OperateType;

typedef struct User {
	char _uname[20];
	char _uidcard[20];
	long long _uipnone;
}User;

typedef struct Record {
	char rtime[35];//"2024-05-25 ������ 11:44:50" ���
	//localtime()   ���� ==>0 1 2 3 4 5 6   ptm->_wday
	OperateType _operate;
	float _rmoney;  //��¼����ʾ�Ľ��
}Record;  

typedef struct RecordsMessage {
	Record* _precord;  //���ٶ�̬�ڴ�
	int _rsize;       //��Ч����
	int _rcapacity;  //��¼��������
}RecordsMessage;

typedef struct BankCard {
	unsigned long long _cid : 20;
	unsigned long long _cpasswd : 20;
	unsigned long long _cerrtimes : 2;   //����Ա״̬
	float _money;
	State _cstate;  //���п�״̬
	BankName _bname;  //��������
	BankAddress _baddress; //���е�ַ
	char _reviewedname[10];  //���������
	User _user;  //����
	RecordsMessage records; //һ�ſ������ĺܶ��¼��Ϣ

}Bankcard;



//����Ա����->��������Ա   �˺�����   ���ļ���ȡ  1��  0�±�     ������1�±�֮����ͨ����Ա  5������Ա��
typedef struct ManagerArry{
	Manager marr[MINITSIZE];  //���ݹ���Ա��������ĸ
	int _msize;//��¼��Ч����Ա����
	int _mlimit;//�����������  MANAGERLIMIT

}MArry;

//���п�����   ->  [100]     relloc  ��̬�����ڴ�
typedef struct CardArry {
	BankCard* pcards;  //��̬�ڴ�
	int _csize;        // �����ڴ�
	int _ccapacity;  //���п�����pcards����
}CardArray;

//����Ա������   msize mlimit����ʼֵ
void MIniArray(ManagerArry *pmarr);//��ʼ��
void CInitArray(CardArry *pcarr);//��ʼ��

//��������Ա    1��  ���ļ���ȡ    ��������Ա��½�ɹ�
void MFileMessageOperate(Manager *pmarr,const char*filepath);  //���� r  �򿪣����ô���

//����Ա��¼ suprt
//����ֵ  bool 
//��½�ɹ�  ���ع���Ա ��ַ  ����NULL
Manager* Mlogin(ManagerArry* pmarr,int id,int passwd, const char* name, Identity identity);

//ע����ͨ����Ա  
bool MRegister(ManagerArry* pmarr, int id, int passwd, const char* name, const char* idcard);

//ע������Ա  name��λ   idcard �ж��Ƿ���
bool Mdelete(ManagerArry* pmarr, const char* name, const char* idcard);

//�޸ĳ�������Ա�Լ�����     �����ļ�������
bool MChangePasswd(Manager* pm, Identity identity,int newpasswd);

//������ͨ����Ա
bool Mactive(ManagerArry* pmarr, const char* name, const char* idcard);

//ע�Ῠ
bool CRegister(CardArray* pearr, Manager* pm);

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
void MChangePhone(CardArray* pcarr, const char* idcard,long long newphone);



#endif // !_BANK_H

