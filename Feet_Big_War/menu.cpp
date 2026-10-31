#include "menu.h"

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
				else if (msg.x >= 600 * windowasp &&
					msg.x <= 700 * windowasp &&
					msg.y >= 500 * windowasp &&
					msg.y <= 600 * windowasp
					) {
					theadvnteofft feetadvanture;
					feetadvanture.adventuremain();
				}
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
