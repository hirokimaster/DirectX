#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize(Model* model,Vector3 pos, uint32_t texHandle)
{
	assert(model);
	// レティクル用テクスチャ取得
	textureReticle_ = TextureManager::Load("resources/2DReticle.png");
	sprite2DReticle_.reset(Sprite::Create({ 640.0f,360.0f }, { 150.0f,150.0f },{0.5f,0.5f}));
	model_ = model;
	model_->SetTexHandle(texHandle);
	worldTransform_.Initialize();
	worldTransform3DReticle_.Initialize();
	worldTransform_.translate = pos;
}

void Player::Update(const Camera& camera)
{
	Vector3 move{ 0,0,0 }; // 移動ベクトル

	if (Input::GetInstance()->PushKey(DIK_A)) {
		move.x -= moveSpeed;
	}
	else if (Input::GetInstance()->PushKey(DIK_D)) {
		move.x += moveSpeed;
	}

	if (Input::GetInstance()->PushKey(DIK_W)) {
		move.y += moveSpeed;
	}
	else if (Input::GetInstance()->PushKey(DIK_S)) {
		move.y -= moveSpeed;
	}

	// ゲームパッドの状態を得る変数(XINPUT)
	XINPUT_STATE joyState;

	// ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(joyState)) {
		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * moveSpeed;
		move.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * moveSpeed;
	}

	// 移動
	worldTransform_.translate = Add(worldTransform_.translate, move);
	// 旋回
	Rotate();
	// 攻撃
	Attack();

	// 弾更新
	for (bulletsItr_ = bullets_.begin();
		bulletsItr_ != bullets_.end(); ++bulletsItr_) {
		(*bulletsItr_)->Update();
	}

	// デスフラグの立ったやつを消す
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		if (bullet->IsDead()) {
			return true;
		}
		return false;
	});

	// 移動限界
	const float kMoveLimitX = 23.0f;
	const float kMoveLimitY = 12.5f;

	// 範囲を超えない処理
	worldTransform_.translate.x = max(worldTransform_.translate.x, -kMoveLimitX);
	worldTransform_.translate.x = std::min(worldTransform_.translate.x, kMoveLimitX);
	worldTransform_.translate.y = max(worldTransform_.translate.y, -kMoveLimitY);
	worldTransform_.translate.y = std::min(worldTransform_.translate.y, kMoveLimitY);

	POINT mousePosition;
	// マウス座標(スクリーン座標)を取得する
	GetCursorPos(&mousePosition);

	// クライアントエリア座標に変換する
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	Vector2 spritePosition = sprite2DReticle_->GetPosition();

	// ジョイスティック状態取得
	if (Input::GetInstance()->GetJoystickState(joyState)) {
		spritePosition.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 5.0f;
		spritePosition.y -= (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 5.0f;
		// スプライトの座標変更を反映
		sprite2DReticle_->SetPosition(spritePosition);

	}

	// レティクル
	Reticle(camera, Vector2((float)spritePosition.x, (float)spritePosition.y));

	
	// ImGui
	ImGui::Begin("Player");
	ImGui::Text(
		"Player X[%.03f].Y[%.03f].Z[%.03f]", worldTransform_.translate.x,
		worldTransform_.translate.y, worldTransform_.translate.z);
	ImGui::End();

	worldTransform_.UpdateMatrix();
}

void Player::Rotate() {
	// 回転速さ[ラジアン/frame]
	const float kRotSpeed = 0.02f;

	// 押した方向で移動ベクトルを変更
	if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		worldTransform_.rotate.y -= kRotSpeed;

	}
	else if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
		worldTransform_.rotate.y += kRotSpeed;
	}
}

// 攻撃
void Player::Attack() {

	// 処理
	if (Input::GetInstance()->PressedKey(DIK_SPACE)) {
		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity = { 0,0,kBulletSpeed };
		// 自機から照準オブジェクトのベクトル
		Vector3 WorldPos = GetWorldPosition();
		Vector3 ReticleWorldPos = GetWorldPosition3DReticle();
		velocity = Subtract(ReticleWorldPos, WorldPos);
		velocity = Normalize(velocity);
		velocity = Multiply(kBulletSpeed, velocity);
		// プレイヤーの向きに速度を合わせる
		velocity = TransformNormal(velocity, worldTransform_.matWorld);
		// 弾を生成し、初期化
		std::unique_ptr<PlayerBullet> bullet = std::make_unique<PlayerBullet>();
		bullet->Initialize(worldTransform_.translate, velocity);
		// 弾をセット
		bullets_.push_back(std::move(bullet));
	}
}

void Player::DrawUI(const Camera& camera)
{
	sprite2DReticle_->Draw(camera, textureReticle_);
}

void Player::OnCollision()
{
}

Vector3 Player::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld.m[3][0];
	worldPos.y = worldTransform_.matWorld.m[3][1];
	worldPos.z = worldTransform_.matWorld.m[3][2];

	return worldPos;
}

// 3Dレティクルのワールド座標
Vector3 Player::GetWorldPosition3DReticle() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform3DReticle_.matWorld.m[3][0];
	worldPos.y = worldTransform3DReticle_.matWorld.m[3][1];
	worldPos.z = worldTransform3DReticle_.matWorld.m[3][2];

	return worldPos;	
}

void Player::SetParent(const WorldTransform* parent)
{
	worldTransform_.parent = parent;
}

void Player::Reticle(const Camera& camera, const Vector2& pos)
{
	// スプライトのレティクルに座標設定
	sprite2DReticle_->SetPosition(pos);

	// ビューポート行列
	Matrix4x4 matViewport =
		MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	// ビュープロジェクションビューポート合成行列
	Matrix4x4 matVPN =
		Multiply(camera.matView, Multiply(camera.matProjection, matViewport));
	// 逆行列を計算
	Matrix4x4 matInverseVPN = Inverse(matVPN);

	// スクリーン座標
	Vector3 posNear = Vector3((float)pos.x, (float)pos.y, 1);
	Vector3 posFar = Vector3((float)pos.x, (float)pos.y, 0);

	// スクリーン座標からワールド座標系へ
	posNear = Transform(posNear, matInverseVPN);
	posFar = Transform(posFar, matInverseVPN);

	// マウスレイの方向
	Vector3 mouseDirection = Subtract(posNear, posFar);
	mouseDirection = Normalize(mouseDirection);
	// カメラから照準オブジェクトの距離
	const float kDistanceTestObject = 100.0f;
    worldTransform3DReticle_.translate = Multiply(kDistanceTestObject, mouseDirection);
	worldTransform3DReticle_.UpdateMatrix();
}

void Player::Draw(const Camera& camera)
{
	model_->Draw(worldTransform_,camera);

	// 弾の描画
	for (bulletsItr_ = bullets_.begin();
		bulletsItr_ != bullets_.end(); ++bulletsItr_) {
		(*bulletsItr_)->Draw(camera);
	}
}
