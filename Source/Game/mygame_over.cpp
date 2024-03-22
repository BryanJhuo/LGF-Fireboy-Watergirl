#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g) : CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	/*
	if (clock() - button_retry_time == 21000) {
		button_retry.SetFrameIndexOfBitmap(0);
		button_play.ShowBitmap();
	}
	else if (clock() - button_retry_time <= 25500) {
		GotoGameState(GAME_STATE_RUN);
	}
	*/
	//GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	background.LoadBitmapByString({ "resources/game_over.bmp" }, RGB(255, 255, 255));
	background.SetTopLeft(170, 150);
	button_menu.LoadBitmapByString({ "resources/button_menu.bmp","resources/button_menu1.bmp" });
	button_retry.LoadBitmapByString({ "resources/button_retry.bmp","resources/button_retry1.bmp" });
	button_menu.SetTopLeft(405, 536);
	button_retry.SetTopLeft(722, 536);


}

void CGameStateOver::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66, "Initialize...");	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	Sleep(1000);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100, "OK!");

	Sleep(1000);


}

void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (WM_LBUTTONDOWN) {
		int idx1 = point.x;
		int idy1 = point.y;

		if (idx1 >= 722 && idy1 > 536 && idx1 <= 915 && idy1 <= 600) {
			button_retry.SetTopLeft(718, 530);
			button_retry.SetFrameIndexOfBitmap(1);
			button_retry.ShowBitmap();
			button_retry_time = clock();

		}
		else if(idx1 >= 405 && idy1 > 536 && idx1 <= 611 && idy1 <= 600){
			button_menu.SetTopLeft(400, 530);
			button_menu.SetFrameIndexOfBitmap(1);
			button_menu.ShowBitmap();
			button_menu_time = clock();
		}

	}


}

void CGameStateOver::OnShow()
{
	background.ShowBitmap();
	button_menu.ShowBitmap();
	button_retry.ShowBitmap();
}
