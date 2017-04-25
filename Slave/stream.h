#pragma once
#include <stdint.h>
//#ifndef stream_h
//#define stream_h

#define BUFFERSIZE 100

class Queue {
private:
	int headIndex;
	int tailIndex;
	unsigned long  buffer[BUFFERSIZE];
public:
	Queue();
	bool push(unsigned long data);
	bool pop(unsigned long& result);
	int length();
	bool isFull();
};


//#endif
