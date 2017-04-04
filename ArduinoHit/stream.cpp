class queue {
private:
	int start;
	int end;
	int length;
	int* buffer;
public:
	queue(int size) {
		buffer = (int*)mallac(size * sizeof(int));
		start = 0;
		end = 0;
	}

	bool push(int data) {
		if ((start + 1) % length == end) {  //catch end case
			buffer[start] = data;
			start = (start + 1) % length;
			return true;
		}
		else {
			//error
			return false;
		}
	}

	int pop(int data) {
		if ((end + 1) % length == start) {  //catch end case
			int result = buffer[end];
			end = (end + 1) % length;
			return result;
		}
		else {
			//error
			return 0;
		}
	}
};