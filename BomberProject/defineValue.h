////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FDefineValue.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�O���[�o���ȃf�B�t�@�C���l�Q
//					��
//
#ifndef	__Define_Value__
#define	__Define_Value__

 

//////////
// �}�N���֐�

#define TL_SQUARE(n)							((n)*(n))

//
//////////


//////////
//	: �R���p�C�����O�t���O
#define CF_SINGLETHREAD					/* �V���O���X���b�h���[�h  ( �����ɂ���ƃ}���`�X���b�h�I�ɂȂ�܂����o�O��܂� )   */
#define DRAW_MOUSE	(false)				/* �}�E�X��`�悷�邩�ǂ��� */

#define DEBUG_KEYBORD_ON				/* �f�o�b�O�p�L�[�{�[�h�����L���� */
#define CF_OVERLORDNEW_ENABLE			/* �����new��������(Manager�L����) */
#define CF_MEMORYOUTPUTPROCESS_ENABLE	/* ���상�����Ǘ��V�X�e���ɂ��Ǘ�����Ă���A�C�e���̃t�@�C���ւ̏����o�����\�ɂ���(Manager�L����) */
///#define CF_LOADINGANIMATION			/* ���[�h��ʂŃA�j���[�V���� */
//#define CF_OVERLORDNEW_ENABLE			/* �����new�������� */

//#define CF_DEBUG_TIMEDRAW				/* ���Ԃ�`�� */
//#define CF_LOADINGANIMATION			/* ���[�h��ʂŃA�j���[�V���� */


#if defined(DEBUG) || defined(_DEBUG)
	//-------------------------------//
	//		�f�o�b�O���[�h��`       //
	//-------------------------------//
	#define ON_DEBUGGINGPROCESS					/* �f�o�b�N���[�h             */
	#define DEBUG_STRINGS_ON					/* �f�o�b�O�p�������L���� */
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
		//#define CF_FULLSCREEN				/* �t���X�N���[�����[�h       */
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

//////////
// �}�N���֐�

#define TL_SQUARE(n)							((n)*(n))

//
//////////


//////////
//	: �O���[�o���ȕϐ�

//	: �f�t�@�C���萔
#define MAP_PARTS_HEIGHT		(    1.0f)	/*  */
#define MAP_PARTS_WIDTH			(    1.0f)	/*  */
#define BASE_CLIENT_HEIGHT		(  600.0f)	/* ��ɂȂ�`��̈�̍��� */
#define BASE_CLIENT_WIDTH		( 1024.0f)	/* ��ɂȂ�`��̈�̕�   */
#if defined(CF_FULLSCREEN)

#define STANDARD_WINDOW_HEIGHT		(  600.0f)	/* ��ɂȂ�`��̈�̍��� */
#define STANDARD_WINDOW_WIDTH		( 1024.0f)	/* ��ɂȂ�`��̈�̕�   */

//#define STANDARD_WINDOW_HEIGHT  (  800.0f)	/* �E�C���h�E���[�h�̍���   */
//#define STANDARD_WINDOW_WIDTH   ( 1280.0f)	/* �E�C���h�E���[�h�̕�     */

//#define STANDARD_WINDOW_HEIGHT  (  768.0f)	/* �E�C���h�E���[�h�̍���   */
//#define STANDARD_WINDOW_WIDTH   ( 1366.0f)	/* �E�C���h�E���[�h�̕�     */

#else
#define STANDARD_WINDOW_HEIGHT  (  600.0f)	/* �E�C���h�E���[�h�̍���   */
#define STANDARD_WINDOW_WIDTH   ( 1024.0f)	/* �E�C���h�E���[�h�̕�     */
#endif
//#define BASE_CLIENT_HEIGHT		(  600.0f)	/* ��ɂȂ�`��̈�̍��� */
//#define BASE_CLIENT_WIDTH		( 1024.0f)	/* ��ɂȂ�`��̈�̕�   */
//#define STANDARD_WINDOW_HEIGHT  ( 1200.0f)	/* �E�C���h�E���[�h�̍���   */
//#define STANDARD_WINDOW_WIDTH   ( 1920.0f)	/* �E�C���h�E���[�h�̕�     */
#define DRAW_TOLERANCE			(   20.0f)	/* �J��������̕`�拗�� */

