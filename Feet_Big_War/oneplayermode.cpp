#include "oneplayermode.h"

//独立模式渲染
void plyr1_fortem::paintoneplayermode() {
	putimage(0, 0, &oneprmodeimg);//渲染场景
	setfillcolor(RGB(0x3F, 0x48, 0xCC));
	solidrectangle(0, 380, 250, 410);//渲染己方腿
	setfillcolor(RGB(0x22, 0xB1, 0x4C));
	solidrectangle(800 - 250, 380, 800, 410);//渲染对手腿
	setfillcolor(WHITE);
	setlinecolor(RGB(0x3F, 0x48, 0xCC));
	setlinestyle(PS_SOLID, 5);
	fillroundrect(0, 2, players[0].blood * 12, 20, 10, 10);//渲染己方血条
	setlinecolor(RGB(0x22, 0xB1, 0x4C));
	fillroundrect(800 - players[1].blood * 12, 2, 800, 20, 10, 10);//渲染对手血条
	settextstyle(40, 0, "楷体");
	char player0coinoutputbuffer[6];
	sprintf(player0coinoutputbuffer, "：%d", players[0].coin);
	outtextxy(50, 600 - 45, player0coinoutputbuffer);//渲染金币数量
	if (players[0].invertory != -1) {
		putimage(110, 510, itemimg + players[0].invertory);
	}//渲染物品栏
	if (players[1].kicker) {
		setfillcolor(WHITE);
		solidrectangle(0, 600 - 150, 800, 600);
	}
	skinPKGdoer(2);
	FlushBatchDraw();
}

//独立模式逻辑
void plyr1_fortem::dooneplayermode() {
	//判断谁先手
	srand(time(NULL));
	if (rand() % 2 == 0) {
		players[0].kicker = true;
	}
	else
	{
		players[1].kicker = true;
	}
	//游戏过程
	while (players[0].blood > 0 && players[1].blood > 0) {
		ExMessage msg;
		bool kickerchange = false;//回合是否更新
		//渲染
		paintoneplayermode();
		//玩家或AI操作
		if (players[0].kicker) {
			if (peekmessage(&msg)) {
				if (msg.message == WM_LBUTTONUP) {
					if (msg.x >= 0 * windowasp &&
						msg.x <= 50 * windowasp &&
						msg.y >= 500 * windowasp &&
						msg.y <= 550 * windowasp) {
						shop(players[0]);
						kickerchange = true;
					}//打开商店
					else if (msg.x >= 50 * windowasp &&
						msg.x <= 100 * windowasp &&
						msg.y >= 500 * windowasp &&
						msg.y <= 550 * windowasp) {
						setfillcolor(WHITE);
						solidrectangle(0, 380, 250, 410);
						setfillcolor(RGB(0x3F, 0x48, 0xCC));
						solidrectangle(0, 293, 800, 317);
						FlushBatchDraw();
						Sleep(500);
						players[1].blood -= 1;
						srand(time(NULL));
						players[0].coin += rand() % 11 + 5;
						kickerchange = true;
					}//踢
					else if (msg.x >= 100 * windowasp &&
						msg.x <= 180 * windowasp &&
						msg.y >= 510 * windowasp &&
						msg.y <= 540 * windowasp &&
						players[0].invertory != -1) {
						if (players[0].invertory != 3 && players[0].invertory != -1) {
							setfillcolor(WHITE);
							for (int i = 0; i < 10; i++) {
								putimage(110 + i * 64, 590 - i * 51, itemmask + players[0].invertory, NOTSRCERASE);
								putimage(110 + i * 64, 590 - i * 51, itemimg + players[0].invertory, SRCINVERT);
								FlushBatchDraw();
								Sleep(100);
								paintoneplayermode();
								solidrectangle(110, 590, 190, 620);
							}
						}//物品使用动画
						useitem(players[0], players[1]);
						kickerchange = true;
					}//使用物品
				}
			}
		}//玩家操作
		else {
			srand(time(NULL));
			Sleep((rand() * (rand() + 1965) * (time(NULL) % 200)) % 500);
			if (players[1].invertory != -1) {
				if (players[1].invertory != 3) {
					setfillcolor(WHITE);
					for (int i = 9; i >= 0; i--) {
						putimage(110 + i * 64, i * 51 + 90, itemmask + players[1].invertory, NOTSRCERASE);
						putimage(110 + i * 64, i * 51 + 90, itemimg + players[1].invertory, SRCINVERT);
						FlushBatchDraw();
						Sleep(100);
						paintoneplayermode();
						solidrectangle(110, 590, 190, 620);
					}//物品使用动画
				}
				useitem(players[1], players[0]);
				kickerchange = true;
			}//使用物品
			else if (coinsofpayitems[((rand() + 162) * rand()) % countofitems] <= players[1].coin) {
				Sleep((rand() * (rand() + 1965) * (time(NULL) % 200)) % 1000);
				players[1].invertory = ((rand() + 162) * rand()) % countofitems;
				if (players[1].invertory == 2) {
					if (rand() % 2 == 1) {
						players[1].invertory += 1;
					}
					else {
						players[1].invertory -= 1;
					}
					players[1].coin -= coinsofpayitems[(((rand() + 162) * rand()) % countofitems) + 1];
				}
				else {
					players[1].coin -= coinsofpayitems[((rand() + 162) * rand()) % countofitems];
				}
				kickerchange = true;
			}//购买物品
			else {
				setfillcolor(WHITE);
				solidrectangle(800 - 250, 380, 800, 410);
				setfillcolor(RGB(0x22, 0xB1, 0x4C));
				solidrectangle(0, 293, 800, 317);
				FlushBatchDraw();
				Sleep(500);
				players[1].coin += rand() % 11 + 5;
				players[0].blood -= 1;
				kickerchange = true;
			}//踢
		}//AI操作
		if (kickerchange) {
			players[0].kicker = !players[0].kicker;
			players[1].kicker = !players[1].kicker;
			buffdoer(players[0]);
			buffdoer(players[1]);
			flushmessage(EX_MOUSE);
		}//buff执行
		Sleep(10);
	}
	if (players[0].blood > 0) {
		cleardevice();
		settextstyle(100, 0, "楷体");
		outtextxy(250, 150, "你赢了");
		settextstyle(30, 0, "楷体");
		int getmoney = players[0].coin / 10;
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