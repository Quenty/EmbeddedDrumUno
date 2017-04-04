#include "stream.h"

Queue::Queue() {
	start = 0;
	end = 0;
}

bool Queue::push(int data) {
	if ((start + 1) % BUFFERSIZE == end) {  //catch end case
		buffer[start] = data;
		start = (start + 1) % BUFFERSIZE;
		return true;
	}
	else {
		//error
		return false;
	}
}

bool Queue::pop(int& result) {
	if ((end + 1) % BUFFERSIZE == start) {  //catch end case
		result = buffer[end];
		end = (end + 1) % BUFFERSIZE;
		return true;
	}
	else {
		//error
		return false;
	}
}

int Queue::length() {
	return ((start - end) + BUFFERSIZE) % BUFFERSIZE;
}

bool Queue::isFull() {
	return length() != BUFFERSIZE;
}

