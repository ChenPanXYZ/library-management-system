/************************************************
*               学生注册/登陆模块
*             Written by 计1704 谭鸿锐
*                   20174712
*************************************************/

#include <stdio.h>
#include "admin.h"
#include "student.h"
#include "statu.h"
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//#include "stdafx.h"

/*******界面********/
void Register(Student_List * pList)     //注册界面
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    //显示栏
    SetConsoleTextAttribute(Color, 0x3F );
    printf("\n\n\n\n                                                  新用户注册                                                   \n");
    SetConsoleTextAttribute(Color, 0xf );
    printf("\n\n\n");
    AddStudent(pList);       //注册学生信息
}

int Loggin(Student_List * pList, int loggin, Student_Node * student)        //登陆界面
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    char tmp_s_number[9];
    char tmp_password[PASSWD_SIZE];
    int status = 0;

    //显示栏
    SetConsoleTextAttribute(Color, 0x3F );
    printf("\n\n\n\n                                                  登录                                                         \n\n\n");
    SetConsoleTextAttribute(Color, 0xf );
    if (loggin)
    {
        printf("\t\t\t\t\t您已经登录过");
        getch();
        return 1;
    }
    printf("\t\t\t\t\t[学号] ");
    scanf("%8s", tmp_s_number);
    printf("\t\t\t\t\t[密码]");
    SetConsoleTextAttribute(Color, 0x0 );
    scanf("%16s", tmp_password);
    SetConsoleTextAttribute(Color, 0xF );

    status = status + Is_Register(pList, tmp_s_number);
    status = status + Is_Register(pList, tmp_password);
    if(status == 3)
    {
        SetConsoleTextAttribute(Color, 0x3 );
        printf("\t\t\t登录成功。");
        SetConsoleTextAttribute(Color, 0xf );
        SaveStudent(pList, student, tmp_s_number, tmp_password);
        getch();
        return 1;
    }
    else
    {
        SetConsoleTextAttribute(Color, 0xC );
        printf("\t\t\t登录失败。");
        SetConsoleTextAttribute(Color, 0xf );
        getch();
        return 0;
    }
}

void AddStudent(Student_List * pList)
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    Student_Node * new;
    char tmp_name[NAME_SIZE];
    char tmp_sex;
    char tmp_s_number[9];
    char tmp_password[PASSWD_SIZE];
    int size;
    int i;

    printf("\t\t\t请填写注册信息，输入姓名时按【q】离开注册。\n\n\n");

    printf("\t\t\t       最多20个字符 姓名 : ");
    get_str(tmp_name, NAME_SIZE);                  //调用admin.h里的输入字符串函数

    printf("\t\t\t              8位数 学号 : ");
    scanf("%8s", tmp_s_number);
    size = strlen(tmp_s_number);
    for (i = 0; i < size; i++)
        if (size <8 || !isdigit(tmp_s_number[i]))            //不是数字//输入的学号不符合条件
        {
            SetConsoleTextAttribute(Color, 0xC );
            printf("\t\t\t[*]您输入的学号不符合条件,中止注册。\n");
            SetConsoleTextAttribute(Color, 0xF );
            getch();
            return;
        }
    if (Is_Register(pList, tmp_s_number) == 1)
    {
        SetConsoleTextAttribute(Color, 0xC );
        printf("\t\t\t[*]您输入的学号已被注册。\n");
        SetConsoleTextAttribute(Color, 0xF );
        getch();
        return;
    }

    getchar();
    printf("\t\t\t       男(b),女(g) 性别 : ");
    tmp_sex = getchar();
    //putchar(tmp_sex);
    /**if ((tmp_sex != 'b') || (tmp_sex != 'g'))
    {
        SetConsoleTextAttribute(Color, 0xC );
        printf("\t\t\t[*]您输入的性别不符合条件,中止注册。\n");
        SetConsoleTextAttribute(Color, 0xF );
        getch();
        return;
    }**/

    printf("\t\t\t          最多16为 密码 : \n");
    SetConsoleTextAttribute(Color, 0x0 );                   //将输入的密码设成黑色
    scanf("%s", tmp_password);

    new = (Student_Node * )malloc (sizeof(Student_Node));   //满足所有条件后，添加到链表
    strcpy(new->name, tmp_name);
    strcpy(new->s_number, tmp_s_number);
    strcpy(new->password, tmp_password);
    new->sex = tmp_sex;
    new->status = 1;                                    //默认账号未被封
    new->booknumber = 0;                                //默认账号借书数目为0;

    new->next = *pList;
    *pList = new;

    SetConsoleTextAttribute(Color, 0xA );
    printf("已完成注册。\n");
    SetConsoleTextAttribute(Color, 0xF );

    //将链表导出到文件
    Student_ListToFile(pList);
    getch();
}

