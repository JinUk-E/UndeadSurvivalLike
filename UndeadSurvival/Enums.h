#pragma once

// �� Ÿ��
enum class SceneType
{
	Menu,
	Game,
	Loading,
	Dev,
	Count
};

// Ű Ÿ��
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

// Ű ����
enum class KeyState
{
	None,
	Press,
	Down,
	Up,
	End
};

// Ű Ÿ�� ����
enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int32>(KeyState::End)
};

//������Ʈ Ŭ����
enum class ObjectType
{
	None,
	Player,
	Projectile,
};

// ������Ʈ �̵�����
enum class MoveDir
{
	Left,
	Right,
};

// ���̾�
enum LAYER_TYPE
{
	LAYER_BACKGROUND,
	LAYER_OBJECT,
	LAYER_UI,
	LAYER_MAXCOUNT
};

// �浹ü
enum class ColliderType
{
	Box,
	Sphere,
	Capsule,
	Count
};

// �浹 ���̾�
enum COLLISION_LAYER_TYPE : uint8
{
	COLLISION_LAYER_TYPE_OBJECT,
	COLLISION_LAYER_TYPE_GROUND,
	COLLISION_LAYER_TYPE_WALL,

	COLLISION_LAYER_TYPE_MAXCOUNT
};

// ����Ű
enum DIRECTION
{
	DIRECTION_NONE = -1,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_MAXCOUNT
};


// �÷��̾� ����
enum class PlayerState
{
	Idle,
	Move,
	Skill
};

// Ÿ�� ũ��
enum TILE_SIZE
{
	TILE_WIDTH = 63,
	TILE_HEIGHT = 43,
	TILE_SIZEX = 48,
	TILE_SIZEY = 48,
};

// ���� Ÿ��
enum class SoundType
{
	BGM,
	Normal,
	Effect,
};

// ��ư ����
enum ButtonState
{
	BS_Default,
	BS_Pressed,
	BS_Clicked,
	BS_MaxCount
};