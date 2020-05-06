/*********************************************************
                      管理员模块
              Written by 计1704 罗廷忠
                       20174693
*********************************************************/

#include "admin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
//#include "stdafx.h"

/****************基础函数**************/
void c_scr(void)
{
    system("cls");
}

void prin_erro(char * str)
{
    c_scr();
    puts(str);
}

char get_first_char(void)       //截取输入字符串的首字符
{
    char ch = getchar();
    while(getchar() != '\n')
            continue;
    return ch;
}

char * get_str(char * st, int n)  //字符串录入
{
    char * ret_val;
    int i = 0;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        while (st[i] != '\n' && st[i] != '\0')
            i++;
        if (st[i] == '\n')
            st[i] = '\0';
        else
            while (getchar() != '\n');
    }
    return ret_val;
}

char * get_long_number(char * ch, int n)        //获取一个只包含数字的字符数组
{
    int size;
    int i;

    scanf("%13s", ch);
    size = strlen(ch);
    for (i = 0; i < size; i++)
        if (size <13 || !isdigit(ch[i]))            //不是数字
            return NULL;
    return ch;
}

char * get_strFromFile(char * st, int n, FILE * fp)  //从文件st中读取一次字符串
{
    char * ret_val;
    int i = 0;

    ret_val = fgets(st, n, fp);
    if (ret_val)
    {
        while (st[i] != '\n' && st[i] != '\0')
            i++;
        if (st[i] == '\n')
            st[i] = '\0';
        else
            while (getchar() != '\n');
    }
    return ret_val;
}

void gettime(void)
{
    struct tm *local;
    time_t t;
    t=time(NULL);
    local=localtime(&t);
    if (local->tm_hour >= 6 && local->tm_hour <= 12)
        printf("早上好，");
    else if (local->tm_hour > 12 &&local->tm_hour <= 18)
        printf("下午好，");
    else
        printf("晚上好，");
    printf("现在是: %d点%d分。\n",local->tm_hour, local->tm_min);
}



/**************界面****************************/

void Help(void)
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Color, 0x3F );
    printf("\n\n                                                       帮助                                                    \n\n\n\n\n");
    SetConsoleTextAttribute(Color, 0xa );
    printf("\t\t1、本图书管理系统是面向我校学生和老师的、集借、还书于一体的开放性系统。\n");
    printf("\t\t2、同学及老师可根据本系统的指令实现借还书操作。\n");
    printf("\t\t3、借还书前请携带自己的学生证，按系统指令完成注册。\n");
    printf("\t\t4、对于借书逾期(60天)不还者，本系统有权取消其借书资格。\n");
    printf("\t\t5、本系统最终解释权归开发团队所有。\n");
    SetConsoleTextAttribute(Color, 0xF );
    getch();
    c_scr();
}
void Welcome(void)
{

    system("color 1F");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
            "\t\t\t\t========================================\n\n"
            "\t\t\t\t   欢 迎 进 入 图 书 管 理 系 统\n\n"
            "\t\t\t\t========================================\n"
            "\t\t\t\t                            ");
    //SetConsoleTextAttribute(Color, 0xF0 );
    //puts("按任意键继续");
    //SetConsoleTextAttribute(Color, 0x1F );

    printf("\n\n\n\n\n\n"
           "\t\t\t\t  图书管理系统. All Rights Reserved.\n\n\n");
    //system("PAUSE");
    getch();
    c_scr();
}

