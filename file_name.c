#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  

typedef struct node
{   
	char name[20]; /* 姓名 */  
	char idnumber[40]; /* 身份证号*/  
	char zhanghao[40]; /* 账号*/  
	long keyword; /* 密码 */  
	struct node *next;//指针指向下一个 
}add_list;  
struct person
{ /* 定义一个结构备用 */  
	char name[20];  
	char idnumber [50];  
	char zhanghao[50];  
	long keyword;  
};  
FILE *fp;  
add_list *tail;
add_list*head; /* 定义链表尾节点指针和头指针 */  
/* 从文件中读出数据生成链表,如果文件不存在,生成空链表 */  
add_list *load(char filename[])  
{ 
	add_list *new1,*head;  
	struct person t;  
	head=(add_list *)malloc(sizeof(add_list));  
	tail=head=NULL;  
	if((fp=fopen(filename,"rb"))==NULL)  
	return head;  
	else  
	if(!feof(fp))  
	if(fread(&t,sizeof(struct person),1,fp)==1)  
	{ 
		new1=(add_list *)malloc(sizeof(add_list)); /* 连入链表第一个节点 */  
 		 strcpy(new1->name,t.name);  
 		 strcpy(new1->idnumber,t.idnumber);  
 		 strcpy(new1->zhanghao,t.zhanghao);  
 	 	new1->keyword=t.keyword;  
 	 	head=tail=new1;  
	  	new1->next=NULL;  
		while(!feof(fp)) /* 连入链表其余节点 */  
		{ 
			if(fread(&t,sizeof(struct person),1,fp)==1)  
			{ 
				new1=(add_list *)malloc(sizeof(add_list));  
				strcpy(new1->name,t.name);  
				strcpy(new1->idnumber,t.idnumber);  
				strcpy(new1->zhanghao,t.zhanghao);  
				new1->keyword=t.keyword;  
				tail->next=new1;  
				new1->next=NULL;  
				tail=new1;  
			}  
		}  
	}  
fclose(fp);  
return head;  
}  
/* 自定义函数,进度条 */  
 
