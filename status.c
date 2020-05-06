/************************************************
*               借书/还书/查询模块
*             Written by 计1704 陈攀
*                   20174438
*************************************************/
#include "statu.h"
#include "admin.h"
#include "student.h"
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*******************界面函数********************/

//用户还书时，
//若当前时间与到期时间少于7天，显示一个红色星号
void PrinWARN(Status_Node * sNode)
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    time_t today = time(NULL);
    SetConsoleTextAttribute(Color, 0xCF );
    if (difftime(sNode->return_book_t, today) <= (14 * 3600 * 24))   //离还书日少于14天
        printf("[*]");
    SetConsoleTextAttribute(Color, 0xF );
}

//查询/还书的UI
void ReferUI(Status_List * pSList, Student_Node * student, int status)
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(Color, 0xF0 );
    printf("\n\n                                            借书/还书                                                   \n");
    SetConsoleTextAttribute(Color, 0xF );
    puts("\n\n\n");

    //用户未登录
    if (status == 0)
        puts("\t\t\t\t您尚未登录，不能使用【查询/借书】功能。");
    else
        WhatIBorrow(pSList, student);
}

//检索图书的UI
void StatusUI(Status_List * pSList, Student_Node * student, int status)    //主体构架
{
    system("mode con cols=135 lines=50");//窗口宽度高度
    char choices = '~';
    char last_choices;
    char search[TITLE_SIZE];
    int id;
    int page = 0;
    int Size;                       //增加或减少页数变量,page = 1,增加页数，page = -1， 减少页数

    getchar();
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    while (1)
    {
        c_scr();
        Size = Status_GetListSize(pSList);
        StatusUI_1();

        switch (choices)
        {
        case '~':
            Status_ShowAllList(*pSList, page, Size);
            last_choices = choices;
            break;
        case '1':
            printf("请输入要检索的书名关键词:");
            scanf("%s", search);
            Status_ShowByTitle(*pSList, search);
            break;
        case '2':
            printf("请输入要检索的领域关键词:");
            scanf("%s", search);
            Status_ShowByDomain(*pSList, search);
            break;
        case '3':
            printf("请输入要检索的作者关键词:");
            scanf("%s", search);
            Status_ShowByAuthor(*pSList, search);
            break;
        case 'b':
            if (student->status == 0)       //账号被封
            {
                SetConsoleTextAttribute(Color, 0xC);
                printf("您因为超过期限未还书，因此现在不能借书。\n"
                       "请先到到图书管理员处缴清超期引起的费用。");
                SetConsoleTextAttribute(Color, 0xF);
                getch();
                choices = last_choices;
                continue;
                break;
            }
            if (status == 0)
            {
                SetConsoleTextAttribute(Color, 0xC);
                printf("您尚未登录，因此现在不能借书。\n");
                SetConsoleTextAttribute(Color, 0xF);
                getch();
                choices = last_choices;
                continue;
            }
            printf("请输入要借书的ID，若要借多本书，请以空格隔开。输入0结束输入:");
            SetConsoleTextAttribute(Color, 0x9);
            while (scanf("%d", &id) == 1)
            {
                if (id == 0)
                    break;
                BorrowBook(pSList, id, student);
            }
            c_scr();
            choices = last_choices;
            continue;
        case 'q':
            break;
        default:
            printf("\a\t\t\t\t输入有误。请重新输入。");
        }

        printf("\n\n\n数据库中共记录了%d本图书的信息。\n\n\n\n\n\n\n", Size);
        StatusUI_2();

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
    }
    c_scr();
    system("mode con cols=111 lines=50");//窗口宽度高度
    return;
}
void StatusUI_1(void)  //UI上半部分
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 0xCF );
    printf("                                                            ====检索图书/还书====                                                      \n");
    SetConsoleTextAttribute(hConsole, 0xF );
    printf("\n\n\n\n");
    printf("%s\t\t【检索图书/还书】\n\n\n\n\n\n\n\n", SKIN);
}
void StatusUI_2(void)  //UI下半部分
{
    printf("\t\t===================================================================================================\n"
           "\t\t【<】上一页    【1】按关键字查找       【2】按专业查找        【3】按作者查找           【>】下一页\n"
           "\t\t【~】显示全部信息                            【b】借书                                    【q】返回\n"
           "\t\t===================================================================================================\n"
           "\t\t输入您的选项【INPUT】");
}

