#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h>

#define DB_NAME "zb.db"
#define TRUE        1
#define FALSE       0


sqlite3 *pdb = NULL;
char *Errmsg = NULL;

//创建数据库 zb.db
int open_db()
{
    int rc;
    rc = sqlite3_open(DB_NAME , &pdb);
    if( rc != SQLITE_OK)
    {
        printf("can't open database:%s\n",sqlite3_errmsg(pdb));
        sqlite3_close(pdb) ;
        exit(1);
    }
    return 0;
}


int creat_table()
{
    int rc;
    char *strsql = "create table if not exists idnumber (name text , idnum text, accnum text , password text)";
    //if not exists如果表student不存在则创建它，当我们第二次运行时执行这个语句（如果表存在，不再创建表）。


    rc = sqlite3_exec(pdb , strsql , 0 , 0 ,&Errmsg);
    if(rc != 0)
    {
        fprintf(stderr , "can't open database: %s\n",sqlite3_errmsg(pdb));
        sqlite3_close(pdb);
        exit(1);
    }
    return 0;
}

/*数据插入*/
int insert_data()
{
    int flag = TRUE;
    char buff[1024];
    char *strsql;
    int rc = 0 ;
    char temp[4][20];
    strsql = buff;


    if(open_db != 0)//创建数据库 创建表
    {
        open_db();
    }//open_db();
    creat_table();


    strcpy(strsql, "insert into idnumber");
    strcat(strsql , " values(?, ? , ? , ?);");

    sqlite3_stmt  *stmt = NULL;
    rc = sqlite3_prepare_v2(pdb , strsql , strlen(strsql) , &stmt , NULL);
    if(rc != SQLITE_OK)
    {
        if(stmt)
        {
            sqlite3_finalize(stmt);
        }
        sqlite3_close(pdb);
        return -1;
    }

    while(flag)
    {
            memset(temp,0,sizeof(temp));
            printf("name：");
            scanf("%s", temp[0]);
            printf("idnum：");
            scanf("%s", temp[1]);
            printf("accnum:");
            scanf("%s", temp[2]);
            printf("password:");
            scanf("%s", temp[3]);

            sqlite3_bind_text( stmt , 1 , temp[0] , strlen(temp[0]), NULL);
            sqlite3_bind_text( stmt , 2 , temp[1] , strlen(temp[1]), NULL);
            sqlite3_bind_text( stmt , 3 , temp[2] , strlen(temp[2]), NULL);
            sqlite3_bind_text( stmt , 4 , temp[3] , strlen(temp[3]), NULL);

            if(sqlite3_step(stmt) != SQLITE_DONE)
            {

                sqlite3_finalize(stmt);
                sqlite3_close(pdb);
                printf(" faile \n" );
                return 0;
            }
        sqlite3_reset(stmt);
        printf("Do you want to do insert ?(0 ruturn menu, 1 insert):");
        scanf("%d", &flag);
    }
    sqlite3_finalize(stmt);
    printf("insert success!\n");
    sqlite3_close(pdb);
    return flag;
}
int revise ()
{
     if(open_db != 0)//创建数据库 创建表
    {
        open_db();
    }//open_db();
    
    
     while(flag)
    {

        char name[20];
        printf("请选择修改名称:");
        gets(name);
        string strsql="update user set name='"+ k +"' where name='admin'";'";
        strcat(strsql,name);
        strcat(strsql,"'")

        sqlite3_exec(pdb,strsql,0,0,&ErrMsg);


        sqlite3_reset(stmt);
        printf("Do you want still to  delete ?(0 ruturn menu, 1 delete):");
        scanf("%d", &flag);
    }
    sqlite3_finalize(stmt);
    printf("delete success!\n");
    sqlite3_close(pdb);
    return flag;

}
/*删除选定数据*/
int delete1()
{
    int flag = TRUE;
    char buff[1024];
    char *strsql;
    int rc = 0 ;
    strsql = buff;
    char *ErrMsg = 0;
    char temp[20];


    if(open_db != 0)//创建数据库 创建表
    {
        open_db();
    }//open_db();

    sqlite3_stmt  *stmt = NULL;
    rc = sqlite3_prepare_v2(pdb , strsql , strlen(strsql) , &stmt , NULL);



    while(flag)
    {

        char name[20];
        printf("请选择删除名称:");
        gets(name);
        char strsql[100]= "delete from idnumber where name='";
        strcat(strsql,name);
        strcat(strsql,"'")

        sqlite3_exec(pdb,strsql,0,0,&ErrMsg);


        sqlite3_reset(stmt);
        printf("Do you want still to  delete ?(0 ruturn menu, 1 delete):");
        scanf("%d", &flag);
    }
    sqlite3_finalize(stmt);
    printf("delete success!\n");
    sqlite3_close(pdb);
    return flag;

}

/*浏览所有数据*/
int search_data()
{
    int rc;
    if(open_db != 0)
    {
        open_db();
    }
    char *strsql = "select * from idnumber" ;

    sqlite3_stmt  *stmt = NULL;


    rc = sqlite3_prepare_v2(pdb , strsql , strlen(strsql) , &stmt , NULL);
    if(rc != SQLITE_OK)
    {
        if(stmt)
        {
            sqlite3_finalize(stmt);
        }
        sqlite3_close(pdb);
        return -1;
    }

    int nColumn = sqlite3_column_count(stmt); //ncolumn 表的列数
    int vtype , i;
    do{
        rc = sqlite3_step(stmt);
        if(rc == SQLITE_ROW)
        {

            for(i = 0 ; i < nColumn ; i++ ) //打印一行的信息
            {

                vtype = sqlite3_column_type(stmt , i); //sqlite3_column_type()函数返回第列的值的数据类型
                if(vtype == SQLITE_INTEGER)
                {
                    printf("%s:%d\n" , sqlite3_column_name(stmt , i) , sqlite3_column_int(stmt , i));
                }
                else if(vtype == SQLITE_TEXT)
                {
                    printf("%s:%s\n" , sqlite3_column_name(stmt , i) , sqlite3_column_text(stmt , i));
                }
                else if(vtype == SQLITE_NULL)
                {
                    printf("no values\n");
                }
            }
            printf("---------------\n");

       }else if(rc == SQLITE_DONE)
       {
           //printf("Select finish\n");
            printf("查看成功\n");
            break;
       }else
       {
            printf("Select faile\n");
            sqlite3_finalize(stmt);
            break;
       }

    }while(1);
    sqlite3_finalize(stmt);
    sqlite3_close(pdb);
    return 0;
}

int main(int argc , char **argv)
{
    int n,flag=1;
    while (flag)
    {
    printf("\t\t********************身份证数据********************\n");
    printf("\t\t\t\t1.添加 \n\t\t\t\t2.修改 \n\t\t\t\t3.删除 \n\t\t\t\t4.浏览所有数据\n\t\t\t\t5.退出程序\n");
    printf("请输入[1 - 5]:");
    scanf("%d" , &n);
    getchar();
    switch(n)
    {
        case 1:

            insert_data();
        //  printf("添加成功\n");
            break;
        case 2:
            printf 
            revise();
            break;
        case 3:
            delete1();
            break;
        case 4:
            search_data();
            break;
        case 5:
            flag=0;

        default :
            printf("再见^.^");
    }
    }
    return 0;
}
