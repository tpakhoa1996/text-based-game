#include "stdafx.h"
#include "Time.h"


int Time::timer;

Time::Time(int timeTaken) : timeTaken(timeTaken) {}

bool Time::consume() {
	bool success = false;
	if (timeTaken <= timer) {
		timer -= timeTaken;
		timeTaken = 0;
		success = true;
	} 
	return success;
}

bool Time::checkLimit() {
	return timeTaken <= timer;
}

int Time::getTime() {
	return timeTaken;
}

bool Time::isTimeout() {
	return timer <= 0;
}

void Time::setTimer(int newTimer) {
	timer = newTimer;
}

int Time::getRemainingTime() {
	return timer;
}

Time* Time::clone() {
	return new Time(timeTaken);
}

Time::~Time() {}
