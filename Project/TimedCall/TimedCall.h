#pragma once
#include <functional>

class TimedCall{
public:
	TimedCall(std::function<void(void)> func, uint32_t time);

	void Update();

	bool IsFinished() { return comp_; }

private:

	// コールバック
	std::function<void(void)> func_;
	//残り時間
	uint32_t time_;
	// 完了フラグ
	bool comp_ = false;

};

