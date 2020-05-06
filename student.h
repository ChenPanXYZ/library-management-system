/************************************************
*               ѧ��ע��/��½ģ��
*             Written by ��1704 ̷����
*                   20174712
*************************************************/

#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

/*************�ṹ�������**********************/

#include "admin.h"

//ѧ���ṹ��ڵ�,������������ΪSTUDENT_NODE
typedef struct student
{
    char name[NAME_SIZE];
    char sex;
    char s_number[9];
    char password[PASSWD_SIZE];
    int status;                                 //�˺�״̬������Ϊ0������Ϊ1;
    //time_t seal;                                //����˺ű��⣬�����˺ű�����ʱ��
    int booknumber;                              //�Ѿ�����鱾��Ŀ
    struct student *next;
}Student_Node;

//ѧ������,����������ΪSTUDENT_LIST
typedef Student_Node * Student_List;
/************************************************/


/************���溯��****************************/

//ע��--���溯��
void Register(Student_List * pList);

//��¼ -- ����/���ܺ���--��½�ɹ�����1�� ���򷵻�0
int Loggin(Student_List * pList, int loggin, Student_Node * stuent);

//��ʾ�û���½�ɹ���Ļ�ӭ����
void Welcome_Student(int status, Student_Node student);

/************************************************/

/***************���ܺ���*************************/

//ע��--���ܺ�����
//�������ڵ�
void AddStudent(Student_List * pList);

//�����������ļ�
void Student_ListToFile(Student_List * pList);

//���������ѧ��/����
//�ж��Ƿ�ע���,
//ע�������1�����򷵻�0
int Is_Register(Student_List * pList, char * number);

//���ļ���������
void Student_FileToList(Student_List * pList);

//��¼�ɹ���
//�����ڵ�½��ѧ����Ϣ������student�ṹ����
void SaveStudent(Student_List * pList, Student_Node * student, char * num, char * passwd);

//ÿһ�ε��￪ʼ�˵�ĩβ(�û��Ѿ���ɲ���)
//��student�ṹ�����Ϣ����д��������
//�û���������Ϣ�ĸ���
void Update_StudentList(Student_List * pList, Student_Node * student);

//�û���½��
//ע�����޸���Ϣ
//��Ϣ���ڵĽڵ㱻�޸�
int QuitorChange_Student(Student_List * pList,Student_Node * pNode, int status);

//�û��������˺�
//�����������statusΪ0���˺ţ�����ʾ����
//��status��Ϊ1
void RecStudnt(Student_List * sList);

//�û���������
//�����������ѧ��
//��ʾ�û���Ϣ
void FindPasswd(const Student_List * sList);
/************************************************/
#endif // STUDENT_H_INCLUDED
