#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	muevex = 2.0f;
	mouseFirstMoved = true;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
	// Inicializar las 4 variables de estado
	puertaIzqAbierta = false;
	puertaDerAbierta = false;
	animandoPuertaIzq = false;
	animandoPuertaDer = false;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	muevex = 2.0f;
	mouseFirstMoved = true;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
	// Inicializar las 4 variables de estado
	puertaIzqAbierta = false;
	puertaDerAbierta = false;
	animandoPuertaIzq = false;
	animandoPuertaDer = false;
}

int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Practica 09: Animacion", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, bufferWidth, bufferHeight);
	glfwSetWindowUserPointer(mainWindow, this);

	return 0;
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}


void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_Y)
	{
		theWindow->muevex += 1.0;
	}
	if (key == GLFW_KEY_U)
	{
		theWindow->muevex -= 1.0;
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			// --- Lógica para tecla 'O' (Puerta Izquierda) ---
			if (key == GLFW_KEY_O)
			{
				// Solo activar si la puerta IZQUIERDA no se está animando
				if (!theWindow->animandoPuertaIzq)
				{
					theWindow->puertaIzqAbierta = !theWindow->puertaIzqAbierta; // Invertir estado Izq
					theWindow->animandoPuertaIzq = true; // Iniciar animación Izq
				}
			}

			// --- Lógica para tecla 'P' (Puerta Derecha) ---
			if (key == GLFW_KEY_P)
			{
				// Solo activar si la puerta DERECHA no se está animando
				if (!theWindow->animandoPuertaDer)
				{
					theWindow->puertaDerAbierta = !theWindow->puertaDerAbierta; // Invertir estado Der
					theWindow->animandoPuertaDer = true; // Iniciar animación Der
				}
			}
			// --- Fin de lógica de puertas ---

			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}

// --- Implementación de nuevas funciones ---
bool Window::getPuertaIzqAbierta() { return puertaIzqAbierta; }
bool Window::getPuertaDerAbierta() { return puertaDerAbierta; }
bool Window::getAnimandoPuertaIzq() { return animandoPuertaIzq; }
bool Window::getAnimandoPuertaDer() { return animandoPuertaDer; }
void Window::setAnimandoPuertaIzq(bool animando) { animandoPuertaIzq = animando; }
void Window::setAnimandoPuertaDer(bool animando) { animandoPuertaDer = animando; }


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}