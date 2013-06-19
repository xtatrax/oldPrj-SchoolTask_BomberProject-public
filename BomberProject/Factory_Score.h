#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"
#include "Factory_Goal.h"

namespace wiz{
namespace bomberobject{

	const	int MAX_DIGIT	= 5;
/**************************************************************************
 class Score : public Sprite;
 用途　：数字の描画用クラス
 担当者：佐藤涼
****************************************************************************/
class Score : public SpriteObject{
protected:
	D3DXVECTOR3	m_vPos;
	D3DXVECTOR3	m_vScale;
	int			m_iScore;
	int			m_DigitArr[MAX_DIGIT];
	bool		m_bFirst;
	PlayerCoil*	m_pCoil;
public:
	Score(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iScore,
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
	int		m_iMaxPosY;	//最高到達点
public:
	ArrivalPos(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect	= NULL );
	virtual ~ArrivalPos();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);

	//ゲッター
	int	getMaxPosY(){
		return	m_iMaxPosY;
	}
};
/**************************************************************************
 class GoalPos : public Score;
 用途　：到達地点描画クラス
 担当者：佐藤涼
****************************************************************************/
class GoalPos : public Score{
	GoalObject*	m_pGoalObject;
public:
	GoalPos(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect	= NULL );
	virtual ~GoalPos();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
};

/**************************************************************************
 class AnimationScore : public Score;
 用途　：アニメーションスコア描画クラス
 担当者：佐藤涼
****************************************************************************/
class AnimationScore : public Score{
	int		m_iDrawScore;
	int		m_iResultScore;
	bool	m_bNext;
public:
	AnimationScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iScore,
				Rect*		Rect	= NULL);
	virtual ~AnimationScore();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);

	bool	getNext(){
		return	m_bNext;
	}
};

/**************************************************************************
 class ResultScore : public Score;
 用途　：リザルトスコア描画クラス
 担当者：佐藤涼
****************************************************************************/
class ResultScore : public Score{
	AnimationScore*		m_pDead;
	AnimationScore*		m_pMaxPos;
	LPDIRECT3DTEXTURE9	m_pDeadTex;
	LPDIRECT3DTEXTURE9	m_pMaxPosTex;
	int					m_iNowDraw;
public:
	ResultScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pDeadTex,
				LPDIRECT3DTEXTURE9	pMaxPosTex,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iDeadScore,
				int			iMaxPosScore,
				Rect*		rect	= NULL);
	virtual ~ResultScore();

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
