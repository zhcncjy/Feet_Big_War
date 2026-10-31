#include "buffdo.h"
//buff效果实施
void buffdoer(_playerdata& player) {
	for (int i = 0; i < 4; i++) {
		if (player.bufftime[i] <= 0) {
			player.buff[i] = -1;
		}
		if (player.buff[i] != -1) {
			if (player.buff[i] == 0) {
				player.blood -= 1;
			}//淤泥炸弹
			if (player.buff[i] == 1) {
				if (player.bufftime[i] % 3 == 0) {
					player.blood -= 1;
				}
			}//女巫毒气弹
			player.bufftime[i] -= 1;
		}
	}
}