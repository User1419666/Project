#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>

#define ROOM_WIDTH 13
#define HOME_POS 1
#define BOWL_POS (ROOM_WIDTH - 2)

// 물건 구매 여부
bool hasToyMouse = false;
bool hasLaser = false;
bool hasScratcher = false;
bool hasTower = false;
int scratcherPos = -1;
int towerPos = -1;

// 야옹이 상태
char name[20];
int intimacy = 2;
int mood = 3;
int soupCount = 0;
int cp = 0;
int catPos = HOME_POS;
int prevPos = HOME_POS;
int turn = 0;


int rollDice() {
    return rand() % 6 + 1;
}

void printMood() {
    switch (mood) {
    case 0: printf("기분이 매우 나쁩니다.\n"); break;
    case 1: printf("심심해합니다.\n"); break;
    case 2: printf("식빵을 굽습니다.\n"); break;
    case 3: printf("골골송을 부릅니다.\n"); break;
    }
}

void printIntimacy() {
    switch (intimacy) {
    case 0: printf("곁에 오는 것조차 싫어합니다.\n"); break;
    case 1: printf("간식 자판기 취급입니다.\n"); break;
    case 2: printf("그럭저럭 쓸 만한 집사입니다.\n"); break;
    case 3: printf("훌륭한 집사로 인정 받고 있습니다.\n"); break;
    case 4: printf("집사 껌딱지입니다.\n"); break;
    }
}

    return 0;
}
