#include "useitem.h"
//物品使用
void useitem(_playerdata& itemuser, _playerdata& itemeater) {
	switch (itemuser.invertory) {
	case 0://冰箱弹
		itemeater.blood -= 2;
		break;
	case 1://淤泥炸弹
		for (int i = 0; i < 4; i++) {
			if (itemeater.buff[i] == -1) {
				itemeater.buff[i] = 0;
				itemeater.bufftime[i] = 5;
				break;
			}
			else if (itemeater.buff[i] == 0) {
				itemeater.bufftime[i] = 5;
			}
		}
		break;
	case 2://望远镜
		char pr2technologybuffer[80];
		sprintf(pr2technologybuffer,
			"金币:%d\n物品在商店中的位置:第%d个\nbuff剩余生效时间:%d回合",
			itemeater.coin,
			itemeater.invertory + 1,
			itemeater.bufftime
		);
		MessageBox(hWnd, pr2technologybuffer, "对手信息", MB_OK | MB_SYSTEMMODAL);
		break;
	case 3://面包
		itemuser.blood += 1;
	default:
		break;
	}
	skinPKGdoer(10 + itemuser.invertory);
	FlushBatchDraw();
	itemuser.invertory = -1;
}
