#include<iostream>
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
	freopen ("Test_d10_n2_100.txt","w",stdout);

    cout<<"5000 10 2\n";
    srand(time(NULL));
	for(int i=0;i<5000;i++){
       cout<<"100 ";
	   for(int j=0;j<100;j++){

            //decimalToOctal(rand() % 63 + 1);
           //cout<<(float)(decimalToBase4(rand() % 63 + 1))/1000;
	   	   //cout<<(float)(decimalToOctal(rand() % 63 + 1))/100;
	   	   cout<<rand() % 1023 + 1;
           cout<<" ";
        }
        cout<<endl;

	}
}
