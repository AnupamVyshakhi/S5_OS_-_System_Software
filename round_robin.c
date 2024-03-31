#include<stdio.h>
void main()
{
    int n,bt[10],arr[10],i,qun,x,temp[10];
    float avgtat=0,avgwt=0;
    printf("Enter the number of process\n");
    scanf("%d",&n);
    x=n;
    printf("Enter the process details\n");
    for(i=0;i<n;i++)
    {
        printf("Arrival time\n");
        scanf("%d",&arr[i]);
        printf("Burst time\n");
        scanf("%d",&bt[i]);
        temp[i]=bt[i];
    }
    printf("Enter the time quantum\n");
    scanf("%d",&qun);
    printf("PROCESS\tBT\tWT\tTAT\n");
    int total=0,counter=0;

    for(total=0,i=0;x!=0;)
    {
        if(temp[i]<=qun&&temp[i]>0)
        {
            total=total+temp[i];
            temp[i]=0;
            counter=1;
        }
        else if(temp[i]>0)
        {
            temp[i]=temp[i]-qun;
            total=total+qun;
        }
        if(temp[i]==0&&counter==1)
        {
            x--;
            printf("%d\t%d\t%d\t%d\n",i+1,bt[i],total-arr[i]-bt[i],total-arr[i]);
            avgtat=avgtat+total-arr[i];
            avgwt=avgwt+total-arr[i]-bt[i];
            counter=0;
        }
        if(i==n-1)
        {
            i=0;
        }
        else if(arr[i+1]<=total)
        {
            i++;
        }
        else{
            i=0;
        }
    }
    avgtat=(float)avgtat/n;
    avgwt=(float)avgwt/n;
    printf("avgtat is %f\n",avgtat);
    printf("avgwt is %f\n",avgwt);
}