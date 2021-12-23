#pragma once
#include <cstdlib>

class Allocator {
public:
	void* allocate(const unsigned int& sizeMemory) {
		return (unsigned char*)malloc(sizeMemory);
	}

	void deallocate(void* ptr) {
		free(ptr);
	}
};
