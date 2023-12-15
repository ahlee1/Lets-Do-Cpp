#include <numeric>
#include <vector>
#include <iostream>
#include <algorithm>

std::vector<uint64_t> SingleThreadVector(uint64_t x) {
	std::vector<uint64_t> res;
	for (uint64_t i = 0; i < x; i++) {
		res.push_back(i);
	}

	return res;
}

bool ValidateVec(std::vector<uint64_t> v) {
	for (uint64_t i = 0; i < v.size()-1; i++) {
		if ((v[i] + 1) != v[i+1]) {
			return false;
		}
	}
	return true;
}

int main() {
	
	std::vector<uint64_t> svec = SingleThreadVector(100000000);
	std::cout << ValidateVec(svec);
}