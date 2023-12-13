#pragma once
#include <functional>

class TimedCall{
public:
	TimedCall();

	void Update();

	bool IsFinished() { return comp_; }

private:

	//残り時間
	uint32_t time_;
	// 完了フラグ
	bool comp_ = false;

};

