#include "load.h"

//初始化
void load() {
	//日志: 启动
	addlog(info, "脚脚大战启动中");
	//加载设置
	if (Jfreopen("config/opinions.txt", "r", stdin)) {
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
	if (Jfreopen("config/user.data", "r", stdin)) {
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
	}//加载物品图片
	Jloadimage(&bankboomimg, "assets/pictures/bank_boom.png");
	Jloadimage(&bankboommask, "assets/pictures/bank_boom_mask.png");
	for (int i = 0; i < countofnpctype; i++) {
		char npcimgpath[30];
		char npcmaskpath[35];
		sprintf(npcimgpath, "assets/pictures/NPC/%d.png", i);
		sprintf(npcmaskpath, "assets/pictures/NPC_mask/%d.png", i);
		Jloadimage(NPCskinimg + i, npcimgpath);
		Jloadimage(NPCskinmask + i, npcmaskpath);
	}//加载NPC图片
	Jloadimage(&exitbtnimg, "assets/pictures/exit.png");
	Jloadimage(&exitbtnmask, "assets/pictures/exit_mask.png");
	//将输入句柄返回控制台
	freopen("CON", "r", stdin);
	//写日志
	freopen("config/latest.log", "w", stdout);
	for (int i = 0; i < logs.size(); i++) {
		char logtime[20] = { 0 };
		sprintf(logtime, "%d:%d:%d",
			logs[i].time / HOURSECONDS + CNTIMEAREA,
			logs[i].time % HOURSECONDS / MINSECONDS,
			logs[i].time % MINSECONDS
		);
		char logcls[10] = { 0 };
		if (logs[i].logclass == error) {
			sprintf(logcls, "%s", "ERROR");
		}
		else if (logs[i].logclass == info) {
			sprintf(logcls, "%s", "INFO");
		}
		char logdata[MAX_PATH + 10] = { 0 };
		StringTochars(logs[i].data, logdata);
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