#include<iostream>
#include<vector>
#include<cstring>
#include<cfloat>
#include<climits>
#include<set>
#include<cmath>
#include<map>
#include<cstdio>
#include<string>
#include<fstream>

typedef long long ll;

using namespace std;
int count_id=0;
struct tree{
 int node_id; 
 int parent_id; 
 double val;
 struct tree *pt;
 vector<pair<struct tree *,int> > adjacent;
 //struct tree *parent;
};
void rec(struct tree* root, ofstream &myfile){
  if(root==NULL){
    return;
  }
  myfile<<root->node_id<<" [label=\""<<root->val<<"\"];\n";
  int n = root->adjacent.size();
  for(int i=0;i<n;i++){
    rec(root->adjacent[i].first,myfile);
  }
  for(int i=0;i<n;i++){
    myfile<<root->adjacent[i].first->node_id<<" -> "<<root->node_id<<" [label=\""<<root->adjacent[i].second<<"\"]; \n";
  }
  
}

void tree_to_dot(vector<struct tree*> &t){
  ofstream myfile;
  myfile.open("output/ee.dot");
  myfile<<"digraph groma{\nrankdir=BT;\n";
  for(vector<struct tree*>::iterator it=t.begin();it!=t.end();it++){
        struct tree* tr=*it;
        rec(tr,myfile);
  }
  myfile<<"}";
  myfile.close();
  
}
int decimalToBasek(int decimalNumber,int k)
{
    int rem, i = 1, Number = 0;
    while (decimalNumber != 0)
    {
        rem = decimalNumber % k;
        decimalNumber /= k;
        Number += rem * i;
        i *= 10;
    }
    return Number;
}


double mytarget;  

//int count1=0;     //for automation
int segment,accuracy;
map<int,struct tree *> node_number;
struct tree *  tree_generation(){
  vector<int> arr;
  double target,acv,d,rcv;
  int x=0; 
  //d=0.0001;
  //cin>>target;
  target=mytarget;
  d=pow((float)10,-(accuracy+1));
  //cout<<"\nd="<<d;
  ll var=decimalToBasek(target,segment);  //change accuracy value for the test cases
  //cout<<"\nvar="<<var; 

  struct tree *parent=NULL, *root;
  //struct tree *t = (struct tree*)malloc(sizeof(struct tree));
  struct tree *t = new tree;
  t->node_id=count_id++;
  t->parent_id=-1;
  t->pt=NULL;
  node_number[t->node_id]=t;
 // cout<<"\n Parent node is created";
 
  target=(double)var/pow(10,accuracy);
  //target=(float)var/1000;
  //cout<<"\ntarget="<<target;
  t->val=target;
  //cout<<"\ntval="<<t->val<<" var"<<var;
  root=t;
  parent = t;
  rcv =(double)var/pow(10,accuracy);
  acv=0.0;
  
  var=target * 1e16;
  if(var%10==9)
    var+=1;
  //cout<<var<<endl;

  while(var){
     int k=var%10;
     arr.insert(arr.begin(),k);
     var=var/10;
  }
  while(arr.size()!=16){
    arr.insert(arr.begin(),0);
  }
  arr.push_back(0);//for edge case resolution
  int i=0; //for pointing into the array

  
 // cout<<"\n Everything is initialized and array size="<<arr.size();
  while(abs(target-acv) > d){
      int y=0, flag=1;
     // cout<<"\n1st part";
      if(arr[i] != 0){
        //struct tree *temp = (struct tree*)malloc(sizeof(struct tree));
        struct tree *temp=new tree;
        temp->node_id=count_id++;
        temp->parent_id=parent->node_id;
        temp->pt=parent;
        temp->val = 1;
        node_number[temp->node_id]=temp;
       // cout<<"\n 1st node created";
        parent->adjacent.push_back(make_pair(temp,arr[i]));
        y= arr[i] ;
        if(arr[i]==segment-1)
          flag=0;
        acv+=arr[i] * pow(10,-x-1);
        arr[i]=0;
        rcv=0.0;
        int k=1;
        for(int j=i;j<arr.size();j++){
            rcv=rcv+(double)arr[j]*pow(10,-k);
            k++;
        }
      //  cout<<"rcv="<<rcv;
        //rcv=(rcv-(int)(rcv*10))* 0.1;
      }
      //cout<<"\nSecond part";
      if(flag){
        
        if(arr[i+1]!=0){
          //struct tree *temp = (struct tree*)malloc(sizeof(struct tree));
          struct tree *temp=new tree;
          temp->node_id=count_id++;
          temp->parent_id=parent->node_id;
          temp->pt=parent;
          temp->val=arr[i+1] * 0.1;
          node_number[temp->node_id]=temp;
          //cout<<"\nSecond node created with val "<<temp->val;
          //struct tree *child1 = (struct tree*)malloc(sizeof(struct tree));
          struct tree *child1 = new tree;
          child1->node_id=count_id++;
          child1->parent_id=temp->node_id;
          child1->pt=temp;
          child1->val=1;
          node_number[child1->node_id]=child1;
          temp->adjacent.push_back(make_pair(child1,(int)(temp->val*10)));
          //struct tree *child2 = (struct tree*)malloc(sizeof(struct tree));
          struct tree *child2 = new tree;
          child2->node_id=count_id++;
          child2->parent_id=temp->node_id;
          child2->pt=temp;
          child2->val=0;
          node_number[child2->node_id]=child2;
          temp->adjacent.push_back(make_pair(child2,segment-(int)(temp->val*10)));
          parent->adjacent.push_back(make_pair(temp,1));
          acv+=double(arr[i+1]) * pow(10,-x-2);
          arr[i+1]=0;
          int k=1;
          rcv=0.0;
          for(int j=i;j<arr.size();j++){
            rcv=rcv+(double)arr[j]*pow(10,-k);
            k++;
          }
          y+=1;
        }
      }
     // cout<<"\nThird Part";
      if(abs(target-acv) > d){
      	// struct tree *temp1 = (struct tree*)malloc(sizeof(struct tree));
         struct tree *temp1 = new tree;
         temp1->node_id=count_id++;
         temp1->parent_id=parent->node_id;
         temp1->pt=parent;
         temp1->val=rcv*10;
         node_number[temp1->node_id]=temp1;
         parent->adjacent.push_back(make_pair(temp1,1));
        // cout<<"\n Third node created and val="<<temp1->val;
         y+=1;
         if((segment-y) != 0){
             //struct tree *temp = (struct tree*)malloc(sizeof(struct tree));
             struct tree *temp = new tree;
             temp->node_id=count_id++;
             temp->parent_id=parent->node_id;
             temp->pt=parent;
             temp->val=0;
             node_number[temp->node_id]=temp;
             //cout<<"\n Node with 0 cv created.";
             parent->adjacent.push_back(make_pair(temp,segment-y));
         }
         parent = temp1;
      }
      else{
      	if((segment-y) != 0){
          struct tree *temp = (struct tree*)malloc(sizeof(struct tree));
          temp->node_id=count_id++;
          temp->parent_id=parent->node_id;
          temp->pt=parent;
          temp->val=0;
          node_number[temp->node_id]=temp;
          //cout<<"\n Node with 0 cv created.";
          parent->adjacent.push_back(make_pair(temp,segment-y));
        }
        break;
      }
      
      rcv=rcv*10;
      i++;
      x++;
  }
  //cout<<"\nACV="<<acv;
  //cout<<"Number of steps=";
  return root;
}

