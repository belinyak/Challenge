#ifndef CHALLENGE_INPUTHANDLER_H
#define CHALLENGE_INPUTHANDLER_H

extern Camera g_camera;


namespace InputHandler
{
//NOTE(mate): function prototype
    
    void MouseCallback(GLFWwindow* _window, int _button, int _action, int _mods)
    {
	if (_action == GLFW_PRESS)//|| _action == GLFW_REPEAT )
	{
	    switch (_button)
	    {
	    case GLFW_MOUSE_BUTTON_RIGHT :
		std::cout << "rmb\n";
		break;
	    case GLFW_MOUSE_BUTTON_LEFT:
		std::cout << "lmb\n";
		break;
	    default:
		break;
	    }
	}
    }
    
    
    void ScrollCallback(GLFWwindow* _window, double _x, double _y)
    {
	Vector3 cameraMove;
	
	//NOTE(mate): y<0 -> scroll down
	if( _y < 0 )
	{
	    cameraMove = g_camera.forward();
	}
	else if(_y > 0)
	{
	    cameraMove = g_camera.backward();
	}
	g_camera.transform.position += cameraMove;
    }


    void updateCamera(GLFWwindow* window)
    {

	if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
	{
	    g_camera.transform.position.y += 0.3f;
	}

	if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
	{
	    g_camera.transform.position.y -= 0.3f;
	}
	if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
	{
	    g_camera.transform.position.x+= 0.3f;
	}
	if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
	{
	    g_camera.transform.position.x -= 0.3f;
	}    
    }

    

} // !namespace InputHandler

INTERNAL void WindowShouldClose(GLFWwindow* _window, bool* _running)
{
    if (glfwWindowShouldClose(_window) ||
	glfwGetKey(_window, GLFW_KEY_ESCAPE))
    {

	*_running = false;
    }
}
#endif // !#define CHALLENGE_INPUTHANDLER_H
