#include "Standing.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

shared_ptr<State> Standing::state = nullptr;

// コンストラクタ
Standing::Standing() {
}

// Standingオブジェクトを初期化する Initialize Standing object
void Standing::Initialize(unique_ptr<Player>& player) {
	this->player = move(player);
}

// Standingオブジェクトを初期化する Initialize Standing object
void Standing::Initialize(unique_ptr<Player>&& player) {
	this->player = move(player);
}
// Standingクラスのインスタンスを取得する Get instance of Standing class
shared_ptr<State> Standing::GetInstance() {
	if (state == nullptr) {
		// Standingオブジェクを生成する
		state.reset (new Standing());
	}
	return state;
}

// Standingオブジェクトを実行する Execute Standing object
inline void Standing::Execute() {
	// 「Eキーを押し下げた場合
	if (this->player->GetKeyTracker()->IsKeyPressed(Keyboard::Keys::E)) {
		// プレイヤの状態を「発射」に変更する
		this->player->ChangeState(Shot::GetInstance());
	}

}

// Standingオブジェクトを破棄する Delete Standing object
void Standing::Dispose() {
	if (state != nullptr) {
		state;
	}
}