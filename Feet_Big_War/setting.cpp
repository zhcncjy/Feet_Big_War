#include "setting.h"

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
		skinPKGdoer(6);
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