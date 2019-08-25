#include "mtcs.h"


//------------------------------------------------------------------
void creat(tNode* tree);
void display(listNode *start1);
void insertNode(tNode *temp);
void deleteNode(listNode *dnode,listNode **list);
bool checkShared(struct listNode *a);
void sortList(listNode **head1);
void schedule(int mixers);
void savePara(int mixers);
int calWaste();
void result();
void bubbleSort(listNode **list);
void swap(struct listNode *a, struct listNode *b);
//------------------------------------------------------------------
void creat(tNode* tree)
{
	if(tree!=NULL)
	 {
           creat(tree->left);
	   creat(tree->right);
	   struct listNode *new_node;
           new_node=(struct listNode *)malloc(sizeof(struct listNode));
	   
	  if(tree->left==NULL&&tree->right==NULL&&tree->nodeID%2==0)
	  {
		tree->time=0;
		tree->mixer=0;
	  }
	 
	  new_node->tnode=tree;
	  new_node->next=NULL;
	
	  if(start==NULL)
	  {
		  start=new_node;
		  current=new_node;
	  }
	  
	  else
	  {
		  current->next=new_node;
		  current=new_node;
	  }

	}
     else return;   
	
}

//------------------------------------------------------------------
void display(listNode *start1)
{
	struct listNode *new_node;
	 printf("The Linked List :\n");
	 new_node=start1;
	int i=0;
	 while(new_node!=NULL&&i++<30)
	   {
		printf("(%d)--->",new_node->tnode->nodeID);
		new_node=new_node->next;
	   }
	  printf("NULL\n");
	return;

}

//------------------------------------------------------------------


void schedule(int mixers)
{
	#ifdef SCH
	printf("\nIn scheduling : %d\n\n",mixers);
	display(start);
	#endif
	bubbleSort(&start);
	#ifdef SCH
	printf("after sorting\n");
	display(start);	
	#endif
	
	
	int time=1,mix=mixers;
	int i=0,c=0;
 	while(start!=NULL)
	{
		struct listNode *temp,*tnxt;
	 	temp=start;
		tnxt=start;//next of temp
		
		//#ifdef SCH
		//printf("first loop in scheduling : ");
		//printf("%d--->\n",temp->tnode->nodeID);
                //printf("\n....................\n");
		//display(head);
		//display(start);	
		//#endif*/

		while(temp) 
		{
			//#ifdef SCH
		   	//printf("second loop in scheduling %d: \n",temp->tnode->nodeID);
		   	//#endif
		
			if((temp->tnode->nodeID)%2!=1&&temp->tnode->time==-1&&temp->tnode->left->time>=0&&temp->tnode->right->time>=0)		    
			{
		   	   // #ifdef SCH
			   // printf("if: \n");
			    //#endif

			    insertNode(temp->tnode);//	
			    tnxt=temp->next;
			    deleteNode(temp,&start); //
	                    temp=tnxt;
			                                  
		  	}
		
			else if(temp->tnode->time>=0)
			    {
				//#ifdef SCH
				//printf("else if : \n");
				//#endif
  
                                tnxt=temp->next;				
				deleteNode(temp,&start);//
				temp=tnxt;
			    }
			else temp=temp->next;
			
			
			
	      	  }
		 
	        mix=mixers;
	       //sortList();//sws
		#ifdef SCH
		printf("\nhead before modify:\n");		
		display(head);
		//display(start);	 	
		#endif
		bubbleSort(&head);
		
		
		#ifdef SCH
		printf("\nhead after modify:\n");		
		display(head);
		//display(start);	 	
		#endif
		struct listNode *temp2,*t2nxt;
		temp2=head;
		
		for(int i=0;i<mixers&&temp2!=NULL;i++)
		{
			temp2->tnode->mixer=i+1;
			temp2->tnode->time=time;
	
			#ifdef SCH
			printf("temt2 %d (%d)\n",temp2->tnode->nodeID,temp2->tnode->time);
			#endif
			 
			if(temp2->tnode->pairID!=-1)
			{
				int id=temp2->tnode->pairID;
				 struct listNode *cur=start;
				 while(cur->tnode->nodeID!=id && cur!=NULL)
					cur=cur->next;
				cur->tnode->time=time;
				cur->tnode->mixer=0;
				#ifdef SCH
				printf("paired %d (%d)\n",cur->tnode->nodeID,cur->tnode->time);
				#endif			
				deleteNode(cur,&start);
			}
			t2nxt=temp2->next;		
			deleteNode(temp2,&head);
			temp2=t2nxt;
	
			//display(start);
		}
		// printf("\n\n");
	 

		time++;

    	}
	
	#ifdef SCH
	printf("\n\n out of loop\n");
	#endif
	while(head!=NULL)
	{
		struct listNode *temp2,*t2nxt;
		temp2=head;
		
			for(int i=0;i<mixers&&temp2!=NULL;i++)
			{
				temp2->tnode->mixer=i+1;
				temp2->tnode->time=time;
				#ifdef SCH
				printf("temt2 %d (%d)\n",temp2->tnode->nodeID,temp2->tnode->time);
				#endif
				if(temp2->tnode->pairID!=-1)
				{
					int id=temp2->tnode->pairID;
					 struct listNode *cur=start;
					 while(cur->tnode->nodeID!=id && cur!=NULL)
						cur=cur->next;
					cur->tnode->time=time;
					cur->tnode->mixer=0;
					#ifdef SCH
					printf("paired %d (%d)\n",cur->tnode->nodeID,cur->tnode->time);
					#endif
					deleteNode(cur,&start);
				}

				t2nxt=temp2->next;		
				deleteNode(temp2,&head);
				temp2=t2nxt;
				head=temp2;
				//display(start);
			}
			#ifdef SCH
			printf("\nhead and start list are:\n");		
			display(head);
			//display(start);
			#endif
	}

result();
}

