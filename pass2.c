#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void display()
{
    char ch;
    FILE *fp1, *fp2, *fp3, *fp4;

    printf("\nIntermediate file is converted into object code");

    printf("\n\nThe contents of Intermediate file:\n\n");
    fp3 = fopen("intermediate.txt", "r");
    ch = fgetc(fp3);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = fgetc(fp3);
    }
    fclose(fp3);

    printf("\n\nThe contents of Symbol Table :\n\n");
    fp2 = fopen("symtab.txt", "r");
    ch = fgetc(fp2);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = fgetc(fp2);
    }
    fclose(fp2);

    printf("\n\nThe contents of Output file :\n\n");
    fp1 = fopen("output.txt", "r");
    ch = fgetc(fp1);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = fgetc(fp1);
    }
    fclose(fp1);

    printf("\n\nThe contents of Object code file :\n\n");
    fp4 = fopen("objcode.txt", "r");
    ch = fgetc(fp4);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = fgetc(fp4);
    }
    fclose(fp4);
}
void main()
{
    char label[10],opcode[10],operand[10],symbol[10],a[10],ad[10];
    int length,prevaddr,finaddr,address,diff,start,actual_len,add,i,j;
    char code[15][15]={"33","44","53","57"};
    char mnemonic[15][15]={"LDA","STA","LDCH","STCH"};
    FILE *fp1,*fp2,*fp3,*fp4;
    fp1=fopen("intermediate.txt","r");
    fp2=fopen("symtab.txt","r");
    fp3=fopen("output.txt","w");
    fp4=fopen("objcode.txt","w");
    fscanf(fp1,"\t%s\t%s\t%s",label,opcode,operand);
    while(strcmp(opcode,"END")!=0)
    {
        prevaddr=address;
        fscanf(fp1,"%d\t%s\t%s\t%s",&address,label,opcode,operand);
    }
    finaddr=address;
    rewind(fp1);
    fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        fprintf(fp3,"%s\t%s\t%s\n",label,opcode,operand);
        fprintf(fp4,"H^%s^00%s^00%d\n",label,operand,finaddr);
        fscanf(fp1,"%d\t%s\t%s\t%s",&address,label,opcode,operand);
        start=address;
        diff=prevaddr-start;
        fprintf(fp4,"T^00%d^%d",address,diff);
    }
    while(strcmp(opcode,"END")!=0)
    {
        if(strcmp(opcode,"BYTE")==0)
        {
            fprintf(fp3,"%d\t%s\t%s\t%s\t",address,label,opcode,operand);
            length=strlen(operand);
            actual_len=length-3;
            fprintf(fp4,"^");
            for(i=2;i<(actual_len+2);i++)
            {
                sprintf(ad,"%X",operand[i]);
                fprintf(fp3,"%s",ad);
                fprintf(fp4,"%s",ad);
            }
            fprintf(fp3,"\n");
        }
        else if(strcmp(opcode,"WORD")==0)
        {
            length=strlen(operand);
            sprintf(a,"%d",atoi(operand));
            fprintf(fp3,"%d\t%s\t%s\t%s\t00000%s\n",address,label,opcode,operand,a);
            fprintf(fp4,"^00000%s",a);

        }
        else if((strcmp(opcode,"RESW")==0)||(strcmp(opcode,"RESB"))==0)
        {
            fprintf(fp3,"%d\t%s\t%s\t%s\n",address,label,opcode,operand);
        }
        else{
            while(strcmp(opcode,mnemonic[j])!=0)
            {
                j++;
            }
            if(strcmp(operand,"COPY")==0)
            {
                fprintf(fp3,"%d\t%s\t%s\t%s\t%s0000\n",address,label,opcode,operand,code[j]);
            }
            else{
            rewind(fp2);
            fscanf(fp2,"%s\t%d",symbol,&add);
            while(strcmp(operand,symbol)!=0)
            {
                fscanf(fp2,"%s\t%d",symbol,&add);
            }
            fprintf(fp3,"%d\t%s\t%s\t%s\t%s%d\n",address,label,opcode,operand,code[j],add);
            fprintf(fp4,"^%s%d",code[j],add);
            }
        }  
            fscanf(fp1,"%d\t%s\t%s\t%s",&address,label,opcode,operand);
        }
    fprintf(fp3,"%d\t%s\t%s\t%s\n",address,label,opcode,operand);
    //fprintf(fp4,"\nE^00%d",start);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    display();
}

##symtab.txt

ALPHA	2012
FIVE	2018
CHARZ	2021
C1	2022

##intermediate.txt

	**	START	2000
2000	**	LDA	FIVE
2003	**	STA	ALPHA
2006	**	LDCH	CHARZ
2009	**	STCH	C1
2012	ALPHA	RESW	2
2018	FIVE	WORD	5
2021	CHARZ	BYTE	C'Z'
2022	C1	RESB	1
2023	**	END	**
