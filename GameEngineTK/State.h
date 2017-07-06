#pragma once
#ifndef STATE
#define STATE

#include "Player.h"

class Player;

// State�C���^�[�t�F�C�X��錾����(Declare State class)
class State {
public:
	// �������z�֐���錾����(Declare pure virtual function)
	virtual void Initialize(std::unique_ptr<Player>& player) = 0;
	virtual void Initialize(std::unique_ptr<Player>&& player) = 0;
	virtual void Execute() = 0;
};

#endif // STATE