//t is a vector used to store trees nodes
map<int,int> counter;
map<int,int> node_shared;

map<int,int> shared;  //first is shared node id and second is shared node with

int i=0;
int sharing_util(struct tree *t){
   
   //cout<<"\n Call="<<++i;
   vector<pair<struct tree *,int> >::iterator it=t->adjacent.begin();
   //cout<<"\nStarted for loop";
   for(;it!=t->adjacent.end();it++){
      pair<struct tree *,int> temp=*it;
      struct tree *t1=temp.first;
      //cout<<"\n"<<t1->val;
      if(counter.find(t1->val*1e8)!=counter.end()){
              if(counter[t1->val*1e8]%segment!=0){
                         t1->adjacent.clear(); 
                         shared[t1->node_id]=node_shared[t1->val*1e8];
                        


              }        //checking node node need to be created
              else{
                  //nothing
                  node_shared[t1->val*1e8]=t1->node_id;       
              }
               counter[t1->val*1e8]++;
             
             // cout<<"\nSharing node for "<<t1->val<<" "<<counter[t1->val*10e6];
             // t1->adjacent.clear();
         }
         else{
            //  cout<<"\n Inside else part";
              
              
             if(!(t1->val==1.0 || t1->val==0.0)){
                     counter[t1->val*1e8]++;
                     node_shared[t1->val*1e8]=t1->node_id;
                     //cout<<"\nSharing util called "<<counter[t1->val*10e9];
                     sharing_util(t1);     
              }         

         }

   }
   //cout<<"\nExited for loop";
   //cout<<"\n Call="<<--i;
   return 0;

}
void sharing(vector<struct tree*> &t){
      /*for(map<int,int>::iterator it=counter.begin();it!=counter.end();){

            //cout<<"\nSharing node for "<<it->first/1e6<<" "<<it->second;
             it=counter.erase(it);
       }*/

     
     

     for(vector<struct tree*>::iterator it=t.begin();it!=t.end();it++){
         struct tree *t1=*it; 
       //  map<int,int>::iterator m;
         //cout<<"\nInside sharing";
        /* if(counter.find(t1->val*1e6)!=counter.end()){
            if(counter[t1->val*1e6]%segment!=0)
                         t1->adjacent.clear();         //checking node node need to be created
           counter[t1->val*1e6]++;
         }
         else
          sharing_util(t1);*/

         sharing_util(t1);


         //cout<<"\nExited sharing util";

     }  
    // cout<<"\nSize of counter="<<counter.size();
     for(map<int,int>::iterator it=counter.begin();it!=counter.end();){
        if(it->second==1)
          it=counter.erase(it);
        else
          it++;

     }

     for(map<int,int>::iterator it=counter.begin();it!=counter.end();it++){

           //  cout<<"\nSharing node for "<<it->first<<" "<<it->second;
     }
     //counter.erase(counter.find(1*1e9));
     //counter.erase(counter.find(0*1e9));


}


int tms=0;
double waste=-1.0, reactant=0.0, buffer=0.0;   //taget solution produced is not a waste
void operations(struct tree *root){
  
  tms++;
  //cout<<"\ntms increased and node val="<<root->val;
    for(int i=0;i<root->adjacent.size();i++){
      struct tree *node=root->adjacent[i].first;
      if(node->val==1.0){
        reactant+=(float)(root->adjacent[i].second);
        waste+=(float)(root->adjacent[i].second);
        //cout<<"\nLeaf node with cv 1";
      }
      else if(node->val==0.0){
        buffer+=(float)(root->adjacent[i].second);
       // cout<<"\nBuffer="<<buffer<<" Segment="<<root->adjacent[i].second;
        waste+=(float)(root->adjacent[i].second);
       // cout<<"\nLeaf node with cv 0";
      }
      else if(counter.find(node->val*1e8)!=counter.end()){
           
           if(node->adjacent.size()!=0){
               operations(node);
              // cout<<"Shared Node found1"<<endl;
           }
           else
             waste-=1;
           //cout<<"Shared Node found "<<node->val<<endl;
          //do nothing
      }
      else{
         //cout<<tms<<" "<<waste<<" "<<reactant;
         //cout<<"\nRecursive calls and val="<<node->val;
        if(node->adjacent.size()!=0)
           operations(node);
      }
    }

}

