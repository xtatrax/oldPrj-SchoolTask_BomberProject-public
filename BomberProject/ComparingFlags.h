////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FComparingFlags.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�R���p�C���ӂ炮 �f�o�b�O�p�֐���؂���������肻��Ȋ���
//					��
//
#ifndef	__Comparing_Flags__
#define	__Comparing_Flags__


//////////
//	: �R���p�C�����O�t���O
#define CF_SINGLETHREAD					/* �V���O���X���b�h���[�h  ( �����ɂ���ƃ}���`�X���b�h�I�ɂȂ�܂����o�O��܂� )   */
#define DRAW_MOUSE	(false)				/* �}�E�X��`�悷�邩�ǂ��� */

#define DEBUG_KEYBORD_ON				/* �f�o�b�O�p�L�[�{�[�h�����L���� */
#define CF_OVERLORDNEW_ENABLE			/* �����new��������(Manager�L����) */
#define CF_MEMORYOUTPUTPROCESS_ENABLE	/* ���상�����Ǘ��V�X�e���ɂ��Ǘ�����Ă���A�C�e���̃t�@�C���ւ̏����o�����\�ɂ���(Manager�L����) */
///#define CF_LOADINGANIMATION			/* ���[�h��ʂŃA�j���[�V���� */
//#define CF_OVERLORDNEW_ENABLE			/* �����new�������� */

#define CF_DEBUG_TIMEDRAW				/* ���Ԃ�`�� */
//#define CF_LOADINGANIMATION			/* ���[�h��ʂŃA�j���[�V���� */


#if defined(DEBUG) || defined(_DEBUG)
	//-------------------------------//
	//		�f�o�b�O���[�h��`       //
	//-------------------------------//
	#define ON_DEBUGGINGPROCESS					/* �f�o�b�N���[�h             */
	//#define DEBUG_STRINGS_ON					/* �f�o�b�O�p�������L���� */
	//#define CF_DEBUGINFORMATIONWINDOW_ENABLE	/* �f�o�b�O���\���p�E�C���h�E��L���� */
	//#define CF_MEMORYMANAGER_ENABLE			/* ���상�����Ǘ��V�X�e����L���� */
	//#define CF_FULLSCREEN				/* �t���X�N���[�����[�h       */

	//#define ___MLP_DEBUG_TIMEDRAW_ 
	//#define ON_GUIDELINE
#else
	#if defined( PRESENTATION )
	//-------------------------------//
	//		�v���[�����[�h��`       //
	//-------------------------------//
		//#define DEBUG_STRINGS_ON					/* �f�o�b�O�p�������L���� */
		//#define CF_MEMORYMANAGER_ENABLE			/* ���상�����Ǘ��V�X�e����L���� */
//		#define CF_FULLSCREEN				/* �t���X�N���[�����[�h       */
		//#define DEBUG_STRINGS_ON			/* �f�o�b�O�p�������L���� */

	#else
	//-------------------------------//
	//		�����[�X���[�h��`       //
	//-------------------------------//

		#define CF_FULLSCREEN				/* �t���X�N���[�����[�h       */
	#endif

#endif
//
//////////


#endif