/***********************************************/


/**************功能函数************************/

//在程序开始时，
//复制书本链表的图书信息到状态链表里
void CopyBookInfo(Book_List * pBList, Status_List * pSList)
{
    Book_Node * walker = *pBList;
    //Status_Node * copyer = *pSList;
    Status_Node * new;

    while(walker != NULL)
    {
        new = (Status_Node * )malloc(sizeof(Status_Node));
        strcpy(new->book.title, walker->title);
        strcpy(new->book.domain, walker->domain);
        strcpy(new->book.author, walker->author);
        strcpy(new->book.publish, walker->publish);
        strcpy(new->book.number, walker->number);
        strcpy(new->student.name , "-\0");
        new->student.sex = '-';
        strcpy(new->student.s_number ,"-\0");

        new->brrow_book_t = 0, new->brrow_book_t = 0;
        //new->borrow_book->tm_year = 0, new->borrow_book->tm_mon = 0, new->borrow_book->tm_mday = 0;
        //new->return_book->tm_year = 0, new->return_book->tm_mon = 0, new->return_book->tm_mday = 0;
        new->book.price = walker->price;

        new->next = *pSList;
        *pSList = new;

        walker = walker->next;
    }
}

//程序开始时，
//读取储存状态信息的文件，
//加载与图书相关的借阅信息
void LoadStatus(Status_List * pSList)
{
    Status_Node * walker;
    char tmp_title[TITLE_SIZE];
    char tmp[256];
    FILE * fp;
    char end;
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    int status = 0;

    if ((fp = fopen("status.info", "r")) == NULL)
    {
        SetConsoleTextAttribute(Color, 0xC );
        printf("[!]图书检索管理文件损坏，无法读入图书文件。\n");
        SetConsoleTextAttribute(Color, 0xF );
        return;
    }
    end = fgetc(fp);
    if (end != EOF)
    {                                                   //未到达文件尾
        rewind(fp);
        while (1)
        {
            walker = *pSList;                               //初始化walker指针
            get_strFromFile(tmp_title, NAME_SIZE, fp);      //从文件获取标题
            if (tmp_title[0] == '#')                        //读取读取结束符结束读入
                break;
            while (walker != NULL)
            {
                if (strcmp(tmp_title, walker->book.title) == 0) //储存在状态链表里的书本标题与读取的标题一致
                {                                               //将储存在文件里的用户信息储存在链表里
                    strcpy(walker->book.title, tmp_title);
                    get_strFromFile(walker->book.domain, TITLE_SIZE, fp);
                    fscanf(fp, "%13s,%f\n", walker->book.number, &(walker->book.price));
                    get_strFromFile(walker->book.author, TITLE_SIZE, fp);
                    get_strFromFile(walker->book.publish, TITLE_SIZE, fp);
                    get_strFromFile(walker->student.name, NAME_SIZE, fp);
                    walker->student.sex = fgetc(fp);
                    fgetc(fp);
                    fscanf(fp,"%s", walker->student.s_number);
                    fscanf(fp, "%d\n", &walker->status);
                    fscanf(fp, "%ld, %ld\n", &(walker->brrow_book_t), &(walker->return_book_t));
                    status++;
                    break;
                }
                walker = walker->next;                      //将标题和下一个节点的标题比较
            }
            //链表里的标题与文件不一致，用一个tmp数组储存废弃数据
            if(status == 0)
            {
                fgets(tmp, 100, fp);
                fgets(tmp, 100, fp);
                fgets(tmp, 100, fp);
                fgets(tmp, 100, fp);
                fgets(tmp, 100, fp);
                fgets(tmp, 100, fp);
                fgets(tmp, 100, fp);
                fgets(tmp, 100, fp);
                fgets(tmp, 100, fp);
            }
        }
    }
    if (fclose(fp) != 0)
        printf("关闭文件时出错。\n");
}

