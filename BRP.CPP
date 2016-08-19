#include<stdio.h>
#include<conio.h>

int SSQ=10,SGQ;
int nnum=0,extra,actionflag=0,carry1,carry2;

class block
{
	public:
		int hn,at,tr,val;
		float pn;

	public:

		void getvalue()
		{
			scanf("%d",&val);
			hn=at=tr=0;
			pn=0.0;
		}
};

struct Snode
{
	block B;
	struct Snode *next;
};

struct Gnode
{
	block B;
	struct Gnode *next;
};

class SQueue
{
	public:
		Snode *rear;
		Snode *front;
		block tempB;
		Snode *p,*inode,*jnode;
		int i;
		float sml;

	public:

		SQueue()
		{
			rear = NULL;
			front = NULL;
		}

		int check(int val);
		void update(int time);
		void updateall(int time);
		void descend();
		int isfull();
		void remove();
		void newadd(block B,int time);
};

int SQueue :: check(int val)
{
	p=front;
	inode=p;
	while(p!=NULL)
	{
		if(val==p->B.val)
		{
			inode=p;
			return 1;
		}
		inode=p;
		p=p->next;
	}
	return 0;
};

void SQueue :: update(int time)
{
	inode->B.hn++;
	inode->B.at=time;
	inode->B.tr=time-(inode->B.at);
	if(inode->B.tr==0)
		inode->B.pn=(float)inode->B.hn;
	else
	{
		inode->B.pn=(float)(inode->B.hn)/(float)(inode->B.tr);
	}
};

void SQueue :: updateall(int time)
{
	p=front;
	while(p!=NULL)
	{
		p->B.tr=time-(p->B.at);
		if(p->B.tr==0)
			p->B.pn=1;
		else
			p->B.pn=(float)p->B.hn/(float)p->B.tr;
		p=p->next;
	}
};

void SQueue :: descend()
{
	inode=front;
	while(inode!=NULL)
	{
		jnode=inode->next;
		while(jnode!=NULL)
		{
			if(jnode->B.pn>inode->B.pn)
			{
				tempB=(jnode->B);
				jnode->B=inode->B;
				inode->B=tempB;
			}
			jnode=jnode->next;
		}
		inode=inode->next;
	}
};

int SQueue :: isfull()
{
	i=0;
	p=front;
	while(p!=NULL)
	{
		i++;
		p=p->next;
	}
	if(i>=SSQ)
		return 1;
	return 0;
};

void SQueue :: remove()
{
	inode=front;
	p=front;
	sml=inode->B.pn;
	while(inode!=NULL)
	{
		if(inode->B.pn<=sml)
		{
			sml=inode->B.pn;
			p=inode;
		}
		inode=inode->next;
	}
	carry1=p->B.val;
	jnode=front;
	if(p==front)
	{
		front = front->next;
		delete p;
	}
	else
	{
		if(p==rear)
		{
			while(jnode->next!=rear)
			{
				jnode=jnode->next;
			}
			rear=jnode;
			rear->next=NULL;
			delete p;
		}
		else
		{
			while((jnode->next)!=p)
			{
				jnode=jnode->next;
			}
			jnode->next=p->next;
			delete p;
		}
	}
};

void SQueue :: newadd(block B,int time)
{
	p=new Snode;
	p->B.hn=1;
	p->B.pn=1;
	p->B.at=time;
	p->B.tr=time-p->B.at;
	p->B.val=B.val;
	p->next=NULL;
	if(rear==NULL || front==NULL)
		rear=front=p;
	else
	{
		rear->next=p;
		rear=p;
	}
};

class GQueue
{
	public:
		Gnode *rear,*front;
		Gnode *p,*temp;
		int i;

	public:
		GQueue()
		{
			rear = NULL;
			front = NULL;
		}

		int check(block B);
		void remove();
		int isfull();
		void removeLRU();
		void addMRU(block B);
		void changeinsize();
};

int GQueue :: check(block B)
{
	if(front==NULL)
	{
		return 0;
	}
	else
	{
		p = front;
		temp=p;
		while(p!=NULL)
		{
			if(p->B.val==B.val)
			{
				temp=p;
				return 1;
			}
			temp=p;
			p = p->next;
		}
		return 0;
	}
};

