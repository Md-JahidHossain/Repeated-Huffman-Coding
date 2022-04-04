#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<dos.h>

	struct node
	{
		long frequency;
		long character;
		int flag;
		struct node *next;
		struct node *prev;
		struct node *right;
		struct node *left;
		struct node *par;
	};

	long k=0;
	long tos=0;
	long size(double x);
	void show();
	long stack[256];
	void push(long ch);
	void tra(struct node *r);
	struct node *ins(long x);
	void garbage_collection();
	void insert(long x,long ch);
	void insert(struct node *x);
	long freq[256];
	long chcd[256];
	long chcdln[256];
	long chdata[256][50];
	long tb=0;
	long pdcdln;

	struct node *head,*temp,*root;
	FILE *fpi,*fpo,*fp;

void main()
{
	 char chai[20],chao[20];
	 long ch;
	 long cv;
	 long i,j,total=0;

	 for(i=0;i<256;i++)
	 {

		 freq[i]=0;
		 chcdln[i]=0;
		 stack[i]=0;

	 }

	printf("\n\n\n\n\n\n\n\t\t\tPROGRAM TO COMPRESS A FILE.");
	printf("\n\n\n\t\tEnter the intput file name: ");
	scanf("%s",chai);
	fpi=fopen(chai,"rb");
	if(fpi==NULL)
	{
		 printf("\n\t\tInput file is not found.");
		 return;
	}
	else
	{
		 printf("\t\tEnter the output file name:");
		 scanf("%s",chao);

		 ch=fgetc(fpi);
		 if(ch!=-1&&ch<0)
			cv=ch+256;
		 else
			cv=ch;

		 while(ch!=EOF)
		 {
			freq[cv]++;
			ch=fgetc(fpi);
			if(ch!=-1&&ch<0)
				cv=ch+256;
			else
				cv=ch;
		 }
	}

	fclose(fpi);
	fpo=fopen(chao,"wb");

	for(i=0;i<256;i++)
	{
		if(freq[i]!=0)
		{
			insert(freq[i],i);
			total++;
		}
	}

	for(i=0;i<total-1;i++)
	{
		root = ins(head->frequency + head->next->frequency);
	}

	if(root!=NULL)
	{
		root->flag=0;
		tra(root);
	}

	for(i=0;i<256;i++)
		if(freq[i]!=0)
			tb=tb%8+freq[i]*chcdln[i];

	pdcdln=8-(tb%8);
	if(pdcdln==8)
		pdcdln=0;

	fprintf(fpo,"%ld %ld\n",total,pdcdln);
	printf("%ld %ld\n",total,pdcdln);

	for(i=0;i<256;i++)
	{
		if(chcdln[i]!=0)
		{
			fprintf(fpo,"%ld ",i);
			printf("%ld ",i);

			for(j=0;j<chcdln[i];j++)
			{
				fprintf(fpo,"%c",chdata[i][j]+48);
				printf("%c",chdata[i][j]+48);
			}
			fprintf(fpo,"\n");
			printf("\n");
		}
	}

	fpi = fopen(chai,"rb");

	ch=fgetc(fpi);
	if(ch!=-1&&ch<0)
		cv=ch+256;
	else
		cv=ch;

	while(ch!=EOF)
	{
		push(cv);
		ch=fgetc(fpi);
		if(ch!=-1&&ch<0)
			cv=ch+256;
		else
			cv=ch;

	}

	if(tos>0)
	{
		for(i=tos;i<8;i++)
			stack[i]=0;

	       j=0;
	       for(i=0;i<8;i++)
			j = j*2 + stack[i];

	       fprintf(fpo,"%c",j);
	}

	fclose(fpi);
	fclose(fpo);
	printf("\n\n\t\tThe file is successfully compressed.");
	garbage_collection();

}

void insert(long x, long ch)
{
	struct node *newnode;
	newnode = (struct node *)malloc(sizeof(struct node));
	newnode->frequency = x;
	newnode->character = ch;
	newnode->right = NULL;
	newnode->left = NULL;
	newnode->next=NULL;

	if(head==NULL)
	{
		head = newnode;
		head->next = NULL;
	}
	else
	{
		if(newnode->frequency < head->frequency)
		{
			newnode->next = head;
			newnode->next->prev = newnode;
			head = newnode;
		}
		else
		{
			temp=head;
			while(temp->next != NULL && newnode->frequency > temp->next->frequency)
				temp = temp->next;

			if(temp->next == NULL)
				temp->next=newnode;
			else
			{

				newnode->next = temp->next;
				newnode->next->prev = newnode;
				newnode->prev = temp;
				temp->next = newnode;

			}
		}
	}
}


struct node *ins(long x)
{
	struct node *newnode;
	newnode=(struct node *)malloc(sizeof(struct node));
	newnode->frequency=x;
	newnode->character=NULL;
	newnode->next=NULL;
	newnode->prev=NULL;
	newnode->left=head;
	head->par=newnode;
	newnode->left->flag=0;
	newnode->right=head->next;
	head->next->par=newnode;
	newnode->right->flag=1;
	newnode->par=NULL;
	head=head->next->next;
	insert(newnode);
	return newnode;

}


void garbage_collection()
{
	temp=head;
	while(head!=NULL)
	{
		head=head->next;
		free(temp);
		temp=head;
	}
}

void tra(struct node *r)
{
	long i; //local variable declared for loop control

	if(r!=NULL)
	{
		if(r->par != NULL)
			chcd[k-1] = r->flag;

		if(r->left == NULL && r->right == NULL)
		{
			chcdln[r->character] = k;

			for(i=0;i < chcdln[r->character];i++)
			{
				chdata[r->character][i] = chcd[i];
			}
		}

		k=k+1;
		tra(r->left);
		k=k+1;
		tra(r->right);
	}

	k=k-1;

	return;
}


void insert(struct node *x)
{
	x->next = NULL;
	x->prev = NULL;

	if(head == NULL)head = x;
	else
	{
		if(x->frequency < head->frequency)
		{
			x->next = head;
			x->next->prev = x;
			head=x;
		}
		else
		{
			temp=head;
			while(temp->next!=NULL && x->frequency > temp->frequency)
			temp=temp->next;

			if(temp->next == NULL)temp->next=x;
			else
			{
				x->next = temp->next;
				x->next->prev = x;
				x->prev = temp;
				temp->next = x;
			}

		}
	}
}

void push(long ch)
{

	long i,y;

	y = chcdln[ch];

	for(i=0;i < y;i++)
	{
		stack[tos] = chdata[ch][i];
		tos++;
	}

	long ii,h=0,q;

	while(tos > 7)
	{
		h=0;

		for(q=0;q<=7;q++)
		{
			h = h*2 + stack[q];
		}

		fprintf(fpo,"%c",h);

		for(q=0;q < tos-8;q++)  // it must be efficient
		{
			stack[q] = stack[q+8];
		}
		tos=tos-8;
	}
}