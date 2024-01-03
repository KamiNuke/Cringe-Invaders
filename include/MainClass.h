#pragma once
#include "Window.h"
#include "MachineState.h"

class MainClass
{
public:
	MainClass();
	~MainClass();

	void Loop();
private:
	Window m_window;
	MachineState* state{ nullptr };

	void Update();
	void Render();
};

