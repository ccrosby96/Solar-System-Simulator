#include "SDLGraphicsProgram.hpp"
#include "Camera.hpp"
#include "Terrain.hpp"
#include "Sphere.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <filesystem>

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h){
	// Initialization flag
	bool success = true;
	// String to hold any errors that occur.
	std::stringstream errorStream;
	// The window we'll be rendering to
	m_window = NULL;

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO)< 0){
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else{
		//Use OpenGL 3.3 core
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
		// We want to request a double buffer for smooth updating.
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		//Create window
		m_window = SDL_CreateWindow( "Lab",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                w,
                                h,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

		// Check if Window did not create.
		if( m_window == NULL ){
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		//Create an OpenGL Graphics Context
		m_openGLContext = SDL_GL_CreateContext( m_window );
		if( m_openGLContext == NULL){
			errorStream << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		// Initialize GLAD Library
		if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
			errorStream << "Failed to iniitalize GLAD\n";
			success = false;
		}

		//Initialize OpenGL
		if(!InitGL()){
			errorStream << "Unable to initialize OpenGL!\n";
			success = false;
		}
  	}

    // If initialization did not work, then print out a list of errors in the constructor.
    if(!success){
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors=errorStream.str();
        SDL_Log("%s\n",errors.c_str());
    }else{
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }

	// SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN); // Uncomment to enable extra debug support!
	GetOpenGLVersionInfo();


    // Setup our Renderer
    m_renderer = new Renderer(w,h);    
}


// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    if(m_renderer!=nullptr){
        delete m_renderer;
    }


    //Destroy window
	SDL_DestroyWindow( m_window );
	// Point m_window to NULL to ensure it points to nothing.
	m_window = nullptr;
	//Quit SDL subsystems
	SDL_Quit();
}


// Initialize OpenGL
// Setup any of our shaders here.
bool SDLGraphicsProgram::InitGL(){
	//Success flag
	bool success = true;

	return success;
}

// ====================== Create the planets =============
// NOTE: I will admit it is a little lazy to have these as globals,
//       we could build on our ObjectManager structure to manage the
//       each object that is inserted and automatically create a 'SceneNode'
//       for it for example. Or otherwise, build a 'SceneTree' class that
//       manages creating nodes and setting their type.
//       (e.g. A good use of the Factory Design Pattern if you'd like to
//             invetigate further--but it is beyond the scope of this assignment).

// Create the Moon
Object* sphere3;
SceneNode* Moon;
Object* m1;
SceneNode* Moon2;
Object* m2;
SceneNode* Moon3;
Object* m4;
SceneNode* Moon4;
// Create the Earth
Object* sphere2;
SceneNode* Earth;
// Create the Sun
Object* sphere;
SceneNode* Sun;
// Create Mercury
Object* merc;
SceneNode* Mercury;
//Mars stuff
Object* mars;
SceneNode* Mars;

//Jupiter Stuff
Object* jup;
SceneNode* Jupiter;

Object* europa;
SceneNode* Europa;

Object* ganymede;
SceneNode* Ganymede;

Object* lo;
SceneNode* Lo;

Object* m5;
Object* m6;
SceneNode* Moon6;
SceneNode* Moon5;

Object* sat;
SceneNode* Saturn;
Object* ring;
SceneNode* Rings;

Object* venus;
SceneNode* Venus;

Object* uranus;
SceneNode* Uranus;

Object* neptune;
SceneNode* Neptune;



// ====================== Create the planets =============

