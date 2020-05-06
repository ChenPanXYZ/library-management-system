/************************************************
*               学生注册/登陆模块
*             Written by 计1704 谭鸿锐
*                   20174712
*************************************************/

#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

/*************结构体和链表**********************/

#include "admin.h"

//学生结构体节点,定义其类类型为STUDENT_NODE
typedef struct student
{
    char name[NAME_SIZE];
    char sex;
    char s_number[9];
    char password[PASSWD_SIZE];
    int status;                                 //账号状态，被封为0，正常为1;
    //time_t seal;                                //如果账号被封，储存账号被封存的时间
    int booknumber;                              //已经借的书本数目
    struct student *next;
}Student_Node;

//学生链表,定义其类型为STUDENT_LIST
typedef Student_Node * Student_List;
/************************************************/


/************界面函数****************************/

//注册--界面函数
void Register(Student_List * pList);

//登录 -- 界面/功能函数--登陆成功返回1， 否则返回0
int Loggin(Student_List * pList, int loggin, Student_Node * stuent);

//显示用户登陆成功后的欢迎界面
void Welcome_Student(int status, Student_Node student);

/************************************************/

/***************功能函数*************************/

//注册--功能函数：
//添加链表节点
void AddStudent(Student_List * pList);

//将链表导出到文件
void Student_ListToFile(Student_List * pList);

//在链表查找学号/姓名
//判断是否被注册过,
//注册过返回1，否则返回0
int Is_Register(Student_List * pList, char * number);

//从文件导入链表
void Student_FileToList(Student_List * pList);

//登录成功后
//将正在登陆的学生信息保存在student结构体里
void SaveStudent(Student_List * pList, Student_Node * student, char * num, char * passwd);

//每一次到达开始菜单末尾(用户已经完成操作)
//将student结构体的信息重新写进链表里
//用户链表里信息的更新
void Update_StudentList(Student_List * pList, Student_Node * student);

//用户登陆后
//注销或修改信息
//信息所在的节点被修改
int QuitorChange_Student(Student_List * pList,Student_Node * pNode, int status);

//用户申请解封账号
//从链表里查找status为0的账号，并显示出来
//将status改为1
void RecStudnt(Student_List * sList);

//用户忘记密码
//从链表里查找学号
//显示用户信息
void FindPasswd(const Student_List * sList);
/************************************************/
#endif // STUDENT_H_INCLUDED
