#pragma once
#include "tools.h"
#include "shop.h"
#include "useitem.h"
#include "buffdo.h"
#include "skinpkg.h"

//打银行
class plyrwithbank {
	_playerdata players[2];//玩家数据&银行数据
	int round = 0;//回合数
	//打银行启动资金兑换
	bool dohitbankprepare();
	//打银行渲染
	void painthitbankmode();
public:
	//打银行逻辑
	void dohitbankmode();
};