//Loops forever!
void SDLGraphicsProgram::Loop(){

    // ================== Initialize the planets ===============
    static float rot = 0.0f;
    static float incrementor = 0.0f;

    static float planet_scaler = 1.0f;
    // getting full path to cwd on your machine for stbi_load function
    std::string path = std::filesystem::current_path();
    path += "/planets/";
    // Uranus
    uranus = new Sphere();
    uranus->LoadJPGTexture(path + "2k_uranus.jpeg");
    Uranus = new SceneNode(uranus);

    // Neptune
    neptune = new Sphere();
    neptune->LoadJPGTexture(path + "2k_neptune.jpeg");
    Neptune = new SceneNode(neptune);
    
    //Saturn Stuff
    sat = new Sphere();
    sat->LoadJPGTexture(path + "2k_saturn.jpeg");
    Saturn = new SceneNode(sat);

    ring = new Sphere();
    ring->LoadJPGTexture(path + "2k_saturn_ring_alpha.png");
    Rings = new SceneNode(ring);

    // Jupiter things
    m5 = new Sphere();
    m6 = new Sphere();

    m5->LoadJPGTexture(path + "2k_moon.jpeg");
    m6->LoadJPGTexture(path + "2k_moon.jpeg");

    Moon5 = new SceneNode(m5);
    Moon6 =new SceneNode(m6);

    jup = new Sphere();
    jup->LoadJPGTexture(path + "2k_jupiter.jpeg");
    Jupiter = new SceneNode(jup);

    europa = new Sphere();
    europa->LoadJPGTexture(path + "europa.jpeg");
    Europa = new SceneNode(europa);

    ganymede = new Sphere();
    ganymede->LoadJPGTexture(path + "ganymede.jpeg");
    Ganymede = new SceneNode(ganymede);

    lo = new Sphere();
    lo->LoadJPGTexture(path + "lo.jpeg");
    Lo = new SceneNode(lo);

    
    // Create Mars moon
    m2 = new Sphere();
    //m2->LoadTexture("rock.ppm");
    m2->LoadJPGTexture(path + "2k_moon.jpeg");
    Moon2 = new SceneNode(m2);
   
    m4 = new Sphere();
    //m4->LoadTexture("rock.ppm");
    m4->LoadJPGTexture(path + "2k_moon.jpeg");
    Moon4 = new SceneNode(m4);
  
    // Create Mars
    mars = new Sphere();
    mars->LoadJPGTexture(path + "2k_mars.jpeg");
    Mars = new SceneNode(mars);
  
    // Create Mercury
    merc = new Sphere();
    merc->LoadJPGTexture(path + "2k_mercury.jpeg");
    Mercury = new SceneNode(merc);

    venus = new Sphere();
    venus->LoadJPGTexture(path + "2k_venus_atmosphere.jpeg");
    Venus = new SceneNode(venus);

    // Create new geometry for Earth's Moon
    sphere3 = new Sphere();
    //sphere3->LoadTexture("rock.ppm");
    sphere3->LoadJPGTexture(path + "2k_moon.jpeg");
    // Create a new node using sphere3 as the geometry
    Moon = new SceneNode(sphere3);

    // Create the Earth
    sphere2 = new Sphere();
    //sphere2->LoadTexture("earth.ppm");
    sphere2->LoadJPGTexture(path + "2k_earth_daymap.jpeg");
    Earth = new SceneNode(sphere2);
    // Create the Sun
    sphere = new Sphere();
    //sphere->LoadTexture("sun.ppm");
    sphere->LoadJPGTexture(path + "2k_sun.jpeg");
    Sun = new SceneNode(sphere);

    // Render our scene starting from the sun.
    m_renderer->setRoot(Sun);
    // Make the Earth a child of the Sun
    Sun->AddChild(Earth);
    Sun->AddChild(Mercury);
    Sun->AddChild(Venus);
    Sun->AddChild(Mars);
    Sun->AddChild(Jupiter);
    Sun->AddChild(Saturn);
    Sun->AddChild(Neptune);
    Sun->AddChild(Uranus);

   // Sun->AddChild(Space);
    // Make the Moon a child of the Earth
    Earth->AddChild(Moon);

    Mars->AddChild(Moon2);
    Mars->AddChild(Moon4);

    //Jupiter->AddChild(Moon5);
    //Jupiter->AddChild(Moon6);
    Jupiter->AddChild(Europa);
    Jupiter->AddChild(Ganymede);
    Jupiter->AddChild(Lo);

    Saturn->AddChild(Rings);

    // Set a default position for our camera
    m_renderer->GetCamera(0)->SetCameraEyePosition(0.0f,0.0f,10.0f);

    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();

    // Set the camera speed for how fast we move.
    float cameraSpeed = 3.0f;
    
    // While application is running
    while(!quit){

        //Handle events on queue
        while(SDL_PollEvent( &e ) != 0){
            // User posts an event to quit
            // An example is hitting the "x" in the corner of the window.
            if(e.type == SDL_QUIT){
                quit = true;
            }
            // Handle keyboad input for the camera class
            if(e.type==SDL_MOUSEMOTION){
                // Handle mouse movements
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
                m_renderer->GetCamera(0)->MouseLook(mouseX, mouseY);

            }
            switch(e.type){
                // Handle keyboard presses
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case SDLK_LEFT:
                            m_renderer->GetCamera(0)->MoveLeft(cameraSpeed);
                            break;
                        case SDLK_RIGHT:
                            m_renderer->GetCamera(0)->MoveRight(cameraSpeed);
                            break;
                        case SDLK_UP:
                            m_renderer->GetCamera(0)->MoveForward(cameraSpeed);
                            break;
                        case SDLK_DOWN:
                            m_renderer->GetCamera(0)->MoveBackward(cameraSpeed);
                            break;
                        case SDLK_RSHIFT:
                            m_renderer->GetCamera(0)->MoveUp(cameraSpeed);
                            break;
                        case SDLK_s:
                            m_renderer->GetCamera(0)->MoveDown(cameraSpeed);
                            break;
                        case SDLK_z:
                            // zooming in here... decrease our fov
                            m_renderer->GetCamera(0)->ProcessZoom(1.0f);
                            break;
                        case SDLK_x:
                            // zoomin out here. increasing our fov
                            m_renderer->GetCamera(0)->ProcessZoom(-1.0f);
                            break;
                        case SDLK_2:
                            // increase rate of orbital simulation
                            incrementor += 0.005f;
                            break;
                        case SDLK_1:
                            incrementor -= 0.005f;
                            if (incrementor < 0.0f)
                                incrementor = 0.0f;
                            break;
                        case SDLK_3:
                            planet_scaler -= 0.05;
                            if (planet_scaler < 1.0f)
                                planet_scaler = 1.0f;
                        case SDLK_4:
                            planet_scaler += 0.05f;
                            break;
                        case SDLK_0:
                            planet_scaler = 1.0f;
                            incrementor = 0.0f;
                            break;

                    

                    }
                break;
            }
       

        } // End SDL_PollEvent loop.
        // ================== Use the planets ===============
        // TODO:
        //      After the planets have been created, and the hiearchy
        //      has been made, you can transform them.
        //      Note, you'll need to setup the scene graph world/local
        //      transformation correctly first before the planets are shown.
        //      
        //      The 'Sun' for example will be the only object shown initially
        //      since the rest of the planets are children (or grandchildren)
        //      of the Sun.
        rot += incrementor;
        if (rot>360){rot=0;}
       
     

        Sun->GetLocalTransform().LoadIdentity();		
        // ... transform the Sun
        Sun->GetLocalTransform().Scale(100.0f,100.0f,100.0f);

        // Rocky Planets

        Mercury->GetLocalTransform().LoadIdentity();
        Mercury->GetLocalTransform().Rotate(rot, 0.0f, 1.0f, 0.0f);
        Mercury->GetLocalTransform().Translate(1.2f,0.0f,0.0f); 
        Mercury->GetLocalTransform().Scale(planet_scaler*0.00350877f,planet_scaler*0.00350877f,planet_scaler*0.00350877f);
       
        Venus->GetLocalTransform().LoadIdentity();
        Venus->GetLocalTransform().Rotate(0.3911111111*rot, 0.0f,1.0f,0.0f);
        Venus->GetLocalTransform().Translate(1.4f,0.0f,0.0f);
        Venus->GetLocalTransform().Scale(planet_scaler*0.00869915f,planet_scaler*0.00869915f,planet_scaler*0.00869915);
        

        Earth->GetLocalTransform().LoadIdentity();		
        Earth->GetLocalTransform().Rotate(0.2410958904*rot,0.0f, 1.0f,0.0f);  
        Earth->GetLocalTransform().Translate(1.6,0,0);
        Earth->GetLocalTransform().Scale(planet_scaler*0.00917431,planet_scaler*0.00917431,planet_scaler*0.00917431);
       

        Mars->GetLocalTransform().LoadIdentity();
        Mars->GetLocalTransform().Rotate(0.12809315787*rot,0.0f,1.0f,0.0f);
         Mars->GetLocalTransform().Translate(1.73f,0.0f,0.0f);
         Mars->GetLocalTransform().Scale(planet_scaler*0.00488141f,planet_scaler*0.00488141f,planet_scaler*0.00488141f);
         // Gas Giants

        Jupiter->GetLocalTransform().LoadIdentity();
        Jupiter->GetLocalTransform().Rotate(0.0200913242*rot, 0.0f, 1.0f,0.0f);    
        Jupiter->GetLocalTransform().Translate(2.0f,0.0f,0.0f);
        Jupiter->GetLocalTransform().Scale(0.10276269f,0.10276269f,0.10276269f);

        Europa->GetLocalTransform().LoadIdentity();
        Europa->GetLocalTransform().Translate(2.0f, 1.0f,0.0f);
         Europa->GetLocalTransform().Scale(0.02232545, 0.02232545,0.02232545);

         Ganymede->GetLocalTransform().LoadIdentity();
         Ganymede->GetLocalTransform().Translate(-2.0f, 0.0f,0.0f);
         Ganymede->GetLocalTransform().Scale(0.01144743f, 0.01144743f, 0.01144743f);

         Lo->GetLocalTransform().LoadIdentity();
         Lo->GetLocalTransform().Translate(0.0f, 0.5f, 1.5f);
         Lo->GetLocalTransform().Scale(0.02605603f, 0.02605603f, 0.02605603f);

         Saturn->GetLocalTransform().LoadIdentity();
        Saturn->GetLocalTransform().Rotate(0.0083136514f*rot, 0.0f,1.0f, 0.0f);
         Saturn->GetLocalTransform().Translate(2.50f,0.0f,0.0f);
       
        Saturn->GetLocalTransform().Scale(0.08662929f,0.08662929f, 0.08662929f);
         Rings->GetLocalTransform().LoadIdentity();
        Rings->GetLocalTransform().Scale(2.0f, 0.05f,2.0f);

        Uranus->GetLocalTransform().LoadIdentity();
        Uranus->GetLocalTransform().Rotate(0.0028701892f*rot, 0.0f, 1.0f, 0.0f);
        Uranus->GetLocalTransform().Translate(2.8f,0.0f,0.0f);
        Uranus->GetLocalTransform().Scale(0.03673854f, 0.03673854f, 0.03673854f);

        Neptune->GetLocalTransform().LoadIdentity();
        Neptune->GetLocalTransform().Rotate(0.0014611872f*rot, 0.0f, 1.0f,0.0f);
        Neptune->GetLocalTransform().Translate(3.0f,0,0);
        Neptune->GetLocalTransform().Scale(0.0355958f,0.0355958f,0.0355958f);

        Moon5->GetLocalTransform().LoadIdentity();
        Moon6->GetLocalTransform().LoadIdentity();

        Moon5->GetLocalTransform().Translate(2.0f,0.0f,0.0f);
        Moon5->GetLocalTransform().Rotate(rot, 0.0f,1.0f,0.0f);
        Moon5->GetLocalTransform().Scale(0.4f,0.4f,0.4f);

        Moon6->GetLocalTransform().Translate(-2.0f, 0.0f,0.0f);
        Moon6->GetLocalTransform().Rotate(rot, 0.0f,1.0f,0.0f);
        Moon6->GetLocalTransform().Scale(0.4f,0.4f,0.4f);


        Moon->GetLocalTransform().LoadIdentity();		
        // ... transform the Moon
        Moon->GetLocalTransform().Rotate(3.37926*rot, 0.0f, 1.0f, 0.0f);
        Moon->GetLocalTransform().Translate(2,0,0);
        Moon->GetLocalTransform().Scale(0.27,0.27,0.27);
        Moon2->GetLocalTransform().Rotate(0.1*rot, 0.0f,1.0f,0.0f);

        // Update our scene through our renderer
        m_renderer->Update();
        // Render our scene using our selected renderer
        m_renderer->Render();
        // Delay to slow things down just a bit!
        SDL_Delay(25);  // TODO: You can change this or implement a frame
                        // independent movement method if you like.
      	//Update screen of our specified window
      	SDL_GL_SwapWindow(GetSDLWindow());
	}
    //Disable text input
    SDL_StopTextInput();
}


// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::GetSDLWindow(){
  return m_window;
}

// Helper Function to get OpenGL Version Information
void SDLGraphicsProgram::GetOpenGLVersionInfo(){
	SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
	SDL_Log("Vendor: %s",(const char*)glGetString(GL_VENDOR));
	SDL_Log("Renderer: %s",(const char*)glGetString(GL_RENDERER));
	SDL_Log("Version: %s",(const char*)glGetString(GL_VERSION));
	SDL_Log("Shading language: %s",(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

    // File path stuff

    std::filesystem::path p = "2k_sun.jpeg";

    std::string path = std::filesystem::current_path();


    std::cout << "working dir path is " << path << '\n';

    path += "/planets/";

    std::cout << "path to planets is " << path << '\n';

    std::cout << path << std::endl;
   
}
