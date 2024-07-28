/*
date modified: 02-07-2024 
caught up and updated
*/

#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define TINYOBJLOADER_IMPLEMENTATION
//#include "tiny_obj_loader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Model/Model3D.h"
#include "Model/Shader.h"
#include "Model/Camera.h"

#include "P6/MyVector.h"
#include "P6/P6Particle.h"
#include "P6/PhysicsWorld.h"
#include "P6/RenderParticle.h"
#include "P6/ParticleContact.h"

#include "P6/Springs/AnchoredSpring.h"
#include "P6/Springs/ParticleSpring.h"

#include "P6/Links//Rod.h"


#include "Utility/RenderLine.h"

#include <chrono>
using namespace std::chrono_literals;
constexpr std::chrono::nanoseconds timestep(16ms);


using namespace model;
using namespace P6;
using namespace utility;


float width = 800.0f;
float height = 800.0f;

float rotate = 0.0f;


std::string cameraType = "Ortho";


void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (cameraType != "Ortho") {
            cameraType = "Ortho";
            std::cout << "Shifted to Ortho Camera" << std::endl;

        }
        else {
            std::cout << "Already using ortho projection" << std::endl;
        }
    }

    //Perspective
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (cameraType != "Perspective") {
            cameraType = "Perspective";
            std::cout << "Shifted to Perspective Camera" << std::endl;
        }
        else {
            std::cout << "Already using Perspective projection" << std::endl;
        }
    }
        //Rotate to the left
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        rotate -= 0.05f;
        std::cout << "Shifted to the left" << std::endl;
    }


    //Rotate to the right
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        rotate += 0.05f;
        std::cout << "Shifted to the right" << std::endl;
    
    }
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Andrea Maxene Legaspi", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    glViewport(0, 0,width,height);

    glfwSetKeyCallback(window, Key_Callback);


    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);


    //--------CREATE SHADER--------
    Shader* shader = new Shader();
    GLuint shaderProg = shader->createShader("Shaders/shader.vert", "Shaders/shader.frag");
    glLinkProgram(shaderProg);
    shader->deleteShader();

    Camera* camera = new Camera();
    P6::PhysicsWorld pWorld = P6::PhysicsWorld();
    std::list<RenderParticle*> RenderParticles;

    GLuint VBO;
    //if ortho cam = set scale by multiplier
    //else 


  //  Model3D* ewan = new Model3D();
  ////  ewan->scale = (MyVector(20, 20, 20));
  //  ewan->setScale(MyVector(20, 20, 20));
  //  ewan->position = MyVector(100, 0, 0);
  //  ewan->loadModel("3D/sphere.obj", &VBO);
  //  ewan->shaderProg = shaderProg;

  //  Model3D* huhu = new Model3D();
  //  huhu->scale = MyVector(10.0f * 30, 10.0f * 30, 10.0f * 30);
  //  huhu->loadModel("3D/sphere.obj", &VBO);
  //  huhu->position = MyVector(-200, -1, 0);
  //  huhu->shaderProg = shaderProg;




    //TEST
    P6Particle* p1 = new P6Particle();
    p1->Position = MyVector(100, 0, 0);
    p1->mass = 10;
    p1->radius = 20;
    pWorld.AddParticle(p1);

    glm::vec4 colorVec = glm::vec4(0 / 254.0f, 255 / 254.0f, 240 / 254.0f, 1.0f);  //cyan

    Model3D* m1 = new Model3D(MyVector(10.0f * 30, 10.0f * 30, 10.0f * 30), colorVec, shaderProg);
    m1->loadModel("3D/sphere.obj", &VBO);

    RenderParticle* rp1 = new RenderParticle(p1, m1);
    rp1->Scale = MyVector(p1->radius, p1->radius, p1->radius);
    RenderParticles.push_back(rp1);



    P6Particle* p2 = new P6Particle();
    p2->Position = MyVector(-100, -200, 0);
    p2->mass = 10;
    p2->radius = 20;
    pWorld.AddParticle(p2);

    colorVec = glm::vec4(254 / 254.0f, 0 / 254.0f, 0 / 254.0f, 1.0f);  //cyan

    Model3D* m2 = new Model3D(MyVector(10.0f * 20, 10.0f * 20, 10.0f * 20), colorVec, shaderProg);
    m2->loadModel("3D/sphere.obj", &VBO);

    RenderParticle* rp2 = new RenderParticle(p2, m2);
    rp2->Scale = MyVector(p2->radius, p2->radius, p2->radius);
    RenderParticles.push_back(rp2);

    Rod* r = new Rod();
    r->particles[0] = p1;
    r->particles[1] = p2;
    r->length = 200;
    
    pWorld.Links.push_back(r);

    RenderLine* line = new RenderLine(p1->Position, p2->Position, MyVector(1, 1, 1));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        curr_time = clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds> (curr_time - prev_time);
        prev_time = curr_time;

        curr_ns += dur;
      ////  timePoint += (float)dur.count() / 1000;

        if (curr_ns >= timestep) {
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);

            curr_ns -= curr_ns;

            pWorld.Update((float)ms.count() / 1000);

        }



        glm::mat4 projection = camera->getProjection(cameraType, width, height);
        glm::mat4 view = camera->getView(cameraType, rotate);
        camera->bindCamera(cameraType, width, height, rotate, shaderProg);


   /*      ewan->drawModel();
       huhu->drawModel();*/

   
        for (std::list<RenderParticle*>::iterator i = RenderParticles.begin();
            i != RenderParticles.end();
            i++
            ) {

            (*i)->draw(cameraType);
        }

      //  m1->drawModel();

        line->Update(p1->Position, p2->Position, projection);
        line->Draw();
     
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}