/*void jindutiao(void)  
{ int i;  
for(i=0;i<78;i++) putchar('.');  
printf("\r\a");  
for(i=0;i<78;i++)  
{  
if(i==0) putchar('|');  
Sleep(100);  
printf("\b|>");  
}  
}  */
/* 插入一条记录 */  
void insert(add_list **head)  //不懂 
{ 
	add_list * new1;  
	new1=(add_list *)malloc(sizeof(add_list));
	
	printf("\n请输入姓名:"); getchar();gets(new1->name);  
	printf("\n请输入身份证号:"); scanf("%s",new1->idnumber);  
	printf("\n请输入账号:"); scanf("%s",new1->zhanghao);  
	printf("\n请输入密码:"); scanf("%ld",&new1->keyword);  
	if(*head==NULL) /* 表头为空时 */  
	{ 
		*head=new1;  
		new1->next=NULL;  
		tail=new1;  
	}  
	else /* 插入到表尾 */  
	{ 
		tail->next=new1;  
		new1->next=NULL;  
		tail=new1;  
	}  
printf("输入完成,按回车键返回......");  
getchar();  
getchar();  
}  
/* 将链表中的内容保存到指定文件中 */  
void save(add_list *head,char filename[])  
{ 
add_list *p;  
struct person t;  
if((fp=fopen(filename,"wb"))==NULL)  
	{ 
		printf("错误:不能打开文件%s\n",filename);  
		exit(1);  
	}  
else  
	{ 
		p=head;  
		while(p!=NULL)  
		{ 
			strcpy(t.name,p->name);  
			strcpy(t.idnumber,p->idnumber);  
			strcpy(t.zhanghao,p->zhanghao);  
			t.keyword=p->keyword;  
			fwrite(&t,sizeof(struct person),1,fp);  
			p=p->next;  
		}  
	}  
	fclose(fp);  
	printf("保存成功,按回车键返回......");  
	getchar();
	getchar();  
}  
/* 显示内容 */  
void display(add_list *head)  
{ 
	add_list *p;  
	p=head;  
	if(p!=NULL)  
		printf("姓名:\t\t身份证号:\t\t密码:\t\t账号:\n");  
	while(p!=NULL)  
	{  
		printf("%s\t\t%s\t\t%ld\t\t%s\n",p->name,p->idnumber,p->keyword,p->zhanghao);  
		p=p->next;  
	}  
	printf("按回车键返回......");  
	getchar();
	getchar();  
}  
void shunxu (add_list *head)
{
	add_list *first;
	add_list *tail;
	add_list *p_min;
	add_list *min;
	add_list *p;
	first=NULL;
	while(head!=NULL)
	{
		for(p=head,min=head;p->next!=NULL;p=p->next)
		{
			if(strcmp(p->next->name,min->name)<0)
			{
				min=p->next;
				p_min=p;
			}
		}
	if(first==NULL)
	{
		first=min;
		tail=min;
	}
	else
	{
		tail->next=min;
		tail=min;
	}
	if(min==head)
	{
		head = head->next;
	}
	else 
	{
		 p_min->next = min->next;
	}	
	}
	if (first != NULL)
	{
		tail->next = NULL;
	}
	head = first;
	display(head);
	
}
/* 按姓名查询记录 */  
int search(add_list *head)  
{ 
	add_list *p;  
	char name[20];  
	int flag=0;  
	printf("请输入要查找的人的姓名:");  
	getchar();  
	gets(name);  
	p=head;  
	while(p!=NULL)  
	{ 
		if(strcmp(name,p->name)==0)  
		{ 
			printf("姓名:\t\t身份证号:\t\t密码:\t\t账号:\n");  
			printf("%s\t\t%s\t\t%ld\t\t%s\n",p->name,p->idnumber,p->keyword,p->zhanghao);  
			flag=1;  
		}  
		p=p->next;  
	}  
	return flag;  
}  
/* 按姓名删除*/  
int delete1(add_list **head)  
{ 
	add_list *p,*q,*t;  
	char name[20],c;  
	int flag=0;  
	printf("请输入要删除人的姓名:");  
	scanf("%s",name);  
	q=p=*head;  
	while(p!=NULL)  
	{ 
		if(strcmp(name,p->name)==0) /* 找到要删除的人 */  
		{ 
			printf("姓名:\t\t身份证号:\t\t密码:\t\t账号:\n");  
			printf("%s\t\t%s\t\t%ld\t\t%s\n",p->name,p->idnumber,p->keyword,p->zhanghao);  
			printf("真的要删除吗?(Y:是,N:否)\n"); /* 征求意见(删&不删) */  
			getchar();
			c=getchar();  
			if(c=='y'||c=='Y') /* 删除 */  
			{ 
				if(p==*head)  
					*head=p->next;  
				else  
					q->next=p->next;  
					t=p;  
					p=p->next;  
					free(t);  
					flag=1;  
			}  
			else /* 不删,跳过 */  
			{ 
				q=p;  
				p=p->next;  
				flag=1;  
			}  
		}  
		else /* 没找到,继续 */  
		{
 			q=p;  
			p=p->next;  
		}  
	}  
	return flag;  
	printf("按回车键返回......");  
	getchar();  
}  
/* 显示菜单并选择菜单项 */  
int menu_select()  
{ 
	char c;  
	printf("\t\t********************身份证数据********************\n");  
	printf("\t\t\t\t 1:输入新的数据记录\n");  
	printf("\t\t\t\t 2:删除记录\n");  
	printf("\t\t\t\t 3:查找\n");  
	printf("\t\t\t\t 4:保存文件\n");  
	printf("\t\t\t\t 5:浏览所有数据\n");  
	printf("\t\t\t\t 6:按顺序显示数据\n");
	printf("\t\t\t\t 7:退出\n");  
	do
	{  
		printf("请输入你的选择(1~~6):");  
		c=getchar();  
	}
	while(c<'1'||c>'7');  
return c;  
}  
/* 主函数 */  
int main(void)  
{
	char filename[20];  
	char c;  
	int t;  
	printf("\n\n\n\n\n\n\t\t\t\t数据库启动中...\n\n\n\n\n\n\n\n\n\n\n\n\n");  
//jindutiao();  

	printf("请输入浏览数据文件名称:\n");  
	scanf("%s",filename);  
	getchar();  
	head=load(filename);  
	while(1)  
	{ 
		c=menu_select();  
		switch(c)  
		{ 
			case '1': insert(&head);
		 	break;  
			case '2': t=delete1(&head);
						if(!t) printf("记错了吧,没这人!\n按回车键返回......");
					 	getchar();
					 	getchar();
			break;  
			case '3':t=search(head);  
					if(!t) printf("天啊!居然没找到!\n按回车键返回......");
					getchar(); 
			break;  
			case '4':save(head,filename); 
			break;  
			case '5':display(head); 
			break;
			case '6':shunxu(head); 
			break;   
			case '7':exit(0);  
		}  
	}  
}
