#include "feetadventure.h"

//脚脚探索渲染
void theadvnteofft::paintavt() {
	setbkcolor(RGB(0x68, 0xA8, 0x3E));
	cleardevice();
	setbkcolor(WHITE);
	for (int i = 0; i < 32; i++) {
		if (NPC[i].type == -1) {
			continue;
		}//筛掉未生成的NPC
		if (NPC[i].x > unusualNPC[0].x + 400 + 12 || NPC[i].x < unusualNPC[0].x - 400 - 12 ||
			NPC[i].y > unusualNPC[0].y + 300 + 12 || NPC[i].y < unusualNPC[0].y - 300 - 12) {
			continue;
		}//筛掉在视野外的NPC
		putimage(NPC[i].x - unusualNPC[0].x + 400 - 12, NPC[i].y - unusualNPC[0].y + 300 - 12, NPCskinmask + NPC[i].type, NOTSRCERASE);
		putimage(NPC[i].x - unusualNPC[0].x + 400 - 12, NPC[i].y - unusualNPC[0].y + 300 - 12, NPCskinimg + NPC[i].type, SRCINVERT);
	}//渲染NPC
	for (int i = 0; i < 32; i++) {
		if (unusualNPC[i].type == -1) {
			continue;
		}//筛掉未生成的NPC
		if (unusualNPC[i].x > unusualNPC[0].x + 400 + 12 || unusualNPC[i].x < unusualNPC[0].x - 400 - 12 ||
			unusualNPC[i].y > unusualNPC[0].y + 300 + 12 || unusualNPC[i].y < unusualNPC[0].y - 300 - 12) {
			continue;
		}//筛掉在视野外的NPC
		putimage(unusualNPC[i].x - unusualNPC[0].x + 400 - 12, unusualNPC[0].y - unusualNPC[i].y + 300 - 12,
			NPCskinmask + unusualNPC[i].type, NOTSRCERASE);
		putimage(unusualNPC[i].x - unusualNPC[0].x + 400 - 12, unusualNPC[0].y - unusualNPC[i].y + 300 - 12,
			NPCskinimg + unusualNPC[i].type, SRCINVERT);
	}//渲染unusualNPC
	//渲染冲刺蓄力条
	if (ablerushingtime < 1800) {
		setlinecolor(LIGHTGRAY);
		rectangle(775, 150, 800, 450);
		setfillcolor(GREEN);
		solidrectangle(775, 450 - (ablerushingtime / 6), 800, 450);
	}
	//渲染手持物品
	
	//渲染退出按钮
	putimage(0, 0, &exitbtnmask, NOTSRCERASE);
	putimage(0, 0, &exitbtnimg, SRCINVERT);
	skinPKGdoer(7);
	FlushBatchDraw();
}
//创上去的反应
bool theadvnteofft::knocking(short speed, short mark, int& addx, int& addy) {
	bool inotherNPC = false;//碰到NPC
	bool inothunusuNPC = false;//碰到unusualNPC
	int beinedNPCmark = -1;//被碰到NPC的下标
	int beinedunusualNPCmark = -1;//被碰到的unusualNPC的下标
	for (int i = 0; i < 32; i++) {
		if (abs(NPC[mark].x - unusualNPC[i].x) <= 12 && abs(NPC[mark].y - unusualNPC[i].y) <= 12) {
			beinedunusualNPCmark = i;
			inothunusuNPC = true;
			break;
		}
		else if (abs(NPC[mark].x - NPC[i].x) <= 12 && abs(NPC[mark].y - NPC[i].y) <= 12 && i != mark) {
			beinedNPCmark = i;
			inotherNPC = true;
			break;
		}
	}//检查是否在其他NPC内
	if (inotherNPC) {
		double distance = sqrt(EMP(NPC[mark].x - NPC[beinedNPCmark].x, 2) +
			EMP(NPC[mark].y - NPC[beinedNPCmark].y, 2));//距离
		addx = (NPC[mark].x - NPC[beinedNPCmark].x) / (distance / (speed / 4));//x轴动量
		addy = (NPC[mark].y - NPC[beinedNPCmark].y) / (distance / (speed / 4));//y轴动量
		return true;
	}
	else if (inothunusuNPC) {
		double distance = sqrt(EMP(NPC[mark].x - unusualNPC[beinedunusualNPCmark].x, 2) +
			EMP(NPC[mark].y - unusualNPC[beinedunusualNPCmark].y, 2));//距离
		addx = (NPC[mark].x - unusualNPC[beinedunusualNPCmark].x) / (distance / (speed / 4));//x轴动量
		addy = (NPC[mark].y - unusualNPC[beinedunusualNPCmark].y) / (distance / (speed / 4));//y轴动量
		return true;
	}
	else {
		return false;
	}
}
//寻路（靠近玩家）
void theadvnteofft::findnearlistroad(short speed, short mark, int& addx, int& addy) {
	if (!knocking(speed, mark, addx, addy)) {
		double distance = sqrt(EMP(NPC[mark].x - unusualNPC[0].x, 2) + EMP(NPC[mark].y - unusualNPC[0].y, 2));//距离
		addx = -((NPC[mark].x - unusualNPC[0].x) / (distance / speed));//x轴动量
		addy = -((NPC[mark].y - unusualNPC[0].y) / (distance / speed));//y轴动量
	}
}
//兵行为
void theadvnteofft::soldiersaction(short mark) {
	srand(time(NULL) + 124312 + mark + timems);
	if (sqrt(EMP(NPC[mark].x - unusualNPC[0].x, 2) + EMP(NPC[mark].y - unusualNPC[0].y, 2)) <= 200) {
		NPC[mark].event.eventtype = 1;
		NPC[mark].event.eventtime = 2048;
	}
	else if (rand() % 150 == 0 && NPC[mark].event.eventtime <= 0) {
		NPC[mark].event.eventtype = 0;
		srand(time(NULL) + 0 + mark + timems);
		NPC[mark].event.eventtime = rand() % 60 + 30;
		srand(time(NULL) + 1243212 + rand() + 799 + mark + timems);
		switch (rand() % 4) {
		case 0:
			NPC[mark].event.movx = NPCwalkingspeed;
			break;
		case 1:
			NPC[mark].event.movx = -NPCwalkingspeed;
			break;
		case 2:
			NPC[mark].event.movy = NPCwalkingspeed;
			break;
		case 3:
			NPC[mark].event.movy = -NPCwalkingspeed;
			break;
		default:
			break;
		}
	}
}
//资本家行为
void theadvnteofft::capitalistaction(short mark) {
	srand(time(NULL) + 686868 + mark + timems);
	if (rand() % 150 == 0 && NPC[mark].event.eventtime <= 0) {
		NPC[mark].event.eventtype = 0;
		srand(time(NULL) + 0 + mark + timems);
		NPC[mark].event.eventtime = rand() % 60 + 30;
		srand(time(NULL) + 1244312 + rand() + 799 + mark + timems);
		switch (rand() % 4) {
		case 0:
			NPC[mark].event.movx = NPCwalkingspeed;
			break;
		case 1:
			NPC[mark].event.movx = -NPCwalkingspeed;
			break;
		case 2:
			NPC[mark].event.movy = NPCwalkingspeed;
			break;
		case 3:
			NPC[mark].event.movy = -NPCwalkingspeed;
			break;
		default:
			break;
		}
	}
}
//犹太人行为
void theadvnteofft::jewaction(short mark) {
	srand(time(NULL) + 296734 + mark + timems);
	if (rand() % 150 == 0 && NPC[mark].event.eventtime <= 0) {
		NPC[mark].event.eventtype = 0;
		srand(time(NULL) + 0 + mark + timems);
		NPC[mark].event.eventtime = rand() % 60 + 30;
		srand(time(NULL) + 1243612 + rand() + 799 + mark + timems);
		switch (rand() % 4) {
		case 0:
			NPC[mark].event.movx = NPCwalkingspeed;
			break;
		case 1:
			NPC[mark].event.movx = -NPCwalkingspeed;
			break;
		case 2:
			NPC[mark].event.movy = NPCwalkingspeed;
			break;
		case 3:
			NPC[mark].event.movy = -NPCwalkingspeed;
			break;
		default:
			break;
		}
	}
}
//世界事件
void theadvnteofft::worldaction() {
	//清除超出场外NPC，并挑一些离视野范围过远的NPC杀掉
	for (int i = 0; i < 32; i++) {
		if (NPC[i].type != -1) {
			if (NPC[i].x >= unusualNPC[0].x + 800 ||
				NPC[i].x <= unusualNPC[0].x - 800 ||
				NPC[i].y >= unusualNPC[0].y + 600 ||
				NPC[i].y <= unusualNPC[0].y - 600) {
				//清空NPC属性
				NPC[i].type = -1;
				NPC[i].x = 0;
				NPC[i].y = 0;
			}//清除超出场外NPC
			else if (NPC[i].x >= unusualNPC[0].x + 600 ||
				NPC[i].x <= unusualNPC[0].x - 600 ||
				NPC[i].y >= unusualNPC[0].y + 450 ||
				NPC[i].y <= unusualNPC[0].y - 450) {
				srand(time(NULL) + i);
				if (rand() % 6400 == 0) {
					//清空NPC属性
					NPC[i].type = -1;
					NPC[i].x = 0;
					NPC[i].y = 0;
				}//挑一些离视野范围过远的NPC杀掉
			}
		}
	}
	//生成新NPC
	for (int i = 0; i < 32; i++) {
		if (NPC[i].type == -1) {
			srand(time(NULL) + i * 3 + 1 + 98684);
			NPC[i].type = (rand() + 0) % countofnpctype;
			srand(time(NULL) + i * 4 + 1 + 76712);
			NPC[i].x = ((rand() * 186) % 1600) - 800 + unusualNPC[0].x;
			srand(time(NULL) + i * 5 + 1 + 20853);
			NPC[i].y = ((rand() * 919) % 1200) - 600 + unusualNPC[0].y;
			bool collided = false;//是否与其他NPC碰撞
			//判断是否与其他NPC/UNPC距离过近
			for (int j = 0; j < 32; j++) {
				if (NPC[j].type != -1 && j != i) {
					if (NPC[j].x <= NPC[i].x + 25 &&
						NPC[j].x >= NPC[i].x - 25 &&
						NPC[j].y <= NPC[i].y + 25 &&
						NPC[j].y >= NPC[i].y - 25) {
						collided = true;
					}
				}
				if (unusualNPC[j].type != -1) {
					if (unusualNPC[j].x <= NPC[i].x + 25 &&
						unusualNPC[j].x >= NPC[i].x - 25 &&
						unusualNPC[j].y <= NPC[i].y + 25 &&
						unusualNPC[j].y >= NPC[i].y - 25) {
						collided = true;
					}
				}
			}
			//清除生成在视线内的NPC与使用玩家贴图的NPC与与其他NPC碰撞的NPC
			if ((NPC[i].x >= unusualNPC[0].x - 400 &&
				NPC[i].x <= unusualNPC[0].x + 400 &&
				NPC[i].y >= unusualNPC[0].y - 300 &&
				NPC[i].y <= unusualNPC[0].y + 300) ||
				NPC[i].type == 1 ||
				collided) {
				//清空NPC属性
				NPC[i].type = -1;
				NPC[i].x = 0;
				NPC[i].y = 0;
			}
		}
	}
}
//脚脚探索主函数
void theadvnteofft::adventuremain() {
	//初始化
	for (int i = 0; i < 32; i++) {
		NPC[i].type = -1;
		NPC[i].x = 0;
		NPC[i].y = 0;
		NPC[i].event.eventtime = 0;
		NPC[i].event.eventtype = -1;
		NPC[i].event.movx = 0;
		NPC[i].event.movy = 0;
		NPC[i].bagareacount = 2;
		for (int j = 0; j < 100; j++) {
			NPC[i].bag[j].bagthingtype = -1;
		}
		_NPCdata nulltmp;
		unusualNPC.push_back(nulltmp);
		unusualNPC[i].type = -1;
		unusualNPC[i].x = 0;
		unusualNPC[i].y = 0;
		unusualNPC[i].bagareacount = 2;
		for (int j = 0; j < 100; j++) {
			unusualNPC[i].bag[j].bagthingtype = -1;
		}
	}
	unusualNPC[0].type = countofbadnpctype;
	unusualNPC[0].x = 0;
	unusualNPC[0].y = 0;
	//首次生成NPC
	for (int i = 0; i < 32; i++) {
		if (NPC[i].type == -1) {
			srand(time(NULL) + i * 3 + 1 + 98684);
			NPC[i].type = (rand() + 0) % countofnpctype;
			srand(time(NULL) + i * 4 + 1 + 76712);
			NPC[i].x = ((rand() * 186) % 1600) - 800;
			srand(time(NULL) + i * 5 + 1 + 20853);
			NPC[i].y = ((rand() * 919) % 1200) - 600;
		}
		bool collided = false;//是否与其他NPC碰撞
		for (int j = 0; j < 32; j++) {
			if (NPC[j].type != -1 && j != i) {
				if (NPC[j].x <= NPC[i].x + 25 &&
					NPC[j].x >= NPC[i].x - 25 &&
					NPC[j].y <= NPC[i].y + 25 &&
					NPC[j].y >= NPC[i].y - 25) {
					collided = true;
				}
			}
			if (unusualNPC[j].type != -1) {
				if (unusualNPC[j].x <= NPC[i].x + 25 &&
					unusualNPC[j].x >= NPC[i].x - 25 &&
					unusualNPC[j].y <= NPC[i].y + 25 &&
					unusualNPC[j].y >= NPC[i].y - 25) {
					collided = true;
				}
			}
		}//判断是否与其他NPC碰撞
		if (NPC[i].type == countofbadnpctype || collided) {
			//清空NPC属性
			NPC[i].type = -1;
			NPC[i].x = 0;
			NPC[i].y = 0;
		}
	}
	const clock_t framechangetime = 1000 / 60;//帧切换时间(ms)
	bool advnteexit = false;//是否退出

	//渲染与逻辑循环
	while (!advnteexit) {
		timems = clock();
		int framestarttime = clock();//帧起始时间
		paintavt();
		bool windowbefocused = true;
		short speed = 10;//玩家速度(px/frame)

		//消息处理
		if (GetForegroundWindow() != GetHWnd()) {
			windowbefocused = false;
		}//判断是否处于焦点
		if (windowbefocused) {
			ExMessage msg;
			if (peekmessage(&msg)) {
				//退出按钮监测
				if (msg.message == WM_LBUTTONUP) {
					if (msg.x >= 0 * windowasp &&
						msg.x <= 75 * windowasp &&
						msg.y >= 0 * windowasp &&
						msg.y <= 75 * windowasp) {
						flushmessage();
						return;
					}
				}
			}
			//键盘键监测
			short moveddistancex = 0;
			short moveddistancey = 0;
			if (JGetKeydown(VK_SHIFT) && ablerushingtime > 0) {
				speed = 19;
				ablerushingtime -= 10;
			}
			else if (!JGetKeydown(VK_SHIFT) && ablerushingtime < 1800) {
				ablerushingtime += 3;
			}//冲刺
			if (JGetKeydown('W')) {
				moveddistancey -= speed;
				playertoward = north;
			}//上
			if (JGetKeydown('A')) {
				moveddistancex -= speed;
				playertoward = west;
			}//左
			if (JGetKeydown('S')) {
				moveddistancey += speed;
				playertoward = sorth;
			}//下
			if (JGetKeydown('D')) {
				moveddistancex += speed;
				playertoward = east;
			}//右
			if (JGetKeydown(VK_ESCAPE)) {
				flushmessage();
				return;
			}//退出
			//统一玩家移动距离，防止斜向移动过远
			if (abs(moveddistancex) + abs(moveddistancey) >= 20) {
				if (moveddistancex > 0)
					moveddistancex = sqrt(moveddistancex * moveddistancex / 2);
				else
					moveddistancex = -sqrt(moveddistancex * moveddistancex / 2);
				if (moveddistancey > 0)
					moveddistancey = sqrt(moveddistancey * moveddistancey / 2);
				else
					moveddistancey = -sqrt(moveddistancey * moveddistancey / 2);;
			}
			//执行玩家移动
			unusualNPC[0].x += moveddistancex;
			unusualNPC[0].y += moveddistancey;
		}
		//世界事件
		worldaction();
		//NPC行为
		for (int i = 0; i < 32; i++) {
			switch (NPC[i].type) {
			case 0://兵
				soldiersaction(i);
				break;
			case 2://资本家
				capitalistaction(i);
				break;
			case 3://犹太仁
				jewaction(i);
				break;
			default:
				break;
			}
		}
		//NPC事件执行
		for (int i = 0; i < 32; i++) {
			if (NPC[i].event.eventtime > 0) {

				switch (NPC[i].event.eventtype) {
				case 0://乱走
					NPC[i].x += NPC[i].event.movx;
					NPC[i].x += NPC[i].event.movy;
					break;
				case 1://仇恨
					if (NPC[i].type != 0) {
						NPC[i].event.eventtime = 0;
						NPC[i].event.eventtype = -1;
					}//这是屎山的一部粪
					int addx = 0, addy = 0;
					findnearlistroad(soldierspeed, i, addx, addy);
					NPC[i].x += addx;
					NPC[i].y += addy;
					break;
				}

				NPC[i].event.eventtime -= 1;
			}
			else if (NPC[i].event.eventtime <= 0) {
				NPC[i].event.eventtype = -1;
			}
		}
		//帧率维持
		int framedotime = clock() - framestarttime;
		framecount++;
		if (framechangetime - framedotime < 0) {
			printf("这什么电脑竟然还掉帧\n");
		}
		Sleep((framechangetime - framedotime) > 0 ? framechangetime - framedotime : 0);
	}
}