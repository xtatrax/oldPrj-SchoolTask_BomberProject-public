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


float f = 0.5f ;

wiz::RENDERSTATE_PARAM g_GlobalRenderStates[] = {
	//{ D3DRS_CULLMODE     , D3DCULL_NONE },	// ���ʕ`�惂�[�h�̎w��
	{ D3DRS_ZENABLE      , TRUE         },  // �y��r���s�Ȃ�
	{ D3DRS_DITHERENABLE , TRUE         },  // �f�B�U�����O���s�Ȃ��i���i���`��j
	{ D3DRS_LIGHTING     , TRUE         },  // ���C�e�B���O���[�h
	{ D3DRS_ALPHAREF     , 0x00000001	},  // ���C�e�B���O���[�h
	{ D3DRS_ALPHATESTENABLE, TRUE				},  // ���C�e�B���O���[�h
	{ D3DRS_ALPHAFUNC    , D3DCMP_GREATEREQUAL	},  // ���C�e�B���O���[�h
	{ D3DRS_FORCE_DWORD  , NULL			}	// �I���錾
};

