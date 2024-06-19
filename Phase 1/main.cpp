#include <iostream>
#include <math.h>
#include <iomanip>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Model/Model3D.h"
#include "Model/Shader.h"
#include "Model/ModelManager.h"
#include "Camera/MyCamera.h"
#include "Camera/OrthoCamera.h"
#include "Camera/PerspectiveCamera.h"

#include "P6/MyVector.h"
#include "P6/P6Particle.h"
#include "P6/PhysicsWorld.h"
#include "P6/RenderParticle.h"

//openGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//obj loader
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <chrono>
using namespace std::chrono_literals;
constexpr std::chrono::nanoseconds timestep(16ms);

using namespace model;
using namespace camera;

int SCREEN_WIDTH = 700;
int SCREEN_HEIGHT = 700;

float timer = 0.0f;
float converter = 1000000;

PerspectiveCamera* persCamera = new PerspectiveCamera();
OrthoCamera* orthoCamera = new OrthoCamera();


int getRandomNumber(int lowerBound, int upperBound) {
    int offset = lowerBound;
    int range = upperBound - lowerBound + 1;
    int nRet = offset + (rand() % range);
    return nRet;
}


int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PC01 - Andrea Maxene Legaspi", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


    //--------CREATE SHADER--------
    Shader* shader = new Shader();
    GLuint shaderProg = shader->createShader("Shaders/shader.vert", "Shaders/shader.frag");
    glLinkProgram(shaderProg);
    shader->deleteShader();



    //--------ORTHO CAMERA-------
    orthoCamera->setPosition(-SCREEN_WIDTH, SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT);
    glm::mat4 viewMatrix = orthoCamera->giveView();
    glm::mat4 projection = orthoCamera->giveProjection();


    std::list<Model3D*> models;
    P6::PhysicsWorld pWorld = P6::PhysicsWorld();
    ModelManager modelTest = ModelManager();
    std::list<RenderParticle*> RenderParticles;

    GLuint VAO, VBO;

    int numSparks = 0;
    std::cout << "Input spark cout: ";
    std::cin >> numSparks;

    std::cout << numSparks << std::endl << std::endl;
    srand((unsigned)time(NULL));
    for (int i = 0; i < numSparks; i++) {

        //GENERATE RANDOM COLOR
        int color[3];
        for (int j = 0; j < 3; j++)
            color[j] = getRandomNumber(50, 254);

        glm::vec4 colorVec = glm::vec4(color[0] / 254.0f, color[1] / 254.0f, color[2] / 254.0f, 1.0f);

        //GENERATE RADIUS
        int radius = getRandomNumber(2, 10);
        
        //GENERATE LIFESPAN
        int lifespan = getRandomNumber(1, 10);
        

        //INSTANTIATE PARTICLE
        P6Particle* particle = new P6Particle(MyVector(0, 15, 0), MyVector(0, -40, 0), MyVector(-14, 0, 0));

        //LINES 124-151 R TEMPORARY
        if (i == 1) {
            particle->Position = P6::MyVector(0, 600, 0);
            particle->Velocity = P6::MyVector(10, -40, 0);
            particle->Acceleration = P6::MyVector(14.5, -14.5, 0);

        }

        if (i == 2) {
            particle->Position = P6::MyVector(100, 300, 0);
            particle->Velocity = P6::MyVector(100, -50, 0);
            particle->Acceleration = P6::MyVector(14.5, -14.5, 0);

        }

        if (i == 3) {
            particle->Position = P6::MyVector(-50, 100, 0);
            particle->Velocity = P6::MyVector(-10, -50, 0);
            particle->Acceleration = P6::MyVector(14.5, -14.5, 0);

        }

        if (i == 4) {
            particle->Position = P6::MyVector(-400, 400, 0);
            particle->Velocity = P6::MyVector(-10, -50, 0);
            particle->Acceleration = P6::MyVector(14.5, -14.5, 0);

        }


        //INSTANTIATE MODEL
        Model3D* model = new Model3D(glm::vec3(radius * 2, radius * 2, radius * 2), colorVec, shaderProg);
        model->loadModel("3D/sphere.obj", &VBO);
        model->setCameraProperties(projection, viewMatrix);
        modelTest.AddModel(model);


        particle->mass = 1.5f;
        pWorld.AddParticle(particle);

        
        RenderParticle* rp = new RenderParticle(particle, model);
        RenderParticles.push_back(rp);


        std::cout << radius << std::endl;
       // std"
    }
    

    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);


        //FIXED UPDATE
        curr_time = clock::now();       
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds> (curr_time - prev_time);
        prev_time = curr_time;     
        curr_ns += dur; 

        timer += (float)dur.count() / 1000;
      //  std::cout << timer << std::endl;
 
        if (curr_ns >= timestep){
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);

            curr_ns -= curr_ns;

            pWorld.Update((float)ms.count() / 1000);

            modelTest.checkModels();
        }

        
        //--------DRAW MODEL--------
        int test = 0;
        for (std::list<RenderParticle*>::iterator i = RenderParticles.begin();
            i != RenderParticles.end();
            i++
            ) {

            if (test >= numSparks + 1) {
                test = 1;
            }
            else {
                test++;
            }

           // (*i)->debugDraw(test);
                (*i)->draw();
            
        }

        //int num = 0;
        //for (std::list<Model3D*>::iterator i = models.begin();
        //    i != models.end();
        //    i++
        //    ) {

        //    if (num >= numSparks + 1) {
        //        num = 1;
        //       
        //    }
        //    else {
        //        num++;
        //    }
        //  //  std::cout << num << " yuh " << (*i)->getPosition() << std::endl;
        //   // num++;


        //}
       
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}