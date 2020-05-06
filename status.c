/************************************************
*               ����/����/��ѯģ��
*             Written by ��1704 ����
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

/*******************���溯��********************/

//�û�����ʱ��
//����ǰʱ���뵽��ʱ������7�죬��ʾһ����ɫ�Ǻ�
void PrinWARN(Status_Node * sNode)
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    time_t today = time(NULL);
    SetConsoleTextAttribute(Color, 0xCF );
    if (difftime(sNode->return_book_t, today) <= (14 * 3600 * 24))   //�뻹��������14��
        printf("[*]");
    SetConsoleTextAttribute(Color, 0xF );
}

//��ѯ/�����UI
void ReferUI(Status_List * pSList, Student_Node * student, int status)
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(Color, 0xF0 );
    printf("\n\n                                            ����/����                                                   \n");
    SetConsoleTextAttribute(Color, 0xF );
    puts("\n\n\n");

    //�û�δ��¼
    if (status == 0)
        puts("\t\t\t\t����δ��¼������ʹ�á���ѯ/���顿���ܡ�");
    else
        WhatIBorrow(pSList, student);
}

//����ͼ���UI
void StatusUI(Status_List * pSList, Student_Node * student, int status)    //���幹��
{
    system("mode con cols=135 lines=50");//���ڿ�ȸ߶�
    char choices = '~';
    char last_choices;
    char search[TITLE_SIZE];
    int id;
    int page = 0;
    int Size;                       //���ӻ����ҳ������,page = 1,����ҳ����page = -1�� ����ҳ��

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
            printf("������Ҫ�����������ؼ���:");
            scanf("%s", search);
            Status_ShowByTitle(*pSList, search);
            break;
        case '2':
            printf("������Ҫ����������ؼ���:");
            scanf("%s", search);
            Status_ShowByDomain(*pSList, search);
            break;
        case '3':
            printf("������Ҫ���������߹ؼ���:");
            scanf("%s", search);
            Status_ShowByAuthor(*pSList, search);
            break;
        case 'b':
            if (student->status == 0)       //�˺ű���
            {
                SetConsoleTextAttribute(Color, 0xC);
                printf("����Ϊ��������δ���飬������ڲ��ܽ��顣\n"
                       "���ȵ���ͼ�����Ա�����峬������ķ��á�");
                SetConsoleTextAttribute(Color, 0xF);
                getch();
                choices = last_choices;
                continue;
                break;
            }
            if (status == 0)
            {
                SetConsoleTextAttribute(Color, 0xC);
                printf("����δ��¼��������ڲ��ܽ��顣\n");
                SetConsoleTextAttribute(Color, 0xF);
                getch();
                choices = last_choices;
                continue;
            }
            printf("������Ҫ�����ID����Ҫ��౾�飬���Կո����������0��������:");
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
            printf("\a\t\t\t\t�����������������롣");
        }

        printf("\n\n\n���ݿ��й���¼��%d��ͼ�����Ϣ��\n\n\n\n\n\n\n", Size);
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
    system("mode con cols=111 lines=50");//���ڿ�ȸ߶�
    return;
}
void StatusUI_1(void)  //UI�ϰ벿��
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 0xCF );
    printf("                                                            ====����ͼ��/����====                                                      \n");
    SetConsoleTextAttribute(hConsole, 0xF );
    printf("\n\n\n\n");
    printf("%s\t\t������ͼ��/���顿\n\n\n\n\n\n\n\n", SKIN);
}
void StatusUI_2(void)  //UI�°벿��
{
    printf("\t\t===================================================================================================\n"
           "\t\t��<����һҳ    ��1�����ؼ��ֲ���       ��2����רҵ����        ��3�������߲���           ��>����һҳ\n"
           "\t\t��~����ʾȫ����Ϣ                            ��b������                                    ��q������\n"
           "\t\t===================================================================================================\n"
           "\t\t��������ѡ�INPUT��");
}

/***********************************************/


/**************���ܺ���************************/

//�ڳ���ʼʱ��
//�����鱾�����ͼ����Ϣ��״̬������
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

