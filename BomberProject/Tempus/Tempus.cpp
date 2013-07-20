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

/**************************************************************************
 Tempus ��`��
***************************************************************************/
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

/////////////////// ////////////////////
//// �֐���     �FTempus::Tempus();
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�C���X�^���X�̐���
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
Tempus::Tempus(void)
{
	m_dwFixFpsTime = (DWORD)MSTOS(1.0f / 60.0f);
	//static DWORD m_dwStartGameTime;

}
/////////////////// ////////////////////
//// �֐���     �FTempus::~Tempus();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�C���X�^���X�̔j��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
Tempus::~Tempus(void)
{
}
/////////////////// ////////////////////
//// �֐���     �Fstatic void Tempus::TimeUpdate();
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F���Ԃ̍X�V
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
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
#ifdef CF_DEBUG_TIMEDRAW
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
#endif
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
}
/////////////////// ////////////////////
//// �֐���     �Fstatic DWORD Tempus::TimeGetTime();
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�N������̌o�ߎ��Ԃ�Ԃ�
//// ����       �F�Ȃ�
//// �ߒl       �F�N������̌o�ߎ���(�_�b)
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
DWORD Tempus::TimeGetTime(){
	return timeGetTime() - m_dwStartGameTime;
}
/////////////////// ////////////////////
//// �֐���     �Fstatic double TwoDwTime2ElapsedTime( DWORD dwOldTime, DWORD dwNowTime );
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F2�̎��Ԃ̍��𕂓������b�ŕԂ�
//// ����       �F  DWORD dwOldTime   //  : �O�̎���
////            �F  DWORD dwNowTime   //  : ���̎���
//// �ߒl       �F2�̎��Ԃ̍�(�b)
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
double Tempus::TwoDwTime2ElapsedTime( DWORD dwOldTime, DWORD dwNowTime ){
	return DWMSTOFS(dwNowTime - dwOldTime);
}

