#include<iostream.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<dos.h>

FILE *fpi,*fpo;
void show(void);
void push(long x);
void bin(float x);
void pdbin(float x);
char stack[300];
long tos=0;
long chcdln[259];//code lenght of a character
char chcd[256][50];
long idata[256];
long total,pdcdln;
long tb,mchcdln=256;
char ddata[256];//used to store the code of a respective character
long ispresent(char x[256]);
long pop();
long ch,th;



void main()
{
	char chai[20],chao[20];

	long i,j;
	//clrscr();
	printf("\n\n\n\n\n\n\n\t\t\tPROGRAM TO DECOMPRESS A FILE.");
	printf("\n\n\n\t\tEnter the intput file name: ");
	scanf("%s",chai);


	fpi = fopen(chai,"rb");
	if(!fpi)
	{
		printf("File not found");
		getch();
		return;
	}
	else
	{
		for(i = 0 ; i < 256 ; i++)
			for(j = 0 ; j < 256 ; j++)
				chcd[i][j]='\0';

		printf("\t\tEnter the output file name: ");
		scanf("%s",chao);
		fpo = fopen(chao,"wb");
		fscanf(fpi,"%ld%ld\n",&total,&pdcdln);
		for(i = 0;i < total;i++)
		{
			fscanf(fpi,"%ld %s ",&idata[i],ddata);
			chcdln[idata[i]] = strlen(ddata);
			if(chcdln[idata[i]]<mchcdln)
				mchcdln=chcdln[idata[i]];
			//printf("%ld ",idata[i]);
			for(j = 0 ; j < chcdln[idata[i]] ; j++)
			{
				chcd[idata[i]][j] = ddata[j];
				//printf("%c",chcd[idata[i]][j]);
			}
			//printf("\n");
		}

		th=fgetc(fpi);
		if(th!=-1&&th<0)
			th=th+256;
		ch=fgetc(fpi);
		if(ch!=-1&&ch<0)
			ch=ch+256;

		while(ch!=EOF)
		{
			bin(float(th));
			th=ch;
			ch=fgetc(fpi);
			if(ch!=-1&&ch<0)
				ch=ch+256;

		}

	}

	if(pdcdln!=0)
		pdbin(float(th));

	printf("\n\n\t\tThe file is successfully decompressed");

	fclose(fpo);
	fclose(fpi);
	printf("\n");
	getch();
}

void bin(float x)
{
	long z = 128;
	long i;
	for(i = 0 ; i < 8 ; i++)
	{
		if(x/z >= 1)
			push(1);
		else
			push(0);
		if(x/z >= 1)
			x = x-z;
		z = z/2;
	}
}

void pdbin(float x)
{
	long z = 128;
	long i;
	for(i = 0 ; i < 8-pdcdln ; i++)
	{
		if(x/z >= 1)
			push(1);
		else
			push(0);
		if(x/z >= 1)
			x = x-z;
		z = z/2;
	}
}


void push(long x)
{
	long z=300,i;
	stack[tos] = x+48;
	tos = tos+1;
	stack[tos]='\0';

	if(tos>=mchcdln)
		z = ispresent(stack);

	if(z!=300)
	{
		printf("%c",z);
		fprintf(fpo,"%c",z);

		for(i=0;i<tos-chcdln[z];i++)
			stack[i]=stack[i+chcdln[z]];
		tos=tos-chcdln[z];
		stack[tos]='\0';
		return;
	}

}

long ispresent(char x[256])
{
	long i,tt=11;

	for(i = 0 ; i < 256; i++)
	{
		tt=strcmp(chcd[i],x);

		if(tt==0)
			return i;

	}
	return  300;
}

