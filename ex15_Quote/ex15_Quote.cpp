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
	Quote data1("sdfds", 2);
	Quote data2("fd", 1);
	Bulk_quote data3("data3", 4.0, 2, 0.5);
	Limited_quote data4("limited", 10, 2, 0.7);
	double ret = print_total(data4, 4);
	return 0;
}
