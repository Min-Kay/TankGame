#pragma once
#include "Game.h"

class Menu :
	public Game
{
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	RECT m_Select_Rect[4]; 
};

