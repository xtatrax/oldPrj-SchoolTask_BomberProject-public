////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FAtdAfx.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�S�\�[�X���ʂ̃f�[�^�Q
//					��
//

#include "StdAfx.h"

D3DXVECTOR3 g_vZero = D3DXVECTOR3(0.0f,0.0f,0.0f);
D3DXVECTOR3 g_vOne  = D3DXVECTOR3(1.0f,1.0f,1.0f);
D3DXVECTOR3 g_vMax  = D3DXVECTOR3(+FLT_MAX,+FLT_MAX,+FLT_MAX);
D3DXVECTOR3 g_vMin  = D3DXVECTOR3(-FLT_MAX,-FLT_MAX,-FLT_MAX);

extern wstring g_sDefaultTexturePath = L"media/Textures/" ;	//	: �e�N�X�`���̒u����


wiz::RENDERSTATE_PARAM g_GlobalRenderStates[] = {
	{ D3DRS_CULLMODE     , D3DCULL_NONE },	// ���ʕ`�惂�[�h�̎w��
	{ D3DRS_ZENABLE      , TRUE         },  // �y��r���s�Ȃ�
	{ D3DRS_DITHERENABLE , TRUE         },  // �f�B�U�����O���s�Ȃ��i���i���`��j
	{ D3DRS_LIGHTING     , TRUE         },  // ���C�e�B���O���[�h
	{ D3DRS_FORCE_DWORD  , NULL			}	// �I���錾
};

HWND g_hWnd ;
bool g_bMouseLB;
bool g_bMouseRB;
