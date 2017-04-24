const int numOfPatterns = 2;
const int maxLength = 45;

const int lengths[numOfPatterns] PROGMEM = { 45, 45 };
const int patterns[numOfPatterns][maxLength] PROGMEM = {
	{ 1, 0, 65, 1, 1, 15, 2, 0, 65, 2, 1, 15, 1, 0, 20, 2, 0, 45, 1, 1, 20, 2, 1, 35, 1, 0, 20, 2, 0, 10, 1, 0, 55, 2, 1, 10, 1, 1, 35, 2, 0, 65, 2, 1, 0 },
	{ 1, 0, 65, 1, 1, 15, 2, 0, 65, 2, 1, 15, 1, 0, 20, 2, 0, 45, 1, 1, 20, 2, 1, 35, 1, 0, 20, 2, 0, 10, 1, 0, 55, 2, 1, 10, 1, 1, 35, 2, 0, 65, 2, 1, 0 }
};
