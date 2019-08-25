#include<iostream>
#include<cmath>

typedef long long ll;
using namespace std;

int error(int N,long double epsilon, long double target){
	  int z=1,flag=0;
	  ll x;
	  long err;

      while(flag==0){
      	   z++;
      	   //cout<<z;
           x=target*pow(N,z);
           if(fabs(target-(long double)x/pow(N,z))<epsilon){
                err=fabs(target-target*pow(N,z));
                flag=1;
           }
      }
      return z;

}

int main(){
	long double arr[100];
    long double ct,epsilon,err,ms,rms,avg_rms=0.0;
    int num,t,N,max_z=0,avg_z=0;
    //freopen ("test.txt","r",stdin);
    cin>>N>>epsilon;
    cin>>num;
 // for(int p=2;p<20;p++){
   // N=p;
    avg_rms=0.0;
    avg_z=0;
    ms=0.0;
    //cout<<"N="<<N<<"  ";
    for(int i=0;i<num;i++){
         cin>>t;
         int temp;
         ms=0.0;
         max_z=0;
         for(int k=0;k<t;k++){
              	  cin>>arr[k];
                  temp=error(N,epsilon,arr[k]);    
                  if(temp>max_z){
                  	max_z=temp;
                  }        
                  
         }
         //cout<<"max_z="<<max_z<<" "<<endl;
         for(int k=0;k<t;k++){
         	  int x=arr[k]*pow(N,max_z);
         	  //cout<<fabs((long double)x/pow(N,max_z)-arr[k])<<endl;
            ms+=pow(arr[k]-(double)x/pow(N,max_z),2);
            //ms+=fabs(arr[k]-(long double)x/pow(N,max_z));
         }
         ms=(long double)ms/t;
         rms=sqrt(ms);
         avg_rms+=ms;
         avg_z+=max_z;
    }
    cout<<" average rms="<<(long double)avg_rms/(num)<<" average z="<<avg_z/num<<endl;
 // }
	




}