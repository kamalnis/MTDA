#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

struct store{
   int id; //id=-1 if it is internal node else it is some positive number
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
        	root->adjacent.push_back(temp);
        	createstorage(l,curr_level+1,n,temp);
        }

    }
}

void check_leaf_nodes(store *root){
	if(root->adjacent.size()==0)
	{
		cout<<"\nNode";
	}
	else{
		for(int i=0;i<root->adjacent.size();i++){

			check_leaf_nodes(root->adjacent[i]);
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

int main(){
	int num,l,num_ch,add=0,max_add;
	struct store* store_root=new store;
	store_root->id=-1;
	storage_node_count=0;
	cin>>num>>num_ch;

    l=pow((float)num,1.0/num_ch);
    cout<<l;
    createstorage(l,0,num_ch,store_root);
    //check_leaf_nodes(store_root);

    max_add=ceil((num - (int)pow(num_ch,l))/(num_ch-1));
    cout<<"\nMax_add="<<max_add;
    add_leaf_nodes(store_root,add,max_add,num_ch);
    check_leaf_nodes(store_root);


}