#include "login.h"

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
								MessageBox(GetHWnd(), "登录成功", "登录成功", MB_OK | MB_SYSTEMMODAL);
							}
						}
					}
					if (!logined) {
						MessageBox(GetHWnd(), "登录失败", "登录失败", MB_OK | MB_SYSTEMMODAL);
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
					if (newusernumbuffer == "\0" || newuserpasswdbuffer == "\0" || newusernamebuffer == "\0") {
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
						if (usernumbuffer == newusernumbuffer) {
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
								MessageBox(GetHWnd(), "注册成功", "注册成功", MB_OK | MB_SYSTEMMODAL);
							}
						}
					}
					if (!logined) {
						MessageBox(GetHWnd(), "注册失败", "注册失败", MB_OK | MB_SYSTEMMODAL);
					}
				}
			}
		}//检测键盘输入
		Sleep(10);
	}
}