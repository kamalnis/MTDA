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




//int count1=0;     //for automation
int segment,accuracy;
map<int,struct tree *> node_number;
struct tree *  tree_generation(){
  vector<int> arr;
  double target,acv,d,rcv;
  int x=0; 
  //d=0.0001;
  cin>>target;
  d=pow((float)10,-(accuracy+1));
  //cout<<"\nd="<<d;
  int var=decimalToBasek(target,segment);  //change accuracy value for the test cases
  //cout<<"\nvar="<<var; 

  struct tree *parent=NULL, *root;
  //struct tree *t = (struct tree*)malloc(sizeof(struct tree));
  struct tree *t = new tree;
  t->node_id=count_id++;
  t->parent_id=-1;
  t->pt=NULL;
  node_number[t->node_id]=t;
 // cout<<"\n Parent node is created";
 
  target=(float)var/pow(10,accuracy);
  //target=(float)var/1000;
  //cout<<"\ntarget="<<target;
  t->val=target;
  //cout<<"\ntval="<<t->val<<" var"<<var;
  root=t;
  parent = t;
  rcv =(float)var/pow(10,accuracy);
  acv=0.0;
  
  var=target * 1e9;
  if(var%10==9)
    var+=1;
  //cout<<var<<endl;

  while(var){
     int k=var%10;
     arr.insert(arr.begin(),k);
     var=var/10;
  }
  while(arr.size()!=9){
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
            rcv=rcv+(float)arr[j]*pow(10,-k);
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
          acv+=float(arr[i+1]) * pow(10,-x-2);
          arr[i+1]=0;
          int k=1;
          rcv=0.0;
          for(int j=i;j<arr.size();j++){
            rcv=rcv+(float)arr[j]*pow(10,-k);
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

             cout<<"\nSharing node for "<<it->first<<" "<<it->second;
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


vector<int> l1;
set<int> l2;
set<int> find_final_schedule;
vector<pair<int,int> > final_schedule;
int storage=0;

void find_list(struct tree* root){
     int flag=0;


/*
     if(root->adjacent.size()!=0){

        for(int i=0;i<root->adjacent.size();i++){
           struct tree *node=root->adjacent[i].first;
         
           if(node->val!=1.0 && node->val!=0.0){
                if(shared.find(node->node_id)==shared.end())
                   flag=1;
           }
         
        }
     }   */

     for(int i=0;i<root->adjacent.size();i++){
         struct tree *node=root->adjacent[i].first;
         if(node->adjacent.size()>0)
            flag=1;
     }  

     if(flag==0)
            l1.push_back(root->node_id);
     else{
         for(int i=0;i<root->adjacent.size();i++){
            struct tree *node=root->adjacent[i].first;
            if(node->val!=1.0 && node->val!=0.0){
               if(node->adjacent.size()>0)
                 find_list(node);
            }

         
        }

     } 




}

int start_schedule(int mixers){
    int tms=0;
    while(!l1.empty()){
        tms++;
        cout<<"\nInside while";
        vector<int> node_scheduled;
        for(int k=0;k<mixers;k++){
            cout<<"\nSchedule in mixer"<<k+1;
            //Condition 1 when node is shared and shared node is already created
            int mark=0;

          
            for(std::vector<int>::iterator it=l1.begin();it!=l1.end() ;it++){
                int flag=0;
                if(*it!=-1){
                cout<<"1";
                struct tree *temp=node_number[*it];
                 if(counter.find(node_number[*it]->val*1e8)!=counter.end())
                            flag=1;
      
                
                for(int i=0;i<temp->adjacent.size();i++){
                    int id=temp->adjacent[i].first->node_id;
                    if(temp->adjacent[i].first->val!=1.0 && temp->adjacent[i].first->val!=0.0){
                        /*if((shared.find(id)!=shared.end() && counter.find(node_number[id]->val*1e8)!=counter.end())
                          || find_final_schedule.find(id)==find_final_schedule.end())
                            flag=1;*/

                         if(shared.find(id)!=shared.end() && find_final_schedule.find(shared.find(id)->second)==find_final_schedule.end())   
                             flag=1;
                         else if(shared.find(id)==shared.end() && find_final_schedule.find(id)==find_final_schedule.end())
                            flag=1;

                    }
                   
                }
                if(flag==0){
                      node_scheduled.push_back(*it);
                      //find_final_schedule.insert(id);
                      if(node_number[*it]->parent_id!=-1 && find_final_schedule.find(*it)==find_final_schedule.end()){
                         int flag=0;
                         for(int p=0;p<node_scheduled.size();p++)
                            if(node_scheduled[p]==node_number[*it]->parent_id)
                               flag=1;
                        for(vector<int>::iterator it1=l1.begin();it1!=l1.end();it1++)
                             if(node_number[*it]->parent_id==*it1)
                               flag=1;    
                         if(!flag)   
                           l2.insert(node_number[*it]->parent_id);
                      }
                      *it=-1;
                      mark=1;
                      break;
                }
                
               }


               if(mark)
                 break;
            }  
            if(mark==0)
            for(std::vector<int>::iterator it=l1.begin();it!=l1.end() ;it++){
               int flag=0; 
               if(*it!=-1){ 
               cout<<"2";
                if(counter.find(node_number[*it]->val*1e8)==counter.end())//&& counter.find(node_number[*it]->val*1e8)==counter.end())
                    flag=1;
                struct tree *temp=node_number[*it];
                for(int i=0;i<temp->adjacent.size();i++){
                    int id=temp->adjacent[i].first->node_id;
                    if(temp->adjacent[i].first->val!=1.0 && temp->adjacent[i].first->val!=0.0){
                         if(shared.find(id)!=shared.end() && find_final_schedule.find(shared.find(id)->second)==find_final_schedule.end())
                             flag=1;
                         else if (shared.find(id)==shared.end() && find_final_schedule.find(id)==find_final_schedule.end())
                            flag=1;
                      /* if(find_final_schedule.find(id)==find_final_schedule.end())
                            flag=1;

                         else if(shared.find(id)!=shared.end() && find_final_schedule.find(shared.find(id)->second)==find_final_schedule.end())   
                             flag=1;*/

                    }
                   
                } 
                 if(flag==0 ){
                      node_scheduled.push_back(*it);
                      //find_final_schedule.insert(id);
                      if(node_number[*it]->parent_id!=-1 && find_final_schedule.find(*it)==find_final_schedule.end()){
                         int flag=0;
                         for(int p=0;p<node_scheduled.size();p++)
                            if(node_scheduled[p]==node_number[*it]->parent_id)
                               flag=1;
                          for(vector<int>::iterator it1=l1.begin();it1!=l1.end();it1++)
                             if(node_number[*it]->parent_id==*it1)
                               flag=1;   
                         if(!flag)   
                           l2.insert(node_number[*it]->parent_id);
                       }
                      *it=-1;
                      mark=1;
                      cout<<"mark";
                      break;
                }  
                
                }
                if(mark)
                  break;
               
            }

           

           
           /* if(mark==0)
            for(std::vector<int>::iterator it=l1.begin();it!=l1.end() ;it++){
                int flag=0;
                if(*it!=-1){
                cout<<"3";
                struct tree *temp=node_number[*it];
                
                for(int i=0;i<temp->adjacent.size();i++){
                    int id=temp->adjacent[i].first->node_id;
                    if(temp->adjacent[i].first->val!=1.0 && temp->adjacent[i].first->val!=0.0){
                       //  if(shared.find(id)!=shared.end() && counter.find(node_number[id]->val*1e8)!=counter.end())
                         //   flag=1;
                       if((shared.find(id)!=shared.end() && counter.find(node_number[id]->val*1e8)==counter.end())
                           && find_final_schedule.find(id)==find_final_schedule.end())
                            flag=1;


                    }
                   
                }
                if(flag==0 ){
                      node_scheduled.push_back(*it);
                      //find_final_schedule.insert(id);
                      if(node_number[*it]->parent_id!=-1 && find_final_schedule.find(*it)==find_final_schedule.end()){
                         int flag=0;
                         for(int p=0;p<node_scheduled.size();p++)
                            if(node_scheduled[p]==node_number[*it]->parent_id)
                               flag=1;
                        for(vector<int>::iterator it1=l1.begin();it1!=l1.end();it1++)
                             if(node_number[*it]->parent_id==*it1)
                               flag=1;    
                         if(!flag)   
                           l2.insert(node_number[*it]->parent_id);
                      }
                      *it=-1;
                      mark=1;
                      break;
                }
                
               }
               if(mark)
                 break;

            } */
            cout<<"nishant2";
        }
        vector<int> temp;
        for(vector<int>::iterator it=l1.begin();it!=l1.end();it++){
             if(*it!=-1){
                temp.push_back(*it);
             }
          
           
        }
        l1.clear();
        cout<<"\nL1:";
        for(vector<int>::iterator it=temp.begin();it!=temp.end();it++){
            cout<<*it<<" "<<node_number[*it]->val<<endl;
            l1.push_back(*it);
           
        }

        cout<<"\nL2:";
        for(set<int>::iterator it=l2.begin();it!=l2.end();it++){
           cout<<*it;
           l1.push_back(*it);
          
           
        }

        for(vector<int>::iterator it=node_scheduled.begin();it!=node_scheduled.end();it++){
            cout<<"nishant3";



            if(shared.find(*it)!=shared.end())
               storage-=1;
            else if(counter.find(node_number[*it]->val*1e8)==counter.end())
               storage+=segment;
           
               //storage
            final_schedule.push_back(make_pair(*it,tms));
            find_final_schedule.insert(*it);
        }


       for(vector<pair<int,int> >::iterator it=final_schedule.begin();it!=final_schedule.end();it++){
            pair<int,int> pr=*it;
            cout<<pr.first<<"->"<<node_number[pr.first]->val<<endl; 
          }

         
        l2.clear();
         
      
       cout<<"\nL1 size="<<l1.size();
    }
    return tms;
}
void schedule(vector<struct tree*> &t){


     for(vector<struct tree*>::iterator it=t.begin();it!=t.end();it++){
         struct tree *t1=*it; 
         find_list(t1);


     } 
      for(vector<int>::iterator it=l1.begin();it!=l1.end();it++)
            cout<<*it<<"->"<<node_number[*it]->val<<endl; 

       int tms=start_schedule(3);    
       cout<<"\nTMS="<<tms;
       cout<<"\nFinal Schedule:\n";
       for(vector<pair<int,int> >::iterator it=final_schedule.begin();it!=final_schedule.end();it++){
            pair<int,int> pr=*it;
            cout<<pr.first<<"->"<<node_number[pr.first]->val<<" tms="<<pr.second<<endl; 

        }


  
}


int main(){
    // struct tree *root=tree_generation();
    int total=0;
    int file_arr[]={2,5,10,20,50,100};
    vector<struct tree*> t;

    waste1=0.0,reactant1=0.0,buffer1=0.0,total_waste=0.0,total_reactant=0.0,total_buffer=0.0;
    tms1=0,total_tms=0;

    total=0;
  //  freopen(str1.c_str(),"r",stdin);
  //  freopen(str2.c_str(),"w",stdout);
    int n;
    cin>>n>>accuracy>>segment;
    for(int i=0;i<n;i++){
      int m;
      cin>>m;
      total+=m;
      for(int j=0;j<m;j++){
         struct tree *root=tree_generation();
         //cout<<"\nTree Generation code exited!!"<<endl;
         t.push_back(root);
         //cout<<endl;
       }


       sharing(t);

      /* for(map<int,int>::iterator it=counter.begin();it!=counter.end();it++){

            cout<<"\nSharing node for "<<it->first/1e6<<" "<<it->second;
            
       }*/


       schedule(t);

       analysis(t);
       tree_to_dot(t);
       t.clear();
       counter.clear();
       node_number.clear();
       cout<<tms1<<" "<<reactant1<<" "<<buffer1<<" "<<waste1<<endl;


    }
   
    cout<<(float)total_tms/total<<" "<<total_reactant/total<<" "<<total_buffer/total<<" "<<total_waste/total;


    /*for(int i=0;i<n;i++){
      struct tree *root=tree_generation();
      //cout<<"\nTree Generation code exited!!"<<endl;
      t.push_back(root);
      //cout<<endl<<endl<<endl;
      tms=0;
      waste=-1.0;
      reactant=0.0;
      buffer=0.0;
      operations(root);
      cout<<endl;
      cout<<i+1<<" "<<tms<<" "<<reactant<<" "<<buffer<<" "<<waste;
    }*/

}