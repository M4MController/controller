//
// Created by ed on 3/6/18.
//

#ifndef CONTROLLER_MBUS_HPP
#define CONTROLLER_MBUS_HPP

#include <string>
#include <exception>
#include <cstring>

#include <mbus/mbus.h>

#include "exceptions.hpp"

namespace m4m {
namespace mbus {
class Mbus {
public:
	explicit Mbus();
	~Mbus();

	bool openSerial(const char* port, long boudrate);
	std::string get(const char* address_str);
	bool close();

private:
	mbus_handle* handle;
	bool connected;
	bool serial;
};

} //mbus
} //m4m

#endif //CONTROLLER_MBUS_HPP
