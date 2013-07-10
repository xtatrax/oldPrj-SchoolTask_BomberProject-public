////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Structs.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：多所で利用される構造体郡
//					▼
//	namespace wiz;
//		struct Command			;
//		struct UpdatePacket		;
//		struct RenderPacket		;
//		struct FactoryPacket	;
//		struct Color			;
//		struct FlexibleVertex	;
//		struct OBB				;
//		struct AABB				;
//		struct Sphere			;
//		struct RENDERSTATE_PARAM	;
//		struct MapPartsStatus			;
//
#pragma once

#include "StdAfx.h"
#include "TextureManager.h"

//#include "DxDevice.h"
namespace wiz{
class  Object ; 
class  Stage ;
class  TextureManager ;
class  StageLoader;
struct CONTROLER_STATE;
class  DxDevice;
namespace system{
class  Sound ;
}
namespace functions {
extern void EarnFromMeshOBB(const LPD3DXBASEMESH i_pMesh,D3DXVECTOR3& o_vPos ,D3DXVECTOR3& o_vSize);
}
using namespace functions ;
namespace structs{
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 struct SaveData : public TLIB::BassSaveaPacketDat;
 用途: セーブデータ
****************************************************************************/
struct SaveData : public TLIB::BassSaveaPacketDat{
private:
	float fDataStructVer ;
public:
	DWORD dwStageNum	;
	DWORD dwCheckPoint	;
	DWORD dwDeadNum		;
	
	SaveData()
	:TLIB::BassSaveaPacketDat(RCVAL_SAVEDATA_IDENTIFIER_H,RCVAL_SAVEDATA_IDENTIFIER_L)
	,fDataStructVer( 0.1f )
	,dwStageNum(0)
	,dwCheckPoint(0)
	,dwDeadNum(0)
	{
		
	}

};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 struct Command;
 用途: シーン内、ステージ内でやり取りされるコマンド
 ＊コマンド内容の定義は、各コンテンツにまかせる
****************************************************************************/
struct Command{
	DWORD m_Command;	
	DWORD m_Param1;
	DWORD m_Param2;
	DWORD m_Param3;

	Command(DWORD Command = 0, DWORD m_Param1 = 0, DWORD m_Param2 = 0, DWORD m_Param3 = 0)
		:m_Command(Command),m_Param1(m_Param1),m_Param2(m_Param2),m_Param3(m_Param3)

	{}
	void Clear(){
		m_Command = m_Param1 = m_Param2 = m_Param3 = 0;
	}
	~Command(){
		Clear();
	}
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class Context;
 用途: シーンデータ構造体
 ユーザーデータは派生クラスを作成して使用する
****************************************************************************/
class Context{
	DWORD m_Command;	
	DWORD m_Param1;
	DWORD m_Param2;
	//タイマー。経過秒を計る
	Avoidance::Timer m_Timer;
	//1回のタイムスパン
	FLOAT m_TimeSpan;
	//ゲームトータル時間
	FLOAT m_TotalTime;
public:
/**************************************************************************
 void ElapsedTime();
 用途: タイマーを進める
 戻り値: なし
***************************************************************************/
	void ElapsedTime(){
		if(m_Timer.IsStopped()){
			//タイマーが止まっていたら動かす
			m_Timer.Start();
		}
		else{
			//タイマーを進める
			m_TimeSpan = m_Timer.GetElapsedTime();
			m_TotalTime += m_TimeSpan;
		}
	}
/**************************************************************************
 FLOAT GetTimeSpan();
 用途: タイムスパンを得る。
 戻り値: タイムスパン
***************************************************************************/
	FLOAT GetTimeSpan(){
		return m_TimeSpan;
	}
/**************************************************************************
 FLOAT GetTotalTime();
 用途: トータル時間を得る。
 戻り値: トータル時間
***************************************************************************/
	FLOAT GetTotalTime(){
		return m_TotalTime;
	}
/**************************************************************************
 void StopTimer();
 用途: タイマーをとめる
 戻り値: なし
***************************************************************************/
	void StopTimer(){
		if(!m_Timer.IsStopped()){
			m_Timer.Stop();
		}
	}
/**************************************************************************
 Context();
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	Context():m_Timer(),
		m_TimeSpan(0.001f),m_TotalTime(0){
		m_Timer.Start();
	}
/**************************************************************************
 virtual ~Context();
 用途: 仮想デストラクタ
 戻り値: なし
***************************************************************************/
	virtual~Context(){}

