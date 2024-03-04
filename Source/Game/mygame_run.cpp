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
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// ���ʹC������
{
	//character1.SetTopLeft(character1.GetLeft(), character1.GetTop() + 10);


	if (character2.IsOverlap(character2, floor)==false || jump==false) {
		character2.SetTopLeft(character2.GetLeft(), character2.GetTop() + 5);
	}



	if (GetAsyncKeyState(0x41)) {  //A��V��
		character1.SetTopLeft(character1.GetLeft() - 10, character1.GetTop());
	}
	if (GetAsyncKeyState(0x44)) {  //D��V�k
		character1.SetTopLeft(character1.GetLeft() + 10, character1.GetTop());
	}

	if (keepLeft == true) {
		character2.SetTopLeft(character2.GetLeft() - 10, character2.GetTop());
	}
	if (keepRight == true) {
		character2.SetTopLeft(character2.GetLeft() + 10, character2.GetTop());
	}

	if (character2.IsOverlap(character2, floor)) {			//����I��a�O
		character2.SetTopLeft(character2.GetLeft(), character2.GetTop() -5);
	}




	
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{

	floor.LoadBitmapByString({ "resources/floor.bmp" });
	floor.SetTopLeft(0, 800);

	character2.LoadBitmapByString({ "resources/GAME_FRAMEWORK.bmp" });
	character2.SetTopLeft(150, 265);

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT) {
		keepLeft = true;
	}

	if (nChar == VK_RIGHT) {
		keepRight = true;
	}

	if (nChar == VK_UP) {
		jump = true;
		for (int i = 10; i >= -10; i=i-1) {
			character2.SetTopLeft(character2.GetLeft(), character2.GetTop() - i);
		}
		jump = false;
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT) {
		keepLeft = false;
	}

	if (nChar == VK_RIGHT) {
		keepRight = false;
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()
{
	floor.ShowBitmap();
	character2.ShowBitmap();
}