#define DEFAULT_WINDOW_TITLE		( L"Magnetica" )
#define DEFAULT_WINDOW_CLASS_NAME	( L"MagneticWindow" )

//	�L�[�{�[�h��`
#define MYVK_GAMEPAD_A				( 'X' )
#define MYVK_GAMEPAD_B				( 'C' )
#define MYVK_GAMEPAD_X				( 'S' )
#define MYVK_GAMEPAD_Y				( 'D' )

#define MYVK_GAMEPAD_BACK			( 'W' )
#define MYVK_GAMEPAD_START			( 'E' )
#define MYVK_GAMEPAD_LB				( 'A' )
#define MYVK_GAMEPAD_RB				( 'F' )

#define MYVK_GAMEPAD_POV_UP			( VK_UP    )
#define MYVK_GAMEPAD_POV_DOWN 		( VK_DOWN  )
#define MYVK_GAMEPAD_POV_RIGHT		( VK_RIGHT )
#define MYVK_GAMEPAD_POV_LEFT		( VK_LEFT  )

#define MYVK_GAMEPAD_STICK_UP		( 'I' )
#define MYVK_GAMEPAD_STICK_DOWN 	( 'K' )
#define MYVK_GAMEPAD_STICK_RIGHT	( 'L' )
#define MYVK_GAMEPAD_STICK_LEFT		( 'J' )


#define MYVK_DEBUG_STOP_UPDATE				( VK_F12     )
#define MYVK_DEBUG_SLOW_UPDATE				( VK_F11     )
#define MYVK_DEBUG_OUTPUT_DBGSTR			( VK_F9      )
#define MYVK_DEBUG_OUTPUT_MEMORY			( VK_F8      )
#define MYVK_DEBUG_OBB_DRAW					( VK_F7      )
#define MYVK_DEBUG_SWITCHING_SOUND			( VK_F6      )
#define MYVK_DEBUG_COIL_INVISIBLE			( VK_CONTROL )
#define MYVK_DEBUG_STAGE_RESTART			( VK_RETURN  )
#define MYVK_DEBUG_STAGE_RESTART_SUBKEY		( VK_SHIFT   )
#define MYVK_DEBUG_STAGE_RELOAD_SUBKEY		( VK_MENU    )
#define MYVK_DEBUG_INVISIBLEGAUGE_MAX		( 'X'     )
#define MYVK_DEBUG_STAGE_RULER				( 'L'        )
#define MYVK_DEBUG_SWITCH_ALPHABLEND		( 'A'        )

#define UI_HEIGHT							( 88.0f )	//	: UI�̍���
#define DRAW_CLIENT_MAGNIFICATION			( 50.0f )	//	: �\����ʂ̔{�� x=800, y=512 : x=40, y=25.6
#define MAGNETIC_RADIUS						( 0.5f )	//	: ���E�̔��a
const float	CURSOR_FIELD_LENGHT				= 10.0f;
const float CURSOR_FIELD_TIME				= 2.0f;		

static ULONG				RCVAL_SAVEDATA_IDENTIFIER_H		= 0x534E4B42 ;	//	: BKNS
static ULONG				RCVAL_SAVEDATA_IDENTIFIER_L		= 0x5F455641 ;	//	: AVE_

static const char*			RCTEXT_SAVEDATA_EXTENSION		= "bkn"  ;
static const char*			RCTEXT_SAVEDATA_FILENAME		= "SaveData/Save.bkn"  ;

static const wchar_t*		RCTEXT_SOUND_WAVEBANK			= L"media/Sound/MagneticaWave.xwb"  ;
static const wchar_t*		RCTEXT_SOUND_SOUNDBANK			= L"media/Sound/MagneticaSound.xsb" ;