	void operator = ( const Command other ) {
		m_Command = other.m_Command ;
		m_Param1  = other.m_Param1  ;
		m_Param2  = other.m_Param2  ;	
	};

};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/


/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************//
// struct UpdatePacket;
//
// 担当者  : 鴫原 徹
// 用途    : アップデート関数郡に流れるデータ
//**************************************************************************//
struct BassPacket{
	friend class  DxDevice ;
	friend class  wiz::Stage ;
//////////
//	: プロテクト変数
protected:
	wiz::Stage*				m_pStage		;
	LPDIRECT3DDEVICE9		m_pD3DDevice	;	// デバイス
	TLIB::Tempus2*			m_pTime			;	// 時間
	Command*				m_pCommand		;	// コマンド
//////////
//	: プロテクト関数
private:
	void SetStage( wiz::Stage* pStage ){ m_pStage = pStage ; }
//////////
//	: 公開関数
public:
	/////////////////// ////////////////////
	//// 関数名     ：BassPacket::BassPacket()
	//// カテゴリ   ：デフォルトコンストラクタ
	//// 用途       ：実体を生成
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 備考       ：
	////            ：
	////
	BassPacket()
		:m_pD3DDevice( NULL )
		,m_pTime( NULL )
		,m_pCommand( NULL )
	
	{}
	/////////////////// ////////////////////
	//// 関数名     ：BassPacket::BassPacket(BassPacket& i_OtherPacket)
	//// カテゴリ   ：コピーコンストラクタ
	//// 用途       ：実体を生成
	//// 引数       ：  BassPacket& i_OtherPacket //  : 他のパケットデータ
	//// 戻値       ：なし
	//// 備考       ：
	////            ：
	////
	BassPacket(BassPacket& i_OtherPacket)
		:m_pStage(		i_OtherPacket.m_pStage		)
		,m_pD3DDevice(	i_OtherPacket.m_pD3DDevice	)
		,m_pTime(		i_OtherPacket.m_pTime		)
		,m_pCommand(	i_OtherPacket.m_pCommand	)
	
