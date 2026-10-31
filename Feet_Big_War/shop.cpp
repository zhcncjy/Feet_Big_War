#include "shop.h"
//商店
void shop(_playerdata& player) {
	bool buyed = false;
	while (!buyed) {
		//渲染
		cleardevice();
		for (int i = 0; i < countofitems; i++) {
			putimage(0 + 80 * (i % 8), 0 + 50 * (i / 8), itemimg + i);
			settextstyle(20, 0, "楷体");
			settextcolor(BLACK);
			char outputcoinofpaybuffer[6];
			sprintf(outputcoinofpaybuffer, "%d", coinsofpayitems[i]);
			outtextxy(0 + 80 * (i % 8), 0 + 50 * (i / 8) + 30, outputcoinofpaybuffer);
		}
		setfillcolor(LIGHTBLUE);
		solidrectangle(640, 0, 800, 600);
		settextstyle(60, 0, "楷体");
		outtextxy(660, 270, "退出");
		skinPKGdoer(5);
		FlushBatchDraw();
		//监测鼠标输入
		ExMessage msg;
		if (peekmessage(&msg, EX_MOUSE)) {
			if (msg.message == WM_LBUTTONUP) {
				if (msg.x >= 0 * windowasp &&
					msg.x <= 640 * windowasp &&
					msg.x / (80 * windowasp) + (int)(msg.y / (50 * windowasp)) * 8 < countofitems) {
					if (player.coin >= coinsofpayitems[(int)(msg.x / (80 * windowasp) + (int)(msg.y / (50 * windowasp)) * 8)]) {
						player.coin -= coinsofpayitems[(int)(msg.x / (80 * windowasp) + (int)(msg.y / (50 * windowasp)) * 8)];
						player.invertory = msg.x / (80 * windowasp) + (int)(msg.y / (50 * windowasp)) * 8;
						buyed = true;
					}
				}//购买
				else {
					buyed = true;
				}//退出
			}
		}
		Sleep(10);
	}
	flushmessage(EX_MOUSE);
}