#include <stdexcept>
#include <string>

using namespace std;

struct Result {
	int solved;
	int strikes;
	int balls;
};

class Baseball {
public:
	explicit Baseball(const string& question)
		: question(question) {
	}

	Result guess(string guessNumber) {
		assertIllegalArgument(guessNumber);

		if (guessNumber == question) {
			return { true, 3, 0 };
		}

		int solved = false;
		int strikes = getStrikeCount(guessNumber);
		int balls = getBallCount(guessNumber);
		return { solved, strikes, balls };
	}

private:
	void assertIllegalArgument(string guessNumber) {
		if (guessNumber == "") {
			throw std::invalid_argument("���� �־����");
		}
		if (guessNumber.length() != 3) {
			throw std::invalid_argument("�ڸ��� ����");
		}
		if (isIncludeChar(guessNumber)) {
			throw std::invalid_argument("���ڷθ� �����Ǿ� ���� ����");
		}
		if (isDuplicatedNumber(guessNumber)) {
			throw std::invalid_argument("�ߺ��� ����");
		}
	}

	bool isIncludeChar(const string& guessNumber) {
		for (char ch : guessNumber) {
			if (ch >= '0' && ch <= '9') continue;
			return true;
		}
		return false;
	}

	bool isDuplicatedNumber(const string& guessNumber) {
		return guessNumber[0] == guessNumber[1] ||
			   guessNumber[0] == guessNumber[2] ||
			   guessNumber[1] == guessNumber[2];
	}

	int getStrikeCount(string guessNumber)
	{
		int result = 0;
		for (int i = 0; i < 3; i++) {
			int index = question.find(guessNumber[i]);
			if (index == -1) continue;
			if (index != i) continue;
			result++;
		}
		return result;
	}

	int getBallCount(string guessNumber)
	{
		int result = 0;
		for (int i = 0; i < 3; i++) {
			int index = question.find(guessNumber[i]);
			if (index == -1) continue;
			if (index == i) continue;
			result++;
		}
		return result;
	}

	string question;
};