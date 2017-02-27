#include "App.hpp"

#include <iostream>
#include <algorithm>

// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <fstream>
#include <sstream>
#include <string>

#include "Configuration.hpp"

namespace Engine
{
	const float DESIRED_FRAME_RATE = 120.0f;
	const float DESIRED_FRAME_TIME = 0.1f / DESIRED_FRAME_RATE;

	App::App(const std::string& title, const int width, const int height)
		: m_title(title)
		, m_width(width)
		, m_height(height)
		, m_nUpdates(0)
		, m_timer(new TimeManager)
		, m_mainWindow(nullptr)
		, m_context(nullptr)
		, m_currentIndex(0)
		
	{
		m_state = GameState::UNINITIALIZED;
		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();
	}

	App::~App()
	{
		CleanupSDL();
	}

	void App::Execute()
	{
		if (m_state != GameState::INIT_SUCCESSFUL)
		{
			std::cerr << "Game INIT was not successful." << std::endl;
			return;
		}

		m_state = GameState::RUNNING;

		SDL_Event event;
		while (m_state == GameState::RUNNING)
		{
			// Input polling
			//
			while (SDL_PollEvent(&event))
			{
				OnEvent(&event);
			}

			//
			Update();
			Render();
		}
	}

	bool App::Init()
	{
		// Init the external dependencies
		//
		bool success = SDLInit() && GlewInit();
		if (!success)
		{
			m_state = GameState::INIT_FAILED;
			return false;
		}

		// Setup the viewport
		//
		SetupViewport();

		// Change game state
		//
		m_state = GameState::INIT_SUCCESSFUL;

		//Load models
		Asteroids::Utilities::Configuration configure;

		m_entities = configure.LoadModels();

		m_asteroid = configure.CreateAsteroid(10);

		return true;
	}

	void App::OnKeyDown(SDL_KeyboardEvent keyBoardEvent)
	{		
		switch (keyBoardEvent.keysym.scancode)
		{
		case SDL_SCANCODE_W:
			std::cout << "Moving up" << std::endl;
			m_entities[m_currentIndex]->MoveUp();
			break;
		case SDL_SCANCODE_A:
			std::cout << "Moving left" << std::endl;
			m_entities[m_currentIndex]->MoveLeft();
			break;
		case SDL_SCANCODE_S:
			std::cout << "Moving Down" << std::endl;
			m_entities[m_currentIndex]->MoveDown();
			break;
		case SDL_SCANCODE_D:
			std::cout << "Moving Right" << std::endl;
			m_entities[m_currentIndex]->MoveRight();
			break;
		default:
			//SDL_Log("%S was pressed.", keyBoardEvent.keysym.scancode);
			SDL_Log("Physical %s key is being pressed",
				SDL_GetScancodeName(keyBoardEvent.keysym.scancode),
				SDL_GetKeyName(keyBoardEvent.keysym.sym));
			break;
		}
	}

	void App::OnKeyUp(SDL_KeyboardEvent keyBoardEvent)
	{
		switch (keyBoardEvent.keysym.scancode)
		{
		case SDL_SCANCODE_P:
			m_currentIndex++;
			if (m_currentIndex > (m_entities.size() - 1))
			{
				m_currentIndex = 0;
			}
			std::cout << "Changed ship model" << std::endl;
			break;
		case SDL_SCANCODE_ESCAPE:
			OnExit();
			break;
		default:
			//DO NOTHING
			break;
		}
	}

	void App::Update()
	{
		double startTime = m_timer->GetElapsedTimeInSeconds();

		
		m_entities[m_currentIndex]->Update(DESIRED_FRAME_TIME);
		m_asteroid[0]->Update(DESIRED_FRAME_TIME);
		


		double endTime = m_timer->GetElapsedTimeInSeconds();
		double nextTimeFrame = startTime + DESIRED_FRAME_TIME;

		while (endTime < nextTimeFrame)
		{
		
			endTime = m_timer->GetElapsedTimeInSeconds();
		}

		   

		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();

		m_nUpdates++;
	}

	void App::Render()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_entities[m_currentIndex]->Draw();
		m_asteroid[0]->Draw();
		SDL_GL_SwapWindow(m_mainWindow);
	}

	bool App::SDLInit()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cerr << "Failed to init SDL" << std::endl;
			return false;
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		Uint32 flags =  SDL_WINDOW_OPENGL     | 
						SDL_WINDOW_SHOWN      | 
						SDL_WINDOW_RESIZABLE;

		m_mainWindow = SDL_CreateWindow(
			m_title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_width,
			m_height,
			flags
		);

		if (!m_mainWindow)
		{
			std::cerr << "Failed to create window!" << std::endl;
			SDL_Quit();
			return false;
		}

		m_context = SDL_GL_CreateContext(m_mainWindow);
		SDL_GL_MakeCurrent(m_mainWindow, m_context);

		SDL_GL_SetSwapInterval(0);

		return true;
	}

	void App::SetupViewport()
	{
		float halfWidth = m_width * 0.5f;
		float halfHeight = m_height * 0.5f;

		glViewport(0, 0, m_width, m_height);
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1, 1);

		glMatrixMode(GL_MODELVIEW);

	}

	bool App::GlewInit()
	{
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
			return false;
		}

		return true;
	}

	void App::CleanupSDL()
	{
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_mainWindow);

		SDL_Quit();
	}

	void App::OnResize(int width, int height)
	{
		m_width = width;
		m_height = height;

		SetupViewport();
	}

	void App::OnExit()
	{
		
		m_state = GameState::QUIT;

		
		CleanupSDL();
		
	}
}
