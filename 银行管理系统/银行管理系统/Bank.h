#pragma once //防止重复引用
#ifndef _BANK_H
#define MINITSIZE 27     //管理员数   0下标，超级管理员
#define CINITSIZE 10     //卡数量 初始换
#define MANAGERLIMIT 5
#define RECORDSIZE  10  //初始化每张卡 对应的记录数组大小
//管理员身份
typedef enum Identity {ordinary,super}Identity;
typedef enum State{normal,islocked,sleep}State;//正常   被锁    睡眠

//管理员类型
//账号6位十进制     密码6位十进制   失败次数最多三次 
typedef struct Manager {
	unsigned long long _mid : 20;
	unsigned long long _mpasswd : 20;
	unsigned long long _merrtimes : 2;   //管理员状态
	State _mstate ; 
	char _midcard[20];
	char _mname[10];

}Manager;      //8+4+20+10+6======48字节


//设计银行卡类型

typedef enum BankName { JH, ZS, GS }BankName;
typedef enum BankAddress { BDJ, XDJ, NDJ }BankAddress;
typedef enum OperateType { _rsave, rwithdraw, _transferin, _transferout }OperateType;

typedef struct User {
	char _uname[20];
	char _uidcard[20];
	long long _uipnone;
}User;

typedef struct Record {
	char rtime[35];//"2024-05-25 星期六 11:44:50" 存款
	//localtime()   星期 ==>0 1 2 3 4 5 6   ptm->_wday
	OperateType _operate;
	float _rmoney;  //记录中显示的金额
}Record;  

typedef struct RecordsMessage {
	Record* _precord;  //开辟动态内存
	int _rsize;       //有效数据
	int _rcapacity;  //记录数组容量
}RecordsMessage;

typedef struct BankCard {
	unsigned long long _cid : 20;
	unsigned long long _cpasswd : 20;
	unsigned long long _cerrtimes : 2;   //管理员状态
	float _money;
	State _cstate;  //银行卡状态
	BankName _bname;  //银行名称
	BankAddress _baddress; //银行地址
	char _reviewedname[10];  //审核人姓名
	User _user;  //储户
	RecordsMessage records; //一张卡关联的很多记录信息

}Bankcard;



//管理员数组->超级管理员   账号密码   从文件获取  1个  0下标     ，，，1下标之后普通管理员  5个管理员数
typedef struct ManagerArry{
	Manager marr[MINITSIZE];  //根据管理员姓名首字母
	int _msize;//记录有效管理员个数
	int _mlimit;//最多人数上限  MANAGERLIMIT

}MArry;

//银行卡数组   ->  [100]     relloc  动态申请内存
typedef struct CardArry {
	BankCard* pcards;  //动态内存
	int _csize;        // 有限内存
	int _ccapacity;  //银行卡数组pcards容量
}CardArray;

//管理员操作，   msize mlimit赋初始值
void MIniArray(ManagerArry *pmarr);//初始化
void CInitArray(CardArry *pcarr);//初始化

//超级管理员    1个  从文件获取    超级管理员登陆成功
void MFileMessageOperate(Manager *pmarr,const char*filepath);  //尝试 r  打开，不用创建

//管理员登录 suprt
//返回值  bool 
//登陆成功  返回管理员 地址  负责NULL
Manager* Mlogin(ManagerArry* pmarr,int id,int passwd, const char* name, Identity identity);

//注册普通管理员  
bool MRegister(ManagerArry* pmarr, int id, int passwd, const char* name, const char* idcard);

//注销管理员  name定位   idcard 判断是否本人
bool Mdelete(ManagerArry* pmarr, const char* name, const char* idcard);

//修改超级管理员自己密码     更新文件中数据
bool MChangePasswd(Manager* pm, Identity identity,int newpasswd);

//激活普通管理员
bool Mactive(ManagerArry* pmarr, const char* name, const char* idcard);

//注册卡
bool CRegister(CardArray* pearr, Manager* pm);

//挂失
bool CGetlost(CardArray* pearr, const char* idcard);

//激活
bool CActive(CardArray* pearr, const char* idcard);

//查流水信息
void GetRecords(BankCard* pc, int month);

//注销卡
bool CDelete(CardArry* pcarr, const char* idcard);

//修改普通管理员密码

//普通管理员登陆成功，修改卡  储户手机号 
void MChangePhone(CardArray* pcarr, const char* idcard,long long newphone);



#endif // !_BANK_H

