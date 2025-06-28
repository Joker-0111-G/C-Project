#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Bank.h"
#include <cassert>
#include <string.h>
#include <ctype.h>
#include <corecrt_malloc.h>
#include <stdlib.h>
#include <time.h>


//管理员操作，   msize mlimit赋初始值
void MInitArray(ManagerArry* pmarr) {//初始化
	//参数校验 
	assert(pmarr != NULL);
	pmarr->_msize = 0;//有效个数
	pmarr->_mlimit = MANAGERLIMIT;
	MFileMessageOperate(pmarr, "manager.txt");//管理员0下标数据
}

//超级管理员    1个  从文件获取    超级管理员登陆成功
//从文件读数据  更新 管理员0下标数据
void MFileMessageOperate(ManagerArry* pmarr, const char* filepath) {  //尝试 r  打开，不用创建
	assert(pmarr && filepath);
	FILE* fp = fopen(filepath,"r");
	// 账号 密码 身份证 姓名
	if (fp == NULL) {//文件不存在应创建文件并写入
		fp = fopen(filepath, "w");
		if (fp == NULL) {
			printf("文件以写方式打开失败\n");
			return;
		}
		fprintf(fp, "%d %d idcard super", 123, 123);
	}
	
	unsigned int id, passwd;
	scanf("%d %d %s %s", &id, &passwd, &pmarr->marr[0]._midcard, &pmarr->marr[0]._mname);
	pmarr->marr[0]._mid = id;
	pmarr->marr[0]._mpasswd = passwd;
	printf("获取数据成功\n");
	pmarr->marr[0]._merrtimes = 0;
	pmarr->marr[0]._mstate = normal;//正常状态
	fclose(fp);
}

//管理员登录 suprt
//返回值  bool 
//登陆成功  返回管理员 地址  负责NULL
Manager* Mlogin(ManagerArry* pmarr, int id, int passwd, const char* name, Identity identity) {
	int index = identity == super ? 0:( isupper(name[0]) ? name[0] - 64 : name[0] - 96);
	////超级管理员
	//if (identity == super && pmarr->marr[0]._mid == id && pmarr->marr[0]._mpasswd==passwd && !strcmp(pmarr->marr[0]._mname, name)) {
	//	printf("超级管理员登录成功\n");
	//	return &pmarr->marr[0];
	//}
	////普通管理员
	////name 首字母  "zs"   ->  26下标
	///*int index = isupper(name[0]) ? name[0] - 64 : name[0] - 96;*/
	//if (pmarr->marr[index]._mid == id && pmarr->marr[index]._mpasswd == passwd && !strcmp(pmarr->marr[index]._mname, name)) {
	//	printf("登陆成功");
	//}
	if (pmarr->marr[index]._mid == id && pmarr->marr[index]._mpasswd == passwd 
		&& !strcmp(pmarr->marr[index]._mname, name)&&pmarr->marr[index]._mstate==normal) {
		printf("管理员登陆成功\n");
		return &pmarr->marr[0];
	}
#ifdef NDEBUG

#else   //debug  版本   调试有效
	if (pmarr->marr[index]._mstate != normal) printf("状态被锁，登录失败\n");
	else printf("管理员账号，密码，姓名错误\n");
#endif 
	return NULL;
}

//注册普通管理员   无一个姓
bool MRegister(ManagerArry* pmarr, int id, int passwd, const char* name, const char* idcard) {
	if (pmarr->_msize == pmarr->_mlimit) {
		printf("管理员岗位已满，注册失败\n");
		return false;
	}
	int index = isupper(name[0]) ? name[0] - 64 : name[0] - 96;
	//将index下标  赋值
	pmarr->marr[index]._merrtimes = 0;
	pmarr->marr[index]._mid = id;
	pmarr->marr[index]._mpasswd = passwd;
	strcpy(pmarr->marr[index]._mname, name);
	strcpy(pmarr->marr[index]._midcard, idcard);
	pmarr->marr[index]._mstate = normal;
	pmarr->_mlimit++;
	printf("注册成功\n");
	return true;

}

//注销管理员  name定位   idcard 判断是否本人
bool Mdelete(ManagerArry* pmarr, const char* name, const char* idcard) {
	bool res = true;
	int index = isupper(name[0]) ? name[0] - 64 : name[0] - 96;
	if (!strcmp(pmarr->marr[index]._mname, name) &&
		!strcmp(pmarr->marr[index]._midcard, idcard))
	{
		pmarr->_msize--;
		printf("删除成功\n");
	}
	else
	{
		printf("不存在管理员, 删除失败\n");
		res = false;
	}
	return res;
}

//修改超级管理员自己密码     更新文件中数据
bool MChangePasswd(Manager* pm, Identity identity, int newpasswd);

//激活普通管理员
bool Mactive(ManagerArry* pmarr, const char* name, const char* idcard);

