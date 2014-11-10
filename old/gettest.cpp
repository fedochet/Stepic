#include <iostream>

using namespace std;

long clp2(long x) { 
 //Ищет и возвращает ближайшую к x сверху степень двойки
 //Вообще говоря, предполагает, что число 32-разрядное
 x--;
 cout<<oct<<x<<endl;
 for (int p=1; p<32; p<<=1)
 {
    x |= (x<< p);
    cout<<oct<<x<<endl;
 }; 
 return ++x;
}

int main()
{
	
	cout<<dec<<clp2()<<endl;
	return 0;
}