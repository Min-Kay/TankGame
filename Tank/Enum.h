#pragma once

namespace OBJID
{
	enum ID
	{
		PLAYER,
		MONSTER,
		MISSILE,
		SATELLITE,
		OBSTACLE,
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


namespace GAME {
	enum GAMEID
	{
		MENU,
		STAGE_ONE,
		STAGE_TWO,
		STAGE_THREE,
		STAGE_FOUR,
		END
	};
}


namespace MONSTER {
	enum LEESIN
	{
		IDLE,
		PUNCH,
		BILLIARD,
		GROGGY,
		DEAD,
		END
	};
}

