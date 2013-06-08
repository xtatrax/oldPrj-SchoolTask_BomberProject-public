////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Wall.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Wall ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"
namespace wiz{
namespace bomberobject{

extern class PlayerCoil ;

/*************************************************************************
class Title_Select  public SpriteObject

担当者：佐藤涼
用途　：タイトル画面のボタン
*************************************************************************/
class	Continue	: public SpriteObject{
	D3DXVECTOR3		m_vPos;
	bool			m_bMark;
	PlayerCoil*		m_pCoil;
public:
	Continue( LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,bool mark,
			D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
};

}
}