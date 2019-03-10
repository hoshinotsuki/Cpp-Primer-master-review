
#include "stdafx.h"
#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


//每种类型内置空间大小
namespace _04_28
{
	void main()
	{
		cout << "bool\t\tis " << sizeof(bool) << "bytes." << endl;
		cout << "char\t\tis " << sizeof(char) << "bytes." << endl;
		cout << "wchar_t\t\tis " << sizeof(wchar_t) << "bytes." << endl;
		cout << "char16_t\tis " << sizeof(char16_t) << "bytes." << endl;
		cout << "char32_t\tis " << sizeof(char32_t) << "bytes." << endl;
		cout << "short\t\tis " << sizeof(short) << "bytes." << endl;
		cout << "int\t\tis " << sizeof(int) << "bytes." << endl;
		cout << "long\t\tis " << sizeof(long) << "bytes." << endl;
		cout << "long long\tis " << sizeof(long long) << "bytes." << endl;
		cout << "float\t\tis " << sizeof(float) << "bytes." << endl;
		cout << "double\t\tis " << sizeof(double) << "bytes." << endl;
		cout << "long double\tis " << sizeof(long double) << "bytes." << endl;
		cout << endl;
		 
	}
}


namespace _04_29
{
	void main() 
	{
		int x[10];   int *p = x;
		cout << sizeof(x) / sizeof(*x) << endl;//10/1=10数组所占内存大小/数组每个元素所占内存的大小=数组的容量
		cout << sizeof(p) / sizeof(*p) << endl;//4/4=1 指针的大小/指针所指内容类型int的大小
		 
	}
}


 
int main()
{
	//_04_28::main();
	//_04_29::main();
}

