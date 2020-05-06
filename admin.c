/*********************************************************
                      ����Աģ��
              Written by ��1704 ��͢��
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

/****************��������**************/
void c_scr(void)
{
    system("cls");
}

void prin_erro(char * str)
{
    c_scr();
    puts(str);
}

char get_first_char(void)       //��ȡ�����ַ��������ַ�
{
    char ch = getchar();
    while(getchar() != '\n')
            continue;
    return ch;
}

char * get_str(char * st, int n)  //�ַ���¼��
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

char * get_long_number(char * ch, int n)        //��ȡһ��ֻ�������ֵ��ַ�����
{
    int size;
    int i;

    scanf("%13s", ch);
    size = strlen(ch);
    for (i = 0; i < size; i++)
        if (size <13 || !isdigit(ch[i]))            //��������
            return NULL;
    return ch;
}

char * get_strFromFile(char * st, int n, FILE * fp)  //���ļ�st�ж�ȡһ���ַ���
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
        printf("���Ϻã�");
    else if (local->tm_hour > 12 &&local->tm_hour <= 18)
        printf("����ã�");
    else
        printf("���Ϻã�");
    printf("������: %d��%d�֡�\n",local->tm_hour, local->tm_min);
}



/**************����****************************/

void Help(void)
{
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Color, 0x3F );
    printf("\n\n                                                       ����                                                    \n\n\n\n\n");
    SetConsoleTextAttribute(Color, 0xa );
    printf("\t\t1����ͼ�����ϵͳ��������Уѧ������ʦ�ġ����衢������һ��Ŀ�����ϵͳ��\n");
    printf("\t\t2��ͬѧ����ʦ�ɸ��ݱ�ϵͳ��ָ��ʵ�ֽ軹�������\n");
    printf("\t\t3���軹��ǰ��Я���Լ���ѧ��֤����ϵͳָ�����ע�ᡣ\n");
    printf("\t\t4�����ڽ�������(60��)�����ߣ���ϵͳ��Ȩȡ��������ʸ�\n");
    printf("\t\t5����ϵͳ���ս���Ȩ�鿪���Ŷ����С�\n");
    SetConsoleTextAttribute(Color, 0xF );
    getch();
    c_scr();
}
void Welcome(void)
{

    system("color 1F");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
            "\t\t\t\t========================================\n\n"
            "\t\t\t\t   �� ӭ �� �� ͼ �� �� �� ϵ ͳ\n\n"
            "\t\t\t\t========================================\n"
            "\t\t\t\t                            ");
    //SetConsoleTextAttribute(Color, 0xF0 );
    //puts("�����������");
    //SetConsoleTextAttribute(Color, 0x1F );

    printf("\n\n\n\n\n\n"
           "\t\t\t\t  ͼ�����ϵͳ. All Rights Reserved.\n\n\n");
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
           "\t\t\t\t |��1�� ���û�ע��                      ��2�� ��¼| \n"
           "\t\t\t\t |��3�� ��������ͼ�� / ����                       | \n"
           "\t\t\t\t |��4�� ���� / ��ѯ                               | \n"
           "\t\t\t\t |��5�� �޸�/ע��                                 | \n"
           "\t\t\t\t |                                                | \n"
           "\t\t\t\t |                           ����Ա����           | \n"
           "\t\t\t\t |                 -----------------------------  | \n"
           "\t\t\t\t |                 ��6������ͼ��/�޸Ĺ���Ա����   | \n"
           "\t\t\t\t |                 ��7������˺�  ��8����ѯ����   | \n"
           "\t\t\t\t |                 -----------------------------  | \n"
           "\t\t\t\t |                                                | \n"
           "\t\t\t\t |                            ��0���˳�  ��9������| \n"
           "\t\t\t\t |________________________________________________| \n"
           "\t\t\t\t                                                    \n");
    SetConsoleTextAttribute(Color, 0x0F );
    printf("\n\n\n\n");
    printf("\t\t");
    gettime();
    printf("\t\t���ڣ�����������ѡ�");
}

void PrinAdmin(void)        //��ӡadmin��ͼ��
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

void AdminMenu(void)        //admin�˵�
{
    puts(LINE);
    printf("%s��HI ADMIN��\n\n\n\n\n", SKIN);
    PrinAdmin();
    printf("\t\t\t\t[-----------------------------------------]\n"
           "\t\t\t\t[****************1            ����ͼ����Ϣ] \n"
           "\t\t\t\t[***********2       ���ⲿ�ļ�����ͼ����Ϣ]\n"
           "\t\t\t\t[********3        ��ͼ����Ϣ�������ⲿ�ļ�]\n"
           "\t\t\t\t[************4          �޸Ĺ���ԱID������]\n"
           "\t\t\t\t[*********************7          ע��ADMIN]\n"
           "\t\t\t\t[-----------------------------------------]\n"
           "\t\t\t\t [INPUT] ");
}

