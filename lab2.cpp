#include<iostream>
#include<stdio.h>
#include<stack>
#include<string.h>
#include<stdlib.h>
using namespace std;
void postfix(char a[],char b[],int );
int priority(char );
void operation(char x);
void convert_to_machinecode(char* b);

struct node{
	char data;
	struct node*next;
};
void addFront(struct node **head,char data);
void removeFront(struct node **head);
		
int main()
{
char a[1000],b[1000]; 
int i;
scanf(" %s",&a);
postfix(a,b,strlen(a));
cout<<endl;
convert_to_machinecode(b);

	
	return 0;
}

	void addFront(struct node **head,char data){
	
	struct node *temp=(struct node *)malloc(sizeof(struct node));
	temp->data=data;
	temp->next=(*head);
	*head=temp;
		
	}
	void removeFront(struct node **head){
	struct node *temp=*head;
	*head=temp->next;
	free(temp);
	}	
	char top(struct node *x){
	return x->data;
	}
	void postfix(char a[],char b[],int size)	
	{	
	int i;
	int ctr=0;
	char temp;
	struct node *stack=NULL;
	

for(i=0;i<size;i++)
{
if(a[i]=='('||a[i]=='+'||a[i]=='-'||a[i]=='/'||a[i]=='*'||a[i]=='^')
{
	while(1)
	{
		if(stack==NULL||top(stack)=='('||(priority(top(stack))-priority(a[i]))<0)
		{
			break;
		}
		
		cout<<top(stack);
		b[ctr]=top(stack);
		ctr++;
		removeFront(&stack);
	}
	
	addFront(&stack,a[i]);

}
else if(a[i]==')')
{
	while(1){
	temp=top(stack);
	if(temp=='('){
		
	removeFront(&stack);
	break;
	}
	
	cout<<top(stack);
	b[ctr]=top(stack);
	ctr++;
		
	removeFront(&stack);
}
}
else
{
cout<<a[i];
b[ctr]=a[i];
ctr++;
}
}
while(stack)
{
	cout<<top(stack);
	b[ctr]=top(stack);
	ctr++;
	
	removeFront(&stack);
}		
}
int priority(char x){
	if(x=='+'||x=='-')
	return 1;
	else if(x=='*'||x=='/')
	return 2;
	else if(x=='^')
	return 3;
	else if(x=='(')
	return 4;
	else
	return -1;
} 

void convert_to_machinecode(char* b){
	int i=0; //for looping
	int j=1; //for temp
	struct node *stack;
	char symb,op1,op2;
	while (b[i]!='\0'){
		symb=b[i];
		if ((b[i]>=65 && b[i]<=90) || (b[i]>=97 && b[i]<=122)){
			addFront(&stack,b[i]);
		}
		else {
			op2=top(stack);
			removeFront(&stack);
			op1=top(stack);
			removeFront(&stack);
			
			if ((op1>=65 && op1<=90) || (op1>=97 && op1<=122))
				printf("LD %c\n",op1);
			else
			{
				printf("LD TEMP%d\n",op1);
	                }
			switch(symb){
				case '*': printf("ML "); break;
				case '+': printf("AD "); break;
				case '-': printf("SB "); break;
				case '/': printf("DV "); break;
			}

			if ((op2>=65 && op2<=90) || (op2>=97 && op2<=122))
				printf("%c\n",op2);
			else
			{
				printf("TEMP%d\n",op2);
	                }
			printf("ST TEMP%d\n",j);
			
			addFront(&stack,j++);
			
		}
		i++;
	}
}
void operation(char x){
	if(x=='+')
	cout<<"AD";
	
	else if(x=='*')
	cout<<"ML";
	
	else if(x=='-')
	cout<<"ST";
	
	else 
	cout<<"DV";
	
} 

