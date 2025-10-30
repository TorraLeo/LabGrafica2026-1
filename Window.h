#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);
	}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }

	// --- FUNCIONES MODIFICADAS/NUEVAS ---
	bool getPuertaIzqAbierta();
	bool getPuertaDerAbierta();
	bool getAnimandoPuertaIzq();
	bool getAnimandoPuertaDer();
	void setAnimandoPuertaIzq(bool animando);
	void setAnimandoPuertaDer(bool animando);
	// --- FIN DE MODIFICACIONES ---

	~Window();

private:
	GLFWwindow* mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	bool mouseFirstMoved;

	// --- VARIABLES MODIFICADAS/NUEVAS ---
	bool puertaIzqAbierta;     // Reemplaza a puertasAbiertas
	bool puertaDerAbierta;     // Nueva
	bool animandoPuertaIzq;    // Reemplaza a animandoPuertas
	bool animandoPuertaDer;    // Nueva
	// --- FIN DE MODIFICACIONES ---

	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};