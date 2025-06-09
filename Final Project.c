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

void drawRoom() {
    printf("###############\n#");
    for (int i = 1; i <= ROOM_WIDTH - 2; i++) {
        if (i == HOME_POS) printf("H");
        else if (i == BOWL_POS) printf("B");
        else if (i == scratcherPos) printf("S");
        else if (i == towerPos) printf("T");
        else printf(" ");
    }
    printf("#\n#");
    for (int i = 1; i <= ROOM_WIDTH - 2; i++) {
        if (i == catPos) printf("C");
        else if (i == prevPos && catPos != prevPos) printf(".");
        else printf(" ");
    }
    printf("#\n###############\n\n");
}

void printStatus() {
    printf("==================== 현재 상태 =============\n");
    printf("현재까지 만든 수프: %d개\n", soupCount);
    printf("CP: %d 포인트\n", cp);
    printf("%s의 기분(0~3): %d\n", name, mood);
    printMood();
    printf("집사와의 관계(0~4): %d\n", intimacy);
    printIntimacy();
    printf("============================================\n\n");
}

void makeSoup() {
    int type = rand() % 3;
    const char* types[] = { "감자 수프", "양송이 수프", "브로콜리 수프" };
    printf("%s이(가) %s를 만들었습니다!\n", name, types[type]);
    soupCount++;
}

void performInteraction() {
    int maxOption = 1;
    if (hasToyMouse) maxOption++;
    if (hasLaser) maxOption++;

    printf("어떤 상호작용을 하시겠습니까?\n0. 아무것도 하지 않음\n1. 긁어 주기\n");
    if (hasToyMouse) printf("2. 장난감 쥐로 놀아 주기\n");
    if (hasLaser) printf("%d. 레이저 포인터로 놀아 주기\n", maxOption);

    int choice;
    do {
        printf(">> ");
        scanf_s("%d", &choice);
    } while (choice < 0 || choice > maxOption);

    int dice = rollDice();
    Sleep(500);

    if (choice == 0) {
        printf("아무것도 하지 않습니다.\n");
        if (mood > 0) mood--;
        if (dice <= 5 && intimacy > 0) {
            intimacy--;
            printf("집사와의 관계가 나빠집니다.\n");
        }
    }
    else if (choice == 1) {
        printf("%s의 턱을 긁어주었습니다.\n", name);
        if (dice >= 5 && intimacy < 4) {
            intimacy++;
            printf("친밀도가 증가했습니다.\n");
        }
    }
    else if (hasToyMouse && choice == 2) {
        printf("장난감 쥐로 %s와 놀아 주었습니다.\n", name);
        if (mood < 3) mood++;
        if (dice >= 4 && intimacy < 4) intimacy++;
    }
    else {
        printf("레이저 포인터로 %s와 신나게 놀아 주었습니다.\n", name);
        mood += 2;
        if (mood > 3) mood = 3;
        if (dice >= 2 && intimacy < 4) intimacy++;
    }
}


    return 0;
}
