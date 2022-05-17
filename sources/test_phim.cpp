#include<iostream>
#include<conio.h>
using namespace std;
int main()
{
	int key;
	while(true)
	{
		key = getch();
		cout << "ban vua an: " << key << endl;
		if(key == 27) return 0;
	}
	return 0;
}
