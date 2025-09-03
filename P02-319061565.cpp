//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá
static const char* vShaderVerde = "shaders/shaderVerde.vert"; 
static const char* vShaderAzul = "shaders/shaderAzul.vert";
static const char* vShaderVerdeOscuro = "shaders/shaderVerdeOscuro.vert";
static const char* vShaderCafe = "shaders/shaderCafe.vert";

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

void CreaPino()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-1.0f,	 -0.6f,	 0.5f,	//0
		-0.6f,	 -0.6f,	 0.5f,	//1
		-0.8f,	 -0.1f,	-0.75f,	//2
		-0.8f,	 -0.6f,	-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

void CreaTecho()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.7f,	 0.3f,	 0.5f,	//0
		 0.7f,	 0.3f,	 0.5f,	//1
		 0.0f,	 0.9f,	-0.75f,	//2
		 0.0f,	 0.3f,	-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

void CreaTronco()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.1f,	-0.1f,  0.5f,
		 0.1f,	-0.1f,  0.5f,
		 0.1f,	 0.1f,	0.5f,
		-0.1f,   0.1f,	0.5f,
		// back
		-0.1f,	-0.1f,  -0.5f,
		 0.1f,	-0.1f,  -0.5f,
		 0.1f,	 0.1f,	-0.5f,
		-0.1f,   0.1f,	-0.5f,
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CreaVentanaPuerta()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.2f,	-0.2f,  0.5f,
		 0.2f,	-0.2f,  0.5f,
		 0.2f,	 0.2f,	0.5f,
		-0.2f,   0.2f,	0.5f,
		// back
		-0.2f,	-0.2f,  -0.5f,
		 0.2f,	-0.2f,  -0.5f,
		 0.2f,	 0.2f,	-0.5f,
		-0.2f,   0.2f,	-0.5f,
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CreaFachada()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f,	-0.8f,  0.5f,
	 0.5f,	-0.8f,  0.5f,
	 0.5f,	 0.3f,	0.5f,
	-0.5f,   0.3f,	0.5f,
	// back
	-0.5f,	-0.8f,  -0.5f,
	 0.5f,	-0.8f,  -0.5f,
	 0.5f,	 0.3f,	-0.5f,
	-0.5f,   0.3f,	-0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat letraD[] = {	
			//X			Y			Z			R		G		B
			-0.8f,	0.5f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.7f,	0.5f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.7f,	-0.3f,		0.5f,			0.3f,	0.5f,	1.0f,
			
			-0.8f,	-0.4f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.8f,	0.5f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.7f,	-0.3f,		0.5f,			0.3f,	0.5f,	1.0f,

			-0.7f,	0.5f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.7f,	0.4f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.5f,	0.4f,		0.5f,			0.3f,	0.5f,	1.0f,

			-0.7f,	0.5f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.5f,	0.5f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.5f,	0.4f,		0.5f,			0.3f,	0.5f,	1.0f,

			-0.5f,	0.5f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.4f,	0.3f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.5f,	0.4f,		0.5f,			0.3f,	0.5f,	1.0f,

			-0.5f,	0.5f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.4f,	0.3f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.3f,	0.3f,		0.5f,			0.3f,	0.5f,	1.0f,

			-0.4f,	0.3f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.4f,	-0.2f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.3f,	0.3f,		0.5f,			0.3f,	0.5f,	1.0f,

			-0.3f,	0.3f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.3f,	-0.2f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.4f,	-0.2f,		0.5f,			0.3f,	0.5f,	1.0f,

			-0.8f,	-0.4f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.7f,	-0.3f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.5f,	-0.3f,		0.5f,			0.3f,	0.5f,	1.0f,

			-0.8f,	-0.4f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.5f,	-0.3f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.5f,	-0.4f,		0.5f,			0.3f,	0.5f,	1.0f,

			-0.5f,	-0.4f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.5f,	-0.3f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.4f,	-0.2f,		0.5f,			0.3f,	0.5f,	1.0f,

			-0.5f,	-0.4f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.4f,	-0.2f,		0.5f,			0.3f,	0.5f,	1.0f,
			-0.3f,	-0.2f,		0.5f,			0.3f,	0.5f,	1.0f,
			
	};
	MeshColor *letraDe = new MeshColor();
	letraDe->CreateMeshColor(letraD,216);
	meshColorList.push_back(letraDe); // item 0

	GLfloat letraL[] = {
		-0.2f,  0.5f,  0.5f,   0.251f,  0.878f,  0.816f,
		-0.2f, -0.4f,  0.5f,   0.251f,  0.878f,  0.816f,
		-0.1f,  0.5f,  0.5f,   0.251f,  0.878f,  0.816f,

		-0.1f,  0.5f,  0.5f,   0.251f,  0.878f,  0.816f,
		-0.2f, -0.4f,  0.5f,   0.251f,  0.878f,  0.816f,
		-0.1f, -0.3f,  0.5f,   0.251f,  0.878f,  0.816f,

		-0.2f, -0.4f,  0.5f,   0.251f,  0.878f,  0.816f,
		-0.1f, -0.3f,  0.5f,   0.251f,  0.878f,  0.816f,
		0.3f, -0.4f,  0.5f,   0.251f,  0.878f,  0.816f,

		-0.1f, -0.3f,  0.5f,   0.251f,  0.878f,  0.816f,
		0.3f, -0.3f,  0.5f,   0.251f,  0.878f,  0.816f,
		0.3f, -0.4f,  0.5f,   0.251f,  0.878f,  0.816f,

	};
	MeshColor* letraele = new MeshColor();
	letraele->CreateMeshColor(letraL, 72);
	meshColorList.push_back(letraele); // item 2

	GLfloat letraA[] = {
		 0.4f, -0.4f, 0.5f,   0.553f, 0.714f, 0.000f,
		 0.6f,  0.5f, 0.5f,   0.553f, 0.714f, 0.000f,
		 0.6f,  0.0f, 0.5f,   0.553f, 0.714f, 0.000f,

		 0.4f, -0.4f, 0.5f,   0.553f, 0.714f, 0.000f,
		 0.5f, -0.4f, 0.5f,   0.553f, 0.714f, 0.000f,
		 0.6f,  0.0f, 0.5f,   0.553f, 0.714f, 0.000f,

		 0.6f,  0.5f, 0.5f,   0.553f, 0.714f, 0.000f,
		 0.6f,  0.1f, 0.5f,   0.553f, 0.714f, 0.000f,
		 0.7f,  0.5f, 0.5f,   0.553f, 0.714f, 0.000f,

		 0.6f,  0.5f, 0.5f,   0.553f, 0.714f, 0.000f,
		 0.7f,  0.5f, 0.5f,   0.553f, 0.714f, 0.000f,
		 0.7f,  0.1f, 0.5f,   0.553f, 0.714f, 0.000f,

		 0.7f,  0.5f, 0.5f,   0.553f, 0.714f, 0.000f,
		 0.7f,  0.0f, 0.5f,   0.553f, 0.714f, 0.000f,
		 0.9f, -0.4f, 0.5f,   0.553f, 0.714f, 0.000f,

		 0.7f,  0.0f, 0.5f,   0.553f, 0.714f, 0.000f,
		 0.8f, -0.4f, 0.5f,   0.553f, 0.714f, 0.000f,
		 0.9f, -0.4f, 0.5f,   0.553f, 0.714f, 0.000f,

		 0.6f,  0.1f, 0.5f,   0.553f, 0.714f, 0.000f,
		 0.7f,  0.1f, 0.5f,   0.553f, 0.714f, 0.000f,
		 0.7f,  0.0f, 0.5f,   0.553f, 0.714f, 0.000f,

		 0.6f,  0.1f, 0.5f,   0.553f, 0.714f, 0.000f,
		 0.6f,  0.0f, 0.5f,   0.553f, 0.714f, 0.000f,
		 0.7f,  0.0f, 0.5f,   0.553f, 0.714f, 0.000f,

	};
	MeshColor* letraabuinter = new MeshColor();
	letraabuinter->CreateMeshColor(letraA, 144);
	meshColorList.push_back(letraabuinter); // item 2

}

