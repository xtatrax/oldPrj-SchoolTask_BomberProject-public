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

#define CF_SINGLETHREAD			/* �V���O���X���b�h���[�h     */
#define DRAW_MOUSE	(true)		
//#define CF_LOADINGANIMATION		/* ���[�h��ʂŃA�j���[�V���� */
#if defined(DEBUG) || defined(_DEBUG)
	#define ON_DEBUGGINGPROCESS			/* �f�o�b�N���[�h             */
	#define DEBUG_STRINGS_ON			/* �f�o�b�O�p�������L���� */
	
	#define ___MLP_DEBUG_TIMEDRAW_ 
	//#define ON_GUIDELINE
	//#define CF_FULLSCREEN				/* �t���X�N���[�����[�h       */

#else
	#define CF_FULLSCREEN				/* �t���X�N���[�����[�h       */
#endif
#define DEBUG_KEYBORD_ON			/* �f�o�b�O�p�L�[�{�[�h�����L���� */

//	: �f�t�@�C���萔
#define MAP_PARTS_HEIGHT		(    1.0f)	/*  */
#define MAP_PARTS_WIDTH			(    1.0f)	/*  */
#define BASE_CLIENT_HEIGHT		(  600.0f)	/* ��ɂȂ�`��̈�̍��� */
#define BASE_CLIENT_WIDTH		( 1024.0f)	/* ��ɂȂ�`��̈�̕�   */
#define STANDARD_WINDOW_HEIGHT  (  600.0f)	/* �E�C���h�E���[�h�̍���   */
#define STANDARD_WINDOW_WIDTH   ( 1024.0f)	/* �E�C���h�E���[�h�̕�     */
#define DRAW_TOLERANCE			(   20.0f)	/* �J��������̕`�拗�� */

#define DEFAULT_WINDOW_TITLE		( L"�E�C���h�E�^�C�g��" )
#define DEFAULT_WINDOW_CLASS_NAME	( L"�E�C���h�E�N���X�l�[��" )

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


#define MYVK_DEBUG_STOP_UPDATE		( VK_F12 )
#define MYVK_DEBUG_SLOW_UPDATE		( VK_F11 )
#define MYVK_DEBUG_OUTPUT_DBGSTR	( VK_F9  )
#define MYVK_DEBUG_OUTPUT_MEMORY	( VK_F8  )
#define MYVK_DEBUG_OBB_DRAW			( VK_F7  )

//
//////////

//


//
namespace wiz{
	//	: �Q�[�������Z�[�W
	enum{
		GM_WITHOUT				,
		GM_OPENSTAGE_TITLE		,
		GM_OPENSTAGE_PLAY		,
		GM_OPENSTAGE_RESULT		,
		GM_OPENSTAGE_RANKING	,
		GM_OPENSTAGE_OPTION		,
		GM_OPENSTAGE_GAMECLEAR	,
		GM_OPENSTAGE_GAMEOVER	,
		GM_EXIT					,

		GM_OPENDEBUGSTAGE_DEBUGMENU      ,
		GM_OPENDEBUGSTAGE_STAGELOADERTEST,
		GM_OPENDEBUGSTAGE_TATEAWORKSPACE ,
		GM_OPENDEBUGSTAGE_TOJIWORKSPACE  ,
		GM_OPENDEBUGSTAGE_HSWORKSPACE    ,
		GM_OPENDEBUGSTAGE_STAGECREATE    ,

		//////////
		//	: 
		GM_PLAYOPENING_END	,

	};
	//////	: 
	////enum CLASSID{
	////	/////////
	////	//
	////	//	���̗񋓌^�͊O���t�@�C���Ŏg�p����̂�
	////	//	�d�l�ɏ]����΂ɒl�𖾋L���邱��
	////	//

	////	CLASSID_NONE		=    0 ,
	////	CLASSID_TESTTIP		=    1 ,
	////	CLASSID_WALL		=  100 ,
	////	CLASSID_ENEMY		=    3 ,



	////	CLASSID_END			=  0xFFFFFFFFFFFFFFFF ,
	////};

	enum OBJID{
		OBJID_NONE					= 0x0000,	//	: �Ȃ�
		OBJID_UNK					= 0x0001,	//	: ����I�u�W�F

		//	: �V�X�e���֌W
		OBJID_SYS_BEGIN				= 0x1000,
		OBJID_SYS_GUIDELINE			,	//	: XYZ�K�C�h��( Debug�p )
		OBJID_SYS_CAMERA			,	//	: �J����
		OBJID_SYS_LIGHT				,	//	: ���C�g
		OBJID_SYS_SOUND				,	//	: ����
		OBJID_SYS_CHECKPOINT		,	//	: �`�F�b�N�|�C���g
		OBJID_SYS_CLEARAREA			,	//	: �N���A�̈�
		OBJID_SYS_RENDERTARGET		,	//	: �����_�[�^�[�Q�b�g
		OBJID_SYS_END				,	


		//	:�T�E���h�܂��
		//	:BGM
		OBJID_SOUND_BGM_TITLE		,
		OBJID_SOUND_BGM_PLAY		,
		OBJID_SOUND_BGM_CLEAR		,
		OBJID_SOUND_BGM_GAME_OVER	,

		//	:���ʉ�
		OBJID_SOUND_SE_ALERT		,
		OBJID_SOUND_SE_BLOKEN_ENEMY	,
		OBJID_SOUND_SE_CHACK_POINT	,
		OBJID_SOUND_SE_CLEAR		,
		OBJID_SOUND_SE_ENTER		,
		OBJID_SOUND_SE_FIRE			,
		OBJID_SOUND_SE_GOAL			,
		OBJID_SOUND_SE_HIT_ENEMY	,
		OBJID_SOUND_SE_INVINGVLE	,
		OBJID_SOUND_SE_MAGNETIC_FIELD,
		OBJID_SOUND_SE_SPARK		,


		//	: UI����
		OBJID_UI_BEGIN				= 0x2000,
		OBJID_UI_SPRITE				,	//	: UI�Ɏg���X�v���C�g
		OBJID_UI_SPRITEBUTTON		,	//	: �X�v���C�g�{�^����UI
		OBJID_UI_LIFE				,	//	: ���C�t( �O�̂��� )
		OBJID_UI_GAUGE				,	//	: �Q�[�W
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
		OBJID_3D_MAGNET				,	//	: ����
		OBJID_3D_WALL				,	//	: ��
		OBJID_3D_ITEM				,	//	: �A�C�e��

		//	:
		OBJID_3D_PLAYER				,
		OBJID_3D_USERMAGNET			,	//	: ���[�U�[
		OBJID_3D_COIL				,	//	: �v���C���[
		OBJID_3D_EFFECT				,	//	: �G�t�F�N�g
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

//////////
//	: �O���[�o���ȕϐ�

extern D3DXVECTOR3 g_vZero ;	//	: �[���x�N�g��
extern D3DXVECTOR3 g_vOne  ;	//	: ��x�N�g��
extern D3DXVECTOR3 g_vMax  ;	//	: �ō��x�N�g��
extern D3DXVECTOR3 g_vMin  ;	//	: �Œ�x�N�g��

extern wstring g_sDefaultTexturePath ;	//	: �e�N�X�`���̒u����

//	
//////////
 
#endif