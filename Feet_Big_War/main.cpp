#include "headfile.h"
//特效包执行
void skinPKGdoer(short addpoint) {
	for (int i = 0; i < addinspainttasklist[addpoint].size(); i++) {
		if (addinspainttasklist[addpoint][i].task == 0) {
			IMAGE taskimg = { 0 };
			Jloadimage(
				&taskimg, 
				addinspainttasklist[addpoint][i].path, 
				addinspainttasklist[addpoint][i].weight, 
				addinspainttasklist[addpoint][i].height
			);
			putimage(
				addinspainttasklist[addpoint][i].x, 
				addinspainttasklist[addpoint][i].y, 
				&taskimg
			);
		}//图片
		else if (addinspainttasklist[addpoint][i].task == 1) {
			setfillcolor(addinspainttasklist[addpoint][i].color);
			solidrectangle(
				addinspainttasklist[addpoint][i].x,
				addinspainttasklist[addpoint][i].y,
				addinspainttasklist[addpoint][i].cx,
				addinspainttasklist[addpoint][i].cy
			);
		}//矩形
		else if (addinspainttasklist[addpoint][i].task == 2) {
			setfillcolor(addinspainttasklist[addpoint][i].color);
			solidcircle(
				addinspainttasklist[addpoint][i].x,
				addinspainttasklist[addpoint][i].y,
				addinspainttasklist[addpoint][i].r
			);
		}//圆
		else if (addinspainttasklist[addpoint][i].task == 3) {
			settextcolor(addinspainttasklist[addpoint][i].color);
			settextstyle(addinspainttasklist[addpoint][i].fort, 0, "宋体");
			outtextxy(
				addinspainttasklist[addpoint][i].x, 
				addinspainttasklist[addpoint][i].y, 
				addinspainttasklist[addpoint][i].words
			);
		}//文字
	}
}
//登录
void login() {
	bool logined = false;
	while (!logined) {
		putimage(0, 0, &loginimg);
		skinPKGdoer(0);
		FlushBatchDraw();//渲染窗口
		ExMessage msg;
		if (peekmessage(&msg)) {
			if (msg.message == WM_LBUTTONUP) {
				if (msg.x >= 100 * windowasp && 
					msg.x <= 700 * windowasp && 
					msg.y >= 150 * windowasp && 
					msg.y <= 300 * windowasp) {
					//输入脚脚号&密码
					char loginusernum[25];
					char loginuserpasswd[25];
					bool enter = InputBox(loginusernum, 20, "请输入脚脚号", "登录", (LPCTSTR)NULL, 0, 0, false);
					if (!enter) {
						continue;
					}
					bool enter2 = InputBox(loginuserpasswd, 20, "请输入密码", "登录", (LPCTSTR)NULL, 0, 0, false);
					if (!enter2) {
						continue;
					}
					//脚脚号&密码合规性检查
					string loginusernumbuffer = loginusernum;
					string loginuserpasswdbuffer = loginuserpasswd;
					bool wordsinrule = true;//脚脚号&密码是否合规
					if (loginusernumbuffer == "NULL" || loginuserpasswdbuffer == "NULL") {
						wordsinrule = false;
					}//检查是否为NULL
					if (loginusernumbuffer == "\0" || loginuserpasswdbuffer == "\0") {
						wordsinrule = false;
					}//检查是否为空
					for (int i = 0; i < 25 && loginusernum[i] != '\0'; i++) {
						if (loginusernum[i] == ' ') {
							wordsinrule = false;
						}
					}
					for (int i = 0; i < 25 && loginuserpasswd[i] != '\0'; i++) {
						if (loginuserpasswd[i] == ' ') {
							wordsinrule = false;
						}
					}//检查是否有空格
					//对号入座
					if (wordsinrule) {
						for (int i = 0; i < 100; i++) {
							string usernumbuffer = userdatas[i].userid;
							string userpasswdbuffer = userdatas[i].password;
							if (loginusernumbuffer == usernumbuffer && loginuserpasswdbuffer == userpasswdbuffer) {
								userdatacount = i;
								logined = true;
								MessageBox(hWnd, "登录成功", "登录成功", MB_OK | MB_SYSTEMMODAL);
							}
						}
					}
					if (!logined) {
						MessageBox(hWnd, "登录失败", "登录失败", MB_OK | MB_SYSTEMMODAL);
					}
				}//登录
				else if (msg.x >= 100 * windowasp && 
					msg.x <= 700 * windowasp && 
					msg.y >= 300 * windowasp && 
					msg.y <= 550 * windowasp) {
					//输入脚脚号&密码
					char newusername[25];
					char newusernum[25];
					char newuserpasswd[25];
					bool enter = InputBox(newusername, 20, "请输入新账户的脚脚名", "注册", (LPCTSTR)NULL, 0, 0, false);
					if (!enter) {
						continue;
					}
					bool enter2 = InputBox(newusernum, 20, "请输入新账户的脚脚号", "注册", (LPCTSTR)NULL, 0, 0, false);
					if (!enter2) {
						continue;
					}
					bool enter3 = InputBox(newuserpasswd, 20, "请输入新账户的密码", "注册", (LPCTSTR)NULL, 0, 0, false);
					if (!enter3) {
						continue;
					}
					//脚脚名&号&密码合规性检查
					string newusernamebuffer = newusername;
					string newusernumbuffer = newusernum;
					string newuserpasswdbuffer = newuserpasswd;
					bool wordsinrule = true;//脚脚号&密码是否合规
					if (newusernumbuffer == "NULL" || newuserpasswdbuffer == "NULL" || newusernamebuffer == "NULL") {
						wordsinrule = false;
					}//检查是否为NULL
					if (newusernumbuffer == "\0" || newuserpasswdbuffer == "\0" || newusernamebuffer =="\0") {
						wordsinrule = false;
					}//检查是否为空
					for (int i = 0; i < 25 && newusername[i] != '\0'; i++) {
						if (newusername[i] == ' ') {
							wordsinrule = false;
						}
					}
					for (int i = 0; i < 25 && newusernum[i] != '\0'; i++) {
						if (newusernum[i] == ' ') {
							wordsinrule = false;
						}
					}
					for (int i = 0; i < 25 && newuserpasswd[i] != '\0'; i++) {
						if (newuserpasswd[i] == ' ') {
							wordsinrule = false;
						}
					}//检查是否有空格
					for (int i = 0; i < 100; i++) {
						string usernumbuffer = userdatas[i].userid;
						if(usernumbuffer == newusernumbuffer){
							wordsinrule = false;
						}
					}//检查是否重复
					//添加账号
					if (wordsinrule) {
						for (int i = 0; i < 100 && logined != true; i++) {
							string usernumbuffer = userdatas[i].userid;
							if (usernumbuffer == "NULL") {
								sprintf(userdatas[i].username, "%s", newusername);
								sprintf(userdatas[i].userid, "%s", newusernum);
								sprintf(userdatas[i].password, "%s", newuserpasswd);
								userdatacount = i;
								logined = true;
								MessageBox(hWnd, "注册成功", "注册成功", MB_OK | MB_SYSTEMMODAL);
							}
						}
					}
					if (!logined) {
						MessageBox(hWnd, "注册失败", "注册失败", MB_OK | MB_SYSTEMMODAL);
					}
				}
			}
		}//检测键盘输入
		Sleep(10);
	}
}
//buff效果实施
void buffdoer(_playerdata &player) {
	if (player.bufftime <= 0) {
		player.buff = -1;
	}
	if (player.buff != -1) {
		if (player.buff == 0) {
			player.blood -= 1;
		}
		player.bufftime -= 1;
	}
}
//物品使用
void useitem(_playerdata &itemuser, _playerdata &itemeater) {
	switch (itemuser.invertory) {
	case 0://冰箱弹
		itemeater.blood -= 2;
		break;
	case 1://淤泥炸弹
		itemeater.buff = 0;
		itemeater.bufftime = 5;
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
//独立模式
class plyr1_fortem {
	_playerdata players[2];//玩家数据 
	//独立模式渲染
	void paintoneplayermode() {
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
public:
	//独立模式逻辑
	void dooneplayermode() {
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
					if (players[1].invertory == 2){
						if (rand() % 2 == 1) {
							players[1].invertory += 1;
						}
						else {
							players[1].invertory -= 1;
						}
						players[1].coin -= coinsofpayitems[(((rand() + 162) * rand()) % countofitems) + 1 ];
					}
					else{
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
};
//PK模式
class plyr2_fortem {
	_playerdata players[4];//玩家数据
	short kicker = 0;//踢人者

	//PK模式渲染
	void paintpkmode() {
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
	//PK模式回合变更
	void kickerchangedoer() {
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
public:
	//PK模式逻辑
	void dopkmode() {
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
							MB_CHOOSE mbc = MessageBox(hWnd, 
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
								MB_CHOOSE mbc = MessageBox(hWnd,
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
			else if(players[1].kicker) {
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
						else if(throw2who == 1 && players[0].blood > 0) {
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
};
//打银行
class plyrwithbank {
	_playerdata players[2];//玩家数据&银行数据
	int round = 0;//回合数

	//打银行渲染
	void painthitbankmode() {
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
		outtextxy(800-300, 40, gunpoweroutputbuffer);
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
	bool dohitbankprepare() {
		bool prepareok = false;
		while(!prepareok){
			char coinsinputbuffer[12];
			bool enter = InputBox(coinsinputbuffer, 11, "1脚脚币=50金币（50%手续费）", "启动资金投入", 0, 0, 0, false);
			if (!enter) {
				return false;
			}
			bool inputisok = true;
			for (int i = 0; coinsinputbuffer[i+1] != '\0'; i++) {
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
				else{
					MessageBox(NULL, "你没钱!!!", "投入失败", MB_SYSTEMMODAL | MB_ICONINFORMATION);
					prepareok = true;
					return false;
				}
			}
			else{
				MessageBox(NULL, "NAN!!!", "投入失败", MB_SYSTEMMODAL | MB_ICONERROR);
				prepareok = true;
				return false;
			}
		}
	}
public:
	//打银行逻辑
	void dohitbankmode() {
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
							msg.y <= 480 * windowasp){
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
};
//设置
void settings() {
	//数据缓存
	_userdata changeuserdatatmp = userdatas[userdatacount];
	float windowasptmp = windowasp;
	bool userischoosing = true;
	while (userischoosing) {
		//渲染
		putimage(0, 0, &settingsimg);
		setfillcolor(LIGHTBLUE);
		solidcircle(170 + (400 * (windowasptmp - 0.5)), 250, 10);//渲染窗口缩放选择圆圈
		settextstyle(50, 0, "楷体");
		outtextxy(220, 40, changeuserdatatmp.username);
		outtextxy(220, 100, changeuserdatatmp.userid);
		for (int i = 0; i < strlen(changeuserdatatmp.password); i++) {
			outtextxy(220 + 25 * i, 160, '*');
		}
		FlushBatchDraw();
		//监测鼠标
		ExMessage msg;
		if (peekmessage(&msg)) {
			if (msg.message == WM_LBUTTONUP) {
				if (msg.x >= 600 * windowasp && 
					msg.x <= 740 * windowasp && 
					msg.y >= 40 * windowasp && 
					msg.y <= 90 * windowasp) {
					char passwdtmp[25] = { 0 };
					bool enter = InputBox(passwdtmp, 20, "请输入密码", "验证身份", (LPCTSTR)NULL, 0, 0, false);
					if (!enter) {
						continue;
					}//身份验证
					if (strcmp(passwdtmp, userdatas[userdatacount].password) == 0) {
						bool enter2 = InputBox(changeuserdatatmp.username, 20, "请输入新游戏名", "验证成功", (LPCTSTR)NULL, 0, 0, false);
						if (!enter2) {
							continue;
						}
					}
				}//编辑游戏名
				else if (msg.x >= 600 * windowasp && 
					msg.x <= 740 * windowasp && 
					msg.y >= 100 * windowasp && 
					msg.y <= 150 * windowasp) {
					char passwdtmp[25] = { 0 };
					bool enter = InputBox(passwdtmp, 20, "请输入密码", "验证身份", (LPCTSTR)NULL, 0, 0, false);
					if (!enter) {
						continue;
					}//身份验证
					if (strcmp(passwdtmp, userdatas[userdatacount].password) == 0) {
						bool enter2 = InputBox(changeuserdatatmp.userid, 20, "请输入新脚脚号", "验证成功", (LPCTSTR)NULL, 0, 0, false);
						if (!enter2) {
							continue;
						}
					}
				}//编辑脚脚号
				else if (msg.x >= 600 * windowasp && 
					msg.x <= 740 * windowasp && 
					msg.y >= 160 * windowasp && 
					msg.y <= 210 * windowasp) {
					char passwdtmp[25] = { 0 };
					bool enter = InputBox(passwdtmp, 20, "请输入密码", "验证身份", (LPCTSTR)NULL, 0, 0, false);
					if (!enter) {
						continue;
					}//身份验证
					if (strcmp(passwdtmp, userdatas[userdatacount].password) == 0) {
						bool enter2 = InputBox(changeuserdatatmp.password, 20, "请输入新密码", "验证成功", (LPCTSTR)NULL, 0, 0, false);
						freopen("CON", "w", stdout);
						std::cout << changeuserdatatmp.password;
						if (!enter2) {
							continue;
						}
					}
				}//编辑密码
				else if (msg.x >= 140 * windowasp && 
					msg.x <= 200 * windowasp && 
					msg.y >= 230 * windowasp && 
					msg.y <= 270 * windowasp) {
					windowasptmp = 0.5;
				}//将窗口缩放设置为50%
				else if (msg.x >= 240 * windowasp && 
					msg.x <= 300 * windowasp && 
					msg.y >= 230 * windowasp && 
					msg.y <= 270 * windowasp) {
					windowasptmp = 0.75;
				}//将窗口缩放设置为75%
				else if (msg.x >= 340 * windowasp && 
					msg.x <= 400 * windowasp && 
					msg.y >= 230 * windowasp && 
					msg.y <= 270 * windowasp) {
					windowasptmp = 1.0;
				}//将窗口缩放设置为100%
				else if (msg.x >= 440 * windowasp && 
					msg.x <= 500 * windowasp && 
					msg.y >= 230 * windowasp && 
					msg.y <= 270 * windowasp) {
					windowasptmp = 1.25;
				}//将窗口缩放设置为125%
				else if (msg.x >= 540 * windowasp && 
					msg.x <= 600 * windowasp && 
					msg.y >= 230 * windowasp &&
					msg.y <= 270 * windowasp) {
					windowasptmp = 1.5;
				}//将窗口缩放设置为150%
				else if (msg.x >= 500 * windowasp && 
					msg.x <= 650 * windowasp && 
					msg.y >= 520 * windowasp && 
					msg.y <= 600 * windowasp) {
					strcpy(userdatas[userdatacount].userid, changeuserdatatmp.userid);
					strcpy(userdatas[userdatacount].username, changeuserdatatmp.username);
					strcpy(userdatas[userdatacount].password, changeuserdatatmp.password);
					windowasp = windowasptmp;
					initgraph(800 * windowasp, 600 * windowasp);
					setaspectratio(windowasp, windowasp);
					freopen("config/opinions.txt", "w", stdout);
					printf("windowasp:%f", windowasp);
					fclose(stdout);
					//加载渲染相关
					Resize(NULL, 800 * windowasp, 600 * windowasp);
					setbkcolor(WHITE);
					settextcolor(BLACK);
					setbkmode(TRANSPARENT);
					BeginBatchDraw();
					userischoosing = false;
				}//确定
				else if (msg.x >= 650 && msg.x <= 800 && msg.y >= 520 && msg.y <= 600) {
					userischoosing = false;
				}//取消
			}
		}
	}
}
//主菜单
void menu() {
	while (true) {
		//渲染
		putimage(0, 0, &menuimg);
		settextstyle(40, 0, "楷体");
		outtextxy(0, 0, userdatas[userdatacount].username);
		settextstyle(30, 0, "楷体");
		char usercoinoutputbuffer[6];
		sprintf(usercoinoutputbuffer, ": %d", userdatas[userdatacount].coins);
		outtextxy(210, 15, usercoinoutputbuffer);
		char usermoneyoutputbuffer[6];
		sprintf(usermoneyoutputbuffer, ": %d", userdatas[userdatacount].money);
		outtextxy(510, 15, usermoneyoutputbuffer);
		skinPKGdoer(1);
		FlushBatchDraw();
		//保存
		freopen("config/user.data", "w", stdout);
		for (int i = 0; i < 100; i++) {
			printf("%s %s %s %d %d\n", 
				userdatas[i].username, 
				userdatas[i].userid, 
				userdatas[i].password, 
				userdatas[i].coins, 
				userdatas[i].money
			);
		}
		fclose(stdout);
		//监测鼠标
		ExMessage msg;
		if (peekmessage(&msg)) {
			if (msg.message == WM_LBUTTONUP) {
				if (msg.x >= 0 * windowasp && 
					msg.x <= 800 / 3 * windowasp && 
					msg.y >= 200 * windowasp && 
					msg.y <= 500 * windowasp) {
					plyr1_fortem oneplayermode;
					oneplayermode.dooneplayermode();
				}//打开独立模式
				else if (msg.x >= 800 / 3 * windowasp && 
					msg.x <= 800 / 3 * 2 * windowasp && 
					msg.y >= 200 * windowasp && 
					msg.y <= 500 * windowasp) {
					plyr2_fortem pkmode;
					pkmode.dopkmode();
				}//打开PK模式
				else if (msg.x >= 800 / 3 * 2 * windowasp && 
					msg.x <= 800 * windowasp && 
					msg.y >= 200 * windowasp && 
					msg.y <= 500 * windowasp) {
					plyrwithbank hitbankmode;
					hitbankmode.dohitbankmode();
				}//打开打银行
				else if (msg.x >= 700 * windowasp && 
					msg.x <= 800 * windowasp && 
					msg.y >= 500 * windowasp && 
					msg.y <= 600 * windowasp) {
					settings();
				}//打开设置
				else if (msg.x >= 170 * windowasp && 
					msg.x <= 200 * windowasp && 
					msg.y >= 15 * windowasp && 
					msg.y <= 45 * windowasp) {
					if (userdatas[userdatacount].money >= 10) {
						userdatas[userdatacount].coins += 1;
						userdatas[userdatacount].money -= 10;
					}
				}//兑换脚脚币
			}
		}
		Sleep(10);
	}
}
//初始化
void load() {
	//日志: 启动
	addlog(info, "脚脚大战启动中");
	//加载设置
	if(Jfreopen("config/opinions.txt", "r", stdin)) {
		scanf("windowasp:%f", &windowasp);
		fclose(stdin);
		freopen("CON", "r", stdin);
	}
	//加载窗口
	initgraph(800 * windowasp, 600 * windowasp);
	setaspectratio(windowasp, windowasp);
	hWnd = GetHWnd();
	SetWindowText(hWnd, "Feet_Big_War v0.9");
	addlog(info, "脚脚大战窗口创建成功");
	//加载渲染相关
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	BeginBatchDraw();
	//加载账户信息
	if(Jfreopen("config/user.data", "r", stdin)) { 
		for (int i = 0; i < 100; i++) {
			scanf("%s %s %s %d %d\n", 
				userdatas[i].username, 
				userdatas[i].userid, 
				userdatas[i].password, 
				&userdatas[i].coins, 
				&userdatas[i].money
			);
		}
		fclose(stdin);
		freopen("CON", "r", stdin);
	}
	//加载物品价格
	if (Jfreopen("config/coinofbuyitem.txt", "r", stdin)) {
		for (int i = 0; i < countofitems; i++) {
			scanf("%d", &coinsofpayitems[i]);
		}
		fclose(stdin);
		freopen("CON", "r", stdin);
	}
	//读取特效包
	for (int i = 0; i < addinpointcount; i++) {
		vector<painttask> null;
		addinspainttasklist.push_back(null);
	}
	vector<string> filelist = EF_GetFileList("addins/", "*.*");//特效包列表
	for (int i = 0; i < filelist.size(); i++) {
		char filepath[300];//特效包文件路径
		char filelisttmp[300] = { 0 };
		StringTochars(filelist[i], filelisttmp);
		sprintf(filepath, "addins/%s", filelisttmp);
		if (Jfreopen(filepath, "r", stdin)) {
			int addpoint = 0;//特效包作用处
			while (std::cin >> addpoint) {
				painttask addinpainttasktmp = { 0 };//特效包读取缓存
				scanf("%d", &addinpainttasktmp.task);
				if (addinpainttasktmp.task == 0) {
					scanf("%d%d%s%d%d\n",
						&addinpainttasktmp.x,
						&addinpainttasktmp.y,
						addinpainttasktmp.path,
						&addinpainttasktmp.weight,
						&addinpainttasktmp.height
					);
				}//图片
				else if (addinpainttasktmp.task == 1) {
					scanf("%d%d%d%d%x\n",
						&addinpainttasktmp.x,
						&addinpainttasktmp.y,
						&addinpainttasktmp.cx,
						&addinpainttasktmp.cy,
						&addinpainttasktmp.color
					);
				}//矩形
				else if (addinpainttasktmp.task == 2) {
					scanf("%d%d%d%x\n",
						&addinpainttasktmp.x,
						&addinpainttasktmp.y,
						&addinpainttasktmp.r,
						&addinpainttasktmp.color
					);
				}//圆
				else if (addinpainttasktmp.task == 3) {
					scanf("%d%d%d%s%x\n",
						&addinpainttasktmp.x,
						&addinpainttasktmp.y,
						&addinpainttasktmp.fort,
						&addinpainttasktmp.words,
						&addinpainttasktmp.color
					);
				}//文字
				addinspainttasklist[addpoint].push_back(addinpainttasktmp);
			}
		}
		fclose(stdin);
		freopen("CON", "r", stdin);
	}//读取特效包
	//加载图片
	Jloadimage(&loginimg, "assets/pictures/login.png");
	Jloadimage(&menuimg, "assets/pictures/menu.png");
	Jloadimage(&settingsimg, "assets/pictures/settings.png");
	Jloadimage(&oneprmodeimg, "assets/pictures/oneplayermode.png");
	Jloadimage(&pkmodeimg, "assets/pictures/pkmode.png");
	Jloadimage(&hitbankmodeimg, "assets/pictures/hitbankmode.png");
	for (int i = 0; i < countofitems; i++) {
		char itemimgpath[30];
		char itemmaskpath[35];
		sprintf(itemimgpath, "assets/pictures/items/%d.png", i);
		sprintf(itemmaskpath, "assets/pictures/items_mask/%d.png", i);
		Jloadimage(itemimg + i, itemimgpath);
		Jloadimage(itemmask + i, itemmaskpath);
	}
	Jloadimage(&bankboomimg, "assets/pictures/bank_boom.png");
	Jloadimage(&bankboommask, "assets/pictures/bank_boom_mask.png");
	//将输入句柄返回控制台
	freopen("CON", "r", stdin);
	//写日志
	freopen("config/latest.log", "w", stdout);
	for (int i = 0; i < logs.size(); i++) {
		char logtime[20] = { 0 };
		sprintf(logtime, "%d:%d:%d", 
			logs[i].time / HOURSECONDS + CNTIMEAREA, 
			logs[i].time% HOURSECONDS / MINSECONDS, 
			logs[i].time% MINSECONDS
		);
		char logcls[10] = { 0 };
		if (logs[i].logclass == error) {
			sprintf(logcls, "%s","ERROR");
		}
		else if (logs[i].logclass == info) {
			sprintf(logcls, "%s", "INFO");
		}
		char logdata[MAX_PATH + 10] = { 0 };
		StringTochars(logs[i].data,logdata);
		printf("[%s]%s: %s\n", logtime, logcls, logdata);
		if (logs[i].logclass == error) {
			willappstart = false;
		}
	}
	fclose(stdout);
	freopen("CON", "w", stdout);
	if (!willappstart) {
		return;
	}
}
int main() {
	load();
	if (!willappstart) {
		MessageBox(hWnd,
			"文件缺失，拒绝启动",
			"启动失败",
			MB_SYSTEMMODAL | MB_ICONERROR
		);
		return 0;
	}
	login();
	menu();
}
