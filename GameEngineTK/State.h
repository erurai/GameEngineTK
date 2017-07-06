#pragma once
#ifndef STATE
#define STATE

#include "Player.h"

class Player;

// Stateインターフェイスを宣言する(Declare State class)
class State {
public:
	// 純粋仮想関数を宣言する(Declare pure virtual function)
	virtual void Initialize(std::unique_ptr<Player>& player) = 0;
	virtual void Initialize(std::unique_ptr<Player>&& player) = 0;
	virtual void Execute() = 0;
};

#endif // STATE