﻿#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
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

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	/////////重力開始////////////////////////////////////////////////////////////////////

	//當角色1
	//沒有碰到最下層跟第二層地板 以及 移動板，會往下掉
	/*
	if (CMovingBitmap::IsOverlap(character1[0], floor1) == false && CMovingBitmap::IsOverlap(character1[0], floor2_up) == false && CMovingBitmap::IsOverlap(character1[0], floor3_up) == false && CMovingBitmap::IsOverlap(character1[0], ramp) == false) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() + 5);
	}
	*/

	bool gravity_flag1 = false;

	if (CMovingBitmap::IsOverlap(foot1, floor1) == true || CMovingBitmap::IsOverlap(foot1, ramp) == true) {
		gravity_flag1 = true;
	}


	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 38; i++) {
			if (j == 1 && i > 29) {
				break;
			}
			if (CMovingBitmap::IsOverlap(foot1, cube[j][i]) == true) {
				gravity_flag1 = true;
				break;
			}
		}
	}


	if (gravity_flag1 == false) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() + 5);
	}



	//當角色2沒有碰到最下層跟第二層地板 以及 移動板，會往下掉
	/*
		if (CMovingBitmap::IsOverlap(foot2, floor1) == false && CMovingBitmap::IsOverlap(foot2, floor2_up) == false && CMovingBitmap::IsOverlap(foot2, floor3_up) == false && CMovingBitmap::IsOverlap(foot2, ramp) == false) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() + 5);
	}
	*/



	bool gravity_flag2 = false;

	if (CMovingBitmap::IsOverlap(foot2, floor1) != false || CMovingBitmap::IsOverlap(foot2, ramp) == true) {
		//character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop());
		gravity_flag2 = true;
	}

	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 38; i++) {
			if (j == 1 && i > 29) {
				break;
			}
			if (CMovingBitmap::IsOverlap(foot2, cube[j][i]) == true) {
				character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop());
				gravity_flag2 = true;
				break;
			}
		}
	}

	if (gravity_flag2 == false) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() + 5);
	}

	/////////重力結束////////////////////////////////////////////////////////////////////


	// character1 move
	// 角色碰到牆壁停止
	if (CMovingBitmap::IsOverlap(character1[0], map_left) == false) {
		character1[0].SetTopLeft(character1[0].GetLeft() - 5, character1[0].GetTop());
	}
	if (CMovingBitmap::IsOverlap(character1[0], map_right) == false) {
		character1[0].SetTopLeft(character1[0].GetLeft() + 5, character1[0].GetTop());
	}


	if (GetAsyncKeyState(0x41) & 0x8000) {  // 當角色1按A向左
		character1[0].SetTopLeft(character1[0].GetLeft() - 5, character1[0].GetTop());
		character1[2].SetAnimation(100, false);
	}
	if (GetAsyncKeyState(0x44) & 0x8000) {  //當角色1按D向右
		character1[0].SetTopLeft(character1[0].GetLeft() + 5, character1[0].GetTop());
		character1[1].SetAnimation(100, false);
	}
	// character 1 跳躍
	if (GetAsyncKeyState(0x57) & 0x8000 && (CMovingBitmap::IsOverlap(foot1, floor1) == true || CMovingBitmap::IsOverlap(foot1, ramp) == true)) {
		jump1 = true;
		jump1_time = clock();
	}

	if (jump1 == true && (clock() - jump1_time) < 500) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() - 12);
	}
	else if (jump1 == true && (clock() - jump1_time) < 560) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() - 5);
	}
	else if (jump1 == true) {
		jump1 = false;
	}

	//角色1頂頭
	for (int j = 1; j < 2; j++) {
		for (int i = 0; i < 38; i++) {
			if (j == 1 && i > 29) {
				break;
			}
			if (CMovingBitmap::IsOverlap(head1, cube[1][i]) == true) {
				jump1 = false;
			}
		}
	}

	bool flag1 = false;

	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 30; i++) {
			if (GetAsyncKeyState(0x57) & 0x8000 && CMovingBitmap::IsOverlap(foot1, cube[j][i]) == true) {
				character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop());
				flag1 = true;
				break;
			}
		}
	}

	if (flag1 == true) {
		jump1 = true;
		jump1_time = clock();
		flag1 = false;
	}
	
	//character2 move
	//如果碰到牆壁就停止

	if (keepLeft == true && CMovingBitmap::IsOverlap(character2[0], map_left) == false) {
		character2[0].SetTopLeft(character2[0].GetLeft() - 5, character2[0].GetTop());
	}
	if (keepRight == true && CMovingBitmap::IsOverlap(character2[0], map_right) == false) {
		character2[0].SetTopLeft(character2[0].GetLeft() + 5, character2[0].GetTop());
	}

	//當角色2跳躍
	if (jump2 == true && (clock() - jump2_time) < 500) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 12);
	}
	else if (jump2 == true && (clock() - jump2_time) < 560) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 5);
	}
	else if (jump2 == true) {
		jump2 = false;
	}

	//角色2頂頭
	for (int j = 1; j < 2; j++) {
		for (int i = 0; i < 30; i++) {
			if (j == 1 && i > 29) {
				break;
			}
			if (CMovingBitmap::IsOverlap(head2, cube[1][i]) == true) {
				jump2 = false;
			}
		}
	}

	//機關
	//button1
	if (CMovingBitmap::IsOverlap(character2[0], button1) == true || CMovingBitmap::IsOverlap(character1[0], button1) == true || CMovingBitmap::IsOverlap(box_down, button1) == true) {
		button1.SetTopLeft(button1.GetLeft(), button1.GetTop() + 1);
	}
	else if (button1.GetTop() > 700) {
		button1.SetTopLeft(button1.GetLeft(), button1.GetTop() - 2);
	}
	else if (button1.GetTop() == 721) {
		button1.SetTopLeft(button1.GetLeft(), button1.GetTop());
	}

	if (button1.GetTop() > 700) {
		ramp.SetTopLeft(ramp.GetLeft(), min(600, ramp.GetTop() + 5));
	}
	else {
		ramp.SetTopLeft(ramp.GetLeft(), max(300, ramp.GetTop() - 5));
	}

	//button2
	
	if (CMovingBitmap::IsOverlap(character2[0], button2) == true || CMovingBitmap::IsOverlap(character1[0], button2) == true) {
		button2.SetTopLeft(button2.GetLeft(), button2.GetTop() + 1);
	}
	else if (button2.GetTop() > 200) {
		button2.SetTopLeft(button2.GetLeft(), button2.GetTop() - 2);
	}
	else if (button2.GetTop() == 221) {
		button2.SetTopLeft(button2.GetLeft(), button2.GetTop());
	}

	

	//角色碰到機關停住
	if (CMovingBitmap::IsOverlap(foot1, ramp) == true && ramp.GetTop() > 300) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() -5);
	}

	if (CMovingBitmap::IsOverlap(foot2, ramp) == true && ramp.GetTop() > 300) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 5);
	}

	//door 動畫
	if (CMovingBitmap::IsOverlap(character1[0], door1) == true && door1.GetFrameIndexOfBitmap() == 0) {
		door1.ToggleAnimation();
	}

	if (CMovingBitmap::IsOverlap(character2[0], door2) == true && door2.GetFrameIndexOfBitmap() == 0) {
		door2.ToggleAnimation();
	}

	//人物一推箱子移動
	//向左推
	if (CMovingBitmap::IsOverlap(character1[0], box_right) == true) {
		if (GetAsyncKeyState(0x41) & 0x8000) {
			box_up.SetTopLeft(box_up.GetLeft() - 5, box_up.GetTop());
			box_down.SetTopLeft(box_down.GetLeft() - 5, box_down.GetTop());
			box_right.SetTopLeft(box_right.GetLeft() - 5, box_right.GetTop());
			box_left.SetTopLeft(box_left.GetLeft() - 5, box_left.GetTop());
		}
	}

	//向右推
	if (CMovingBitmap::IsOverlap(character1[0], box_left) == true) {
		if (GetAsyncKeyState(0x44) & 0x8000) {
			box_up.SetTopLeft(box_up.GetLeft() + 5, box_up.GetTop());
			box_down.SetTopLeft(box_down.GetLeft() + 5, box_down.GetTop());
			box_right.SetTopLeft(box_right.GetLeft() + 5, box_right.GetTop());
			box_left.SetTopLeft(box_left.GetLeft() + 5, box_left.GetTop());
		}
	}

	//站在箱子上不會穿越箱子
	if (CMovingBitmap::IsOverlap(character1[0], box_up) == true) {
		character1[0].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop() - 5);
	}

	//人物二推箱子移動
	//向左推
	if (CMovingBitmap::IsOverlap(character2[0], box_right) == true) {
		if (keepLeft == true) {
			box_up.SetTopLeft(box_up.GetLeft() - 5, box_up.GetTop());
			box_down.SetTopLeft(box_down.GetLeft() - 5, box_down.GetTop());
			box_right.SetTopLeft(box_right.GetLeft() - 5, box_right.GetTop());
			box_left.SetTopLeft(box_left.GetLeft() - 5, box_left.GetTop());
		}
	}

	//向右推
	if (CMovingBitmap::IsOverlap(character2[0], box_left) == true) {
		if (keepRight == true) {
			box_up.SetTopLeft(box_up.GetLeft() + 5, box_up.GetTop());
			box_down.SetTopLeft(box_down.GetLeft() + 5, box_down.GetTop());
			box_right.SetTopLeft(box_right.GetLeft() + 5, box_right.GetTop());
			box_left.SetTopLeft(box_left.GetLeft() + 5, box_left.GetTop());
		}
	}

	//站在箱子上不會穿越箱子
	if (CMovingBitmap::IsOverlap(character2[0], box_up) == true) {
		character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop() - 5);
	}

	// 箱子碰到牆壁停止
	if (CMovingBitmap::IsOverlap(box_up, map_left) == true) {
		box_up.SetTopLeft(box_up.GetLeft() + 5, box_up.GetTop());
		box_down.SetTopLeft(box_down.GetLeft() + 5, box_down.GetTop());
		box_right.SetTopLeft(box_right.GetLeft() + 5, box_right.GetTop());
		box_left.SetTopLeft(box_left.GetLeft() + 5, box_left.GetTop());

		//箱子碰到牆壁時人物不會穿越箱子
		character1[0].SetTopLeft(character1[0].GetLeft() + 5, character1[0].GetTop());
		character2[0].SetTopLeft(character2[0].GetLeft() + 5, character2[0].GetTop());

	}


}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	//背景
	bg.LoadBitmapByString({ "Resources/bg.bmp" });
	bg.SetTopLeft(0, 0);

	//////////////////////////////地板///////////////////////////
	
	//第一層
	for (int i = 0; i < 38; i++) {
		cube[0][i].LoadEmptyBitmap(34, 36);
	}

	cube[0][0].SetTopLeft(0,841);

	//第二層
	for (int i = 0; i < 30; i++) {
		cube[1][i].LoadEmptyBitmap(34, 36);
	}
	cube[1][0].SetTopLeft(0, 720);

	floor1.LoadBitmapByString({ "Resources/floor1.bmp" });
	floor1.SetTopLeft(0, 842);

	floor2_up.LoadBitmapByString({ "Resources/floor2_up.bmp" });
	floor2_up.SetTopLeft(0, 720);

	floor2_down.LoadBitmapByString({ "Resources/floor2_down.bmp" });
	floor2_down.SetTopLeft(0, 721);

	floor2_right.LoadBitmapByString({ "Resources/floor2_right.bmp" });
	floor2_right.SetTopLeft(975, 721);

	floor3_up.LoadBitmapByString({ "Resources/floor2_up.bmp" });
	floor3_up.SetTopLeft(0, 220);

	floor3_down.LoadBitmapByString({ "Resources/floor2_down.bmp" });
	floor3_down.SetTopLeft(0, 221);

	floor3_right.LoadBitmapByString({ "Resources/floor2_right.bmp" });
	floor3_right.SetTopLeft(980, 221);


	/////////////////////////////////角色////////////////////////////////////////
	character1[0].LoadBitmapByString({ "Resources/fireboy.bmp" }, RGB(255, 255, 255));
	character1[0].SetTopLeft(850, 750);

	character1[2].LoadBitmapByString({ "Resources/fireboy(1_0).bmp",
										"Resources/fireboy(1_1).bmp",
										"Resources/fireboy(1_2).bmp",
										"Resources/fireboy(1_3).bmp",
										"Resources/fireboy(1_4).bmp",
										"Resources/fireboy(1_5).bmp",
										"Resources/fireboy(1_6).bmp",
										"Resources/fireboy(1_7).bmp" }, RGB(255, 255, 255));

	character1[1].LoadBitmapByString({ "Resources/fireboy(2_0).bmp",
									   "Resources/fireboy(2_1).bmp",
									   "Resources/fireboy(2_2).bmp",
									   "Resources/fireboy(2_3).bmp",
									   "Resources/fireboy(2_4).bmp",
									   "Resources/fireboy(2_5).bmp",
									   "Resources/fireboy(2_6).bmp",
									   "Resources/fireboy(2_7).bmp" }, RGB(255, 255, 255));

	foot1.LoadEmptyBitmap(5, 21);
	head1.LoadEmptyBitmap(5, 21);
	character1_left.LoadEmptyBitmap(75, 11);
	character1_right.LoadEmptyBitmap(75, 11);


	character2[0].LoadBitmapByString({ "Resources/watergirl_sprite (0_0).bmp", "Resources/watergirl_ignore.bmp" }, RGB(255, 255, 255));
	character2[0].SetTopLeft(850, 750);

	character2[1].LoadBitmapByString({ "Resources/watergirl_sprite (1_0).bmp",
										"Resources/watergirl_sprite (1_1).bmp",
										"Resources/watergirl_sprite (1_2).bmp",
										"Resources/watergirl_sprite (1_3).bmp",
										"Resources/watergirl_sprite (1_4).bmp",
										"Resources/watergirl_sprite (1_5).bmp",
										"Resources/watergirl_sprite (1_6).bmp",
										"Resources/watergirl_sprite (1_7).bmp"
		}, RGB(255, 255, 255));

	character2[2].LoadBitmapByString({ "Resources/watergirl_sprite (2_0).bmp",
									"Resources/watergirl_sprite (2_1).bmp",
									"Resources/watergirl_sprite (2_2).bmp",
									"Resources/watergirl_sprite (2_3).bmp",
									"Resources/watergirl_sprite (2_4).bmp",
									"Resources/watergirl_sprite (2_5).bmp",
									"Resources/watergirl_sprite (2_6).bmp",
									"Resources/watergirl_sprite (2_7).bmp"
		}, RGB(255, 255, 255));


	//角色2碰撞感測器

	foot2.LoadEmptyBitmap(5, 21);
	head2.LoadEmptyBitmap(5, 21);
	character2_left.LoadEmptyBitmap(75, 11);
	character2_right.LoadEmptyBitmap(75, 11);

	/////////////////////////////////////////////////////////////////////////////////////////////////


	//牆壁
	map_left.LoadBitmapByString({ "Resources/map_left.bmp" });
	map_left.SetTopLeft(0, 0);

	map_right.LoadBitmapByString({ "Resources/map_right.bmp" });
	map_right.SetTopLeft(1348, 0);

	map_top.LoadBitmapByString({ "Resources/map_top.bmp" });
	map_top.SetTopLeft(0, 0);

	//機關
	button1.LoadBitmapByString({ "Resources/button1(1).bmp" }, RGB(255, 255, 255));
	button1.SetTopLeft(300, 700);

	button2.LoadBitmapByString({ "Resources/button1(1).bmp" }, RGB(255, 255, 255));
	button2.SetTopLeft(600, 200);

	ramp.LoadBitmapByString({ "Resources/ramp.bmp", "Resources/ramp1.bmp" });
	ramp.SetTopLeft(1000, 300);

	//箱子
	box_up.LoadBitmapByString({ "Resources/box_up.bmp" }, RGB(255, 255, 255));
	box_up.SetTopLeft(200, 676);

	box_down.LoadBitmapByString({ "Resources/box_down.bmp" }, RGB(255, 255, 255));
	box_down.SetTopLeft(205, 681);

	box_right.LoadBitmapByString({ "Resources/box_right.bmp" }, RGB(255, 255, 255));
	box_right.SetTopLeft(239, 681);
	
	box_left.LoadBitmapByString({ "Resources/box_left.bmp" }, RGB(255, 255, 255));
	box_left.SetTopLeft(200, 681);

	//門
	door1.LoadBitmapByString({ "Resources/door100.bmp",
							   "Resources/door101.bmp",
							   "Resources/door102.bmp",
							   "Resources/door103.bmp",
							   "Resources/door104.bmp",
							   "Resources/door105.bmp" });
	door1.SetTopLeft(200, 131);
	door1.SetAnimation(100, true);

	door2.LoadBitmapByString({ "Resources/door200.bmp",
							   "Resources/door201.bmp",
							   "Resources/door202.bmp",
							   "Resources/door203.bmp",
							   "Resources/door204.bmp",
							   "Resources/door205.bmp" });
	door2.SetTopLeft(100, 131);
	door2.SetAnimation(100, true);

	//水池
	pond.LoadBitmapByString({ "Resources/pond.bmp" }, RGB(255, 255, 255));
	pond.SetTopLeft(1150, 842);

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	////////角色2左右移動
	if (nChar == VK_LEFT) {
		keepLeft = true;
		character2[2].SetAnimation(100, false);
	}

	if (nChar == VK_RIGHT) {
		keepRight = true;
		character2[1].SetAnimation(100, false);
	}
	////////角色2 跳
	if (nChar == VK_UP && (CMovingBitmap::IsOverlap(foot2, floor1) == true || CMovingBitmap::IsOverlap(foot2, ramp) == true)) {
		jump2 = true;
		jump2_time = clock();
	}

	bool flag2 = false;

	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 30; i++) {
			if (nChar == VK_UP && CMovingBitmap::IsOverlap(foot2, cube[j][i]) == true) {
				character2[0].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop());
				flag2 = true;
				break;
			}
		}
	}

	if (flag2 == true) {
		jump2 = true;
		jump2_time = clock();
		flag2 = false;
	}

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	////////角色2左右移動
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
	//牆壁
	bg.ShowBitmap();

	//門
	door1.ShowBitmap();
	door2.ShowBitmap();

	//機關與動畫
	button1.ShowBitmap();
	button2.ShowBitmap();
	ramp.ShowBitmap();
	
	//箱子
	box_up.ShowBitmap();
	box_down.ShowBitmap();
	box_right.ShowBitmap();
	box_left.ShowBitmap();

	//////////////地板///////////////////////////////////////
		

	floor1.ShowBitmap();
	floor2_up.ShowBitmap();
	floor2_down.ShowBitmap();

	floor3_up.ShowBitmap();
	floor3_down.ShowBitmap();


	for (int i = 0; i < 38; i++) {
		cube[0][i].SetTopLeft(cube[0][0].GetLeft() + (36 * i), cube[0][0].GetTop());
		cube[0][i].ShowBitmap();
	}

	for (int i = 0; i < 30; i++) {
		cube[1][i].SetTopLeft(cube[1][0].GetLeft() + (36 * i), cube[1][0].GetTop());
		cube[1][i].ShowBitmap();
	}

	///////////////////////人物與動畫//////////////////////////////////////
	// character1
	//角色碰撞感測器
	foot1.SetTopLeft(character1[0].GetLeft() + 25, character1[0].GetTop() + 85);
	foot1.ShowBitmap();

	head1.SetTopLeft(character1[0].GetLeft() + 25, character1[0].GetTop() + 4);
	head1.ShowBitmap();

	character1_left.SetTopLeft(character1[0].GetLeft() + 5, character1[0].GetTop() + 15);
	character1_left.ShowBitmap();
	character1_right.SetTopLeft(character1[0].GetLeft() + 55, character1[0].GetTop() + 15);
	character1_right.ShowBitmap();
	
	//角色跑步動畫
	if (GetAsyncKeyState(0x41) & 0x8000) {
		character1[1].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop());
		character1[1].ShowBitmap();
	}
	else if (GetAsyncKeyState(0x44) & 0x8000)
	{
		character1[2].SetTopLeft(character1[0].GetLeft(), character1[0].GetTop());
		character1[2].ShowBitmap();
	}
	else {
		character1[0].ShowBitmap();
	}




	// character2

	//角色碰撞感測器
	foot2.SetTopLeft(character2[0].GetLeft() + 39, character2[0].GetTop() + 95);
	foot2.ShowBitmap();

	head2.SetTopLeft(character2[0].GetLeft() + 39, character2[0].GetTop() + 15);
	head2.ShowBitmap();

	character2_left.SetTopLeft(character2[0].GetLeft() + 22, character2[0].GetTop() + 25);
	character2_left.ShowBitmap();
	character2_right.SetTopLeft(character2[0].GetLeft() + 66, character2[0].GetTop() + 25);
	character2_right.ShowBitmap();
	//角色跑步動畫
	if (keepRight) {

		character2[1].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop());
		character2[1].ShowBitmap();
	}
	else if (keepLeft)
	{
		character2[2].SetTopLeft(character2[0].GetLeft(), character2[0].GetTop());
		character2[2].ShowBitmap();
	}
	else if (CMovingBitmap::IsOverlap(character2[0], pond) == true) {  //死亡條件
		character2[0].SetFrameIndexOfBitmap(1);
		GotoGameState(GAME_STATE_OVER);
	}
	else {
		character2[0].ShowBitmap();

	}

	

	//牆壁
	map_left.ShowBitmap();
	map_right.ShowBitmap();
	map_top.ShowBitmap();

	//水池
	pond.ShowBitmap();

}



