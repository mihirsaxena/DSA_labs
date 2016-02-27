#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
using namespace std;

struct node{
	int data;
	int node_no;				
	char child_type;			 // child_type is either left child or right child
	struct node *parent;      
	struct node *left;
	int level;
	struct node *right;	
	struct node* next;
};

void addEnd(struct node **head,struct node *temp);
struct node *removeFront(struct node** head);
struct node *tree_construct(int n,struct node **head);
void binary_number(int a[],int n,int size);
int evaluate_leafnode(int x,char b[],int size_of_input ,struct node **head,int offset);
void load_leafvalues(int x,char b[],int size_of_input,struct node *queue_head,int offset);
struct node *egt(struct node *q,char b[],int size,int x,int offset);
void preorder(struct node *root);

int main(){
	struct node *root=(struct node*)malloc(sizeof(struct node));
	root->node_no=1;
	root->next=NULL;
	
	char exp[1000];
	scanf(" %s",exp);
	
	int x=0;            //x is the number of alphabets in the expression
	for(int i=0;i<strlen(exp);i++)
	{
	if(exp[i]>=65&&exp[i]<=90)
	{
		x++;
	}
	}
	
	struct node *ab=tree_construct(pow(2,x+1)-1,&root);  //a-> queue
	int offset=ab->node_no;
	struct node *temp_queue=ab;
	

struct node *root1=egt(ab,exp,strlen(exp), x,offset);
preorder(root1);
return 0;
}

void addEnd(struct node **head,struct node *temp){
	if (*head== NULL) {
		
	struct node *x=temp;	
	//x->next=NULL;
	*head=x;
		
    (*head)->next=NULL;
  //  cout<<temp->node_no<<" ";
    }
    else
	{
	
	struct node *temp1=*head;
	while(temp1->next!=NULL){
		temp1=temp1->next;
	}
	(temp1->next)=(temp);
	//cout<<temp->node_no<<" ";
	temp->next=NULL;
	}
}
struct node *removeFront(struct node** head){
	if(*head==NULL)
	return NULL;
	struct node *temp=*head;
	*head=(*head)->next;
	return temp;
	//free(temp);
}

struct node* tree_construct(int n,struct node **head){		//n= no of nodes to be created in the tree. n=h^2+h^1+h^0 if 2 is the no of variables
	int ctr=1,count=1;
	struct node *temp=*head;
//	struct node *queue_head=(struct node *)malloc(sizeof(struct node));
	struct node *queue_head=NULL;
	//queue_head->next=NULL;
	struct node *tempz=NULL;
	temp->level=count;
	temp->parent=NULL;
	count++;
//	temp->next=NULL;
	addEnd(&queue_head,temp);
	
	while(ctr<=n-1){
		tempz=removeFront(&queue_head);
		struct node* temp1=(struct node *)malloc(sizeof(struct node));
		temp1->node_no=++ctr;
		temp1->next=NULL;
		
		temp1->level=count;
		
		tempz->left=temp1;
		temp1->parent=tempz;
		temp1->child_type='l';
		addEnd(&queue_head,temp1);
		
		struct node* temp2=(struct node *)malloc(sizeof(struct node));
		temp2->node_no=++ctr;
		temp2->next=NULL;
		temp2->child_type='r';
		temp2->level=count;
		
		tempz->right=temp2;
		temp2->parent=tempz;
		
		addEnd(&queue_head,temp2);
			
		count++;	
	}	
	
	return queue_head;	
	
}

int evaluate_leafnode(int x,char b[],int size_of_input ,struct node **head,int offset){			//head refers to the head of the queue
			struct node *queue_head=*head;
			
			
			int a[x];
			int ctr=1;
  //x is number of variables
				binary_number(a,(queue_head->node_no-offset),x);
				
				int i=0,j=0;
				while(i<size_of_input){
				if(b[i]>=65&&b[i]<=90){
					
					if(a[j]==1)
					{
						while(b[i]!=')')
						{
						i++;
						if(b[i]>=65&&b[i]<=90)
						j++;
						                    	
					
						}
					}
					
					j++;
				}
			else if(b[i]=='-'){
					i++;
					if(a[j]==0)
					{
					while(b[i]!=')')
						{
							i++;
						if(b[i]>=65&&b[i]<=90)
						j++;
						}	
					}
					
					j++;
				}	
			else if(b[i]==')'){
				return 0;				
				
			}
				
				i++;
			}				
			return 1;
}

void binary_number(int a[],int n,int size){   //size of the array is the number of variables
	//to convert number n to binary
	int i;
	for(int i=0;i<size;i++){			//instead of writing while(n!=0) because size of array is fixed for all cases
		a[size-1-i]=n%2;
		
		n/=2;
	}
	}


struct node *egt(struct node *q,char b[],int size,int x,int offset){
	
	int res=0;int node_no=0;
	struct node *root=NULL;
	
	for(int i=1;i<=pow(2,x);i++)
	{
		struct node *k=removeFront(&q);
		res=evaluate_leafnode(x,b,strlen(b),&k,offset);
		k->data=res;
		k->left=NULL;
		k->right=NULL;
		if(k->child_type=='r')
		{
		addEnd(&q,k->parent);
		
		}
		
	}

	int level=x-1;
	while(level>=0)
	{
		for(int i=1;i<=pow(2,level);i++)
		{
			node *k=removeFront(&q);
	
		if(level%2==1)
		{
			k->data=(k->left->data)*(k->right->data);
		}
		else
		{
			
			k->data=k->left->data+k->right->data;
			if(k->data==2)k->data=1;
		}
		if(k->parent==NULL)root=k;
	    if(k->child_type=='r')
		addEnd(&q,k->parent);
		
		}
		level--;
	}
	return root;
	
	
}
void preorder(struct node *root)
{
	if(root==NULL)return;
	printf("%d",root->data);
	preorder(root->left);
	preorder(root->right);
	
	
}

