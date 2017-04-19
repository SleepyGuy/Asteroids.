#include "App.hpp"
#include <iostream>
#include <algorithm>

// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

//
#include "Utils.h"

namespace Engine
{
	const float DESIRED_FRAME_RATE = 60.0f;
	const float DESIRED_FRAME_TIME = 1.0f / DESIRED_FRAME_RATE;
	bool stop = true;

	App::App(const std::string& title, const int width, const int height)
		: m_title(title)
		, m_width(width)
		, m_height(height)
		, m_nUpdates(0)
		, m_timer(new TimeManager)
		, m_mainWindow(nullptr)
	{
		m_game = new Game::AsteroidsGame(width, height);
		m_state = GameState::UNINITIALIZED;
		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();
	}

	App::~App()
	{
		
		delete m_game;

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
			// Polling
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
		// External dependencies
		//
		bool success = SDLInit() && GlewInit();
		if (!success)
		{
			m_state = GameState::INIT_FAILED;
			return false;
		}

		// Setup viewport
		//
		SetupViewport();

		// Change game state
		//
		m_state = GameState::INIT_SUCCESSFUL;

		//Game init
		m_game->Init();

		//Prints

		return true;
	}

	void App::OnKeyDown(SDL_KeyboardEvent keyBoardEvent)
	{		
		switch (keyBoardEvent.keysym.scancode)
		{
		case SDL_SCANCODE_W:
			//std::cout << "Moving Forward "<< std::endl;
			m_game->m_player[m_game->m_playerIndex]->MoveForward();
			break;
		case SDL_SCANCODE_A:
			//std::cout << "Moving Left " << std::endl;
			m_game->m_player[m_game->m_playerIndex]->MoveLeft();
			break;
		case SDL_SCANCODE_S:
			//std::cout << "Moving Down " << std::endl;
			//NOTHING
			break;
		case SDL_SCANCODE_D:
			//std::cout << "Moving Right " << std::endl;
			m_game->m_player[m_game->m_playerIndex]->MoveRight();
			break;
		case SDL_SCANCODE_UP:
			break;
		case SDL_SCANCODE_LEFT:
			break;
		case SDL_SCANCODE_RIGHT:
			break;
		case SDL_SCANCODE_DOWN:
			break;
		case SDL_SCANCODE_SPACE:
			std::cout << "Shoting " << std::endl;
			m_game->m_player[m_game->m_playerIndex]->Shoot();
			break;
		case SDL_SCANCODE_P:
			//Do nothing
			break;
		default:
			SDL_Log("Presing key.", keyBoardEvent.keysym.scancode);
			break;
		}
	}

	void App::OnKeyUp(SDL_KeyboardEvent keyBoardEvent)
	{
		switch (keyBoardEvent.keysym.scancode)
		{
		case SDL_SCANCODE_W:
			break;				  
		case SDL_SCANCODE_A:	 
			break;				  
		case SDL_SCANCODE_S:	  
			break;				  
		case SDL_SCANCODE_D:	  
			break;
		case SDL_SCANCODE_P:
			m_game->m_playerIndex++;
			break;
		case SDL_SCANCODE_UP:
			break;
		case SDL_SCANCODE_LEFT:
			break;
		case SDL_SCANCODE_DOWN:
			break;
		case SDL_SCANCODE_RIGHT:
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

		// Update code goes here
		//
		m_game->Update(DESIRED_FRAME_RATE);

		double endTime = m_timer->GetElapsedTimeInSeconds();
		double nextTimeFrame = startTime + DESIRED_FRAME_TIME;
		while (endTime < nextTimeFrame)
		{
			// Spin lock
			endTime = m_timer->GetElapsedTimeInSeconds();
		}

		double elapsedTime = endTime - startTime;        

		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();

		m_nUpdates++;
	}

	void App::Render()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_game->Render();
		SDL_GL_SwapWindow(m_mainWindow);
	}
	
	bool App::SDLInit()
	{
		// Initialize SDL's Video subsystem
		//
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

		// Make double buffer interval synced with vertical scanline refresh
		SDL_GL_SetSwapInterval(0);

		return true;
	}

	void App::SetupViewport()
	{
		
		float halfWidth = m_width * 0.5f;
		float halfHeight = m_height * 0.5f;

		// Set viewport 
		//
		glViewport(0, 0, m_width, m_height);

		// Set Mode to GL_PROJECTION
		//
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Set projection MATRIX to ORTHO
		//
		glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1, 1);

		// Setting Mode to GL_MODELVIEW
		//
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
		// Cleanup
		//
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_mainWindow);

		SDL_Quit();
	}

	void App::OnResize(int width, int height)
	{
		// TODO: Add resize functionality
		//
		m_width = width;
		m_height = height;

		SetupViewport();
	}

	void App::OnExit()
	{
		// Exit main for loop
		//
		m_state = GameState::QUIT;

		// Cleanup SDL pointers
		//
		CleanupSDL();
	}
}