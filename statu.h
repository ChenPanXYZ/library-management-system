/************************************************
*               ����/����/��ѯģ��
*             Written by ��1704 ����
*                   20174438
*************************************************/
#ifndef STATU_H_INCLUDED
#define STATU_H_INCLUDED

#include <time.h>
#include "admin.h"
#include "student.h"


/******************�ṹ��************************/

//�鱾״̬�ڵ�
typedef struct status {
    Book_Node book;                             //�����鱾��Ϣ�ṹ���ȫ����Ϣ
    Student_Node student;                       //����ѧ����Ϣ
    int status;                                 //����״̬���Ѿ�����Ϊ1��Ϊ����Ϊ0.
    time_t brrow_book_t;                             //�����������
    time_t return_book_t;                            //��������
    //struct tm * borrow_book;
    //struct tm * return_book;
    struct status * next;
} Status_Node;
//�鱾״̬����
typedef Status_Node * Status_List;

/************************************************/


/*******************���溯��********************/

//�û�����ʱ��
//����ǰʱ���뵽��ʱ������7�죬��ʾһ����ɫ�Ǻ�
void PrinWARN(Status_Node * sNode);

//��ѯ/�����UI
void ReferUI(Status_List * pSList, Student_Node * student, int status);

//����ͼ���UI
void StatusUI(Status_List * pSList, Student_Node * student, int status);    //���幹��
void StatusUI_1(void);  //UI�ϰ벿��
void StatusUI_2(void);  //UI�°벿��

/***********************************************/


/**************���ܺ���************************/

//�ڳ���ʼʱ��
//�����鱾�����ͼ����Ϣ��״̬������
void CopyBookInfo(Book_List * pBList, Status_List * pSList);

//����ʼʱ��
//��ȡ����״̬��Ϣ���ļ���
//������ͼ����صĽ�����Ϣ
void LoadStatus(Status_List * pSList);

//ÿһ��״̬��Ϣ�ĸ���(�軹�������
//��״̬���������ļ���
//��״̬��Ϣ����һ��
void Status_ListToFile(Status_List * pSList);

//ÿһ�μ�������ͼ��(������ѯ���棩
//Ϊÿһ���ڵ����·���id
//����������
int Status_GetListSize(Status_List * pSList);

//ÿһ�μ�������ͼ��
//����״̬����
//��ʾ����ͼ��Ľ������
void Status_ShowAllList(Status_List SList, int page, int size);

//�û�����ͼ������
//����������������
//��ӡ����������Ϣ
void Status_ShowByTitle(Status_List SList, char * str);

//�û�����ͼ������
//�������а��������
//��ӡ����������Ϣ
void Status_ShowByDomain(Status_List sList, char * str);

//�û�����ͼ������
//�������м���
//��ӡ����������Ϣ
void Status_ShowByAuthor(Status_List List,char * str);

//����������û�����ͼ��ID
//��ͼ��״̬�����ͼ��״̬��Ϊ1,�û����Խ������Ŀ+1�򲻱�
//��ʾ���(ʧ��/�ɹ�)
void BorrowBook(Status_List * pSList, int id, Student_Node * student);

//�û����в�ѯ����
//��״̬�����в����û�����
//��ʾ�û�������Ϣ
void WhatIBorrow(Status_List * pSList, Student_Node * student);

//����������û�����ͼ��ID
//��ͼ��״̬�����ͼ��״̬��Ϊ0���û�������Ŀ-1
//��ʾ������ɹ���
void ReturnBook(Status_List * pSList, int id, Student_Node * student);

int CheckStudent(Status_List * pSList, Student_Node * student);
/***********************************************/

#endif // STATU_H_INCLUDED