void PrinMenu(void)
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);

    //system("color 1F");
    printf("\n\n\n\n\n\n\n\n");
    SetConsoleTextAttribute(Color, 0x3F);
    printf("\n\n"
           "\t\t\t\t  ________________________________________________  \n");
    printf(
           "\t\t\t\t |                                                | \n"
           "\t\t\t\t |【1】 新用户注册                      【2】 登录| \n"
           "\t\t\t\t |【3】 检索所有图书 / 借书                       | \n"
           "\t\t\t\t |【4】 还书 / 查询                               | \n"
           "\t\t\t\t |【5】 修改/注销                                 | \n"
           "\t\t\t\t |                                                | \n"
           "\t\t\t\t |                           管理员功能           | \n"
           "\t\t\t\t |                 -----------------------------  | \n"
           "\t\t\t\t |                 【6】管理图书/修改管理员密码   | \n"
           "\t\t\t\t |                 【7】解封账号  【8】查询密码   | \n"
           "\t\t\t\t |                 -----------------------------  | \n"
           "\t\t\t\t |                                                | \n"
           "\t\t\t\t |                            【0】退出  【9】帮助| \n"
           "\t\t\t\t |________________________________________________| \n"
           "\t\t\t\t                                                    \n");
    SetConsoleTextAttribute(Color, 0x0F );
    printf("\n\n\n\n");
    printf("\t\t");
    gettime();
    printf("\t\t现在，请输入您的选项：");
}

void PrinAdmin(void)        //打印admin的图案
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Color, 0xc );
    printf("\t\t\t\t      AA         d\n"
           "\t\t\t\t     AA A        d          **\n"
           "\t\t\t\t    BA   A    dddd  mmmmm       nnnnn\n"
           "\t\t\t\t   AAAAAAAA   d  d  m m m   **  nn nn\n"
           "\t\t\t\t  AA      AA  dddd  m m m   **  nn nn\n");
    SetConsoleTextAttribute(Color, 0xf );
}

void AdminMenu(void)        //admin菜单
{
    puts(LINE);
    printf("%s【HI ADMIN】\n\n\n\n\n", SKIN);
    PrinAdmin();
    printf("\t\t\t\t[-----------------------------------------]\n"
           "\t\t\t\t[****************1            管理图书信息] \n"
           "\t\t\t\t[***********2       从外部文件导入图书信息]\n"
           "\t\t\t\t[********3        将图书信息导出到外部文件]\n"
           "\t\t\t\t[************4          修改管理员ID或密码]\n"
           "\t\t\t\t[*********************7          注销ADMIN]\n"
           "\t\t\t\t[-----------------------------------------]\n"
           "\t\t\t\t [INPUT] ");
}

void AdminManageUI_1(void)  //admin管理界面
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 0xCF );
    printf("                                            ====管理图书信息====                                               \n");
    SetConsoleTextAttribute(hConsole, 0xF );
    printf("\n\n\n\n");
    printf("%s\b\b【管理图书信息】\n\n\n\n\n\n\n\n", SKIN);
    //puts("这里是全部的图书列表。\n\n\n");
}

void AdminManageUI_2(void)
{
    printf("\t===================================================================================================\n"
           "\t【<】上一页    【1】按关键字查找       【2】按专业查找        【3】按作者查找           【>】下一页\n"
           "\t【a】增加图书信息       【d】删除图书信息    【c】 *清空所有图书信息（不可逆）【r】撤销上一次的删除\n"
           "\t【~】显示全部信息                                                                       【q】返回\n"
           "\t===================================================================================================\n"
           "\t输入您的选项【INPUT】");
}






/***************admin loggin*******************/
int AdminLoggin(void)       //admin登陆界面
{
    FILE *fp;
    int i;
    int size;
    char name[NAME_SIZE], fname[NAME_SIZE];
    char passwd[PASSWD_SIZE], fpasswd[PASSWD_SIZE];

    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    if ((fp = fopen("1.adm", "a+")) == NULL)
    {
        printf("管理员密钥管理文件已损坏，无法进入管理员系统。\n");
        return 0;
    }
    i = fscanf(fp, "%s%s", fname, fpasswd);

    if (i != 2)
    {
        fprintf(fp, "admin admin");
        printf("这是您第一次使用管理员系统，请用默认账户密码(admin/admin)登陆。\n"
               "      在登陆后请先修改默认的admin账户信息。\n");
    }
    fclose(fp);

    fp = fopen("1.adm", "r");
    fscanf(fp, "%s%s", fname, fpasswd);
    puts(LINE);
    printf("%s【Hi，Admin】\n\n\n\n\n", SKIN);
    PrinAdmin();
    printf("\t\t\t\t[-----------------------------------------]\n");
    SetConsoleTextAttribute(color, 0xF0 );
    printf("\t\t\t\t PLEASE        LOG          IN       FIRST \n");
    SetConsoleTextAttribute(color, 0x0f );
    printf("\t\t\t\t  【name】\t\t");
    SetConsoleTextAttribute(color, 0x3 );
    scanf("%20s", name);
    SetConsoleTextAttribute(color, 0xf );
    printf("\t\t\t\t  【password】\t\t");
    SetConsoleTextAttribute(color, 0x0 );
    scanf("%16s", passwd);
    SetConsoleTextAttribute(color, 0xf );
    printf("\t\t\t\t[-----------------------------------------]\n");

    size = strlen(fname);
    for (i = 0; i < size; i ++)
        if (name[i] != fname[i])
        {
            getchar();
            return 0;
        }
    size = strlen(fpasswd);
    for (i = 0; i < size; i ++)
        if (passwd[i] != fpasswd[i])
        {
            getchar();
            return 0;
        }
    c_scr();
    fclose(fp);
    return 1;
}

