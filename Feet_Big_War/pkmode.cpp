#include "pkmode.h"

//PK模式回合变更
void plyr2_fortem::kickerchangedoer() {
	for (int i = 0; i < 4; i++) {
		kicker = (kicker + 1) % 4;
		if (players[kicker].blood > 0) {
			players[kicker].kicker = true;
			break;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (i != kicker) {
			players[i].kicker = false;
		}
	}
	buffdoer(players[0]);
	buffdoer(players[1]);
	buffdoer(players[2]);
	buffdoer(players[3]);
}
//PK模式渲染
void plyr2_fortem::paintpkmode() {
	putimage(0, 0, &pkmodeimg);//渲染场景
	setfillcolor(RGB(0x3F, 0x48, 0xCC));
	solidrectangle(0, 140, 250, 160);//渲染己方腿
	solidrectangle(0, 340, 250, 360);//渲染己方腿
	setfillcolor(RGB(0x22, 0xB1, 0x4C));
	solidrectangle(800 - 250, 140, 800, 160);//渲染对手腿
	solidrectangle(800 - 250, 340, 800, 360);//渲染对手腿
	setfillcolor(WHITE);
	setlinecolor(RGB(0x3F, 0x48, 0xCC));
	setlinestyle(PS_SOLID, 5);
	fillroundrect(0, 12, players[1].blood * 12, 32, 10, 10);//渲染己方血条
	fillroundrect(0, 222, players[0].blood * 12, 242, 10, 10);//渲染己方血条
	setlinecolor(RGB(0x22, 0xB1, 0x4C));
	fillroundrect(800 - players[2].blood * 12, 12, 800, 32, 10, 10);//渲染对手血条
	fillroundrect(800 - players[3].blood * 12, 222, 800, 242, 10, 10);//渲染对手血条
	settextstyle(40, 0, "楷体");
	char player0coinoutputbuffer[6];
	sprintf(player0coinoutputbuffer, "：%d", players[0].coin);
	outtextxy(50, 600 - 45, player0coinoutputbuffer);//渲染金币数量
	if (players[0].invertory != -1) {
		putimage(110, 510, itemimg + players[0].invertory);
	}//渲染物品栏
	if (!players[0].kicker) {
		setfillcolor(WHITE);
		solidrectangle(0, 600 - 150, 800, 600);
	}
	skinPKGdoer(3);
	FlushBatchDraw();
}
//PK模式逻辑
void plyr2_fortem::dopkmode() {
	//判断谁先手
	srand(time(NULL));
	kicker = rand() % 4;
	players[kicker].kicker = true;
	//游戏过程
	while ((players[0].blood > 0 || players[1].blood > 0) && (players[2].blood > 0 || players[3].blood > 0)) {
		ExMessage msg;
		bool kickerchange = false;//回合是否更新
		//渲染
		paintpkmode();
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
						solidrectangle(0, 340, 250, 360);
						setfillcolor(RGB(0x3F, 0x48, 0xCC));
						MB_CHOOSE mbc = MessageBox(GetHWnd(),
							"踢哪个对手?（是则为上方对手，否则为下方对手）",
							"选择被踢者",
							MB_YESNOCANCEL | MB_SYSTEMMODAL);
						if (mbc == IDYES) {
							POINT points[] = { { 0, 310 }, { 0, 330 }, { 800, 130 }, { 800, 110 } };
							solidpolygon(points, 4);
							players[2].blood -= 1;
							FlushBatchDraw();
							Sleep(500);
							srand(time(NULL));
							players[0].coin += rand() % 11 + 5;
							kickerchange = true;
						}//踢上方对手
						else if (mbc == IDNO) {
							POINT points[] = { { 0, 310 }, { 0, 330 }, { 800, 330 } ,{ 800, 310 } };
							solidpolygon(points, 4);
							players[3].blood -= 1;
							FlushBatchDraw();
							Sleep(500);
							srand(time(NULL));
							players[0].coin += rand() % 11 + 5;
							kickerchange = true;
						}//踢下方对手
					}//踢
					else if (msg.x >= 100 * windowasp &&
						msg.x <= 180 * windowasp &&
						msg.y >= 510 * windowasp &&
						msg.y <= 540 * windowasp &&
						players[0].invertory != -1) {
						if (players[0].invertory != 3/* 过滤物品 */) {
							MB_CHOOSE mbc = MessageBox(GetHWnd(),
								"对哪个对手使用物品?（是则为上方对手，否则为下方对手）",
								"选择被物品砸者",
								MB_YESNOCANCEL | MB_SYSTEMMODAL);
							if (mbc == IDYES) {
								setfillcolor(WHITE);
								for (int i = 0; i < 10; i++) {
									putimage(110 + i * 64, 590 - i * 64, itemmask + players[0].invertory, NOTSRCERASE);
									putimage(110 + i * 64, 590 - i * 64, itemimg + players[0].invertory, SRCINVERT);
									FlushBatchDraw();
									Sleep(100);
									paintpkmode();
									solidrectangle(110, 590, 190, 620);
								}//物品使用动画
								useitem(players[0], players[2]);
							}//砸上方对手
							else if (mbc == IDNO) {
								setfillcolor(WHITE);
								for (int i = 0; i < 10; i++) {
									putimage(110 + i * 64, 590 - i * 41, itemmask + players[0].invertory, NOTSRCERASE);
									putimage(110 + i * 64, 590 - i * 41, itemimg + players[0].invertory, SRCINVERT);
									FlushBatchDraw();
									Sleep(100);
									paintpkmode();
									solidrectangle(110, 590, 190, 620);
								}//物品使用动画
								useitem(players[0], players[3]);
							}//砸下方对手
						}
						else {
							useitem(players[0], players[0]);
						}//食用面包
						kickerchange = true;
					}//使用物品
				}
			}
		}//玩家操作
		else if (players[1].kicker) {
			srand(time(NULL));
			Sleep((rand() * (rand() + 1965) * (time(NULL) % 200)) % 500);//思考时间
			if (players[1].invertory != -1) {
				if (players[1].invertory != 3) {
					srand(time(NULL));
					short throw2who = rand() % 2;//扔给谁
					if (players[throw2who + 2].blood <= 0) {
						throw2who = (throw2who + 1) % 2;
					}
					setfillcolor(WHITE);
					if (throw2who == 0 && players[2].blood > 0) {
						for (int i = 0; i < 10; i++) {
							putimage(100 + i * 55, 160 - i * 13, itemmask + players[1].invertory, NOTSRCERASE);
							putimage(100 + i * 55, 160 - i * 13, itemimg + players[1].invertory, SRCINVERT);
							FlushBatchDraw();
							Sleep(100);
							paintpkmode();
						}//物品使用动画
						useitem(players[1], players[2]);
					}//甩物品给右上
					else  if (throw2who == 1 && players[3].blood > 0) {
						for (int i = 0; i < 10; i++) {
							putimage(100 + i * 55, 160 + i * 7, itemmask + players[1].invertory, NOTSRCERASE);
							putimage(100 + i * 55, 160 + i * 7, itemimg + players[1].invertory, SRCINVERT);
							FlushBatchDraw();
							Sleep(100);
							paintpkmode();
						}//物品使用动画
						useitem(players[1], players[3]);
					}//甩物品给右下
				}
				else {
					useitem(players[1], players[1]);
				}
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
				}//不买望远镜
				else {
					players[1].coin -= coinsofpayitems[((rand() + 162) * rand()) % countofitems];
				}
				kickerchange = true;
			}//购买物品
			else {
				setfillcolor(WHITE);
				solidrectangle(0, 140, 250, 160);
				setfillcolor(RGB(0x3F, 0x48, 0xCC));
				srand(time(NULL));
				short kickwho = rand() % 2;
				if (players[kickwho + 2].blood <= 0) {
					kickwho = (kickwho + 1) % 2;
				}
				if (kickwho == 0 && players[2].blood > 0) {
					POINT points[] = { { 0, 110 }, { 0, 130 }, { 800, 130 }, { 800, 110 } };
					solidpolygon(points, 4);
					players[2].blood -= 1;
					FlushBatchDraw();
					Sleep(500);
					srand(time(NULL));
					players[1].coin += rand() % 11 + 5;
					kickerchange = true;
				}//踢上方对手
				else if (kickwho == 1 && players[3].blood > 0) {
					POINT points[] = { { 0, 110 }, { 0, 130 }, { 800, 330 } ,{ 800, 310 } };
					solidpolygon(points, 4);
					players[3].blood -= 1;
					FlushBatchDraw();
					Sleep(500);
					srand(time(NULL));
					players[1].coin += rand() % 11 + 5;
					kickerchange = true;
				}//踢下方对手
			}//踢
			kickerchange = true;
		}//左上AI操作
		else if (players[2].kicker) {
			srand(time(NULL));
			Sleep((rand() * (rand() + 1965) * (time(NULL) % 200)) % 500);//思考时间
			if (players[2].invertory != -1) {
				if (players[2].invertory != 3) {
					srand(time(NULL));
					short throw2who = rand() % 2;//扔给谁
					if (players[(throw2who + 1) % 2].blood <= 0) {
						throw2who = (throw2who + 1) % 2;
					}
					setfillcolor(WHITE);
					if (throw2who == 0 && players[1].blood > 0) {
						for (int i = 0; i < 10; i++) {
							putimage(650 - i * 55, 160 - i * 13, itemmask + players[2].invertory, NOTSRCERASE);
							putimage(650 - i * 55, 160 - i * 13, itemimg + players[2].invertory, SRCINVERT);
							FlushBatchDraw();
							Sleep(100);
							paintpkmode();
						}//物品使用动画
						useitem(players[2], players[1]);
					}//甩物品给左上
					else if (throw2who == 1 && players[0].blood > 0) {
						for (int i = 0; i < 10; i++) {
							putimage(650 - i * 55, 160 + i * 9, itemmask + players[2].invertory, NOTSRCERASE);
							putimage(650 - i * 55, 160 + i * 9, itemimg + players[2].invertory, SRCINVERT);
							FlushBatchDraw();
							Sleep(100);
							paintpkmode();
						}//物品使用动画
						useitem(players[2], players[0]);
					}//甩物品给左下
				}
				else {
					useitem(players[2], players[2]);
				}
				kickerchange = true;
			}//使用物品
			else if (coinsofpayitems[((rand() + 162) * rand()) % countofitems] <= players[2].coin) {
				Sleep((rand() * (rand() + 1965) * (time(NULL) % 200)) % 1000);
				players[2].invertory = ((rand() + 162) * rand()) % countofitems;
				if (players[2].invertory == 2) {
					if (rand() % 2 == 1) {
						players[2].invertory += 1;
					}
					else {
						players[2].invertory -= 1;
					}
					players[2].coin -= coinsofpayitems[(((rand() + 162) * rand()) % countofitems) + 1];
				}//不买望远镜
				else {
					players[2].coin -= coinsofpayitems[((rand() + 162) * rand()) % countofitems];
				}
				kickerchange = true;
			}//购买物品
			else {
				setfillcolor(WHITE);
				solidrectangle(800 - 250, 140, 800, 160);
				setfillcolor(RGB(0x22, 0xB1, 0x4C));
				srand(time(NULL));
				short kickwho = rand() % 2;
				if (players[(kickwho + 1) % 2].blood <= 0) {
					kickwho = (kickwho + 1) % 2;
				}
				if (kickwho == 0 && players[1].blood > 0) {
					POINT points[] = { { 800, 130 }, { 800, 110 }, { 0, 110 }, { 0, 130 } };
					solidpolygon(points, 4);
					players[1].blood -= 1;
					FlushBatchDraw();
					Sleep(500);
					srand(time(NULL));
					players[2].coin += rand() % 11 + 5;
					kickerchange = true;
				}//踢上方对手
				else  if (kickwho == 1 && players[0].blood > 0) {
					POINT points[] = { { 800, 130 }, { 800, 110 }, { 0, 310 }, { 0, 330 } };
					solidpolygon(points, 4);
					players[0].blood -= 1;
					FlushBatchDraw();
					Sleep(500);
					srand(time(NULL));
					players[2].coin += rand() % 11 + 5;
					kickerchange = true;
				}//踢下方对手
			}//踢
			kickerchange = true;
		}//右上AI操作
		else if (players[3].kicker) {
			srand(time(NULL));
			Sleep((rand() * (rand() + 1965) * (time(NULL) % 200)) % 500);//思考时间
			if (players[3].invertory != -1) {
				if (players[3].invertory != 3) {
					srand(time(NULL));
					short throw2who = rand() % 2;//扔给谁
					if (players[(throw2who + 1) % 2].blood <= 0) {
						throw2who = (throw2who + 1) % 2;
					}
					setfillcolor(WHITE);
					if (throw2who == 0 && players[1].blood > 0) {
						for (int i = 0; i < 10; i++) {
							putimage(650 - i * 55, 360 - i * 31, itemmask + players[3].invertory, NOTSRCERASE);
							putimage(650 - i * 55, 360 - i * 31, itemimg + players[3].invertory, SRCINVERT);
							FlushBatchDraw();
							Sleep(100);
							paintpkmode();
						}//物品使用动画
						useitem(players[3], players[1]);
					}//甩物品给左上
					else  if (throw2who == 1 && players[0].blood > 0) {
						for (int i = 0; i < 10; i++) {
							putimage(650 - i * 55, 360 - i * 11, itemmask + players[3].invertory, NOTSRCERASE);
							putimage(650 - i * 55, 360 - i * 11, itemimg + players[3].invertory, SRCINVERT);
							FlushBatchDraw();
							Sleep(100);
							paintpkmode();
						}//物品使用动画
						useitem(players[3], players[0]);
					}//甩物品给左下
				}
				else {
					useitem(players[3], players[3]);
				}
				kickerchange = true;
			}//使用物品
			else if (coinsofpayitems[((rand() + 162) * rand()) % countofitems] <= players[3].coin) {
				Sleep((rand() * (rand() + 1965) * (time(NULL) % 200)) % 1000);
				players[3].invertory = ((rand() + 162) * rand()) % countofitems;
				if (players[3].invertory == 2) {
					if (rand() % 2 == 1) {
						players[3].invertory += 1;
					}
					else {
						players[3].invertory -= 1;
					}
					players[3].coin -= coinsofpayitems[(((rand() + 162) * rand()) % countofitems) + 1];
				}//不买望远镜
				else {
					players[3].coin -= coinsofpayitems[((rand() + 162) * rand()) % countofitems];
				}
				kickerchange = true;
			}//购买物品
			else {
				setfillcolor(WHITE);
				solidrectangle(800 - 250, 340, 800, 360);
				setfillcolor(RGB(0x22, 0xB1, 0x4C));
				srand(time(NULL));
				short kickwho = rand() % 2;
				if (players[(kickwho + 1) % 2].blood <= 0) {
					kickwho = (kickwho + 1) % 2;
				}
				if (kickwho == 0 && players[1].blood > 0) {
					POINT points[] = { { 800, 330 }, { 800, 310 }, { 0, 110 }, { 0, 130 } };
					solidpolygon(points, 4);
					players[1].blood -= 1;
					FlushBatchDraw();
					Sleep(500);
					srand(time(NULL));
					players[3].coin += rand() % 11 + 5;
					kickerchange = true;
				}//踢上方对手
				else  if (kickwho == 1 && players[0].blood > 0) {
					POINT points[] = { { 800, 330 }, { 800, 310 }, { 0, 310 }, { 0, 330 } };
					solidpolygon(points, 4);
					players[0].blood -= 1;
					FlushBatchDraw();
					Sleep(500);
					srand(time(NULL));
					players[3].coin += rand() % 11 + 5;
					kickerchange = true;
				}//踢下方对手
			}//踢
			kickerchange = true;
		}//右下AI操作
		if (kickerchange) {
			kickerchangedoer();
			flushmessage(EX_MOUSE);
		}//回合更新
		Sleep(10);
	}
	if (players[0].blood > 0 || players[1].blood > 0) {
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