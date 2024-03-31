#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char label[10],input[10],ch1;
int address,taddr,ptaddr,w=0,count=0,i=0,addr,start,end,length,l,k;
FILE *fp1,*fp2;
void check()
{
  address++;
  count++;
  taddr=taddr+1;
            if(count==4)
            {
                fprintf(fp2," ");
                i++;
                if(i==4)
                {
                    fprintf(fp2,"\n\n%X\t\t",taddr);
                    i=0;
                }
               count=0; 
            }   
}
void main()
{
  fp1=fopen("input.txt","r");
  fp2=fopen("output.txt","w");
  printf("ABSOLUTE LOADER\n");
  fprintf(fp2,"MAEMORY ADDRESS\tCONTENTS\n");
  fscanf(fp1,"%s",input);
  while(strcmp(input,"E")!=0)
  {
    if(strcmp(input,"H")==0)
    {
     fscanf(fp1,"%s %X %X %s",label,&start,&end,input);
     address=start;
    }
    else if(strcmp(input,"T")==0)
    {
        l=length;
        ptaddr=addr;
        fscanf(fp1,"%X %X %s",&taddr,&length,input);
        addr=taddr;
        if(w==0)
        {
            ptaddr=address;
            w=1;
        }
        for(k=0;k<(taddr-(ptaddr+l));k++)
        {
            address=address+1;
            fprintf(fp2,"XX");
            count++;
            if(count==4)
            {
                fprintf(fp2," ");
                i++;
                if(i==4)
                {
                    fprintf(fp2,"\n\n%X\t\t",address);
                    i=0;
                }
               count=0; 
            }
        }    
            if(taddr==start)
            {
              fprintf(fp2,"\n\n%X\t\t",taddr);
              fprintf(fp2,"%c%c",input[0],input[1]);
              check();
              fprintf(fp2,"%c%c",input[2],input[3]);
              check();
              fprintf(fp2,"%c%c",input[4],input[5]);
              check();
              fscanf(fp1,"%s",input);
            }
    }
    else
    {
        fprintf(fp2,"%c%c",input[0],input[1]);
              check();
              fprintf(fp2,"%c%c",input[2],input[3]);
              check();
              fprintf(fp2,"%c%c",input[4],input[5]);
              check();
              fscanf(fp1,"%s",input);
    }
}
fclose(fp1);
fclose(fp2);
printf("The contents of output file is \n");
fp2=fopen("output.txt","r");
ch1=fgetc(fp2);
while(ch1!=EOF)
{
    printf("%c",ch1);
    ch1=fgetc(fp2);
}
fclose(fp2);
}