void AdminManage(Book_List * pList)    //Admin管理界面
{
    int choices;

    while (1)
    {
        AdminMenu();
        scanf("%d", &choices);
        switch (choices)
        {
        case 1:
            BookManage(pList);
            break;
        case 2:
            FileToList(pList);
            break;
        case 3:
            ListToFile(pList);
            break;
        case 4:
            ChangeAdmin();
            break;
        case 7:
            c_scr();
            return;
        default:
            prin_erro(ERRO_NUM);
        }
        while (getchar() != '\n')
            prin_erro(NO_CHAR);
    }
}







/**************admin 1实现 ********************/
void AddNodeFromFile(Book_List * pList, char * str)   //从文件写入链表
{
    FILE * fp;
    Book_Node * newnode;
    char end;
    //int status = 0;                                           //判断是否有#号标识符

    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    if ((fp = fopen(str, "r")) == NULL)
    {
        SetConsoleTextAttribute(Color, 0xC );
        printf("[!]图书管理文件损坏或不存在，无法读入图书文件。\n");
        SetConsoleTextAttribute(Color, 0xf );
        return;
    }
    /**while ((end = fgetc(fp)) != EOF)
        if (end == '#')
            status++;**/
//    if (status == 0)

    end = fgetc(fp);
    if (end != EOF)
    {                                                   //不是空文件
        rewind(fp);
        do
        {
            newnode = (Book_Node *) malloc (sizeof(Book_Node));

            get_strFromFile(newnode->title, TITLE_SIZE, fp);
            if (newnode->title[0] == '#')
                break;
            get_strFromFile(newnode->domain, TITLE_SIZE, fp);

            if (fscanf(fp, "%13s,%f\n", newnode->number, &newnode->price) != 2)
                break;
            get_strFromFile(newnode->author, TITLE_SIZE, fp);
            get_strFromFile(newnode->publish, TITLE_SIZE, fp);

            newnode->next = *pList;
            *pList = newnode;
        }while(!feof(fp));
    }
    if (fclose(fp) != 0)
        printf("关闭文件时出错。\n");
}

void log_AddNodeFromFile(Book_List * pList, char * str)   //从文件写入链表自带log
{
    FILE * fp;
    Book_Node * newnode;
    char end;                                           //判断是空文件

    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    if ((fp = fopen(str, "r+")) == NULL)
    {
        SetConsoleTextAttribute(Color, 0xC );
        printf("[!]图书管理文件损坏，无法读入图书文件。\n");
        SetConsoleTextAttribute(Color, 0xF );
        return;
    }
    end = fgetc(fp);
    if (end != EOF)
    {                                                   //未到达文件尾
        rewind(fp);
        do
        {
            newnode = (Book_Node *) malloc (sizeof(Book_Node));

            get_strFromFile(newnode->title, TITLE_SIZE, fp);
            if (newnode->title[0] == '#')
                break;
            get_strFromFile(newnode->domain, TITLE_SIZE, fp);
            if (fscanf(fp, "%13s,%f\n", newnode->number, &newnode->price) != 2)
                break;
            get_strFromFile(newnode->author, TITLE_SIZE, fp);
            get_strFromFile(newnode->publish, TITLE_SIZE, fp);

            //输出状态
            SetConsoleTextAttribute(Color, 0x2 );
            printf("[success read:title= %s, author = %s]\n", newnode->title, newnode->author);
            SetConsoleTextAttribute(Color, 0xF );

            newnode->next = *pList;
            *pList = newnode;
        }while (!feof(fp));
    }
    else
    {
        SetConsoleTextAttribute(Color, 0x2 );
        printf("尚未储存过任何记录。\n");
        SetConsoleTextAttribute(Color, 0xF );
    }
    if (fclose(fp) != 0)
        printf("关闭文件时出错。\n");
}

