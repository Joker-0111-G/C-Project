
#pragma once
#ifndef OPERATION_H

#define ADMSIZE 3 //目前设置管理员仅有三人
#define MEDINCE 100   //初始药

//设计管理员
typedef struct administrator {
	int a_num;         //编号
	char a_name[20];  //姓名
	int a_passwd;  //密码
}administrator;

//设计药品
typedef struct medince {
	float m_price;            //药品单价
	int m_inventory;          //药品库存量
	char m_name[20];          //药品名称
	char m_brand[20];         //药品品牌
	char m_manufacture[20];   //药品生产日期
	char m_introduction[50];  //药品简介

}medince;

//管理员数组
typedef struct adm {
	administrator a_arr[ADMSIZE];  
	int a_size;
}adm;

//药品数组
typedef struct med {
	medince* pmeds;      //动态内存
	int m_size;        //有效药品数量
	int medcapacity;   //药品数组容量
}med;




// File 文件操作 

//药品文件读入
void File_read_med(med* pmarr, const char* filepath);

//药品文件写入
void File_write_med(med *pmarr, const char* filepath);

//管理员文件读入
void File_read_adm(adm *paarr, const char* filepath);

//管理员文件写入
void File_write_adm(adm* paarr, const char* filepath);


//Administrator 管理员操作

//初始化Administrator数组
void AInit(adm *paarr); 

//注册
void enroll(adm*paarr,int num,const char *name, int passwd);

//登录
void login(adm* paarr, int num, int passwd,med *pmarr);

//注销
void logout(adm* paarr, int num,const char *name, int passwd);

//更改密码
void change_password(adm* paarr, int num,const char *name, int passwd,int newpasswd);


//Medince 药品操作

//初始化药品数组
void MInit(med* pmarr);

//动态内存扩容
void Grow(med* pmarr);

//添加药品 
void add_med(med *pmarr);

//查询药品
void search_med_byname(med* pmarr);  // 通过名称
void search_med_bytime(med* pmarr); //通过时间

//更新药品 
void revise_update_med(med* pmarr);  // 修改药品信息
void sell_update_med(med* pmarr); //卖药品

// 统计价格（例如统计大于30元药品）
void statistics_med(med* pmarr);

//显示药品信息
void show_med(med* pmarr);



void show1();   //登录前页面展示

void OPIN(med *pmarr);   //药品管理系统进入

void show2();   //药品操作目录显示

#endif OPERATION_H