	{}
	/////////////////// ////////////////////
	//// 関数名     ：TLIB::Tempus2* BassPacket::GetTime() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：時間管理クラスへのポインターを獲得
	//// 引数       ：なし
	//// 戻値       ：時間管理クラスへのポインタ
	//// 備考       ：
	////            ：
	////
	TLIB::Tempus2* GetTime() const;
	/////////////////// ////////////////////
	//// 関数名     ：LPDIRECT3DDEVICE9 BassPacket::GetDevice() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：現在のデバイスを獲得
	//// 引数       ：なし
	//// 戻値       ：デバイスのポインタ
	//// 備考       ：
	////            ：
	////
	LPDIRECT3DDEVICE9 GetDevice() const;
	/////////////////// ////////////////////
	//// 関数名     ：LPTATRATEXTURE AddTexture( const wchar_t* sTextureName )
	//// カテゴリ   ：ゲッター
	//// 用途       ：指定のテクスチャーへのポインターを返します
	//// 引数       ：  const wchar_t* sTextureName      //  : 読み込みたい画像データのファイル名
	//// 戻値       ：テクスチャーへのポインタ
	//// 備考       ：初回の参照の際は新規で画像を読み込みます
	////            ：次回以降同じ画像を要求された場合は前回と同じポインターを返します
	////            ：またファイルの読み込みに失敗した際にはNULLが帰ります
	////            ：ファイル名は"作業ディレクトリ/Media/Textures"からの相対パスで指定出来ます
	////            ：
	////
	LPTATRATEXTURE AddTexture( const wchar_t* sTextureName );
	/////////////////// ////////////////////
	//// 関数名     ：void BassPacket::AddButton( Object* pButton )
	//// カテゴリ   ：セッター
	//// 用途       ：ステージにボタンオブジェクトセットします
	//// 引数       ：  Object*      pButton         //  : ボタンオブジェクトへのポインタ
	//// 戻値       ：なし
	//// 備考       ：
	////            ：
	////
	void AddButton( Object* pButton );
	/////////////////// ////////////////////
	//// 関数名     ：void BassPacket::AddObject( Object* pObje )
	//// カテゴリ   ：セッター
	//// 用途       ：ステージにオブジェクトをセットします
	//// 引数       ：  Object*       pObje          //  : セットするオブジェクトへのポインタ
	//// 戻値       ：なし
	//// 備考       ：Objectクラスを継承しているものならばなんでも入ります
	////            ：
	////
	void AddObject( Object* pObje );
	/////////////////// ////////////////////
	//// 関数名     ：void BassPacket::SearchSoundAndPlay( const char* sSoundName )
	//// カテゴリ   ：サウンドプレイヤー
	//// 用途       ：XACTに登録されているSOUNDデータを再生します
	//// 引数       ：  const char*    sSoundName          //  : サウンド名
	//// 戻値       ：なし
	//// 備考       ：XACTに登録されているものしか再生出来ません
	////            ：サウンドが再生されない場合は以下の項目を確認してください
	////            ：XACTに登録されているか
	////            ：sSoundName に渡した名前が正しいか
	////            ：音量が小さ過ぎないか
	////            ：
	////
	void SearchSoundAndPlay( const char* sSoundName );
	/////////////////// ////////////////////
	//// 関数名     ：void BassPacket::SearchSoundAndStop( const char* sSoundName )
	//// カテゴリ   ：サウンドプレイヤー
	//// 用途       ：XACTSOUNDで再生されている音を停止します
	//// 引数       ：  const char*    sSoundName          //  : サウンド名
	//// 戻値       ：なし
	//// 備考       ：
	////            ：
	////
	void SearchSoundAndStop( const char* sSoundName );
	/////////////////// ////////////////////
	//// 関数名     ：void BassPacket::SearchWaveAndPlay( const char* sSoundName )
	//// カテゴリ   ：サウンドプレイヤー
	//// 用途       ：XACTに登録されているWAVEデータを再生します
	//// 引数       ：  const char*    sSoundName          //  : サウンド名
	//// 戻値       ：なし
	//// 備考       ：XACTに登録されているものしか再生出来ません
	////            ：サウンドが再生されない場合は以下の項目を確認してください
	////            ：XACTに登録されているか
	////            ：sSoundName に渡した名前が正しいか
	////            ：音量が小さ過ぎないか
	////            ：
	////
	void SearchWaveAndPlay( const char* sWaveName );
	/////////////////// ////////////////////
	//// 関数名     ：void BassPacket::SearchWaveAndStop( const char* sSoundName )
	//// カテゴリ   ：サウンドプレイヤー
	//// 用途       ：XACTWAVEで再生されている音を停止します
	//// 引数       ：  const char*    sSoundName          //  : サウンド名
	//// 戻値       ：なし
	//// 備考       ：
	////            ：
	////
	void SearchWaveAndStop( const char* sWaveName );
	/////////////////// ////////////////////
	//// 関数名     ：void BassPacket::SoundStop( const char* sSoundName )
	//// カテゴリ   ：サウンドプレイヤー
	//// 用途       ：XACTで再生されている音をWAVE/SOUND問わずに停止します
	//// 引数       ：  const char*    sSoundName          //  : サウンド名
	//// 戻値       ：なし
	//// 備考       ：
	////            ：
	////
	void SoundStop( const char* sSoundName );
	/////////////////// ////////////////////
	//// 関数名     ：void BassPacket::PushCommand( const Command Com )
	//// カテゴリ   ：セッター
	//// 用途       ：コマンドをセットします(＊仕様改変予定)
	//// 引数       ：  const Command Com          //  : 追加するコマンド
	//// 戻値       ：なし
	//// 備考       ：
	////            ：
	////
	void PushCommand( const Command	Com );	//	: 現状実質SetCommand 
	/////////////////// ////////////////////
	//// 関数名     ：void BassPacket::ClearCommand( ) const
	//// カテゴリ   ：セッター
	//// 用途       ：コマンドをクリアします
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 備考       ：
	////            ：
	////
	void ClearCommand( ) const;
	/////////////////// ////////////////////
	//// 関数名     ：Command BassPacket::PopCommand( ) const
	//// カテゴリ   ：ゲッター
	//// 用途       ：コマンドを獲得します
	//// 引数       ：なし
	//// 戻値       ：コマンド
	//// 備考       ：
	////            ：
	////
	Command PopCommand( ) const;