//����ʼʱ��
//��ȡ����״̬��Ϣ���ļ���
//������ͼ����صĽ�����Ϣ
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
        printf("[!]ͼ����������ļ��𻵣��޷�����ͼ���ļ���\n");
        SetConsoleTextAttribute(Color, 0xF );
        return;
    }
    end = fgetc(fp);
    if (end != EOF)
    {                                                   //δ�����ļ�β
        rewind(fp);
        while (1)
        {
            walker = *pSList;                               //��ʼ��walkerָ��
            get_strFromFile(tmp_title, NAME_SIZE, fp);      //���ļ���ȡ����
            if (tmp_title[0] == '#')                        //��ȡ��ȡ��������������
                break;
            while (walker != NULL)
            {
                if (strcmp(tmp_title, walker->book.title) == 0) //������״̬��������鱾�������ȡ�ı���һ��
                {                                               //���������ļ�����û���Ϣ������������
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
                walker = walker->next;                      //���������һ���ڵ�ı���Ƚ�
            }
            //������ı������ļ���һ�£���һ��tmp���鴢���������
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
        printf("�ر��ļ�ʱ����\n");
}

//ÿһ��״̬��Ϣ�ĸ���(�軹�������
//��״̬���������ļ���
//��״̬��Ϣ����һ��
void Status_ListToFile(Status_List * pSList)
{
    FILE * fp;
    Status_Node * walker = *pSList;
    if ((fp = fopen("status.info", "w+")) == NULL)
    {
        printf("[!]ͼ������ļ��𻵣��޷������ݵ������ļ���\n");
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
        printf("�ر��ļ�ʱ����\n");
}

//ÿһ�μ�������ͼ��(������ѯ���棩
//Ϊÿһ���ڵ����·���id
//����������
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

//ÿһ�μ�������ͼ��
//����״̬����
//��ʾ����ͼ��Ľ������
void Status_ShowAllList(Status_List List, int status, int size)
{
    int i;
    static int s_page = 1;
    int page_number;
    static int beggin = 0;
//    struct tm * show_b;
    struct tm * show_t;
    Status_Node * walker = List;

    printf("\tID\tͼ������\tרҵ����\tͼ����\t����\tͼ��״̬\t������\t�Ա�\tѧ��\t\t����ʱ��\n");
    printf(" \t==========================================================================================================================\n");

    if (size == 0)
        page_number = 1;
    else
    {
        if (size % PAGE_SIZE == 0)                      //������ҳ��
            page_number = size / PAGE_SIZE;
        else
            page_number = size / PAGE_SIZE + 1;
    }
    s_page = s_page + status ;                           //����������ʾ��ҳ��
    beggin = (s_page - 1) * PAGE_SIZE;                //����ҳ����Ӧ��ƫ����
    if(s_page< 1)
    {
        printf("\t\t\t\t\t\nû����һҳ�ˡ�\n\n");
        s_page = 0;                             //��ҳ��������0ҳ
        return;
    }
    else if (s_page > (size / PAGE_SIZE) + 1)
    {
        printf("\t\t\t\t\t\nû����һҳ�ˡ�\n\n");
        s_page = page_number + 1;            //��ҳ�����������һҳ�ĺ�һҳ
        return;
    }
    if (List == NULL)
        printf("\t\t\t>>>>>>>>>>>>> δ¼���κ�ͼ����Ϣ <<<<<<<<<<<<<<<<<\n");
    else
    {
        if (s_page > 0 && s_page < page_number + 1)        //ҳ������ɷ�Χ��
            for (i = 0; i < beggin; i++)     //��walker�ƶ�beggin��λ��
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
                printf("�ѱ�����\t");
            else
                printf("δ������\t");
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
    if (s_page <= 0)                      //��page����������ʾ��ҳ��
        i =  1;
    else if(s_page >= page_number)
        i = page_number;
    else
        i = s_page;
    printf("\t\t\t\t\t\t\t\t��%dҳ/", i);
    if (size == 0)                      //��size�������е�ҳ��
        i = 1;
    else
        i = page_number;
    printf("��%dҳ\n", i);
}

//�û�����ͼ������
//����������������
//��ӡ����������Ϣ
void Status_ShowByTitle(Status_List SList, char * str)
{
    Status_Node * walker = SList;
    int log = 0;
    //struct tm * show_b;
    struct tm * show_t;

    c_scr();
    StatusUI_1();
    //printf("%s\n    %s\n", STATUS, START);
    printf("\tID\tͼ������\tרҵ����\tͼ����\t����\tͼ��״̬\t������\t�Ա�\tѧ��\t\t����ʱ��\n");
    printf(" \t==========================================================================================================================\n");
    if (SList == NULL)
        printf("\t\t\t\t\tͼ���¼Ϊ��\n");
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
                printf("�ѱ�����\t");
            else
                printf("δ������\t");
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
            printf("\t\t\t\t\tδ�ҵ�����ؼ��ʡ�%s������ؼ�¼��\n", str);
    }
    printf(" \t==========================================================================================================================\n");
}

//�û�����ͼ������
//�������а��������
//��ӡ����������Ϣ
void Status_ShowByDomain(Status_List sList, char * str)
{
    Status_Node * walker = sList;
    int log = 0;
    struct tm * show_b;
    struct tm * show_r;
    c_scr();
    StatusUI_1();
    //printf("%s\n    %s\n", STATUS, START);
    printf("\tID\tͼ������\tרҵ����\tͼ����\t����\tͼ��״̬\t������\t�Ա�\tѧ��\t\t����ʱ��\n");
    printf(" \t==========================================================================================================================\n");
    if (sList == NULL)
        printf("\t\t\t\t\tͼ���¼Ϊ��\n");
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
                printf("�ѱ�����\t");
            else
                printf("δ������\t");
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
            printf("\t\t\t\t\tδ�ҵ�����ؼ��ʡ�%s������ؼ�¼��\n", str);
    }
    printf(" \t==========================================================================================================================\n");
}

//�û�����ͼ������
//�������м���
//��ӡ����������Ϣ
void Status_ShowByAuthor(Status_List List,char * str)
{
    Status_Node * walker = List;
    int log = 0;
    struct tm * show_r;

    c_scr();
    StatusUI_1();

    printf("\tID\tͼ������\tרҵ����\tͼ����\t����\tͼ��״̬\t������\t�Ա�\tѧ��\t\t����ʱ��\n");
    printf(" \t==========================================================================================================================\n");
    if (List == NULL)
        printf("\t\t\t\t\tͼ���¼Ϊ��\n");
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
                printf("�ѱ�����\t");
            else
                printf("δ������\t");
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
            printf("\t\t\t\t\tδ�ҵ����߹ؼ��ʡ�%s������ؼ�¼��\n", str);
    }
    printf(" \t==========================================================================================================================\n");
}

//����������û�����ͼ��ID
//��ͼ��״̬�����ͼ��״̬��Ϊ1,�û����Խ������Ŀ+1�򲻱�
//��ʾ���(ʧ��/�ɹ�)
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
                printf("\t\t[����ʧ�� : �Ȿ���Ѿ�������]\n");
                SetConsoleTextAttribute(Color, 0xF );
                getch();
                return;
            }
            printf("%s", student->name);
            if (student->booknumber > 10)
            {
                SetConsoleTextAttribute(Color, 0xC );
                printf("\t\t[����ʧ�� : �����ֻ�ܽ�ʮ����]\n");
                SetConsoleTextAttribute(Color, 0xF );
                getch();
                return;
            }
            SetConsoleTextAttribute(Color, 0xF0 );
            printf("\t\t[����ɹ� : ���� = %s, ID = %d]\n", walker->book.title, walker->book.id);
            SetConsoleTextAttribute(Color, 0xF );
            strcpy(walker->student.name, student->name);
            strcpy(walker->student.s_number, student->s_number);
            walker->student.sex = student->sex;
            walker->status = 1;
            student->booknumber++;

            walker->brrow_book_t = get_t;          //��ý���ʱ��
