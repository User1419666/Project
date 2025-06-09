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

void moveCat() {
    prevPos = catPos;
    if (mood == 0) {
        printf("기분이 매우 나쁜 %s은(는) 집으로 향합니다.\n", name);
        if (catPos > HOME_POS) catPos--;
    }
    else if (mood == 1) {
        if (hasScratcher || hasTower) {
            int target = -1;
            if (hasScratcher && hasTower)
                target = (abs(catPos - scratcherPos) < abs(catPos - towerPos)) ? scratcherPos : towerPos;
            else if (hasScratcher) target = scratcherPos;
            else target = towerPos;
            if (catPos < target) catPos++;
            else if (catPos > target) catPos--;
            printf("%s은(는) 심심해서 놀이기구 쪽으로 이동합니다.\n", name);
        }
        else {
            printf("놀 거리가 없어서 기분이 매우 나빠집니다.\n");
            mood = 0;
        }
    }
    else if (mood == 3) {
        printf("%s은(는) 골골송을 부르며 수프를 만들러 갑니다.\n", name);
        if (catPos < BOWL_POS) catPos++;
    }
    else {
        printf("%s은(는) 기분 좋게 식빵을 굽고 있습니다.\n", name);
    }
}

void performAction() {
    if (catPos == HOME_POS && prevPos == HOME_POS && mood < 3) {
        mood++;
        printf("%s은(는) 집에서 편안하게 쉬고 있습니다. 기분이 좋아졌습니다.\n", name);
    }
    else if (catPos == BOWL_POS) {
        makeSoup();
    }
    else if (catPos == scratcherPos) {
        mood++;
        if (mood > 3) mood = 3;
        printf("%s은(는) 스크래처를 긁고 놀았습니다.\n", name);
    }
    else if (catPos == towerPos) {
        mood += 2;
        if (mood > 3) mood = 3;
        printf("%s은(는) 캣타워를 뛰어다닙니다.\n", name);
    }
}

void produceCP() {
    int gain = (mood > 0 ? mood - 1 : 0) + intimacy;
    cp += gain;
    printf("%s의 기분과 친밀도에 따라 CP를 %d 포인트 얻었습니다. 현재 CP: %d\n", name, gain, cp);
}

void shop() {
    printf("상점에서 물건을 살 수 있습니다.\n0. 아무 것도 사지 않는다\n");
    printf("1. 장난감 쥐: 1CP %s\n", hasToyMouse ? "(품절)" : "");
    printf("2. 레이저 포인터: 2CP %s\n", hasLaser ? "(품절)" : "");
    printf("3. 스크래처: 4CP %s\n", hasScratcher ? "(품절)" : "");
    printf("4. 캣타워: 6CP %s\n", hasTower ? "(품절)" : "");

    int choice;
    do {
        printf(">> ");
        scanf_s("%d", &choice);
    } while (choice < 0 || choice > 4);

    if (choice == 0) return;
    if ((choice == 1 && hasToyMouse) || (choice == 2 && hasLaser) ||
        (choice == 3 && hasScratcher) || (choice == 4 && hasTower)) {
        printf("이미 구매한 물건입니다.\n");
        return;
    }

    int price[] = { 0, 1, 2, 4, 6 };
    if (cp < price[choice]) {
        printf("CP가 부족합니다.\n");
        return;
    }

    cp -= price[choice];
    printf("구매 완료. 남은 CP: %d\n", cp);
    if (choice == 1) hasToyMouse = true;
    else if (choice == 2) hasLaser = true;
    else if (choice == 3) {
        hasScratcher = true;
        scratcherPos = rand() % (ROOM_WIDTH - 4) + 2;
    }
    else if (choice == 4) {
        hasTower = true;
        do {
            towerPos = rand() % (ROOM_WIDTH - 4) + 2;
        } while (towerPos == scratcherPos);
    }
}

void suddenQuest() {
    printf("돌발 퀘스트 발생! %s이(가) 숨은 고양이 발바닥을 찾고 있습니다.\n", name);
    printf("5초 안에 1~5 중 고양이 발바닥이 있을 위치를 맞혀보세요! >> ");
    int correct = rand() % 5 + 1;
    int answer;
    scanf_s("%d", &answer);
    if (answer == correct) {
        printf("정답! 친밀도 +1!\n");
        if (intimacy < 4) intimacy++;
    }
    else {
        printf("틀렸습니다... 기분 -1\n");
        if (mood > 0) mood--;
    }
}

    return 0;
}