void GQueue :: remove()
{
	if(temp==front)
	{
		front=front->next;
		delete temp;
	}
	else
	{
		if(temp==rear)
		{
			p=front;
			while(p->next!=rear)
			{
				p=p->next;
			}
			rear=p;
			delete temp;
			rear->next=NULL;
		}
		else
		{
			p=front;
			while(p->next!=temp)
			{
				p=p->next;
			}
			p->next=temp->next;
			delete temp;
		}
	}
	return;
};

int GQueue :: isfull()
{
	i=0;
	p=front;
	while(p!=NULL)
	{
		i++;
		p=p->next;
	}
	if(i>=SGQ)
		return 1;
	return 0;
};

void GQueue :: removeLRU()
{
	p=front;
	front=p->next;
	carry2=p->B.val;
	delete p;
};

void GQueue :: addMRU(block B)
{
	temp=new Gnode;
	temp->B=B;
	temp->next=NULL;
	if(rear==NULL || front==NULL)
	{
		rear=front=temp;
	}
	else
	{
		rear->next=temp;
		rear=temp;
	}
};

void GQueue :: changeinsize()
{
	i=0;
	if(front==NULL)
		return;
	if(front==rear)
		i=1;
	else
	{
		i=0;
		for(p=front;p!=NULL;p=p->next)
		{
			i++;
		}
	}

	if(i<=SGQ)
		return;
	else
	{
		i=0;
		for(p=front;p!=NULL;p=p->next)
		{
			rear=p;
			if(i==SGQ)
			{
				while(p!=NULL)
				{
					temp=p;
					p=p->next;
					delete temp;
				}
			}
			if(i>SGQ)
				return;

			i++;
		}
	}
	return;
};

GQueue GQueue;
SQueue SQueue;

int max(int val1,int val2)
{
	if(val1>val2)
		return val1;
	return val2;
}

int min(int val1,int val2)
{
	if(val1<val2)
		return val1;
	return val2;
}

void GQBAssg(block B,int time)
{
	int i,j;

	SGQ=0.1*SSQ;
	if((SQueue.check(B.val))==1)
	{
		SGQ=max(0.1*SSQ,(SGQ-SSQ)/(SSQ-SGQ));
		GQueue.changeinsize();
		SQueue.update(time);
		SQueue.updateall(time);
		SQueue.descend();
		actionflag=1;
		return;
	}
	SGQ=min(0.9*SSQ,(SGQ+SSQ)/SGQ);
	GQueue.changeinsize();
	if((GQueue.check(B))==1)
	{
		actionflag=2;
		GQueue.remove();
		if((SQueue.isfull())==1)
		{
			SQueue.remove();
			SQueue.updateall(time);
			SQueue.descend();
			actionflag=3;
		}
		SQueue.newadd(B,time);
		SQueue.updateall(time);
		SQueue.descend();
	}
	else
	{
		actionflag=4;
		if((GQueue.isfull())==1)
		{
			actionflag=5;
			GQueue.removeLRU();
		}
		GQueue.addMRU(B);
		SQueue.updateall(time);
		SQueue.descend();
	}
}