int Is_Register(Student_List * pList, char * ch)    //判断字符串是否在链表里,若在学号里，返回1，若在在密码里返回2
{
    Student_Node * walker = *pList;
    int i = 0;

    if (*pList == NULL)
        return 0;
    else
    {
        while (walker != NULL)
        {
            if (strcmp(walker->s_number, ch) == 0)
            {
                i++;
                return 1;
            }
            if (strcmp(walker->password, ch) == 0)
            {
                i++;
                return 2;
            }
            walker = walker->next;
        }
        if (i == 0)
            return 0;
    }
}

//将链表导出到文件
void Student_ListToFile(Student_List * pList)
{
    FILE * fp;
    Student_Node * walker = *pList;
    if ((fp = fopen("student.dat", "w")) == NULL)
    {
        printf("[!]用户管理文件损坏，无法将数据导出至文件。\n");
        return;
    }
    while (walker != NULL)
    {
        fputs(walker->name, fp);
        putc('\n', fp);
        putc(walker->sex, fp);
        putc('\n', fp);
        fputs(walker->s_number, fp);
        putc('\n', fp);
        fputs(walker->password, fp);
        putc('\n', fp);
        fprintf(fp, "%d, %d\n", walker->status, walker->booknumber);

        walker = walker->next;
    }
        fprintf(fp,"#\n");
    if (fclose(fp) != 0)
        printf("关闭文件时出错。\n");
}

void Student_FileToList(Student_List * pList)
{
    FILE * fp;
    Student_Node * newnode;
    char end;                                           //判断是空文件

    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    if ((fp = fopen("student.dat", "r")) == NULL)
    {
        SetConsoleTextAttribute(Color, 0xC );
        printf("[!]用户管理文件损坏或不存在，无法读入用户。\n");
        SetConsoleTextAttribute(Color, 0xf );
        return;
    }
    end = fgetc(fp);
    if (end != EOF)
    {                                                   //未到达文件尾
        rewind(fp);
        while (1)
        {
            newnode = (Student_Node *) malloc (sizeof(Student_Node));

            get_strFromFile(newnode->name, NAME_SIZE, fp);
            if (newnode->name[0] == '#')
                break;
            newnode->sex = fgetc(fp);
            fgetc(fp);
            get_strFromFile(newnode->s_number, NAME_SIZE, fp);
            get_strFromFile(newnode->password, PASSWD_SIZE, fp);
            fscanf(fp, "%d, %d\n", &(newnode->status), &(newnode->booknumber));

            newnode->next = *pList;
            *pList = newnode;
        }
    }
    if (fclose(fp) != 0)
        printf("关闭文件时出错。\n");
}

//若用户成功登陆，将信息储存在student结构体里
void SaveStudent(Student_List * pList, Student_Node * student, char * num, char * passwd)
{
    Student_Node * walker = *pList;
    while (walker != NULL)
    {
        if ((strcmp(walker->s_number, num) == 0) &&
             (strcmp(walker->password, passwd) == 0))
        {
            *student = *walker;
            return;
        }
            walker = walker->next;
    }
}

//用户成功登录的状态栏
void Welcome_Student(int status, Student_Node student)
{
    if (status == 1)
    {
        HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(Color, 0xCF );
        printf("                                       ====WECOME COME TO LBRARY SYSTEM====                                    \n");
        SetConsoleTextAttribute(Color, 0xC );
        printf("                                           \t[你好，%s，欢迎回来]\t\n", student.name);
        SetConsoleTextAttribute(Color, 0xF );
    }
}

//每一次到达开始菜单末尾(用户已经完成操作)
//将student结构体的信息重新写进链表里
//用户链表里信息的更新
void Update_StudentList(Student_List * pList, Student_Node * student)
{
    Student_Node * walker = *pList;

    while (walker != NULL)
    {
        if (strcmp(student->s_number, walker->s_number) == 0)    //找到学生
        {
            walker->booknumber = student->booknumber;
            strcpy(walker->name, student->name);
            strcpy(walker->s_number, student->s_number);
            strcpy(walker->password, student->password);
            walker->sex = walker->sex;
            walker->status = student->status;
            break;
        }
        walker = walker->next;
    }
}

