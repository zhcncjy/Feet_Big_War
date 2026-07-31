#pragma once
#include <easyx.h>
#include <Windows.h>
#include <cstdio>
#include <string>
#include <conio.h>
#include <ctime>
#include <wchar.h>

#define countofitems 4

using std::string;

short coinsofpayitems[countofitems];

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