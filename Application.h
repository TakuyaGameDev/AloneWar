#pragma once
#include "Scene/BaseScene.h"
#include "Geometory.h"

class Controller;

constexpr float screen_x = 1000.0f;
constexpr float screen_y = 640.0f;

#define lpApp Application::getInstance()

class Application
{
public:
	static Application& getInstance(void)
	{
		static Application sinstance_;
		return sinstance_;
	}

	const Vector2I& GetViewport(void)
	{
		return Vector2I(screen_x, screen_y);
	}
	void Run(void);

	void Exit(void);
	bool SystemInit(void);

	// get controller
	const std::shared_ptr<Controller>& GetController(void)
	{
		return controller_;
	}


private:
	Application() = default;
	~Application();

	void operator=(const Application&) = delete;
	ScenePtr sptr_;
	// controller
	std::shared_ptr<Controller> controller_;
};

