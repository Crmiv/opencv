#include<stdio.h>
#define MAX_N 1000000
int x[MAX_N];
int min(x,y)
{
	if(x>=y)
	{
		  return y;
	}
	else
	{
		  return x;
	}
}

int max(x,y)
{
	 if(x>=y) 
	 {return x;}
	  else
	  {return y;}
}

int main()
{
	int i,l,n;
	long case;
	scanf("%ld",&case);
	for(i=case;i>0;i--)
	{
		scanf("%d %d",&l,&n);

		for(i=0;i<n;i++)
		{
			 scanf("%d",&x[i]);
		}
		int minT=0 ;
		for(i=0;i<n;i++)
		{
			 minT = min(minT,min(x[i],l-x[i]));
		}

		int maxT=0;
		for(i=0;i<n;i++)
		{
			 maxT = max(maxT,max(x[i],l-x[i]));
		}

		printf("%d %d\n",minT,maxT);
	}
	return 0;
}
if(x<l-x){min1=x;max1=1-x;}
else{min1=1-x;max1=x;}
minT>?=min1;
maxT>?=max1;
