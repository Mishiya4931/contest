#pragma once
class Texture;
class Score
{
private:
	Score();
	~Score();
public:
	static void Init();
	static void Uninit();
	static Score* GetInstanse() {
		return Instanse;
	}
	void Update();
	void Draw();
	void SetScore(int InScore) { m_nScore = InScore; }
	int GetScore() { return m_nScore; }
private:
	static Score* Instanse;
	int m_nScore;
	Texture* m_pTexture;
};

