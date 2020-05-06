/************************************************
*               ѧ��ע��/��½ģ��
*             Written by ��1704 ̷����
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

/*******����********/
void Register(Student_List * pList)     //ע�����
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    //��ʾ��
    SetConsoleTextAttribute(Color, 0x3F );
    printf("\n\n\n\n                                                  ���û�ע��                                                   \n");
    SetConsoleTextAttribute(Color, 0xf );
    printf("\n\n\n");
    AddStudent(pList);       //ע��ѧ����Ϣ
}

int Loggin(Student_List * pList, int loggin, Student_Node * student)        //��½����
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    char tmp_s_number[9];
    char tmp_password[PASSWD_SIZE];
    int status = 0;

    //��ʾ��
    SetConsoleTextAttribute(Color, 0x3F );
    printf("\n\n\n\n                                                  ��¼                                                         \n\n\n");
    SetConsoleTextAttribute(Color, 0xf );
    if (loggin)
    {
        printf("\t\t\t\t\t���Ѿ���¼��");
        getch();
        return 1;
    }
    printf("\t\t\t\t\t[ѧ��] ");
    scanf("%8s", tmp_s_number);
    printf("\t\t\t\t\t[����]");
    SetConsoleTextAttribute(Color, 0x0 );
    scanf("%16s", tmp_password);
    SetConsoleTextAttribute(Color, 0xF );

    status = status + Is_Register(pList, tmp_s_number);
    status = status + Is_Register(pList, tmp_password);
    if(status == 3)
    {
        SetConsoleTextAttribute(Color, 0x3 );
        printf("\t\t\t��¼�ɹ���");
        SetConsoleTextAttribute(Color, 0xf );
        SaveStudent(pList, student, tmp_s_number, tmp_password);
        getch();
        return 1;
    }
    else
    {
        SetConsoleTextAttribute(Color, 0xC );
        printf("\t\t\t��¼ʧ�ܡ�");
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

    printf("\t\t\t����дע����Ϣ����������ʱ����q���뿪ע�ᡣ\n\n\n");

    printf("\t\t\t       ���20���ַ� ���� : ");
    get_str(tmp_name, NAME_SIZE);                  //����admin.h��������ַ�������

    printf("\t\t\t              8λ�� ѧ�� : ");
    scanf("%8s", tmp_s_number);
    size = strlen(tmp_s_number);
    for (i = 0; i < size; i++)
        if (size <8 || !isdigit(tmp_s_number[i]))            //��������//�����ѧ�Ų���������
        {
            SetConsoleTextAttribute(Color, 0xC );
            printf("\t\t\t[*]�������ѧ�Ų���������,��ֹע�ᡣ\n");
            SetConsoleTextAttribute(Color, 0xF );
            getch();
            return;
        }
    if (Is_Register(pList, tmp_s_number) == 1)
    {
        SetConsoleTextAttribute(Color, 0xC );
        printf("\t\t\t[*]�������ѧ���ѱ�ע�ᡣ\n");
        SetConsoleTextAttribute(Color, 0xF );
        getch();
        return;
    }

    getchar();
    printf("\t\t\t       ��(b),Ů(g) �Ա� : ");
    tmp_sex = getchar();
    //putchar(tmp_sex);
    /**if ((tmp_sex != 'b') || (tmp_sex != 'g'))
    {
        SetConsoleTextAttribute(Color, 0xC );
        printf("\t\t\t[*]��������Ա𲻷�������,��ֹע�ᡣ\n");
        SetConsoleTextAttribute(Color, 0xF );
        getch();
        return;
    }**/

    printf("\t\t\t          ���16Ϊ ���� : \n");
    SetConsoleTextAttribute(Color, 0x0 );                   //�������������ɺ�ɫ
    scanf("%s", tmp_password);

    new = (Student_Node * )malloc (sizeof(Student_Node));   //����������������ӵ�����
    strcpy(new->name, tmp_name);
    strcpy(new->s_number, tmp_s_number);
    strcpy(new->password, tmp_password);
    new->sex = tmp_sex;
    new->status = 1;                                    //Ĭ���˺�δ����
    new->booknumber = 0;                                //Ĭ���˺Ž�����ĿΪ0;

    new->next = *pList;
    *pList = new;

    SetConsoleTextAttribute(Color, 0xA );
    printf("�����ע�ᡣ\n");
    SetConsoleTextAttribute(Color, 0xF );

    //�����������ļ�
    Student_ListToFile(pList);
    getch();
}

int Is_Register(Student_List * pList, char * ch)    //�ж��ַ����Ƿ���������,����ѧ�������1�������������ﷵ��2
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

