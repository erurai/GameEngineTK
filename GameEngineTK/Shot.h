#pragma once
#ifndef SHOT
#define SHOT

#include "Player.h"
#include "State.h"

class State;
class Player;

// Standing�N���X��錾���� Declare Standing class
class Shot : public State {
public:
	// Standing�N���X�̃C���X�^���X���擾���� Get instance of Standing class
	static std::shared_ptr<State> GetInstance();
	// Standing�I�u�W�F�N�g������������ Initialize Standing object
	void Initialize(std::unique_ptr<Player>& player) override;
	void Initialize(std::unique_ptr<Player>&& player) override;
	// Standing�I�u�W�F�N�g�����s���� Execute Standing object
	void Execute() override;
	// Standing�I�u�W�F�N�g��j������ Delete Standing object
	static void Dispose();

private:
	Shot();
	static std::shared_ptr<State> state;
	std::unique_ptr<Player> player;
};

#endif // SHOT