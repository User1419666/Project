#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define ROOM_WIDTH 10
#define HOME_POS 1
#define BOWL_POS (ROOM_WIDTH - 2)

void drawIntro(char* name) {
    printf("****�߿��̿� ����****\n");
    printf("         /\\_/\\\n");
    printf("  /\\    / o o \\\n");
    printf(" //\\\\   \\~(*)~/\n");
    printf(" `  \\/     ^ /\n");
    printf("     | \\ || ||\n");
    printf("     \\ ' || ||\n");
    printf("      \\) ()-())\n");
    printf("\n");
    printf("�߿����� �̸��� ���� �ּ��� (�ִ� 19��): ");
    scanf_s("%19s", name, 20);
    printf("�߿����� �̸��� %s�Դϴ�.\n", name);
    Sleep(2500);
    system("cls");
}

void printStatus(int soupCount, int intimacy) {
    printf("==================== ���� ���� ===================\n");
    printf("������� ���� ����: %d��\n", soupCount);
    printf("������� ����(0~4): %d\n", intimacy);

    switch (intimacy) {
    case 0:
        printf("�翡 ���� ������ �Ⱦ��մϴ�.\n");
        break;
    case 1:
        printf("���� ���Ǳ� ����Դϴ�.\n");
        break;
    case 2:
        printf("�׷����� �� ���� �����Դϴ�.\n");
        break;
    case 3:
        printf("�Ǹ��� ����� ���� �ް� �ֽ��ϴ�.\n");
        break;
    case 4:
        printf("���� �������Դϴ�.\n");
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
    printf("�߿��̰� ");
    switch (type) {
    case 0:
        printf("���� ����");
        break;
    case 1:
        printf("����� ����");
        break;
    case 2:
        printf("����ݸ� ����");
        break;
    }
    printf("�� ��������ϴ�!\n");
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
        printf("� ��ȣ�ۿ��� �Ͻðڽ��ϱ�? 0. �ƹ��͵� ���� ����  1. �ܾ� �ֱ�\n>> ");
        scanf_s("%d", &choice);

        while (choice < 0 || choice > 1) {
            printf("�ٽ� �Է��� �ּ��� (0 �Ǵ� 1): ");
            scanf_s("%d", &choice);
        }

        int dice = rollDice();
        Sleep(500);

        if (choice == 0) {
            printf("�ƹ��͵� ���� �ʽ��ϴ�.\n");
            printf("4/6�� Ȯ���� ģ�е��� �������ϴ�.\n");
            printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
            printf("%d��(��) ���Խ��ϴ�!\n", dice);
            if (dice <= 4 && intimacy > 0) {
                intimacy--;
                printf("ģ�е��� �������ϴ�.\n");
            }
            else {
                printf("������ ģ�е��� �������� �ʾҽ��ϴ�.\n");
            }
        }
        else if (choice == 1) {
            printf("%s�� ���� �ܾ��־����ϴ�.\n", name);
            printf("2/6�� Ȯ���� ģ�е��� �������ϴ�.\n");
            printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
            printf("%d��(��) ���Խ��ϴ�!\n", dice);
            if (dice >= 5 && intimacy < 4) {
                intimacy++;
                printf("ģ�е��� �������ϴ�.\n");
            }
            else {
                printf("ģ�е��� �״���Դϴ�.\n");
            }
        }

        Sleep(1000);

        // �̵�
        int moveDice = rollDice();
        printf("\n%s �̵�: ����� ģ���Ҽ��� ���� ������ �� Ȯ���� �������ϴ�.\n", name);
        printf("�ֻ��� ���� %d �̻��̸� ���� ������ �̵��մϴ�.\n", 6 - intimacy);
        printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
        printf("%d��(��) ���Խ��ϴ�!\n", moveDice);

        prevPos = catPos;
        int newPos = catPos;
        if (moveDice >= (6 - intimacy)) {
            if (catPos < BOWL_POS) newPos++;
            printf("���� ������ �����Դϴ�.\n");
        }
        else {
            if (catPos > HOME_POS) newPos--;
            printf("�� ������ �����Դϴ�.\n");
        }

        if (newPos == catPos) {
            printf("%s��(��) �������� �ʾҽ��ϴ�.\n", name);
        }

        catPos = newPos;

        // �ൿ
        if (catPos == BOWL_POS) {
            makeSoup(&soupCount);
        }
        else if (catPos == HOME_POS) {
            printf("%s��(��) �ڽ��� ������ ������� �����ϴ�.\n", name);
        }

        Sleep(2500);
        system("cls");
    }

    return 0;
}