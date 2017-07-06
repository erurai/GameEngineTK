#include "Shot.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

shared_ptr<State> Shot::state = nullptr;

// �R���X�g���N�^
Shot::Shot() {
}

// Shot�I�u�W�F�N�g������������ Initialize Shot object
void Shot::Initialize(unique_ptr<Player>& player) {
	this->player = move(player);
}

// Shot�I�u�W�F�N�g������������ Initialize Shot object
void Shot::Initialize(unique_ptr<Player>&& player) {
	this->player = move(player);
}
// Shot�N���X�̃C���X�^���X���擾���� Get instance of Shot class
shared_ptr<State> Shot::GetInstance() {
	if (state == nullptr) {
		// Standing�I�u�W�F�N�𐶐�����
		state.reset(new Shot());
	}
	return state;
}

// Shot�I�u�W�F�N�g�����s���� Execute Shot object
inline void Shot::Execute() {
	// �uE�v�L�[�������������ꍇ
	if (this->player->GetKeyTracker()->IsKeyPressed(Keyboard::Keys::E)) {
		// �v���C���̏�Ԃ��u�ҋ@�v�ɕύX����
		this->player->ChangeState(Standing::GetInstance());
	}
}

// Shooting�I�u�W�F�N�g��j������ Delete Shooting object
void Shot::Dispose() {
	if (state != nullptr) {
		state;
	}
}