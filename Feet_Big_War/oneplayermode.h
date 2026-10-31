#pragma once
#include "tools.h"
#include "shop.h"
#include "useitem.h"
#include "buffdo.h"
#include "skinpkg.h"

//独立模式
class plyr1_fortem {
	_playerdata players[2];//玩家数据
	//独立模式渲染
	void paintoneplayermode();
public:
	//独立模式逻辑
	void dooneplayermode();
};