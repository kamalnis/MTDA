#include<iostream>
#include<cmath>

using namespace std;
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

int main(){
	int x,n,d;
	int total_time=0,total_r=0,total_b=0,total_w=0;
	cin>>n>>d;
    x=pow(n,d);
	for(int i=1;i<x;i++){
	     int r,b,w,t;
         int num=decimalToBasek(i,n);
         r = num%10;
         b= n-r;
         num=num/10; 
         t=1;
         while(num!=0){
            r += num%10;
            b += n - num%10 - 1;
            t++;
            num=num/10;
         } 
         w = r+b-n;
       
         total_time+=t;
         total_r+=r;
         total_b+=b;
         total_w+=w;

	}
    cout<<total_time/(x-1)<<" "<<total_r/(x-1)<<" "<<total_b/(x-1)<<" "<<total_w/(x-1);


}