//---------------------------------------------------------
void result()
{
	struct listNode *cur=root;
	// printf("%s ",filename);
	while(cur!=NULL)
	{
	     printf("%d ",cur->tnode->time);
	     cur=cur->next;
	}
	printf("\n");
        //printf("NULL\n");
}

//-----------------------------------------------------------

void deleteNode(listNode *dnode,listNode **list)
  {
    // Store head node
    struct listNode* temp = *list, *prev;
 
   //#ifdef SCH
   // printf("delete node %d from %d: \n",dnode->tnode->nodeID,(*list)->tnode->nodeID);
    //#endif

  // If head node itself holds the key to be deleted
    if (temp != NULL && temp== dnode)
    {
			
        *list = temp->next;   // Changed head
        free(temp);               // free old head
	return;
    }
 
    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp!= dnode)
    {
        prev = temp;
        temp = temp->next;
    }
 
    // If key was not present in linked list
    if (temp == NULL) return;
 
    // Unlink the node from linked list
    prev->next = temp->next;
 	free(temp); 
  }

//------------------------------------------

void insertNode(tNode *temp)
 {
    struct listNode *last;
    last=(struct listNode *)malloc(sizeof(struct listNode));

    if(last == NULL)
  	  printf("Unable to allocate memory.");
    

    else
  	{
	    	last->next=NULL;
	    	last->tnode=temp;

	    	   // If the linked list is empty then set head = last
		    if (head == NULL) 
		    {
			head = last;
		    } 

		    else 
                    {
			// Creates a temp node and sets it to head
			struct listNode *temp =head;

			

			// Uses temp to find the last node
			while (temp->next != NULL) {
			    temp = temp->next;
			}

			// Appends the last node with last
			temp->next = last;
		    }

        }
	
 }

//-----------------------------------------

void savePara(int mixers)
{
	int tms=0,waste=0,tlb=0,mlb=0,ncs=0,in=0,w=0;
	
    /*	#ifdef SCH
	struct listNode *cur=start;
	printf("List is: \n");
	while(cur!=NULL)
	{
    	     printf("%d-->",cur->tnode->nodeID);
	    cur=cur->next;
	}
        printf("NULL\n");
        #endif
*/
	struct listNode *temp=start;
	mlb=mixers;
	tlb=nB;
	while(temp!=NULL)
	{
		if(temp->tnode->leaf!=1)
			tms++;
		if(temp->tnode->nodeID%2==1)
			ncs++;
		if(temp->tnode->leaf==1&&temp->tnode->nodeID%2==0)
		{ 
		 //printf("%d--> ",temp->tnode->nodeID);		
		 w++;
		}
		
		temp=temp->next;  			
	}
	//printf("\nwaste is : %d\n",w);
	waste=w-nrat;
	//printf("tms,w,tlb,mlb,ncs\n");
	//printf("%s %d %d %d %d %d \n",filename,tms,waste,tlb,mlb,ncs);
	printf("%d %d %d %d %d \n",tms,waste,tlb,mlb,ncs);
	//printf("")
   


}

//---------------------------------------- 

int calWaste()
{
	struct listNode *temp=head;
	int w=0;
	while(temp!=NULL)
	{
		
		temp=temp->next;  			
	}

}

//------------------------------------------------------------------------
 
bool checkShared(struct listNode *a)
{
    if(a->tnode->pairID!=-1)
    return true;
    else
    return false;
}
//-----------------------------------------------------------------------

void bubbleSort(struct listNode **list)
{
    int swapped, i;
    struct listNode *ptr1;
    struct listNode *lptr = NULL;
 	
    /* Checking for empty list */
    if (ptr1 == NULL)
        return;
 
    do
    {
        swapped = 0;
        ptr1 = *list;
 
        while (ptr1->next != lptr)
        {
            if (ptr1->tnode->level > ptr1->next->tnode->level)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}
 //---------------------------------------------------------------------------------

/* function to swap data of two nodes a and b*/
void swap(struct listNode *a, struct listNode *b)
{
    tNode *temp = a->tnode;
    a->tnode = b->tnode;
    b->tnode = temp;
}

