#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>


using namespace std;

int decimalToBase4(int decimalNumber)
{
    int rem, i = 1, octalNumber = 0;
    while (decimalNumber != 0)
    {
        rem = decimalNumber % 4;
        decimalNumber /= 4;
        octalNumber += rem * i;
        i *= 10;
    }
    return octalNumber;
}

int decimalToOctal(int decimalNumber)
{
    int rem, i = 1, octalNumber = 0;
    while (decimalNumber != 0)
    {
        rem = decimalNumber % 8;
        decimalNumber /= 8;
        octalNumber += rem * i;
        i *= 10;
    }
    return octalNumber;
}

int main(){
    int n;
    cin>>n;
    int arr[]={2,5,10,20,50,100};
    for(int i=6;i<=8;i++){
        for(int j=1;j<=6;j++){
            string str="N"+to_string(n)+"/n"+to_string(n)+"_d"+to_string(i)+"/Test_d"+to_string(i)+"_n"+to_string(n)+"_"+to_string(arr[j])+".txt";
            freopen (str.c_str(),"w",stdout);

            string str1="5000 "+to_string(i)+" "+to_string(n)+"\n";   
            cout<<str1;	

            srand(time(0));

            for(int l=0;i<5000;l++){
               cout<<arr[j]<<" ";
               for(int k=0;k<arr[j];k++){ 
                    //cout<<"nis"<<endl;
                    //decimalToOctal(rand() % 63 + 1);
                   //cout<<(float)(decimalToBase4(rand() % 63 + 1))/1000;
               	   //cout<<(float)(decimalToOctal(rand() % 63 + 1))/100;
               	   //cout<<rand() % ((int)pow((float)n,(float)i) -1) + 1;
                   
                   cout<<(rand() % ((1<<i)-1) )+1;
                   cout<<" ";
                }
                cout<<endl;
              
            }
        }
    }
}