//用户登陆后
//注销或修改信息
//信息所在的节点被修改
int QuitorChange_Student(Student_List * pList, Student_Node * pNode, int status)
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    int ch;
    char tmp_name[NAME_SIZE];
    char tmp_sex;
    char tmp_password[PASSWD_SIZE];
    Student_Node * walker = *pList;

    SetConsoleTextAttribute(Color, 0xCF );
    printf("\n\n                         输入1--------------------->修改/注销<--------------------输入其他                     \n\n");
    SetConsoleTextAttribute(Color, 0xF );
    if (status == 0)
    {
        printf("[*]您还没有登录。\n");
        getch();
        return 0;
    }
    else
    {
        printf("输入您的选项 = ");
        scanf("%d", &ch);
        getch();
        if (ch == 1)
        {
            printf("\t\t\t\t\t【这是您的账户信息】\n");
            printf("\t\t姓名 = %s\t||性别 = %c\t||学号 = %s\n\n",
                   pNode->name, pNode->sex, pNode->s_number);
            printf("请填写您的密码以修改信息(直接按回车退出修改)\n");
            SetConsoleTextAttribute(Color, 0x0 );
            //get_str(tmp_password, PASSWD_SIZE);
            scanf("%s", tmp_password);
            SetConsoleTextAttribute(Color, 0xF );
            if (tmp_password[0] == '\0')
                return 1;
            if (strcmp(tmp_password, pNode->password) != 0)
            {
                printf("密码不正确。");
                getch();
                return 1;
            }
            printf("\n\n\n\t\t\t       最多20个字符 姓名 : ");
            scanf("%20s", tmp_name);
            printf("\t\t\t       男(b),女(g) 性别 : ");
            getchar();
            tmp_sex = getchar();
            getchar();
            printf("是否修改密码(最大16位)？【Y/N】");
            if (getchar() == 'Y')
            {
                SetConsoleTextAttribute(Color, 0xC );
                printf("\t\t\t\t新密码");
                SetConsoleTextAttribute(Color, 0x0 );
                scanf("%s", tmp_password);
                SetConsoleTextAttribute(Color, 0xF );
            }
            else
                strcpy(tmp_password, pNode->password);

            while (walker != NULL)
            {
                if (strcmp(pNode->s_number, walker->s_number) == 0)
                {
                    strcpy(walker->name, tmp_name);
                    strcpy(walker->password, tmp_password);
                    walker->sex = tmp_sex;
                    break;
                }
                walker = walker->next;
            }
        }
        strcpy(pNode->name, "-");
        strcpy(pNode->password, "\0");
        pNode->status = 0;
        strcpy(pNode->s_number, "-");
        printf("\n已撤销。\n");
        getch();
        return 0;
    }
}

//用户申请解封账号
//从链表里查找status为0的账号，并显示出来
//将status改为1
void RecStudnt(Student_List * sList)
{
    Student_Node * walker = *sList;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char input[TITLE_SIZE];
    int status = 0;
    SetConsoleTextAttribute(hConsole, 0xCF );
    printf("                                                ====解封账号====                                               \n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF );

    printf("未按时还书导致账号异常的同学如下:\n\n");

    //显示账号异常列表
    while (walker != NULL)
    {
        if (walker->status == 0)
        {
            status++;
            SetConsoleTextAttribute(hConsole, 0xC );
            printf("[\t学号 = %s\t姓名 = %s\t]\n", walker->s_number, walker->name);
            SetConsoleTextAttribute(hConsole, 0xF );
        }
        walker = walker->next;
    }
    if (status == 0)
    {
        SetConsoleTextAttribute(hConsole, 0xc );
        printf("[\t    没有被锁定的账号。\t]\n");
        SetConsoleTextAttribute(hConsole, 0xF );
    }
    else
    {
    //解封账号
        printf("\n\n\t输入要解封的学号，若同时解封多个学号以空格隔开，输入#结束输入:");

        while(1)
        {
            status = 0;
            walker = *sList;
            scanf("%8s", input);
            if(input[0] == '#')
                break;
            while(walker != NULL)
            {
                if ((strcmp(input, walker->s_number) == 0) && (walker->status == 0))
                {
                    status++;
                    walker->status = 1;
                    SetConsoleTextAttribute(hConsole, 0xA );
                    printf("[\t成功解封 ：学号 = %s\t]\n", walker->s_number);
                    SetConsoleTextAttribute(hConsole, 0xF );
                }
                walker = walker->next;
            }
            if (status == 0)
            {
                SetConsoleTextAttribute(hConsole, 0xc );
                printf("[\t    失败 ：您输入的学号未被封号或者不存在\t]\n");
                SetConsoleTextAttribute(hConsole, 0xF );
            }
        }
    }
    getch();
    c_scr();
}

//用户忘记密码
//从链表里查找学号
//显示用户信息
void FindPasswd(const Student_List * sList)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char input[TITLE_SIZE];
    Student_Node * walker;
    int status = 0;
    SetConsoleTextAttribute(hConsole, 0x5F );
    printf("                                               ====查询密码====                                                \n\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF );

    while (1)
    {
        walker = *sList;
        printf("输入要查询的学号：按#退出");
        scanf("%8s", input);
        if (input[0] == '#')
            break;
        printf("\n\n\t\t");
        SetConsoleTextAttribute(hConsole, 0xCF );
        while (walker != NULL)
        {
            if (strcmp(walker->s_number, input) == 0)
            {
                status++;
                printf("\t[学号 = %s, 密码 = %s]\n\n\n", walker->s_number, walker->password);
            }
            walker = walker->next;
        }
        if (status == 0)
            printf("\t学号不存在\n\n\n\n");
        SetConsoleTextAttribute(hConsole, 0xF );
    }
    getch();
    c_scr();
}
