#pragma once
class CLifeEnvironment {
public:
	void SetLifeTime(float NewTime);
	float* GetLifeTime();
	float* GetTimeRate();
};

CLifeEnvironment* GetEnvironment();