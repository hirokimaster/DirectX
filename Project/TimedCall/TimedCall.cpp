#include "TimedCall.h"

void TimedCall::Update()
{
	if (comp_) {
		return;
	}

	--time_;

	if (time_ <= 0) {
		comp_ = true;
	}
}
