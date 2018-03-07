#include <iostream>

#include "mbus/Mbus.hpp"

using namespace m4m;

int main(int argc, const char* argv[]) {
	const char* device = argc < 2 ? "/dev/ttyACM0" : argv[1];
	const char* address = argc < 3 ? "1" : argv[2];

	mbus::Mbus mbus;
	mbus.openSerial(device, 9600);

	std::cout << mbus.get(address);

	return 0;
}