//Analyzing the tree generated
int tms1=0,total_tms=0;
float waste1=0.0,reactant1=0.0,buffer1=0.0,total_waste=0.0,total_reactant=0.0,total_buffer=0.0;
void analysis(vector<struct tree*> &t){
   //cout<<"\nSize of counter="<<counter.size();
   

   tms1=0;
   waste1=0.0;
   reactant1=0.0;
   buffer1=0.0;
   for(vector<struct tree*>::iterator it=t.begin();it!=t.end();it++){
         struct tree *t1=*it; 
         tms=0;
         waste=-1.0 * segment;
         reactant=0.0;
         buffer=0.0;
         operations(t1);
         //cout<<endl;
         //cout<<tms<<" "<<reactant<<" "<<buffer<<" "<<waste<<"\n";
         tms1+=tms;
         waste1+=reactant+buffer-1*segment;
         reactant1+=reactant;
         buffer1+=buffer;
         total_waste+=reactant+buffer-1*segment;
         total_tms+=tms;
         total_reactant+=reactant;
         total_buffer+=buffer;

    }  

}

//------------------------Storage Module started------------------------------

struct store{
   int id; //id=-1 if it is internal node else it is some positive number
   float val;
   int num_valve;
   vector<struct store*> adjacent;
};
int storage_node_count=0;

void createstorage(int l,int curr_level,int n,store *root){    //l=level  n=number of child
    if(curr_level==l)
      return;

    else{
        for(int i=0;i<n;i++){
          store *temp=new store;
          temp->id=-1;
          temp->num_valve=curr_level+2;
          root->adjacent.push_back(temp);
          createstorage(l,curr_level+1,n,temp);
        }

    }
}

void check_leaf_nodes(store *root,vector<struct store*> &storage){
  if(root->adjacent.size()==0)
  {
    //cout<<"\nNode";
    storage.push_back(root);
  }
  else{
    for(int i=0;i<root->adjacent.size();i++){

      check_leaf_nodes(root->adjacent[i],storage);
    }
  }
}
void add_leaf_nodes(store *root,int &add,int max_add,int n){
  if(root->adjacent.size()==0 && add>=max_add)
     return;
  if(root->adjacent.size()==0 && add<max_add)
  {
    //cout<<"\nNode";
    for(int i=0;i<n;i++){
          store *temp=new store;
          temp->id=storage_node_count;
          temp->num_valve=root->num_valve+1;
          root->adjacent.push_back(temp);
          
        }
        add++;
  }

  else{
    for(int i=0;i<root->adjacent.size();i++){

      add_leaf_nodes(root->adjacent[i],add,max_add,n);
    }
  }
}

//---------------------Storage Module ended--------------------






//-------------------Scheduling Module Started------------------
set<pair<int,int> > l1;
set<pair<int,int> > l2;
vector<int> l3;

set<int> find_final_schedule;
vector<pair<int,int> > final_schedule;
vector<pair<int,int> > L1, L2;
vector<int> levelwise[100];
int storage=0,max_storage=-1,max_height=-1;
map<int,int> levelorder; //Store node id in levelwise order


void find_list(struct tree* root,int height){

    for(int i=0;i<root->adjacent.size();i++){
    	    struct tree *node=root->adjacent[i].first;
    	    levelwise[height+1].push_back(node->node_id);
            if(node->val!=1.0 && node->val!=0.0){
              
            	if(node->adjacent.size()>0)
                    find_list(node,height+1);

            }       
    }

}

