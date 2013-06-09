////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FBassItems.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F�Q�[���̃x�[�X�ɂȂ�A�C�e���Q�̐錾
//					��
//	�v���~�e�B�u���ӂ��R�m��搶�̃\�[�X���Q�l�ɑ��������! 
//
//	namespace wiz;
//
#include "StdAfx.h"
#include "Bass2DItems.h"
namespace wiz {

namespace base2Dobject{
/**************************************************************************
 PrimitiveSprite ��`��
***************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FPrimitiveSprite::PrimitiveSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,RECT* Rect,
////            �F    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,D3DCOLOR color = 0xFFFFFFFF);
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	//	: �f�o�C�X
////            �F  LPDIRECT3DTEXTURE9 pTexture,	//	: �e�N�X�`���[�ւ̃|�C���^
////            �F  RECT*			Rect,			//	: �e�N�X�`���̕`��͈�
////            �F  D3DXVECTOR3&	vCenter,		//	: ���S�ʒu
////            �F  D3DXVECTOR3&	vOffsetPos,		//	: ���[�J�����W
////            �F  D3DCOLOR		color			//	: �F
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
PrimitiveSprite::PrimitiveSprite(
	const LPDIRECT3DDEVICE9 pD3DDevice,
	const LPDIRECT3DTEXTURE9 pTexture,const RECT* rect,
	const D3DXVECTOR3& vCenter,const D3DXVECTOR3& vOffsetPos,const  Color color)
	:m_pTexture(pTexture)
	,m_vOffsetPos(vOffsetPos)
	,m_vCenter(vCenter)
	,m_pRect(NULL)
	,m_Color(color)
{
	try{
		if(rect){
			m_pRect = new RECT(*rect);
		}
		if(
			FAILED(
				D3DXCreateSprite(
					pD3DDevice,
					&m_pSprite
				)
			)
		){
			// ���������s
			throw BaseException(
				L"�X�v���C�g�̍쐬�Ɏ��s���܂����B",
				L"PrimitiveSprite::PrimitiveSprite()"
			);
		}
	}
	catch(...){
		SafeRelease(m_pSprite);
		//�ăX���[
		throw;
	}
}

/////////////////// ////////////////////
//// �֐���     �Fvirtual PrimitiveSprite::~PrimitiveSprite()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
PrimitiveSprite::~PrimitiveSprite(){
	SafeDelete(m_pRect);
	SafeRelease(m_pSprite);
}



/////////////////// ////////////////////
//// �֐���     �Fvoid PrimitiveSprite::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void PrimitiveSprite::Draw(DrawPacket& i_DrawPacket)
{
	if(m_pSprite && m_pTexture){
		D3DXMATRIX mAspectRate,mAll;
		D3DXVECTOR2 AspectRate = DxDevice::getAspectRate();
		D3DXMatrixScaling(&mAspectRate,AspectRate.x,AspectRate.y,1.0f);
	    D3DXMatrixMultiply(&mAll,&m_mMatrix,&mAspectRate);
		m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			m_pSprite->SetTransform( &mAll );
			m_pSprite->Draw(m_pTexture, m_pRect,
				&m_vCenter, &m_vOffsetPos, m_Color.dwColor );
		}
		m_pSprite->End();
	}
}
/**************************************************************************
 SpriteObject ��`��
***************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FSpriteObject(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
////            �F    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  LPDIRECT3DTEXTURE9 pTexture     // �\��t�������e�N�X�`��
////            �F  D3DXVECTOR3 &vScale             // �傫��
////            �F  D3DXVECTOR3 &vRot               // �O����]
////            �F  D3DXVECTOR3 &vPos               // �ݒu���W
////            �F  RECT* pRect                     // �`�悵�����͈�(NULL�őS�̂�`��)
////            �F  D3DXVECTOR3& vCenter            // ���S
////            �F  D3DXVECTOR3& vOffsetPos         // �I�t�Z�b�g���W
////            �F  Color color = 0xFFFFFFFF        // �F
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
SpriteObject::SpriteObject(const LPDIRECT3DDEVICE9 pD3DDevice,const LPDIRECT3DTEXTURE9 pTexture,
			const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
			const RECT *pRect,const D3DXVECTOR3 &vCenter,const D3DXVECTOR3 &vOffsetPos,const Color color,
			const wiz::OBJID id)
			:Object(id)
			,PrimitiveSprite(pD3DDevice,pTexture,pRect,vCenter,vOffsetPos,color)
{
	try{
		//	: �����}�g���b�N�X���v�Z
		D3DXMATRIX mScale,mRot,mPos;
		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
		m_mMatrix = mScale * mRot * mPos ;
	}
	catch(...){
		SafeRelease(m_pSprite);
		//�ăX���[
		throw;
	}

};
/////////////////// ////////////////////
//// �֐���     �F~SpriteObject();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
SpriteObject::~SpriteObject(){
};
/////////////////// ////////////////////
//// �֐���     �Fvoid SpriteObject::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void SpriteObject::Draw(DrawPacket& i_DrawPacket)
{
	//	: �`��͐e�N���X�ɔC����
	PrimitiveSprite::Draw(i_DrawPacket);
};
/**************************************************************************
  ��`��
***************************************************************************/

RenderTargetSprite::RenderTargetSprite(BassPacket* i_BassPacket, UINT i_Width, UINT i_Height, wiz::OBJID id )
: m_sfRenderTarget( NULL )
, m_sfRenderTargetZ( NULL )
, m_ClientSize(i_Width,i_Height)
, Object(id)
, PrimitiveSprite( i_BassPacket->pD3DDevice,  NULL, NULL, g_vZero, g_vZero)
{
	//	: �e�N�X�`���𓮓I�ɐ�������i���U�S�O�s�N�Z���E�c�S�W�O�s�N�Z���A�R�Q�r�b�g�J���[�j
	D3DXCreateTexture( i_BassPacket->pD3DDevice, i_Width, i_Height, 0, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture );
	i_BassPacket->pD3DDevice->CreateDepthStencilSurface( i_Width, i_Height, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, FALSE, &m_sfRenderTargetZ, NULL );	//	�[�x�o�b�t�@�𐶐�
	m_pTexture->GetSurfaceLevel( 0, &m_sfRenderTarget );																	//	�e�N�X�`������T�[�t�F�C�X���擾


}
/////////////////// ////////////////////
//// �p�r       �Fvirtual void TargetRender( LPDIRECT3DDEVICE9 pD3DDevice
////            �F      vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�I�u�W�F�N�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,               // �I�u�W�F�N�g�̔z��
////            �F  Command i_DrawPacket.pCommand                         // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
////            �F
////
void RenderTargetSprite::TargetRender( RenderPacket& i_RenderPacket ){

	LPDIRECT3DDEVICE9 pd3dDevice = i_RenderPacket.pD3DDevice ;
    //	: ���݂̃����_�[�^�[�Q�b�g��ۑ�����
    D3DVIEWPORT9		defaultViewport ;	//	��ʂ̕`��̈�Ɋւ���f�[�^
    LPDIRECT3DSURFACE9	sfBackBuffer	= NULL,
    					sfBackBufferZ	= NULL ;
    pd3dDevice->GetViewport( &defaultViewport );
    pd3dDevice->GetRenderTarget( 0, &sfBackBuffer );
    pd3dDevice->GetDepthStencilSurface( &sfBackBufferZ );
    
    //	: �V���������_�[�^�[�Q�b�g��ݒ肷��
    //		�i�e�N�X�`���ɑ΂���`��ɐ؂�ւ���j
	D3DVIEWPORT9	newViewport	= { 0, 0, m_ClientSize.cx, m_ClientSize.cy, 0.0f, 1.0f } ;	//	��ʂ̍���[���畝640����480��`��̈�ɂ���
    pd3dDevice->SetViewport( &newViewport );
    pd3dDevice->SetRenderTarget( 0, m_sfRenderTarget );
    pd3dDevice->SetDepthStencilSurface( m_sfRenderTargetZ );

    // Clear the render target and the zbuffer 
    FAILED( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 255, 45, 50, 170 ), 1.0f, 0 ) );

    // Render the scene
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
		//	: ���f���̕ϊ��s���ݒ�
		D3DXMATRIX	m ;
		D3DXMatrixIdentity( &m );
		pd3dDevice->SetTransform( D3DTS_WORLD, &m );
		

        FAILED( pd3dDevice->EndScene() );
    }
    
    //	: �����_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂�
    pd3dDevice->SetViewport( &defaultViewport );
    pd3dDevice->SetRenderTarget( 0, sfBackBuffer );
    pd3dDevice->SetDepthStencilSurface( sfBackBufferZ );
    
    //	: �o�b�N�o�b�t�@��߂����̂ŁA�����͗p�ς�
    SAFE_RELEASE( sfBackBuffer );
    SAFE_RELEASE( sfBackBufferZ );
};

/////////////////// ////////////////////
//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////            �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
void RenderTargetSprite::Draw(DrawPacket& i_DrawPacket){
	PrimitiveSprite::Draw(i_DrawPacket);
}

}//end of namespace	base2Dobject.
}//end of namespace	wiz.