static const char*			RCTEXT_SOUND_BGM_CLEAR			= "BGM-CLEAR"			;
static const char*			RCTEXT_SOUND_BGM_GAMEOVER		= "BGM-GAME_OVER"		;
//static const char*			RCTEXT_SOUND_BGM_PLAY		= "BGM-PLAY001"			;
static const char*			RCTEXT_SOUND_BGM_PLAY			= "BGM-PLAY002"			;
static const char*			RCTEXT_SOUND_BGM_TITLE			= "BGM-TITLE"			;
static const char*			RCTEXT_SOUND_SE_ALERT			= "SE-ALERT002"			;
static const char*			RCTEXT_SOUND_SE_BREAKENEMY		= "SE-BLOKEN_ENEMY"		;
static const char*			RCTEXT_SOUND_SE_CHECKPOINT		= "SE-CHACK_POINT"		;
static const char*			RCTEXT_SOUND_SE_CLEAR			= "SE-CLEAR"			;
static const char*			RCTEXT_SOUND_SE_SELECT			= "SE-SELECT"			;
static const char*			RCTEXT_SOUND_SE_ENTER			= "SE-ENTER"			;
static const char*			RCTEXT_SOUND_SE_FIRE			= "SE-FIRE"				;
static const char*			RCTEXT_SOUND_SE_GOAL			= "SE-GOAL"				;
static const char*			RCTEXT_SOUND_SE_PLAYERBLOKEN	= "SE-PLAYER_BLOKEN"	;
static const char*			RCTEXT_SOUND_SE_INVISIBLE		= "SE-INVINGVLE"		;
static const char*			RCTEXT_SOUND_SE_ITEMS			= "SE-ITEMS"			;
static const char*			RCTEXT_SOUND_SE_SUPER_FULL		= "SE-ITEM_FULL"		;
static const char*			RCTEXT_SOUND_SE_SETFIELD		= "SE-MAGNETIC_FIELD"	;
static const char*			RCTEXT_SOUND_SE_SPARK			= "SE-SPARK002"			;
static const char*			RCTEXT_SOUND_SE_SPARK_WARNING	= "SE-SPARK002"			;

static const char*			RCTEXT_MODEL_ENEMY				= "media/Model/mine.x"	;

static const float			MGPRM_INVISIBLESOUND_TIME		= 0.7f	; /* ���E�̉e�����a*/
static const int			MGPRM_MAGNETICUM				= 10	; /* ���E�̉e�����a*/
static const int			MGPRM_MAGNETICUM_QUAD			= ( MGPRM_MAGNETICUM * MGPRM_MAGNETICUM );
static const int			DRAWING_RANGE					= 25;
static const D3DXVECTOR3	g_vZero							= D3DXVECTOR3(0.0f,0.0f,0.0f);
static const D3DXVECTOR3	g_vOne							= D3DXVECTOR3(1.0f,1.0f,1.0f);
static const D3DXVECTOR3	g_vMax							= D3DXVECTOR3(+FLT_MAX,+FLT_MAX,+FLT_MAX);
static const D3DXVECTOR3	g_vMin							= D3DXVECTOR3(-FLT_MAX,-FLT_MAX,-FLT_MAX);
static const wstring		g_sDefaultTexturePath			= L"media/Textures/" ;	//	: �e�N�X�`���̒u����
      //extern HWND			wiz::DxDevice::m_hWnd			;
static const SIZE			g_GaugeReverseSize				= { 146,67 };


//
//////////

//


