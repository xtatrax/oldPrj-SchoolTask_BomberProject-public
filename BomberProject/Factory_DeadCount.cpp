#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_DeadCount.h"
#include "BassItems.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
 DeadCount 定義部
***************************************************************************/
/**************************************************************************
 DeadCount(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
DeadCount::DeadCount(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect)
:SpriteObject( pD3DDevice, pTexture, vScale, g_vZero, vPos, Rect, g_vZero, g_vZero, 0x00FFFFFF )
,m_vPos( vPos )
,m_vScale( vScale )
,m_iDeadScore( 0 )
,m_bFirst( false )
,m_pCoil( NULL )
{
	m_Color.byteColor.a	= 0xFF;
	m_Color.byteColor.r	= 0xFF;
	m_Color.byteColor.g	= 0xFF;
	m_Color.byteColor.b	= 0xFF;
}

/**************************************************************************
 DeadCount::~DeadCount();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
DeadCount::~DeadCount(){
	m_pCoil	= NULL;
}

/**************************************************************************
 DeadCount::Draw(DrawPacket& i_DrawPacket);
 用途: 描画
 戻り値: なし
***************************************************************************/
void	DeadCount::Draw(DrawPacket& i_DrawPacket){
	for( int i = 0; i < MAX_DIGIT ; i++ ){
		update_Matrix( i );
		if( !m_bFirst ){
			if( m_DigitArr[i] != 0 )
				m_bFirst	= true;
			else if( i == MAX_DIGIT-1 )
				m_bFirst	= true;
		}
		if( m_bFirst )
			SpriteObject::Draw( i_DrawPacket );
	}
	m_bFirst	= false;
}

/**************************************************************************
 DeadCount::Update(UpdatePacket& i_UpdatePacket)
 用途: 更新
 戻り値: なし
***************************************************************************/
void	DeadCount::Update(UpdatePacket& i_UpdatePacket){

	if(m_pCoil == NULL){
		m_pCoil = (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(PlayerCoil));
	}
	else	m_iDeadScore	= m_pCoil->getDeadCount();

	int	iDigit	= 1000;
	for( int i = 0; i < MAX_DIGIT; i++ ){
		int	a	= m_iDeadScore / iDigit;
		if( a > 10 ){
			a	%= 10;
		}
		m_DigitArr[i]	= a;
		iDigit	= iDigit / 10;
	}

	//m_DigitArr[0]	= 0;
	//m_DigitArr[1]	= 2;
	//m_DigitArr[2]	= 3;
	//m_DigitArr[3]	= 1;
}

/**************************************************************************
 DeadCount::setMatrix(int i)
 用途: マトリックスの更新
 戻り値: なし
***************************************************************************/
void	DeadCount::update_Matrix(int i){
	m_pRect->left	= int( 51.2f*m_DigitArr[i] );
	m_pRect->right	= int( 51.2f*(m_DigitArr[i]+1) );

	D3DXMATRIX mScale,mRot,mPos;
	D3DXMatrixScaling(&mScale,m_vScale.x,m_vScale.y,m_vScale.z);
	D3DXMatrixTranslation(&mPos,m_vPos.x+(i*25.0f),m_vPos.y,m_vPos.z);
	m_mMatrix = mScale * mPos ;
}

/**************************************************************************
 Factory_DeadCount 定義部
****************************************************************************/
/**************************************************************************
 Factory_DeadCount::Factory_DeadCount(
	Factory_DeadCount *fpac
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_DeadCount::Factory_DeadCount(FactoryPacket *fpac){
	try{
		fpac->m_pVec->push_back(
			new SpriteObject( fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"DeadCountChar.png" ),
					D3DXVECTOR3( 0.7f, 0.7f, 0.0f ),
					g_vZero,
					D3DXVECTOR3( 800.0f, 10.0f, 0.0f ),					
					&Rect( 0, 0, 256, 64 ),
					g_vZero,
					g_vZero
			)
		);
		fpac->m_pVec->push_back(
			new DeadCount( fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"DeadScore.png" ),
					D3DXVECTOR3( 0.5f, 0.5f, 0.0f ),
					D3DXVECTOR3( 880.0f, 50.0f, 0.0f ),					
					&Rect( 0, 0, 512, 64 )
			)
		);
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_DeadCount::~Factory_DeadCount();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_DeadCount::~Factory_DeadCount(){
    //なにもしない
}

}
}
