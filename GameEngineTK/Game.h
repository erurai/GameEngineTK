//
// Game.h
//

#pragma once

#include "StepTimer.h"
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include "DebugCamera.h"
#include <Model.h>
#include <Keyboard.h>
#include "FollowCamera.h"
#include "Obj3d.h"
#include "Player.h"
#include "Enemy.h"
#include "LandShape.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

	//std::unique_ptr<DirectX::Keyboard>& GetKeyBoard() { return m_keyboard; }
	//std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>& GetKeyTracker() { return m_keytracker; }

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_batch;
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	std::unique_ptr<DirectX::CommonStates> m_states;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	std::unique_ptr<DebugCamera> m_debugCamera;	//デバッグカメラ

	std::unique_ptr<DirectX::EffectFactory> m_factory;

	std::unique_ptr<DirectX::Model> m_ball;
	std::unique_ptr<DirectX::Model> m_teapot;

	Obj3d m_objSkydome;
	//Obj3d m_objGround;
	LandShape m_LandShape;

	std::unique_ptr<Player> m_player;	//プレイヤー
	std::vector<std::unique_ptr<Enemy>> m_enemis; //敵

	//球のワールド行列
	DirectX::SimpleMath::Matrix m_world_ball[20];
	//自機のワールド行列
	DirectX::SimpleMath::Matrix m_world_head;
	DirectX::SimpleMath::Matrix m_world_head2;

	float m_radian1;	//角度
	float m_radian2;	//逆回転させる角度

	float m_pos_x[20];	//x座標
	float m_pos_z[20];	//z座標

	float m_time;

	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<FollowCamera> m_camera;

	//std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keytracker;

};