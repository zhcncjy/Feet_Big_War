#include "tools.h"

//增加新日志
void addlog(_logcls logclass, string logdata) {
	_log logtmp;
	logtmp.logclass = logclass;
	logtmp.data = logdata;
	logtmp.time = time(NULL) % DAYSECONDS;
	logs.push_back(logtmp);
}
//带报错的定制版freopen
bool Jfreopen(const char* _FileName, const char* _Mode, FILE* _Stream) {
	if (freopen(_FileName, _Mode, _Stream) == NULL) {
		char logdata[MAX_PATH + 7];
		sprintf(logdata, "找不到%s", _FileName);
		MessageBox(GetHWnd(),
			logdata,
			"你给老子东西干哪去了?",
			MB_SYSTEMMODAL | MB_ICONERROR
		);
		addlog(error, logdata);
		return false;
	}
	else {
		char logdata[MAX_PATH + 10];
		sprintf(logdata, "%s加载成功", _FileName);
		addlog(info, logdata);
		return true;
	}
}
//带报错的定制版loadimage
bool Jloadimage(IMAGE* pDstImg, LPCTSTR pImgFile, int nWidth, int nHeight, bool bResize) {
	if (Jfreopen(pImgFile, "r", stdin)) {
		loadimage(pDstImg, pImgFile, nWidth, nHeight, bResize);
		return true;
	}
	else {
		return false;
	}
	fclose(stdin);
	freopen("CON", "r", stdin);
}
//string转char*
void StringTochars(string input, LPSTR output) {
	for (int i = 0; i < input.size(); i++) {
		output[i] = input[i];
	}
}
//某键是否按下
bool JGetKeydown(int vKey) {
	if (GetAsyncKeyState(vKey) & 0x8000) {
		return true;
	}
	else {
		return false;
	}
}
//幂
double EMP(double num, int emp) {
	double retnum = num;
	if (emp > 0) {
		for (int i = 1; i < emp; i++) {
			retnum *= num;
		}
	}
	else if (emp < 0) {
		for (int i = emp; i <= 0; i++) {
			retnum /= num;
		}
	}
	else if (emp == 0) {
		retnum = 1;
	}
	return retnum;
}