//
// Created by ed on 3/6/18.
//

#ifndef CONTROLLER_EXCEPTIONS_HPP
#define CONTROLLER_EXCEPTIONS_HPP

#include <exception>

namespace m4m {
namespace mbus {
class Exception : public std::exception {
public:
	explicit Exception(const char* msg);

	const char* what() const noexcept override;

private:
	const char* const msg;
};

} //mbus
} //m4m

#endif //CONTROLLER_EXCEPTIONS_HPP
