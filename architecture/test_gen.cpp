#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
	       // string str="N"+to_string(n)+"/n"+to_string(n)+"_d"+to_string(i)+"/Test_d"+to_string(i)+"_n"+to_string(n)+"_"+to_string(arr[j])+".txt";
            freopen ("test_20.txt","w",stdout);

            //string str1="5000 "+to_string(i)+" "+to_string(n)+"\n";   
            cout<<"5000"<<endl;	
            srand(time(NULL));
            for(int i=0;i<5000;i++){
               cout<<20<<" ";
               for(int k=0;k<10;k++){ 

                    //decimalToOctal(rand() % 63 + 1);
                   //cout<<(float)(decimalToBase4(rand() % 63 + 1))/1000;
               	   //cout<<(float)(decimalToOctal(rand() % 63 + 1))/100;
               	   cout<<(double)((rand() % 99999) +1)/100000;
                   cout<<" ";
                }
                cout<<endl;
              
            }

}