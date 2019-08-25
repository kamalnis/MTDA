#include<iostream>
#include<vector>
#include<cstring>
#include<cfloat>
#include<climits>
#include<set>
#include<map>
#include<cstdio>
#include<string>
#include<fstream>

typedef long long ll;

using namespace std;
int count_id=0;
struct tree{
 int node_id;  
 double val;
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
        temp->val = 1;
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
          temp->val=arr[i+1] * 0.1;
          //cout<<"\nSecond node created with val "<<temp->val;
          //struct tree *child1 = (struct tree*)malloc(sizeof(struct tree));
          struct tree *child1 = new tree;
          child1->node_id=count_id++;
          child1->val=1;
          temp->adjacent.push_back(make_pair(child1,(int)(temp->val*10)));
          //struct tree *child2 = (struct tree*)malloc(sizeof(struct tree));
          struct tree *child2 = new tree;
          child2->node_id=count_id++;
          child2->val=0;
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
         temp1->val=rcv*10;
         parent->adjacent.push_back(make_pair(temp1,1));
        // cout<<"\n Third node created and val="<<temp1->val;
         y+=1;
         if((segment-y) != 0){
             //struct tree *temp = (struct tree*)malloc(sizeof(struct tree));
             struct tree *temp = new tree;
             temp->node_id=count_id++;
             temp->val=0;
             //cout<<"\n Node with 0 cv created.";
             parent->adjacent.push_back(make_pair(temp,segment-y));
         }
         parent = temp1;
      }
      else{
      	if((segment-y) != 0){
          struct tree *temp = (struct tree*)malloc(sizeof(struct tree));
          temp->node_id=count_id++;
          temp->val=0;
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
              if(counter[t1->val*1e8]%segment!=0)
                         t1->adjacent.clear();         //checking node node need to be created
              counter[t1->val*1e8]++;
             // cout<<"\nSharing node for "<<t1->val<<" "<<counter[t1->val*10e6];
             // t1->adjacent.clear();
         }
         else{
            //  cout<<"\n Inside else part";
              
              
             if(!(t1->val==1.0 || t1->val==0.0)){
                     counter[t1->val*1e8]=1;
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

             //cout<<"\nSharing node for "<<it->first<<" "<<it->second;
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

       analysis(t);
       tree_to_dot(t);
       t.clear();
       counter.clear();
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
