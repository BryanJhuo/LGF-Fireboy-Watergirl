/*
 * mygame.h: ���ɮ��x�C��������class��interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/


#include "myMap.h"
#include "myObject.h"
#include "myScene.h"


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	protected:
		void OnMove();
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap logo;								// csie��logo
	private:
		void load_background();
		void draw_text();
		CMovingBitmap background;
		CMovingBitmap button_play;
		int button_play_time;
	};
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:


		int phase = 1;									//���d
		int sub_phase = 1;								//�l���d
		CMovingBitmap background;						//�I��
		CMovingBitmap bg;
		CMovingBitmap character1[3];						//�n�n
		CMovingBitmap character2[3];						//�̧�
		CMovingBitmap character1_left;
		CMovingBitmap character2_left;
		CMovingBitmap character1_right;
		CMovingBitmap character2_right;
		CMovingBitmap foot1;
		CMovingBitmap foot2;
		CMovingBitmap head1;
		CMovingBitmap head2;					
		CMovingBitmap cube[5][40];
		CMovingBitmap floor1;
		
		CMovingBitmap continueUI;
		CMovingBitmap gameover;

		void gravety();
		void boxMove();
		void characterMove();

		void show_image_by_phase();
		void show_text_by_phase();
		bool validate_phase_1();
		bool validate_phase_2();
		bool validate_phase_3();
		bool validate_phase_4();
		bool validate_phase_5();
		bool validate_phase_6();
		bool isdead = false;

		int continue_what;
		int floor[6] = {40,40,40,40,40,40};
		int floor_num = 4;
		int diamond_num = 0;
	

		CMovingBitmap maps[29][40];




		bool keepLeft = false;
		bool keepRight = false;
		bool jump1 = false;
		int jump1_time = 0;
		bool jump2 = false;
		int jump2_time = 0;

		int button_retry_time;
		int button_menu_time;
		int button_continue_time;
		CMovingBitmap button_continue;
		CMovingBitmap button_retry;
		CMovingBitmap button_menu;
		
		Scene scene;

		Map map;
		Object::Door door;
		Object::Button button;
		Object::Ramp ramp;
		Object::Box box;
		Object::Pond pond;
		Object::Diamond diamond;
		Object::Joystick joystick;

	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////


	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
		void OnLButtonDown(UINT nFlags, CPoint point);
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
		int button_retry_time;
		int button_menu_time;
		CMovingBitmap background;
		CMovingBitmap button_retry;
		CMovingBitmap button_menu;
	};

}