//            walker->borrow_book = localtime(&(walker->brrow_book_t));

            get_t = get_t + (3600 * 24 * 60);
            walker->return_book_t = get_t;
        }
        walker = walker->next;
    }
    Status_ListToFile(pSList);
}

//�û����в�ѯ����
//��״̬�����в����û�����
//��ʾ�û�������Ϣ
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
    printf("                                                  ����/����                                                    \n");
    SetConsoleTextAttribute(Color, 0xF );
    puts("\n\n\n");
    printf("���Ѿ�����%d���顣\n\n\n\n", student->booknumber);
    printf("\t\tID\tͼ������\tרҵ����\tͼ����\t����\t����ʱ��\n");
    printf(" \t==========================================================================================\n");
    while (walker != NULL)
    {
        if (strcmp(walker->student.s_number, student->s_number) == 0)       //���������û�������
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

    printf("\n\n  ���߼��Ǻ�");
    SetConsoleTextAttribute(Color, 0xCF );
    printf("[*]");
    SetConsoleTextAttribute(Color, 0xF );
    printf("�ļ�¼˵��ͼ��Ҫ������");
    SetConsoleTextAttribute(Color, 0xC );
    printf("(�뻹�����޻���14�죩");
    SetConsoleTextAttribute(Color, 0xF );
    printf("���뾡�컹�顣\n");
    printf("  ����Ҫ�����id���л�������������౾�����Կո����������0�˳�������档\n");

    SetConsoleTextAttribute(Color, 0xA );
    printf("��������Ҫ�����ID��");
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

//����������û�����ͼ��ID
//��ͼ��״̬�����ͼ��״̬��Ϊ0���û�������Ŀ-1
//��ʾ������ɹ���
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
                printf("\t\t[����ɹ� : ���� = %s, ID = %d]\n", walker->book.title, walker->book.id);
                SetConsoleTextAttribute(Color, 0xF );
                strcpy(walker->student.name, "-\0");
                strcpy(walker->student.s_number , "-\0");
                walker->student.sex = '-';
                walker->brrow_book_t = 0;
                walker->return_book_t = 0;
                student->booknumber--;
                if (student->booknumber <= 0)
                    student->booknumber = 0;
                walker->status = 0;         //״̬=0
            }
            else
            {
                SetConsoleTextAttribute(Color, 0xFC );
                printf("\t\t[����ʧ�� : ���� = %s, ID = %d����δ�����Ȿ�顣]\n",
                       walker->book.title, walker->book.id);
                SetConsoleTextAttribute(Color, 0xF );
            }
        }
        walker = walker->next;
    }
    Status_ListToFile(pSList);
}

//��½�ɹ���
//����˻�״̬���
//���鳬��--��ţ�
int CheckStudent(Status_List * pSList, Student_Node * student)
{
    time_t today = time(NULL);
    Status_Node * walker = *pSList;

    while (walker != NULL)
    {
        if (strcmp(student->s_number, walker->student.s_number) == 0)    //�ҵ�ѧ��
            if(today - walker->return_book_t >= 0)                       //����
            {
                student->status = 0;
                return 0;
            }                                                             //���
        walker = walker->next;
    }
    return 1;
}

/***********************************************/