//
namespace wiz{
	//	: �Q�[�������Z�[�W
	enum{
		GM_WITHOUT					,	//	: �������Ȃ�
		GM_OPENSTAGE_TITLE			,	//	: �^�C�g����ʂ��J��
		GM_OPENSTAGE_SELECT			,	//	: �Z���N�g��ʂ��J��
		GM_OPENSTAGE_LOAD			,	//	: ���[�h��ʂ��J��
		GM_OPENSTAGE_LOAD_PLAY		,	//	: ���[�h��ʂ��J������Ƀv���C��ʂ��J��
		GM_OPENSTAGE_PLAY			,	//	: �v���C��ʂ��J��
		GM_OPENSTAGE_GAMECLEAR		,	//	: �N���A��ʂ��J��
		GM_OPENSTAGE_GAMEOVER		,	//	: �Q�[���I�[�o�[��ʂ��J��
		GM_OPENSTAGE_CLEAR			,	//	: �N���A��ʂ��J��
		GM_OPENSTAGE_RESULT			,	//	: ���U���g��ʂ��J��
		GM_OPENSTAGE_RANKING		,	//	: �����L���O��ʂ��J��
		GM_OPENSTAGE_OPTION			,	//	: �I�v�V������ʂ��J��
		GM_EXIT						,	//	: �Q�[�����I������

		GM_OPENDEBUGSTAGE_DEBUGMENU			,
		GM_OPENDEBUGSTAGE_PLAY_RELOAD		,
		GM_OPENDEBUGSTAGE_STAGELOADERTEST	,
		GM_OPENDEBUGSTAGE_TATEAWORKSPACE	,
		GM_OPENDEBUGSTAGE_STAGECREATE		,


		GM_CHANGE_PARENTSTAGE	,
		GM_CHANGE_CHILDSTAGE	,

		//////////
		//	: 
		GM_PLAYOPENING_END	,

	};
	//	: 
	enum CLASSID{
		/////////
		//
		//	���̗񋓌^�͊O���t�@�C���Ŏg�p����̂�
		//	�d�l�ɏ]����΂ɒl�𖾋L���邱��
		//

		CLASSID_NONE		=    0 ,
		CLASSID_TESTTIP		=    1 ,
		CLASSID_GOAL		=   10 ,
		CLASSID_CHECKPOINT	=   11 ,
		CLASSID_WALL		=   20 ,
		CLASSID_MAGNET		=   30 ,
		CLASSID_ENEMY		=   31 ,
		CLASSID_ITEM		=   40 ,



		CLASSID_END			=  0xFFFFFFFFFFFFFFFF ,
	};
/**/
	//////////////////////////////////////////////////
	//                                              //
	//                                              //
	//   �I�u�W�F�N�g���ʂ��邽�߂ɗ��p�m���ID     //
	//                                              //
	//   �ǉ��̍ۂ͂��ׂđ啶���ŋL�q���Ă�������   //
	//                                              //
	//                                              //
	//////////////////////////////////////////////////
	enum OBJID{
		OBJID_NONE					= 0x0000,	//	: �Ȃ�
		OBJID_UNK					= 0x0001,	//	: ����I�u�W�F

		//	: �V�X�e���֌W
		OBJID_SYS_BEGIN				= 0x1000,
		OBJID_SYS_GUIDELINE			,	//	: XYZ�K�C�h��( Debug�p )
		OBJID_SYS_CAMERA			,	//	: �J����
		OBJID_SYS_LIGHT				,	//	: ���C�g
		OBJID_SYS_DIRECTIONAL		,	//	: ���������C�g
		OBJID_SYS_CURSOR			,	//	: �J�[�\��
		OBJID_SYS_SOUND				,	//	: ����
		OBJID_SYS_CHECKPOINT		,	//	: �`�F�b�N�|�C���g
		OBJID_SYS_CLEARAREA			,	//	: �N���A�̈�
		OBJID_SYS_RENDERTARGET		,	//	: �����_�[�^�[�Q�b�g
		OBJID_SYS_END				,	
		OBJID_SYS_START				,	

		OBJID_BEHAVIOR_TEST					,
		OBJID_BEHAVIOR_CHECKPOINTSAVE		,

		//	:�T�E���h�܂��
		//	:BGM
		//OBJID_SOUND_BGM_TITLE			,
		//OBJID_SOUND_BGM_PLAY			,
		//OBJID_SOUND_BGM_CLEAR			,
		//OBJID_SOUND_BGM_GAME_OVER		,

