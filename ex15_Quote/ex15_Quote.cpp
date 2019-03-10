// ex15_Quote.cpp : 定义控制台应用程序的入口点。
//
 
#include "stdafx.h"
#include "Quote.h"

//计算总价函数 
double print_total(const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	cout << "ISBN:" << item.isbn()
		<< "#sold:" << n << "total due:" << ret << endl;
	return ret;
}



int main()
{
	double ret;

	cout << "\n15.3 限购：" << endl;
	Quote data2("fd", 1);
	ret = print_total(data2, 2);

	cout << "\n15.5 满减：" << endl;
	Bulk_quote data3("data3", 4.0, 2, 0.5);
	ret = print_total(data3, 5);

	cout << "\n15.7 限购：" << endl;
	Limited_quote data4("limited", 10, 2, 0.7);
	ret = print_total(data4, 4);

	cout << "\n15.11虚函数构造练习：" << endl;
	data3.debug();//虚函数
	return 0;
}
