////////////////////////////// //////////////////////////////
//	プロジェクト	：TATRA-Library
//	ファイル名		：Tempus.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：時間関係の関数
//					▼
//	namespace wiz;
//		class Tempus ;
//		class Tempus2 ;
//
#include "StdAfx.h"
#include "Tempus.h"

namespace TLIB{

DWORD Tempus::m_dwStartGameTime		= timeGetTime();	//	: 実行ファイルが起動した時のシステムミリ秒
DWORD Tempus::m_dwFrameAccumulator	= 0;			//	: 起動からの経過フレーム数
DWORD Tempus::m_dwOFOTime			= 0;			//	: 前フレームのクロック時間
DWORD Tempus::m_dwElapsedTime		= 0;			//	: １フレームにかかった時間
DWORD Tempus::m_dwFixFpsTime		= 0;			//	: フレーム処理の規制時間

float Tempus::m_fOneSecondCounter	= 0;
bool  Tempus::m_bOneSecondSignal	= false;


float Tempus::m_fFps				= 0;			//	: FPS
DWORD Tempus::m_dwFFA				= 0;			//	: FPS計算用にフレーム数を蓄積する
DWORD Tempus::m_dwLFT				= 0;			//	: FPS計算用にフレーム数を蓄積する

/**************************************************************************
 関数名: Tempus::Tempus();
 用途: コンストラクタ
 戻り値: なし
****************************************************************************/
Tempus::Tempus(void)
{
	m_dwFixFpsTime = (DWORD)MSTOS(1.0f / 60.0f);
	//static DWORD m_dwStartGameTime;

}
/**************************************************************************
 関数名: Tempus::~Tempus();
 用途: デストラクタ
 戻り値: なし
****************************************************************************/
Tempus::~Tempus(void)
{
}
/**************************************************************************
 関数名: void  Tempus::TimeUpdate();
 用途: 時間の更新
 戻り値: なし
****************************************************************************/
void  Tempus::TimeUpdate(){
	//	: Frame数え
	m_dwFrameAccumulator++;
	//	: 現在時間の獲得とFPS制限
	DWORD dwNowFrameMiriSecond = 0 ;
	m_dwElapsedTime = ( dwNowFrameMiriSecond = TimeGetTime() ) - m_dwOFOTime;
	//while( (m_dwElapsedTime = ( dwNowFrameMiriSecond = TimeGetTime() ) - m_dwOFOTime) < m_dwFixFpsTime){
	//	//break;
	//	Sleep(1);
	//}
	////	: 1フレームにかかった時間の計算
	//m_dwLFT += m_dwElapsedTime;
	//	: 今の時間を保持
	m_dwOFOTime = dwNowFrameMiriSecond;
	//	: FPSの計算
    //m_dwFFA++;
    //if(500 <= m_dwLFT) {// 0.5秒毎に更新
    //    float dt = (double)(m_dwLFT) / 1000.0f;
    //    m_fFps = (double)m_dwFFA / dt;
    //    m_dwLFT = m_dwFFA = 0;
    //}

	m_fOneSecondCounter += (float)getElapsedTime();
	if(m_fOneSecondCounter >= 1.0f){
		m_fOneSecondCounter -= 1.0f;
		m_bOneSecondSignal   = true;
	}else{
		m_bOneSecondSignal   = false;
	}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//#ifdef ___MLP_DEBUG_TIMEDRAW_
	int h = (int)(DWMSTOFS(dwNowFrameMiriSecond) / (60 * 60)) % 24;
	int m = (int)(DWMSTOFS(dwNowFrameMiriSecond) / 60) % 60;
	int S = (int)(DWMSTOFS(dwNowFrameMiriSecond) ) % 60;

	Debugger::DBGSTR::addStr(
		L"時間:\n"
		L"FPS = %2.2f \n"
		L"%02d時 %02d分 %02d秒 %03d�_秒\n"
		L"実行時間 = %d\n"
		L"前回時間 = %d\n"
		L"ﾌﾚｰﾑ�_秒 = %f\n",
		m_fFps,
		h,m,S,dwNowFrameMiriSecond % 1000,
		dwNowFrameMiriSecond,
		m_dwOFOTime,
		DWMSTOFS(m_dwElapsedTime)
		);
//#endif
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
}
/**************************************************************************
 関数名: DWORD Tempus::TimeGetTime();
 用途: 起動からの経過時間を返す
 戻り値: 起動からの経過時間(�_秒)
****************************************************************************/
DWORD Tempus::TimeGetTime(){
	return timeGetTime() - m_dwStartGameTime;
}
/**************************************************************************
 関数名: double TwoDwTime2ElapsedTime( DWORD dwOldTime, DWORD dwNowTime );
 用途: 2つの時間差を浮動少数秒で返す
 戻り値: 起動からの経過時間(秒)
****************************************************************************/
double Tempus::TwoDwTime2ElapsedTime( DWORD dwOldTime, DWORD dwNowTime ){
	return DWMSTOFS(dwNowTime - dwOldTime);
}

/**************************************************************************
 関数名: double Tempus::getWorkTime();
 用途: １フレームの経過時間を返す
 戻り値: 経過時間(秒)
****************************************************************************/
double Tempus::getWorkTime(){
	return DWMSTOFS(timeGetTime() - m_dwStartGameTime);
}
/**************************************************************************
 関数名: double Tempus::getElapsedTime();
 用途: 起動からの経過時間(TimeUpdate時現在)
 戻り値: 起動からの経過時間(秒)
****************************************************************************/
double Tempus::getElapsedTime(){
	return DWMSTOFS(m_dwElapsedTime);
}
/**************************************************************************
 関数名: double Tempus::getClockSec();
 用途: 秒の獲得
 戻り値: 秒
****************************************************************************/
double Tempus::getClockSec(){
	return double( clock()) / double( CLOCKS_PER_SEC);
}
/**************************************************************************
 関数名: double Tempus::getFps();
 用途: フレームレートの計算
 戻り値: フレームレート
****************************************************************************/
double Tempus::getFps(){
	return m_fFps;
};
/**************************************************************************
 関数名: double Tempus::getClock();
 用途: clock()
 戻り値: clock()
****************************************************************************/
clock_t Tempus::getClock(){
	return clock();
}
/**************************************************************************
 関数名: bool Tempus::OneSecondSignal();
 用途: 一秒シグナル
 戻り値: 一秒シグナル
****************************************************************************/
bool Tempus::OneSecondSignal(){
	return m_bOneSecondSignal;
}
//	: 未実装
//void Tempus::FixedFPS(int i_iFPS){
//	
//	
//}





/**************************************************************************
 関数名: Tempus2::Tempus2();
 用途: コンストラクタ
 戻り値: なし
****************************************************************************/
Tempus2::Tempus2(void)
{
	m_dwFixFpsTime			= (DWORD)MSTOS(1.0f / 60.0f);
	m_dwStartGameTime		= timeGetTime();	//	: 実行ファイルが起動した時のシステムミリ秒
	m_dwFrameAccumulator	= 0;			//	: 起動からの経過フレーム数
	m_dwOFOTime				= 0;			//	: 前フレームのクロック時間
	m_dwElapsedTime			= 0;			//	: １フレームにかかった時間

	m_fOneSecondCounter		= 0;
	m_bOneSecondSignal		= false;

	m_fFps					= 0;			//	: FPS
	m_dwFFA					= 0;			//	: FPS計算用にフレーム数を蓄積する
	m_dwLFT					= 0;			//	: FPS計算用にフレーム数を蓄積する

}
/**************************************************************************
 関数名: Tempus2::~Tempus2();
 用途: デストラクタ
 戻り値: なし
****************************************************************************/
Tempus2::~Tempus2(void)
{
}
/**************************************************************************
 関数名: void  Tempus2::TimeUpdate();
 用途: 時間の更新
 戻り値: なし
****************************************************************************/
void  Tempus2::TimeUpdate(){
	//	: Frame数え
	m_dwFrameAccumulator++;
	//	: 現在時間の獲得とFPS制限
	DWORD dwNowFrameMiriSecond = 0 ;
	m_dwElapsedTime = ( dwNowFrameMiriSecond = timeGetTime() ) - m_dwOFOTime;
	bool b = false ;
	//while( (m_dwElapsedTime = ( dwNowFrameMiriSecond = timeGetTime() ) - m_dwOFOTime) < m_dwFixFpsTime){
	//	Sleep(1);
	//	b = true;
	//}
	//if(b) Debugger::DBGSTR::addStrTop(L"規制");
	//else  Debugger::DBGSTR::addStrTop(L"無法");
	//	: 1フレームにかかった時間の計算
	m_dwLFT += m_dwElapsedTime;
	//	: 今の時間を保持
	m_dwOFOTime = dwNowFrameMiriSecond;// - (m_dwElapsedTime - m_dwFixFpsTime);
	//	: FPSの計算
    //m_dwFFA++;
    //if(500 <= m_dwLFT) {// 0.5秒毎に更新
    //    float dt = (double)(m_dwLFT) / 1000.0f;
    //    m_fFps = (double)m_dwFFA / dt;
    //    m_dwLFT = m_dwFFA = 0;
    //}

	m_fOneSecondCounter += (float)getElapsedTime();
	if(m_fOneSecondCounter >= 1.0f){
		m_fOneSecondCounter -= 1.0f;
		m_bOneSecondSignal   = true;
	}else{
		m_bOneSecondSignal   = false;
	}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//#ifdef ___MLP_DEBUG_TIMEDRAW_
	int h = (int)(DWMSTOFS(dwNowFrameMiriSecond) / (60 * 60)) % 24;
	int m = (int)(DWMSTOFS(dwNowFrameMiriSecond) / 60) % 60;
	int S = (int)(DWMSTOFS(dwNowFrameMiriSecond) ) % 60;

	Debugger::DBGSTR::addStr(
		L"時間:\n"
		L"FPS = %2.2f \n"
		L"%02d時 %02d分 %02d秒 %03d�_秒\n"
		L"実行時間 = %d\n"
		L"前回時間 = %d\n"
		L"ﾌﾚｰﾑ�_秒 = %f\n",
		m_fFps,
		h,m,S,dwNowFrameMiriSecond % 1000,
		dwNowFrameMiriSecond,
		m_dwOFOTime,
		DWMSTOFS(m_dwElapsedTime)
		);
//#endif
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
}
/**************************************************************************
 関数名: DWORD Tempus2::TimeGetTime();
 用途: 起動からの経過時間を返す
 戻り値: 起動からの経過時間(�_秒)
****************************************************************************/
DWORD Tempus2::TimeGetTime(){
	return timeGetTime() - m_dwStartGameTime;
}
/**************************************************************************
 関数名: double Tempus2::getWorkTime();
 用途: １フレームの経過時間を返す
 戻り値: 経過時間(秒)
****************************************************************************/
double Tempus2::getWorkTime(){
	return DWMSTOFS(timeGetTime() - m_dwStartGameTime);
}
/**************************************************************************
 関数名: double Tempus::getWorkTime();
 用途: １フレームの経過時間を返す
 戻り値: 経過時間(秒)
****************************************************************************/
DWORD Tempus2::getWorkFrame(){
	return m_dwFrameAccumulator;
}
/**************************************************************************
 関数名: double Tempus2::getElapsedTime();
 用途: 起動からの経過時間(TimeUpdate時現在)
 戻り値: 起動からの経過時間(秒)
****************************************************************************/
double Tempus2::getElapsedTime(){
	return DWMSTOFS(m_dwElapsedTime);
}
/**************************************************************************
 関数名: double Tempus2::getClockSec();
 用途: 秒の獲得
 戻り値: 秒
****************************************************************************/
double Tempus2::getClockSec(){
	return double( clock()) / double( CLOCKS_PER_SEC);
}
/**************************************************************************
 関数名: double Tempus2::getFps();
 用途: フレームレートの計算
 戻り値: フレームレート
****************************************************************************/
double Tempus2::getFps(){
	return m_fFps;
};
/**************************************************************************
 関数名: double Tempus2::getClock();
 用途: clock()
 戻り値: clock()
****************************************************************************/
clock_t Tempus2::getClock(){
	return clock();
}
/**************************************************************************
 関数名: bool Tempus2::OneSecondSignal();
 用途: 一秒シグナル
 戻り値: 一秒シグナル
****************************************************************************/
bool Tempus2::OneSecondSignal(){
	return m_bOneSecondSignal;
}
//	: 未実装
//void Tempus2::FixedFPS(int i_iFPS){
//	
//	
//}

}