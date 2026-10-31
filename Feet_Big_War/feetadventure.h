#pragma once
#include "tools.h"
#include "skinpkg.h"

//脚脚探索
class theadvnteofft {
	clock_t timems = 0;
	int framecount = 0;
	const short soldierspeed = 9;//兵速度
	const short NPCwalkingspeed = 4;//NPC行走速度
	enum { east, sorth, west, north }playertoward;
	_NPCdata NPC[32];
	vector<_NPCdata> unusualNPC;
	short ablerushingtime = 1800;//可冲刺时间(1/60frame)

	//脚脚探索渲染
	void paintavt();
	//创上去的反应
	bool knocking(short speed, short mark, int& addx, int& addy);
	//寻路（靠近玩家）
	void findnearlistroad(short speed, short mark, int& addx, int& addy);
	//兵行为
	void soldiersaction(short mark);
	//资本家行为
	void capitalistaction(short mark);
	//犹太人行为
	void jewaction(short mark);
	//世界事件
	void worldaction();
public:
	//脚脚探索主函数
	void adventuremain();
};