#include "function.h"
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// 진짜 변수 생성 및 초기화
int mapnum = 0;
int see = 0;
int gameset = 0;


int main() {
	HANDLE MonsterThread = CreateThread(NULL, 0, monstermove, NULL, 0, NULL);
	HANDLE SeeThread = CreateThread(NULL, 0, seenum, NULL, 0, NULL);

	if (MonsterThread == NULL || SeeThread == NULL) {

		// 생성에 성공한 스레드가 있다면 그것만 닫아줍니다.
		if (MonsterThread != NULL) CloseHandle(MonsterThread);
		if (SeeThread != NULL) CloseHandle(SeeThread);

		return 1; // 프로그램 종료
	};

	map(mapnum);
	while (1) {
		if (gameset == 0) {
			Sleep(500);
			if (see == 119) {
				if (mapnum == 0) {
					system("cls");
					map(0);
				}
				else {
					system("cls");
					map(mapnum);
				}
			}
			else if (see == 97) {
				system("cls");
				map(1);
			}
			else if (see == 100) {
				system("cls");
				map(2);
			}
		}
		else if (gameset == 1) {
			system("cls");
			break;
		}
	}
	WaitForSingleObject(MonsterThread, INFINITE);
	WaitForSingleObject(SeeThread, INFINITE);
	CloseHandle(MonsterThread);
	CloseHandle(SeeThread);
}