//práctica 3: Modelado Geométrico y Cámara Sintética.
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/random.hpp>
//clases
#include "Mesh.h"
#include "Shader.h"
#include "Sphere.h"
#include "Window.h"
#include "Camera.h"

using std::vector;

//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
const float PI = 3.14159265f;
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;
Camera camera;
Window mainWindow;
vector<Mesh*> meshList;
vector<MeshColor*> meshColorList;
vector<Shader> shaderList;

//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";

// Pirámide triangular regular
void CrearPiramideTriangular() {
    unsigned int indices[] = {
        0,1,2,
        1,3,2,
        3,0,2,
        1,0,3
    };
    GLfloat vertices[] = {
        -0.5f, 0.0f, 0.0f,
         0.5f, 0.0f, 0.0f,
         0.0f, 0.0f, -0.86f,
         0.0f, 0.86f, -0.43f,
    };
    Mesh* obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);
}

void CrearPiramideColores() {
    GLfloat vertices[] = {
        // Cara 1 - rojo
        -0.5f, 0.0f, 0.0f, 1,0,0,
         0.5f, 0.0f, 0.0f, 1,0,0,
         0.0f, 0.0f, -0.86f, 1,0,0,
         // Cara 2 - azul
         -0.5f, 0.0f, 0.0f, 0,0,1,
          0.5f, 0.0f, 0.0f, 0,0,1,
          0.0f, 0.86f, -0.43f, 0,0,1,
          // Cara 3 - amarillo
          -0.5f, 0.0f, 0.0f, 1,1,0,
           0.0f, 0.86f, -0.43f, 1,1,0,
           0.0f, 0.0f, -0.86f, 1,1,0,
           // Cara 4 - verde
            0.5f, 0.0f, 0.0f, 0,1,0,
            0.0f, 0.0f, -0.86f, 0,1,0,
            0.0f, 0.86f, -0.43f, 0,1,0,
    };
    MeshColor* piramideColor = new MeshColor();
    piramideColor->CreateMeshColor(vertices, 72);
    meshColorList.push_back(piramideColor);
}

void CreateShaders() {
    Shader* shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);

    Shader* shader2 = new Shader();
    shader2->CreateFromFiles(vShaderColor, fShader);
    shaderList.push_back(*shader2);
}

// Función para renderizar pirámides con transformaciones personalizadas
void RenderPiramide(GLuint uniformModel, const glm::vec3& traslacionExtra,
    const std::vector<std::pair<float, glm::vec3>>& rotacionesExtra = {},
    const glm::vec3& escalaExtra = glm::vec3(0.9f)) {
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
    model = glm::scale(model, glm::vec3(0.33f));
    model = glm::rotate(model, glm::radians(mainWindow.getrotax()), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(mainWindow.getrotay()), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(mainWindow.getrotaz()), glm::vec3(0, 0, 1));

    for (auto& rot : rotacionesExtra)
        model = glm::rotate(model, glm::radians(rot.first), rot.second);

    model = glm::translate(model, traslacionExtra);
    model = glm::scale(model, escalaExtra);

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    meshColorList[0]->RenderMeshColor();
}

