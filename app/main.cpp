#include <iostream>

#include <thoth/matrix.h>
#include <vector>
#include <algorithm>
#include <chrono>


int main()
{
	thoth::Matrix<float> m({ 3,3 }, { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
	std::cout << "OKAY" << std::endl;

	std::vector<int> b{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

	const int s = 5;

	auto s1 = std::chrono::high_resolution_clock::now();
	m += s;
	auto e1 = std::chrono::high_resolution_clock::now();

	auto s2 = std::chrono::high_resolution_clock::now();
	for (int j = 0; j < b.size(); ++j)
	{
		b[j] += s;
	}
	auto e2 = std::chrono::high_resolution_clock::now();

	auto t1 = e1 - s1;
	auto t2 = e2 - s2;

	std::cout << "for_each " << std::chrono::duration_cast<std::chrono::nanoseconds>(t1).count() << std::endl;

	std::cout << "raw " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2).count() << std::endl;

	thoth::Matrix<float> f = thoth::Matrix<float>::Like(m);

	std::cout << (m.Shape() == f.Shape()) << std::endl;

	return 0;
}