void AdminManageUI_1(void)  //admin�������
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 0xCF );
    printf("                                            ====����ͼ����Ϣ====                                               \n");
    SetConsoleTextAttribute(hConsole, 0xF );
    printf("\n\n\n\n");
    printf("%s\b\b������ͼ����Ϣ��\n\n\n\n\n\n\n\n", SKIN);
    //puts("������ȫ����ͼ���б�\n\n\n");
}

void AdminManageUI_2(void)
{
    printf("\t===================================================================================================\n"
           "\t��<����һҳ    ��1�����ؼ��ֲ���       ��2����רҵ����        ��3�������߲���           ��>����һҳ\n"
           "\t��a������ͼ����Ϣ       ��d��ɾ��ͼ����Ϣ    ��c�� *�������ͼ����Ϣ�������棩��r��������һ�ε�ɾ��\n"
           "\t��~����ʾȫ����Ϣ                                                                       ��q������\n"
           "\t===================================================================================================\n"
           "\t��������ѡ�INPUT��");
}






/***************admin loggin*******************/
int AdminLoggin(void)       //admin��½����
{
    FILE *fp;
    int i;
    int size;
    char name[NAME_SIZE], fname[NAME_SIZE];
    char passwd[PASSWD_SIZE], fpasswd[PASSWD_SIZE];

    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    if ((fp = fopen("1.adm", "a+")) == NULL)
    {
        printf("����Ա��Կ�����ļ����𻵣��޷��������Աϵͳ��\n");
        return 0;
    }
    i = fscanf(fp, "%s%s", fname, fpasswd);

    if (i != 2)
    {
        fprintf(fp, "admin admin");
        printf("��������һ��ʹ�ù���Աϵͳ������Ĭ���˻�����(admin/admin)��½��\n"
               "      �ڵ�½�������޸�Ĭ�ϵ�admin�˻���Ϣ��\n");
    }
    fclose(fp);

    fp = fopen("1.adm", "r");
    fscanf(fp, "%s%s", fname, fpasswd);
    puts(LINE);
    printf("%s��Hi��Admin��\n\n\n\n\n", SKIN);
    PrinAdmin();
    printf("\t\t\t\t[-----------------------------------------]\n");
    SetConsoleTextAttribute(color, 0xF0 );
    printf("\t\t\t\t PLEASE        LOG          IN       FIRST \n");
    SetConsoleTextAttribute(color, 0x0f );
    printf("\t\t\t\t  ��name��\t\t");
    SetConsoleTextAttribute(color, 0x3 );
    scanf("%20s", name);
    SetConsoleTextAttribute(color, 0xf );
    printf("\t\t\t\t  ��password��\t\t");
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

void AdminManage(Book_List * pList)    //Admin�������
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







/**************admin 1ʵ�� ********************/
void AddNodeFromFile(Book_List * pList, char * str)   //���ļ�д������
{
    FILE * fp;
    Book_Node * newnode;
    char end;
    //int status = 0;                                           //�ж��Ƿ���#�ű�ʶ��

    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    if ((fp = fopen(str, "r")) == NULL)
    {
        SetConsoleTextAttribute(Color, 0xC );
        printf("[!]ͼ������ļ��𻵻򲻴��ڣ��޷�����ͼ���ļ���\n");
        SetConsoleTextAttribute(Color, 0xf );
        return;
    }
    /**while ((end = fgetc(fp)) != EOF)
        if (end == '#')
            status++;**/
//    if (status == 0)

    end = fgetc(fp);
    if (end != EOF)
    {                                                   //���ǿ��ļ�
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
        printf("�ر��ļ�ʱ����\n");
}

void log_AddNodeFromFile(Book_List * pList, char * str)   //���ļ�д�������Դ�log
{
    FILE * fp;
    Book_Node * newnode;
    char end;                                           //�ж��ǿ��ļ�

    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    if ((fp = fopen(str, "r+")) == NULL)
    {
        SetConsoleTextAttribute(Color, 0xC );
        printf("[!]ͼ������ļ��𻵣��޷�����ͼ���ļ���\n");
        SetConsoleTextAttribute(Color, 0xF );
        return;
    }
    end = fgetc(fp);
    if (end != EOF)
    {                                                   //δ�����ļ�β
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

            //���״̬
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
        printf("��δ������κμ�¼��\n");
        SetConsoleTextAttribute(Color, 0xF );
    }
    if (fclose(fp) != 0)
        printf("�ر��ļ�ʱ����\n");
}

void AddNodeToFile(Book_List * pList, char * str)   //������д���ļ�
{
    FILE * fp;
    Book_Node * walker = *pList;
    if ((fp = fopen(str, "w+")) == NULL)
    {
        printf("[!]ͼ������ļ��𻵣��޷������ݵ������ļ���\n");
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

//        printf("[�ѵ���: TITLE = %s�� DOMAIN = %s�� NUMBER = %d�� PRICE = %.2f"
//               "AUTHOR = %s, PUBLISH = %s]\n", walker->title, walker->domain,
//               walker->number, walker->price, walker->author, walker->publish);
    }
        fprintf(fp,"#\n");
    if (fclose(fp) != 0)
        printf("�ر��ļ�ʱ����\n");
}

void log_AddNodeToFile(Book_List * pList, char * str)   //������д���ļ�(log��)
{
    FILE * fp;
    Book_Node * walker = *pList;
    if ((fp = fopen(str, "w+")) == NULL)
    {
        printf("[!]ͼ������ļ��𻵣��޷������ݵ������ļ���\n");
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

        printf("[�ѵ���: TITLE = %s, DOMAIN = %s, NUMBER = %s, PRICE = %.2f"
               "AUTHOR = %s, PUBLISH = %s]\n",
               walker->title, walker->domain,walker->number, walker->price,
                walker->author, walker->publish);
        walker = walker->next;

    }
        fprintf(fp,"#\n");
    if (fclose(fp) != 0)
        printf("�ر��ļ�ʱ����\n");
}

int GetListSize(Book_List * List)         //����������
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

void ShowAllList(Book_List List, int status, int size)  //��������
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
        if (size % PAGE_SIZE == 0)                      //������ҳ��
            page_number = size / PAGE_SIZE;
        else
            page_number = size / PAGE_SIZE + 1;
    }
    page = page + status ;                           //����������ʾ��ҳ��
    beggin = (page - 1) * PAGE_SIZE;                //����ҳ����Ӧ��ƫ����
    if(page< 1)
    {
        printf("\t\t\t\t\t\nû����һҳ�ˡ�\n\n");
        page = 0;                             //��ҳ��������0ҳ
        return;
    }
    else if (page > (size / PAGE_SIZE) + 1)
    {
        printf("\t\t\t\t\t\nû����һҳ�ˡ�\n\n");
        page = page_number + 1;            //��ҳ�����������һҳ�ĺ�һҳ
        return;
    }
    if (List == NULL)
        printf("\t\t\t>>>>>>>>>>>>> δ¼���κ�ͼ����Ϣ <<<<<<<<<<<<<<<<<\n");
    else
    {
        if (page > 0 && page < page_number + 1)        //ҳ������ɷ�Χ��
            for (i = 0; i < beggin; i++)     //��walker�ƶ�beggin��λ��
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
    if (page <= 0)                      //��page����������ʾ��ҳ��
        i =  1;
    else if(page >= page_number)
        i = page_number;
    else
        i = page;
    printf("\t\t\t\t\t\t��%dҳ/", i);
    if (size == 0)                      //��size�������е�ҳ��
        i = 1;
    else
        i = page_number;
    printf("��%dҳ\n", i);
}

void AddList(Book_List * pList)         //���ӽڵ�
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
           "                 ��ͼ�����ơ�רҵ����ͼ���š����ۡ����ߡ��������˳��¼��ͼ����Ϣ��                        \n"
           "                 ��������֤¼����Ϣ��׼ȷ��.ͼ���ż�ISBN���13λ���ֲ���                                   \n"
           "                 ������һ��ͼ���ȫ����Ϣ��                                                                  \n"
           "                 ����ENTER��������һ��ͼ���¼�롣���һ��ֱ�Ӱ���#��������¼�롣                              \n"
           "                                                                                                               \n"
           "                                                                                                               \n"
           "                                                                                                               \n\n\n\n");
    SetConsoleTextAttribute(Color, 0xF );
    /**printf("\n\n\n"
           "\t����¼���嵥��\n"
           "ID\tͼ������\t\t\tרҵ����\tͼ����\t����\t����\t\t������\n");

    **/
    //printf("%s\n", START);

    while (1)
    {
        newnode = (Book_Node *) malloc (sizeof(Book_Node));

        printf("\t\t\t");
        printf("ͼ������=");
        get_str(tmp_title, NAME_SIZE);
        if (tmp_title[0] == '#')
            break;
        printf("\t\t\tרҵ����=");
        get_str(tmp_domain, NAME_SIZE);
        printf("\t\t\tͼ������=");
        get_str(tmp_author, NAME_SIZE);
        printf("\t\t\t������=");
        get_str(tmp_publish, NAME_SIZE);
        printf("\t\t\tͼ����=");
        if (get_long_number(tmp_number, NUMBER_SIZE) == NULL)
        {
            SetConsoleTextAttribute(Color, 0xC );
            printf("\t\t\t\t[!]¼��ͼ����ʱ��������,��������Ϊ��δ��Ҫ��¼��.������¼������.\n");
            SetConsoleTextAttribute(Color, 0xF );
             while (getchar() != '\n');
            continue;
        }
        printf("\t\t\tͼ��۸�=");
        if (!scanf("%f", &tmp_price))
        {
            SetConsoleTextAttribute(Color, 0xC );
            printf("\t\t\t\t[!]¼��ͼ��۸�ʱ��������,��������δ��Ҫ��¼��.������¼������.\n");
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
        printf("\t\t\t\t\t\t\t\t[��¼��]\n");
        SetConsoleTextAttribute(Color, 0xF );
        while (getchar() != '\n')
            ;
    }
    printf("��¼��%d����¼��\n", log);
    printf("Done!\n");
}

