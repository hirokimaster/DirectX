#include "TimedCall.h"

TimedCall::TimedCall(std::function<void(void)> func, uint32_t time) : func_(func), time_(time)
{
}

void TimedCall::Update()
{
	if (comp_) {	
		return;
	}

	--time_;

	if (time_ <= 0) {
		comp_ = true;
		func_();
	}
}