void AddNodeToFile(Book_List * pList, char * str)   //将链表写入文件
{
    FILE * fp;
    Book_Node * walker = *pList;
    if ((fp = fopen(str, "w+")) == NULL)
    {
        printf("[!]图书管理文件损坏，无法将数据导出至文件。\n");
        return;
    }
    while (walker != NULL)
    {
        fputs(walker->title, fp);
        putc('\n', fp);
        fputs(walker->domain, fp);
        putc('\n', fp);
        fprintf(fp, "%s,%.2f\n", walker->number, walker->price);
        fputs(walker->author, fp);
        putc('\n', fp);
        fputs(walker->publish, fp);
        putc('\n', fp);
        walker = walker->next;

//        printf("[已导出: TITLE = %s， DOMAIN = %s， NUMBER = %d， PRICE = %.2f"
//               "AUTHOR = %s, PUBLISH = %s]\n", walker->title, walker->domain,
//               walker->number, walker->price, walker->author, walker->publish);
    }
        fprintf(fp,"#\n");
    if (fclose(fp) != 0)
        printf("关闭文件时出错。\n");
}

void log_AddNodeToFile(Book_List * pList, char * str)   //将链表写入文件(log版)
{
    FILE * fp;
    Book_Node * walker = *pList;
    if ((fp = fopen(str, "w+")) == NULL)
    {
        printf("[!]图书管理文件损坏，无法将数据导出至文件。\n");
        return;
    }
    while (walker != NULL)
    {
        fputs(walker->title, fp);
        putc('\n', fp);
        fputs(walker->domain, fp);
        putc('\n', fp);
        fprintf(fp, "%s,%.2f\n", walker->number, walker->price);
        fputs(walker->author, fp);
        putc('\n', fp);
        fputs(walker->publish, fp);
        putc('\n', fp);

        printf("[已导出: TITLE = %s, DOMAIN = %s, NUMBER = %s, PRICE = %.2f"
               "AUTHOR = %s, PUBLISH = %s]\n",
               walker->title, walker->domain,walker->number, walker->price,
                walker->author, walker->publish);
        walker = walker->next;

    }
        fprintf(fp,"#\n");
    if (fclose(fp) != 0)
        printf("关闭文件时出错。\n");
}

int GetListSize(Book_List * List)         //返回链表长度
{
    int size = 0;
    Book_Node * walker = *List;

    if (*List == NULL)
        return 0;
    else
    {
        while (walker != NULL)
        {
            size++;
            walker->id = size;
            walker = walker->next;
        }
        return size;
    }
}

