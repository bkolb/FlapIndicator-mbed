#pragma once

#include <cstddef>
#include <cstdint>

#define BUFFER_SIZE 32

struct Msg {
	char msgBuffer[BUFFER_SIZE];
	uint8_t pos;
};
