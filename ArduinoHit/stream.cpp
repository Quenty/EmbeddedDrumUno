#include "stream.h"

Queue::Queue() {
	headIndex = 0;
	tailIndex = 0;
}

bool Queue::push(int data) {
	if ((headIndex + 1) % BUFFERSIZE != tailIndex) {  //catch end case
		buffer[headIndex] = data;
		headIndex = (headIndex + 1) % BUFFERSIZE;
		return true;
	}
	else {
		//error
		return false;
	}
}

bool Queue::pop(int& result) {
	if ((tailIndex) % BUFFERSIZE != headIndex) {  //catch end case
		result = buffer[tailIndex];
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
	return length() != BUFFERSIZE;
}

