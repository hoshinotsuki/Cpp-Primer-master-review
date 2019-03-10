// sort.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//STD::sort���÷�
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>

int main()
{
	std::array<int, 10> s = { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };

	// ��Ĭ�ϵ� operator< ����
	std::sort(s.begin(), s.end());
	for (auto a : s) {
		std::cout << a << " ";
	}
	std::cout << '\n';

	// �ñ�׼��ȽϺ����������򡣴Ӵ�С
	std::sort(s.begin(), s.end(), std::greater<int>());
	for (auto a : s) {
		std::cout << a << " ";
	}
	std::cout << '\n';

	// ���Զ��庯����������
	struct {
		bool operator()(int a, int b) const
		{
			return a < b;
		}
	} customLess;
	std::sort(s.begin(), s.end(), customLess);
	for (auto a : s) {
		std::cout << a << " ";
	}
	std::cout << '\n';

	// �� lambda ���ʽ����
	std::sort(s.begin(), s.end(), [](int a, int b) {
		return b < a;
	});
	for (auto a : s) {
		std::cout << a << " ";
	}
	std::cout << '\n';
}