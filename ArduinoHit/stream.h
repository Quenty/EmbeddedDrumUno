#pragma once
#include <stdint.h>
//#ifndef stream_h
//#define stream_h

#define BUFFERSIZE 300

class Queue {
private:
	int headIndex;
	int tailIndex;
	uint8_t buffer[BUFFERSIZE];
public:
	Queue();
	bool push(uint8_t data);
	bool pop(uint8_t& result);
	int length();
	bool isFull();
};


//#endif
