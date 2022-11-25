#include "C:\DxLib_VC\プロジェクトに追加すべきファイル_VC用/DxLib.h"
#include"Vector2.h"
#include<cmath>

bool CheckLine2Circle(Vector2& lineStart, Vector2& lineEnd, Vector2& circle, int circleR);

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LC1D_26_モミヤマケイタ: タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 600;

// ウィンドウ縦幅
const int WIN_HEIGHT = 400;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	bool hitflag = false;
	Vector2 lineStart = { 20 ,20 }, lineEnd = { 120, 20 };

	int circleR = 40;

	Vector2 circle = { WIN_WIDTH / 2,WIN_HEIGHT / 2 };

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		if (keys[KEY_INPUT_W])
		{
			lineStart.y -= 10;
			lineEnd.y -= 10;
		}
		if (keys[KEY_INPUT_S])
		{
			lineStart.y += 10;
			lineEnd.y += 10;
		}
		if (keys[KEY_INPUT_A])
		{
			lineStart.x -= 10;
			lineEnd.x -= 10;
		}
		if (keys[KEY_INPUT_D])
		{
			lineStart.x += 10;
			lineEnd.x += 10;
		}

		hitflag = CheckLine2Circle(lineStart, lineEnd, circle, circleR);


		// 描画処理
		DrawLine(lineStart.x, lineStart.y, lineEnd.x, lineEnd.y, GetColor(255, 255, 255));
		
		hitflag ? DrawCircle(circle.x, circle.y, circleR, GetColor(255, 0, 0)) : DrawCircle(circle.x, circle.y, circleR, GetColor(255, 255, 255));
		
		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}

bool CheckLine2Circle(Vector2& lineStart, Vector2& lineEnd, Vector2& circle, int circleR)
{
	Vector2 lineVec = lineEnd - lineStart;

	Vector2 lineEndCirclVec = circle - lineEnd;

	Vector2 lineStartCirclVec = circle - lineStart;
	Vector2 normLineVec = lineVec.normalized();

	float distance = lineStartCirclVec.cross(normLineVec);

	if (fabsf(distance)< circleR)
	{
		float circlVecLineStartVecDot = lineStartCirclVec.dot(lineVec);

		float circlVecLineEndVecDot = lineEndCirclVec.dot(lineVec);

		if (circlVecLineStartVecDot* circlVecLineEndVecDot<= 0)
		{
			return true;
		}

		if (lineEndCirclVec.length() < circleR || lineStartCirclVec.length() < circleR)
		{
			return true;
		}
	}
		return false;
}
