/*********************************************************
                      ����Աģ��
              Written by ��1704 ��͢��
                       20174693
*********************************************************/

#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#include <stdio.h>

#define LINE "===============================================================================================================\n"
#define SKIN "                                                                                                 "
#define START "*******************************************************************************************************"
#define STATUS "\tID     ͼ������          רҵ����     ͼ����   ����   ����       ������"
    //         5             10              4           5           5          10
//����
#define NAME_SIZE 20
#define PASSWD_SIZE 16
#define NUMBER_SIZE 14
#define TITLE_SIZE 40
#define PAGE_SIZE 15

//������Ϣ
#define NO_CHAR "��������������������������ַ���\n"
#define ERRO_NUM "����ѡ�����ɷ�Χ��\n"
#define FIRST_PAGE "�Ѿ��ǵ�һҳ��\n"
#define LAST_PAGE "�Ѿ������һҳ��\n"

/**����ṹ��**/

//�鱾��Ϣ�ṹ�壬��������BOOK
typedef struct book {
    int id;                     //�����鱾��Ϣ(������ѯ����ӡ��޸ģ���ʹ�õ�id����id����ÿһ�α�������ʱ���·��䡣
    char title[TITLE_SIZE];
    char domain[TITLE_SIZE];             //רҵ��_
    char number[NUMBER_SIZE];                //ͼ����
    float price;                  //����
    char author[TITLE_SIZE];      //����
    char publish[TITLE_SIZE];     //������
    struct book * next;
} Book_Node;
//�鱾��Ϣ��������������ΪBook_List
typedef Book_Node * Book_List;

/**���庯��**/

//�ַ������뺯��
char * get_str(char * ch, int n);
//���ļ�st�ж�ȡһ���ַ�����¼
char * get_strFromFile(char * ch, int n, FILE *st);
void c_scr(void);
void prin_erro(char *);
char get_first_char(void);
char * get_long_number(char * ch, int n);

//���ļ���ȡ�鱾��Ϣ����
void ReadBookList(Book_List * pList);

//--���˵�
void gettime(void);
void PrinMenu(void);
void Welcome(void);

//--ADMIN�˵�
void PrinAdmin(void);
//admin��½���棬����½�ɹ�����1�����򷵻�0
int AdminLoggin(void);
//admin�������
void AdminManage(Book_List * pList);

//--ADMIN 1 ����ͼ��
void BookManage(Book_List * pList);
//--ADMIN 2 ���ⲿ�ļ�����
void FiletoList(Book_List * pList);
//--Admin 3 �������ⲿ
void ListToFile(Book_List * pList);
//--admin 4 �ܳ׸���
void ChangeAdmin(void);

//�������
void AdminManageUI_1(void);
void AdminManageUI_2(void);

//--��������ĺ���
//���ļ���ӽڵ�
void AddNodeFromFile(Book_List * pList, char * str);
//�ļ���ӽڵ㣨Log�棩
void log_AddNodeFromFile(Book_List * pList, char * str);
//������д�뵽һ���ļ���
void AddNodeToFile(Book_List * pList, char * str);
//������д�뵽һ���ļ�(Log��)
void log_AddToFromFile(Book_List * pList,char * str);

//��ȡ������
int GetListSize(Book_List * List);
//��������
void ShowAllList(Book_List List, int page, int size);
//���ӽڵ�
void AddList(Book_List *pList);
//����������
void ShowByTitle(Book_List List, char * str);
//���������
void ShowByDomain(Book_List List, char * str);
//�����߼���
void ShowByAuthor(Book_List List,char * str);
//ɾ���ڵ�
void DelList(Book_List * pList);
//�ָ��ڵ�
void RecoveryDel(Book_List *pList);
//�������
void FreeList(Book_List *pList);
//�����Ϣ
void ClearAll(Book_List *pList);

void Help(void);

#endif // STRUCT_H_INCLUDED
