#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

void print();               //打印数字
void gameInit();            //游戏初始化
void gameMain();
void move(char ch);         //数字移动
void randNum ();            //随机出现数字
int gameOver();
void gameScore();           //记录游戏分数
int mapFull();              //判断是否满了
int gameWin();

int map[4][4] = {0};
int score;

int main()
{
    gameInit();
    gameMain();
}

//游戏主体
void gameMain()
{
    char ch;
    int game_over;
    do
    {
        gameScore();
        ch = getch();
        randNum();
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
    }while (1);
}

//如果满了
int mapFull()
{
    int mapfull = 1;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
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

//数字移动
void move(char ch)
{
    if(ch == 'a')       //当用户输入的是a时
    {
        for (int i = 0; i < 4; i++)
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
                        if ((k + 1) != j)       //判断k和j是否相邻
                        {
                            map[i][j] = 0;
                        }
                        k++;
                    }
                }
            }
        }
        system("CLS");
        print();
    }
    else if (ch == 'd')          //当用户输入的值是d时
    {
        for (int i = 0; i < 4; i++)
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
        for (int i = 0; i < 4; i++)
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
        for (int i = 0; i < 4; i++)
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
    system("CLS");              //清除屏幕
    print();                    //将数组打印出来
}

//游戏初始化
void gameInit()
{
    srand((unsigned)time(NULL));
    int x, y;

    x = rand() % 4;
    y = rand() % 4;

    map[x][y] = 2;

    x = rand() % 4;
    y = rand() % 4;

    if (map[x][y] != 0)                //判断数组内是否不是0，如果不是0就再随机一次
    {
        x = rand() % 4;
        y = rand() % 4;
    }

    map[x][y] = 2;
    print();
}

//游戏胜利
int gameWin ()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
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

//游戏结束
int gameOver()
{
    int gameover = 1;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if ((map[i][j] == map[i][j + 1] || map[j][i] == map[j + 1][i]) && (map[i][j + 1] != 0 || map[j + 1][i]))   //判断横向和纵向是否相等
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

//分数
void gameScore()
{
    score = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            score += map[i][j];
        }
    }
    printf("\n\t分数:%d", score);
}

//随机出数
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


//打印
void print()
{
    for (int i = 0; i < 4; i++)
    {
        printf("---------------------------------\n");
        printf("|");
        for (int j = 0; j < 4; j++)
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
