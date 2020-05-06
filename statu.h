/************************************************
*               借书/还书/查询模块
*             Written by 计1704 陈攀
*                   20174438
*************************************************/
#ifndef STATU_H_INCLUDED
#define STATU_H_INCLUDED

#include <time.h>
#include "admin.h"
#include "student.h"


/******************结构体************************/

//书本状态节点
typedef struct status {
    Book_Node book;                             //包含书本信息结构体的全部信息
    Student_Node student;                       //包含学生信息
    int status;                                 //借阅状态，已经借阅为1，为借阅为0.
    time_t brrow_book_t;                             //储存借阅日期
    time_t return_book_t;                            //还书日期
    //struct tm * borrow_book;
    //struct tm * return_book;
    struct status * next;
} Status_Node;
//书本状态链表
typedef Status_Node * Status_List;

/************************************************/


/*******************界面函数********************/

//用户还书时，
//若当前时间与到期时间少于7天，显示一个红色星号
void PrinWARN(Status_Node * sNode);

//查询/还书的UI
void ReferUI(Status_List * pSList, Student_Node * student, int status);

//检索图书的UI
void StatusUI(Status_List * pSList, Student_Node * student, int status);    //主体构架
void StatusUI_1(void);  //UI上半部分
void StatusUI_2(void);  //UI下半部分

/***********************************************/


/**************功能函数************************/

//在程序开始时，
//复制书本链表的图书信息到状态链表里
void CopyBookInfo(Book_List * pBList, Status_List * pSList);

//程序开始时，
//读取储存状态信息的文件，
//加载与图书相关的借阅信息
void LoadStatus(Status_List * pSList);

//每一次状态信息的更新(借还书操作）
//将状态链表导出到文件，
//将状态信息更新一遍
void Status_ListToFile(Status_List * pSList);

//每一次检索所有图书(或进入查询界面）
//为每一个节点重新分配id
//返回链表长度
int Status_GetListSize(Status_List * pSList);

//每一次检索所有图书
//遍历状态链表
//显示所有图书的借阅情况
void Status_ShowAllList(Status_List SList, int page, int size);

//用户输入图书姓名
//从链表中搜索姓名
//打印搜索到的信息
void Status_ShowByTitle(Status_List SList, char * str);

//用户输入图书领域
//在链表中按领域检索
//打印检索到的信息
void Status_ShowByDomain(Status_List sList, char * str);

//用户输入图书作者
//在链表中检索
//打印检索到的信息
void Status_ShowByAuthor(Status_List List,char * str);

//借书操作，用户输入图书ID
//将图书状态链表的图书状态改为1,用户可以借书的数目+1或不变
//显示结果(失败/成功)
void BorrowBook(Status_List * pSList, int id, Student_Node * student);

//用户进行查询操作
//在状态链表中查找用户名字
//显示用户借阅信息
void WhatIBorrow(Status_List * pSList, Student_Node * student);

//还书操作，用户输入图书ID
//将图书状态链表的图书状态改为0，用户借书数目-1
//显示结果（成功）
void ReturnBook(Status_List * pSList, int id, Student_Node * student);

int CheckStudent(Status_List * pSList, Student_Node * student);
/***********************************************/

#endif // STATU_H_INCLUDED
