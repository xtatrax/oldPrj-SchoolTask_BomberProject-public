////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FTATRA-Library
//	�t�@�C����		�FTempus.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���Ԋ֌W�̊֐�
//					��
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
// �S��  : �����O
// �p�r  : ���Ԃ��Ǘ�����N���X
// ���l  : �ÓI
//**************************************************************************//
class Tempus
{
	static DWORD m_dwStartGameTime;		//	: ���s�t�@�C�����N���������̃V�X�e���~���b
	static DWORD m_dwFrameAccumulator ;	//	: �N������̌o�߃t���[����
	static DWORD m_dwOFOTime ;			//	: �O�t���[���̃N���b�N����
	static DWORD m_dwElapsedTime;		//	: �P�t���[���ɂ�����������
	static DWORD m_dwFixFpsTime ;		//	: �t���[�������̋K������

	static float m_fOneSecondCounter;
	static bool  m_bOneSecondSignal;

	static float m_fFps;				//	: FPS
	static DWORD m_dwFFA;				//	: FPS�v�Z�p�Ƀt���[������~�ς���
	static DWORD m_dwLFT;				//	: �Ō��FPS���v�Z���Ă���̎���
//::::: �E���� :::::://
	static void	Fps_Calculation();
public:
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
	Tempus(void);

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
	~Tempus(void);

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
	static void    TimeUpdate();

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
	static DWORD   TimeGetTime();

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
	static double   TwoDwTime2ElapsedTime( DWORD dwOldTime, DWORD dwNowTime );

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
	static double  getWorkTime();

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
	static double  getElapsedTime();

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
	static double  getFps();

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
	static double  getClockSec();

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
	static clock_t getClock();

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
	static bool OneSecondSignal();
	//static void  FixedFPS(int i_iFPS);
};

//**************************************************************************//
// class Tempus2 ;
// �S��  : �����O
// �p�r  : ���Ԃ��Ǘ�����N���X
// ���l  : 
//**************************************************************************//
class Tempus2
{
	DWORD m_dwStartGameTime;		//	: ���s�t�@�C�����N���������̃V�X�e���~���b
	DWORD m_dwFrameAccumulator ;	//	: �N������̌o�߃t���[����
	DWORD m_dwOFOTime ;				//	: �O�t���[���̃N���b�N����
	DWORD m_dwElapsedTime;			//	: �P�t���[���ɂ�����������
	DWORD m_dwFixFpsTime ;			//	: �t���[�������̋K������

	float m_fOneSecondCounter;
	bool  m_bOneSecondSignal;

	float m_fFps;					//	: FPS
	DWORD m_dwFFA;					//	: FPS�v�Z�p�Ƀt���[������~�ς���
	DWORD m_dwLFT;					//	: �Ō��FPS���v�Z���Ă���̎���
//::::: �E���� :::::://
	void	Fps_Calculation();
public:
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
	Tempus2(void);

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
	~Tempus2(void);

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
	void    TimeUpdate();

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
	DWORD   TimeGetTime();

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
	double  getWorkTime();

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
	DWORD getWorkFrame();

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
	double  getElapsedTime();

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
	double  getFps();

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
	double  getClockSec();

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
	clock_t getClock();

	/////////////////// ////////////////////
	//// �֐���     �Fstatic bool Tempus2::OneSecondSignal();
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F��b�V�O�i��
	//// ����       �F�Ȃ�
	//// �ߒl       �F��b�V�O�i��
	//// �S��       �F���� �O
	//// ���l       �F
	////            �F
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