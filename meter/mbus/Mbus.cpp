//
// Created by ed on 3/6/18.
//

#include "Mbus.hpp"

using namespace m4m::mbus;

Mbus::Mbus() {
	connected = false;
	serial = true;
	handle = nullptr;
}

Mbus::~Mbus() {
	if (connected) {
		mbus_disconnect(handle);
	}
	if (handle) {
		mbus_context_free(handle);
	}
}

bool Mbus::openSerial(const char* port, long boudrate) {
	serial = true;

	switch (boudrate) {
		case 300:
		case 600:
		case 1200:
		case 2400:
		case 4800:
		case 9600:
		case 19200:
		case 38400:
			break;
		default:
			boudrate = 2400;
			break;
	}

	if (!connected) {
		if (!(handle = mbus_context_serial(port))) {
			return false;
		}
		if (mbus_connect(handle) == -1) {
			mbus_context_free(handle);
			handle = nullptr;
			return false;
		}
		if (mbus_serial_set_baudrate(handle, boudrate) == -1) {
			mbus_disconnect(handle);
			mbus_context_free(handle);
			handle = nullptr;
			return false;
		}
		connected = true;
		return true;
	}
	return false;
}

bool Mbus::close() {
	if (connected) {
		mbus_disconnect(handle);
		mbus_context_free(handle);

		handle = nullptr;
		connected = false;

		return true;
	} else {
		return false;
	}
}

static bool init_slaves(mbus_handle* handle) {
	if (mbus_send_ping_frame(handle, MBUS_ADDRESS_NETWORK_LAYER, 1) == -1) {
		return false;
	}

	return mbus_send_ping_frame(handle, MBUS_ADDRESS_NETWORK_LAYER, 1) != -1;
}

std::string Mbus::get(const char* address_str) {
	mbus_frame reply;
	mbus_frame_data reply_data;
	int address;

	std::memset((void*) &reply, 0, sizeof(mbus_frame));
	std::memset((void*) &reply_data, 0, sizeof(mbus_frame_data));

	if (!init_slaves(handle)) {
		mbus_disconnect(handle);
		mbus_context_free(handle);
		throw Exception("Failed to init slaves.");
	}

	if (mbus_is_secondary_address(address_str)) {
		// secondary addressing

		int ret = mbus_select_secondary_address(handle, address_str);

		if (ret == MBUS_PROBE_COLLISION) {
			throw Exception("The address mask [%s] matches more than one device."); // address_str
		} else if (ret == MBUS_PROBE_NOTHING) {
			throw Exception("The selected secondary address does not match any device [%s]."); // address_str
		} else if (ret == MBUS_PROBE_ERROR) {
			throw Exception("Failed to select secondary address [%s]."); // address_str
		}

		address = MBUS_ADDRESS_NETWORK_LAYER;
	} else {
		// primary addressing
		address = std::atoi(address_str);
	}

	if (mbus_send_request_frame(handle, address) == -1) {
		throw Exception("Failed to send M-Bus request frame[%s]."); // address_str
	}

	if (mbus_recv_frame(handle, &reply) != MBUS_RECV_RESULT_OK) {
		throw Exception("Failed to receive M-Bus response frame[%s]."); // address_str
	}

	// parse data
	if (mbus_frame_data_parse(&reply, &reply_data) == -1) {
		throw Exception("M-bus data parse error [%s]."); // address_str
	}

	// generate JSON and print to standard output
	auto a = mbus_frame_data_json(&reply_data);
	if (a == nullptr) {
		throw Exception("Failed to generate JSON representation of MBUS frame [%s]."); // address_str
	}

	// manual free
	if (reply_data.data_var.record) {
		mbus_data_record_free(reply_data.data_var.record);
	}

	std::string data = a;
	std::free(a); // it was create by C code
	return data;
}
