#pragma once
#ifndef STANDING
#define STANDING

#include "Player.h"
#include "State.h"

class State;
class Player;

// Standingクラスを宣言する Declare Standing class
class Standing : public State {
public:
	// Standingクラスのインスタンスを取得する Get instance of Standing class
	static std::shared_ptr<State> GetInstance();
	// Standingオブジェクトを初期化する Initialize Standing object
	void Initialize(std::unique_ptr<Player>& player) override;
	void Initialize(std::unique_ptr<Player>&& player) override;
	// Standingオブジェクトを実行する Execute Standing object
	void Execute() override;
	// Standingオブジェクトを破棄する Delete Standing object
	static void Dispose();

private:
	Standing();
	static std::shared_ptr<State> state;
	std::unique_ptr<Player> player;
};

#endif // STANDING