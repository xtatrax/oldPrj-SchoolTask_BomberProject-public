////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Enemy.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�֓��@����
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Enemy ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Enemy.h"
#include "BassItems.h"

namespace wiz
{


	/**************************************************************************
	 EnemySphere ��`��
	***************************************************************************/
	
	/////////////////// ////////////////////
	//// �֐���     �Fvoid EnemySphere::Vec2UV(float x,float y,float z,float r,float& u,float& v );
	//// �J�e�S��   �F�����o�֐�
	//// �p�r       �FVector��U��V�ɃR���o�[�g
	//// ����       �F  float x     //x�̒l
	////            �F  float y     //y�̒l
	////            �F  float z     //z�̒l
	////            �F  float r     //���̔��a
	////            �F  float& u    //�ϊ�����u�i�e�N�X�`�����U���W�j
	////            �F  float& v    //�ϊ�����v�i�e�N�X�`�����V���W�j
	//// �ߒl       �F�Ȃ�
	//// �S����     �F (�R�m��搶�̂ЂȌ`���)
	//// ���l       �Ffloat& u��float& v�ɕϊ���̒l����
	////            �F
	////
	void EnemySphere::Vec2UV(float x,float y,float z,float r,float& u,float& v) 
	{
		float q ;
		float q2;
		q = atan2(z,x);
		u = q / (2.0f * D3DX_PI);
		q2 = asin(y / r);
		v = (1.0f - q2 / (D3DX_PI / 2.0f)) / 2.0f;
		if( u > 1.0f)
			u = 1.0f;
	}
	/////////////////// ////////////////////
	//// �֐���     �Fvoid EnemySphere::CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice)
	//// �J�e�S��   �F�֐�
	//// �p�r       �F���𐶐�
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	//// �ߒl       �F�Ȃ�
	//// �S����     �F�֓��@����(�R�m��搶�̂ЂȌ`���)
	//// ���l       �Ffloat& u��float& v�ɕϊ���̒l����
	////            �F
	////
	void EnemySphere::CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice)
	{
		try
		{
			

		
				//���̍쐬
			if(
				FAILED(
					D3DXCreateSphere(
						pD3DDevice, 
						30.0f,//���̑傫��
						18,
						18,
						&m_pMesh, 
						NULL
					)
				)
			)
			{
				// ���������s
				throw BaseException(
					L"���̍쐬�Ɏ��s���܂����B",
					L"EnemySphere::EnemySphere"
					);
			}
			if(m_pTexture)
			{
				//�e�N�X�`�����b�V��
				LPD3DXMESH pMesh2 = 0;
				//�쐬���ꂽ���b�V�������ɁA�e�N�X�`�����̃��b�V�����쐬
				if(FAILED(m_pMesh->CloneMeshFVF(NULL,BallFVF,pD3DDevice,&pMesh2)))
				{
					// ���������s
					throw BaseException(
						L"�e�N�X�`���t�̋��̍쐬�Ɏ��s���܂����B",
						L"EnemySphere::EnemySphere"
						);
				}
				//���̒i�K��m_pMesh�͂���Ȃ�����폜
				SafeRelease(m_pMesh);
				//�V�������b�V������
				m_pMesh = pMesh2;
				//�e�N�X�`����̍��W���}�b�s���O
				LPDIRECT3DVERTEXBUFFER9 pVB = 0;
				SphereVertex* pVer = 0;
				m_pMesh->GetVertexBuffer(&pVB);
				pVB->Lock(0,0,(VOID**)&pVer,0);
				for(DWORD n = 0;n < m_pMesh->GetNumVertices();n++)
				{ //���_�̐����擾����
					float u,v;
					Vec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,1.0f,u,v);
					pVer[n].tu=u;
					pVer[n].tv=v;
				}
				pVB->Unlock();
			}
			//�N�I�[�^�j�I���̏�����
			//D3DXQuaternionRotationYawPitchRoll(&m_Qtn,0,0,0);
		}
		catch(...)
		{
			//�R���X�g���N�^��O����
			//��n��
			SafeRelease(m_pMesh);
			//�ăX���[
			throw;
		}
	};

	/////////////////// ////////////////////
	//// �֐���     �FEnemySphere::EnemySphere(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,
	////            �F  D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,LPDIRECT3DTEXTURE9 pTexture = 0);
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F���̂��쐬
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
	////            �F  D3DCOLORVALUE& Specular,            //�X�y�L�����F
	////            �F  D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	////            �F  LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
	//// �ߒl       �F�Ȃ��i���s���͗�O��throw�j
	//// �S����     �F (�R�m��搶�̂ЂȌ`���)
	//// ���l       �F
	////            �F
	////
	//CPP�ł̃R���X�g���N�^�̏������B
	EnemySphere::EnemySphere(LPDIRECT3DDEVICE9 pD3DDevice,
			   D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
			   LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id)
		//�p����������Ȋ����ŏ����B�^�͕ϐ������B
		: PrimitiveSphere( pD3DDevice,
			    Diffuse, Specular, Ambient, pTexture)
				,Object(id)
				,m_pTexture(pTexture)
	{
		try
		{
			EnemySphere* Sphere = new EnemySphere( pD3DDevice, Diffuse, Specular, Ambient, pTexture, id);

			CreateSphere(pD3DDevice);
		}
		catch(...)
		{
			//�ăX���[
			throw;
		}

	}



	/////////////////// ////////////////////
	//// �֐���     �FEnemySphere::~EnemySphere();
	//// �J�e�S��   �F�f�X�g���N�^
	//// �p�r       �F���̂�j��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F (�R�m��搶�̂ЂȌ`���)
	//// ���l       �F
	////            �F
	////
	EnemySphere::~EnemySphere()
	{
		//��n��
		SafeRelease(m_pMesh);
	}
	/////////////////// ////////////////////
	//// �֐���     �FvoidEnemySphere::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
	//// �J�e�S��   �F���z�֐�
	//// �p�r       �F���̂�`��
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
	//// �ߒl       �F�Ȃ�
	//// �S����     �F (�R�m��搶�̂ЂȌ`���)
	//// ���l       �F
	////            �F
	////
	void EnemySphere::Draw(DrawPacket& i_DrawPacket)
	{
		//�e�N�X�`�����������ꍇ
		if(m_pTexture)
		{
			//�e�N�X�`���`�施��
			DWORD wkdword;
			//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
			i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
			//�X�e�[�W�̐ݒ�
			i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
			//�f�t�B�[�Y�F�ƃe�N�X�`�����|�����킹��ݒ�
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
			i_DrawPacket.pD3DDevice->SetFVF(BallFVF);

			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//�X�e�[�W�����ɖ߂�
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else
		{
			//�e�N�X�`�����Ȃ��ꍇ

			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
		}
	}
}