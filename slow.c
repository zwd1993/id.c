#include <stdio.h>
//第一步找出找出一个位置使其左侧都小于其值，右侧都大于其值//
//*********************************************************
//第二步对每个值都这么操作，没搞懂怎么做
int i,n,j,k,l;
int a[],b[];
int scan  ()
{
    printf("请输入比较数字个数：\n");
    scanf("%d",&n);
    if(n<2)
        {
            printf("error\n");
        };

    for(i = 1;i <= n ;i++)
    {  
		printf("请输入第%d个数:",i);
    	scanf("%d",&a[i-1]);
    }
   
     return 0;
}
int main()
{	
	scan();
    //	printf("%d",n); 
	//{4 , 5 , 3 , 1 , 2 } >
	//{2 , 5 , 3 , 1 , 4 } 
	//{2, 1 , 3 , 5 ,4 }
	
	printf("%d\n",a[n/2]);
	for(i = 0,j = n-1;;i++,j--)
		{
			while(a[i]<a[n/2])
			i++;
			while(a[j]>a[n/2])
			j--;
			if(i>=j)
			break;
			k = a[i];
			a[i] = a[j];
			a[j] = k;
		};
	 for(i = 0;i < n ;i++)
	printf("-%d-",a[i]); 

}

