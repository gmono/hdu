#include <stdio.h>
#include <string.h>
bool  mycode(char *buf1,char *buf2,char *buf3)
{
        
        int findex=0;
        int findex2=0;
        bool isok=true;
        for(int j=0;buf3[j]!=0;++j)
        {
            char c=buf3[j];
            if(c==buf1[findex]&&c==buf2[findex2])
            {
                // if(findex<=findex2) findex++;
                // else findex2++;
                findex++;
                findex2++;
            }
            else if(c==buf1[findex]) findex++;
            else if(c==buf2[findex2]) findex2++;
            else
            {
                //debug
                printf("fail on %d %d %d\n",j,findex,findex2);
                printf("here %c %c %c\n",buf1[findex],buf2[findex2],buf3[j]);
                isok=false;
                break;
            }

        }
        return isok;
}

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<string.h>
#include<memory.h>
#include <stack>
#include <list>
#include <vector>
#include <time.h>
using namespace std;
char *a,*b,*c;
int lenc,lena,lenb;
bool h[205][205];

int searchsum = 0;//分支搜索计数器


    struct state
    {
        int pa;
        int pb;
        int pc;
        bool isused; //记录父状态是否已经处理过
    };
state tstack[100000];
//由dfs函数循环化而来
bool whiledfs(int pa,int pb,int pc)
{
	int sptr = 0;//栈底
#define push(a) tstack[++sptr]=a
#define pop() sptr--
#define top() tstack[sptr]
#define empty() sptr==0
    state root={pa,pb,pc,false};//根状态
	push(root);

    while(!empty())
    {
		
		state &nowp = top();
        if(nowp.pa>lena) {pop();continue;}
        if(nowp.pb>lenb) {pop();continue;}
		if (nowp.pc == lenc) {return true; }
        if(h[nowp.pa][nowp.pb]) {pop();continue;}
        if(!nowp.isused)
        {
            searchsum++;
            h[nowp.pa][nowp.pb]=true;
            nowp.isused=true;
            //这里校验分支有效性 如果无效则无需放入 对应cstate为false

            if(b[nowp.pb]==c[nowp.pc])
            {
                //state right={nowp.pa,nowp.pb+1,nowp.pc+1,false,&nowp,{false,false},1};
				tstack[++sptr] = { nowp.pa,nowp.pb + 1,nowp.pc + 1,false};
            }
            if(a[nowp.pa]==c[nowp.pc])
            {
                //state left= { nowp.pa + 1,nowp.pb,nowp.pc + 1,false,&nowp,{ false,false },0 };
				tstack[++sptr]={ nowp.pa + 1,nowp.pb,nowp.pc + 1,false };
            }

            
        }
        else
        {
            pop();
        }
    }
    return false;
}
bool dfs(int pa,int pb,int pc)
{

	searchsum++;//加一分支
    if(pc==lenc)return true;
    if(pa>lena)return false; //关键 为何为大于 而非大于等于
    if(pb>lenb)return false;
    if(h[pa][pb])return false;
    h[pa][pb]=true;
    if(a[pa]==c[pc])
    {
        if(dfs(pa+1,pb,pc+1))return true;
    }
    if(b[pb]==c[pc])
    {
        if(dfs(pa,pb+1,pc+1))return true;
    }
    return false;
}
bool dfs2(int pa,int pb,int pc)
{

    //原始对比测试 证明dfs2不等价于dfs
    if(pc==lenc)return true;
    if(pa>lena)return false; 
    if(pb>lenb)return false;
    // if(h[pa][pb])return false;
    // h[pa][pb]=true;
    if(a[pa]==c[pc])
    {
        if(dfs(pa+1,pb,pc+1))return true;
    }
    if(b[pb]==c[pc])
    {
        if(dfs(pa,pb+1,pc+1))return true;
    }
    return false;
}
bool taotao(char *a,char *b,char *c,bool (*func)(int,int,int))
{
	searchsum = 0;//分支计数器
    ::a=a;
    ::b=b;
    ::c=c;
        memset(h,0,sizeof(h));
        lenc=strlen(c);
        lena=strlen(a);
        lenb=strlen(b);
        bool flag=func(0,0,0);
        return flag;
}

