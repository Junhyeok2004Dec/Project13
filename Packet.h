#pragma once

#include "State.h"

typedef struct PacketHeader {

	size_t header;
	size_t size;
	size_t checksum;
	size_t packet_type;
	size_t packet_id;

};
typedef struct Packet {
	
	PacketHeader* header;

	size_t size;
	size_t parity_bit;

};