//每一次状态信息的更新(借还书操作）
//将状态链表导出到文件，
//将状态信息更新一遍
void Status_ListToFile(Status_List * pSList)
{
    FILE * fp;
    Status_Node * walker = *pSList;
    if ((fp = fopen("status.info", "w+")) == NULL)
    {
        printf("[!]图书检索文件损坏，无法将数据导出至文件。\n");
        return;
    }
    while (walker != NULL)
    {
        fputs(walker->book.title, fp);
        putc('\n', fp);
        fputs(walker->book.domain, fp);
        putc('\n', fp);
        fprintf(fp, "%s,%.2f\n", walker->book.number, walker->book.price);
        fputs(walker->book.author, fp);
        putc('\n', fp);
        fputs(walker->book.publish, fp);
        putc('\n', fp);
        fputs(walker->student.name, fp);
        putc('\n', fp);
        putc(walker->student.sex, fp);
        putc('\n', fp);
        fputs(walker->student.s_number, fp);
        putc('\n', fp);
        fprintf(fp, "%d\n", walker->status);
        fprintf(fp, "%ld, %ld\n", walker->brrow_book_t, walker->return_book_t);
        walker = walker->next;
    }
        fprintf(fp,"#\n");
    if (fclose(fp) != 0)
        printf("关闭文件时出错。\n");
}

//每一次检索所有图书(或进入查询界面）
//为每一个节点重新分配id
//返回链表长度
int Status_GetListSize(Status_List * pSList)
{
    int size = 0;
    Status_Node * walker = *pSList;

    if (*pSList == NULL)
        return 0;
    else
    {
        while (walker != NULL)
        {
            size++;
            walker->book.id = size;
            walker = walker->next;
        }
        return size;
    }
}

//每一次检索所有图书
//遍历状态链表
//显示所有图书的借阅情况
void Status_ShowAllList(Status_List List, int status, int size)
{
    int i;
    static int s_page = 1;
    int page_number;
    static int beggin = 0;
//    struct tm * show_b;
    struct tm * show_t;
    Status_Node * walker = List;

    printf("\tID\t图书名称\t专业领域\t图书编号\t单价\t图书状态\t借书人\t性别\t学号\t\t还书时间\n");
    printf(" \t==========================================================================================================================\n");

    if (size == 0)
        page_number = 1;
    else
    {
        if (size % PAGE_SIZE == 0)                      //计算总页数
            page_number = size / PAGE_SIZE;
        else
            page_number = size / PAGE_SIZE + 1;
    }
    s_page = s_page + status ;                           //计算正在显示的页数
    beggin = (s_page - 1) * PAGE_SIZE;                //计算页数对应的偏移量
    if(s_page< 1)
    {
        printf("\t\t\t\t\t\n没有上一页了。\n\n");
        s_page = 0;                             //将页数定格在0页
        return;
    }
    else if (s_page > (size / PAGE_SIZE) + 1)
    {
        printf("\t\t\t\t\t\n没有下一页了。\n\n");
        s_page = page_number + 1;            //将页数定格在最后一页的后一页
        return;
    }
    if (List == NULL)
        printf("\t\t\t>>>>>>>>>>>>> 未录入任何图书信息 <<<<<<<<<<<<<<<<<\n");
    else
    {
        if (s_page > 0 && s_page < page_number + 1)        //页数在许可范围内
            for (i = 0; i < beggin; i++)     //把walker移动beggin个位置
                walker = walker->next;
        for (i = 0; i < PAGE_SIZE; i++)
        {
            if (walker == NULL)
                break;
            //show_b = localtime(&(walker->brrow_book_t));
            show_t = localtime(&(walker->return_book_t));
//            printf("%d\n%d\n", walker->brrow_book_t, walker->return_book_t);
            printf("\t%d\t%-10s\t%10s\t%s\t%.2f\t",
                   walker->book.id, walker->book.title, walker->book.domain, walker->book.number, walker->book.price);
            if(walker->status == 1)
                printf("已被借阅\t");
            else
                printf("未被借阅\t");
            printf("%s\t%c\t%s\t", walker->student.name, walker->student.sex, walker->student.s_number);
            if (walker->brrow_book_t == 0)
                printf("\t- / - / -\n");
            else
                printf("%d/%d/%d\n",
                show_t->tm_year + 1900, show_t->tm_mon + 1, show_t->tm_mday);
            walker = walker->next;
        }
        while (walker != NULL)
        {
            walker = walker->next;
        }
    }

    printf(" \t==========================================================================================================================\n");
    if (s_page <= 0)                      //由page计算正在显示的页数
        i =  1;
    else if(s_page >= page_number)
        i = page_number;
    else
        i = s_page;
    printf("\t\t\t\t\t\t\t\t第%d页/", i);
    if (size == 0)                      //由size计算所有的页数
        i = 1;
    else
        i = page_number;
    printf("共%d页\n", i);
}

