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


    return 0;
}
