#include <stdio.h>
#include <string.h>
char buf1[210];
char buf2[210];
char buf3[420];
int  main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%s %s %s",buf1,buf2,buf3);
        int findex=0;
        int findex2=0;
        bool isok=true;
        for(int j=0;buf3[j]!=0;++j)
        {
            char c=buf3[j];
            if(c==buf1[findex]&&c==buf2[findex2])
            {
                if(findex<=findex2) findex++;
                else findex2++;
            }
            else if(c==buf1[findex]) findex++;
            else if(c==buf2[findex2]) findex2++;
            else
            {
                isok=false;
                break;
            }

        }
        if(isok)
        {
            printf("Data set %d: yes\n",i+1);
        }
        else
        {
            printf("Data set %d: no\n",i+1);
        }
    }
}