//用户输入图书姓名
//从链表中搜索姓名
//打印搜索到的信息
void Status_ShowByTitle(Status_List SList, char * str)
{
    Status_Node * walker = SList;
    int log = 0;
    //struct tm * show_b;
    struct tm * show_t;

    c_scr();
    StatusUI_1();
    //printf("%s\n    %s\n", STATUS, START);
    printf("\tID\t图书名称\t专业领域\t图书编号\t单价\t图书状态\t借书人\t性别\t学号\t\t还书时间\n");
    printf(" \t==========================================================================================================================\n");
    if (SList == NULL)
        printf("\t\t\t\t\t图书记录为空\n");
    else
    {
        while (walker != NULL)
        {
            if (strstr(walker->book.title, str) != NULL)
            {
                show_t = localtime(&(walker->return_book_t));
                log++;
                printf("\t%d\t%-10s\t%10s\t%s\t%.2f\t",
                   walker->book.id, walker->book.title, walker->book.domain, walker->book.number, walker->book.price);
            if(walker->status == 1)
                printf("已被借阅\t");
            else
                printf("未被借阅\t");
            printf("%s\t%c\t%s\t", walker->student.name, walker->student.sex, walker->student.s_number);
            if (walker->brrow_book_t == 0)
                printf("\t- / - / -\n");
            else
                printf("%d/%d/%d\n",
                show_t->tm_year + 1900, show_t->tm_mon + 1, show_t->tm_mday);

            }
            walker = walker->next;
        }
        if (log == 0)
            printf("\t\t\t\t\t未找到标题关键词【%s】的相关记录。\n", str);
    }
    printf(" \t==========================================================================================================================\n");
}

//用户输入图书领域
//在链表中按领域检索
//打印检索到的信息
void Status_ShowByDomain(Status_List sList, char * str)
{
    Status_Node * walker = sList;
    int log = 0;
    struct tm * show_b;
    struct tm * show_r;
    c_scr();
    StatusUI_1();
    //printf("%s\n    %s\n", STATUS, START);
    printf("\tID\t图书名称\t专业领域\t图书编号\t单价\t图书状态\t借书人\t性别\t学号\t\t还书时间\n");
    printf(" \t==========================================================================================================================\n");
    if (sList == NULL)
        printf("\t\t\t\t\t图书记录为空\n");
    else
    {
        while (walker != NULL)
        {
            if (strstr(walker->book.domain, str) != NULL)
            {
                show_r = localtime(&(walker->return_book_t));
                printf("\t%d\t%-10s\t%10s\t%s\t%.2f\t",
                   walker->book.id, walker->book.title, walker->book.domain, walker->book.number, walker->book.price);
            if(walker->status == 1)
                printf("已被借阅\t");
            else
                printf("未被借阅\t");
            printf("%s\t%c\t%s\t", walker->student.name, walker->student.sex, walker->student.s_number);
            if (walker->brrow_book_t == 0)
                printf("\t- / - / -\n");
            else
                printf("%d/%d/%d\n",
                show_r->tm_year + 1900, show_r->tm_mon + 1, show_r->tm_mday);
            }
            walker = walker->next;
        }
        if (log == 0)
            printf("\t\t\t\t\t未找到领域关键词【%s】的相关记录。\n", str);
    }
    printf(" \t==========================================================================================================================\n");
}