void CGameStateRun::show_image_by_phase() {
	if (phase <= 6) {

		if (phase == 3 && sub_phase == 1) {

		}
		if (phase == 4 && sub_phase == 1) {
	
		}
		if (phase == 5 && sub_phase == 1) {

		}
		if (phase == 6 && sub_phase == 1) {

		}
	}
}

void CGameStateRun::show_text_by_phase() {
	CDC *pDC = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(0, 0, 0), 800);

	if (phase == 1 && sub_phase == 1) {
		CTextDraw::Print(pDC, 237, 128, "修改你的主角！");
		CTextDraw::Print(pDC, 55, 163, "將灰色方格換成 resources 內的 giraffe.bmp 圖樣！");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (phase == 2 && sub_phase == 1) {
		CTextDraw::Print(pDC, 26, 128, "下一個階段，讓長頸鹿能夠透過上下左右移動到這個位置！");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (phase == 3 && sub_phase == 1) {
		CTextDraw::Print(pDC, 205, 128, "幫你準備了一個寶箱");
		CTextDraw::Print(pDC, 68, 162, "設計程式讓長頸鹿摸到寶箱後，將寶箱消失！");
		CTextDraw::Print(pDC, 68, 196, "記得寶箱要去背，使用 RGB(255, 255, 255)");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (phase == 4 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "幫你準備了一個蜜蜂好朋友");
		CTextDraw::Print(pDC, 89, 162, "已經幫它做了兩幀的動畫，讓它可以上下移動");
		CTextDraw::Print(pDC, 110, 196, "寫個程式來讓你的蜜蜂好朋友擁有動畫！");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (phase == 5 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "幫你準備了三扇門");
		CTextDraw::Print(pDC, 89, 162, "設計程式讓長頸鹿摸到門之後，門會打開");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (phase == 6 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "幫你準備了一顆會倒數的球");
		CTextDraw::Print(pDC, 89, 162, "設計程式讓球倒數，然後顯示 OK 後停止動畫");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (sub_phase == 2) {
		CTextDraw::Print(pDC, 268, 128, "完成！");
	}

	CDDraw::ReleaseBackCDC();
}

bool CGameStateRun::validate_phase_1() {
	return 0;
}

bool CGameStateRun::validate_phase_2() {
	return 0;
}

bool CGameStateRun::validate_phase_3() {
	return 0;
}

bool CGameStateRun::validate_phase_4() {
	return 0;
}

bool CGameStateRun::validate_phase_5() {
	return 0;
}

bool CGameStateRun::validate_phase_6() {
	return 0;
}
