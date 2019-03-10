// ex15_Quote.cpp : �������̨Ӧ�ó������ڵ㡣
//
 
#include "stdafx.h"
#include "Quote.h"

//�����ܼۺ��� 
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

	cout << "\n15.3 �޹���" << endl;
	Quote data2("fd", 1);
	ret = print_total(data2, 2);

	cout << "\n15.5 ������" << endl;
	Bulk_quote data3("data3", 4.0, 2, 0.5);
	ret = print_total(data3, 5);

	cout << "\n15.7 �޹���" << endl;
	Limited_quote data4("limited", 10, 2, 0.7);
	ret = print_total(data4, 4);

	cout << "\n15.11�麯��������ϰ��" << endl;
	data3.debug();//�麯��
	return 0;
}