void ShowAllList(Book_List List, int status, int size)  //遍历链表
{
    int i;
    static int page = 1;
    int page_number;
    static int beggin = 0;
    Book_Node * walker = List;

    printf("%s\n  %s\n", STATUS, START);

    if (size == 0)
        page_number = 1;
    else
    {
        if (size % PAGE_SIZE == 0)                      //计算总页数
            page_number = size / PAGE_SIZE;
        else
            page_number = size / PAGE_SIZE + 1;
    }
    page = page + status ;                           //计算正在显示的页数
    beggin = (page - 1) * PAGE_SIZE;                //计算页数对应的偏移量
    if(page< 1)
    {
        printf("\t\t\t\t\t\n没有上一页了。\n\n");
        page = 0;                             //将页数定格在0页
        return;
    }
    else if (page > (size / PAGE_SIZE) + 1)
    {
        printf("\t\t\t\t\t\n没有下一页了。\n\n");
        page = page_number + 1;            //将页数定格在最后一页的后一页
        return;
    }
    if (List == NULL)
        printf("\t\t\t>>>>>>>>>>>>> 未录入任何图书信息 <<<<<<<<<<<<<<<<<\n");
    else
    {
        if (page > 0 && page < page_number + 1)        //页数在许可范围内
            for (i = 0; i < beggin; i++)     //把walker移动beggin个位置
                walker = walker->next;
        for (i = 0; i < PAGE_SIZE; i++)
        {
            if (walker == NULL)
                break;
            printf("\t%-7d%-19s%-10s%-14s%-7.2f%-12s%s\n",
                    walker->id, walker->title, walker->domain, walker->number,
                    walker->price, walker->author, walker->publish);
            walker = walker->next;
            }
        while (walker != NULL)
        {
            walker = walker->next;
        }
    }

    printf("  %s\n", START);
    if (page <= 0)                      //由page计算正在显示的页数
        i =  1;
    else if(page >= page_number)
        i = page_number;
    else
        i = page;
    printf("\t\t\t\t\t\t第%d页/", i);
    if (size == 0)                      //由size计算所有的页数
        i = 1;
    else
        i = page_number;
    printf("共%d页\n", i);
}

void AddList(Book_List * pList)         //增加节点
{
    Book_Node * newnode;

    int log = 0;
    char tmp_title[TITLE_SIZE];
    char tmp_domain[TITLE_SIZE];
    char tmp_author[TITLE_SIZE];
    char tmp_publish[TITLE_SIZE];
    char tmp_number[NUMBER_SIZE];
    float tmp_price;

    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    c_scr();
    SetConsoleTextAttribute(Color, 0x3F );
    printf("                                                                                                               \n"
           "                                                                                                               \n"
           "                                                                                                               \n"
           "                 以图书名称、专业领域、图书编号、单价、作者、出版社的顺序录入图书信息，                        \n"
           "                 您有义务保证录入信息的准确性.图书编号即ISBN码的13位数字部分                                   \n"
           "                 输入完一本图书的全部信息后，                                                                  \n"
           "                 按【ENTER】继续下一本图书的录入。最后一行直接按【#】键结束录入。                              \n"
           "                                                                                                               \n"
           "                                                                                                               \n"
           "                                                                                                               \n\n\n\n");
    SetConsoleTextAttribute(Color, 0xF );
    /**printf("\n\n\n"
           "\t新增录入清单：\n"
           "ID\t图书名称\t\t\t专业领域\t图书编号\t单价\t作者\t\t出版社\n");

    **/
    //printf("%s\n", START);

    while (1)
    {
        newnode = (Book_Node *) malloc (sizeof(Book_Node));

        printf("\t\t\t");
        printf("图书名称=");
        get_str(tmp_title, NAME_SIZE);
        if (tmp_title[0] == '#')
            break;
        printf("\t\t\t专业领域=");
        get_str(tmp_domain, NAME_SIZE);
        printf("\t\t\t图书作者=");
        get_str(tmp_author, NAME_SIZE);
        printf("\t\t\t出版社=");
        get_str(tmp_publish, NAME_SIZE);
        printf("\t\t\t图书编号=");
        if (get_long_number(tmp_number, NUMBER_SIZE) == NULL)
        {
            SetConsoleTextAttribute(Color, 0xC );
            printf("\t\t\t\t[!]录入图书编号时发生错误,可能是因为您未按要求录入.此条记录已作废.\n");
            SetConsoleTextAttribute(Color, 0xF );
             while (getchar() != '\n');
            continue;
        }
        printf("\t\t\t图书价格=");
        if (!scanf("%f", &tmp_price))
        {
            SetConsoleTextAttribute(Color, 0xC );
            printf("\t\t\t\t[!]录入图书价格时发生错误,可能是您未按要求录入.此条记录已作废.\n");
            SetConsoleTextAttribute(Color, 0xF );
             while (getchar() != '\n');
            continue;
        }

        strcpy(newnode->title, tmp_title);
        strcpy(newnode->domain, tmp_domain);
        strcpy(newnode->author, tmp_author);
        strcpy(newnode->publish, tmp_publish);
        strcpy(newnode->number, tmp_number);
        newnode->price = tmp_price;

        newnode->next = *pList;
//        *pList->next = NULL;
        *pList = newnode;

        log++;
        SetConsoleTextAttribute(Color, 0x20 );
        printf("\t\t\t\t\t\t\t\t[已录入]\n");
        SetConsoleTextAttribute(Color, 0xF );
        while (getchar() != '\n')
            ;
    }
    printf("已录入%d条记录。\n", log);
    printf("Done!\n");
}

