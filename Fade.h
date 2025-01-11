#pragma once
class Fade
{
public:
	Fade();
	virtual ~Fade() {}

	// 更新処理 
	void Update();

	// 描画処理 
	void Draw();

	// フェードの再スタート 
	void Start(bool isIn);

	// フェードの初期設定 
	void SetFade(float time, bool isIn);

	// フェード終了判定 
	bool IsFinish() { return m_time <= 0.0f; }

	// フェードイン判定 
	bool IsFadeIn() { return m_isFadeIn; }

	// フェードアウト判定 
	bool IsFadeOut() { return !m_isFadeIn; }
	float GetRate() {
		if (m_maxTime == 0.0f) { return 0.0f; } // 0除算回避 
		return m_time / m_maxTime;
	}

	// フェードの透明度を取得 
	float GetAlpha() {
		float alpha = GetRate();
		if (IsFadeOut()) // フェードアウトの時だけ開始時点で0、終了時点で1（Rateと逆の関係 
			alpha = 1.0f - alpha;
		return alpha;
	}

protected:
	virtual void DrawFadeIn(float alpha) {}
	virtual void DrawFadeOut(float alpha) {}
private:
	bool m_isFadeIn; // フェードインフラグ 
	float m_time;   // 現在のフェードの経過時間 
	float m_maxTime;  // フェードの最大時間
};


