#ifndef APPLICATION_H
#define APPLICATION_H
//------------------------------------------------------------------
/// \file    ProgramLoader.h
/// \author  Lloyd Phillips
/// \brief   This is the Application loader class
//------------------------------------------------------------------
#include <SDL.h>
#include "glew.h"
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Model.h"
#include "TextureLoader.h"
#include "FrameBuffer.h"

class Application
{
public:
	/// \brief constructor for the application class.
	Application(void);
	/// \brief deconstructor for the application class.
	~Application(void);
	/// \brief check if Glew has been initialised.
	bool InitGL();
	/// \brief initalises the application
	void init();
	/// \brief runs the application, uses Delta Time
	void run(float DT);
	/// \brief draws the application to screen
	void draw();
	/// \brief updates application based on Delta Time
	void update(float DT);
	/// \brief input handler for the application
	void inputHandler();
	/// \brief returns delta time of application
	float getDeltaTime();
	/// \brief returns screen width of application
	int getWidth();
	/// \brief returns screen height of application
	int getHeight();

private:
	int mouse_X, mouse_Y; ///<Mouse Co-ordinates
	SDL_Window *window; ///< Window for SDL
	SDL_Renderer *renderer; ///< Renderer for SDL
	SDL_GLContext glContext; ///< GL context for window
	unsigned int lastTime, current; ///< seed for delta time
	int winPosX; ///<window X position
	int winPosY; ///< window Y poisition
	int winWidth; ///< window width
	int winHeight; ///< window Height
	float camera_Zoom, camera_Left_Right, camera_Up_Down, camera_rotate; ///< Camera attributes
	glm::mat4 projectionMatrix, viewMatrix; ///< matrix for viewing
	float delta_Time; ///< Deltat time for frame rate.
	Model *skyDome, *house, *plane, *shelter,*car;
	TextureLoader *textLoad, *textLoad2, *textLoad3,*textLoad4,*textLoad5;
	FrameBuffer *fBuffer;


};
#endif; //!APPLICATION_H
