#include<stdio.h>
void main()
{
    int pn,fn,pages[30],frames[10],flag,fpos=0,pos,j,i,k,least[30];
    printf("Enter the number of pages\n");
    scanf("%d",&pn);
    printf("Enter the reference string\n");
    for(i=0;i<pn;i++)
    {
      scanf("%d",&pages[i]);
    }
    printf("Enter the number of frames\n");
    scanf("%d",&fn);
    for(i=0;i<fn;i++)
    {
        frames[i]=-1;
    }
    printf("pages\tframes\n");
    for(i=0;i<pn;i++)
    {
        flag=0;
        for(j=0;j<fn;j++)
        {
            if(pages[i]==frames[j])
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            if(fpos<fn)
            {
                frames[fpos]=pages[i];
                fpos++;
            }
            else
            {
                for(j=0;j<fn;j++)
                {
                    least[j]=0;
                    for(k=i-1;k>=0;k--)
                    {
                        if(frames[j]==pages[k])
                        {
                            least[j]=i-k;
                            break;
                        }
                    }
                }
                pos=0;
                for(j=1;j<fn;j++)
                {
                    if(least[j]>least[pos])
                    {
                        pos=j;
                    }
                }
                frames[pos]=pages[i];
            }
        }    
            printf("%d\t",pages[i]);
            if(flag==1)
            {
                printf("\t page hit\n");
            }
            else{
                for(j=0;j<fn;j++)
                {
                    printf("%d\t",frames[j]);
                }
                printf("\n");
            }
    }
}