#pragma once
#ifndef APP_HPP
#define APP_HPP

// C++ STL
#include <string>
#include <list>
#include <vector>

// Asteroids
#include "SDLEvent.hpp"
#include "TimeManager.hpp"

//
#include "Asteroids.h"
#include "EnemyShip.h"

namespace Engine
{
	class App : public SDLEvent
	{
	public:
		struct GameState
		{
			enum State
			{
				UNINITIALIZED = 0,
				INIT_FAILED = 1,
				INIT_SUCCESSFUL = 2,
				RUNNING = 4,
				PAUSED = 8,
				QUIT = 16
			};
		};

		
		App( const std::string& title, const int width, const int height );
		~App( );
		void Execute						( );
		bool Init							( );
		void Update							( );
		void Render							( );
		
	private:
		bool SDLInit						( );
		bool GlewInit						( );
		void SetupViewport					( );
		void CleanupSDL						( );
		void OnResize						( int width, int height ) override;
		void OnExit							( ) override;
		void OnKeyDown						( SDL_KeyboardEvent keyBoardEvent ) override;
		void OnKeyUp						( SDL_KeyboardEvent keyBoardEvent ) override;

		int	m_width;
		int	m_height;
		int	m_nUpdates;
		double m_lastFrameTime;
		std::string	m_title;
		SDL_Window*	m_mainWindow;
		SDL_GLContext m_context;
	    GameState::State m_state;
		Engine::TimeManager* m_timer;
		Game::AsteroidsGame* m_game;
		

		int m_lives = 10;
		
	};
}
#endif /* GAME_HPP */