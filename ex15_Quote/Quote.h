#pragma once
#ifndef QUOTE_H
#define QUOTE_H

#include <memory> //��̬�����ڴ� 
#include <iostream>
#include <string>
#include <cstddef> //ԭ��Ϊ <stddef.h> ������ C ��׼�⡣�ǹ��߿�
#include <utility> //ͨ�ù���
using namespace std;

class Quote {
	/*
	** istream&�������Ƿǳ�������Ϊ���������������������ݣ���״̬��ı䣻
	** Quote& �������Ƿǳ�������Ϊ������������˶���д�����ݣ��˶���ֵ��ı䣻
	*/
	friend istream& operator >> (istream&, Quote&);


	/*
	**ostream& �������Ƿǳ�������Ϊ��������������д�����ݣ���״̬��ı䣻
	**const Quote& ����������Ϊ���⸳ֵʵ�Σ���������Ϊͨ����ӡ���󲻻�ı�������ֵ��
	*/
	friend ostream& operator<<(ostream&, const Quote&);

public:

	/*���ִ����еĴ���ʹ�����±��������Ʊ��룻
	**������IN_CLASS_INITS/DEFAULT_FCNS����ӦC++���ã����ʼ״̬����/default(Ĭ��)��
	*/
#if defined(IN_CLASS_INITS) && defined(DEFAULT_FCNS)
	//���������ʼֵ���ü�Ĭ��ֵ������Ĭ�Ϲ��캯��,�������κ�ʵ�Σ�
	Quote() = default;
#else
	/*��δ�������ʼֵ��Ĭ��ֵ�����幹�캯����������գ�
	**���캯����ʼ�б�Ϊ�´��������ݳ�Աprice��ʼ������Ӧ��ʼ��ֵΪ 0.0��
	*/
	Quote() : price(0.0) { }
#endif // !defined(IN_CLASS_INITS) && defined(DEFAULT_FCNS)


	//��ʼ�����캯��
	Quote(const string &book, double sales_price) :
		bookNo(book), price(sales_price) { }

	//��������������̬�󶨣����������Դ�ͷţ���ֹ�ڴ�й©��
#ifdef DEFAULT_FCNS
	virtual ~Quote() = default;
#else
	virtual ~Quote() {	}
#endif // DEFAULT_FCNS

	//const fun�� ��ΪbookNo��������const obj������ֻ�ܱ�const fun���ã����붨��Ϊconst fun�����򱨴�
	string isbn() const
	{
		return bookNo;
	}

	//�麯������������������д�����������������ȡ��ͬ���ۿ��㷨��
	//��Ϊprice�����ۣ�Ҳ��const obj,���ᱻ�ġ����Զ���Ϊconst fun��
	virtual double net_price(size_t n) const
	{
		return n*price;
	}//�麯�����ض�̬����������� ����̬��

	//�麯�����ֱ���ʾÿ��������ݳ�Ա��
	virtual void debug()
	{
		cout << "bookNo=" << bookNo << " price= " << price << endl;
	}

private:
	const string bookNo;//��ţ���������const obj

protected://��ͨ״̬�����۵ļ۸�

#ifndef IN_CLASS_INITS
	const double price = 0.0;
#else
	const double price;
#endif // !IN_CLASS_INITS

	//������ӡ�ܼۺ���
	double print_total(ostream&, const Quote&, size_t);
};


//�����ۿ�ս�ԣ�����ĳ�����Ŵ���
class Bulk_quote : public Quote {
public:

	//������Ĭ�Ϲ��캯�� 
#if defined(IN_CLASS_INITS) && defined(DEFAULT_FCNS) 
	Bulk_quote() = default;
#else
	Bulk_quote() : min_qty(0), discount(0.0) { }
#endif

	//�������Զ��幹�캯��
	Bulk_quote(const string& book, double price, size_t qty, double disc) :
		Quote(book, price),
		min_qty(qty), discount(disc) { }

	//�麯������
	double net_price(size_t cnt) const override
	{
		if (cnt >= min_qty)
			return cnt*(1 - discount) *price;//�̳и����Ա����
		else
			return cnt*price;
	}

	//�麯���������಻��ֱ�ӷ��ʻ����private��Ա��Ҫͨ������ĺ��������ʡ�
	virtual void debug()
	{
		Quote::debug();//���û����debug()��ʾprivate����bookNo
		cout << "min_qty=" << min_qty << " discount=" << discount << endl;
	}

private:
	//˽�����ԡ��������ۿۡ�
	size_t min_qty = 2;
	double discount = 0.5;
};

//�������޵��ۿ�ս��(С��ĳ�����Ŵ���
class Limited_quote :public Quote {
public:

	//���캯��
#if defined(IN_CLASS_INITS) && defined(DEFAULT_FCNS) 
	Limited_quote() = default;
#else
	Limited_quote() :max_qty(0), discount(0.0) { }
#endif

	//�Զ���Ĭ�Ϻ���
	Limited_quote(const string&book, double price, size_t cnt, double dis) :
		Quote(book, price), max_qty(cnt), discount(dis)
	{ }

	//override
	double net_price(size_t cnt) const override
	{
		if (cnt <= max_qty)
			return cnt*(1 - discount)*price;
		else
			return max_qty*(1 - discount)*price + (cnt - max_qty)*price;
	}

	//15.11 �麯���������಻��ֱ�ӷ��ʻ����private��Ա��Ҫͨ������ĺ��������ʡ�
	virtual void debug()
	{
		Quote::debug();//���û����debug()��ʾprivate����bookNo
		cout << "max_qty=" << max_qty << " discount=" << discount << endl;
	}
private:
	//˽����Ϥ���������ۿۡ�
	size_t max_qty;
	double discount;
};

 
#endif//QUOTE_H 