void ShowByTitle(Book_List List, char * str) //���ؼ��ʼ���
{
    Book_Node * walker = List;
    int log = 0;

    c_scr();
    AdminManageUI_1();
    printf("%s\n    %s\n", STATUS, START);
    if (List == NULL)
        printf("\t\t\t\t\tͼ���¼Ϊ��\n");
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
            printf("\t\t\t\t\tδ�ҵ��ؼ��ʡ�%s������ؼ�¼��\n", str);
    }
    printf("    %s\n", START);
}

void ShowByDomain(Book_List List, char * str)       //���������
{
    Book_Node * walker = List;
    int log = 0;

    c_scr();
    AdminManageUI_1();
    printf("%s\n    %s\n", STATUS, START);
    if (List == NULL)
        printf("\t\t\t\t\tͼ���¼Ϊ��\n");
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
            printf("\t\t\t\t\tδ�ҵ�����%s������ؼ�¼��\n", str);
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
        printf("\t\t\t\t\tͼ���¼Ϊ��\n");
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
            printf("\t\t\t\t\tδ�ҵ����߹ؼ��ʡ�%s������ؼ�¼��\n", str);
    }
    printf("    %s\n", START);
}

void DelList(Book_List * pList)         //ɾ���ڵ�
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
        printf("����վ�ļ����𻵻򲻴��ڣ�������ִ��ɾ�������ɻָ���\n");
        return;
    }
    while (1)
    {
        c_scr();
        puts(LINE);
        printf("\n\nɾ��ͼ����Ϣ\n\n\n\n");
        ShowAllList(*pList, page, size);
        printf("\n\n"
               "\t\t\t============================================================\n"
               "\t\t\t< ��һҳ   ������Ҫɾ��ͼ���id�����id�Կո����    ��һҳ>\n"
               "\t\t\t                    ����0�˳����ɾ��\n"
               "\t\t\t============================================================\n");
        printf("��INPUT��");
        while ((scanf("%d", &get_id) == 1) && (get_id != 0))
        {
            i = 0;
            cur = *pList;
            while(cur != NULL)                              //����ǿ�
            {
                if (cur->id == get_id)
                {
                    i++;
                    printf("[\tsuceess:del id = %d\t\t title = %s\t]\n", cur->id, cur->title);

                    fputs(cur->title, fp);               //��ɾ���Ľڵ�д���ļ�
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
                printf("\tID%dδ�ҵ�\n", get_id);
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

void RecoveryDel(Book_List *pList)              //�ָ��ڵ�
{
    FILE * fp;

    c_scr();
    puts(LINE);
    printf("\n\n\n");
    printf("\t\t\t��Ϊ���ָ���һ��ɾ�������ݡ�\n"
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
void ClearAll(Book_List *pList)                  //���������Ϣ
{
    char ch;
    FILE *fp;
    system("color 4f");
    printf("\n\n\n\n\n\n\n"
           "\t\t\t���棺�˲�����������е�ͼ����Ϣ���Ҳ��ɳ�����\n"
           "\t\t\t�Ƿ��������Y/N��\n");

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

void BookManage(Book_List * pList)      //ͼ�����˵�
{
    getchar();
    char choices = '~';
    char last_choices;
    char search[TITLE_SIZE];
    int page = 0;
    int Size;                       //���ӻ����ҳ������,page = 1,����ҳ����page = -1�� ����ҳ��

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
            printf("������Ҫ�����������ؼ���:");
            scanf("%s", search);
            ShowByTitle(*pList, search);
            break;
        case '2':
            printf("������Ҫ����������ؼ���:");
            scanf("%s", search);
            ShowByDomain(*pList, search);
            break;
        case '3':
            printf("������Ҫ���������߹ؼ���:");
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
            printf("\a\t\t\t\t�����������������롣");
        }

        printf("\n\n\n���ݿ��й���¼��%d��ͼ�����Ϣ��\n\n\n\n\n\n\n", Size);
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
    printf("                                          ====�����ⲿͼ�������ļ�====                                         \n");
    SetConsoleTextAttribute(hConsole, 0xF );

    printf("\n\n"
           "\t\t*�����Ե���֮ǰ���ݹ��Ļ��Լ�������ͼ���ļ������Ǹ��ı��ļ���\n"
           "\t\t*����Ҫ����������ͬһĿ¼�¡�\n");
    printf("\t\t*�����Լ�Ҫ����һ������ͼ����Ϣ���ļ�������ѭ���¸�ʽ��\n");
    SetConsoleTextAttribute(hConsole, 0x3 );
    printf("\t\tTip:ͼ������ͼ��۸�֮��Ķ���Ϊ��ǵĶ��š����ļ������һ����#��һ���ո������\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xA );
    printf("\t\t\t[ͼ������]\n"
           "\t\t\t[רҵ����]\n"
           "\t\t\t[ͼ����], [ͼ��۸�]\n"
           "\t\t\t[ͼ������]\n"
           "\t\t\t[������]\n"
           "\t\t\t>>>>>>>��һ��ͼ����Ϣ<<<<<<<<<\n"
           "\t\t\t#\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF );
    printf("��������Ҫ������ļ�����Ϣ:");
    scanf("%39s", file);
    printf("\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF0 );
    printf("                                          ====       STATUS    ====                                            \n\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF );
    log_AddNodeFromFile(pList, file);       //��file��������
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
    printf("                                          ====�����ⲿͼ�������ļ�====                                         \n");
    SetConsoleTextAttribute(hConsole, 0xF );

    printf("\n\n"
           "\t\t*�����Ե������е�ͼ���¼�����Ǹ��ı��ļ���\n"
           "\t\t*�����ɺ��������ͬһĿ¼�¡�\n");
    printf("\t\t*���ɵ��ļ���ѭ���¸�ʽ��\n");
    SetConsoleTextAttribute(hConsole, 0x3 );
    printf("\t\tTip:ͼ������ͼ��۸�֮��Ķ���Ϊ��ǵĶ��š����ļ������һ����#��һ���ո������\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xA );
    printf("\t\t\t[ͼ������]\n"
           "\t\t\t[רҵ����]\n"
           "\t\t\t[ͼ����], [ͼ��۸�]\n"
           "\t\t\t[ͼ������]\n"
           "\t\t\t[������]\n"
           "\t\t\t>>>>>>>��һ��ͼ����Ϣ<<<<<<<<<\n"
           "\t\t\t#\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF );
    printf("����������Ҫ�������ļ���:");
    scanf("%39s", file);
    printf("\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF0 );
    printf("                                          ====       STATUS    ====                                            \n\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF );
    log_AddNodeToFile(pList, file);       //������д���ļ�
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
    printf("\n\n                                          ====���Ĺ���Ա�ܳ�====                                               \n\n\n\n");
    SetConsoleTextAttribute(hConsole, 0xF );

    fp = fopen("1.adm", "w");
    printf("\n\n");
    printf("\t\t\t\t[�µĹ���ԱID]\t");
    SetConsoleTextAttribute(hConsole, 0xc );
    scanf("%16s", id);
    SetConsoleTextAttribute(hConsole, 0xF );
    printf("\t\t\t\t[�µĹ���Ա����]\t");
    SetConsoleTextAttribute(hConsole, 0x0 );
    scanf("%16s", passwd);
    SetConsoleTextAttribute(hConsole, 0xF );

    fprintf(fp, "%s %s", id, passwd);
    fclose(fp);
    printf("Done.\n");
    getch();
    c_scr();
}
