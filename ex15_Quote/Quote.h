#pragma once
#ifndef QUOTE_H
#define QUOTE_H

#include <memory> //动态分配内存 
#include <iostream>
#include <string>
#include <cstddef> //原作为 <stddef.h> 存在于 C 标准库。是工具库
#include <utility> //通用工具
using namespace std;

class Quote {
	/*
	** istream&：必须是非常量，因为本操作就是向流读出数据，其状态会改变；
	** Quote& ：必须是非常量，因为本操作就是向此对象写入数据，此对象值会改变；
	*/
	friend istream& operator >> (istream&, Quote&);


	/*
	**ostream& ：必须是非常量，因为本操作就是向流写入数据，其状态会改变；
	**const Quote& ：引用是因为避免赋值实参；常量是因为通常打印对象不会改变对象本身的值；
	*/
	friend ostream& operator<<(ostream&, const Quote&);

public:

	/*这种传递中的代码使用以下变量来控制编译；
	**变量：IN_CLASS_INITS/DEFAULT_FCNS；对应C++作用：类初始状态设置/default(默认)；
	*/
#if defined(IN_CLASS_INITS) && defined(DEFAULT_FCNS)
	//若定义类初始值设置及默认值，则定义默认构造函数,不接受任何实参；
	Quote() = default;
#else
	/*若未定义类初始值及默认值，则定义构造函数，函数体空；
	**构造函数初始列表为新创建的数据成员price初始化，对应初始化值为 0.0；
	*/
	Quote() : price(0.0) { }
#endif // !defined(IN_CLASS_INITS) && defined(DEFAULT_FCNS)


	//初始化构造函数
	Quote(const string &book, double sales_price) :
		bookNo(book), price(sales_price) { }

	//虚析构函数，动态绑定，派生类的资源释放，防止内存泄漏。
#ifdef DEFAULT_FCNS
	virtual ~Quote() = default;
#else
	virtual ~Quote() {	}
#endif // DEFAULT_FCNS

	//const fun。 因为bookNo被期望是const obj，所以只能被const fun调用，必须定义为const fun，否则报错。
	string isbn() const
	{
		return bookNo;
	}

	//虚函数。将在派生类中重写，根据书的数量，采取不同的折扣算法。
	//因为price（定价）也是const obj,不会被改。所以定义为const fun。
	virtual double net_price(size_t n) const
	{
		return n*price;
	}//虚函数返回动态分配的自身副本 ：动态绑定

	//虚函数，分别显示每个类的数据成员。
	virtual void debug()
	{
		cout << "bookNo=" << bookNo << " price= " << price << endl;
	}

private:
	const string bookNo;//书号，被期望是const obj

protected://普通状态不打折的价格

#ifndef IN_CLASS_INITS
	const double price = 0.0;
#else
	const double price;
#endif // !IN_CLASS_INITS

	//声明打印总价函数
	double print_total(ostream&, const Quote&, size_t);
};


//基本折扣战略（大于某数量才打折
class Bulk_quote : public Quote {
public:

	//派生类默认构造函数 
#if defined(IN_CLASS_INITS) && defined(DEFAULT_FCNS) 
	Bulk_quote() = default;
#else
	Bulk_quote() : min_qty(0), discount(0.0) { }
#endif

	//派生类自定义构造函数
	Bulk_quote(const string& book, double price, size_t qty, double disc) :
		Quote(book, price),
		min_qty(qty), discount(disc) { }

	//虚函数重载
	double net_price(size_t cnt) const override
	{
		if (cnt >= min_qty)
			return cnt*(1 - discount) *price;//继承父类成员变量
		else
			return cnt*price;
	}

	//虚函数，派生类不能直接访问基类的private成员，要通过基类的函数来访问。
	virtual void debug()
	{
		Quote::debug();//调用基类的debug()显示private变量bookNo
		cout << "min_qty=" << min_qty << " discount=" << discount << endl;
	}

private:
	//私有属性。数量。折扣。
	size_t min_qty = 2;
	double discount = 0.5;
};

//数量受限的折扣战略(小于某数量才打折
class Limited_quote :public Quote {
public:

	//构造函数
#if defined(IN_CLASS_INITS) && defined(DEFAULT_FCNS) 
	Limited_quote() = default;
#else
	Limited_quote() :max_qty(0), discount(0.0) { }
#endif

	//自定义默认函数
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

	//15.11 虚函数，派生类不能直接访问基类的private成员，要通过基类的函数来访问。
	virtual void debug()
	{
		Quote::debug();//调用基类的debug()显示private变量bookNo
		cout << "max_qty=" << max_qty << " discount=" << discount << endl;
	}
private:
	//私有熟悉。数量。折扣。
	size_t max_qty;
	double discount;
};

 
#endif//QUOTE_H 