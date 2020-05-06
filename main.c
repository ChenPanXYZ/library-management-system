#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "admin.h"
#include "student.h"
#include "statu.h"

int main()
{
    system("title 图书管理系统");     //设置cmd窗口标题
    system("mode con cols=111 lines=50");//窗口宽度高度

    Status_List StatusList = NULL;
    Book_List BookList = NULL;
    Student_List StudentList = NULL;
    Student_Node LogginStudent;       //获取登陆学生信息
    char ch;
    int choices;
    int is_loggin = 0;               //判断是否登陆

    AddNodeFromFile(&BookList, "bookinfo.book");
    Student_FileToList(&StudentList);

    Welcome();
    while (1)
    {
        StatusList = NULL;
        CopyBookInfo(&BookList, &StatusList);
        LoadStatus(&StatusList);

        system("color 0F");
        Welcome_Student(is_loggin, LogginStudent);
        PrinMenu();
        scanf("%d", &choices);

        switch (choices) {
        case 1:
            getchar();
            Register(&StudentList);
            c_scr();
            break;
        case 2:
            is_loggin = Loggin(&StudentList, is_loggin, &LogginStudent);
            if (CheckStudent(&StatusList, &LogginStudent) == 0)
            {
                printf("\n!!!!由于您借书超过60天仍未归还，您将不能再继续借书。\n"
                       "!!!!到图书管理员处缴清所欠金额后账户才能正常使用。\n");
                Update_StudentList(&StudentList, &LogginStudent);
                getch();
            }
            c_scr();
            break;
        case 3:
            StatusUI(&StatusList, &LogginStudent, is_loggin);
            c_scr();
            break;
        case 4:
            ReferUI(&StatusList, &LogginStudent, is_loggin);
            c_scr();
            break;
        case 6:
            c_scr();
            if (AdminLoggin())
                AdminManage(&BookList);
            else
            {
                c_scr();
                puts("[fail loggin:Press any key to continue...]");
            }
            break;
        case 5:
            is_loggin = QuitorChange_Student(&StudentList, &LogginStudent, is_loggin);
            c_scr();
            break;
        case 7:
            c_scr();
            if (AdminLoggin())
                RecStudnt(&StudentList);
            else
            {
                c_scr();
                puts("[fail loggin:Press any key to continue...]");
            }
            break;
        case 8:
            c_scr();
            if (AdminLoggin())
                FindPasswd(&StudentList);
            else
            {
                c_scr();
                puts("[fail loggin:Press any key to continue...]");
            }
            break;
        case 9:
            Help();
            break;
        case 0:
            puts("Bye.\n");
            AddNodeToFile(&BookList, "bookinfo.book");
            FreeList(&BookList);
            Student_FileToList(&StudentList);
            getch();
            return 0;
        default:
            prin_erro(ERRO_NUM);
        }

        Update_StudentList(&StudentList, &LogginStudent);
        Student_ListToFile(&StudentList);
         while ((ch = getchar()) != '\n')
        {
            prin_erro(NO_CHAR);
            continue;
        }
        if(ch == '\n')
            continue;
    }
}
