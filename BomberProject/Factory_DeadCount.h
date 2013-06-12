#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"

namespace wiz{
namespace bomberobject{

	const	int MAX_DIGIT	= 4;
/**************************************************************************
 class DeadCount : public Sprite;
****************************************************************************/
class DeadCount : public SpriteObject{
	D3DXVECTOR3	m_vPos;
	D3DXVECTOR3	m_vScale;
	int			m_iDeadScore;
	int			m_DigitArr[MAX_DIGIT];
	bool		m_bFirst;
	PlayerCoil*	m_pCoil;
public:
	DeadCount(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect	= NULL );
	virtual ~DeadCount();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
	void	update_Matrix( int i );
};

/**************************************************************************
 class Factory_DeadCount;
 用途: メイン工場クラス
****************************************************************************/
class Factory_DeadCount{
public:
/**************************************************************************
 Factory_DeadCount(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_DeadCount( FactoryPacket* fpac ) ;
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
~Factory_DeadCount() ;
};

}
}
