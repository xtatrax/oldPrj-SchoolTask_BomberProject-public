////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_PlaneCircle.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F
//					��
//	namespace wiz;
//		namespace bomberobject;
//
#pragma once
//////////
//	: �C���N���[�h
//	: �C���N���[�h
//////////
namespace wiz{
namespace bomberobject{

/**************************************************************************
 class Factory_PlaneCircle;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_PlaneCircle{
public:
/**************************************************************************
 Factory_PlaneCircle(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr			//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_PlaneCircle(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_PlaneCircle();
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
