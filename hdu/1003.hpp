#include <stdio.h>
#include <string.h>
#define INT_MMAX 1<<(sizeof(int)*8-1)
#define INT_MAX ~INT_MMAX
int sequence[100000]={0};
char linebuf[1000000]={0};
struct Pos
{
    int start;
    int end;
    int max;
};
//计算最大子串
Pos Cal(int start,int end)
{
    if(start==end) return Pos()={start:start,end:end,max:sequence[start]};
    int len=end-start+1;
    int mid=(len-1)/2;
    Pos lp=Cal(start,mid);
    Pos rp=Cal(mid+1,end);
    //cross
    int lstart=mid;
    int max=INT_MMAX;
    int sum=0;
    for(int i=mid;i>=0;i--)
    {
        sum+=sequence[i];
        if(sum>max)
        {
            lstart=i;
            max=sum;
        }
    }
    int rend=mid+1;
    for(int i=mid+1;i<=end;++i)
    {
        sum+=sequence[i];
        if(sum>max)
        {
            rend=i;
            max=sum;
        }
    }
    Pos ret;
    if(lp.max>rp.max) ret=lp;
    else ret=rp;
    if(ret.max>max) return ret;
    else
    {
        ret.start=lstart;
        ret.end=rend;
        ret.max=max;
        return ret;
    }
}
int main()
{
    start:
    int testn;
    scanf("%d",&testn);
    for(int i=0;i<testn;++i)
    {
        scanf("%s",linebuf);
        int temp;
        int sum=0;
        for(int j=0;sscanf(linebuf,"%d",&temp);++j)
        {
            sequence[j]=temp;
            sum++;
        }
        Pos max=Cal(0,sum-1);
        printf("Case %d:\n",i);
        printf("%d %d %d\n",max.max,max.start,max.end);
        if(i==testn-1) putchar('\n');
    }
    goto start;
    return 0;
}