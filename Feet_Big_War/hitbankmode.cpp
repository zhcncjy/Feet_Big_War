#include "hitbankmode.h"

//打银行渲染
void plyrwithbank::painthitbankmode() {
	putimage(0, 0, &hitbankmodeimg);//渲染场景
	setfillcolor(RGB(0x3F, 0x48, 0xCC));
	solidrectangle(0, 380, 250, 410);//渲染己方腿
	setfillcolor(WHITE);
	setlinecolor(RGB(0x3F, 0x48, 0xCC));
	setlinestyle(PS_SOLID, 5);
	fillroundrect(0, 2, players[0].blood * 12, 20, 10, 10);//渲染己方血条
	setlinecolor(RGB(0x22, 0xB1, 0x4C));
	fillroundrect(800 - players[1].blood * 12, 2, 800, 20, 10, 10);//渲染对手血条
	settextstyle(40, 0, "楷体");
	char player0coinoutputbuffer[6];
	sprintf(player0coinoutputbuffer, "：%d", players[0].coin);
	outtextxy(50, 600 - 115, player0coinoutputbuffer);//渲染金币数量
	char gunpoweroutputbuffer[20];
	sprintf(gunpoweroutputbuffer, "弹药装填中:%d%c", (round % 5 + 1) * 20, '%');
	outtextxy(800 - 300, 40, gunpoweroutputbuffer);
	if (players[0].invertory != -1) {
		putimage(110, 440, itemimg + players[0].invertory);
	}//渲染物品栏
	if (players[1].kicker) {
		setfillcolor(WHITE);
		solidrectangle(0, 430, 150, 530);
	}
	skinPKGdoer(4);
	FlushBatchDraw();
}
//打银行启动资金兑换
bool plyrwithbank::dohitbankprepare() {
	bool prepareok = false;
	while (!prepareok) {
		char coinsinputbuffer[12];
		bool enter = InputBox(coinsinputbuffer, 11, "1脚脚币=50金币（50%手续费）", "启动资金投入", 0, 0, 0, false);
		if (!enter) {
			return false;
		}
		bool inputisok = true;
		for (int i = 0; coinsinputbuffer[i + 1] != '\0'; i++) {
			if (!(coinsinputbuffer[i] >= '0' && coinsinputbuffer[i] <= '9')) {
				inputisok = false;
			}
		}
		if (inputisok) {
			int temp = 0;
			sscanf(coinsinputbuffer, "%d", &temp);
			if (temp <= userdatas[userdatacount].coins) {
				players[0].coin = temp * 50;
				userdatas[userdatacount].coins -= temp;
				prepareok = true;
				return true;
			}
			else {
				MessageBox(NULL, "你没钱!!!", "投入失败", MB_SYSTEMMODAL | MB_ICONINFORMATION);
				prepareok = true;
				return false;
			}
		}
		else {
			MessageBox(NULL, "NAN!!!", "投入失败", MB_SYSTEMMODAL | MB_ICONERROR);
			prepareok = true;
			return false;
		}
	}
}
//打银行逻辑
void plyrwithbank::dohitbankmode() {
	if (!dohitbankprepare()) {
		return;
	}
	players[1].blood = 40;
	srand(time(NULL));
	players[0].kicker = true;
	//游戏过程
	while (players[0].blood > 0 && players[1].blood > 0) {
		bool kickerchange = false;//回合是否更新
		//渲染
		painthitbankmode();
		//玩家或AI操作
		if (players[0].kicker) {
			ExMessage msg;
			if (peekmessage(&msg)) {
				if (msg.message == WM_LBUTTONUP) {
					if (msg.x >= 0 * windowasp
						&& msg.x <= 50 * windowasp
						&& msg.y >= 430 * windowasp
						&& msg.y <= 480 * windowasp) {
						shop(players[0]);
					}//打开商店
					else if (msg.x >= 50 * windowasp &&
						msg.x <= 100 * windowasp &&
						msg.y >= 430 * windowasp &&
						msg.y <= 480 * windowasp) {
						setfillcolor(WHITE);
						solidrectangle(0, 380, 250, 410);
						setfillcolor(RGB(0x3F, 0x48, 0xCC));
						solidrectangle(0, 570, 680, 600);
						FlushBatchDraw();
						Sleep(500);
						players[1].blood -= 1;
						srand(time(NULL));
						kickerchange = true;
					}//踢
					else if (msg.x >= 100 * windowasp &&
						msg.x <= 180 * windowasp &&
						msg.y >= 440 * windowasp &&
						msg.y <= 470 * windowasp &&
						players[0].invertory != -1) {
						if (players[0].invertory != 3) {
							setfillcolor(WHITE);
							for (int i = 0; i < 10; i++) {
								putimage(110 + i * 64, 590 - i * 51, itemmask + players[0].invertory, NOTSRCERASE);
								putimage(110 + i * 64, 590 - i * 51, itemimg + players[0].invertory, SRCINVERT);
								FlushBatchDraw();
								Sleep(100);
								painthitbankmode();
								solidrectangle(110, 590, 190, 620);
							}
						}
						useitem(players[0], players[1]);
					}//使用物品
				}
			}
		}//玩家操作
		else {
			setbkcolor(WHITE);
			setlinestyle(PS_SOLID, 0);
			for (int i = 20; i >= 0; i--) {
				painthitbankmode();
				putimage(i * 22, 260, &bankboommask, NOTSRCERASE);
				putimage(i * 22, 260, &bankboomimg, SRCINVERT);
				FlushBatchDraw();
				Sleep(100);
			}
			players[0].blood -= 5;
			kickerchange = true;
		}//AI操作
		if (kickerchange) {
			round += 1;
			if (round % 5 == 0) {
				players[1].kicker = true;
				players[0].kicker = false;
			}
			else {
				players[0].kicker = true;
				players[1].kicker = false;
			}
			buffdoer(players[0]);
			buffdoer(players[1]);
			flushmessage(EX_MOUSE);
		}//buff执行&踢者变更
		Sleep(10);
	}
	if (players[0].blood > 0) {
		cleardevice();
		settextstyle(100, 0, "楷体");
		outtextxy(250, 150, "你赢了");
		settextstyle(30, 0, "楷体");
		int getmoney = 100;
		userdatas[userdatacount].money += getmoney;
		char getmoneyoutputbuffer[30];
		sprintf(getmoneyoutputbuffer, "本局收获 %d 脚脚钱", getmoney);
		outtextxy(280, 300, getmoneyoutputbuffer);
	}
	else {
		cleardevice();
		settextstyle(100, 0, "楷体");
		outtextxy(250, 150, "你输了");
	}
	settextstyle(25, 0, "楷体");
	outtextxy(312, 560, "三秒后返回主页");
	FlushBatchDraw();
	Sleep(3000);
	flushmessage(EX_MOUSE);
}