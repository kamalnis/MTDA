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
	int num,tms,a,b;
	float reactant,buffer,wastage;
	//freopen("test_d2.txt","r",stdin);
	freopen("N4_d3_out.txt","w",stdout);
	set<int> myset;
	map<int,float> mymap;
	for(int i=0;i<63;i++){
	   cin>>num>>a>>b>>tms>>reactant>>buffer>>wastage;
	   
	   cout<<num<<"\t"<<tms<<"\t"<<reactant/4<<"\t"<<buffer/4<<"\t"<<wastage/4<<endl;
	  
	}
}