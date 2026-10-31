#pragma once
#include "tools.h"
#include "shop.h"
#include "useitem.h"
#include "buffdo.h"
#include "skinpkg.h"

class plyr2_fortem {
	_playerdata players[4];//玩家数据
	short kicker = 0;//踢人者
	//PK模式渲染
	void paintpkmode();
	//PK模式回合变更
	void kickerchangedoer();
public:
	//PK模式逻辑
	void dopkmode();
};