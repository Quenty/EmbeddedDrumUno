#pragma once
#include <stdint.h>
//#ifndef stream_h
//#define stream_h

#define BUFFERSIZE 100

class Queue {
private:
	int headIndex;
	int tailIndex;
	uint16_t buffer[BUFFERSIZE];
public:
	Queue();
	bool push(uint16_t data);
	bool pop(uint16_t& result);
	int length();
	bool isFull();
};


//#endif
