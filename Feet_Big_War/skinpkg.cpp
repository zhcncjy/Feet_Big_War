#include "skinpkg.h"
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