void show(int num,block B[50],int time,int i)
{
	int j,izero;

	clrscr();

	printf("At Time %d,\t",time);
	switch(actionflag)
	{
		case 0:
			printf("Error");
			break;

		case 1:
			printf("Block %d is found in SDD Queue hence its Popularity is updated\n\t\tand Size of Ghost Queue is changed",B[i].val);
			break;

		case 2:
			printf("Block %d is found in Ghost Queue hence it is moved to SDD Queue\n",B[i].val);
			break;

		case 3:
			printf("Block %d is found in Ghost Queue but SSD Queue is full\n\t\thence Block %d is replaced by Block %d",B[i].val,carry1,B[i].val);
			break;

		case 4:
			printf("Block %d is not found in SDD Queue as well as in Ghost Queue\n\t\thence Block %d is added as a MRU in Ghost Queue",B[i].val,B[i].val);
			break;

		case 5:
			printf("Block %d is not found in SDD Queue as well as in Ghost Queue but\t\tGhost Queue is full hence Block %d is replaced by Block %d",B[i].val,carry2,B[i].val);
			break;

		default:
			printf("Error");
	}

	izero=i;
	if(num>12)
	{
		if((num - izero)<12)
		{
			printf("\n\t\t ");
			if(nnum==0)
			{
				extra=izero-1;
				nnum=1;
			}
			for(j=extra;j<num;j++)
			{
				if(j>=9)
					printf("---- ");
				else
					printf("--- ");
			}
			printf("\nInput\t->\t|");

			for(j=extra;j<num;j++)
			{
				if(B[j].val<10)
				{
					if(j>=9)
						printf("  %d |",B[j].val);
					else
						printf(" %d |",B[j].val);
				}
				if(B[j].val>=10)
				{
					if(j>=9)
						printf(" %d |",B[j].val);
					else
						printf("%d |",B[j].val);
				}
			}
			printf("\n\t\t ");
			for(j=extra;j<num;j++)
			{
				if(j>=9)
					printf("---- ");
				else
					printf("--- ");
			}
			printf("\n\t\t  ");
			for(j=extra;j<i;j++)
			{
				if(j>=9)
					printf("     ");
				else
					printf("    ");
			}
			textcolor(YELLOW+BLINK);
			cprintf("^");
			textcolor(WHITE);
		}
		else
		{
			izero=i;
			printf("\n\t\t ");
			while(izero<(12+i))
			{
				if(izero>=9)
					printf("---- ");
				else
					printf("--- ");
				izero++;
			}
			izero=i;
			printf("\nInput\t->\t|");
			while(izero<(12+i))
			{
				if(B[izero].val<10)
				{
					if(izero>=9)
						printf("  %d |",B[izero].val);
					else
						printf(" %d |",B[izero].val);
				}
				if(B[izero].val>=10)
				{
					if(izero>=9)
						printf(" %d |",B[izero].val);
					else
						printf("%d |",B[izero].val);
				}
				izero++;
			}
			izero=i;
			printf("\n\t\t ");
			while(izero<(12+i))
			{
				if(izero>=9)
					printf("---- ");
				else
					printf("--- ");
				izero++;
			}
			printf("\n\t\t  ");
			textcolor(YELLOW+BLINK);
			cprintf("^");
			textcolor(WHITE);
		}
	}
	else
	{
		printf("\n\t\t ");
		for(j=0;j<num;j++)
		{
			if(j>=9)
				printf("---- ");
			else
				printf("--- ");
		}
		printf("\nInput\t->\t|");
		for(j=0;j<num;j++)
		{
			if(B[j].val<10)
			{
				if(j>=9)
					printf("  %d |",B[j].val);
				else
					printf(" %d |",B[j].val);
			}
			if(B[j].val>=10)
			{
				if(j>=9)
					printf(" %d |",B[j].val);
				else
					printf("%d |",B[j].val);
			}
		}
		printf("\n\t\t ");
		for(j=0;j<num;j++)
		{
			if(j>=9)
				printf("---- ");
			else
				printf("--- ");
		}
		printf("\n\t\t  ");
		for(j=i;j>0;j--)
		{
			printf("    ");
		}
		textcolor(YELLOW+BLINK);
		cprintf("^");
		textcolor(WHITE);
	}
	printf("\nSDD Queue\t");
	j=1;
	printf(" ");
	textcolor(GREEN);
	cprintf("-----");
	textcolor(WHITE);
	for(j=1;j<SSQ-1;j++)
	{
		printf(" -----");
	}
	printf(" ");
	textcolor(RED);
	cprintf("-----");
	textcolor(WHITE);
	printf("\n\t\t");

	j=0;
	if(SQueue.front==NULL)
	{
		textcolor(GREEN);
		cprintf("|");
		textcolor(WHITE);
		printf("     ");
		textcolor(GREEN);
		cprintf("|");
		textcolor(WHITE);
		for(j=1;j<SSQ-2;j++)
		{
			printf("     |");
		}
		printf("     ");
		textcolor(RED);
		cprintf("|");
		printf("     ");
		textcolor(RED);
		cprintf("|");
		textcolor(WHITE);
		j=SSQ;
	}
	else
	{
		j=0;
		textcolor(GREEN);
		cprintf("|");
		textcolor(WHITE);
		if(SQueue.front->B.val<10)
		{
			printf("  %d  ",SQueue.front->B.val);
			textcolor(GREEN);
			cprintf("|");
			textcolor(WHITE);
			j++;
		}
		else
		{
			printf(" %d  ",SQueue.front->B.val);
			textcolor(GREEN);
			cprintf("|");
			textcolor(WHITE);
			j++;
		}

		for(SQueue.p=SQueue.front;SQueue.p!=NULL;SQueue.p=SQueue.p->next)
		{
			if(SQueue.p==SQueue.front)
				SQueue.p=SQueue.p->next;

			if(SQueue.p==NULL)
				break;

			if(j==8)
			{
				if(SQueue.p==NULL)
				{
					printf("     ");
					textcolor(RED);
					cprintf("|");
					textcolor(WHITE);
					j++;
					printf("     ");
					textcolor(RED);
					cprintf("|");
					textcolor(WHITE);
					j++;
					break;
				}
				else
				{
					if(SQueue.p->B.val<10)
						printf("  %d  ",SQueue.p->B.val);
					else
						printf(" %d  ",SQueue.p->B.val);
					textcolor(RED);
					cprintf("|");
					textcolor(WHITE);
					j++;
					SQueue.p=SQueue.p->next;
					if(SQueue.p==NULL)
					{
						printf("     ");
						textcolor(RED);
						cprintf("|");
						textcolor(WHITE);
						j++;
						break;
					}
					else
					{
						if(SQueue.p->B.val<10)
							printf("  %d  ",SQueue.p->B.val);
						else
							printf(" %d  ",SQueue.p->B.val);
						textcolor(RED);
						cprintf("|");
						textcolor(WHITE);
						j++;
						break;
					}
				}
			}
			else
			{
				if(SQueue.p->B.val<10)
					printf("  %d  |",SQueue.p->B.val);
				else
					printf(" %d  |",SQueue.p->B.val);

				j++;
			}
		}

	}

	while(j<SSQ)
	{
		if(j==SSQ-2)
		{
			printf("     ");
			textcolor(RED);
			cprintf("|");
			textcolor(WHITE);
			printf("     ");
			textcolor(RED);
			cprintf("|");
			textcolor(WHITE);
			break;
		}
		printf("     |");
		j++;
	}

	printf("\n\t\t ");

	j=1;
	textcolor(GREEN);
	cprintf(".....");
	textcolor(WHITE);
	printf(".");
	for(j=1;j<SSQ-1;j++)
	{
		printf("......");
	}
	textcolor(RED);
	cprintf(".....");
	textcolor(WHITE);
	printf("\n\t\t");

	j=0;
	printf("\nPopularity\t");

	j=0;
	if(SQueue.front==NULL)
	{
		textcolor(GREEN);
		cprintf("|");
		textcolor(WHITE);
		printf("     ");
		textcolor(GREEN);
		cprintf("|");
		textcolor(WHITE);
		for(j=1;j<SSQ-2;j++)
		{
			printf("     |");
		}
		printf("     ");
		textcolor(RED);
		cprintf("|");
		printf("     ");
		textcolor(RED);
		cprintf("|");
		textcolor(WHITE);
		j=SSQ;
	}
	else
	{
		j=0;
		textcolor(GREEN);
		cprintf("|");
		textcolor(WHITE);
		if(SQueue.front->B.pn<10)
		{
			printf(" %.1f ",SQueue.front->B.pn);
			textcolor(GREEN);
			cprintf("|");
			textcolor(WHITE);
			j++;
		}
		else
		{
			printf("%.1f ",SQueue.front->B.pn);
			textcolor(GREEN);
			cprintf("|");
			textcolor(WHITE);
			j++;
		}

		for(SQueue.p=SQueue.front;SQueue.p!=NULL;SQueue.p=SQueue.p->next)
		{
			if(SQueue.p==SQueue.front)
				SQueue.p=SQueue.p->next;

			if(SQueue.p==NULL)
				break;

			if(j==8)
			{
				if(SQueue.p==NULL)
				{
					printf("     ");
					textcolor(RED);
					cprintf("|");
					textcolor(WHITE);
					j++;
					printf("     ");
					textcolor(RED);
					cprintf("|");
					textcolor(WHITE);
					j++;
					break;
				}
				else
				{
					if(SQueue.p->B.pn<10)
						printf(" %.1f ",SQueue.p->B.pn);
					else
						printf("%.1f ",SQueue.p->B.pn);
					textcolor(RED);
					cprintf("|");
					textcolor(WHITE);
					j++;
					SQueue.p=SQueue.p->next;
					if(SQueue.p==NULL)
					{
						printf("     ");
						textcolor(RED);
						cprintf("|");
						textcolor(WHITE);
						j++;
						break;
					}
					else
					{
						if(SQueue.p->B.pn<10)
							printf(" %.1f ",SQueue.p->B.pn);
						else
							printf("%.1f ",SQueue.p->B.pn);
						textcolor(RED);
						cprintf("|");
						textcolor(WHITE);
						j++;
						break;
					}
				}
			}
			else
			{
				if(SQueue.p->B.pn<10)
					printf(" %.1f |",SQueue.p->B.pn);
				else
					printf("%.1f |",SQueue.p->B.pn);

				j++;
			}
		}

	}

	while(j<SSQ)
	{
		if(j==SSQ-2)
		{
			printf("     ");
			textcolor(RED);
			cprintf("|");
			textcolor(WHITE);
			printf("     ");
			textcolor(RED);
			cprintf("|");
			textcolor(WHITE);
			break;
		}
		printf("     |");
		j++;
	}

	printf("\n\t\t ");

	j=1;
	textcolor(GREEN);
	cprintf(".....");
	textcolor(WHITE);
	printf(".");
	for(j=1;j<SSQ-1;j++)
	{
		printf("......");
	}
	textcolor(RED);
	cprintf(".....");
	textcolor(WHITE);
	printf("\n\t\t");

	j=0;
	printf("\nLast Acs Time\t");

	j=0;
	if(SQueue.front==NULL)
	{
		textcolor(GREEN);
		cprintf("|");
		textcolor(WHITE);
		printf("     ");
		textcolor(GREEN);
		cprintf("|");
		textcolor(WHITE);
		for(j=1;j<SSQ-2;j++)
		{
			printf("     |");
		}
		printf("     ");
		textcolor(RED);
		cprintf("|");
		printf("     ");
		textcolor(RED);
		cprintf("|");
		textcolor(WHITE);
		j=SSQ;
	}
	else
	{
		j=0;
		textcolor(GREEN);
		cprintf("|");
		textcolor(WHITE);
		if(SQueue.front->B.at<10)
		{
			printf("  %d  ",SQueue.front->B.at);
			textcolor(GREEN);
			cprintf("|");
			textcolor(WHITE);
			j++;
		}
		else
		{
			printf(" %d  ",SQueue.front->B.at);
			textcolor(GREEN);
			cprintf("|");
			textcolor(WHITE);
			j++;
		}

		for(SQueue.p=SQueue.front;SQueue.p!=NULL;SQueue.p=SQueue.p->next)
		{
			if(SQueue.p==SQueue.front)
				SQueue.p=SQueue.p->next;

			if(SQueue.p==NULL)
				break;

			if(j==8)
			{
				if(SQueue.p==NULL)
				{
					printf("     ");
					textcolor(RED);
					cprintf("|");
					textcolor(WHITE);
					j++;
					printf("     ");
					textcolor(RED);
					cprintf("|");
					textcolor(WHITE);
					j++;
					break;
				}
				else
				{
					if(SQueue.p->B.at<10)
						printf("  %d  ",SQueue.p->B.at);
					else
						printf(" %d ",SQueue.p->B.at);
					textcolor(RED);
					cprintf("|");
					textcolor(WHITE);
					j++;
					SQueue.p=SQueue.p->next;
					if(SQueue.p==NULL)
					{
						printf("     ");
						textcolor(RED);
						cprintf("|");
						textcolor(WHITE);
						j++;
						break;
					}
					else
					{
						if(SQueue.p->B.at<10)
							printf("  %d  ",SQueue.p->B.at);
						else
							printf(" %d ",SQueue.p->B.at);
						textcolor(RED);
						cprintf("|");
						textcolor(WHITE);
						j++;
						break;
					}
				}
			}
			else
			{
				if(SQueue.p->B.at<10)
					printf("  %d  |",SQueue.p->B.at);
				else
					printf(" %d  |",SQueue.p->B.at);

				j++;
			}
		}

	}

	while(j<SSQ)
	{
		if(j==SSQ-2)
		{
			printf("     ");
			textcolor(RED);
			cprintf("|");
			textcolor(WHITE);
			printf("     ");
			textcolor(RED);
			cprintf("|");
			textcolor(WHITE);
			break;
		}
		printf("     |");
		j++;
	}

	printf("\n\t\t ");

	j=1;
	textcolor(GREEN);
	cprintf(".....");
	textcolor(WHITE);
	printf(".");
	for(j=1;j<SSQ-1;j++)
	{
		printf("......");
	}
	textcolor(RED);
	cprintf(".....");
	textcolor(WHITE);
	printf("\n\t\t");

	j=0;
	printf("\nResidence Time\t");

	j=0;
	if(SQueue.front==NULL)
	{
		textcolor(GREEN);
		cprintf("|");
		textcolor(WHITE);
		printf("     ");
		textcolor(GREEN);
		cprintf("|");
		textcolor(WHITE);
		for(j=1;j<SSQ-2;j++)
		{
			printf("     |");
		}
		printf("     ");
		textcolor(RED);
		cprintf("|");
		printf("     ");
		textcolor(RED);
		cprintf("|");
		textcolor(WHITE);
		j=SSQ;
	}
	else
	{
		j=0;
		textcolor(GREEN);
		cprintf("|");
		textcolor(WHITE);
		if(SQueue.front->B.tr<10)
		{
			printf("  %d  ",SQueue.front->B.tr);
			textcolor(GREEN);
			cprintf("|");
			textcolor(WHITE);
			j++;
		}
		else
		{
			printf(" %d  ",SQueue.front->B.tr);
			textcolor(GREEN);
			cprintf("|");
			textcolor(WHITE);
			j++;
		}

		for(SQueue.p=SQueue.front;SQueue.p!=NULL;SQueue.p=SQueue.p->next)
		{
			if(SQueue.p==SQueue.front)
				SQueue.p=SQueue.p->next;

			if(SQueue.p==NULL)
				break;

			if(j==8)
			{
				if(SQueue.p==NULL)
				{
					printf("     ");
					textcolor(RED);
					cprintf("|");
					textcolor(WHITE);
					j++;
					printf("     ");
					textcolor(RED);
					cprintf("|");
					textcolor(WHITE);
					j++;
					break;
				}
				else
				{
					if(SQueue.p->B.tr<10)
						printf("  %d  ",SQueue.p->B.tr);
					else
						printf(" %d ",SQueue.p->B.tr);
					textcolor(RED);
					cprintf("|");
					textcolor(WHITE);
					j++;
					SQueue.p=SQueue.p->next;
					if(SQueue.p==NULL)
					{
						printf("     ");
						textcolor(RED);
						cprintf("|");
						textcolor(WHITE);
						j++;
						break;
					}
					else
					{
						if(SQueue.p->B.tr<10)
							printf("  %d  ",SQueue.p->B.tr);
						else
							printf(" %d ",SQueue.p->B.tr);
						textcolor(RED);
						cprintf("|");
						textcolor(WHITE);
						j++;
						break;
					}
				}
			}
			else
			{
				if(SQueue.p->B.tr<10)
					printf("  %d  |",SQueue.p->B.tr);
				else
					printf(" %d  |",SQueue.p->B.tr);

				j++;
			}
		}

	}

	while(j<SSQ)
	{
		if(j==SSQ-2)
		{
			printf("     ");
			textcolor(RED);
			cprintf("|");
			textcolor(WHITE);
			printf("     ");
			textcolor(RED);
			cprintf("|");
			textcolor(WHITE);
			break;
		}
		printf("     |");
		j++;
	}

	printf("\n\t\t ");

	j=1;
	textcolor(GREEN);
	cprintf(".....");
	textcolor(WHITE);
	printf(".");
	for(j=1;j<SSQ-1;j++)
	{
		printf("......");
	}
	textcolor(RED);
	cprintf(".....");
	textcolor(WHITE);
	printf("\n\t\t");

	j=0;
	printf("\nHit cout\t");

	j=0;
	if(SQueue.front==NULL)
	{
		textcolor(GREEN);
		cprintf("|");
		textcolor(WHITE);
		printf("     ");
		textcolor(GREEN);
		cprintf("|");
		textcolor(WHITE);
		for(j=1;j<SSQ-2;j++)
		{
			printf("     |");
		}
		printf("     ");
		textcolor(RED);
		cprintf("|");
		printf("     ");
		textcolor(RED);
		cprintf("|");
		textcolor(WHITE);
		j=SSQ;
	}
	else
	{
		j=0;
		textcolor(GREEN);
		cprintf("|");
		textcolor(WHITE);
		if(SQueue.front->B.hn<10)
		{
			printf("  %d  ",SQueue.front->B.hn);
			textcolor(GREEN);
			cprintf("|");
			textcolor(WHITE);
			j++;
		}
		else
		{
			printf(" %d  ",SQueue.front->B.hn);
			textcolor(GREEN);
			cprintf("|");
			textcolor(WHITE);
			j++;
		}

		for(SQueue.p=SQueue.front;SQueue.p!=NULL;SQueue.p=SQueue.p->next)
		{
			if(SQueue.p==SQueue.front)
				SQueue.p=SQueue.p->next;

			if(SQueue.p==NULL)
				break;

			if(j==8)
			{
				if(SQueue.p==NULL)
				{
					printf("     ");
					textcolor(RED);
					cprintf("|");
					textcolor(WHITE);
					j++;
					printf("     ");
					textcolor(RED);
					cprintf("|");
					textcolor(WHITE);
					j++;
					break;
				}
				else
				{
					if(SQueue.p->B.hn<10)
						printf("  %d  ",SQueue.p->B.hn);
					else
						printf(" %d ",SQueue.p->B.hn);
					textcolor(RED);
					cprintf("|");
					textcolor(WHITE);
					j++;
					SQueue.p=SQueue.p->next;
					if(SQueue.p==NULL)
					{
						printf("     ");
						textcolor(RED);
						cprintf("|");
						textcolor(WHITE);
						j++;
						break;
					}
					else
					{
						if(SQueue.p->B.hn<10)
							printf("  %d  ",SQueue.p->B.hn);
						else
							printf(" %d ",SQueue.p->B.hn);
						textcolor(RED);
						cprintf("|");
						textcolor(WHITE);
						j++;
						break;
					}
				}
			}
			else
			{
				if(SQueue.p->B.hn<10)
					printf("  %d  |",SQueue.p->B.hn);
				else
					printf(" %d  |",SQueue.p->B.hn);

				j++;
			}
		}

	}

	while(j<SSQ)
	{
		if(j==SSQ-2)
		{
			printf("     ");
			textcolor(RED);
			cprintf("|");
			textcolor(WHITE);
			printf("     ");
			textcolor(RED);
			cprintf("|");
			textcolor(WHITE);
			break;
		}
		printf("     |");
		j++;
	}

	printf("\n\t\t");

	j=1;
	printf(" ");
	textcolor(GREEN);
	cprintf("-----");
	textcolor(WHITE);
	for(j=1;j<SSQ-1;j++)
	{
		printf(" -----");
	}
	printf(" ");
	textcolor(RED);
	cprintf("-----");
	textcolor(WHITE);

	printf("\n\nGhost Queue\t    ");

	for(j=0;j<SGQ;j++)
	{
		printf(" ---");
	}
	printf("\n\t\t");

	textcolor(RED);
	cprintf("LRU");
	textcolor(WHITE);

	printf(" |");

	j=0;
	if(GQueue.front==NULL)
	{
		for(j=0;j<SGQ;j++)
		{
			printf("   |");
		}
	}
	else
	{
		for(GQueue.p=GQueue.front;GQueue.p!=NULL;GQueue.p=GQueue.p->next)
		{
			if(GQueue.p->B.val<10)
				printf(" %d |",GQueue.p->B.val);
			else
				printf("%d |",GQueue.p->B.val);
			j++;
			if(j>=SGQ)
				break;
		}
		while(j<SGQ)
		{
			printf("   |");
			j++;
		}
	}
	printf(" ");
	textcolor(GREEN);
	cprintf("MRU");
	textcolor(WHITE);
	printf("\n\t\t    ");
	for(j=0;j<SGQ;j++)
	{
		printf(" ---");
	}

	getch();
}

void main()
{
	block B[50];

	int i,num,time;

	clrscr();

	textcolor(WHITE);
	printf("Enter the number of Pages\t");
	scanf("%d",&num);
	printf("\n\nEnter the value of each page");
	printf("\n\nName\tValue\n");
	for(i=0;i<num;i++)
	{
		printf("B%d\t",i+1);
		B[i].getvalue();
	}

	time=1;
	for(i=0;i<num;i++)
	{
		GQBAssg(B[i],time);
		show(num,B,time,i);
		time++;

	}
	delete &SQueue;
	delete &GQueue;
	getch();
}
