#define BUFFERSIZE 300

class Queue {
private:
	int start;
	int end;
	int buffer[BUFFERSIZE];
public:
	Queue();
	bool push(int data);
	int pop();
};