void ShowByTitle(Book_List List, char * str) //按关键词检索
{
    Book_Node * walker = List;
    int log = 0;

    c_scr();
    AdminManageUI_1();
    printf("%s\n    %s\n", STATUS, START);
    if (List == NULL)
        printf("\t\t\t\t\t图书记录为空\n");
    else
    {
        while (walker != NULL)
        {
            if (strstr(walker->title, str) != NULL)
            {
                printf("\t%-7d%-19s%-10s%-14s%-7.2f%-12s%s\n",
                    walker->id, walker->title, walker->domain, walker->number,
                    walker->price, walker->author, walker->publish);
                log++;
            }
            walker = walker->next;
        }
        if (log == 0)
            printf("\t\t\t\t\t未找到关键词【%s】的相关记录。\n", str);
    }
    printf("    %s\n", START);
}

void ShowByDomain(Book_List List, char * str)       //按领域检索
{
    Book_Node * walker = List;
    int log = 0;

    c_scr();
    AdminManageUI_1();
    printf("%s\n    %s\n", STATUS, START);
    if (List == NULL)
        printf("\t\t\t\t\t图书记录为空\n");
    else
    {
        while (walker != NULL)
        {
            if (strstr(walker->domain, str) != NULL)
            {
                printf("\t%-7d%-19s%-10s%-14s%-7.2f%-12s%s\n",
                    walker->id, walker->title, walker->domain, walker->number,
                    walker->price, walker->author, walker->publish);
                log++;
            }
            walker = walker->next;
        }
        if (log == 0)
            printf("\t\t\t\t\t未找到领域【%s】的相关记录。\n", str);
    }
    printf("    %s\n", START);
}

void ShowByAuthor(Book_List List,char * str)
{
    Book_Node * walker = List;
    int log = 0;

    c_scr();
    AdminManageUI_1();
    printf("%s\n    %s\n", STATUS, START);
    if (List == NULL)
        printf("\t\t\t\t\t图书记录为空\n");
    else
    {
        while (walker != NULL)
        {
            if (strstr(walker->author, str) != NULL)
            {
                printf("\t%-7d%-19s%-10s%-14s%-7.2f%-12s%s\n",
                    walker->id, walker->title, walker->domain, walker->number,
                    walker->price, walker->author, walker->publish);
                log++;
            }
            walker = walker->next;
        }
        if (log == 0)
            printf("\t\t\t\t\t未找到作者关键词【%s】的相关记录。\n", str);
    }
    printf("    %s\n", START);
}

