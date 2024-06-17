#include <iostream>
#include <math.h>
#include <iomanip>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Model/Model3D.h"
#include "Model/Shader.h"
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

    std::list<Model3D*> models;

   
    P6::PhysicsWorld pWorld = P6::PhysicsWorld();

    P6::P6Particle p1 = P6::P6Particle();
    p1.Position = P6::MyVector(0, 0, 0);
    p1.Velocity = P6::MyVector(0, -40, 0);   
     //  p1.Acceleration = P6::MyVector(14.5, -14.5, -14.5);
      // p1.damping = 1.0f;
    p1.lifespan = 10;
   // p1.lifespan = std::chrono::seconds(10);
    p1.mass = 0.5; // 1KG
    p1.AddForce(P6::MyVector(60, 0, 0));  //around 6000,0,0 kg m/s^2
    pWorld.AddParticle(&p1);

    P6::P6Particle p2 = P6::P6Particle();
    p2.Position = P6::MyVector(20, 0, 0);
    p2.Velocity = P6::MyVector(80, -80, -80);   
     //  p1.Acceleration = P6::MyVector(14.5, -14.5, -14.5);
      // p1.damping = 1.0f;
    p2.lifespan = 5;
    // p1.lifespan = std::chrono::seconds(10);
    p2.mass = 10.0; // 1KG
    p2.AddForce(P6::MyVector(6000, 0, 0));  //around 6000,0,0 kg m/s^2
    pWorld.AddParticle(&p2);


    //--------ORTHO CAMERA-------
    orthoCamera->setPosition(-SCREEN_WIDTH, SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT);
    glm::mat4 viewMatrix = orthoCamera->giveView();
    glm::mat4 projection = orthoCamera->giveProjection();


    //--------CREATE SHADER--------
    Shader* shader = new Shader();
    GLuint shaderProg = shader->createShader("Shaders/shader.vert", "Shaders/shader.frag");
    glLinkProgram(shaderProg);
    shader->deleteShader();



    Model3D* sphere1 = new Model3D(p1.Position,
                                   glm::vec3(15, 15, 15),
                                   glm::vec4(254 / 254.0f, 0.0f / 254.0f, 0.0f / 254.0f, 1.0f),
                                   shaderProg);
    models.push_back(sphere1);

    Model3D* sphere2 = new Model3D(p2.Position,
                                glm::vec3(20, 20, 20),
                                glm::vec4(52.0f / 254.0f, 235.0f / 254.0f, 70.0f / 254.0f, 1.0f),
                                shaderProg);
    models.push_back(sphere2);


    //--------SPHERE MODEL--------
    tinyobj::attrib_t attributes;
    GLuint VAO, VBO;

    for (std::list<Model3D*>::iterator i = models.begin();
        i != models.end();
        i++
        ) {

        (*i)->loadModel_("3D/sphere.obj", &attributes, &VBO);
        (*i)->setCameraProperties(projection, viewMatrix);
    }


    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);

    
    std::list<RenderParticle*> RenderParticles;

    RenderParticle rp1 = RenderParticle(&p1, sphere1);
    RenderParticles.push_back(&rp1);

    RenderParticle rp2 = RenderParticle(&p2, sphere2);
    RenderParticles.push_back(&rp2);


    //timer
    auto test_timer = std::chrono::steady_clock::now();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);


        //FIXED UPDATE
        curr_time = clock::now();       

        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds> (curr_time - prev_time);

        timer += (float)dur.count() / 1000;


        prev_time = curr_time;     

        curr_ns += dur; 

      //  std::cout << timer << std::endl;
 
        if (curr_ns >= timestep){
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);

            curr_ns -= curr_ns;

            pWorld.Update((float)ms.count() / 1000);


        }

        auto now = clock::now();

        
        //--------DRAW MODEL--------
        glUseProgram(shaderProg);

        
        //temporary
        if (p1.lifespan <= timer / converter) {
            p1.Destroy();
        }

        if (p2.lifespan <= timer / converter) {
            p2.Destroy();
        }


        for (std::list<RenderParticle*>::iterator i = RenderParticles.begin();
            i != RenderParticles.end();
            i++
            ) {

         //   if(pWorld[i])
            (*i)->draw();
        }
       
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

