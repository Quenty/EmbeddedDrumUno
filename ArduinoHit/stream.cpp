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

	int Queue::pop() {
		if ((end + 1) % BUFFERSIZE == start) {  //catch end case
			int result = buffer[end];
			end = (end + 1) % BUFFERSIZE;
			return result;
		}
		else {
			//error
			return 0;
		}
	}