void DelList(Book_List * pList)         //删除节点
{
    Book_Node * cur;
    Book_Node * pre;

    int size = GetListSize(pList);
    int page = 0;
    int i;
    int get_id;
    char ch;
    FILE * fp;

    if ((fp = fopen("rec.book", "a+")) == NULL)
    {
        printf("回收站文件已损坏或不存在，若继续执行删除将不可恢复。\n");
        return;
    }
    while (1)
    {
        c_scr();
        puts(LINE);
        printf("\n\n删除图书信息\n\n\n\n");
        ShowAllList(*pList, page, size);
        printf("\n\n"
               "\t\t\t============================================================\n"
               "\t\t\t< 上一页   请输入要删除图书的id，多个id以空格隔开    下一页>\n"
               "\t\t\t                    输入0退出完成删除\n"
               "\t\t\t============================================================\n");
        printf("【INPUT】");
        while ((scanf("%d", &get_id) == 1) && (get_id != 0))
        {
            i = 0;
            cur = *pList;
            while(cur != NULL)                              //链表非空
            {
                if (cur->id == get_id)
                {
                    i++;
                    printf("[\tsuceess:del id = %d\t\t title = %s\t]\n", cur->id, cur->title);

                    fputs(cur->title, fp);               //将删除的节点写入文件
                    putc('\n', fp);
                    fputs(cur->domain, fp);
                    putc('\n', fp);
                    fprintf(fp, "%s,%.2f\n", cur->number, cur->price);
                    fputs(cur->author, fp);
                    putc('\n', fp);
                    fputs(cur->publish, fp);
                    putc('\n', fp);

                    if (cur == *pList)
                        *pList = cur->next;
                    else
                        pre->next = cur->next;
                }
                pre = cur;
                cur = cur->next;
            }
            if (i == 0)
                printf("\tID%d未找到\n", get_id);
        }
        fputc('#', fp);
        if (get_id == 0)
            break;
        ch = get_first_char();
        if (ch == '>')
            page = 1;
        else if (ch == '<')
            page = -1;
        else
            page = 0;
    }
    fclose(fp);
}

void RecoveryDel(Book_List *pList)              //恢复节点
{
    FILE * fp;

    c_scr();
    puts(LINE);
    printf("\n\n\n");
    printf("\t\t\t将为您恢复上一次删除的数据。\n"
           "\t==============================================\n");

    log_AddNodeFromFile(pList, "rec.book");
    printf("\t==============================================\n");

    fp = fopen("rec.book", "w");
    fclose(fp);
    AddNodeToFile(pList, "bookinfo.book");
}
void FreeList(Book_List * pList)
{
    Book_Node * walker;

    while (*pList != NULL)
    {
        walker = (*pList)->next;
        free(*pList);
        *pList = walker;
    }
}
void ClearAll(Book_List *pList)                  //清空所有信息
{
    char ch;
    FILE *fp;
    system("color 4f");
    printf("\n\n\n\n\n\n\n"
           "\t\t\t警告：此操作会清除所有的图书信息，且不可撤销。\n"
           "\t\t\t是否继续？【Y/N】\n");

    ch = toupper(get_first_char());
    if (ch == 'Y')
    {
        FreeList(pList);
        fp = fopen("bookinfo.book", "w");
        fclose(fp);
        fp = fopen("rec.book", "w");
        fclose(fp);
    }
    system("color 0F");
}

void BookManage(Book_List * pList)      //图书管理菜单
{
    getchar();
    char choices = '~';
    char last_choices;
    char search[TITLE_SIZE];
    int page = 0;
    int Size;                       //增加或减少页数变量,page = 1,增加页数，page = -1， 减少页数

    while (1)
    {
        c_scr();
        Size = GetListSize(pList);
        AdminManageUI_1();

        //printf("[Now=%c]\n", choices);
        switch (choices)
        {
        case '~':
            ShowAllList(*pList, page, Size);
            last_choices = choices;
            break;
        case '1':
            printf("请输入要检索的书名关键词:");
            scanf("%s", search);
            ShowByTitle(*pList, search);
            break;
        case '2':
            printf("请输入要检索的领域关键词:");
            scanf("%s", search);
            ShowByDomain(*pList, search);
            break;
        case '3':
            printf("请输入要检索的作者关键词:");
            scanf("%s", search);
            ShowByAuthor(*pList, search);
            break;
        case 'a':
            AddList(pList);
            AddNodeToFile(pList, "bookinfo.book");
            choices = '~';
            continue;
            //break;
        case 'd':
            DelList(pList);
            choices = '~';
            AddNodeToFile(pList, "bookinfo.book");
            continue;
        case 'c':
            ClearAll(pList);
            choices = '~';
            continue;
            break;
        case 'r':
            RecoveryDel(pList);
            break;
        case 'q':
            break;
        default:
            printf("\a\t\t\t\t输入有误。请重新输入。");
        }

        printf("\n\n\n数据库中共记录了%d本图书的信息。\n\n\n\n\n\n\n", Size);
        AdminManageUI_2();
        if (choices == '<')
        {
            page = -1;
            choices = last_choices;
        } else if (choices == '>')
        {
            page = 1;
            choices = last_choices;
        } else if (choices == 'q')
            break;
        else
            choices = get_first_char();

        //printf("[Next=%c]\n", choices);
    }
    c_scr();
    return;
}












