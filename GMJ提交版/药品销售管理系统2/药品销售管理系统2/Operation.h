
#pragma once
#ifndef OPERATION_H

#define ADMSIZE 3 //Ŀǰ���ù���Ա��������
#define MEDINCE 100   //��ʼҩ

//��ƹ���Ա
typedef struct administrator {
	int a_num;         //���
	char a_name[20];  //����
	int a_passwd;  //����
}administrator;

//���ҩƷ
typedef struct medince {
	float m_price;            //ҩƷ����
	int m_inventory;          //ҩƷ�����
	char m_name[20];          //ҩƷ����
	char m_brand[20];         //ҩƷƷ��
	char m_manufacture[20];   //ҩƷ��������
	char m_introduction[50];  //ҩƷ���

}medince;

//����Ա����
typedef struct adm {
	administrator a_arr[ADMSIZE];  
	int a_size;
}adm;

//ҩƷ����
typedef struct med {
	medince* pmeds;      //��̬�ڴ�
	int m_size;        //��ЧҩƷ����
	int medcapacity;   //ҩƷ��������
}med;




// File �ļ����� 

//ҩƷ�ļ�����
void File_read_med(med* pmarr, const char* filepath);

//ҩƷ�ļ�д��
void File_write_med(med *pmarr, const char* filepath);

//����Ա�ļ�����
void File_read_adm(adm *paarr, const char* filepath);

//����Ա�ļ�д��
void File_write_adm(adm* paarr, const char* filepath);


//Administrator ����Ա����

//��ʼ��Administrator����
void AInit(adm *paarr); 

//ע��
void enroll(adm*paarr,int num,const char *name, int passwd);

//��¼
void login(adm* paarr, int num, int passwd,med *pmarr);

//ע��
void logout(adm* paarr, int num,const char *name, int passwd);

//��������
void change_password(adm* paarr, int num,const char *name, int passwd,int newpasswd);


//Medince ҩƷ����

//��ʼ��ҩƷ����
void MInit(med* pmarr);

//��̬�ڴ�����
void Grow(med* pmarr);

//���ҩƷ 
void add_med(med *pmarr);

//��ѯҩƷ
void search_med_byname(med* pmarr);  // ͨ������
void search_med_bytime(med* pmarr); //ͨ��ʱ��

//����ҩƷ 
void revise_update_med(med* pmarr);  // �޸�ҩƷ��Ϣ
void sell_update_med(med* pmarr); //��ҩƷ

// ͳ�Ƽ۸�����ͳ�ƴ���30ԪҩƷ��
void statistics_med(med* pmarr);

//��ʾҩƷ��Ϣ
void show_med(med* pmarr);



void show1();   //��¼ǰҳ��չʾ

void OPIN(med *pmarr);   //ҩƷ����ϵͳ����

void show2();   //ҩƷ����Ŀ¼��ʾ

#endif OPERATION_H





