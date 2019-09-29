#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

void print();               //��ӡ����
void gameInit();            //��Ϸ��ʼ��
int gameMain();
void move(char ch);         //�����ƶ�
void randNum ();            //�����������
int gameOver();
void gameScore();           //��¼��Ϸ����
int mapFull();              //�ж��Ƿ�����
int gameWin();

int map[4][4] = {0};
int score;

int main()
{
    gameInit();
    gameMain();
}

//��Ϸ����
int gameMain()
{
    char ch;
    int game_over;
    do
    {
        gameScore();
        ch = getch();
        move(ch);
        if (gameWin())
        {
            return 0;
        }
        while (mapFull())
        {
            if (gameOver() == 1)
            {
                return 0;
            }
            ch = getch();
            move(ch);
        }
        randNum();
        print();
    }while (1);
}

//�������
int mapFull()
{
    int mapfull = 1;
    int i;
    for (i = 0; i < 4; i++)
    {
    	int j;
        for (j = 0; j < 4; j++)
        {
            if (map[i][j] == 0)
            {
                mapfull = 0;
                return mapfull;
            }
        }
    }
    return mapfull;
}

//�����ƶ�
void move(char ch)
{
    if(ch == 'a')       //���û��������aʱ
    {
    	int i;
        for (i = 0; i < 4; i++)
        {
            int j, k;
            for (j = 1, k = 0; j < 4; j++)
            {
                if (map[i][j] > 0)
                {
                    if (map[i][j] == map[i][k])
                    {
                        map[i][k] = map[i][j] * 2;
                        map[i][j] = 0;
                        k++;
                    } else if (map[i][k] == 0) {
                        map[i][k] = map[i][j];
                        map[i][j] = 0;
                    } else {
                        map[i][k + 1] = map[i][j];
                        if ((k + 1) != j)       //�ж�k��j�Ƿ�����
                        {
                            map[i][j] = 0;
                        }
                        k++;
                    }
                }
            }
        }
    }
    else if (ch == 'd')          //���û������ֵ��dʱ
    {
    	int i;
        for (i = 0; i < 4; i++)
        {
            int j, k;
            for (j = 2, k = 3; j >= 0; j--)
            {
                if (map[i][j] > 0)
                {
                    if (map[i][j] == map[i][k])
                    {
                        map[i][k] = map[i][k] * 2;
                        map[i][j] = 0;
                        k--;
                    } else if (map[i][k] == 0) {
                        map[i][k] = map[i][j];
                        map[i][j] = 0;
                    } else {
                        map[i][k - 1] = map[i][j];

                        if ((k - 1) != j)
                        {
                            map[i][j] = 0;
                        }
                        k--;
                    }
                }
            }
        }
    }
    else if (ch == 'w')
    {
    	int i;
        for (i = 0; i < 4; i++)
        {
            int j, k;
            for (j = 1, k = 0; j < 4; j++)
            {
                if (map[j][i] > 0)
                {
                    if (map[j][i] == map[k][i])
                    {
                        map[k][i] = map[k][i] * 2;
                        map[j][i] = 0;
                        k++;
                    } else if (map[k][i] == 0) {
                        map[k][i] = map[j][i];
                        map[j][i] = 0;
                    } else {
                        map[k + 1][i] = map[j][i];

                        if ((k + 1) != j)
                        {
                            map[j][i] = 0;
                        }
                        k++;
                    }
                }
            }
        }
    }
    else if (ch == 's')
    {
    	int i;
        for (i = 0; i < 4; i++)
        {
            int j, k;
            for (j = 2, k = 3; j >= 0; j--)
            {
                if (map[j][i] > 0)
                {
                    if (map[j][i] == map[k][i])
                    {
                        map[k][i] = map[k][i] * 2;
                        map[j][i] = 0;
                        k--;
                    } else if (map[k][i] == 0) {
                        map[k][i] = map[j][i];
                        map[j][i] = 0;
                    } else {
                        map[k - 1][i] = map[j][i];

                        if ((k - 1) != j)
                        {
                            map[j][i] = 0;
                        }
                        k--;
                    }
                }
            }
        }
    }
    system("CLS");              //�����Ļ
}

//��Ϸ��ʼ��
void gameInit()
{
    srand((unsigned)time(NULL));
    int x, y;

    x = rand() % 4;
    y = rand() % 4;

    map[x][y] = 2;

    x = rand() % 4;
    y = rand() % 4;

    if (map[x][y] != 0)                //�ж��������Ƿ���0���������0�������һ��
    {
        x = rand() % 4;
        y = rand() % 4;
    }

    map[x][y] = 2;
    print();
}

//��Ϸʤ��
int gameWin ()
{
	int i;
    for (i = 0; i < 4; i++)
    {
    	int j;
        for (j = 0; j < 4; j++)
        {
            if (map[i][j] == 2048)
            {
                printf("\n\tYou Win!");
                return 1;
            }
        }
    }
    return 0;
}

//��Ϸ����
int gameOver()
{
    int gameover = 1;
    int i;
    for (i = 0; i < 4; i++)
    {
    	int j;
        for (j = 0; j < 3; j++)
        {
            if ((map[i][j] == map[i][j + 1] || map[j][i] == map[j + 1][i]) && (map[i][j + 1] != 0 || map[j + 1][i]))   //�жϺ���������Ƿ����
            {
                gameover = 0;
                return 0;
            }
        }
    }
    if (gameover == 1)
        printf("\nGame Over!");
    return gameover;
}

//����
void gameScore()
{
    score = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
    	int j;
        for (j = 0; j < 4; j++)
        {
            score += map[i][j];
        }
    }
    printf("\n\t����:%d", score);
}

//�������
void randNum ()
{
    srand((unsigned)time(NULL));
    int x, y;
    x = rand() % 4;
    y = rand() % 4;

    while (map[x][y] != 0)
    {
        x = rand() % 4;
        y = rand() % 4;
    }
    map[x][y] = 2;
}


//��ӡ
void print()
{
	int i;
    for (i = 0; i < 4; i++)
    {
        printf("---------------------------------\n");
        printf("|");
        int j;
        for (j = 0; j < 4; j++)
        {
            if (map[i][j] == 0)
            {
                printf(" \t|");
                continue;
            }
            printf("%d\t|", map[i][j]);
        }
        printf("\n|\t|\t|\t|\t|\n");
    }
    printf("---------------------------------");
}
