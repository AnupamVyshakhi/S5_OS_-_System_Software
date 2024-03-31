#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char bit[30],bitmask[30];
void bitmask_convert(char mask[])
{
    int len=strlen(mask);
    int i;
    strcpy(bit,"");
    for(i=0;i<len;i++)
    {
        switch(mask[i])
        {
            case '0':strcat(bit,"0000");
                     break;
            case '1':strcat(bit,"0001");
                     break;
            case '2':strcat(bit,"0010");
                     break;
            case '3':strcat(bit,"0011");
                     break;
            case '4':strcat(bit,"0100");
                     break;
            case '5':strcat(bit,"0101");
                     break;
            case '6':strcat(bit,"0110");
                     break;
            case '7':strcat(bit,"0111");
                     break;
            case '8':strcat(bit,"1000");
                     break;
            case '9':strcat(bit,"1001");
                     break;
            case 'A':strcat(bit,"1010");
                     break;
            case 'B':strcat(bit,"1011");
                     break;
            case 'C':strcat(bit,"1100");
                     break;
            case 'D':strcat(bit,"1101");
                     break;
            case 'E':strcat(bit,"1110");
                     break;
            case 'F':strcat(bit,"1111");
                     break;
            default:break;
        }
    }
}
void main()
{
    char name[10],rec[30],first[20],second[30];
    int addr,add,start,length,bitmask_index,i,modif_objcode;
    FILE *objptr;
    objptr=fopen("program.txt","r");
    printf("Enter the starting address\n");
    scanf("%X",&start);
    addr=start;
    fscanf(objptr,"%s",rec);
    if(strcmp(rec,"H")==0)
    {
        fscanf(objptr,"%s %X %X",name,&add,&length);
        printf("The name of the program is %s\n",name);
        printf("ADDRESS\tOBJCODE\n");
    }
    else{
        printf("Invalid Object code\n");
        fclose(objptr);
        exit(1);
    }
    strcpy(rec,"");
    fscanf(objptr,"%s",rec);
    while(strcmp(rec,"E")!=0)
    {
        if(strcmp(rec,"T")==0)
        {
            fscanf(objptr,"%X %X %s",&add,&length,bitmask);
            add=add+start;
            bitmask_index=0;
            bitmask_convert(bitmask);
            fscanf(objptr,"%s",rec);
        }
        if(bit[bitmask_index]=='1')
        {
            for(i=0;i<6;i++)
            {
              if(i<2)
              {
                first[i]=rec[i];
              }
              else
              {
                second[i-2]=rec[i];
              }
            }
            first[2]='\0';
            second[4]='\0';
            modif_objcode=strtol(second,NULL,16);
            modif_objcode+=start;
            printf("%X\t%s%X\n",add,first,modif_objcode);
        }
        else
        {
           printf("%X\t%s\n",add,rec);
        }
        add+=3;
        bitmask_index++;
        fscanf(objptr,"%s",rec);
    }
    fclose(objptr); 
}