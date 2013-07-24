////////////////////////////// //////////////////////////////
//	プロジェクト	：TATRA-Library
//	ファイル名		：Tempus.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：時間関係の関数
//					▼
//	namespace wiz;
//		class Tempus ;
//		class Tempus2 ;
//
#ifndef TLIB_TEMPUS
#define TLIB_TEMPUS
namespace TLIB{
#define DWMSTOFS( DW ) ((float)(DW) / 1000.0f)/*Dword miri second to float Second*/
#define MSTOS( DW )    ((DW) * 1000.0f)
//**************************************************************************//
// class Tempus ;
// 担当  : 鴫原徹
// 用途  : 時間を管理するクラス
// 備考  : 静的
//**************************************************************************//
class Tempus
{
	static DWORD m_dwStartGameTime;		//	: 実行ファイルが起動した時のシステムミリ秒
	static DWORD m_dwFrameAccumulator ;	//	: 起動からの経過フレーム数
	static DWORD m_dwOFOTime ;			//	: 前フレームのクロック時間
	static DWORD m_dwElapsedTime;		//	: １フレームにかかった時間
	static DWORD m_dwFixFpsTime ;		//	: フレーム処理の規制時間

	static float m_fOneSecondCounter;
	static bool  m_bOneSecondSignal;

	static float m_fFps;				//	: FPS
	static DWORD m_dwFFA;				//	: FPS計算用にフレーム数を蓄積する
	static DWORD m_dwLFT;				//	: 最後にFPSを計算してからの時間
//::::: 拾い物 :::::://
	static void	Fps_Calculation();
public:
	/////////////////// ////////////////////
	//// 関数名     ：Tempus::Tempus();
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：インスタンスの生成
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	Tempus(void);

	/////////////////// ////////////////////
	//// 関数名     ：Tempus::~Tempus();
	//// カテゴリ   ：デストラクタ
	//// 用途       ：インスタンスの破棄
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	~Tempus(void);

	/////////////////// ////////////////////
	//// 関数名     ：static void Tempus::TimeUpdate();
	//// カテゴリ   ：メンバ関数
	//// 用途       ：時間の更新
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	static void    TimeUpdate();

	/////////////////// ////////////////////
	//// 関数名     ：static DWORD Tempus::TimeGetTime();
	//// カテゴリ   ：メンバ関数
	//// 用途       ：起動からの経過時間を返す
	//// 引数       ：なし
	//// 戻値       ：起動からの経過時間(㍉秒)
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	static DWORD   TimeGetTime();

	/////////////////// ////////////////////
	//// 関数名     ：static double TwoDwTime2ElapsedTime( DWORD dwOldTime, DWORD dwNowTime );
	//// カテゴリ   ：メンバ関数
	//// 用途       ：2つの時間の差を浮動少数秒で返す
	//// 引数       ：  DWORD dwOldTime   //  : 前の時間
	////            ：  DWORD dwNowTime   //  : 今の時間
	//// 戻値       ：2つの時間の差(秒)
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	static double   TwoDwTime2ElapsedTime( DWORD dwOldTime, DWORD dwNowTime );

	/////////////////// ////////////////////
	//// 関数名     ：static double Tempus::getWorkTime();
	//// カテゴリ   ：ゲッター
	//// 用途       ：起動からの経過時間(TimeUpdate時現在)
	//// 引数       ：なし
	//// 戻値       ：起動からの経過時間(秒)
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	static double  getWorkTime();

	/////////////////// ////////////////////
	//// 関数名     ：static double Tempus::getElapsedTime();
	//// カテゴリ   ：ゲッター
	//// 用途       ：１フレームの経過時間を返す
	//// 引数       ：なし
	//// 戻値       ：経過時間(秒)
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	static double  getElapsedTime();

	/////////////////// ////////////////////
	//// 関数名     ：static double Tempus::getFps();
	//// カテゴリ   ：ゲッター
	//// 用途       ：フレームレートの計算
	//// 引数       ：なし
	//// 戻値       ：フレームレート
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	static double  getFps();

	/////////////////// ////////////////////
	//// 関数名     ：static double Tempus::getClockSec();
	//// カテゴリ   ：ゲッター
	//// 用途       ：秒の獲得
	//// 引数       ：なし
	//// 戻値       ：秒
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	static double  getClockSec();

	/////////////////// ////////////////////
	//// 関数名     ：static double Tempus::getClock();
	//// カテゴリ   ：ゲッター
	//// 用途       ：clock()
	//// 引数       ：なし
	//// 戻値       ：clock()
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	static clock_t getClock();

