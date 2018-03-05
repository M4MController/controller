//
// Created by ed on 3/6/18.
//

#include "exceptions.hpp"

using namespace m4m::mbus;

Exception::Exception(const char* msg)
	: msg(msg) {

}

const char* Exception::what() const noexcept {
	return msg;
}