#include <time.h>
void create(char *buf,int len)
{
    srand(time(NULL));
    for(int i=0;i<len;++i)
    {
        buf[i]=rand()%10;
        buf[i]+=rand()%2==0? 'A':'a';
    }
    buf[len]=0;
}
void mix(char *buf1,char *buf2,char *buf3)
{
    //混肴
    struct zip
    {
        char *buf;
        int len;
        int setd=0;
    };
    int len1=strlen(buf1);
    int len2=strlen(buf2);
    int len=len1+len2;
    char *tbuf1=new char[len1+1];
    char *tbuf2=new char[len2+1];
    strcpy(tbuf1,buf1);
    strcpy(tbuf2,buf2);
    zip z1={tbuf1,len1};
    zip z2={tbuf2,len2};
    zip bufs[]={z1,z2};
    for(int i=0;i<len;++i)
    {
        int sel=rand()%2;
        zip &buf=bufs[sel];
        if(buf.setd==buf.len) buf=bufs[sel==0?1:0];
        int bindex;
        if(buf.len-buf.setd<buf.len/2)
        {
            for(int j=0;j<buf.len;++j) if(buf.buf[bindex=j]!=0) break;
        }
        else while(buf.buf[bindex=rand()%buf.len]==0);
        buf3[i]=buf.buf[bindex];
        buf.setd++;
        buf.buf[bindex]=0;
    }
    buf3[len]=0;
}
void mix2(char *buf1,char *buf2,char *buf3)
{
    int findex=0;
    int findex2=0;
    int len=strlen(buf1)+strlen(buf2);

int len1=strlen(buf1);
int len2=strlen(buf2);
    for(int i=0;i<len;++i)
    {
        if(findex2==len2) buf3[i]=buf1[findex++];
        else if(findex==len1)buf3[i]=buf2[findex2++];
        else
        {
            int sel=rand()%2;
            if(sel==0)
            {
                buf3[i]=buf1[findex++];
            }
            else buf3[i]=buf2[findex2++];
        }
    }
    buf3[len]=0;

}
#include "MyTimer_win.h"
constexpr bool isdisplay=false;
int main()
{
    char *buf1=new char[210];
    char *buf2=new char[210];
    char *buf3=new char[420];
    int fatsum=0;
	MyTimer timer;
    long long ss1=0;
    long long ss2=0;
    double ti1;
    double ti2;
    for(int i=0;i<100000;++i)
    {
        create(buf1,rand()%100);
        create(buf2,rand()%100);
        mix2(buf1,buf2,buf3);

        //mycode
        // bool isok=mycode(buf1,buf2,buf3);
        // bool isok=taotao(buf1,buf2,buf3,&dfs2); //此测试证明此搜索无需记忆 以及边界判断的精妙之处
		timer.start();
        bool isok=taotao(buf1,buf2,buf3,&whiledfs); //状态转换模型改写递归结构测试
		timer.stop();
        ss1+=searchsum;
        ti1+=timer.ticks();
        if(isdisplay)
        {
            printf("Mycode time:%d\t",timer.ticks());
		    printf("SearchSum=%d\n", searchsum);
        }

		timer.start();
        bool isok2=taotao(buf1,buf2,buf3,&dfs);
		timer.stop();
        ss2+=searchsum;
        ti2+=timer.ticks();
        if(isdisplay)
        {
            printf("Raw time:%d\t",timer.ticks());
            printf("SearchSum=%d\n", searchsum);
            printf("Mycode :%s Taotao: %s \n\n",isok? "True":"False",isok2? "True":"False");

            
            if(isok!=isok2)
            {
                
                printf("Fail \n\n");
                        printf("Data One: %s\n\n Data Two: %s \n\n des: %s \n\n",buf1,buf2,buf3);
            
                fatsum++;
            }
            else printf("OK\n\n");
        }
    }

    if(fatsum==0) printf("All is Ok\n");
    else printf("Fail %d\n",fatsum);
    printf("Mycode 1:%lld\nDFS 2:%lld\n",ss1,ss2);
    printf("Mycode Time 1:%lf\nDFS Time 2:%lf\n",ti1,ti2);
    for(;;);
}