/////////////////// ////////////////////
//// �֐���     �Fstatic double Tempus::getWorkTime();
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F�N������̌o�ߎ���(TimeUpdate������)
//// ����       �F�Ȃ�
//// �ߒl       �F�N������̌o�ߎ���(�b)
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
double Tempus::getWorkTime(){
	return DWMSTOFS(timeGetTime() - m_dwStartGameTime);
}
/////////////////// ////////////////////
//// �֐���     �Fstatic double Tempus::getElapsedTime();
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F�P�t���[���̌o�ߎ��Ԃ�Ԃ�
//// ����       �F�Ȃ�
//// �ߒl       �F�o�ߎ���(�b)
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
double Tempus::getElapsedTime(){
	return DWMSTOFS(m_dwElapsedTime);
}
/////////////////// ////////////////////
//// �֐���     �Fstatic double Tempus::getClockSec();
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F�b�̊l��
//// ����       �F�Ȃ�
//// �ߒl       �F�b
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
double Tempus::getClockSec(){
	return double( clock()) / double( CLOCKS_PER_SEC);
}
/////////////////// ////////////////////
//// �֐���     �Fstatic double Tempus::getFps();
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F�t���[�����[�g�̌v�Z
//// ����       �F�Ȃ�
//// �ߒl       �F�t���[�����[�g
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
double Tempus::getFps(){
	return m_fFps;
};
/////////////////// ////////////////////
//// �֐���     �Fstatic double Tempus::getClock();
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �Fclock()
//// ����       �F�Ȃ�
//// �ߒl       �Fclock()
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
clock_t Tempus::getClock(){
	return clock();
}
/////////////////// ////////////////////
//// �֐���     �Fstatic bool Tempus::OneSecondSignal();
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F��b�V�O�i��
//// ����       �F�Ȃ�
//// �ߒl       �F��b�V�O�i��
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
bool Tempus::OneSecondSignal(){
	return m_bOneSecondSignal;
}
//	: ������
//void Tempus::FixedFPS(int i_iFPS){
//	
//	
//}




/**************************************************************************
 Tempus2 ��`��
***************************************************************************/

/////////////////// ////////////////////
//// �֐���     �FTempus2::Tempus2();
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�C���X�^���X�̐���
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
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
/////////////////// ////////////////////
//// �֐���     �FTempus2::~Tempus2();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�C���X�^���X�̔j��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
Tempus2::~Tempus2(void)
{
}
/////////////////// ////////////////////
//// �֐���     �Fstatic void  Tempus2::TimeUpdate();
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F���Ԃ̍X�V
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
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
    m_dwFFA++;
    if(500 <= m_dwLFT) {// 0.5�b���ɍX�V
        float dt = (double)(m_dwLFT) / 1000.0f;
        m_fFps = (double)m_dwFFA / dt;
        m_dwLFT = m_dwFFA = 0;
    }

	m_fOneSecondCounter += (float)getElapsedTime();
	if(m_fOneSecondCounter >= 1.0f){
		m_fOneSecondCounter -= 1.0f;
		m_bOneSecondSignal   = true;
	}else{
		m_bOneSecondSignal   = false;
	}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#ifdef CF_DEBUG_TIMEDRAW
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
#endif
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
}
/////////////////// ////////////////////
//// �֐���     �Fstatic DWORD Tempus2::TimeGetTime();
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F�N������̌o�ߎ��Ԃ�Ԃ�
//// ����       �F�Ȃ�
//// �ߒl       �F�N������̌o�ߎ���(�_�b)
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
DWORD Tempus2::TimeGetTime(){
	return timeGetTime() - m_dwStartGameTime;
}
/////////////////// ////////////////////
//// �֐���     �Fstatic double Tempus2::getWorkTime();
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F�N������̌o�ߎ���(TimeUpdate������)
//// ����       �F�Ȃ�
//// �ߒl       �F�N������̌o�ߎ���(�b)
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
double Tempus2::getWorkTime(){
	return DWMSTOFS(timeGetTime() - m_dwStartGameTime);
}
/////////////////// ////////////////////
//// �֐���     �Fstatic double Tempus::getWorkTime();
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F�P�t���[���̌o�ߎ��Ԃ�Ԃ�
//// ����       �F�Ȃ�
//// �ߒl       �F�o�ߎ���(�_�b)
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
DWORD Tempus2::getWorkFrame(){
	return m_dwFrameAccumulator;
}
/////////////////// ////////////////////
//// �֐���     �Fstatic double Tempus2::getElapsedTime();
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F�P�t���[���̌o�ߎ��Ԃ�Ԃ�
//// ����       �F�Ȃ�
//// �ߒl       �F�o�ߎ���(�b)
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
double Tempus2::getElapsedTime(){
	return DWMSTOFS(m_dwElapsedTime);
}
/////////////////// ////////////////////
//// �֐���     �Fstatic double Tempus2::getClockSec();
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F�b�̊l��
//// ����       �F�Ȃ�
//// �ߒl       �F�b
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
double Tempus2::getClockSec(){
	return double( clock()) / double( CLOCKS_PER_SEC);
}
/////////////////// ////////////////////
//// �֐���     �Fstatic Tempus2::getFps();
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F�t���[�����[�g�̌v�Z
//// ����       �F�Ȃ�
//// �ߒl       �F�t���[�����[�g
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
double Tempus2::getFps(){
	return m_fFps;
};
/////////////////// ////////////////////
//// �֐���     �Fstatic double Tempus2::getClock();
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �Fclock()
//// ����       �F�Ȃ�
//// �ߒl       �Fclock()
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
clock_t Tempus2::getClock(){
	return clock();
}
/////////////////// ////////////////////
//// �֐���     �Fstatic double Tempus2::getClock();
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �Fclock()
//// ����       �F�Ȃ�
//// �ߒl       �Fclock()
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
bool Tempus2::OneSecondSignal(){
	return m_bOneSecondSignal;
}
//	: ������
//void Tempus2::FixedFPS(int i_iFPS){
//	
//	
//}

}