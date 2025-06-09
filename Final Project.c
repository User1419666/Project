#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define ROOM_WIDTH 10
#define HOME_POS 1
#define BOWL_POS (ROOM_WIDTH - 2)

void drawIntro(char* name) {
    printf("****야옹이와 수프****\n");
    printf("         /\\_/\\\n");
    printf("  /\\    / o o \\\n");
    printf(" //\\\\   \\~(*)~/\n");
    printf(" `  \\/     ^ /\n");
    printf("     | \\ || ||\n");
    printf("     \\ ' || ||\n");
    printf("      \\) ()-())\n");
    printf("\n");
    printf("야옹이의 이름을 지어 주세요 (최대 19자): ");
    scanf_s("%19s", name, 20);
    printf("야옹이의 이름은 %s입니다.\n", name);
    Sleep(2500);
    system("cls");
}

void printStatus(int soupCount, int intimacy) {
    printf("==================== 현재 상태 ===================\n");
    printf("현재까지 만든 수프: %d개\n", soupCount);
    printf("집사와의 관계(0~4): %d\n", intimacy);

    switch (intimacy) {
    case 0:
        printf("곁에 오는 것조차 싫어합니다.\n");
        break;
    case 1:
        printf("간식 자판기 취급입니다.\n");
        break;
    case 2:
        printf("그럭저럭 쓸 만한 집사입니다.\n");
        break;
    case 3:
        printf("훌륭한 집사로 인정 받고 있습니다.\n");
        break;
    case 4:
        printf("집사 껌딱지입니다.\n");
        break;
    }
    printf("==================================================\n\n");
}

void drawRoom(int catPos, int prevPos) {
    printf("##########\n");
    printf("#");
    for (int i = 1; i <= ROOM_WIDTH - 2; i++) {
        if (i == HOME_POS) printf("H");
        else if (i == BOWL_POS) printf("B");
        else printf(" ");
    }
    printf("#\n#");
    for (int i = 1; i <= ROOM_WIDTH - 2; i++) {
        if (i == catPos) printf("C");
        else if (i == prevPos && catPos != prevPos) printf(".");
        else printf(" ");
    }
    printf("#\n##########\n\n");
}

int rollDice() {
    return rand() % 6 + 1;
}

void makeSoup(int* soupCount) {
    int type = rand() % 3;
    printf("야옹이가 ");
    switch (type) {
    case 0:
        printf("감자 수프");
        break;
    case 1:
        printf("양송이 수프");
        break;
    case 2:
        printf("브로콜리 수프");
        break;
    }
    printf("를 만들었습니다!\n");
    (*soupCount)++;
}

int main() {
    char name[20];
    int intimacy = 2;
    int soupCount = 0;
    int catPos = HOME_POS;
    int prevPos = HOME_POS;

    srand((unsigned int)time(NULL));
    drawIntro(name);

    while (1) {
        printStatus(soupCount, intimacy);
        drawRoom(catPos, prevPos);

        int choice;
        printf("어떤 상호작용을 하시겠습니까? 0. 아무것도 하지 않음  1. 긁어 주기\n>> ");
        scanf_s("%d", &choice);

        while (choice < 0 || choice > 1) {
            printf("다시 입력해 주세요 (0 또는 1): ");
            scanf_s("%d", &choice);
        }

        int dice = rollDice();
        Sleep(500);

        if (choice == 0) {
            printf("아무것도 하지 않습니다.\n");
            printf("4/6의 확률로 친밀도가 떨어집니다.\n");
            printf("주사위를 굴립니다. 또르륵...\n");
            printf("%d이(가) 나왔습니다!\n", dice);
            if (dice <= 4 && intimacy > 0) {
                intimacy--;
                printf("친밀도가 떨어집니다.\n");
            }
            else {
                printf("다행히 친밀도가 떨어지지 않았습니다.\n");
            }
        }
        else if (choice == 1) {
            printf("%s의 턱을 긁어주었습니다.\n", name);
            printf("2/6의 확률로 친밀도가 높아집니다.\n");
            printf("주사위를 굴립니다. 또르륵...\n");
            printf("%d이(가) 나왔습니다!\n", dice);
            if (dice >= 5 && intimacy < 4) {
                intimacy++;
                printf("친밀도가 높아집니다.\n");
            }
            else {
                printf("친밀도는 그대로입니다.\n");
            }
        }

        Sleep(1000);

        // 이동
        int moveDice = rollDice();
        printf("\n%s 이동: 집사와 친밀할수록 냄비 쪽으로 갈 확률이 높아집니다.\n", name);
        printf("주사위 눈이 %d 이상이면 냄비 쪽으로 이동합니다.\n", 6 - intimacy);
        printf("주사위를 굴립니다. 또르륵...\n");
        printf("%d이(가) 나왔습니다!\n", moveDice);

        prevPos = catPos;
        int newPos = catPos;
        if (moveDice >= (6 - intimacy)) {
            if (catPos < BOWL_POS) newPos++;
            printf("냄비 쪽으로 움직입니다.\n");
        }
        else {
            if (catPos > HOME_POS) newPos--;
            printf("집 쪽으로 움직입니다.\n");
        }

        if (newPos == catPos) {
            printf("%s은(는) 움직이지 않았습니다.\n", name);
        }

        catPos = newPos;

        // 행동
        if (catPos == BOWL_POS) {
            makeSoup(&soupCount);
        }
        else if (catPos == HOME_POS) {
            printf("%s은(는) 자신의 집에서 편안함을 느낍니다.\n", name);
        }

        Sleep(2500);
        system("cls");
    }

    return 0;
}