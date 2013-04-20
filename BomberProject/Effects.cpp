////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FMagnetica
//	�t�@�C����		�FDebug_Stage.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�f�o�b�N�p�X�e�[�W
//					��
//	namespace wiz;
//		class DebugStage : public MenuStage;
//		class DebugMenu  : public MenuStage;
//
#include "StdAfx.h"
#include "Effects.h"


namespace wiz{

SlidingEffect::SlidingEffect(LPDIRECT3DDEVICE9 pD3DDevice,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		Player* pPlayer,BYTE byFrameQty,fRect FirstRect,LPDIRECT3DTEXTURE9 pTexture )
	:m_pPlayer(pPlayer), m_byFrameQty(byFrameQty),m_byFrameNum(0)
	,PrimitiveBox(pD3DDevice,Diffuse,Specular,Ambient,pTexture)
{
	m_pFrameRectArray = new fRect[ m_byFrameQty ];

	m_pFrameRectArray[0] = FirstRect;
	for( BYTE i = 1; i < m_byFrameQty ; i++ ){
		m_pFrameRectArray[i].right	= m_pFrameRectArray[i].left +1 ;
		m_pFrameRectArray[i].top	= FirstRect.top;
		m_pFrameRectArray[i].left	= m_pFrameRectArray[i].right + FirstRect.right;
		m_pFrameRectArray[i].bottom	= FirstRect.bottom;
	}
}
SlidingEffect::~SlidingEffect(){
	SafeDeleteArr(m_pFrameRectArray);
}

}//	: wiz
