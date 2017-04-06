#include "stream.h"

Queue::Queue() {
	headIndex = 0;
	tailIndex = 0;
}

bool Queue::push(uint8_t data) {
	if ((headIndex + 1) % BUFFERSIZE != tailIndex) {  //catch end case
		buffer[headIndex * sizeof(uint8_t)] = data;
		headIndex = (headIndex + 1) % BUFFERSIZE;
		return true;
	}
	else {
		//error
		return false;
	}
}

bool Queue::pop(uint8_t& result) {
	if ((tailIndex) % BUFFERSIZE != headIndex) {  //catch end case
		result = buffer[tailIndex * sizeof(uint8_t)];
		tailIndex = (tailIndex + 1) % BUFFERSIZE;
		return true;
	}
	else {
		//error
		return false;
	}
}

int Queue::length() {
	return ((headIndex - tailIndex) + BUFFERSIZE) % BUFFERSIZE;
}

bool Queue::isFull() {
	return length() < BUFFERSIZE;
}