//初始化卡
void CInitArray(CardArray* pcarr) {
	pcarr->pcards = (BankCard*)malloc(CINITSIZE * sizeof(BankCard));
	assert(pcarr->pcards != NULL);
	if (pcarr->pcards == NULL){
		return;

	}
	pcarr->_ccapacity = CINITSIZE;
	pcarr->_csize = 0; //有效卡张数  0
	printf("初始化卡数组成功\n");
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

//缺点:  项目终止  所有卡 的记录信息  清空 未存储在文件中
//注册卡   pm   --- 文件中获取id passwd  身份证...初始化银行卡数组.
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
		//读取到文件末尾 账号 密码 钱 状态 银行名 地址 审核人名 储户姓名 身份证 电话
		pc = &pcarr->pcards[i];
		fscanf(fp, "%d %d %f %d %d %d %s %s %s %lld\n",
			&id, &passwd, &pc->_money, &state, pc->_bname,
			pc->_baddress, pc->_reviewedname, pc->_user._uname,
			pc->_user._uidcard, &pc->_user._uipnone);
		pc->_cid = id;
		pc->_cpasswd = passwd;
		pc->_cstate = (enum State)state;
		//不考虑以前记录存起来
		//一张卡  对应一个流水记录数组 --   新记录新数组
		pc->records._precord = (Record*)malloc(RECORDSIZE * sizeof(Record));
		assert(pc->records._precord != NULL);
		pc->records._rsize = 0;// 记录有效个数
		pc->records._rcapacity = RECORDSIZE; //记录个数

		i++;
		if (pcarr->_csize == pcarr->_ccapacity)
			Grow(pcarr);  //数组扩容  
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
{ //7位 8位 9位 10位     2006  -->  2024
	char buff[5] = { 0 };
	for (int i = 0; i < 4; i++)    //截取身份证中年份
		buff[i] = idcard[i + 6];  //2002
	int year = atoi(buff); //字符串转整型 -> int 2002
	//获取系统时间
	time_t t;  	time(&t);
	tm* ptm = localtime(&t);
	return ptm->tm_year + 1900 - year;
}


//卡业务逻辑调用函数顺序: 
//   1. CInitArray(); 2. ReadFileToInitCardsMessage 3. CRegister
//注册逻辑: 1.身份证重复，年龄<18 注册失败 
//          2. 内存是否扩容  
//          3.数组size下标存数据  size++   注册成功
bool  CRegister(CardArray* pcarr, Manager* pm)
{
	char idcard[20];
	printf("请输入卡储户身份证: ");   scanf("%s", idcard);
	if (CSearchByIdCard(pcarr, idcard) != NULL)
	{
		printf("储户身份证号重复，注册失败\n");   //strcpy(pc->_user.idcard,idcard)
		return false;
	}
	if (GetAge(idcard) < 18)
	{
		printf("未成年age<18，注册失败\n");
		return false;
	}
	if (pcarr->_csize == pcarr->_ccapacity)
		Grow(pcarr);
	//卡数组满  -- 扩容

	//在卡数组中 对应 size下标下 存放 卡信息  （所有属性）
	// 从键盘获取 卡信息  并存放 card[size] 下
	unsigned short id, passwd;
	BankCard* pc = &pcarr->pcards[pcarr->_csize];
	printf("请输入卡账号: ");	scanf("%d", &id); pc->_cid = id;
	printf("请输入卡密码: "); scanf("%d", &passwd); pc->_cpasswd = passwd;
	printf("请输入卡存储金额: "); scanf("%f", &pc->_money);
	int choice;
	do {
		printf("请输入银行编号:0.建行 1.招行 2工行 : ");
		scanf("%d", &choice);
	} while (choice > 2 || choice < 0);
	pc->_bname = (enum BankName)choice;
	pc->_baddress = (enum BankAddress)choice;  //银行名 枚举    与 银行地址 一一对应关系
	strcpy(pc->_reviewedname, pm->_mname);
	printf("请输入卡储户姓名: "); scanf("%s", &pc->_user._uname);
	printf("请输入卡储户电话: "); scanf("%lld", &pc->_user._uipnone);
	pc->_cerrtimes = 0;//新卡登录失败次数0
	pc->_cstate = normal;
	strcpy(pc->_user._uidcard, idcard);

	//一张卡  对应一个流水记录数组 -- 
	pc->records._precord = (Record*)malloc(RECORDSIZE * sizeof(Record));
	assert(pc->records._precord != NULL);
	pc->records._rsize = 0;// 记录有效个数
	pc->records._rcapacity = RECORDSIZE; //记录个数

	pcarr->_csize++;
	printf("注册成功\n");
}

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
void MChangePhone(CardArry* pcarr, const char* idcard, long long newphone) {
	BankCard* pc = CSearchByIdCard(pcarr, idcard);
	if (pc == NULL)
	{
	}
	pc->_user._uipnone = newphone;
}
