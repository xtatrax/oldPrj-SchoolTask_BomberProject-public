////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FTATRA-Library
//	�t�@�C����		�FTempus.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���Ԋ֌W�̊֐�
//					��
//	namespace wiz;
//		class Tempus ;
//		class Tempus2 ;
//
#include "StdAfx.h"
#include "Tempus.h"

namespace TLIB{

DWORD Tempus::m_dwStartGameTime		= timeGetTime();	//	: ���s�t�@�C�����N���������̃V�X�e���~���b
DWORD Tempus::m_dwFrameAccumulator	= 0;			//	: �N������̌o�߃t���[����
DWORD Tempus::m_dwOFOTime			= 0;			//	: �O�t���[���̃N���b�N����
DWORD Tempus::m_dwElapsedTime		= 0;			//	: �P�t���[���ɂ�����������
DWORD Tempus::m_dwFixFpsTime		= 0;			//	: �t���[�������̋K������

float Tempus::m_fOneSecondCounter	= 0;
bool  Tempus::m_bOneSecondSignal	= false;


float Tempus::m_fFps				= 0;			//	: FPS
DWORD Tempus::m_dwFFA				= 0;			//	: FPS�v�Z�p�Ƀt���[������~�ς���
DWORD Tempus::m_dwLFT				= 0;			//	: FPS�v�Z�p�Ƀt���[������~�ς���

/**************************************************************************
 �֐���: Tempus::Tempus();
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
****************************************************************************/
Tempus::Tempus(void)
{
	m_dwFixFpsTime = (DWORD)MSTOS(1.0f / 60.0f);
	//static DWORD m_dwStartGameTime;

}
/**************************************************************************
 �֐���: Tempus::~Tempus();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
****************************************************************************/
Tempus::~Tempus(void)
{
}
/**************************************************************************
 �֐���: void  Tempus::TimeUpdate();
 �p�r: ���Ԃ̍X�V
 �߂�l: �Ȃ�
****************************************************************************/
void  Tempus::TimeUpdate(){
	//	: Frame����
	m_dwFrameAccumulator++;
	//	: ���ݎ��Ԃ̊l����FPS����
	DWORD dwNowFrameMiriSecond = 0 ;
	m_dwElapsedTime = ( dwNowFrameMiriSecond = TimeGetTime() ) - m_dwOFOTime;
	//while( (m_dwElapsedTime = ( dwNowFrameMiriSecond = TimeGetTime() ) - m_dwOFOTime) < m_dwFixFpsTime){
	//	//break;
	//	Sleep(1);
	//}
	////	: 1�t���[���ɂ����������Ԃ̌v�Z
	//m_dwLFT += m_dwElapsedTime;
	//	: ���̎��Ԃ�ێ�
	m_dwOFOTime = dwNowFrameMiriSecond;
	//	: FPS�̌v�Z
    //m_dwFFA++;
    //if(500 <= m_dwLFT) {// 0.5�b���ɍX�V
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
		L"����:\n"
		L"FPS = %2.2f \n"
		L"%02d�� %02d�� %02d�b %03d�_�b\n"
		L"���s���� = %d\n"
		L"�O�񎞊� = %d\n"
		L"�ڰч_�b = %f\n",
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
 �֐���: DWORD Tempus::TimeGetTime();
 �p�r: �N������̌o�ߎ��Ԃ�Ԃ�
 �߂�l: �N������̌o�ߎ���(�_�b)
****************************************************************************/
DWORD Tempus::TimeGetTime(){
	return timeGetTime() - m_dwStartGameTime;
}
/**************************************************************************
 �֐���: double TwoDwTime2ElapsedTime( DWORD dwOldTime, DWORD dwNowTime );
 �p�r: 2�̎��ԍ��𕂓������b�ŕԂ�
 �߂�l: �N������̌o�ߎ���(�b)
****************************************************************************/
double Tempus::TwoDwTime2ElapsedTime( DWORD dwOldTime, DWORD dwNowTime ){
	return DWMSTOFS(dwNowTime - dwOldTime);
}

/**************************************************************************
 �֐���: double Tempus::getWorkTime();
 �p�r: �P�t���[���̌o�ߎ��Ԃ�Ԃ�
 �߂�l: �o�ߎ���(�b)
****************************************************************************/
double Tempus::getWorkTime(){
	return DWMSTOFS(timeGetTime() - m_dwStartGameTime);
}
/**************************************************************************
 �֐���: double Tempus::getElapsedTime();
 �p�r: �N������̌o�ߎ���(TimeUpdate������)
 �߂�l: �N������̌o�ߎ���(�b)
****************************************************************************/
double Tempus::getElapsedTime(){
	return DWMSTOFS(m_dwElapsedTime);
}
/**************************************************************************
 �֐���: double Tempus::getClockSec();
 �p�r: �b�̊l��
 �߂�l: �b
****************************************************************************/
double Tempus::getClockSec(){
	return double( clock()) / double( CLOCKS_PER_SEC);
}
/**************************************************************************
 �֐���: double Tempus::getFps();
 �p�r: �t���[�����[�g�̌v�Z
 �߂�l: �t���[�����[�g
****************************************************************************/
double Tempus::getFps(){
	return m_fFps;
};
/**************************************************************************
 �֐���: double Tempus::getClock();
 �p�r: clock()
 �߂�l: clock()
****************************************************************************/
clock_t Tempus::getClock(){
	return clock();
}
/**************************************************************************
 �֐���: bool Tempus::OneSecondSignal();
 �p�r: ��b�V�O�i��
 �߂�l: ��b�V�O�i��
****************************************************************************/
bool Tempus::OneSecondSignal(){
	return m_bOneSecondSignal;
}
//	: ������
//void Tempus::FixedFPS(int i_iFPS){
//	
//	
//}





/**************************************************************************
 �֐���: Tempus2::Tempus2();
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
****************************************************************************/
Tempus2::Tempus2(void)
{
	m_dwFixFpsTime			= (DWORD)MSTOS(1.0f / 60.0f);
	m_dwStartGameTime		= timeGetTime();	//	: ���s�t�@�C�����N���������̃V�X�e���~���b
	m_dwFrameAccumulator	= 0;			//	: �N������̌o�߃t���[����
	m_dwOFOTime				= 0;			//	: �O�t���[���̃N���b�N����
	m_dwElapsedTime			= 0;			//	: �P�t���[���ɂ�����������

	m_fOneSecondCounter		= 0;
	m_bOneSecondSignal		= false;

	m_fFps					= 0;			//	: FPS
	m_dwFFA					= 0;			//	: FPS�v�Z�p�Ƀt���[������~�ς���
	m_dwLFT					= 0;			//	: FPS�v�Z�p�Ƀt���[������~�ς���

}
/**************************************************************************
 �֐���: Tempus2::~Tempus2();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
****************************************************************************/
Tempus2::~Tempus2(void)
{
}
/**************************************************************************
 �֐���: void  Tempus2::TimeUpdate();
 �p�r: ���Ԃ̍X�V
 �߂�l: �Ȃ�
****************************************************************************/
void  Tempus2::TimeUpdate(){
	//	: Frame����
	m_dwFrameAccumulator++;
	//	: ���ݎ��Ԃ̊l����FPS����
	DWORD dwNowFrameMiriSecond = 0 ;
	m_dwElapsedTime = ( dwNowFrameMiriSecond = timeGetTime() ) - m_dwOFOTime;
	bool b = false ;
	//while( (m_dwElapsedTime = ( dwNowFrameMiriSecond = timeGetTime() ) - m_dwOFOTime) < m_dwFixFpsTime){
	//	Sleep(1);
	//	b = true;
	//}
	//if(b) Debugger::DBGSTR::addStrTop(L"�K��");
	//else  Debugger::DBGSTR::addStrTop(L"���@");
	//	: 1�t���[���ɂ����������Ԃ̌v�Z
	m_dwLFT += m_dwElapsedTime;
	//	: ���̎��Ԃ�ێ�
	m_dwOFOTime = dwNowFrameMiriSecond;// - (m_dwElapsedTime - m_dwFixFpsTime);
	//	: FPS�̌v�Z
    //m_dwFFA++;
    //if(500 <= m_dwLFT) {// 0.5�b���ɍX�V
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
		L"����:\n"
		L"FPS = %2.2f \n"
		L"%02d�� %02d�� %02d�b %03d�_�b\n"
		L"���s���� = %d\n"
		L"�O�񎞊� = %d\n"
		L"�ڰч_�b = %f\n",
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
 �֐���: DWORD Tempus2::TimeGetTime();
 �p�r: �N������̌o�ߎ��Ԃ�Ԃ�
 �߂�l: �N������̌o�ߎ���(�_�b)
****************************************************************************/
DWORD Tempus2::TimeGetTime(){
	return timeGetTime() - m_dwStartGameTime;
}
/**************************************************************************
 �֐���: double Tempus2::getWorkTime();
 �p�r: �P�t���[���̌o�ߎ��Ԃ�Ԃ�
 �߂�l: �o�ߎ���(�b)
****************************************************************************/
double Tempus2::getWorkTime(){
	return DWMSTOFS(timeGetTime() - m_dwStartGameTime);
}
/**************************************************************************
 �֐���: double Tempus::getWorkTime();
 �p�r: �P�t���[���̌o�ߎ��Ԃ�Ԃ�
 �߂�l: �o�ߎ���(�b)
****************************************************************************/
DWORD Tempus2::getWorkFrame(){
	return m_dwFrameAccumulator;
}
/**************************************************************************
 �֐���: double Tempus2::getElapsedTime();
 �p�r: �N������̌o�ߎ���(TimeUpdate������)
 �߂�l: �N������̌o�ߎ���(�b)
****************************************************************************/
double Tempus2::getElapsedTime(){
	return DWMSTOFS(m_dwElapsedTime);
}
/**************************************************************************
 �֐���: double Tempus2::getClockSec();
 �p�r: �b�̊l��
 �߂�l: �b
****************************************************************************/
double Tempus2::getClockSec(){
	return double( clock()) / double( CLOCKS_PER_SEC);
}
/**************************************************************************
 �֐���: double Tempus2::getFps();
 �p�r: �t���[�����[�g�̌v�Z
 �߂�l: �t���[�����[�g
****************************************************************************/
double Tempus2::getFps(){
	return m_fFps;
};
/**************************************************************************
 �֐���: double Tempus2::getClock();
 �p�r: clock()
 �߂�l: clock()
****************************************************************************/
clock_t Tempus2::getClock(){
	return clock();
}
/**************************************************************************
 �֐���: bool Tempus2::OneSecondSignal();
 �p�r: ��b�V�O�i��
 �߂�l: ��b�V�O�i��
****************************************************************************/
bool Tempus2::OneSecondSignal(){
	return m_bOneSecondSignal;
}
//	: ������
//void Tempus2::FixedFPS(int i_iFPS){
//	
//	
//}

}