		//	:���ʉ�
		//OBJID_SOUND_SE_ALERT			,
		//OBJID_SOUND_SE_BLOKEN_ENEMY		,
		//OBJID_SOUND_SE_CHACK_POINT		,
		//OBJID_SOUND_SE_CLEAR			,
		//OBJID_SOUND_SE_ENTER			,
		//OBJID_SOUND_SE_FIRE				,
		//OBJID_SOUND_SE_GOAL				,
		//OBJID_SOUND_SE_PLAYER_BLOKEN	,
		//OBJID_SOUND_SE_INVINGVLE		,
		//OBJID_SOUND_SE_ITEMS			,
		//OBJID_SOUND_SE_MAGNETIC_FIELD	,
		//OBJID_SOUND_SE_SPARK			,


		//	: UI����
		OBJID_UI_BEGIN				= 0x2000,
		OBJID_UI_SPRITE				,	//	: UI�Ɏg���X�v���C�g
		OBJID_UI_SPRITEBUTTON		,	//	: �X�v���C�g�{�^����UI
		OBJID_UI_BUTTON_NORMAL		,	//	:
		OBJID_UI_BUTTON_HARD		,	//	:
		OBJID_UI_BUTTON_EXTRA		,	//	:
		OBJID_UI_BUTTON_BACK		,	//	:
		OBJID_UI_SELECTINFORMATION	,	//	:
		OBJID_UI_CHECKPOINT_CHAR	,	//	: �`�F�b�N�|�C���g
		OBJID_UI_LIFE				,	//	: ���C�t( �O�̂��� )
		OBJID_UI_SUPERGAUGE			,	//	: �Q�[�W
		OBJID_UI_MAGNETGAUGE_N		,	//	: N�ɃQ�[�W
		OBJID_UI_MAGNETGAUGE_S		,	//	: S�ɃQ�[�W
		OBJID_UI_SCORE				,	//	: �X�R�A
		OBJID_UI_TIME				,	//	: ����( ����? )
		OBJID_UI_END				,

		//	: 3D�I�u�W�F
		////
		// �v���~�e�B�u�n
		OBJID_3D_BEGIN				= 0x3000,
		OBJID_3D_POLYGON			,	//	: �Ƃ肠�����ǂݍ��񂾃��f���f�[�^
		OBJID_3D_BOX				,	//	: �Ƃ肠�����������
		OBJID_3D_BOX_PARALLEL		,	//	: �ς���?�E�E�E
		OBJID_3D_SPHERE				,	//	: �Ƃ肠�������������
		OBJID_3D_CYLINDER			,	//	: �Ƃ肠����������~���~��

		//	: �}���`�v���~�e�B�u
		OBJID_3D_MULTI_POLYGON		,	
		OBJID_3D_MULTI_BOX			,
		OBJID_3D_MULTI_BOX_PARALLEL	,
		OBJID_3D_MULTI_SPHERE		,
		OBJID_3D_MULTI_CYLINDER		,
		OBJID_3D_MULTI_TAURUS		,
		// �v���~�e�B�u�n
		////

		//	: 
		//OBJID_3D_MAGNET			,	//	: ����
		OBJID_3D_WALL				,	//	: ��
		OBJID_3D_ITEM				,	//	: �A�C�e��


		//	:
		//OBJID_3D_PLAYER				,
		OBJID_3D_USERMAGNET			,	//	: ���[�U�[
		OBJID_3D_COIL				,	//	: �v���C���[
		OBJID_3D_STATIC_MAGNET		,	//	: ����
		OBJID_3D_EFFECT				,	//	: �G�t�F�N�g
		OBJID_3D_WARNING			,	//	: �x��
		OBJID_3D_ENEMY				,	//	: �G



		//	: 
		OBJID_3D_TESTBOX			,	//	: �e�X�g�p�̔�
		OBJID_3D_DRAWOBB			,
		OBJID_3D_END				,


		//	: �I���
		OBJID_END					=  0xFFFFFFFFFFFFFFFF ,

	} ;
	enum POLE{
		POLE_S , 		/* S�� */
		POLE_N , 		/* N�� */
	};


}
//
//////////

 
#endif