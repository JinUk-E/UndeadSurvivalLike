#pragma once

// 씬 타입
enum class SceneType
{
	Menu,
	Game,
	Loading,
	Dev,
	Count
};

// 키 타입
enum class KeyType
{
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,

	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,
	SpaceBar = VK_SPACE,

	KEY_1 = '1',
	KEY_2 = '2',

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	Q = 'Q',
	E = 'E'
};

// 키 상태
enum class KeyState
{
	None,
	Press,
	Down,
	Up,
	End
};

// 키 타입 개수
enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int32>(KeyState::End)
};

//오브젝트 클래스
enum class ObjectType
{
	None,
	Player,
	Projectile,
};

// 오브젝트 이동방향
enum class MoveDir
{
	Left,
	Right,
};

// 레이어
enum LAYER_TYPE
{
	LAYER_BACKGROUND,
	LAYER_OBJECT,
	LAYER_UI,
	LAYER_MAXCOUNT
};

// 충돌체
enum class ColliderType
{
	Box,
	Sphere,
	Capsule,
	Count
};

// 충돌 레이어
enum COLLISION_LAYER_TYPE : uint8
{
	COLLISION_LAYER_TYPE_OBJECT,
	COLLISION_LAYER_TYPE_GROUND,
	COLLISION_LAYER_TYPE_WALL,

	COLLISION_LAYER_TYPE_MAXCOUNT
};

// 방향키
enum DIRECTION
{
	DIRECTION_NONE = -1,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_MAXCOUNT
};


// 플레이어 상태
enum class PlayerState
{
	Idle,
	Move,
	Skill
};

// 타일 크기
enum TILE_SIZE
{
	TILE_WIDTH = 63,
	TILE_HEIGHT = 43,
	TILE_SIZEX = 48,
	TILE_SIZEY = 48,
};

// 사운드 타입
enum class SoundType
{
	BGM,
	Normal,
	Effect,
};

// 버튼 상태
enum ButtonState
{
	BS_Default,
	BS_Pressed,
	BS_Clicked,
	BS_MaxCount
};