void CreateShaders()
{

	Shader *shader1 = new Shader(); //FACHADA
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();// letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader();// VENTANA 
	shader3->CreateFromFiles(vShaderVerde, fShader);
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader();// TECHO 
	shader4->CreateFromFiles(vShaderAzul, fShader);
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader();// PINOS 
	shader5->CreateFromFiles(vShaderVerdeOscuro, fShader);
	shaderList.push_back(*shader5);

	Shader* shader6 = new Shader();// TRONCO 
	shader6->CreateFromFiles(vShaderCafe, fShader);
	shaderList.push_back(*shader6);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaTecho(); //índice 0 en MeshList
	CreaFachada();//índice 1 en MeshList
	CreaPino(); // INDICE 2
	CreaTronco(); // INDICE 3
	CreaVentanaPuerta(); // INDICE 4
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
													
		// /*
		//	-------------------------LETRAS-------------------------
		//*/
		//// D
		//shaderList[1].useShader();
		//uniformModel = shaderList[1].getModelLocation();
		//uniformProjection = shaderList[1].getProjectLocation();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[0]->RenderMeshColor();

		//// L
		//shaderList[1].useShader();
		//uniformModel = shaderList[1].getModelLocation();
		//uniformProjection = shaderList[1].getProjectLocation();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[1]->RenderMeshColor();

		//// A
		//shaderList[1].useShader();
		//uniformModel = shaderList[1].getModelLocation();
		//uniformProjection = shaderList[1].getProjectLocation();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[2]->RenderMeshColor();

		/*
			--------------------------------------------CASITA----------------------------------------------------
		*/
		// TECHO
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		// FACHADA
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		// PINO IZQUIERDO
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[2]->RenderMesh();

		// PINO DERECHO
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.55f, 0.0f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[2]->RenderMesh();

		// TRONCO IZQUIERDO
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.8f, -0.7f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[3]->RenderMesh();

		// TRONCO DERECHO
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.7f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[3]->RenderMesh();

		// VENTANA DERECHA
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.25f, 0.0f, -1.9f));
		model = glm::scale(model, glm::vec3(0.8f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[4]->RenderMesh();

		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.25f, 0.0f, -1.9f));
		model = glm::scale(model, glm::vec3(0.8f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[4]->RenderMesh();

		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.01;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.6f, -1.9f));
		model = glm::scale(model, glm::vec3(0.8f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[4]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}