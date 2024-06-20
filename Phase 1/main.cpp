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

#include "Utility.h"

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
using namespace utility;

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 800;

float timer = 0.0f;
float converter = 1000000;

PerspectiveCamera* persCamera = new PerspectiveCamera();
OrthoCamera* orthoCamera = new OrthoCamera();


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

    MyVector defaultSpawn(0, -SCREEN_HEIGHT+200, 0);
    Utility utility;

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    //--------CREATE SHADER--------
    Shader* shader = new Shader();
    GLuint shaderProg = shader->createShader("Shaders/shader.vert", "Shaders/shader.frag");
    glLinkProgram(shaderProg);
    shader->deleteShader();



    //--------ORTHO CAMERA-------
    orthoCamera->setPosition(-SCREEN_WIDTH, SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT);
   //orthoCamera->setPosition(-500, 500, -500, 500);
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

    int vec[3];
    int lowerBoundVel[3] = { 0, 10, 0 };
    int upperBoundVel[3] = { 0, 500, 0 };
    int lowerBoundAcc[3] = { -10000, 600, -10000 };
    int upperBoundAcc[3] = { 100000, 6000, 100000 };


    glm::vec3 testVec = utility.getRandomVector(lowerBoundVel, upperBoundVel);
    //std::cout << "test: " << testVec.x << " " << testVec.y << " " << testVec.z << std::endl;
    //std::cout << "test: " << testVec[0] << " " << testVec[1] << " " << testVec[2] << std::endl;


    for (int i = 0; i < numSparks; i++) {

        //GENERATE LIFESPAN
        int lifespan = utility.getRandomNumber(1, 10);

        //GENERATE VELOCITY
        glm::vec3 rngVel = utility.getRandomVector(lowerBoundVel, upperBoundVel);
        
        //GENERATE ACCELERATION
        glm::vec3 rngAcc = utility.getRandomVector(lowerBoundAcc, upperBoundAcc);
        

        //INSTANTIATE PARTICLE
        P6Particle* particle = new P6Particle(defaultSpawn, 
                                              MyVector(rngVel.x, rngVel.y, rngVel.z),
                                              MyVector(rngAcc.x, rngAcc.y, rngAcc.z),
                                              lifespan);


        ////LINES 124-151 R TEMPORARY
        /*
        if (i == 0) {
            particle->Position = P6::MyVector(0, -700, 000);
            particle->Velocity = P6::MyVector(0, -50, 0);
            particle->Acceleration = P6::MyVector(100, 10000.0, 0);

        }

        if (i == 2) {
            particle->Position = P6::MyVector(100, 300, -300);
            particle->Velocity = P6::MyVector(100, -50, 0);
            particle->Acceleration = P6::MyVector(14.5, -14.5, 0);

        }

        if (i == 3) {
            particle->Position = P6::MyVector(-50, 100, -150);
            particle->Velocity = P6::MyVector(-10, -50, 0);
            particle->Acceleration = P6::MyVector(14.5, -14.5, 0);

        }

        if (i == 4) {
            particle->Position = P6::MyVector(0, -600, 150);
            particle->Velocity = P6::MyVector(0, 50, 0);
            particle->Acceleration = P6::MyVector(14.5, 14.5, 0);

         }*/

        // GENERATE RANDOM COLOR
;
        for (int j = 0; j < 3; j++)
            vec[j] = utility.getRandomNumber(100, 254);

        glm::vec4 colorVec = glm::vec4(vec[0] / 254.0f, vec[1] / 254.0f, vec[2] / 254.0f, 1.0f);

        //GENERATE RADIUS
        int radius = utility.getRandomNumber(2, 10);
        //INSTANTIATE MODEL
        Model3D* model = new Model3D(glm::vec3(radius * 2, radius * 2, radius * 2), colorVec, shaderProg);
        model->loadModel("3D/sphere.obj", &VBO);
        model->setCameraProperties(projection, viewMatrix);
        modelTest.AddModel(model);


        particle->mass = 5.0f;
        pWorld.AddParticle(particle);

        
        RenderParticle* rp = new RenderParticle(particle, model);
        RenderParticles.push_back(rp);

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
        std::cout << timer << std::endl;
 
        if (curr_ns >= timestep){
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);

            curr_ns -= curr_ns;

            pWorld.Update((float)ms.count() / 1000);

            modelTest.checkModels();
        }

        
        pWorld.CheckLifespan(timer / converter);

        
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