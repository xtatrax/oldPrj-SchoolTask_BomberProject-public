#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"

namespace wiz{
namespace bomberobject{

	const	int MAX_DIGIT_DEAD	= 4;
/**************************************************************************
 class Score : public Sprite;
 用途　：数字の描画用クラス
 担当者：佐藤涼
****************************************************************************/
class Score : public SpriteObject{
protected:
	D3DXVECTOR3	m_vPos;
	D3DXVECTOR3	m_vScale;
	int			m_iDigit;
	int			m_iScore;
	int			m_DigitArr[MAX_DIGIT_DEAD];
	bool		m_bFirst;
	PlayerCoil*	m_pCoil;
public:
	Score(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iDigit,
				Rect*		Rect	= NULL );
	virtual ~Score();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
	void	update_Matrix( int i );
};

/**************************************************************************
 class DeadScore : public Score;
 用途　：死亡回数描画クラス
 担当者：佐藤涼
****************************************************************************/
class DeadScore : public Score{
public:
	DeadScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect	= NULL );
	virtual ~DeadScore();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
};

/**************************************************************************
 class ArrivalPos : public Score;
 用途　：到達地点描画クラス
 担当者：佐藤涼
****************************************************************************/
class ArrivalPos : public Score{
public:
	ArrivalPos(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect	= NULL );
	virtual ~ArrivalPos();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
};
/**************************************************************************
 class Factory_Score;
 用途: メイン工場クラス
****************************************************************************/
class Factory_Score{
public:
/**************************************************************************
 Factory_Score(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Score( FactoryPacket* fpac ) ;
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
~Factory_Score() ;
};

}
}
