#ifndef FUNCTION_H
#define FUNCTION_H

#include <windows.h>

// 메인에 있는 mapnum 변수를 공유하겠다고 선언
extern int mapnum;

extern int see;

extern int gameset;

extern int door;

// 다른 파일에서 쓸 함수들의 모양 선언
void map(int num);

DWORD WINAPI monstermove(LPVOID lpParam);

DWORD WINAPI seenum(LPVOID lpParam);
#endif