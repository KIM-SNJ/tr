#include "function.h"
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int mapnum = 0;
int see = 0;
int gameset = 0;
int door = 0;

int main() {
	HANDLE MonsterThread = CreateThread(NULL, 0, monstermove, NULL, 0, NULL);
	HANDLE SeeThread = CreateThread(NULL, 0, seenum, NULL, 0, NULL);

	if (MonsterThread == NULL || SeeThread == NULL) {


		if (MonsterThread != NULL) CloseHandle(MonsterThread);
		if (SeeThread != NULL) CloseHandle(SeeThread);

		return 1;
	};

	map(7);
	while (1) {
		if (gameset == 0) {
			Sleep(500);
			if (see == 119 || see == 101 || see == 0) {
				if (mapnum == 0) {
					system("cls");
					map(mapnum);
				}
				else {
					system("cls");
					map(mapnum);
				}
				if (see == 101) {
					if (door == 0) {
						door = 1;
						see = 0;
					}
					else {
						door = 0;
						see = 0;
					}
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
	return 0;
}