	/////////////////// ////////////////////
	//// 関数名     ：Object* SearchObjectFromID(
	////            ：    DWORD                                i_dwID             ,
	////            ：    vector<Object*>::size_type*          o_Point     = NULL ,
	////            ：    vector<Object*>*                     o_pVec      = NULL ,
	////            ：    vector<vector<Object*>::size_type>*  o_PointList = NULL );
	//// カテゴリ   ：ゲッター
	//// 用途       ：OBJIDを元にオブジェクトを探す
	//// 引数       ：  DWORD                                i_dwID      //  :  [IN] 探したいオブジェクトのOBJID
	////            ：  vector<Object*>::size_type*          o_Point     //  : [OUT] 見つけた場所
	////            ：  vector<Object*>*                     o_pVec      //  : [OUT] 複数見つけた場合のオブジェクト一覧
	////            ：  vector<vector<Object*>::size_type>*  o_PointList //  : [OUT] 複数見つけた場合のオブジェクトの場所一覧
	//// 戻値       ：一番最初に発見したオブジェクトへのポインタ
	//// 備考       ：
	////            ：
	////
	Object* SearchObjectFromID( 
				DWORD									i_dwID,
				vector<Object*>::size_type*				o_Point		= NULL,
				vector<Object*>*						o_pVec		= NULL,
				vector<vector<Object*>::size_type>*		o_PointList = NULL
	);

