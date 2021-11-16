#pragma once

namespace OBJID
{
	enum ID
	{
		PLAYER,
		MONSTER,
		MISSILE,
		END
	};
}

namespace GAMERESULT
{
	enum RESULT
	{
		NONE,
		WIN,
		LOSE,
		END
	};
}


namespace OBJECT {
	enum OBJECT_TYPE
	{
		OBJECT_TYPE_PLAYER,
		OBJECT_TYPE_BULLET,
		OBJECT_TYPE_MONSTER,
		OBJECT_TYPE_END
	};

	enum POINT_TYPE
	{
		POINT_TYPE_MOUSE,
		POINT_TYPE_TARGET,
		POINT_TYPE_AIM,
		POINT_TYPE_END
	};


	enum DIRECTION
	{
		DIRECTION_LEFT,
		DIRECTION_TOP,
		DIRECTION_RIGHT,
		DIRECTION_BOTTOM,
		DIRECTION_END
	};
}