int start_schedule(int mixers){
    int tms=0;
    while(!l1.empty()){
        tms++;
        //cout<<"\nInside while";
        vector<int> node_scheduled;
        vector<int> shared_node_scheduled;
        for(int k=0;k<mixers && l1.size()!=0;k++){
            //cout<<"\nSchedule in mixer"<<k+1;
            //Condition 1 when node is shared and shared node is already created
            int mark=0;
            
          
            for(std::set<pair<int,int> >::iterator it=l1.begin();it!=l1.end() ;it++){
                int flag=0;
                pair<int,int> mypair=*it;

                
                if(mypair.second!=-1 && counter.find(node_number[mypair.second]->val*1e8)==counter.end()){
                  struct tree *temp=node_number[mypair.second];

                  if(temp->adjacent.size()!=0 ){
                    int temp_flag=0;	
 
                   for(int i=0;i<temp->adjacent.size();i++){
                      int id=temp->adjacent[i].first->node_id;
                      if(temp->adjacent[i].first->val!=1.0 && temp->adjacent[i].first->val!=0.0){
                        /*if((shared.find(id)!=shared.end() && counter.find(node_number[id]->val*1e8)!=counter.end())
                          || find_final_schedule.find(id)==find_final_schedule.end())
                            flag=1;*/

                         if(shared.find(id)!=shared.end() && find_final_schedule.find(shared.find(id)->second)==find_final_schedule.end())   
                             temp_flag=1;
                         //else
                         	//temp_flag=0;
                         else if(shared.find(id)==shared.end() && find_final_schedule.find(id)==find_final_schedule.end())
                            temp_flag=1;

                       }
                   
                    }
                    if(temp_flag==1 || temp_flag==-1)
                    	 flag=0;
                    else
                         flag=1;	
                   if(flag==1){
                   	 // cout<<"pre1"<<" "<<mypair.second<<endl;
                      node_scheduled.push_back(mypair.second);
                      l1.erase(l1.find(mypair));
                      cout<<"Node_scheduled"<<" "<<mypair.second<<endl<<" tms="<<tms<<" 1"<<endl;

                      //find_final_schedule.insert(id);
                      if(node_number[mypair.second]->parent_id!=-1 && find_final_schedule.find(mypair.second)==find_final_schedule.end()){
                         int flag=0;
                         for(int p=0;p<node_scheduled.size();p++)
                            if(node_scheduled[p]==node_number[mypair.second]->parent_id)
                               flag=1;
                        for(set<pair<int,int> >::iterator it1=l1.begin();it1!=l1.end();it1++)
                             if(node_number[mypair.second]->parent_id==it1->second)
                               flag=1;    
                         if(!flag){
                               //l2.insert(make_pair(mypair.first+1,node_number[mypair.second]->parent_id));
                               l3.push_back(node_number[mypair.second]->parent_id);

                         }   
                           
                      }

                     // mypair.second=-1;
                      mark=1;
                      break;
                    }
                 }
                 
                
               }
             


               if(mark)
                 break;
            }  
            if(mark==0)
            for(std::set<pair<int,int> >::iterator it=l1.begin();it!=l1.end() ;it++){
               int flag=0;
               pair<int,int> mypair=*it;


                if(mypair.second!=-1 && counter.find(node_number[mypair.second]->val*1e8)==counter.end()){
                 // cout<<"pre2"<<endl;
                       if(counter.find(node_number[mypair.second]->val*1e8)==counter.end())//&& counter.find(node_number[*it]->val*1e8)==counter.end())
                                    flag=1;
                       struct tree *temp=node_number[mypair.second];
                       if(temp->adjacent.size()!=0) //check
                       for(int i=0;i<temp->adjacent.size();i++){
                            int id=temp->adjacent[i].first->node_id;
                                if(temp->adjacent[i].first->val!=1.0 && temp->adjacent[i].first->val!=0.0){
                                    //if(shared.find(id)!=shared.end() && find_final_schedule.find(shared.find(id)->second)==find_final_schedule.end())
                                      //    flag=1;
                                    if (shared.find(id)==shared.end() && find_final_schedule.find(id)==find_final_schedule.end())
                                          flag=1;

                                 }
                   
                        } 
                       if(flag==0 ){
                            node_scheduled.push_back(mypair.second);
                            l1.erase(l1.find(mypair));
                            cout<<"Node_scheduled"<<" "<<mypair.second<<endl<<" tms="<<tms<<" 2"<<endl;
                            //find_final_schedule.insert(id);
                            if(node_number[mypair.second]->parent_id!=-1 && find_final_schedule.find(mypair.second)==find_final_schedule.end()){
                                      int flag=0;
                                     for(int p=0;p<node_scheduled.size();p++)
                                          if(node_scheduled[p]==node_number[mypair.second]->parent_id)
                                              flag=1;
                                     for(set<pair<int,int> >::iterator it1=l1.begin();it1!=l1.end();it1++)
                                          if(node_number[mypair.second]->parent_id==it1->second)
                                              flag=1;   
                                     if(!flag){
                                          //l2.insert(make_pair(mypair.first+1,node_number[mypair.second]->parent_id));
                                          l3.push_back(node_number[mypair.second]->parent_id);

                                      }   
                                      mypair.second=-1;
                                      mark=1;
                                       // cout<<"mark";
                                       break;
                            }  
                
                        }
                       if(mark)
                           break;
               
                
            }
           }
            if(mark==0)
            for(std::set<pair<int,int> >::iterator it=l1.begin();l1.size()!=0 && it!=l1.end() ;it++){
               
               int flag=0;
               pair<int,int> mypair=*it;
               struct tree *temp=node_number[mypair.second];
                if(mypair.second!=-1){
                      
                	  int k1;
                	  if(temp->adjacent.size()==0){
                	  	if(l1.find(mypair)!=l1.end())
                      	      l1.erase(l1.find(mypair));

                        for(map<int,int>::iterator it1=shared.begin();it1!=shared.end();it1++){

                           if(it1->first == mypair.second){                           	  
                           	  k1=it1->second;
                              
                           	  if(node_number[it1->second]->parent_id!=-1 && find_final_schedule.find(it1->second)==find_final_schedule.end()){
                           	  	   // cout<<"pre3"<<" "<<it1->second<<endl;
                           	  	    node_scheduled.push_back(it1->second);
                           	  	    cout<<"Node_scheduled"<<" "<<it1->second<<endl<<" tms="<<tms<<" 3"<<endl; 
                           	  	   // cout<<"err1"<<endl;
                           	  	    if(l1.find(make_pair(levelorder[it1->second],it1->second))!=l1.end())
                           	         l1.erase(l1.find(make_pair(levelorder[it1->second],it1->second)));
                           	        //cout<<"err1"<<endl;
                                    int flag=0;

                                    for(int p=0;p<node_scheduled.size();p++)
                                        if(node_scheduled[p]==node_number[it1->second]->parent_id)
                                            flag=1;
                                    for(set<pair<int,int> >::iterator it2=l1.begin();it2!=l1.end();it2++){
                                    	pair<int,int> temp_pair=*it2;
                                        if(node_number[it1->second]->parent_id==temp_pair.second)
                                            flag=1;                                         
                                    }
                                    if(!flag){
                                       //l2.insert(make_pair(mypair.first+1,node_number[mypair.second]->parent_id));
                                      l3.push_back(node_number[mypair.second]->parent_id);
                                   }
                                   for(set<pair<int,int> >::iterator it2=l1.begin();it2!=l1.end();it2++){
                                   	     pair<int,int> temp_pair=*it2;
                                   	     if(shared.find(temp_pair.second)!=shared.end() && shared.find(temp_pair.second)->second == it1->second ){
                                   	     	shared_node_scheduled.push_back(temp_pair.second);
                                        	//l1.erase(l1.find(make_pair(levelorder[temp_pair.second],temp_pair.second)));
                       
                                        	     l3.push_back(node_number[temp_pair.second]->parent_id);
                                        	//cout<<"nis"<<endl;
                                        }    
                                   }   
                               }
                               mark=1;
                               break;
 
                           }    	     	
                        }

                      }
                      else{
                              
                      	   node_scheduled.push_back(mypair.second);
                            if(l1.find(mypair)!=l1.end())
                      	      l1.erase(l1.find(mypair));
                      	  cout<<"Node_scheduled"<<" "<<mypair.second<<endl<<" tms="<<tms<<" 4"<<endl; 
                            //find_final_schedule.insert(id);
                            if(node_number[mypair.second]->parent_id!=-1 && find_final_schedule.find(mypair.second)==find_final_schedule.end()){
                                      int flag=0;
                                     
                                     for(int p=0;p<node_scheduled.size();p++)
                                          if(node_scheduled[p]==node_number[mypair.second]->parent_id)
                                              flag=1;
                                     for(set<pair<int,int> >::iterator it1=l1.begin();it1!=l1.end();it1++){
                                     	  pair<int,int> temp_pair=*it1;
                                          if(node_number[mypair.second]->parent_id==it1->second)
                                              flag=1;   
           
                                     }
                                     if(!flag){
                                          //l2.insert(make_pair(mypair.first+1,node_number[mypair.second]->parent_id));
                                          l3.push_back(node_number[mypair.second]->parent_id);

                                      }
                                      for(set<pair<int,int> >::iterator it2=l1.begin();it2!=l1.end();it2++){
                                   	     pair<int,int> temp_pair=*it2;
                                   	     //cout<<"nis111"<<endl;
                                   	     if(shared.find(temp_pair.second)!=shared.end() && shared.find(temp_pair.second)->second == mypair.second ){
                                   	     	shared_node_scheduled.push_back(temp_pair.second);
                                        	//l1.erase(l1.find(temp_pair));
                                            

                                        	     l3.push_back(node_number[temp_pair.second]->parent_id);
                                        	//cout<<"nis123"<<endl;
                                          }    
                                      }  

                                      mypair.second=-1;
                                      mark=1;
                                       // cout<<"mark";
                                      break;
                            }  




                      }

                      //find_final_schedule.insert(id);
                      
                      
                      //mark=1;
                      //cout<<"mark="<<mark<<endl;
                      //break;
                    
                
                }
                
                if(mark || l1.size()==0){
                  //cout<<"d_nis1"<<endl; 	
                  break;
                }

               
            }
            
            //cout<<"d_nis1"<<endl; 



            //cout<<"nishant2";
        }
       // cout<<"d_nis2"<<endl;

        for(vector<int>::iterator it=node_scheduled.begin();it!=node_scheduled.end();it++){
            //cout<<"nishant3";
             for(set<pair<int,int> >::iterator it1=l1.begin();it1!=l1.end();it1++){
             	pair<int,int> mypair= *it1;
             	if(mypair.second==*it){
             		l1.erase(l1.find(mypair));
             		break;
             		
             	}
             }
         }


         for(vector<int>::iterator it=shared_node_scheduled.begin();it!=shared_node_scheduled.end();it++){
            //cout<<"nishant3";
             for(set<pair<int,int> >::iterator it1=l1.begin();it1!=l1.end();it1++){
             	pair<int,int> mypair= *it1;
             	if(mypair.second==*it){
             		 
             		   l1.erase(l1.find(mypair));
             		   break;
             		   
             	}
             }
         }


        /*set<pair<int,int> > temp;
        for(set<pair<int,int> >::iterator it=l1.begin();it!=l1.end();it++){
             if(it->second!=-1){
                temp.insert(*it);
             }
          
           
        }
        l1.clear();*/
        for(vector<int>::iterator it=l3.begin();it!=l3.end();it++){
        	for(vector<int>::iterator it1=it+1;it1!=l3.end();it1++){
        		if(*it1==*it){
        			 cout<<"l3="<<*it<<endl;
        			l3.erase(it1);
                    break;
        		}
        	}
        }

        for(vector<int>::iterator it=l3.begin();it!=l3.end();it++){
           //cout<<*it;
           l1.insert(make_pair(levelorder[*it],*it));
           //cout<<node_number[*it]->val<<"\t"<<levelorder[*it]<<endl;
          
           
        }
        for(set<pair<int,int> >::iterator it=l1.begin();it!=l1.end();it++){
        	    pair<int,int> mypair=*it; 
        	    int temp=0;
                for(set<pair<int,int> >::iterator it1=l1.begin();it1!=l1.end();it1++){
                	pair<int,int> temp_pair=*it1;

                	if(temp==0 && temp_pair.second==mypair.second){
                		 temp=1;
                		
                	}
                	else if(temp==1 && temp_pair.second==mypair.second){
                		l1.erase(it1);
                		break;
                	}
                          
                }

        }

        for(vector<int>::iterator it=node_scheduled.begin();it!=node_scheduled.end();it++){
            //cout<<"nishant3
            //cout<<*it<<endl;
            final_schedule.push_back(make_pair(*it,tms));
            find_final_schedule.insert(*it);
        }


       for(vector<pair<int,int> >::iterator it=final_schedule.begin();it!=final_schedule.end();it++){
            pair<int,int> pr=*it;
           //cout<<pr.first<<"->"<<node_number[pr.first]->val<<" "<<pr.second<<endl; 
          }
          
         
        l2.clear();
        l3.clear();
        node_scheduled.clear();
         
      
      // cout<<"\nL1 size="<<l1.size();
    }
    return tms;
}


