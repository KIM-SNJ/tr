#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

int mapnum = 0;
int gameset = 0;
int door = 0;
float wdoor = 30;
int updown = 0;
int temp = 40;

int main() {
    int monstertime = 0;
    int monstertype = 0;
    int tick = 0;
    int attacktimer = 0;
    int survivetime = 0;
    int current_view = 0;

    srand((unsigned int)time(NULL));

    while (1) {
        // 1. 단발성 키 입력 처리
        if (_kbhit()) {
            int key = _getch();

            if (key == 119) { // 'w'
                current_view = 0;
            }
            else if (key == 101) { // 'e' 문 조작
                current_view = 0;

                if (temp > 25 && temp < 75) {
                    door = !door;
                }
            }
            else if (key == 97) { // 'a'
                current_view = 1;
            }
            else if (key == 107) { // 'k'
                current_view = 1;
                if (wdoor < 30)
                    wdoor += 5;
            }
            else if (key == 100) { // 'd'
                current_view = 2;
            }
            else if (key == 104) { // 'h'
                current_view = 2;
                updown = 1;
            }
            else if (key == 106) { // 'j'
                current_view = 2;
                updown = 0;
            }
        }

        // 2. 시간 흐름 (0.1초 대기)
        Sleep(100);
        tick++;

        // 3. 1초(0.1초 * 10)마다 수치 변동 로직
        if (tick >= 10) {
            tick = 0;

            // 1초가 지날 때마다 생존 시간 증가
            survivetime++;

            // 3분(180초) 달성 시 클리어 조건 만족
            if (survivetime >= 180) {
                gameset = 2;
            }

            wdoor -= 3;
            if (updown == 1) 
                temp += 5;
            else if (updown == 0) 
                temp -= 5;

            // temp 범위 제한 (0 ~ 100)
            if (temp > 100) temp = 100;
            if (temp < 0) temp = 0;

            // 이미 클리어 상태가 아닐 때만 게임 오버 판정
            if (wdoor <= 0 && gameset == 0) 
                gameset = 1;

            // 몬스터 타이머 계산
            if (monstertype == 0) {
                monstertime++;
                if (monstertime >= 7) {
                    monstertype = rand() % 3 + 1;
                    monstertime = 0;
                    attacktimer = 0;
                }
            }
        }

        // 4. 몬스터 공격 진행 상태 판정
        if (monstertype != 0) {
            attacktimer++;

            if (monstertype == 3 && attacktimer % 5 == 0)
                Beep(1567.982, 100);
            else if (monstertype == 2 && attacktimer % 2 == 0)
                Beep(1975.533, 100);

            if (monstertype == 1 || monstertype == 3) {
                if (attacktimer > 50) {
                    if (gameset == 0) {
                        if (monstertype == 3 && door == 0)
                            gameset = 1;
                        else if (monstertype == 1 && door == 1)
                            gameset = 1;
                    }
                    monstertype = 0;
                }
            }
            else if (monstertype == 2) {
                if (attacktimer > 30) {
                    if (gameset == 0) {
                        if (monstertype == 2 && door == 0)
                        gameset = 1;
                    }
                    monstertype = 0;
                }
            }
        }

        // 게임 오버 또는 게임 클리어 시 루프 탈출 및 화면 출력
        if (gameset == 1) {
            system("cls");
            printf("GAME OVER\n");
            break;
        }
        else if (gameset == 2) { // 게임 클리어 화면 추가
            system("cls");
            printf("\n");
            printf("========================================\n");
            printf("              GAME CLEAR!               \n");
            printf("      3분을 무사히 버텨냈습니다!        \n");
            printf("========================================\n");
            break;
        }

        // 5. 지속적인 화면 갱신
        system("cls");

        if (current_view == 0) {
            if (monstertype == 0) {
                mapnum = (door == 1) ? 0 : 7;
            }
            else {
                if (monstertype == 1) mapnum = (door == 1) ? 3 : 10;
                else if (monstertype == 2) mapnum = (door == 1) ? 4 : 9;
                else if (monstertype == 3) mapnum = (door == 1) ? 5 : 8;
            }
            map(mapnum);
        }
        else if (current_view == 1) {
            if (wdoor > 20)
                map(1);
            else if (wdoor > 10)
                map(11);
            else
                map(12);
        }
        else if (current_view == 2) {
            map(2);
        }
    }

    return 0;
}