#ifndef stream_h
#define stream_h

#define BUFFERSIZE 300

class Queue {
private:
	int start;
	int end;
	int buffer[BUFFERSIZE];
public:
	Queue();
	bool push(int data);
	bool pop(int& result);
	int length();
	bool isFull();
};


#endif