int valve_used(vector<struct store*> &myvec_storage,vector<vector<int> > &temp_list){
       int num_valve=0;
       map<int,int> counter1(counter);

       for(int i=0;i<myvec_storage.size();i++){
          myvec_storage[i]->val=0.0;
       }

         for(vector<pair<int,int> >::iterator it=final_schedule.begin();it!=final_schedule.end();it++){
            pair<int,int> pr=*it;
           // int time=pr.second;
            //cout<<pr.first<<"->"<<node_number[pr.first]->val<<" tms="<<pr.second<<endl; 

            //Calculating storage
            if(node_number[pr.first]->parent_id!=-1 && counter1.find(node_number[pr.first]->val*1e8)==counter1.end()){
                      storage+=1;
                      struct tree* temp=node_number[pr.first];
                      for(vector<pair<struct tree*,int> >::iterator  it1=temp->adjacent.begin();it1!=temp->adjacent.end();it1++){
                            struct tree *node=it1->first;
                            if(node->val!=1.0 && node->val!=0.0){
                                   //if(shared.find(node->node_id)!=shared.end())
                                   int p=0;
                                   for(vector<int>::iterator it2=temp_list[pr.second-1].begin();it2!=temp_list[pr.second-1].end();it2++){
                                          if(node->val==node_number[*it2]->val){
                                                p=1;
                                                break;
                                          }

          
                                   }    
                                   if(p!=1){
                                     for(int i=0;i<myvec_storage.size();i++){
                                        if(myvec_storage[i]->val==node->val){
                                          myvec_storage[i]->val=0.0;
                                        }  

                                     }   
                                     storage-=1;
                                   }

                         
                            }
                      } 
                       for(int i=0;i<myvec_storage.size();i++){
                             if(myvec_storage[i]->val==0){
                                  myvec_storage[i]->val=node_number[pr.first]->val;
                                  num_valve+=myvec_storage[i]->num_valve;
                             }

                      } 
            }

            else if(shared.find(pr.first)==shared.end() && counter1.find(node_number[pr.first]->val*1e8)!=counter1.end()){
                      int t=0;   
                      if(counter1[node_number[pr.first]->val*1e8]-segment>=0){
                           storage+=segment;
                           t+=segment;
                           counter1[node_number[pr.first]->val*1e8]-=segment;
                      }
                      else{
                          storage+=counter1[node_number[pr.first]->val*1e8];
                          t+=counter1[node_number[pr.first]->val*1e8];
                           counter1[node_number[pr.first]->val*1e8]=0;
                      }
                      //cout<<"\nStorage="<<storage;

                      for(vector<int>::iterator it1=temp_list[pr.second+1].begin();it1!=temp_list[pr.second+1].end();it1++){
                          for(vector<pair<struct tree*,int> >::iterator it2=node_number[*it1]->adjacent.begin();it2!=node_number[*it1]->adjacent.end();it2++){
                              if(node_number[pr.first]->val==it2->first->val){
                                   // cout<<"\nnis";
                                   storage-=1;
                                   t-=1;
                              }
                          }
                      }
                      struct tree* temp=node_number[pr.first];
                      for(vector<pair<struct tree*,int> >::iterator  it1=temp->adjacent.begin();it1!=temp->adjacent.end();it1++){
                           struct tree *node=it1->first;
                           if(node->val!=1.0 && node->val!=0.0){
                             //if(shared.find(node->node_id)!=shared.end())
                               int p=0;
                               for(vector<int>::iterator it2=temp_list[pr.second-1].begin();it2!=temp_list[pr.second-1].end();it2++){
                                     if(node->val==node_number[*it2]->val){
                                          p=1;
                                          break;
                                     }

          
                               }    
                               if(p!=1){
                                 for(int i=0;i<myvec_storage.size();i++){
                                      if(myvec_storage[i]->val==node->val){
                                          myvec_storage[i]->val=0.0;
                                      }

                                 }   
                                 storage-=1;
                               }

                         
                           }
                       } 
                       for(int j=0;j<t;j++){
                          for(int i=0;i<myvec_storage.size();i++){
                             if(myvec_storage[i]->val==0){
                                  myvec_storage[i]->val=node_number[pr.first]->val;
                                  num_valve+=myvec_storage[i]->num_valve;
                             }

                          } 
                       }      
             }
             struct tree* temp=node_number[pr.first];
             for(vector<pair<struct tree*,int> >::iterator  it1=temp->adjacent.begin();it1!=temp->adjacent.end();it1++){
                  struct tree *node=it1->first;
                  if(node->val!=1.0 && node->val!=0.0){
                     //if(shared.find(node->node_id)!=shared.end())
                         int p=0;
                         for(vector<int>::iterator it2=temp_list[pr.second-1].begin();it2!=temp_list[pr.second-1].end();it2++){
                                if(node->val==node_number[*it2]->val){
                                   p=1;
                                   break;
                                }

          
                          }    
                          if(p!=1)
                             storage-=1;

                         
                  }
             } 
         

        }

     return num_valve;
}



