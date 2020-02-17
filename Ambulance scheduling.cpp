#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

class Point
{
public:
	int x;
	int y;
};

class Ambulance
{
public:
	int availability;
	Ambulance()
	{
		availability=1;
	}
};

class node
{
public:
   int data;
   int priority;
   float tot_p;
   struct node *next;
};
node *front = NULL;

class Priority_Queue
{
public:
void insertPQ(int data, int priority)
{
   priority=priority*data;	/// for calculating distance from hospital to a destination, assume distance=priority*dis;
   node *temp, *ptr;
   temp = new node;
   temp->data = data;
   temp->priority = priority;
   cout<<"Total priority : "<<temp->priority<<endl;
   if (front == NULL || priority < front->priority)
   {
      temp->next = front;
      front = temp;
   
   }
   else
   {
      ptr = front;
	  while (ptr->next != NULL && ptr->next->tot_p <= priority)
      ptr=ptr->next;
      temp->next = ptr->next;
      ptr->next = temp;
   }
}
void deletePQ()
{
   node *temp;
   
   if(front == NULL)
   cout<<"Priority Queue empty\n";
   
   else
   {
      temp = front;
	  if(temp->next!=NULL)
	  {
		  while(temp->next->next != NULL)
		  {
			 temp = temp->next;
		  }
	  }
	  if(temp->next!=NULL)
	  {
		  cout<<"Deleted item is: "<<temp->next->data<<endl;
		  temp->next= NULL;
	  }
	  else
	  {
		  cout<<"Deleted item is: "<<temp->data<<endl;
		  temp= NULL;
	  }
   }
}
void displayPQ()
{
   node *ptr;
   ptr = front;
   
   if (front == NULL)
   cout<<"Priority Queue is empty\n";
   
   else
   { 
      cout<<"Queue elements in decreasing priority are :\n";
      while(ptr != NULL)
	  {
         cout<<ptr->data<<" ";
         ptr = ptr->next;
      }
      cout<<endl;
   }
}
};
int main()
{
	  Ambulance A[3];
	  Priority_Queue P[3];
	  node *n=new node;
	  float dataa; int priority;
	  for(int i=0; i<3; i++)
	  {
		  cout<<"Enter the data for the "<<i+1<<" th"<<" patient"<<endl;
		  cin>>dataa;
		  cout<<"Enter the prioirty for the "<<i+1<<" th"<<" patient"<<endl;
		  cin>>priority;
		  P[i].insertPQ(dataa,priority);

	 }
	  int noa=1;
	  P[0].displayPQ();
	  for(int i=0; i<3; i++)
	  {
		if(noa<=3)
		{
			A[noa].availability=1;
			cout<<"Patient "<<i+1<<" has been assigned ambulance no : "<<noa<<endl;
			noa++;
			P[0].deletePQ();
		}
	  }
	  P[0].displayPQ();
	  system("pause");   
      return 0;
}