	/////////////////// ////////////////////
	//// 関数名     ：static bool Tempus::OneSecondSignal();
	//// カテゴリ   ：ゲッター
	//// 用途       ：一秒シグナル
	//// 引数       ：なし
	//// 戻値       ：一秒シグナル
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	static bool OneSecondSignal();
	//static void  FixedFPS(int i_iFPS);
};

//**************************************************************************//
// class Tempus2 ;
// 担当  : 鴫原徹
// 用途  : 時間を管理するクラス
// 備考  : 
//**************************************************************************//
class Tempus2
{
	DWORD m_dwStartGameTime;		//	: 実行ファイルが起動した時のシステムミリ秒
	DWORD m_dwFrameAccumulator ;	//	: 起動からの経過フレーム数
	DWORD m_dwOFOTime ;				//	: 前フレームのクロック時間
	DWORD m_dwElapsedTime;			//	: １フレームにかかった時間
	DWORD m_dwFixFpsTime ;			//	: フレーム処理の規制時間

	float m_fOneSecondCounter;
	bool  m_bOneSecondSignal;

	float m_fFps;					//	: FPS
	DWORD m_dwFFA;					//	: FPS計算用にフレーム数を蓄積する
	DWORD m_dwLFT;					//	: 最後にFPSを計算してからの時間
//::::: 拾い物 :::::://
	void	Fps_Calculation();
public:
	/////////////////// ////////////////////
	//// 関数名     ：Tempus2::Tempus2();
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：インスタンスの生成
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	Tempus2(void);

	/////////////////// ////////////////////
	//// 関数名     ：Tempus2::~Tempus2();
	//// カテゴリ   ：デストラクタ
	//// 用途       ：インスタンスの破棄
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	~Tempus2(void);

	/////////////////// ////////////////////
	//// 関数名     ：static void  Tempus2::TimeUpdate();
	//// カテゴリ   ：メンバ関数
	//// 用途       ：時間の更新
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void    TimeUpdate();

	/////////////////// ////////////////////
	//// 関数名     ：static DWORD Tempus2::TimeGetTime();
	//// カテゴリ   ：ゲッター
	//// 用途       ：起動からの経過時間を返す
	//// 引数       ：なし
	//// 戻値       ：起動からの経過時間(㍉秒)
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	DWORD   TimeGetTime();

	/////////////////// ////////////////////
	//// 関数名     ：static double Tempus2::getWorkTime();
	//// カテゴリ   ：ゲッター
	//// 用途       ：起動からの経過時間(TimeUpdate時現在)
	//// 引数       ：なし
	//// 戻値       ：起動からの経過時間(秒)
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	double  getWorkTime();

	/////////////////// ////////////////////
	//// 関数名     ：static double Tempus::getWorkTime();
	//// カテゴリ   ：ゲッター
	//// 用途       ：１フレームの経過時間を返す
	//// 引数       ：なし
	//// 戻値       ：経過時間(㍉秒)
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	DWORD getWorkFrame();

	/////////////////// ////////////////////
	//// 関数名     ：static double Tempus2::getElapsedTime();
	//// カテゴリ   ：ゲッター
	//// 用途       ：１フレームの経過時間を返す
	//// 引数       ：なし
	//// 戻値       ：経過時間(秒)
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	double  getElapsedTime();

	/////////////////// ////////////////////
	//// 関数名     ：static Tempus2::getFps();
	//// カテゴリ   ：ゲッター
	//// 用途       ：フレームレートの計算
	//// 引数       ：なし
	//// 戻値       ：フレームレート
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	double  getFps();

	/////////////////// ////////////////////
	//// 関数名     ：static double Tempus2::getClockSec();
	//// カテゴリ   ：ゲッター
	//// 用途       ：秒の獲得
	//// 引数       ：なし
	//// 戻値       ：秒
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	double  getClockSec();

	/////////////////// ////////////////////
	//// 関数名     ：static double Tempus2::getClock();
	//// カテゴリ   ：ゲッター
	//// 用途       ：clock()
	//// 引数       ：なし
	//// 戻値       ：clock()
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	clock_t getClock();

	/////////////////// ////////////////////
	//// 関数名     ：static bool Tempus2::OneSecondSignal();
	//// カテゴリ   ：ゲッター
	//// 用途       ：一秒シグナル
	//// 引数       ：なし
	//// 戻値       ：一秒シグナル
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	bool OneSecondSignal();
	//static void  FixedFPS(int i_iFPS);



private :
	float m_fStageActiveTime ;
public :
	float getStageActiveTime() ;

	void setStageActiveTime(float i_fTime) ;
};

}

#endif