// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// OpenGL without using GLUT - 2013 by Neil Dansey, Tim Dykes and Ian Cant, and using excerpts from here:
// http://bobobobo.wordpress.com/2008/02/11/opengl-in-a-proper-windows-app-no-glut/
// Feel free to adapt this for what you need, but please leave these comments in.

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// All edits made by Elliott Chaplin (with possible exception to lecturers throughout the year), UP706225 for TOGA Coursework - 2013/2014

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//TOGA - New Todo
//•fix power ups collision
//add powerup random spawns


#pragma once

#include "GameInfo.h"

// include the opengl and glu libraries
#pragma comment(lib, "opengl32.lib")	
#pragma comment(lib, "glu32.lib")



// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


// function prototypes:

// these were already here as part of the windows application template...
LRESULT CALLBACK WndProc(   HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );	
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow );

// these are ones we have added...
void updateGame(HDC deviceContext, gameInfo* currentGame);				// update the game here
void draw(HDC deviceContext, gameInfo* currentGame);        			// drawing function containing OpenGL function calls
//void controls();

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// In a C++ Windows app, the starting point is WinMain() rather than _tmain() or main().
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow )
{


	// some variables need for our game...
    MSG msg;								// this will be used to store messages from the operating system
	bool needToQuit = false;				// whether or not the player has quit the app
	gameInfo* currentGame = new gameInfo;	// this creates our game instance, and calls it currentGame



	// this bit creates a window class, basically a template for the window we will make later, so we can do more windows the same.
    WNDCLASS myWindowClass;
    myWindowClass.cbClsExtra = 0;											// no idea
    myWindowClass.cbWndExtra = 0;											// no idea
    myWindowClass.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );	// background fill black
    myWindowClass.hCursor = LoadCursor( NULL, IDC_ARROW );					// arrow cursor       
    myWindowClass.hIcon = LoadIcon( NULL, IDI_APPLICATION );				// type of icon to use (default app icon)
    myWindowClass.hInstance = hInstance;									// window instance name (given by the OS when the window is created)   
    myWindowClass.lpfnWndProc = WndProc;									// window callback function - this is our function below that is called whenever something happens
    myWindowClass.lpszClassName = TEXT("my window class name");				// our new window class name
    myWindowClass.lpszMenuName = 0;											// window menu name (0 = default menu?) 
    myWindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;				// redraw if the window is resized horizontally or vertically, allow different context for each window instance

    // Register that class with the Windows OS..
	RegisterClass(&myWindowClass);
    
   
	// create a rect structure to hold the dimensions of our window
    RECT rect;
    SetRect( &rect, TOPLEFTX,				// the top-left corner x-coordinate
                    TOPLEFTY,				// the top-left corner y-coordinate
                    TOPLEFTX + WIDTH,		// far right
                    TOPLEFTY + HEIGHT );	// far left
    

    
    // adjust the window, no idea why.
    AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false );

  
    
    // call CreateWindow to create the window
   HWND myWindow = CreateWindow(TEXT("my window class name"),		// window class to use - in this case the one we created a minute ago
                          TEXT("OpenGL, No GLUT"),					// window title
                          WS_OVERLAPPEDWINDOW,						// ??
                          TOPLEFTX, TOPLEFTY,						// x, y
                          TOPLEFTX + WIDTH, TOPLEFTY + HEIGHT,		// width and height
                          NULL, NULL,								// ??
                          hInstance, NULL);							// ??

    
   // check to see that the window created okay
    if( myWindow == NULL )
    {
        FatalAppExit( NULL, TEXT("CreateWindow() failed!") );
    }

    // if so, show it
    ShowWindow( myWindow, iCmdShow );
   

    // get a device context from the window
    HDC myDeviceContext = GetDC( myWindow );


	// we create a pixel format descriptor, to describe our desired pixel format. 
	// we set all of the fields to 0 before we do anything else
	// this is because PIXELFORMATDESCRIPTOR has loads of fields that we won't use
    PIXELFORMATDESCRIPTOR myPfd = { 0 };
 

    // now set only the fields of the pfd we care about:
    myPfd.nSize = sizeof( PIXELFORMATDESCRIPTOR );		// size of the pfd in memory
    myPfd.nVersion = 1;									// always 1

    myPfd.dwFlags = PFD_SUPPORT_OPENGL |				// OpenGL support - not DirectDraw
					PFD_DOUBLEBUFFER   |				// double buffering support
					PFD_DRAW_TO_WINDOW;					// draw to the app window, not to a bitmap image

    myPfd.iPixelType = PFD_TYPE_RGBA ;					// red, green, blue, alpha for each pixel
    myPfd.cColorBits = 24;								// 24 bit == 8 bits for red, 8 for green, 8 for blue.
														// This count of color bits EXCLUDES alpha.

    myPfd.cDepthBits = 32;								// 32 bits to measure pixel depth.



	// now we need to choose the closest pixel format to the one we wanted...	
    int chosenPixelFormat = ChoosePixelFormat( myDeviceContext, &myPfd );
 
	// if windows didnt have a suitable format, 0 would have been returned...
    if( chosenPixelFormat == 0 )
    {
        FatalAppExit( NULL, TEXT("ChoosePixelFormat() failed!") );
    }

	// if we get this far it means we've got a valid pixel format
	// so now we need to set the device context up with that format...
    int result = SetPixelFormat( myDeviceContext, chosenPixelFormat, &myPfd );

	// if it failed...
    if (result == NULL)
    {
        FatalAppExit( NULL, TEXT("SetPixelFormat() failed!") );
    }

  
    // we now need to set up a render context (for opengl) that is compatible with the device context (from windows)...
    HGLRC myRenderContext = wglCreateContext( myDeviceContext );

	// then we connect the two together
    wglMakeCurrent( myDeviceContext, myRenderContext );


    // opengl display setup
	glMatrixMode(GL_PROJECTION);	// select the projection matrix, i.e. the one that controls the "camera"
    glLoadIdentity();				// reset it
    gluPerspective(45.0,(float)WIDTH/(float)HEIGHT, 1, 1000);	// set up fov, and near / far clipping planes
	glViewport(0, 0, WIDTH, HEIGHT);							// make the viewport cover the whole window
	glClearColor( 0.9, 0.9, 0.9, 0 );								// set the colour used for clearing the screen



	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// main game loop starts here!
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	// as long as the player hasnt exited the app: 
    while( !needToQuit )
    {
		// this is the start of the main game loop, so we need to record the time...
		currentGame->frameStartTime = GetTickCount();

	//	time_t currentTime;
	//	struct tm timeInfo;

	//	time (&currentTime);
	//	localtime_s(&timeInfo, &currentTime);
			
		// we need to listen out for OS messages.
		// if there is a windows message to process...
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
			
			
			// if the message was a "quit" message...
			if( msg.message == WM_QUIT )
			{
				needToQuit = true;	// we want to quit asap
				currentGame->playerArray[0]->bulletArray.clear(); //deletes bullets on exit
				currentGame->playerArray[1]->bulletArray.clear(); //deletes bullets on exit
			}
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//										KEYDOWN
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
			
			// otherwise, if it was a "key pressed" message...
			else if (msg.message == WM_KEYDOWN)
			{
				switch (msg.wParam)
				{
//############################## Player 1 ##############################
					case PLAYER1UP:		
					// player 1 forward	
						currentGame->playerArray[0]->upPressed = true; //player tank forward	
						break;	
	
					case PLAYER1DOWN:		
						// player 1 reverse	
						currentGame->playerArray[0]->downPressed = true; //player tank reverse	
						break;	
		
					case PLAYER1RIGHT:		
						// player 1 right	
						currentGame->playerArray[0]->rightPressed = true; //player tank right	
						break;	
		
					case PLAYER1LEFT:		
						// player 1 left	
						currentGame->playerArray[0]->leftPressed = true; //player tank left	
						break;	
		
					case PLAYER1ROTATELEFT:		
						//player 1's turret left	
						currentGame->playerArray[0]->turretLeft = true; //players turret left	
						break;	
		
		
					case PLAYER1ROTATERIGHT:		
						//player 1's turret right	
						currentGame->playerArray[0]->turretRight = true; //players turret right	
						break;	
		
					case PLAYER1SHOOT:		
						//player 1's shooting	
						if (currentGame->playerArray[0]->canFire)//checks if player can shoot	
						{	
						currentGame->playerArray[0]->fireNormal = true;//if yes then shoots	
						currentGame->playerArray[0]->reload = false;	
						}	
						break;	
		
					case PLAYER1RELOAD:	//player 1 reload	
						if ((GetTickCount() - currentGame->playerArray[0]->previousTime) > RELOAD_TIME)	
						{	
						currentGame->playerArray[0]->canFire = true; //player can now shoot	
						}	
						break;	
		
					case PLAYER1SPECIAL: 		
						//player 1's special shot	
						if (currentGame->playerArray[0]->canFire && currentGame->playerArray[0]->hasSpecial)//checks if player can shoot	
						{	
							currentGame->playerArray[0]->fireSpecial = true;//if yes then shoots
							currentGame->playerArray[0]->reload = false;
							currentGame->playerArray[0]->hasSpecial = false;
						}	
						break;	
		
					case PLAYER1GRENADE:		
						//player 1's grenade shot	
						if (currentGame->playerArray[0]->canFire && currentGame->playerArray[0]->hasGrenade)//checks if player can shoot	
						{	
							currentGame->playerArray[0]->fireGrenade = true;//if yes then shoots
							currentGame->playerArray[0]->reload = false;
							currentGame->playerArray[0]->hasGrenade = false;
						}	
						break;	
		
					case PLAYER1SHEILD:		
						//player 1's normal sheild	
						currentGame->playerArray[0]->sheild = true;	
						currentGame->playerArray[0]->canFire = false;	
						break;	
		
//############################## Player 2 ##############################

					case PLAYER2UP:		
						// player 2 forward	
						currentGame->playerArray[1]->upPressed = true; //player tank forward	
						break;	
		
					case PLAYER2DOWN:		
						// player 2 reverse	
						currentGame->playerArray[1]->downPressed = true; //player tank reverse	
						break;	
		
					case PLAYER2RIGHT:		
						// player 2 right	
						currentGame->playerArray[1]->rightPressed = true; //player tank right	
						break;	
		
					case PLAYER2LEFT:		
						// player 2 left	
						currentGame->playerArray[1]->leftPressed = true; //player tank left	
						break;	
		
					case PLAYER2ROTATELEFT:		
						//player 2's turret left	
						currentGame->playerArray[1]->turretLeft = true; //players turret left	
						break;	
		
		
					case PLAYER2ROTATERIGHT:		
						//player 2's turret left	
						currentGame->playerArray[1]->turretRight = true; //players turret right	
						break;	
		
					case PLAYER2SHOOT:		
						//player 2's shooting	
						if (currentGame->playerArray[1]->canFire) //checks if player can shoot	
						{	
							currentGame->playerArray[1]->fireNormal = true; //if yes then shoots
							currentGame->playerArray[1]->reload = false; 
						}	
						break;	
		
					case PLAYER2RELOAD:	//player 2 reload	
						if ((GetTickCount() - currentGame->playerArray[1]->previousTime) > RELOAD_TIME)	
						{	
						currentGame->playerArray[1]->canFire = true; //player can now shoot	
						}	
						break;	
		
					case PLAYER2SPECIAL:		
						//player 2's special shot	
						if (currentGame->playerArray[1]->canFire && currentGame->playerArray[1]->hasSpecial)//checks if player can shoot	
						{	
							currentGame->playerArray[1]->fireSpecial = true;//if yes then shoots
							currentGame->playerArray[1]->reload = false;
							currentGame->playerArray[1]->hasSpecial = false;
						}	
						break;	
		
					case PLAYER2GRENADE:		
						//player 2's grenade shot	
						if (currentGame->playerArray[1]->canFire && currentGame->playerArray[1]->hasGrenade)//checks if player can shoot	
						{	
							currentGame->playerArray[1]->fireGrenade = true;//if yes then shoots
							currentGame->playerArray[1]->reload = false;
							currentGame->playerArray[1]->hasGrenade = false;
						}	
						break;	
		
					case PLAYER2SHEILD:		
						//player 1's normal sheild	
						currentGame->playerArray[1]->sheild = true;	
						currentGame->playerArray[1]->canFire = false;	
						break;	
		
					case 0x46:		
						//player 1's debug button	
						currentGame->playerArray[0]->testInt = 1;	
						currentGame->playerArray[0]->testFloat = 1.0f;	
						currentGame->playerArray[0]->testbool = true;	
						break;	
		
					case VK_ESCAPE:		
						needToQuit = true; //quits the game if escape is pressed	
						break;	
		
					default:		
						break;	
				}
			}
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//										KEYUP
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			// otherwise, if they let go of a key (you get the idea)
			else if (msg.message == WM_KEYUP)
			{
				switch (msg.wParam)
				{
//############################## Player 1 ##############################
					case PLAYER1UP:
						currentGame->playerArray[0]->upPressed = false;
						break;
					
					case PLAYER1DOWN:
						currentGame->playerArray[0]->downPressed = false;
						break;

					case PLAYER1LEFT:
						currentGame->playerArray[0]->leftPressed = false;
						break;
					
					case PLAYER1RIGHT:
						currentGame->playerArray[0]->rightPressed = false;
						break;

					case PLAYER1ROTATELEFT:
						currentGame->playerArray[0]->turretLeft = false;
						break;

					case PLAYER1ROTATERIGHT:
						currentGame->playerArray[0]->turretRight = false;
						break;

					case PLAYER1SHOOT:
						currentGame->playerArray[0]->fireNormal = false;
						break;

					case PLAYER1RELOAD:
						currentGame->playerArray[0]->reload = false;
						break;

					case PLAYER1SPECIAL:
						currentGame->playerArray[0]->fireSpecial = false;//if yes then shoots
						break;

					case PLAYER1GRENADE:
						currentGame->playerArray[0]->fireGrenade = false;//if yes then shoots
						break;

					case PLAYER1SHEILD:
						//player 1's normal sheild
						currentGame->playerArray[0]->sheild = false;
						break;

//############################## Player 2 ##############################

					case PLAYER2UP:
						currentGame->playerArray[1]->upPressed = false;					
						break;

					case PLAYER2DOWN:
						currentGame->playerArray[1]->downPressed = false;							
						break;		

					case PLAYER2RIGHT:
						currentGame->playerArray[1]->rightPressed = false;
						break;

					case PLAYER2LEFT:
						currentGame->playerArray[1]->leftPressed = false;
						break;

					case PLAYER2ROTATELEFT:
						currentGame->playerArray[1]->turretLeft = false;
						break;

					case PLAYER2ROTATERIGHT:
						currentGame->playerArray[1]->turretRight = false;
						break;

					case PLAYER2SHOOT:
						currentGame->playerArray[1]->fireNormal = false;
						break;

					case PLAYER2RELOAD:
						currentGame->playerArray[1]->reload = false;
						break;

					case PLAYER2SPECIAL:
						currentGame->playerArray[1]->fireSpecial = false;//if yes then shoots
						break;

					case PLAYER2GRENADE:
						currentGame->playerArray[1]->fireGrenade = false;//if yes then shoots
						break;

					case PLAYER2SHEILD:
						//player 1's normal sheild
						currentGame->playerArray[1]->sheild = false;
						break;

					case VK_ESCAPE:
						needToQuit = false;
						break;

					case 0x46:
						//player 1's debug button
						currentGame->playerArray[0]->testInt = 0;
						currentGame->playerArray[0]->testFloat = 0.0f;
						currentGame->playerArray[0]->testbool = false;
						break;	

					default:

						break;

				}


			}
			// if it was any other type of message (i.e. one we don't care about), process it as normal
            else 
            {
			
				TranslateMessage( &msg );
				DispatchMessage( &msg );
                
            }

            

        }
		
		// now update the gameplay...
		updateGame(myDeviceContext, currentGame);

		// now draw the scene...
		draw(myDeviceContext, currentGame);
		
		// this is the end of the main game loop, so we need to record the time again and then work out how long this frame took...
		currentGame->frameEndTime = GetTickCount();
		currentGame->frameDelta = (currentGame->frameEndTime - currentGame->frameStartTime);

    }
	// end of "while" loop


	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


    // the next bit will therefore happen when the player quits the app,
	// because they are trapped in the game loop as long as (needToQuit == false).


    // free up the memory used by the game state and set its pointer to NULL
    delete currentGame;
	currentGame = NULL;

    // UNmake our rendering context (make it 'uncurrent')
    wglMakeCurrent( NULL, NULL );

    // delete the rendering context, we no longer need it.
    wglDeleteContext( myRenderContext );

    // release our window's DC from the window
    ReleaseDC( myWindow, myDeviceContext );
  
	// end the program
    return msg.wParam;
}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// this function is called when any events happen to our window
LRESULT CALLBACK WndProc(   HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam ) 
{

    switch( message )
    {
		// if they exited the window...	
		case WM_DESTROY:
			// post a message "quit" message to the main windows loop
			PostQuitMessage( 0 ) ;
			return 0;
			break;
    }
 
	// must do this as a default case (i.e. if no other event was handled)...
    return DefWindowProc( hwnd, message, wparam, lparam );

}