//�����������ļ�
void Student_ListToFile(Student_List * pList)
{
    FILE * fp;
    Student_Node * walker = *pList;
    if ((fp = fopen("student.dat", "w")) == NULL)
    {
        printf("[!]�û������ļ��𻵣��޷������ݵ������ļ���\n");
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
        printf("�ر��ļ�ʱ����\n");
}

void Student_FileToList(Student_List * pList)
{
    FILE * fp;
    Student_Node * newnode;
    char end;                                           //�ж��ǿ��ļ�

    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    if ((fp = fopen("student.dat", "r")) == NULL)
    {
        SetConsoleTextAttribute(Color, 0xC );
        printf("[!]�û������ļ��𻵻򲻴��ڣ��޷������û���\n");
        SetConsoleTextAttribute(Color, 0xf );
        return;
    }
    end = fgetc(fp);
    if (end != EOF)
    {                                                   //δ�����ļ�β
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
        printf("�ر��ļ�ʱ����\n");
}

//���û��ɹ���½������Ϣ������student�ṹ����
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

//�û��ɹ���¼��״̬��
void Welcome_Student(int status, Student_Node student)
{
    if (status == 1)
    {
        HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(Color, 0xCF );
        printf("                                       ====WECOME COME TO LBRARY SYSTEM====                                    \n");
        SetConsoleTextAttribute(Color, 0xC );
        printf("                                           \t[��ã�%s����ӭ����]\t\n", student.name);
        SetConsoleTextAttribute(Color, 0xF );
    }
}

//ÿһ�ε��￪ʼ�˵�ĩβ(�û��Ѿ���ɲ���)
//��student�ṹ�����Ϣ����д��������
//�û���������Ϣ�ĸ���
void Update_StudentList(Student_List * pList, Student_Node * student)
{
    Student_Node * walker = *pList;

    while (walker != NULL)
    {
        if (strcmp(student->s_number, walker->s_number) == 0)    //�ҵ�ѧ��
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

//�û���½��
//ע�����޸���Ϣ
//��Ϣ���ڵĽڵ㱻�޸�
int QuitorChange_Student(Student_List * pList, Student_Node * pNode, int status)
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    int ch;
    char tmp_name[NAME_SIZE];
    char tmp_sex;
    char tmp_password[PASSWD_SIZE];
    Student_Node * walker = *pList;

    SetConsoleTextAttribute(Color, 0xCF );
    printf("\n\n                         ����1--------------------->�޸�/ע��<--------------------��������                     \n\n");
    SetConsoleTextAttribute(Color, 0xF );
    if (status == 0)
    {
        printf("[*]����û�е�¼��\n");
        getch();
        return 0;
    }
    else
    {
        printf("��������ѡ�� = ");
        scanf("%d", &ch);
        getch();
        if (ch == 1)
        {
            printf("\t\t\t\t\t�����������˻���Ϣ��\n");
            printf("\t\t���� = %s\t||�Ա� = %c\t||ѧ�� = %s\n\n",
                   pNode->name, pNode->sex, pNode->s_number);
            printf("����д�����������޸���Ϣ(ֱ�Ӱ��س��˳��޸�)\n");
            SetConsoleTextAttribute(Color, 0x0 );
            //get_str(tmp_password, PASSWD_SIZE);
            scanf("%s", tmp_password);
            SetConsoleTextAttribute(Color, 0xF );
            if (tmp_password[0] == '\0')
                return 1;
            if (strcmp(tmp_password, pNode->password) != 0)
            {
                printf("���벻��ȷ��");
                getch();
                return 1;
            }
            printf("\n\n\n\t\t\t       ���20���ַ� ���� : ");
            scanf("%20s", tmp_name);
            printf("\t\t\t       ��(b),Ů(g) �Ա� : ");
            getchar();
            tmp_sex = getchar();
            getchar();
            printf("�Ƿ��޸�����(���16λ)����Y/N��");
            if (getchar() == 'Y')
            {
                SetConsoleTextAttribute(Color, 0xC );
                printf("\t\t\t\t������");
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
        printf("\n�ѳ�����\n");
        getch();
        return 0;
    }
}

//�û��������˺�
//�����������statusΪ0���˺ţ�����ʾ����
//��status��Ϊ1
void RecStudnt(Student_List * sList)
{
    Student_Node * walker = *sList;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char input[TITLE_SIZE];
    int status = 0;
    SetConsoleTextAttribute(hConsole, 0xCF );
    printf("                                                ====����˺�====                                               \n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF );

    printf("δ��ʱ���鵼���˺��쳣��ͬѧ����:\n\n");

    //��ʾ�˺��쳣�б�
    while (walker != NULL)
    {
        if (walker->status == 0)
        {
            status++;
            SetConsoleTextAttribute(hConsole, 0xC );
            printf("[\tѧ�� = %s\t���� = %s\t]\n", walker->s_number, walker->name);
            SetConsoleTextAttribute(hConsole, 0xF );
        }
        walker = walker->next;
    }
    if (status == 0)
    {
        SetConsoleTextAttribute(hConsole, 0xc );
        printf("[\t    û�б��������˺š�\t]\n");
        SetConsoleTextAttribute(hConsole, 0xF );
    }
    else
    {
    //����˺�
        printf("\n\n\t����Ҫ����ѧ�ţ���ͬʱ�����ѧ���Կո����������#��������:");

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
                    printf("[\t�ɹ���� ��ѧ�� = %s\t]\n", walker->s_number);
                    SetConsoleTextAttribute(hConsole, 0xF );
                }
                walker = walker->next;
            }
            if (status == 0)
            {
                SetConsoleTextAttribute(hConsole, 0xc );
                printf("[\t    ʧ�� ���������ѧ��δ����Ż��߲�����\t]\n");
                SetConsoleTextAttribute(hConsole, 0xF );
            }
        }
    }
    getch();
    c_scr();
}

//�û���������
//�����������ѧ��
//��ʾ�û���Ϣ
void FindPasswd(const Student_List * sList)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char input[TITLE_SIZE];
    Student_Node * walker;
    int status = 0;
    SetConsoleTextAttribute(hConsole, 0x5F );
    printf("                                               ====��ѯ����====                                                \n\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF );

    while (1)
    {
        walker = *sList;
        printf("����Ҫ��ѯ��ѧ�ţ���#�˳�");
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
                printf("\t[ѧ�� = %s, ���� = %s]\n\n\n", walker->s_number, walker->password);
            }
            walker = walker->next;
        }
        if (status == 0)
            printf("\tѧ�Ų�����\n\n\n\n");
        SetConsoleTextAttribute(hConsole, 0xF );
    }
    getch();
    c_scr();
}