void schedule(vector<struct tree*> &t,int mixers){


     for(vector<struct tree*>::iterator it=t.begin();it!=t.end();it++){
         struct tree *t1=*it; 
         levelwise[0].push_back(t1->node_id);
         find_list(t1,0);


     } 
     for(int i=0;i<100;i++){
        if(levelwise[i].size()==0){
             max_height=i-1;
             break;
        }
     }
     for(int i=max_height;i>=0;i--){

        for(vector<int>::iterator it=levelwise[i].begin();it!=levelwise[i].end();it++){
        	 levelorder[*it]=max_height-i;
        	 //cout<<*it<<endl;
        	 if(node_number[*it]->adjacent.size()==0){
        	 	if(node_number[*it]->val!=0 && node_number[*it]->val!=1 ){
                            l1.insert(make_pair(max_height-i,*it));
                            //cout<<*it<<endl; 
                           // cout<<"nis"<<endl;
                }
                


        	 }

                

              else{

              	  int flag=0;
                  for(int h=0;h<node_number[*it]->adjacent.size();h++){

                  	  if((node_number[*it]->adjacent[h].first)->val!=0 && node_number[*it]->adjacent[h].first->val!=1 ){
                  	  	  flag=1;
                  	  	  //cout<<"nis";
                  	  }
                  	  
                  }
                  if(flag==0){	
                  	  l1.insert(make_pair(max_height-i,*it)); 
                  	 // cout<<*it<<endl; 
                  }
              }


        }
        
      }

     for(set<pair<int,int> >::iterator it=l1.begin();it!=l1.end();it++){
     	    pair<int,int> mypair=*it;
             //cout<<mypair.second<<"->"<<node_number[mypair.second]->val<<endl; 
     }
     cout<<"nishant"<<endl;

       int tms=start_schedule(mixers);    
       cout<<"\nTMS="<<tms;
       
       storage=0;
       vector<vector<int> > temp_list(1000);
       map<int,int> counter1(counter);
       //temp_list.resize(tms+1);
   
       //Storage calculations
       for(vector<pair<int,int> >::iterator it=final_schedule.begin();it!=final_schedule.end();it++){
             pair<int,int> pr=*it;
             temp_list[pr.second].push_back(pr.first);
       }
       cout<<"\nFinal Schedule:\n";

      
       for( vector<vector<int> >::iterator it=temp_list.begin(); it!=temp_list.end();it++ ){
               vector<int> myvec=*it;
               int ab=0;
               for(vector<int> ::iterator it1=myvec.begin(); it1!=myvec.end();it1++){
                 cout<<++ab<<":"<<*it1<<" "<<node_number[*it1]->val<<endl;
               } 

       }
       cout<<endl;


       for(vector<pair<int,int> >::iterator it=final_schedule.begin();it!=final_schedule.end();it++){
            pair<int,int> pr=*it;
           // int time=pr.second;
            //cout<<pr.first<<"->"<<node_number[pr.first]->val<<" tms="<<pr.second<<endl; 

            //Calculating storage
            if(node_number[pr.first]->parent_id!=-1 && counter1.find(node_number[pr.first]->val*1e8)==counter1.end())
                      storage+=1;

            else if(shared.find(pr.first)==shared.end() && counter1.find(node_number[pr.first]->val*1e8)!=counter1.end()){   
                      if(counter1[node_number[pr.first]->val*1e8]-segment>=0){
                           storage+=segment;
                           counter1[node_number[pr.first]->val*1e8]-=segment;
                      }
                      else{
                          storage+=counter1[node_number[pr.first]->val*1e8];
                           counter1[node_number[pr.first]->val*1e8]=0;
                      }
                      //cout<<"\nStorage="<<storage;
             }
             struct tree* temp=node_number[pr.first];
             for(vector<pair<struct tree*,int> >::iterator  it1=temp->adjacent.begin();it1!=temp->adjacent.end();it1++){
                  struct tree *node=it1->first;
                  if(node->val!=1.0 && node->val!=0.0){
                     //if(shared.find(node->node_id)!=shared.end())
                         int p=0;
                         for(vector<int>::iterator it2=temp_list[pr.second-1].begin();it2!=temp_list[pr.second-1].end();it2++){
                                if(node->val==node_number[*it2]->val){
                                   p=1;
                                   break;
                                }

          
                          }    
                          if(p!=1)
                             storage-=1;

                         
                  }
             } 
             //Checking whether this node is used in the next tms
            /* vector<pair<int,int> >::iterator p=it+1;
             for(int i=0;i<2;i++,p++){
                pair<int,int> t1=*p;
                //if(nodet1.first)
                for(vector<pair<struct tree*,int> >::iterator it1=node_number[t1.first]->adjacent.begin();it1!=node_number[t1.first]->adjacent.end();it1++){
                    if(pr.first==it1->first->node_id)
                      storage-=1;
                }
             }*/

             for(vector<int>::iterator it1=temp_list[pr.second+1].begin();it1!=temp_list[pr.second+1].end();it1++){
                  for(vector<pair<struct tree*,int> >::iterator it2=node_number[*it1]->adjacent.begin();it2!=node_number[*it1]->adjacent.end();it2++){
                    if(node_number[pr.first]->val==it2->first->val){
                     // cout<<"\nnis";
                      storage-=1;
                    }
                }
             }               

             if(max_storage<storage)
                 max_storage=storage;

             //cout<<"\nStorage="<<storage;  

        }

        cout<<"\nMax storage needed="<<max_storage<<endl;

        //Creating storage 
        for(int num_ch=2;num_ch<=4;num_ch++){
                int num,l=0,add=0,max_add;
                struct store* store_root=new store;
                store_root->id=-1;
                storage_node_count=0;
                //cin>>num>>num_ch;
                num=max_storage;

                //l=(int)pow((double)128,1.0/num_ch);
                l=0;
                while(pow(num_ch,l+1)<num){
                   l++;
                }
                //cout<<l;
                createstorage(l,0,num_ch,store_root);
                //check_leaf_nodes(store_root);

                max_add=ceil((num - (int)pow(num_ch,l))/(num_ch-1));
                //cout<<"\nMax_add="<<max_add;
                add_leaf_nodes(store_root,add,max_add,num_ch);
                vector<struct store*> myvec_storage;
                check_leaf_nodes(store_root,myvec_storage); 
                reverse(myvec_storage.begin(),myvec_storage.end());
                cout<<"\nValve used="<<valve_used(myvec_storage,temp_list);
                cout<<"\n";
                myvec_storage.clear();



        }
        
        cout<<"\nDebug:nis\n";


  
}

