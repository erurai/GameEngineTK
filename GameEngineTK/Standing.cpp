#include "Standing.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

shared_ptr<State> Standing::state = nullptr;

// �R���X�g���N�^
Standing::Standing() {
}

// Standing�I�u�W�F�N�g������������ Initialize Standing object
void Standing::Initialize(unique_ptr<Player>& player) {
	this->player = move(player);
}

// Standing�I�u�W�F�N�g������������ Initialize Standing object
void Standing::Initialize(unique_ptr<Player>&& player) {
	this->player = move(player);
}
// Standing�N���X�̃C���X�^���X���擾���� Get instance of Standing class
shared_ptr<State> Standing::GetInstance() {
	if (state == nullptr) {
		// Standing�I�u�W�F�N�𐶐�����
		state.reset (new Standing());
	}
	return state;
}

// Standing�I�u�W�F�N�g�����s���� Execute Standing object
inline void Standing::Execute() {
	// �uE�L�[�������������ꍇ
	if (this->player->GetKeyTracker()->IsKeyPressed(Keyboard::Keys::E)) {
		// �v���C���̏�Ԃ��u���ˁv�ɕύX����
		this->player->ChangeState(Shot::GetInstance());
	}

}

// Standing�I�u�W�F�N�g��j������ Delete Standing object
void Standing::Dispose() {
	if (state != nullptr) {
		state;
	}
}