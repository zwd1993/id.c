gb#include<stdio.h>
#include<string.h>
#include<winsock2.h>
#include <windows.h>
/*==================================================================================================================================
已经写完大半，思路是将网上下载的天气地区编码如北京101010100存储为文本，在文本中查找到输入城市如北京通过操作指针得到北京的编码101010100；
得到后改变网络地址http：//www.weather.com.cn/cityinfo/101010100/html中城市编号获得返回后后存入另一个txt,然后通过操做指针的手段得到关键字符；
weather:晴；通过在文本中找到weather位置移动指针得到‘晴’；然后发现网页返回格式是utf8需要转换成gbk格式；在网上可以找函数达到目的；我知道整个过程很蠢
需要本地有个文件保存地区编码，还有不知道网址中地区编码是否可以赋值成变量；在写的时候有一些问题，比如有个函数strstr可以找出子串并且返回指针，我最开始不知道
自己编了个函数，早了很久发现有现成的，还有指针 数组 字符串的定义有事分不清楚，关于网络部分有些是找的完成的方案；需要反思的地方还有很多；


还有重要一点，不用试着跑，还没完成，用到了windowS  = =，第二次强调这个方法很蠢；但是经过测试基本的模块是可以运行的，组合在一起应该能完成
===================================================================================================================================
*/

void ReadPage(char* host)
{

    int t;
    char WEATHER[8];
    char weather[200];


    WSADATA data;
    //winsock版本2.2
    int err = WSAStartup(MAKEWORD(2, 2), &data);
    if (err)
        return ;

    //用域名获取对方主机名
    struct hostent *h = gethostbyname(host);
    if (h == NULL)
        {printf("1");
        return ;};

    //IPV4
    if (h->h_addrtype != AF_INET)
    {printf("2");
        return ;};
    struct in_addr ina;
    //解析IP
    memmove(&ina, h->h_addr, 4);
    LPSTR ipstr = inet_ntoa(ina);

    //Socket封装
    struct sockaddr_in si;
    si.sin_family = AF_INET;
    si.sin_port = htons(80);
    si.sin_addr.S_un.S_addr = inet_addr(ipstr);
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(sock, (SOCKADDR*)&si, sizeof(si));
    if (sock == -1 || sock == -2)
    {printf("3");
        return ;};

    //发送请求
    char request[1024] = "GET http://www.weather.com.cn/data/cityinfo/101010100.html  HTTP/1.1\r\nHost:";//data/cityinfo/101010100.html
    strcat(request, host);
    strcat(request, "\r\nConnection:Close\r\n\r\n");
    int ret = send(sock, request, strlen(request), 0);
    //获取网页内容
    FILE *f = fopen("recieved.txt", "rb");
   // int isstart = 0;
    while (ret > 0)
    {
        const int bufsize = 1024;
        char* buf = (char*)calloc(bufsize, 1);
        ret = recv(sock, buf, bufsize - 1, 0);
        fprintf(f, "%s", buf);
        free(buf);
    }

    closesocket(sock);
    WSACleanup();
    printf("读取网页内容成功，已保存在recieved.txt中");

    for(t=0;t<200;t++)
    weather[t]=fgetc(f);
    printf("%s",weather);
    WEATHER[8]=("weather");
    char *nu = strstr(weather,WEATHER);
    printf("----%p----",nu);
            int n;
            for(n=3;n<5;n++)
            printf ("%s",(nu+n));

    return ;
}
int searchs(char a[20])
{   char *nu;
    char ch[50000];
    char num[9];
    int j,i;
    int t=0;
    FILE *f;

    f=fopen("c://city.txt","rb");
    if (NULL==f)
    {
        printf("Can not open file .txt!\n");
        return 1;
    };
 for(t=0;t<50000;t++)

    ch[t]=fgetc(f);
  //  printf("%s\n",ch);
  nu = strstr(ch,a);
    printf("%p\n",nu);
    if(nu)

        for(i =10; i>=1; i--)
            num[10-i]=(*(nu-i)-48);


    else
        printf("NotFound!");
for(j=0;j<9;j++)
    printf("%d",num[j]);
    fclose(f);
return num;

}
int main ()
{
    char city[20];
    printf("请输入城市名称：");
    gets(city);
    searchs( city);
	ReadPage("www.weather.com.cn");
	return 0;

 }
