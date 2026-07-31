#include "headfile.h"

//登录
void login() {
	bool logined = false;
	IMAGE loginimg;
	loadimage(&loginimg, "assets/pictures/login.png");
	while (!logined) {
		putimage(0, 0, &loginimg);
		FlushBatchDraw();//渲染窗口
		ExMessage msg;
		if (peekmessage(&msg)) {
			if (msg.message == WM_LBUTTONUP) {
				if (msg.x >= 100 && msg.x <= 800 - 100 && msg.y >= 150 && msg.y <= 600 - 150 - 150) {
					//输入脚脚号&密码
					char loginusernum[25];
					char loginuserpasswd[25];
					InputBox(loginusernum, 20, "请输入脚脚号", "登录");
					InputBox(loginuserpasswd, 20, "请输入密码", "登录");
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
								MessageBox(NULL, "登录成功", "登录成功", 0x0000000L);
							}
						}
					}
					if (!logined) {
						MessageBox(NULL, "登录失败", "登录失败", 0x0000000L);
					}
				}//登录
				else if (msg.x >= 100 && msg.x <= 800 - 100 && msg.y >= 150 + 150 && msg.y <= 600 - 150) {
					//输入脚脚号&密码
					char newusername[25];
					char newusernum[25];
					char newuserpasswd[25];
					InputBox(newusername, 20, "请输入新账户的脚脚名", "注册");
					InputBox(newusernum, 20, "请输入新账户的脚脚号", "注册");
					InputBox(newuserpasswd, 20, "请输入新账户的密码", "注册");
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
								MessageBox(NULL, "注册成功", "注册成功", 0x0000000L);
							}
						}
					}
					if (!logined) {
						MessageBox(NULL, "注册失败", "注册失败", 0x0000000L);
					}
				}
			}
		}//检测键盘输入
		Sleep(10);
	}
}
//buff效果实施
void buffdoer(playerdata &player) {
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
void useitem(playerdata &itemuser, playerdata &itemeater) {
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
		sprintf(pr2technologybuffer, "金币:%d\n物品在商店中的位置:第%d个\nbuff剩余生效时间:%d回合", itemeater.coin, itemeater.invertory + 1, itemeater.bufftime);
		MessageBox(NULL, pr2technologybuffer, "对手信息", 0x0000000L);
		break;
	case 3://面包
		itemuser.blood += 1;
	default:
		break;
	}
	itemuser.invertory = -1;
}
//商店
void shop(playerdata& player) {
	bool buyed = false;
	while (!buyed) {
		//渲染
		cleardevice();
		for (int i = 0; i < countofitems; i++) {
			IMAGE itemimg;
			char itemimgfileway[30];
			sprintf(itemimgfileway, "assets/pictures/items/%d.png", i);
			loadimage(&itemimg, itemimgfileway);
			putimage(0 + 80 * (i % 8), 0 + 50 * (i / 8), &itemimg);
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
		FlushBatchDraw();
		//监测鼠标输入
		ExMessage msg;
		if (peekmessage(&msg, EX_MOUSE)) {
			if (msg.message == WM_LBUTTONUP) {
				if (msg.x >= 0 && msg.x <= 640 && msg.x / 80 + msg.y / 50 * 8 < countofitems) {
					if (player.coin >= coinsofpayitems[msg.x / 80 + msg.y / 50 * 8]) {
						player.coin -= coinsofpayitems[msg.x / 80 + msg.y / 50 * 8];
						player.invertory = msg.x / 80 + msg.y / 50 * 8;
						buyed = true;
					}
				}//购买
				else {
					buyed = true;
				}//退出
			}
		}
		flushmessage();
		Sleep(10);
	}
}
//独立模式
class plyr1_fortem {
	playerdata players[2];//玩家数据

	//独立模式渲染
	void paintoneplayermode() {
		IMAGE oneprmodeimg;
		loadimage(&oneprmodeimg, "assets/pictures/oneplayermode.png");
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
			IMAGE itemimg;
			char itemimgfileway[30];
			sprintf(itemimgfileway, "assets/pictures/items/%d.png", players[0].invertory);
			loadimage(&itemimg, itemimgfileway);
			putimage(110, 510, &itemimg);
		}//渲染物品栏
		if (players[1].kicker) {
			setfillcolor(WHITE);
			solidrectangle(0, 600 - 150, 800, 600);
		}
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
			bool kickerchange = false;//回合是否更新
			//渲染
			paintoneplayermode();
			//玩家或AI操作
			if (players[0].kicker) {
				ExMessage msg;
				if (peekmessage(&msg)) {
					if (msg.message == WM_LBUTTONUP) {
						if (msg.x >= 0 && msg.x <= 50 && msg.y >= 600 - 100 && msg.y <= 600 - 50) {
							shop(players[0]);
							kickerchange = true;
						}//打开商店
						else if (msg.x >= 50 && msg.x <= 50 + 50 && msg.y >= 600 - 100 && msg.y <= 600 - 50) {
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
						else if (msg.x >= 100 && msg.x <= 100 + 80 && msg.y >= 600 - 90 && msg.y <= 600 - 60) {
							if (players[0].invertory != 3) {
								IMAGE itemimg;
								char itemimgfileway[30];
								sprintf(itemimgfileway, "assets/pictures/items/%d.png", players[0].invertory);
								loadimage(&itemimg, itemimgfileway);
								setfillcolor(WHITE);
								for (int i = 0; i < 10; i++) {
									putimage(110 + i * 64, 590 - i * 51, &itemimg);
									FlushBatchDraw();
									Sleep(100);
									paintoneplayermode();
									solidrectangle(110, 590, 190, 620);
								}
							}
							
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
						IMAGE itemimg;
						char itemimgfileway[30];
						sprintf(itemimgfileway, "assets/pictures/items/%d.png", players[0].invertory);
						loadimage(&itemimg, itemimgfileway);
						setfillcolor(WHITE);
						for (int i = 9; i >= 0; i--) {
							putimage(110 + i * 64, i * 51 + 90, &itemimg);
							FlushBatchDraw();
							Sleep(100);
							paintoneplayermode();
							solidrectangle(110, 590, 190, 620);
						}
					}
					useitem(players[1], players[0]);
					kickerchange = true;
				}//使用物品
				else if (coinsofpayitems[((rand() + 162) * rand()) % 4] <= players[1].coin) {
					Sleep((rand() * (rand() + 1965) * (time(NULL) % 200)) % 1000);
					players[1].invertory = ((rand() + 162) * rand()) % 4;
					if (players[1].invertory == 2){
						if (rand() % 2 == 1) {
							players[1].invertory += 1;
						}
						else {
							players[1].invertory -= 1;
						}
						players[1].coin -= coinsofpayitems[(((rand() + 162) * rand()) % 4 ) + 1 ];
					}
					else{
						players[1].coin -= coinsofpayitems[((rand() + 162) * rand()) % 4];
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
			flushmessage(EX_MOUSE);
			Sleep(10);
			if (kickerchange) {
				players[0].kicker = !players[0].kicker;
				players[1].kicker = !players[1].kicker;
				buffdoer(players[0]);
				buffdoer(players[1]);
			}//buff执行
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
	playerdata players[4];//玩家数据

	//PK模式渲染
	void paintpkmode() {
		setlinestyle(PS_SOLID, 1);
	}
public:
	//PK模式逻辑
	void dopkmode() {

	}
};
//打银行
class plyrwithbank {
	playerdata players[2];//玩家数据&银行数据
	int round = 0;//回合数

	//打银行渲染
	void painthitbankmode() {
		IMAGE hitbankmodeimg;
		loadimage(&hitbankmodeimg, "assets/pictures/hitbankmode.png");
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
			IMAGE itemimg;
			char itemimgfileway[30];
			sprintf(itemimgfileway, "assets/pictures/items/%d.png", players[0].invertory);
			loadimage(&itemimg, itemimgfileway);
			putimage(110, 440, &itemimg);
		}//渲染物品栏
		if (players[1].kicker) {
			setfillcolor(WHITE);
			solidrectangle(0, 430, 150, 530);
		}
		FlushBatchDraw();
	}
	//打银行启动资金兑换逻辑
	void dohitbankprepare() {
		bool prepareok = false;
		while(!prepareok){
			char coinsinputbuffer[12];
			InputBox(coinsinputbuffer, 11, "1脚脚币=50金币（50%手续费）", "启动资金投入", 0, 0, 0, false);
			bool inputisok = true;
			for (int i = 0; coinsinputbuffer[i+1] != '\0'; i++) {
				if (!((int(coinsinputbuffer[i])) >= 48 && (int(coinsinputbuffer[i])) <= 57)) {
					inputisok = false;
				}
			}
			if (inputisok) {
				int temp = 0;
				sscanf(coinsinputbuffer, "%d", &temp);
				if (temp < userdatas[userdatacount].coins) {
					players[0].coin = temp * 50;
					userdatas[userdatacount].coins -= temp;
					prepareok = true;
				}
				else{
					MessageBoxA(NULL, "你没钱!!!", "投入失败", 0x00000000L);
				}
			}
			else{
				MessageBoxA(NULL, "NAN!!!", "投入失败",0x00000000L);
			}
		}
	}
public:
	//打银行逻辑
	void dohitbankmode() {
		dohitbankprepare();
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
						if (msg.x >= 0 && msg.x <= 50 && msg.y >= 430 && msg.y <= 480) {
							shop(players[0]);
						}//打开商店
						else if (msg.x >= 50 && msg.x <= 50 + 50 && msg.y >= 430 && msg.y <= 480) {
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
						else if (msg.x >= 100 && msg.x <= 100 + 80 && msg.y >= 440 && msg.y <= 470) {
							if (players[0].invertory != 3) {
								IMAGE itemimg;
								char itemimgfileway[30];
								sprintf(itemimgfileway, "assets/pictures/items/%d.png", players[0].invertory);
								loadimage(&itemimg, itemimgfileway);
								setfillcolor(WHITE);
								for (int i = 0; i < 10; i++) {
									putimage(110 + i * 64, 590 - i * 51, &itemimg);
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
				IMAGE bankboomimg;
				setbkcolor(WHITE);
				setlinestyle(PS_SOLID, 0);
				loadimage(&bankboomimg, "assets/pictures/bank_boom.png");
				for (int i = 20; i >= 0; i--) {
					painthitbankmode();
					putimage(i * 22, 260, &bankboomimg);
					FlushBatchDraw();
					Sleep(100);
				}
				players[0].blood -= 5;
				kickerchange = true;
			}//AI操作
			flushmessage(EX_MOUSE);
			Sleep(10);
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
			}//buff执行&踢者变更
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
//主菜单
void menu() {
	while (true) {
		//渲染
		IMAGE menuimg;
		loadimage(&menuimg, "assets/pictures/menu.png");
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
		FlushBatchDraw();
		//保存
		freopen("config/user.data", "w", stdout);
		for (int i = 0; i < 100; i++) {
			printf("%s %s %s %d %d\n", userdatas[i].username, userdatas[i].userid, userdatas[i].password, userdatas[i].coins, userdatas[i].money);
		}
		fclose(stdout);
		//监测鼠标
		ExMessage msg;
		if (peekmessage(&msg)) {
			if (msg.message == WM_LBUTTONUP) {
				if (msg.x >= 0 && msg.x <= 800 / 3 && msg.y >= 200 && msg.y <= 500) {
					plyr1_fortem oneplayermode;
					oneplayermode.dooneplayermode();
				}
				else if (msg.x >= 800 / 3 && msg.x <= 800 / 3 * 2 && msg.y >= 200 && msg.y <= 500) {
					plyr2_fortem pkmode;
					pkmode.dopkmode();
				}
				else if (msg.x >= 800 / 3 * 2 && msg.x <= 800 && msg.y >= 200 && msg.y <= 500) {
					plyrwithbank hitbankmode;
					hitbankmode.dohitbankmode();
				}
				else if (msg.x >= 170 && msg.x <= 200 && msg.y >= 15 && msg.y <= 45) {
					if (userdatas[userdatacount].money >= 10) {
						userdatas[userdatacount].coins += 1;
						userdatas[userdatacount].money -= 10;
					}
				}
			}
		}
		Sleep(10);
	}
}
//初始化
void load() {
	freopen("config/user.data", "r", stdin);
	for (int i = 0; i < 100; i++) {
		scanf("%s %s %s %d %d\n", userdatas[i].username, userdatas[i].userid, userdatas[i].password, &userdatas[i].coins, &userdatas[i].money);
	}
	fclose(stdin);//加载账户信息
	freopen("config/coinofbuyitem.txt", "r", stdin);
	for (int i = 0; i < countofitems; i++) {
		scanf("%d", &coinsofpayitems[i]);
	}
	fclose(stdin);
	initgraph(800, 600);
	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, "Feet_Big_War v0.5");//修改标题
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	BeginBatchDraw();
}
int main() {
	load();//初始化
	login();//登录
	menu();//主菜单
}
