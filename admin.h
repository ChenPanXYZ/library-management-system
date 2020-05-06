/*********************************************************
                      管理员模块
              Written by 计1704 罗廷忠
                       20174693
*********************************************************/

#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#include <stdio.h>

#define LINE "===============================================================================================================\n"
#define SKIN "                                                                                                 "
#define START "*******************************************************************************************************"
#define STATUS "\tID     图书名称          专业领域     图书编号   单价   作者       出版社"
    //         5             10              4           5           5          10
//常量
#define NAME_SIZE 20
#define PASSWD_SIZE 16
#define NUMBER_SIZE 14
#define TITLE_SIZE 40
#define PAGE_SIZE 15

//错误信息
#define NO_CHAR "您不能在这里输入数字以外的字符。\n"
#define ERRO_NUM "您的选项超过许可范围。\n"
#define FIRST_PAGE "已经是第一页。\n"
#define LAST_PAGE "已经是最后一页。\n"

/**定义结构体**/

//书本信息结构体，定义类型BOOK
typedef struct book {
    int id;                     //操作书本信息(包括查询、添加、修改）所使用的id。该id会在每一次遍历链表时重新分配。
    char title[TITLE_SIZE];
    char domain[TITLE_SIZE];             //专业领_
    char number[NUMBER_SIZE];                //图书编号
    float price;                  //单价
    char author[TITLE_SIZE];      //作者
    char publish[TITLE_SIZE];     //出版社
    struct book * next;
} Book_Node;
//书本信息的链表，定义类型为Book_List
typedef Book_Node * Book_List;

/**定义函数**/

//字符串输入函数
char * get_str(char * ch, int n);
//从文件st中读取一次字符串记录
char * get_strFromFile(char * ch, int n, FILE *st);
void c_scr(void);
void prin_erro(char *);
char get_first_char(void);
char * get_long_number(char * ch, int n);

//从文件读取书本信息链表
void ReadBookList(Book_List * pList);

//--主菜单
void gettime(void);
void PrinMenu(void);
void Welcome(void);

//--ADMIN菜单
void PrinAdmin(void);
//admin登陆界面，若登陆成功返回1，否则返回0
int AdminLoggin(void);
//admin管理界面
void AdminManage(Book_List * pList);

//--ADMIN 1 管理图书
void BookManage(Book_List * pList);
//--ADMIN 2 从外部文件导入
void FiletoList(Book_List * pList);
//--Admin 3 导出到外部
void ListToFile(Book_List * pList);
//--admin 4 密匙更改
void ChangeAdmin(void);

//管理界面
void AdminManageUI_1(void);
void AdminManageUI_2(void);

//--操作链表的函数
//从文件添加节点
void AddNodeFromFile(Book_List * pList, char * str);
//文件添加节点（Log版）
void log_AddNodeFromFile(Book_List * pList, char * str);
//把链表写入到一个文件中
void AddNodeToFile(Book_List * pList, char * str);
//把链表写入到一个文件(Log版)
void log_AddToFromFile(Book_List * pList,char * str);

//获取链表长度
int GetListSize(Book_List * List);
//遍历链表
void ShowAllList(Book_List List, int page, int size);
//增加节点
void AddList(Book_List *pList);
//按姓名检索
void ShowByTitle(Book_List List, char * str);
//按领域检索
void ShowByDomain(Book_List List, char * str);
//按作者检索
void ShowByAuthor(Book_List List,char * str);
//删除节点
void DelList(Book_List * pList);
//恢复节点
void RecoveryDel(Book_List *pList);
//清空链表
void FreeList(Book_List *pList);
//清空信息
void ClearAll(Book_List *pList);

void Help(void);

#endif // STRUCT_H_INCLUDED
