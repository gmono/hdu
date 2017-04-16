#include <stdio.h>
#include <string.h>
int main()
{
    start:
    char *buf1=new char[1024];
    char *buf2=new char[1024];
    char *result=new char[2048];
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%s %s",buf1,buf2);
        int len1=strlen(buf1);
        int len2=strlen(buf2);
        int min=len1>len2? len2:len1;
        len1--;len2--;
        memset(result,0,2048);
        int j=0;
        int cf=0;
        for(int i=min-1;i>=0;--i,++j)
        {
            char c=buf1[len1--]-'0';
            char c2=buf2[len2--]-'0';
            char t=c+c2+cf;
            cf=(int)t>9;
            if(t>9) t-=10;
            result[j]=t+'0';
        }
        if(len1>=0)
        {
            for(int i=len1;i>=0;--i)
            {
                char &t=result[j++];
                t+=buf1[i]-'0'+cf;
                cf=(int)t>9;
                if(t>9) t-=10;
                t+='0';
            }
        }
        else if(len2>=0)
        {
            for(int i=len2;i>=0;--i)
            {
                char &t=result[j++];
                t+=buf2[i]-'0'+cf;
                cf=(int)t>9;
                if(t>9) t-=10;
                t+='0';
            }
        }
        if(cf!=0) result[j++]=cf+'0';
        printf("Case %d:\n",i+1);
        printf("%s + %s = ",buf1,buf2);
        for(int i=j-1;i>=0;--i)
        {
            putchar(result[i]);
        }
        if(i<n-1) printf("\n");
        printf("\n");
    }
    goto start;
}