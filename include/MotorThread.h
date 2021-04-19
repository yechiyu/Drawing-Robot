#ifndef MOTOR_THREAD_H
#define MOTOR_THREAD_H

#include "CppThread.h"

class MotorThread : public CppThread {

public:
	MotorThread(int _offset) {
		offset = _offset;
	}

private:
	void run();

private:
	int offset;
};

#endif