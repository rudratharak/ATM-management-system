#include<stdio.h>
#include<string.h>

//structure for atm storage
typedef struct account{
	char name[100];
	int pin;
	float balance;
	long int account_number;
}account;

//for genrating account number
struct account acc[40];
int i=0,count=0;
long int next_num=1003250;

//for adding account 
void add(void)
{
	printf("Enter your name:"),scanf("%s",acc[i].name);
	printf("Enter a pin for %s's account:",acc[i].name),scanf("%d",&acc[i].pin);
	printf("Enter amount intial amount for deposit:"),scanf(" %f",&acc[i].balance);
	printf("Assigned account number %ld ,",next_num);
	printf("account sucessfully created\n");
	next_num+=100;
	i++;
	count++;
	
	//file
	FILE *fp=fopen("account","w");
	if(fp==NULL)
	{
		printf("can't open file\n");
		return;
	}
	fwrite(acc,sizeof(acc),1,fp);
	fclose(fp);
}

//for checking account number
int account_num(void)
{
	long int num;
	int i;
	printf("Enter the account number:"),scanf("%ld",&num);
	for(i=0;i<count;i++)
	{
		if(acc[i].account_number==num)
		return i;
	}
	return -9;
	
	//file
	FILE *fp=fopen("account","r");
	if(fp==NULL)
	{
		printf("can't open file\n");
		return;
	}
	fread(&acc,sizeof(acc),1,fp);
	//fclose(fp);
}

//checking balance
void check(void)
{
	int j;
	j=account_num();
	printf("Name:%s\naccount number:%ld\nbalance:%0.2f",acc[j].name,acc[j].account_number,acc[j].balance);
}

//with draw
void with_draw(void)
{
	int j;
	float num;
	j=account_num();
	printf("Amount for with draw:"),scanf("%f",&num);
	if(num>acc[j].balance)
	{
		printf("insuffent funds");
		return;
	}
	acc[j].balance-=num;
	
	//file
	FILE *fp=fopen("account","w");
	if(fp==NULL)
	{
		printf("can't open file\n");
		return;
	}
	fwrite(acc,sizeof(acc),1,fp);
	fclose(fp);
	
	printf("Name:%s\naccount number:%ld\nbalance:%0.2f",acc[j].name,acc[j].account_number,acc[j].balance);
}

//deposit
void deposit(void)
{
	int j;
	float num;
	j=account_num();
	printf("Amount for deposit:"),scanf("%f",&num);
	if(num>acc[j].balance)
	return;
	acc[j].balance+=num;
	
	//file
	FILE *fp=fopen("account","w");
	if(fp==NULL)
	{
		printf("can't open file\n");
		return;
	}
	fwrite(acc,sizeof(acc),1,fp);
	fclose(fp);
	
	printf("Name:%s\naccount number:%ld\nbalance:%0.2f",acc[j].name,acc[j].account_number,acc[j].balance);
}

//sub menu for banking
void banking(void)
{
	int m;
	printf("1.check balance\n2.deposit\n3.with draw\nchose from service:"),scanf("%d",&m);
	switch(m)
	{
		case 1:check();break;
		case 2:deposit();break;
		case 3:with_draw();break;
		default:printf("invaid input tryagain");break;
	}
}

main()
{
	int n,p;
	while(1)
	{
		printf("1.Banking for already existing account\n2.Creating new account\n3.exit\n");
		printf("chose the service:"),scanf("%d",&n);
		//for menu
		switch(n)
		{
			case 1:banking();break;//gives another menu
			case 2:add();break;
			case 3:printf("exit......");return;break;
			default:printf("invaid input tryagain");break;
		}
	}
}
