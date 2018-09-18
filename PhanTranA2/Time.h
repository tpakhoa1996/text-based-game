#pragma once
class Time {
public:
	static void setTimer(int);
	Time(int);
	~Time();
	bool consume();
	bool checkLimit();
	int getTime();
	static int getRemainingTime();
	static bool isTimeout();
	Time* clone();
private:
	static int timer;
	int timeTaken;
};

