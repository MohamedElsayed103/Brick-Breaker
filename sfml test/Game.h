#pragma once
#include <sfml/System.hpp>
#include <sfml/Window.hpp>
#include <sfml/Audio.hpp>
#include <sfml/Network.hpp>
#include <sfml/Graphics.hpp>


class Game
{
private:
	void initvariables();
	void initwindow();

public:
	
	Game();
	virtual ~Game();

	//functions
	void update();
	void render();
};
