#pragma once
#include <conio.h>
#include <cstdio>
#include <ctime>
#include <EasyFile.h>
#include <easyx.h>
#include <iostream>
#include <string>
#include <vector>
#include <wchar.h>
#include <Windows.h>

#define CNTIMEAREA (+8)		//中国处于东8区
#define MINSECONDS 60		//一分钟的秒数
#define HOURSECONDS 3600	//一小时的秒数
#define DAYSECONDS 86400	//一天的秒数
#define countofitems 4		//物品数量
#define countofnpctype 4	//NPC类型数量
#define countofbadnpctype 1	//敌对NPC数量(玩家数字代号)
#define countofunusualnpctype 0	//非常规NPC类型数量
#define addinpointcount 14	//插入点数量
#define IDFAILED 0			//MessageBox失败

typedef int MB_CHOOSE;//MessageBox返回值

using std::string, std::vector;

enum _logcls { info, error };//日志类型

//日志信息结构体
struct _log {
	_logcls logclass;
	long long time = 0;//在一天中的秒数
	string data;
};
//用户数据结构体
struct _userdata {
	char username[25];//名字
	char password[25];//密码
	char userid[25];//号
	int coins = 0;//脚脚币
	int money = 0;//脚脚钱
};
_userdata userdatas[100];//用户数据数组
unsigned short userdatacount = 0;//用户数据数组下标
//玩家数据结构体
struct _playerdata {
	int blood = 20;//血量
	int invertory = -1;//物品栏
	int coin = 0;
	int buff[4] = { -1, -1, -1, -1 };//buff/debuff
	int bufftime[4] = { 0, 0, 0, 0 };//buff/debuff剩余生效回合
	bool kicker = false;//是否是踢人者
};
//插件渲染任务
struct painttask {
	int task = 0;//插入类型，0为图片，1为长方形，2为圆形，3为文字
	int x = 0;//插入的x坐标
	int y = 0;//插入的y坐标
	int cx = 0;//另一个x(仅长方形有效)
	int cy = 0;//另一个y(仅长方形有效)
	int r = 0;//半径(仅圆有效)
	int weight = 0;//宽(仅图片有效)
	int height = 0;//高(仅图片有效)
	int fort = 0;//字号(仅文字有效)
	char words[200];//文本(仅文字有效)
	char path[100];//路径(仅图片有效)
	int color = 0;//颜色(图片无效)
};
//NPC数据
struct _NPCdata {
	short type = -1;//类型
	long long x = 0;//x坐标
	long long y = 0;//y坐标
};

vector<vector<painttask>> addinspainttasklist;//插件渲染任务列表
short coinsofpayitems[countofitems];//物品价格
HWND hWnd;//应用窗口句柄
float windowasp = 1.0;//窗口缩放
vector<_log> logs;//日志
bool willappstart = true;//脚脚大战是否启动

//图片变量
IMAGE loginimg;//登录界面图片
IMAGE itemimg[countofitems];//物品图片
IMAGE itemmask[countofitems];//物品掩码图
IMAGE oneprmodeimg;//独立模式图片
IMAGE pkmodeimg;//PK模式图片
IMAGE hitbankmodeimg;//打银行模式图片
IMAGE bankboomimg;//银行炮弹图片
IMAGE bankboommask;//银行炮弹掩码图
IMAGE menuimg;//菜单图片
IMAGE settingsimg;//设置图片
IMAGE NPCskinimg[countofnpctype];//NPC外形图片
IMAGE NPCskinmask[countofnpctype];//NPC外形掩码图
IMAGE exitbtnimg;//退出按钮图片
IMAGE exitbtnmask;//退出按钮掩码图

//增加新日志
void addlog(_logcls logclass, string logdata) {
	_log logtmp;
	logtmp.logclass = logclass;
	logtmp.data = logdata;
	logtmp.time = time(NULL) % DAYSECONDS;
	logs.push_back(logtmp);
}
//带报错的定制版freopen
bool Jfreopen(const char* _FileName, const char* _Mode, FILE* _Stream) {
	if (freopen(_FileName, _Mode, _Stream) == NULL) {
		char logdata[MAX_PATH + 7];
		sprintf(logdata, "找不到%s", _FileName);
		MessageBox(hWnd,
			logdata,
			"你给老子东西干哪去了?",
			MB_SYSTEMMODAL | MB_ICONERROR
		);
		addlog(error, logdata);
		return false;
	}
	else {
		char logdata[MAX_PATH + 10];
		sprintf(logdata, "%s加载成功", _FileName);
		addlog(info, logdata);
		return true;
	}
}
//带报错的定制版loadimage
bool Jloadimage(IMAGE* pDstImg, LPCTSTR pImgFile, int nWidth = 0, int nHeight = 0, bool bResize = false) {
	if (Jfreopen(pImgFile, "r", stdin)) {
		loadimage(pDstImg, pImgFile, nWidth, nHeight, bResize);
		return true;
	}
	else {
		return false;
	}
	fclose(stdin);
	freopen("CON", "r", stdin);
}
//string转char*
void StringTochars(string input, LPSTR output) {
	for (int i = 0; i < input.size(); i++) {
		output[i] = input[i];
	}
}
//某键是否按下
bool JGetKeydown(int vKey) {
	if (GetAsyncKeyState(vKey) & 0x8000) {
		return true;
	}
	else {
		return false;
	}
}
//幂
double EMP(double num, int emp) {
	double retnum = num;
	if (emp > 0) {
		for (int i = 1; i < emp; i++) {
			retnum *= num;
		}
	}
	else if (emp < 0) {
		for (int i = emp; i <= 0; i++) {
			retnum /= num;
		}
	}
	else if (emp == 0) {
		retnum = 1;
	}
	return retnum;
}