#include <stdio.h>
//输入数字大于五个自动跳出scan函数 ，看不出哪里问题，排序打印也有问题。很奇怪
int n;
int a[];

void quick_sort(int *a,int n)
{
	int i,j,p,tmp;
	if(n<2)
	return;
	p=a[n/2];
	
	for(i=0,j=n-1;;i++,j--)
	{
		while(a[i]<p)
		i++;
		while(a[j]>p)
		j++;
		if(i>=j)
		break;
		tmp=a[i];
		a[i]=a[j];
		a[j]=tmp;
	
	}
	quick_sort(a,i);
	quick_sort(a+i,n-i); 

}
int scan  ()
{
	int i;
    printf("请输入比较数字个数：\n");
    scanf("%d",&n);
    printf("%d",n);
    if(n<2)
        {
            printf("error\n");
            return 0;
        };

    for(i = 1;i <= n ;i++)
    {  
		printf("请输入第%d个数:",i);
    	scanf("%d",&a[i-1]);
    }
   
     return 0;
}
int main (void)
{
    scan();
	int i;
	printf("原来数字顺序是："); 
	for(i=0;i<n;i++)
	printf("%d%s",a[i],i==n-1?"\n":"");
	quick_sort(a,n);
	printf("修改之后顺序为："); 
	for(i=0;i<n;i++)
	printf("%d%s",a[i],i==n-1?"\n":"");
	return 0; 
	
}