//----------------------Scheduling module ended----------------------------

int error(int N,double epsilon, double target){
    int z=1,flag=0;
    ll x;
    long err;

      while(flag==0){
           z++;
           //cout<<z;
           if(target*pow(N,z)-(int)target*pow(N,z) <= 0.5)
                 x=target*pow(N,z);
           else
                 x=target*pow(N,z)+1;   
           if(fabs(target-(long double)x/pow(N,z))<epsilon){
                err=fabs(target-target*pow(N,z));
                flag=1;

           }
      }
      return z;

}



int main(){
    // struct tree *root=tree_generation();
    double table[20][10],a1,a2,a3,a4;
    int total=0;
    int file_arr[]={2,5,10,20,50,100};
    vector<struct tree*> t;

    waste1=0.0,reactant1=0.0,buffer1=0.0,total_waste=0.0,total_reactant=0.0,total_buffer=0.0;
    tms1=0,total_tms=0;

    total=0;
  //  freopen(str1.c_str(),"r",stdin);
  //  freopen(str2.c_str(),"w",stdout);
    double arr[100];
    double ct,epsilon,err,ms,rms,avg_rms=0.0;
    int num,N,max_z=0,avg_z=0;
    //freopen ("test.txt","r",stdin);
    //cin>>epsilon;
    epsilon=0.001;
    //cin>>a1>>a2>>a3>>a4;
    a1=0.5,a2=.1,a3=.1,a4=.3;
    cin>>num;

    for(int k=0;k<num;k++)
                  cin>>arr[k];
   // cout<<"N\tz\tTm\tNr\tNw\tNb\tRS\tf\tdelta"<<endl;            
    for(int N=2;N<11;N++){

          avg_rms=0.0;
          avg_z=0;
          ms=0.0;
         
         int temp;
         ms=0.0;
         max_z=0;
         for(int k=0;k<num;k++){
                  //cin>>arr[k];
                  temp=error(N,epsilon,arr[k]);    
                  if(temp>max_z){
                    max_z=temp;
                  }        
                  
         }
         //cout<<"max_z="<<max_z<<" "<<endl;
         for(int k=0;k<num;k++){
            //int x=arr[k]*pow(N,max_z);
            int x;
            if(arr[k]*pow(N,max_z)-(int)arr[k]*pow(N,max_z) <= 0.5)
                 x=arr[k]*pow(N,max_z);
            else
                 x=arr[k]*pow(N,max_z)+1;  
             //cout<<"x="<<x<<endl;  
            //cout<<fabs((long double)x/pow(N,max_z)-arr[k])<<endl;
            ms+=pow(arr[k]-(double)x/pow(N,max_z),2);
            //ms+=fabs(arr[k]-(long double)x/pow(N,max_z));
         }
         //ms=(double)ms/num;
         rms=sqrt(ms);
       //  avg_rms+=ms;
       //  avg_z+=max_z;
    //}
    //cout<<" average rms="<<(long double)avg_rms/(num)<<" average z="<<avg_z/num<<endl;
    //cout<<"RMS="<<rms<<" Max_z="<<max_z<<endl;    
    int n;
    //cin>>n>>accuracy>>segment;
     segment=N;
     accuracy=max_z;

    //for(int i=0;i<n;i++){
     // int m;
      //cin>>m;
      total+=num;
      for(int j=0;j<num;j++){
           if(arr[j]*pow(N,max_z)-(int)arr[j]*pow(N,max_z) <= 0.5)
                 mytarget=floor(arr[j]*pow(N,max_z));
           else
                 mytarget=floor(arr[j]*pow(N,max_z)+1);
        //mytarget=arr[j]*pow(N,max_z);
         //cout<<"mytarget="<<mytarget<<" "<<arr[j]*pow(N,max_z)<<endl;
         if(mytarget==pow(N,max_z))
              mytarget-=1;
         struct tree *root=tree_generation();
         //cout<<"\nTree Generation code exited!!"<<endl;
         t.push_back(root);
         //cout<<endl;
       }

       sharing(t);

       analysis(t);
       //tree_to_dot(t);
       t.clear();
       counter.clear();
       node_number.clear();

      
       l1.clear();
       l2.clear();
       find_final_schedule.clear();
       final_schedule.clear();
       for(int p=0;p<100;p++)
            levelwise[p].clear();
  
       shared.clear();
       node_shared.clear(); 
       storage=0,max_storage=-1,max_height=-1;
       table[N][0]=N;
       table[N][1]=max_z;
       table[N][2]=(double)tms1/num;
       table[N][3]=(double)reactant1/num;
       table[N][4]=(double)waste1/num;
       table[N][5]=(double)buffer1/num;
       table[N][6]=rms;
       table[N][7]=(double)(a1*table[N][2] + a2*table[N][3] + a3*table[N][4] + a4*table[N][6]/epsilon); 

      cout<<table[N][0]<<" "<<table[N][1]<<" "<<table[N][2]<<" "<<table[N][3]<<" "<<table[N][4]<<" "<<table[N][5]<<" "<<table[N][6]<<" "<<table[N][7]<<" "<<a4*table[N][6]/epsilon<<endl;


   }

      double fmin=(double)INT_MAX;
      int final_N;
      for(int i=2;i<11;i++){
               if(fmin>table[i][7]){
                   fmin=table[i][7];
                   final_N=i;
               }
             
      }
      cout<<final_N<<" "<<table[final_N][1]<<endl;


   

}
