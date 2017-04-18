#include <stdio.h>
#include <string.h>
char buf1[210];
char buf2[210];
char buf3[420];
char mem[210][210];
// int  main()
// {
//     int n;
//     scanf("%d",&n);
//     for(int i=0;i<n;++i)
//     {
//         scanf("%s %s %s",buf1,buf2,buf3);
//         int findex=0;
//         int findex2=0;
//         bool isok=true;
//         for(int j=0;buf3[j]!=0;++j)
//         {
//             char c=buf3[j];
//             if(c==buf1[findex]&&c==buf2[findex2])
//             {
//                 if(findex<=findex2) findex++;
//                 else findex2++;
//             }
//             else if(c==buf1[findex]) findex++;
//             else if(c==buf2[findex2]) findex2++;
//             else
//             {
//                 isok=false;
//                 break;
//             }

//         }
//         if(isok)
//         {
//             printf("Data set %d: yes\n",i+1);
//         }
//         else
//         {
//             printf("Data set %d: no\n",i+1);
//         }
//     }
// }
    struct state
    {
        int pa;
        int pb;
        int pc;
        bool isused; //记录父状态是否已经处理过
    };
state tstack[100000];
int main()
{

    
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%s %s %s",buf1,buf2,buf3);
        int len1=strlen(buf1);
        int len2=strlen(buf2);
        int len3=strlen(buf3);
        memset(mem,false,sizeof(mem));
        int sptr = 0;//栈底
    #define push(a) tstack[++sptr]=a
    #define pop() sptr--
    #define top() tstack[sptr]
    #define empty() sptr==0
        state root={0,0,0,false};//根状态
        push(root);
        bool isok=false;
        while(!empty())
        {
            state &nowp = top();
            if(nowp.pa>len1) {pop();continue;}
            if(nowp.pb>len2) {pop();continue;}
            if (nowp.pc == len3) {isok=true;break; }
            if(mem[nowp.pa][nowp.pb]) {pop();continue;}
            if(!nowp.isused)
            {
                nowp.isused=true;
                mem[nowp.pa][nowp.pb]=true;
                //这里校验分支有效性 如果无效则无需放入 对应cstate为false
                if(buf1[nowp.pa]==buf3[nowp.pc])
                {
                    tstack[++sptr]={ nowp.pa + 1,nowp.pb,nowp.pc + 1,false};
                }
                if(buf2[nowp.pb]==buf3[nowp.pc])
                {
                    tstack[++sptr] = { nowp.pa,nowp.pb + 1,nowp.pc + 1,false};
                }
                
            }
            else
            {
                pop();
            }
        }
        printf("Data set %d: ",i+1);
        if(isok)
        {
            puts("yes");
        }
        else puts("no");
    
    }
}
