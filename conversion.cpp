#include<iostream>
#include<vector>
#include<cmath>
#include<cstring>
#include<cfloat>
#include<climits>
#include<set>
#include<map>
typedef long long ll;

using namespace std;


int main(){
	int num,tms;
	float reactant,buffer,wastage;
	//freopen("test_d2.txt","r",stdin);
	freopen("test_d2_out.txt","w",stdout);
	set<int> myset;
	map<int,float> mymap;
	for(int i=0;i<99;i++){
	   cin>>num>>tms>>reactant>>buffer>>wastage;
	   float temp=0.64*num;
	   mymap[(int)temp]=temp-(int)temp;
	   //cout<<"nis";
	   if(myset.find((int)temp)==myset.end()){
	      myset.insert((int)temp);
	      //reactant*=10;
	      //buffer*=10;
	      //wastage*=10;
	      cout<<(int)temp<<"\t"<<tms<<"\t"<<reactant<<"\t"<<buffer<<"\t"<<wastage<<endl;
	  }
	}
}