	/////////////////// ////////////////////
	//// 関数名     ：Object* SearchObjectFromID( 
	////            ：    const type_info&         i_typeinfo           ,
	////            ：    vector<Object*>*         o_pVec      = NULL   );
	//// カテゴリ   ：ゲッター
	//// 用途       ：OBJIDを元にオブジェクトを探す
	//// 引数       ：  const type_info&           i_typeinfo      //  :  [IN] 探したいオブジェクトのtype_info
	////            ：  vector<Object*>*           o_pVec          //  : [OUT] 複数見つけた場合のオブジェクト一覧
	//// 戻値       ：一番最初に発見したオブジェクトへのポインタ
	//// 備考       ：
	////            ：
	////
	Object* SearchObjectFromTypeID(
				const type_info&						i_typeinfo,
				vector<Object*>*						o_pVec		= NULL
	);
};
//**************************************************************************//
// struct UpdatePacket;
//
// 担当者  : 鴫原 徹
// 用途    : アップデート関数郡に流れるデータ
//**************************************************************************//
struct UpdatePacket : public BassPacket{
	const CONTROLER_STATE*	m_pCntlState	;
	UpdatePacket::UpdatePacket()
		:m_pCntlState( NULL ){
	};
	UpdatePacket::UpdatePacket( BassPacket& i_BassPacket )
		:BassPacket(i_BassPacket)
		,m_pCntlState( NULL ){}
	;
};
//**************************************************************************//
// struct RenderPacket;
//
// 担当者  : 鴫原 徹
// 用途    : レンダー関数群に流れるデータ
//**************************************************************************//
struct RenderPacket : public BassPacket{
};
//**************************************************************************//
// struct DrawPacket;
//
// 担当者  : 鴫原 徹
// 用途    : ドロー関数群に流れるデータ
//**************************************************************************//
struct DrawPacket : public BassPacket{
};



/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/


/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************//
// struct FactoryPacket;
//
// 担当者  : 鴫原 徹
// 用途    : ファクトリーに渡すパケットデータ
//**************************************************************************//
struct FactoryPacket : public BassPacket{
public:
	//ダイアログステージかどうか
	bool m_IsDialog;
public:
	FactoryPacket(		LPDIRECT3DDEVICE9 i_pD3DDevice, bool i_IsDialog, Command* i_pCommand, Stage* i_pStage )
		:m_IsDialog(	i_IsDialog		)
	{

		this->m_IsDialog	= i_IsDialog	;
		this->m_pD3DDevice	= i_pD3DDevice	;
		this->m_pCommand	= i_pCommand	;
		this->m_pStage		= i_pStage		;
		this->m_pTime		= NULL			;

	}
	vector<Object*>* GetObjectVector();
	void SetSound( system::Sound*  pSound  );
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

//**************************************************************************
// union Color;
//
// 担当者  : 鴫原 徹
// 用途    : DWORDColorを管理しやすくする
//**************************************************************************
union Color {
	DWORD dwColor;
	struct {BYTE b , g , r , a ;}byteColor;
	Color(){};
	Color(DWORD Color):dwColor(Color){};
	Color(BYTE A ,BYTE R ,BYTE G , BYTE B )
	{ byteColor.a = A;byteColor.r = R;byteColor.g = G;byteColor.b = B;};
	Color& operator = (DWORD other){ dwColor = other ; return *this; };
	operator DWORD(){ return dwColor; }
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************//
// struct FlexibleVertex;
//
// 担当者  : 鴫原 徹
// 用途    : フレキシブルな頂点を扱う
// 備考    : かなり重くなることが予想されます
//**************************************************************************//
struct FlexibleVertex{
	D3DXVECTOR3 *pos;
	float       *rhw;
	float		*blend1;
	float		*blend2;
	float		*blend3;
	D3DXVECTOR3 *normal;
	float		*pointSize;
	DWORD		*diffuse;
	DWORD		*specular;
	//D3DXVECTOR4	*TexSet1;
	//D3DXVECTOR4	*TexSet2;
	//D3DXVECTOR4	*TexSet3;
	//D3DXVECTOR4	*TexSet4;
	//D3DXVECTOR4	*TexSet5;
	//D3DXVECTOR4	*TexSet6;
	//D3DXVECTOR4	*TexSet7;
	//D3DXVECTOR4	*TexSet8;
	FlexibleVertex(BYTE* vBuffer,DWORD FVF)
		:pos(NULL),rhw(NULL),blend1(NULL),blend2(NULL),blend3(NULL)
		,normal(NULL),pointSize(NULL),diffuse(NULL),specular(NULL)
	{
		BYTE floatByteNum  = 4;
		BYTE DwordByteNum  = 4;
		BYTE VectorByteNum = floatByteNum*3;
		BYTE Address = 0;

		//////////
		//	: 頂点ポインタ
		pos = ( D3DXVECTOR3* )  vBuffer;
		Address += VectorByteNum;

		//////////
		//	: RHWポインタ
		if( FVF & D3DFVF_XYZRHW ){
			rhw = ( float* )( vBuffer + Address );
			Address += VectorByteNum + floatByteNum;
		}

		//////////
		//	: ベータ1
		if( FVF & D3DFVF_XYZB1  ){
			blend1 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
		}

		//////////
		//	: ベータ2
		if( FVF & D3DFVF_XYZB2  ){
			blend1 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
			blend2 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
		}

		//////////
		//	: ベータ3
		if( FVF & D3DFVF_XYZB3  ){
			blend1 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
			blend2 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
			blend3 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
		}

		//////////
		//	: ノーマル
		if( FVF & D3DFVF_NORMAL ){
			normal = ( D3DXVECTOR3* )( vBuffer + Address );
			Address +=  VectorByteNum;
		}

		//////////
		//	: ポイントサイズ
		if( FVF & D3DFVF_PSIZE ){
			pointSize = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
		}

		//////////
		//	: ディフューズ
		if( FVF & D3DFVF_DIFFUSE  ){
			diffuse = ( DWORD* )( vBuffer + Address );
			Address +=  DwordByteNum;
		}

		//////////
		//	: スペキュラー
		if( FVF & D3DFVF_SPECULAR  ){
			specular = ( DWORD* )( vBuffer + Address ); 
			Address +=  DwordByteNum;
		}
	}
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************//
// struct OBB;
//
// 担当者  : なし(山ノ井先生のひな形より)
// 用途    : OBBボリューム境界
//**************************************************************************//
struct OBB{
    D3DXVECTOR3 m_Center;   //中心点の座標
	D3DXMATRIX	m_mRot;
    D3DXVECTOR3 m_Rot[3];   //XYZ の各座標軸の傾きを表す方向ベクトル
    D3DXVECTOR3 m_Size;     //OBB の各座標軸に沿った長さの半分（中心点から面までの長さ）
	OBB():m_Center(g_vZero),m_Size(g_vOne){
		m_Rot[0] = g_vZero;
		m_Rot[1] = g_vZero;
		m_Rot[2] = g_vZero;
	};
	OBB(D3DXVECTOR3 vScale,D3DXVECTOR3 vRot,D3DXVECTOR3 vPos){
		//衝突判定用のOBBの初期化
		m_Center = vPos   ;
		//m_Size   = vScale ;
		m_Size   = vScale * 0.5f ;
		D3DXMATRIX mRot   ;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		m_mRot = mRot ;
		m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
	};
	OBB(D3DXVECTOR3 vScale,D3DXQUATERNION vQt,D3DXVECTOR3 vPos){
		//衝突判定用のOBBの初期化
		m_Center = vPos   ;
		//m_Size   = vScale ;
		m_Size   = vScale * 0.5f ;
		//vQt		*= vQt ; 
		//D3DXQuaternionNormalize(&vQt,&vQt);

		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&vQt);
		m_mRot = mRot ;
		m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
	};
	OBB(LPD3DXMESH pMesh){
		//衝突判定用のOBBの初期化
		EarnFromMeshOBB(pMesh,m_Center,m_Size);
		D3DXMATRIX mRot   ;
		D3DXMatrixIdentity(&mRot);
		m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
	};
	void setRot(D3DXVECTOR3 vRot){
		D3DXMATRIX mRot   ;
		D3DXMatrixIdentity(&mRot);
		m_mRot = mRot ;
		m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
	}

};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 struct AABB;
 用途: AABBボリューム境界
****************************************************************************/
struct AABB{
    D3DXVECTOR3 m_Min;     //小さいほうの座標
    D3DXVECTOR3 m_Max;     //大きいほうの座標
	AABB(){}
	AABB(D3DXVECTOR3& Min,D3DXVECTOR3& Max)
		:m_Min(Min),m_Max(Max){}
	AABB(D3DXVECTOR3& Center,FLOAT XSize,FLOAT YSize,FLOAT ZSize){
		FLOAT xh = XSize / 2.0f;
		FLOAT yh = YSize / 2.0f;
		FLOAT zh = ZSize / 2.0f;

		m_Min.x = Center.x - xh;
		m_Max.x = Center.x + xh;

		m_Min.y = Center.y - yh;
		m_Max.y = Center.y + yh;

		m_Min.z = Center.z - zh;
		m_Max.z = Center.z + zh;
	}
	void GetCenter(D3DXVECTOR3& Pos){
		Pos.x = (m_Min.x + m_Max.x) / 2.0f;
		Pos.y = (m_Min.y + m_Max.y) / 2.0f;
		Pos.z = (m_Min.z + m_Max.z) / 2.0f;
	}
	void Move(D3DXVECTOR3& MoveVec){
		m_Min += MoveVec;
		m_Max += MoveVec;
	}
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 struct SPHERE;
 用途: 球データ
****************************************************************************/
struct SPHERE
{
    D3DXVECTOR3 m_Center;	//中心点の座標
    float m_Radius;			//半径
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************//
// struct RENDERSTATE_PARAM;
//
// 担当者  : 鴫原 徹
// 用途    : レンダータイプとデータのセットを記憶しておきたい!
//
//**************************************************************************//
struct RENDERSTATE_PARAM{
	D3DRENDERSTATETYPE	renderType;
	DWORD				value;
	//RENDERSTATE_PARAM(){};
	//RENDERSTATE_PARAM(D3DRENDERSTATETYPE i_RenderType, DWORD i_dwValue)
	//	:renderType(i_RenderType), value(i_dwValue){};
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/



}//end of namespace structs.
using namespace structs;
}//end of namespace wiz.
