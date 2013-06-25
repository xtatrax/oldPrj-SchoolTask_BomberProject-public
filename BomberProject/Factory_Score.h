#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"
#include "Factory_Goal.h"
#include "Factory_Title.h"
#include "Factory_Result.h"

namespace wiz{
namespace bomberobject{

	const	int MAX_DIGIT	= 6;
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
	bool		m_bTotal;
	PlayerCoil*	m_pCoil;
public:
	Score(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iScore,
				Rect*		Rect	= NULL,
				wiz::OBJID	id		= OBJID_UI_SCORE
	);
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
 class ScratchPoint : public Score;
 用途　：到達地点描画クラス
 担当者：佐藤涼
****************************************************************************/
class ScratchPoint : public Score{
public:
	ScratchPoint(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect	= NULL );
	virtual ~ScratchPoint();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);

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
 class TimeScore : public Score;
 用途　：到達地点描画クラス
 担当者：佐藤涼
****************************************************************************/
class TimeScore : public Score{
	int		m_iTime;
	float	m_fElapsedTime;
public:
	TimeScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iTime,
				Rect*		Rect	= NULL );
	virtual ~TimeScore();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
	void	setTime(){
		m_iTime	= LIMIT_TIME;
	}

};

/**************************************************************************
 class AnimationScore : public Score;
 用途　：アニメーションスコア描画クラス
 担当者：佐藤涼
****************************************************************************/
class AnimationScore : public Score{
	int		m_iDrawScore;		//描画するスコア
	int		m_iResultScore;		//最終的なスコア
	bool	m_bNext;			//アニメーションするスコアを次に進める
	bool	m_bClickRock;		//
	float	m_fTransRate;
	float	m_fTime;
	int		m_iDight;
public:
	AnimationScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iScore,
				int			iDight,
				bool		bTotal	= false,
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
	Rank*				m_pRank;
	AnimationScore*		m_pMaxPos;		//最高位置用アニメーションスコアのポインタ
	AnimationScore*		m_pScratch;		//
	AnimationScore*		m_pDead;		//死亡回数用アニメーションスコアのポインタ
	AnimationScore*		m_pTotal;		//
	SpriteObject*		m_pRate_10;
	SpriteObject*		m_pRate_30;
	SpriteObject*		m_pRate_1;
	LPDIRECT3DTEXTURE9	m_pDeadTex;		//死亡回数スコアのテクスチャ
	LPDIRECT3DTEXTURE9	m_pMaxPosTex;	//最高位置スコアのテクスチャ
	LPDIRECT3DTEXTURE9	m_pRate10Tex;	//
	LPDIRECT3DTEXTURE9	m_pRate30Tex;	//
	LPDIRECT3DTEXTURE9	m_pRate1Tex;	//
	int					m_iNowDraw;		//アニメーションさせたいスコアの番号
	Result_Rank			m_ResultRank;
public:
	ResultScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pDeadTex,
				LPDIRECT3DTEXTURE9	pMaxPosTex,
				LPDIRECT3DTEXTURE9	pRate10Tex,
				LPDIRECT3DTEXTURE9	pRate30Tex,
				LPDIRECT3DTEXTURE9	pRate1Tex,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iDeadScore,
				int			iMaxPosScore,
				int			iScratchScore,
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
