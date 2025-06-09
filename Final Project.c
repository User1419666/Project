#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>

#define ROOM_WIDTH 13
#define HOME_POS 1
#define BOWL_POS (ROOM_WIDTH - 2)

// ���� ���� ����
bool hasToyMouse = false;
bool hasLaser = false;
bool hasScratcher = false;
bool hasTower = false;
int scratcherPos = -1;
int towerPos = -1;

// �߿��� ����
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
    case 0: printf("����� �ſ� ���޴ϴ�.\n"); break;
    case 1: printf("�ɽ����մϴ�.\n"); break;
    case 2: printf("�Ļ��� �����ϴ�.\n"); break;
    case 3: printf("������ �θ��ϴ�.\n"); break;
    }
}

void printIntimacy() {
    switch (intimacy) {
    case 0: printf("�翡 ���� ������ �Ⱦ��մϴ�.\n"); break;
    case 1: printf("���� ���Ǳ� ����Դϴ�.\n"); break;
    case 2: printf("�׷����� �� ���� �����Դϴ�.\n"); break;
    case 3: printf("�Ǹ��� ����� ���� �ް� �ֽ��ϴ�.\n"); break;
    case 4: printf("���� �������Դϴ�.\n"); break;
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
    printf("==================== ���� ���� =============\n");
    printf("������� ���� ����: %d��\n", soupCount);
    printf("CP: %d ����Ʈ\n", cp);
    printf("%s�� ���(0~3): %d\n", name, mood);
    printMood();
    printf("������� ����(0~4): %d\n", intimacy);
    printIntimacy();
    printf("============================================\n\n");
}

void makeSoup() {
    int type = rand() % 3;
    const char* types[] = { "���� ����", "����� ����", "����ݸ� ����" };
    printf("%s��(��) %s�� ��������ϴ�!\n", name, types[type]);
    soupCount++;
}

void performInteraction() {
    int maxOption = 1;
    if (hasToyMouse) maxOption++;
    if (hasLaser) maxOption++;

    printf("� ��ȣ�ۿ��� �Ͻðڽ��ϱ�?\n0. �ƹ��͵� ���� ����\n1. �ܾ� �ֱ�\n");
    if (hasToyMouse) printf("2. �峭�� ��� ��� �ֱ�\n");
    if (hasLaser) printf("%d. ������ �����ͷ� ��� �ֱ�\n", maxOption);

    int choice;
    do {
        printf(">> ");
        scanf_s("%d", &choice);
    } while (choice < 0 || choice > maxOption);

    int dice = rollDice();
    Sleep(500);

    if (choice == 0) {
        printf("�ƹ��͵� ���� �ʽ��ϴ�.\n");
        if (mood > 0) mood--;
        if (dice <= 5 && intimacy > 0) {
            intimacy--;
            printf("������� ���谡 �������ϴ�.\n");
        }
    }
    else if (choice == 1) {
        printf("%s�� ���� �ܾ��־����ϴ�.\n", name);
        if (dice >= 5 && intimacy < 4) {
            intimacy++;
            printf("ģ�е��� �����߽��ϴ�.\n");
        }
    }
    else if (hasToyMouse && choice == 2) {
        printf("�峭�� ��� %s�� ��� �־����ϴ�.\n", name);
        if (mood < 3) mood++;
        if (dice >= 4 && intimacy < 4) intimacy++;
    }
    else {
        printf("������ �����ͷ� %s�� �ų��� ��� �־����ϴ�.\n", name);
        mood += 2;
        if (mood > 3) mood = 3;
        if (dice >= 2 && intimacy < 4) intimacy++;
    }
}

void moveCat() {
    prevPos = catPos;
    if (mood == 0) {
        printf("����� �ſ� ���� %s��(��) ������ ���մϴ�.\n", name);
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
            printf("%s��(��) �ɽ��ؼ� ���̱ⱸ ������ �̵��մϴ�.\n", name);
        }
        else {
            printf("�� �Ÿ��� ��� ����� �ſ� �������ϴ�.\n");
            mood = 0;
        }
    }
    else if (mood == 3) {
        printf("%s��(��) ������ �θ��� ������ ���鷯 ���ϴ�.\n", name);
        if (catPos < BOWL_POS) catPos++;
    }
    else {
        printf("%s��(��) ��� ���� �Ļ��� ���� �ֽ��ϴ�.\n", name);
    }
}

void performAction() {
    if (catPos == HOME_POS && prevPos == HOME_POS && mood < 3) {
        mood++;
        printf("%s��(��) ������ ����ϰ� ���� �ֽ��ϴ�. ����� ���������ϴ�.\n", name);
    }
    else if (catPos == BOWL_POS) {
        makeSoup();
    }
    else if (catPos == scratcherPos) {
        mood++;
        if (mood > 3) mood = 3;
        printf("%s��(��) ��ũ��ó�� �ܰ� ��ҽ��ϴ�.\n", name);
    }
    else if (catPos == towerPos) {
        mood += 2;
        if (mood > 3) mood = 3;
        printf("%s��(��) ĹŸ���� �پ�ٴմϴ�.\n", name);
    }
}

void produceCP() {
    int gain = (mood > 0 ? mood - 1 : 0) + intimacy;
    cp += gain;
    printf("%s�� ��а� ģ�е��� ���� CP�� %d ����Ʈ ������ϴ�. ���� CP: %d\n", name, gain, cp);
}

void shop() {
    printf("�������� ������ �� �� �ֽ��ϴ�.\n0. �ƹ� �͵� ���� �ʴ´�\n");
    printf("1. �峭�� ��: 1CP %s\n", hasToyMouse ? "(ǰ��)" : "");
    printf("2. ������ ������: 2CP %s\n", hasLaser ? "(ǰ��)" : "");
    printf("3. ��ũ��ó: 4CP %s\n", hasScratcher ? "(ǰ��)" : "");
    printf("4. ĹŸ��: 6CP %s\n", hasTower ? "(ǰ��)" : "");

    int choice;
    do {
        printf(">> ");
        scanf_s("%d", &choice);
    } while (choice < 0 || choice > 4);

    if (choice == 0) return;
    if ((choice == 1 && hasToyMouse) || (choice == 2 && hasLaser) ||
        (choice == 3 && hasScratcher) || (choice == 4 && hasTower)) {
        printf("�̹� ������ �����Դϴ�.\n");
        return;
    }

    int price[] = { 0, 1, 2, 4, 6 };
    if (cp < price[choice]) {
        printf("CP�� �����մϴ�.\n");
        return;
    }

    cp -= price[choice];
    printf("���� �Ϸ�. ���� CP: %d\n", cp);
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
    printf("���� ����Ʈ �߻�! %s��(��) ���� ����� �߹ٴ��� ã�� �ֽ��ϴ�.\n", name);
    printf("5�� �ȿ� 1~5 �� ����� �߹ٴ��� ���� ��ġ�� ����������! >> ");
    int correct = rand() % 5 + 1;
    int answer;
    scanf_s("%d", &answer);
    if (answer == correct) {
        printf("����! ģ�е� +1!\n");
        if (intimacy < 4) intimacy++;
    }
    else {
        printf("Ʋ�Ƚ��ϴ�... ��� -1\n");
        if (mood > 0) mood--;
    }
}

    return 0;
}
