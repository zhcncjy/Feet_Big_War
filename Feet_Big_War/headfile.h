#pragma once
#include <easyx.h>
#include <Windows.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <conio.h>
#include <ctime>
#include <wchar.h>
#include<vector>
#include<EasyFile.h>

#define countofitems 4 //物品数量
#define addinpointcount 14 //插入点数量
#define IDFAILED 0 //MessageBox失败

typedef int MB_CHOOSE;//MessageBox返回值

using std::string, std::vector;

short coinsofpayitems[countofitems];//物品价格
HWND hWnd;//应用窗口句柄
float windowasp = 1.0;//窗口缩放

//string转char*
void StringTochars(string input, LPSTR output) {
	for (int i = 0; i < input.size(); i++) {
		output[i] = input[i];
	}
}

//用户数据结构体
struct userdata {
	char username[25];//名字
	char password[25];//密码
	char userid[25];//号
	int coins = 0;//脚脚币
	int money = 0;//脚脚钱
};
userdata userdatas[100];//用户数据数组
unsigned short userdatacount = 0;//用户数据数组下标
//玩家数据结构体
struct playerdata {
	int blood = 20;//血量
	int invertory = -1;//物品栏
	int coin = 0;
	int buff = -1;//buff/debuff
	int bufftime = 0;//buff/debuff剩余生效回合
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
vector<vector<painttask>> addinspainttasklist;//插件渲染任务列表
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
IMAGE settingsimg;