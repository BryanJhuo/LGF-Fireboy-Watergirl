#include "stdafx.h"
#include "myScene.h"



void Scene::loadScene() {

	//�������� 0
	//�~��_ALL�_�ۤ��� 1
	//�~��_NOT ALL�_�ۤ��� 2
	// ��l��椶�� 3

	//window(setting paused die pass)
	window[0].LoadBitmapByString({ "Resources/w_game_over.bmp" });				//��������
	window[1].LoadBitmapByString({ "Resources/w_continue_all.bmp" });			//�~��_ALL�_�ۤ���
	window[2].LoadBitmapByString({ "Resources/w_continue.bmp" });				//�~��_NOT ALL�_�ۤ���
	window[3].LoadBitmapByString({ "Resources/w_choose0.bmp" });				// ��l��椶��

	window[4].LoadBitmapByString({ "Resources/w_choose1.bmp" });				// �q�L�Ĥ@��
	window[5].LoadBitmapByString({ "Resources/w_choose2.bmp" });				// �q�L�ĤG��
	window[6].LoadBitmapByString({ "Resources/w_choose3.bmp" });				// �q�L�ĤT��
	window[7].LoadBitmapByString({ "Resources/w_choose4.bmp" });				// �q�L�ĥ|��
	window[8].LoadBitmapByString({ "Resources/w_choose5.bmp" });				// �q�L�Ĥ���



	for (int i = 0; i < 9; i++) {
		window[i].SetTopLeft(0, 0);
	}

}

void Scene::showScene(int page_phase) {

	//setting window
	if (page_phase == 0) {
		window[0].ShowBitmap();		//window
	}

	//paused window
	if (page_phase == 1) {
		window[1].ShowBitmap();		//window
	}

	//die window
	if (page_phase == 2) {
		window[2].ShowBitmap();		//window
	}

	//pass window
	if (page_phase == 3) {
		window[3].ShowBitmap();		//window
	}

	//pass 1 window
	if (page_phase == 4) {
		window[4].ShowBitmap();		//window
	}

	//pass 2 window
	if (page_phase == 5) {
		window[5].ShowBitmap();		//window
	}

	//pass 3 window
	if (page_phase == 6) {
		window[6].ShowBitmap();		//window
	}

	//pass 4 window
	if (page_phase == 7) {
		window[7].ShowBitmap();		//window
	}

	//pass 5 window
	if (page_phase == 8) {
		window[8].ShowBitmap();		//window
	}



}