/***********admin 2******************/
void FileToList(Book_List * pList)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char file[40];
    c_scr();
    SetConsoleTextAttribute(hConsole, 0x3F );
    printf("                                          ====导入外部图书数据文件====                                         \n");
    SetConsoleTextAttribute(hConsole, 0xF );

    printf("\n\n"
           "\t\t*您可以导入之前备份过的或自己创建的图书文件，它是个文本文件。\n"
           "\t\t*您需要把与程序放在同一目录下。\n");
    printf("\t\t*若您自己要创建一个包含图书信息的文件，请遵循以下格式：\n");
    SetConsoleTextAttribute(hConsole, 0x3 );
    printf("\t\tTip:图书编号与图书价格之间的逗号为半角的逗号。在文件的最后一行以#加一个空格结束。\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xA );
    printf("\t\t\t[图书名字]\n"
           "\t\t\t[专业领域]\n"
           "\t\t\t[图书编号], [图书价格]\n"
           "\t\t\t[图书作者]\n"
           "\t\t\t[出版社]\n"
           "\t\t\t>>>>>>>下一本图书信息<<<<<<<<<\n"
           "\t\t\t#\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF );
    printf("请输入您要导入的文件名信息:");
    scanf("%39s", file);
    printf("\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF0 );
    printf("                                          ====       STATUS    ====                                            \n\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF );
    log_AddNodeFromFile(pList, file);       //从file读到链表
    AddNodeToFile(pList, "bookinfo.book");
    printf("Done.");
    getch();
    c_scr();
}







/*******admin 3*******************/
void ListToFile(Book_List * pList)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char file[40];
    c_scr();
    SetConsoleTextAttribute(hConsole, 0x3F );
    printf("                                          ====导出外部图书数据文件====                                         \n");
    SetConsoleTextAttribute(hConsole, 0xF );

    printf("\n\n"
           "\t\t*您可以导出所有的图书记录，它是个文本文件。\n"
           "\t\t*它生成后与程序在同一目录下。\n");
    printf("\t\t*生成的文件遵循以下格式：\n");
    SetConsoleTextAttribute(hConsole, 0x3 );
    printf("\t\tTip:图书编号与图书价格之间的逗号为半角的逗号。在文件的最后一行以#加一个空格结束。\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xA );
    printf("\t\t\t[图书名字]\n"
           "\t\t\t[专业领域]\n"
           "\t\t\t[图书编号], [图书价格]\n"
           "\t\t\t[图书作者]\n"
           "\t\t\t[出版社]\n"
           "\t\t\t>>>>>>>下一本图书信息<<<<<<<<<\n"
           "\t\t\t#\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF );
    printf("请输入您将要导出的文件名:");
    scanf("%39s", file);
    printf("\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF0 );
    printf("                                          ====       STATUS    ====                                            \n\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF );
    log_AddNodeToFile(pList, file);       //从链表写到文件
    printf("Done.");
    getch();
    c_scr();
}





/************admin  4  ************/
void ChangeAdmin(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *fp;
    char id[TITLE_SIZE];
    char passwd[PASSWD_SIZE];

    SetConsoleTextAttribute(hConsole, 0xCF );
    printf("\n\n                                          ====更改管理员密匙====                                               \n\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF );

    fp = fopen("1.adm", "w");
    printf("\n\n");
    printf("\t\t\t\t[新的管理员ID]\t");
    SetConsoleTextAttribute(hConsole, 0xc );
    scanf("%16s", id);
    SetConsoleTextAttribute(hConsole, 0xF );
    printf("\t\t\t\t[新的管理员密码]\t");
    SetConsoleTextAttribute(hConsole, 0x0 );
    scanf("%16s", passwd);
    SetConsoleTextAttribute(hConsole, 0xF );

    fprintf(fp, "%s %s", id, passwd);
    fclose(fp);
    printf("Done.\n");
    getch();
    c_scr();
}
