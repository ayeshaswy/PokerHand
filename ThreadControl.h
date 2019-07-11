#pragma once

#include <thread>
#include <string>
#include <functional>

class ThreadControl {
public:
	std::thread threadObj;

	ThreadControl(std::function<void()> threadFunc) {
		threadObj = std::thread(threadFunc);
	}

	~ThreadControl() {
		threadObj.join();
	}
};