int main() {
    mainWindow = Window(800, 800);
    mainWindow.Initialise();
    CrearPiramideTriangular();
    CreateShaders();
    CrearPiramideColores();

    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
        -60.0f, 0.0f, 0.3f, 0.3f);

    GLuint uniformProjection = 0;
    GLuint uniformModel = 0;
    GLuint uniformView = 0;
    GLuint uniformColor = 0;
    glm::mat4 projection = glm::perspective(glm::radians(60.0f),
        mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

    glm::vec3 color = glm::vec3(0.0f);

    while (!mainWindow.getShouldClose()) {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        deltaTime += (now - lastTime) / limitFPS;
        lastTime = now;

        glfwPollEvents();
        camera.keyControl(mainWindow.getsKeys(), deltaTime);
        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[1].useShader();
        uniformModel = shaderList[1].getModelLocation();
        uniformProjection = shaderList[1].getProjectLocation();
        uniformView = shaderList[1].getViewLocation();

        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

        // Colocación de las 22 pirámides
        RenderPiramide(uniformModel, glm::vec3(0.0f, 0.0f, 0.0f)); // P01
        RenderPiramide(uniformModel, glm::vec3(1.02f, 0.0f, 0.0f)); // P02
        RenderPiramide(uniformModel, glm::vec3(-1.02f, 0.0f, 0.0f)); // P03
        RenderPiramide(uniformModel, glm::vec3(0.0f, 0.0f, -1.75f)); // P04
        RenderPiramide(uniformModel, glm::vec3(0.0f, 1.75f, -0.875f)); // P05
        RenderPiramide(uniformModel, glm::vec3(-0.51f, 0.0f, -0.875f)); // P06
        RenderPiramide(uniformModel, glm::vec3(-0.51f, 0.875f, -0.4375f)); // P07
        RenderPiramide(uniformModel, glm::vec3(0.51f, 0.875f, -0.4375f)); // P08
        RenderPiramide(uniformModel, glm::vec3(0.51f, 0.0f, -0.875f)); // P09
        RenderPiramide(uniformModel, glm::vec3(0.0f, 0.875f, -1.3125f)); // P10

        RenderPiramide(uniformModel, glm::vec3(0.51f, 0.86f, -0.429f), { {180, {0,0,1}}, {53.1f, {1,0,0}} }); // P11
        RenderPiramide(uniformModel, glm::vec3(-0.51f, 0.86f, -0.429f), { {180, {0,0,1}}, {53.1f, {1,0,0}} }); // P12
        RenderPiramide(uniformModel, glm::vec3(0.0f, 1.72f/2, 0.429f), { {180, {0,0,1}}, {53.1f, {1,0,0}} }); // P13

        RenderPiramide(uniformModel, glm::vec3(-1.124f, -0.25f, 0.06f), { {180, {0,0,1}}, {-120,{0,1,0}}, {28.2f, {-0.5f,0,0.86f}} }); // P14
        RenderPiramide(uniformModel, glm::vec3(-1.63f, -0.25f, 0.95f), { {180, {0,0,1}}, {-120,{0,1,0}}, {28.2f, {-0.5f,0,0.86f}} }); // P15
        RenderPiramide(uniformModel, glm::vec3(-1.63f, -1.11f, 0.505f), { {180, {0,0,1}}, {-120,{0,1,0}}, {28.2f, {-0.5f,0,0.86f}} }); // P16

        RenderPiramide(uniformModel, glm::vec3(1.124f, -0.25f, 0.06f), { {180, {0,0,1}}, {120,{0,1,0}}, {28.2f, {-0.5f,0,-0.86f}} }); // P17
        RenderPiramide(uniformModel, glm::vec3(1.63f, -0.25f, 0.93f), { {180, {0,0,1}}, {120,{0,1,0}}, {28.2f, {-0.5f,0,-0.86f}} }); // P18
        RenderPiramide(uniformModel, glm::vec3(1.63f, -1.11f, 0.505f), { {180, {0,0,1}}, {120,{0,1,0}}, {28.2f, {-0.5f,0,-0.86f}} }); // P19

        RenderPiramide(uniformModel, glm::vec3(0.51f, 0.0f, 0.87f), { {180, {0,1,0}} }); // P20
        RenderPiramide(uniformModel, glm::vec3(-0.51f, 0.0f, 0.87f), { {180, {0,1,0}} }); // P21
        RenderPiramide(uniformModel, glm::vec3(0.0f, 0.0f, 1.74f), { {180, {0,1,0}} }); // P22

        // Pirámide base
        glm::mat4 model(1.0);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
        model = glm::rotate(model, glm::radians(mainWindow.getrotax()), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(mainWindow.getrotay()), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(mainWindow.getrotaz()), glm::vec3(0, 0, 1));
        model = glm::scale(model, glm::vec3(0.95f));
        model = glm::translate(model, glm::vec3(0.0f, 0.01f, -0.01f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        color = glm::vec3(0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        meshList[0]->RenderMesh();

        glUseProgram(0);
        mainWindow.swapBuffers();
    }
    return 0;
}
