#include "Shot.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

shared_ptr<State> Shot::state = nullptr;

// コンストラクタ
Shot::Shot() {
}

// Shotオブジェクトを初期化する Initialize Shot object
void Shot::Initialize(unique_ptr<Player>& player) {
	this->player = move(player);
}

// Shotオブジェクトを初期化する Initialize Shot object
void Shot::Initialize(unique_ptr<Player>&& player) {
	this->player = move(player);
}
// Shotクラスのインスタンスを取得する Get instance of Shot class
shared_ptr<State> Shot::GetInstance() {
	if (state == nullptr) {
		// Standingオブジェクを生成する
		state.reset(new Shot());
	}
	return state;
}

// Shotオブジェクトを実行する Execute Shot object
inline void Shot::Execute() {
	// 「E」キーを押し下げた場合
	if (this->player->GetKeyTracker()->IsKeyPressed(Keyboard::Keys::E)) {
		// プレイヤの状態を「待機」に変更する
		this->player->ChangeState(Standing::GetInstance());
	}
}

// Shootingオブジェクトを破棄する Delete Shooting object
void Shot::Dispose() {
	if (state != nullptr) {
		state;
	}
}