//用户输入图书作者
//在链表中检索
//打印检索到的信息
void Status_ShowByAuthor(Status_List List,char * str)
{
    Status_Node * walker = List;
    int log = 0;
    struct tm * show_r;

    c_scr();
    StatusUI_1();

    printf("\tID\t图书名称\t专业领域\t图书编号\t单价\t图书状态\t借书人\t性别\t学号\t\t还书时间\n");
    printf(" \t==========================================================================================================================\n");
    if (List == NULL)
        printf("\t\t\t\t\t图书记录为空\n");
    else
    {
        while (walker != NULL)
        {
            if (strstr(walker->book.author, str) != NULL)
            {
                show_r = localtime(&(walker->return_book_t));
                log++;
               printf("\t%d\t%-10s\t%10s\t%s\t%.2f\t",
                   walker->book.id, walker->book.title, walker->book.domain, walker->book.number, walker->book.price);
            if(walker->status == 1)
                printf("已被借阅\t");
            else
                printf("未被借阅\t");
            printf("%s\t%c\t%s\t", walker->student.name, walker->student.sex, walker->student.s_number);
            if (walker->brrow_book_t == 0)
                printf("\t- / - / -\n");
            else
                printf("%d/%d/%d\n",
                show_r->tm_year + 1900, show_r->tm_mon + 1, show_r->tm_mday);
            }
            walker = walker->next;
        }
        if (log == 0)
            printf("\t\t\t\t\t未找到作者关键词【%s】的相关记录。\n", str);
    }
    printf(" \t==========================================================================================================================\n");
}

//借书操作，用户输入图书ID
//将图书状态链表的图书状态改为1,用户可以借书的数目+1或不变
//显示结果(失败/成功)
void BorrowBook(Status_List * pSList, int id, Student_Node * student)
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    Status_Node * walker = *pSList;
    time_t get_t = time(NULL);
    //time_t

    while (walker != NULL)
    {
        if (id == walker->book.id)
        {
            if (walker->status == 1)
            {
                SetConsoleTextAttribute(Color, 0xC );
                printf("\t\t[借书失败 : 这本书已经被借走]\n");
                SetConsoleTextAttribute(Color, 0xF );
                getch();
                return;
            }
            printf("%s", student->name);
            if (student->booknumber > 10)
            {
                SetConsoleTextAttribute(Color, 0xC );
                printf("\t\t[借书失败 : 您最多只能借十本书]\n");
                SetConsoleTextAttribute(Color, 0xF );
                getch();
                return;
            }
            SetConsoleTextAttribute(Color, 0xF0 );
            printf("\t\t[借书成功 : 书名 = %s, ID = %d]\n", walker->book.title, walker->book.id);
            SetConsoleTextAttribute(Color, 0xF );
            strcpy(walker->student.name, student->name);
            strcpy(walker->student.s_number, student->s_number);
            walker->student.sex = student->sex;
            walker->status = 1;
            student->booknumber++;

            walker->brrow_book_t = get_t;          //获得今日时间
//            walker->borrow_book = localtime(&(walker->brrow_book_t));

            get_t = get_t + (3600 * 24 * 60);
            walker->return_book_t = get_t;
        }
        walker = walker->next;
    }
    Status_ListToFile(pSList);
}

//用户进行查询操作
//在状态链表中查找用户名字
//显示用户借阅信息
void WhatIBorrow(Status_List * pSList, Student_Node * student)
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    Status_Node * walker = *pSList;
    int id;
