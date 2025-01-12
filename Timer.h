#pragma once
class Texture;
class Timer
{
public:
	Timer();
	~Timer();
	void Update();
	void Draw();
	int GetTime() { return m_nTimeCnt; }
private:
	Texture* m_pTexture;
	int m_nTimeCnt;
};

