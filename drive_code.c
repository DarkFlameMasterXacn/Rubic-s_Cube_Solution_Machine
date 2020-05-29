/*
**  魔方朝向说明: U==上  R==右  F==前  F==底  F==左  F==后
**  控制各个位置的步进电机转动
**  每个面都可能有3种转动方式:
**  顺时针90°  逆时针90°  顺时针180°  逆时针180°
*/

// 定义各个位置电机的控制信号的针脚(PUL->脉冲信号, DIR->转向信号):

int U_PUL = 22;
int U_DIR = 23;

int R_PUL = 24;
int R_DIR = 25;

int F_PUL = 26;
int F_DIR = 27;

int D_PUL = 28;
int D_DIR = 29;

int L_PUL = 30;
int L_DIR = 31;

int B_PUL = 32;
int B_DIR = 33;

// 还原状态(0为未还原, 1为已还原, 初始化为0)
int IS_OK = 0;

// 魔方解法
char const *solve[22] = {"U", "D'", "L", "U'", "L2", "D'", "R2", "F", "U2", "B'", "U'", "L'", "B2", "D", "L2", "D'", "R2", "B2", "L2", "D'", "R2", "U2"};

void setup()
{
    // 初始化针脚
    pinMode(U_PUL, OUTPUT);
    pinMode(U_DIR, OUTPUT);

    pinMode(R_PUL, OUTPUT);
    pinMode(R_DIR, OUTPUT);

    pinMode(F_PUL, OUTPUT);
    pinMode(F_DIR, OUTPUT);

    pinMode(D_PUL, OUTPUT);
    pinMode(D_DIR, OUTPUT);

    pinMode(L_PUL, OUTPUT);
    pinMode(L_DIR, OUTPUT);

    pinMode(B_PUL, OUTPUT);
    pinMode(B_DIR, OUTPUT);
}

void loop()
{
    if (IS_OK == 0)
    {
        for (int i = 0; i < 22; i++)
        {
            // 上
            if (strcmp("U", solve[i]) == 0)
            {
                move(1, 0, U_PUL, U_DIR);
            }
            else if (strcmp("U'", solve[i]) == 0)
            {
                move(0, 0, U_PUL, U_DIR);
            }
            else if (strcmp("U2", solve[i]) == 0)
            {
                move(1, 1, U_PUL, U_DIR);
            }

            // 右
            else if (strcmp("R", solve[i]) == 0)
            {
                move(1, 0, R_PUL, R_DIR);
            }
            else if (strcmp("R'", solve[i]) == 0)
            {
                move(0, 0, R_PUL, R_DIR);
            }
            else if (strcmp("R2", solve[i]) == 0)
            {
                move(1, 1, R_PUL, R_DIR);
            }

            // 前
            else if (strcmp("F", solve[i]) == 0)
            {
                move(1, 0, F_PUL, F_DIR);
            }
            else if (strcmp("F'", solve[i]) == 0)
            {
                move(0, 0, F_PUL, F_DIR);
            }
            else if (strcmp("F2", solve[i]) == 0)
            {
                move(1, 1, F_PUL, F_DIR);
            }

            // 下
            else if (strcmp("D", solve[i]) == 0)
            {
                move(1, 0, D_PUL, D_DIR);
            }
            else if (strcmp("D'", solve[i]) == 0)
            {
                move(0, 0, D_PUL, D_DIR);
            }
            else if (strcmp("D2", solve[i]) == 0)
            {
                move(1, 1, D_PUL, D_DIR);
            }

            // 左
            else if (strcmp("L", solve[i]) == 0)
            {
                move(1, 0, L_PUL, L_DIR);
            }
            else if (strcmp("L'", solve[i]) == 0)
            {
                move(0, 0, L_PUL, L_DIR);
            }
            else if (strcmp("L2", solve[i]) == 0)
            {
                move(1, 1, L_PUL, L_DIR);
            }

            // 后
            else if (strcmp("B", solve[i]) == 0)
            {
                move(1, 0, B_PUL, B_DIR);
            }
            else if (strcmp("B'", solve[i]) == 0)
            {
                move(0, 0, B_PUL, B_DIR);
            }
            else if (strcmp("B2", solve[i]) == 0)
            {
                move(1, 1, B_PUL, B_DIR);
            }
        }

        IS_OK = 1;
    }
}

/*
**  控制电机往指定方向转动指定角度
**  @d_status: 魔方转动方向信号(1为顺时针, 0为逆时针)
**  @a_status: 转动角度信号(0为90°, 1为180°)
**  @PUL: 脉冲控制针脚
**  @DIR: 转向控制针脚
*/
void move(int d_status, int a_status, int PUL, int DIR)
{
    // 脉冲数(转动90度需要200脉冲, 180度需要400脉冲, 初始化为零)
    int pul_count = 0;

    // 根据状态码判断当前输入的转动方向
    if (d_status == 0)
    {
        digitalWrite(DIR, LOW); // 低电平电机顺时针转动,魔方逆时针转动
    }
    else if (d_status == 1)
    {
        digitalWrite(DIR, HIGH); // 高电平电机逆时针转动,魔方顺时针转动
    }

    // 将转动角度信号转化为对应角度的脉冲
    if (a_status == 0)
    {
        pul_count = 200;
    }
    else if (a_status == 1)
    {
        pul_count = 400;
    }

    // 转动电机
    for (int i = 0; i < pul_count; i++)
    {
        digitalWrite(PUL, HIGH);
        delayMicroseconds(400);
        digitalWrite(PUL, LOW);
    }
    //  delay(1);
}