//    struct tm * show_b;
    struct tm * show_r;

    c_scr();
    Status_GetListSize(pSList);
    SetConsoleTextAttribute(Color, 0xF0 );
    printf("                                                  借书/还书                                                    \n");
    SetConsoleTextAttribute(Color, 0xF );
    puts("\n\n\n");
    printf("你已经借了%d本书。\n\n\n\n", student->booknumber);
    printf("\t\tID\t图书名称\t专业领域\t图书编号\t单价\t还书时间\n");
    printf(" \t==========================================================================================\n");
    while (walker != NULL)
    {
        if (strcmp(walker->student.s_number, student->s_number) == 0)       //链表里有用户的名字
        {
            //show_b = localtime(&(walker->brrow_book_t));
            show_r = localtime(&(walker->return_book_t));
            PrinWARN(walker);
            printf("\t\t%d\t%-10s\t%10s\t%s\t%.2f\t%d/%d/%d\n",
                   walker->book.id, walker->book.title, walker->book.domain, walker->book.number, walker->book.price,
                   //show_b->tm_year + 1900, show_b->tm_mon, show_b->tm_mday,
                   show_r->tm_year + 1900, show_r->tm_mon + 1, show_r->tm_mday);
        }
        walker = walker->next;
    }
    printf(" \t=========================================================================================\n");

    printf("\n\n  傍边加星号");
    SetConsoleTextAttribute(Color, 0xCF );
    printf("[*]");
    SetConsoleTextAttribute(Color, 0xF );
    printf("的记录说明图书要到期了");
    SetConsoleTextAttribute(Color, 0xC );
    printf("(离还书期限还有14天）");
    SetConsoleTextAttribute(Color, 0xF );
    printf("，请尽快还书。\n");
    printf("  输入要还书的id进行还书操作，若还多本书请以空格隔开。输入0退出还书界面。\n");

    SetConsoleTextAttribute(Color, 0xA );
    printf("【请输入要还书的ID】");
    SetConsoleTextAttribute(Color, 0xC );
    while (scanf("%d", &id) == 1)
    {
        if (id == 0)
            return;
        ReturnBook(pSList, id, student);
    }
    while (getchar() != '\n')
        ;
    Status_ListToFile(pSList);
}

//还书操作，用户输入图书ID
//将图书状态链表的图书状态改为0，用户借书数目-1
//显示结果（成功）
void ReturnBook(Status_List * pSList, int id, Student_Node * student)
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);

    Status_Node * walker = *pSList;
    while (walker != NULL)
    {
        if ((id == walker->book.id))
        {
            if(strcmp(student->s_number, walker->student.s_number) == 0)
            {
                SetConsoleTextAttribute(Color, 0xF0 );
                printf("\t\t[还书成功 : 书名 = %s, ID = %d]\n", walker->book.title, walker->book.id);
                SetConsoleTextAttribute(Color, 0xF );
                strcpy(walker->student.name, "-\0");
                strcpy(walker->student.s_number , "-\0");
                walker->student.sex = '-';
                walker->brrow_book_t = 0;
                walker->return_book_t = 0;
                student->booknumber--;
                if (student->booknumber <= 0)
                    student->booknumber = 0;
                walker->status = 0;         //状态=0
            }
            else
            {
                SetConsoleTextAttribute(Color, 0xFC );
                printf("\t\t[还书失败 : 书名 = %s, ID = %d，您未借阅这本书。]\n",
                       walker->book.title, walker->book.id);
                SetConsoleTextAttribute(Color, 0xF );
            }
        }
        walker = walker->next;
    }
    Status_ListToFile(pSList);
}

//登陆成功后
//检查账户状态情况
//借书超期--封号，
int CheckStudent(Status_List * pSList, Student_Node * student)
{
    time_t today = time(NULL);
    Status_Node * walker = *pSList;

    while (walker != NULL)
    {
        if (strcmp(student->s_number, walker->student.s_number) == 0)    //找到学生
            if(today - walker->return_book_t >= 0)                       //超期
            {
                student->status = 0;
                return 0;
            }                                                             //封号
        walker = walker->next;
    }
    return 1;
}

/***********************************************/
