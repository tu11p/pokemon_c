#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>
typedef struct stuff {
	char item[20];
	int count;
	int money;
} inv;
typedef struct pokemon {
	char name[20];
	char type[20];
	int power;
	int hp;
	int maxhp;
} pk;
int pkLoad(pk** pkS) {
	int numPk;
	FILE* fp = fopen("pokemon_list.txt", "rt");
	fscanf(fp, "%d", &numPk);
	*pkS = (pk*)calloc(numPk, sizeof(pk));
	for (int i = 0; i < numPk; i++) {
		fscanf(fp, "%s %s %d %d", (*pkS)[i].name, (*pkS)[i].type, &(*pkS)[i].power, &(*pkS)[i].hp);
		(*pkS)[i].maxhp = (*pkS)[i].hp;
	}
	fclose(fp);
	return numPk;
}												//Ÿ�̸� �ϼ�
void firstPokemon(pk* userPk, pk* pkS, int num) {
	int point = 0;
	srand(time(NULL));
	printf("\n============================\n\n");
	printf("��� ���ϸ��� ���ðڽ��ϱ�?\n\n");
	printf("1. ���̸� 2. �̻��ؾ� 3. ���α�\n\n");
	while (point > '3' || point < '0') {
		if (num != 1)
			while (getchar() != '\n');
		point = getchar();
	}
	strcpy(userPk[0].name, pkS[point - 49].name);
	strcpy(userPk[0].type, pkS[point - 49].type);
	userPk[0].power = 500;
	userPk[0].maxhp = userPk[0].hp = rand() % (701) + 1000;
}																							//���ϸ� ó�� ���� �ϼ�
void load(pk* userPk, inv* item) {
	int numSave;
	FILE* load = fopen("savefile.txt", "rt");
	fscanf(load, "%d", &numSave);
	for (int i = 0; i < numSave; i++)
		fscanf(load, "%*d %*c %s %*c %s %*c %d %*c %d %*c %d", userPk[i].name, userPk[i].type, &userPk[i].power, &userPk[i].hp, &userPk[i].maxhp);
	for (int j = 0; j < 2; j++)
		fscanf(load, "%s %*c %d", item[j].item, &item[j].count);
	fscanf(load, "%d", &item[0].money);
	fclose(load);
}																							//���̺����� �ε� �ϼ�
pk mkRandPk(pk* pkS, int pkNum) {
	pk randPk;
	strcpy(randPk.name, pkS[pkNum].name);
	strcpy(randPk.type, pkS[pkNum].type);
	randPk.maxhp = randPk.hp = rand() % (701) + 1000;
	randPk.power = rand() % (101) + 200;
	return randPk;
}																							//���� ���ϸ� ���� �ϼ�
int attack(pk* randPk, pk* userPk) {
	char userType[20]; strcpy(userType, userPk->type);
	char comType[20];  strcpy(comType, randPk->type);
	if (strcmp(userType, comType) == 0) {
		randPk->hp -= userPk->power;
		if (randPk->hp > 0)
			userPk->hp -= randPk->power;
		printf("\n\n");
	}
	else if (strcmp(userType, "��") == 0 && strcmp(comType, "Ǯ") == 0
		|| strcmp(userType, "��") == 0 && strcmp(comType, "��") == 0
		|| strcmp(userType, "Ǯ") == 0 && strcmp(comType, "��") == 0) {
		randPk->hp -= userPk->power * 1.5;
		if (randPk->hp > 0)
			userPk->hp -= randPk->power * 0.5;
		printf("\nȿ���� �����ߴ�!\n\n");
	}
	else {
		randPk->hp -= userPk->power * 0.5;
		if (randPk->hp > 0)
			userPk->hp -= randPk->power * 1.5;
		printf("\nȿ���� �����ε� �ϴ�!\n\n");
	}
	if (randPk->hp == 0) {
		printf("��! ���ϸ��� ���������ȴ�!\n\n");
		return 0;
	}
	else if (randPk->hp < 0) {
		printf("��� ���ϸ� : %s %s\nü��: %d/%d\n", randPk->name, randPk->type, randPk->hp, randPk->maxhp);
		printf("�� ���ϸ� : %s %s\nü��: %d/%d\n\n", userPk->name, userPk->type, userPk->hp, userPk->maxhp);
		printf("���ϸ��� �����߷ȴ�!\n\n");
		return 2;
	}
	else if (userPk->hp <= 0) {
		printf("��� ���ϸ� : %s %s\nü��: %d/%d\n", randPk->name, randPk->type, randPk->hp, randPk->maxhp);
		printf("�� ���ϸ� : %s %s\nü��: %d/%d\n\n", userPk->name, userPk->type, userPk->hp, userPk->maxhp);
		return 1;
	}
	printf("��� ���ϸ� : %s %s\nü��: %d/%d\n", randPk->name, randPk->type, randPk->hp, randPk->maxhp);
	printf("�� ���ϸ� : %s %s\nü��: %d/%d\n\n", userPk->name, userPk->type, userPk->hp, userPk->maxhp);
	return 10;
}
void addPk(pk* userPk, pk randPk, int numUserSum) {
	strcpy(userPk[numUserSum].name, randPk.name);
	strcpy(userPk[numUserSum].type, randPk.type);
	userPk[numUserSum].maxhp = userPk[numUserSum].hp = randPk.maxhp;
	userPk[numUserSum].power = randPk.power;
}
int run(pk randPk) {
	int hpPercent = ((double)randPk.hp / randPk.maxhp) * 100;
	int numRand = rand() % 10;
	if (hpPercent == 100) {
		if (numRand == 0) {
			return 1;
		}
	}
	else if (hpPercent >= 50) {
		if ((numRand) <= 3) {
			return 1;
		}
	}
	else if (hpPercent >= 25) {
		if ((numRand) <= 6) {
			return 1;
		}
	}
	else {
		if ((numRand) <= 8) {
			return 1;
		}
	}
	printf("������ �����ߴ�!\n\n");
	return 0;
}																							//�����Լ� �ϼ�
int throwBall(pk randPk, pk* pkName, inv* item) {
	double hpPercent = (double)randPk.hp / randPk.maxhp * 100;
	if (hpPercent > 50) {
		printf("ü���� �� ����ּ���...\n\n");
		return 100;
	}
	printf("����! ���ͺ�!\n\n");
	item[0].count--;
	if (hpPercent >= 30) {
		if (rand() % 10 <= 2) {
			printf("���ϸ��� ��Ҵ�! �̸��� �Է��� �ּ���\n\n");
			scanf("%s", pkName->name);
			return 1;
		}
	}
	else if (hpPercent >= 10) {
		if (rand() % 10 <= 5) {
			printf("���ϸ��� ��Ҵ�! �̸��� �Է��� �ּ���\n\n");
			scanf("%s", pkName->name);
			return 1;
		}
	}
	else {
		if (rand() % 10 <= 8) {
			printf("���ϸ��� ��Ҵ�! �̸��� �Է��� �ּ���\n\n");
			scanf("%s", pkName->name);
			return 1;
		}
	}
	printf("���ϸ��� ���ͺ��� �������Դ�!\n\n");
	return 10;
}
int fight(pk* pkS, pk* userPk, int num, int numUserSum, inv* item) {
	pk* randUserPk;
	int pkNum;
	int point = 0;
	int maxhp;
	int numUserRand;
	int result, a = 1, count = 1;
	pk randPk;
	do
		numUserRand = rand() % numUserSum;
	while (userPk[numUserRand].hp <= 0);
	printf("\n============================\n\n");
	printf("       ���� �ȴ���... ...       \n\n");
	srand(time(NULL));
	Sleep(rand() % 3000);
	pkNum = rand() % num;
	randUserPk = &userPk[numUserRand];
	randPk = mkRandPk(pkS, pkNum);
	printf("\n============================\n\n");
	printf(" �߻��� ���ϸ��� ��Ÿ����!  \n\n");
	printf("��� ���ϸ� : %s %s\nü��: %d/%d\n\n", randPk.name, randPk.type, randPk.hp, randPk.maxhp);
	printf("�� ���ϸ� : %s %s\nü��: %d/%d\n\n", randUserPk->name, randUserPk->type, randUserPk->hp, randUserPk->maxhp);
	while (1) {
		printf("1.���� 2.����ġ�� 3.���濭��\n\n");
		do {
			while (getchar() != '\n');
			point = getchar();
		} while (point != '1' && point != '2' && point != '3');
		if (point == '1') {
			result = attack(&randPk, randUserPk);
			if (result == 0) {
				return 0;
			}
			else if (result == 1) {
				a = 1;
				printf("\n============================\n\n");
				for (int i = 0; i < numUserSum; i++)
					if (userPk[i].hp > 0) {
						printf("%d. %s	%s	%d/%d\n\n", a, userPk[i].name, userPk[i].type, userPk[i].hp, userPk[i].maxhp);
						a++;
					}
				if (a == 1) {
					printf("������ ����������...\n\n");
					Sleep(rand() % 1500);
					printf("�����ϰ� ��� ��� ���ϸ��� ü���� ȸ���Ͽ����ϴ�.\n\n");
					for (int i = 0; i < numUserSum; i++)
						userPk[i].hp = userPk[i].maxhp;
					return 0;
				}
				point = -1;
				while (!(point - 48 > 0 && point - 48 < a)) {
					while (getchar() != '\n');
					point = getchar();
				}
				count = 1;
				for (int j = 0; j < numUserSum; j++)
					if (userPk[j].hp > 0) {
						count++;
						if (count == point - 47) {
							randUserPk = &userPk[j];
							break;
						}
					}
			}

			else if (result == 2) {
				addPk(userPk, randPk, numUserSum);
				return 1;
			}
		}
		else if (point == '2') {
			int runResult = run(randPk);
			if (runResult == 1)
				return 0;
		}
		else if (point == '3') {
			printf("\n============================\n\n");
			printf("1. %s	x%d\n", item[0].item, item[0].count);
			printf("2. %s	x%d\n\n", item[1].item, item[1].count);
			do {
				while (getchar() != '\n');
				point = getchar();
				if (item[0].count == 0 && point == '1' || item[1].count == 0 && point == '2')
					printf("������ �����մϴ�.\n\n");
			} while (point != '0' && point != '1' && point != '2' || (item[0].count == 0 && point == '1' || item[1].count == 0 && point == '2'));
			if (point == '0') {
				continue;
			}
			else if (point == '1') {
				result = throwBall(randPk, &randPk, item);
				if (result == 1) {
					addPk(userPk, randPk, numUserSum);
					return 1;
				}
			}
			else if (point == '2') {
				randUserPk->hp = randUserPk->hp + randUserPk->maxhp * 0.3;
				item[1].count--;
				if (randUserPk->hp > randUserPk->maxhp)
					randUserPk->hp = randUserPk->maxhp;
				continue;
			}
		}
	}
}
void store(inv* item) {
	int point;
	int count = 0;
	while (1) {
		printf("\n============================\n\n");
		printf("1. %s	%d\n", item[0].item, 1000);
		printf("2. %s	%d\n\n", item[1].item, 2500);
		printf(" ���� �ݾ� : %d\n\n", item[0].money);
		do {
			while (getchar() != '\n');
			point = getchar();
		} while (point != '0' && point != '1' && point != '2');
		if (point == '0')
			return;
		printf("��� �����Ͻðڽ��ϱ�?\n\n");
		scanf("%d", &count);
		if (point == '1') {
			if (item[0].money >= count * 1000) {
				item[0].count += count;
				item[0].money -= count * 1000;
			}
			else printf("���� �����մϴ�\n\n");
		}
		else if (point == '2') {
			if (item[0].money >= count * 2500) {
				item[1].count += count;
				item[0].money -= count * 2500;
			}
			else printf("���� �����մϴ�\n\n");
		}
		else return;
	}
}
int userTotalPk(pk* userPk) {
	int i;
	for (i = 0; i < 6; i++)
		if (userPk[i].maxhp == 0)
			break;
	return i;
}
void init(inv** item) {
	(*item) = (inv*)calloc(2, sizeof(inv));
	strcpy((*item)[0].item, "���ͺ�");
	strcpy((*item)[1].item, "ȸ������");
	(*item)[0].count = 0;
	(*item)[1].count = 0;
	(*item)[0].money = 10000;
	return;
}
int main() {
	int point = 0;
	FILE* save;
	inv* item;
	int numTotalPk, numUserSum;
	pk* pkS;
	pk* userPk;
	numTotalPk = pkLoad(&pkS);
	userPk = calloc(6, sizeof(pk));
	init(&item);
	printf("============================\n\n");
	printf("        ���ϸ���         \n\n");
	printf("  ENTER ANY TEXT TO START \n\n");
	printf("============================\n\n");
	while (getchar() != 10);
	if (fopen("savefile.txt", "rt") != NULL) {
		printf("\n============================\n\n");
		printf("  1. �����ϱ� 2. �̾��ϱ�   \n\n");
		while (point != '1' && point != '2') {
			point = getchar();
		}
		if (point == '1') {
			firstPokemon(userPk, pkS, 2);
			init(&item);
		}
		else if (point == '2') {
			item = calloc(2, sizeof(inv));
			load(userPk, item);
		}
	}
	else {
		firstPokemon(userPk, pkS, 1);
		init(&item);
	}
	while (1) {
		printf("\n============================\n\n");
		printf("    ������ �����ðڽ��ϱ�?  \n\n");
		printf("1. ��  2. �ƴϿ�  3. �������� \n\n");
		do {
			while (getchar() != '\n');
			point = getchar();
		} while (point != '1' && point != '2' && point != '3');
		if (point == '1') {
			numUserSum = userTotalPk(userPk);
			int result;
			result = fight(pkS, userPk, numTotalPk, numUserSum, item);
			if (result == 1 && numUserSum == 5) {
				printf("�� ���� ������! ������ �� ��������(Y/N)?\n\n");
				while (getchar() != '\n');
				scanf("%c", &point);
				if (point == 'Y') {
					for (int i = 1; i < 6; i++) {
						userPk[i].hp = userPk[i].maxhp = 0;
					}
				}
				else if (point == 'N') {
					return;
				}
			}
		}
		else if (point == '2') {
			printf("�����Ͻðڽ��ϱ�?\n\n");
			printf("1. ��   2.�ƴϿ�\n\n");
			do {
				while (getchar() != '\n');
				point = getchar();
			} while (point != '0' && point != '1' && point != '2');
			if (point == '1') {
				save = fopen("savefile.txt", "wt");
				numUserSum = userTotalPk(userPk);
				fprintf(save, "%d\n", numUserSum);
				for (int i = 0; i < numUserSum; i++)
					fprintf(save, "%d_%s | %s | %d | %d/%d\n", i + 1, userPk[i].name, userPk[i].type, userPk[i].power, userPk[i].hp, userPk[i].maxhp);
				for (int j = 0; j < 2; j++)
					fprintf(save, "%s | %d\n", item[j].item, item[j].count);
				fprintf(save, "%d\n", item[0].money);
				fclose(save);
				free(pkS);
				free(userPk);
				free(item);
				return 0;
			}
			else if (point == '2') {
				free(pkS);
				free(userPk);
				free(item);
				return 0;
			}
		}
		else if (point == '3') {
			store(item);
		}
	}
}
