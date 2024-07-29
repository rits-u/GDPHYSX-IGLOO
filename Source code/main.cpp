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

#include "P6/Cable.h"
#include "P6/Renderline.h"

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

/*INPUT DELCARATION*/
bool bStart = false;
float cableLength, particleGap, particleRadius, gravityStrength, forceX, forceY, forceZ;

MyCamera* mainCamera = new OrthoCamera();
PerspectiveCamera* persCamera = new PerspectiveCamera();
OrthoCamera* orthoCamera = new OrthoCamera(-SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_HEIGHT, -SCREEN_HEIGHT);

std::string cameraType = "Ortho";


//Key Input Handler
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //Orthographic
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (cameraType != "Ortho") {
            cameraType = "Ortho";
            mainCamera = new OrthoCamera();
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
            mainCamera = new PerspectiveCamera();
            std::cout << "Shifted to Perspective Camera" << std::endl;
        }
        else {
            std::cout << "Already using Perspective projection" << std::endl;
        }
    }

    //Rotate downwards
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        if (cameraType == "Ortho") {
            orthoCamera->topMost -= 20;
        }
        else {
            persCamera->cameraPos.x -= 30;
        }
        std::cout << "Shifted downwards" << std::endl;
    }

    //Rotate upwards
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        if (cameraType == "Ortho")
            orthoCamera->topMost += 20;
        else
            persCamera->cameraPos.x += 30;

        std::cout << "Shifted upwards" << std::endl;
    }

    //Rotate to the left
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        if (cameraType == "Ortho")
            orthoCamera->rightMost += 15;
        else
            persCamera->cameraPos.y -= 30;

        std::cout << "Shifted to the left" << std::endl;
    }


    //Rotate to the right
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        if (cameraType == "Ortho")
            orthoCamera->rightMost -= 15;
        else
            persCamera->cameraPos.y += 30;

        std::cout << "Shifted to the right" << std::endl;
    }

    //Start
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        if (!bStart) {
            bStart = true;
            std::cout << "SIMULATION STARTED" << std::endl;
        }

    }

}


//----------MAIN FUNCTION-----------
int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "IGLOO", NULL, NULL);
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



    //--------DECLARATION OF NEEDED VARIABLES-----------
    P6::PhysicsWorld pWorld = P6::PhysicsWorld();
    ModelManager modelManager = ModelManager();
    std::list<RenderParticle*> RenderParticles;
    P6::GravityForceGenerator Gravity = P6::GravityForceGenerator(P6::MyVector(0,-9.8,0));

    GLuint VAO, VBO;

    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);


    float timePoint = 0.0f;
    float converter = 1000000;  //used for converting timePoint to seconds

    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);

    /*ASKING USER INPUT */
    std::cout << "Cable Length: ";
    std::cin >> cableLength;

    std::cout << "Particle Gap: ";
    std::cin >> particleGap;

    std::cout << "Particle Radius: ";
    std::cin >> particleRadius;

    std::cout << "GravityStrength: ";
    std::cin >> gravityStrength;

    std::cout << "Apply Force" << std::endl << "x:";
    std::cin >> forceX;
    std::cout << "y:";
    std::cin >> forceY;
    std::cout << "z:";
    std::cin >> forceZ;

    /*PARTICLE DECLARATION FOR ANCHORS*/
    /*These anchor particles will be invisble, to hold the render particles that we see on screen*/
    P6::P6Particle* p1 = new P6::P6Particle(MyVector(0,0,0), MyVector(0,10,0), MyVector(0, 0, 0));
    P6::P6Particle* p2 = new P6::P6Particle(MyVector(30 + particleGap,0, 0), MyVector(0, 10, 0), MyVector(0, 0, 0));
    P6::P6Particle* p3 = new P6::P6Particle(MyVector(-30 + particleGap, 0, 0), MyVector(0, 10, 0), MyVector(0, 0, 0));
    P6::P6Particle* p4 = new P6::P6Particle(MyVector(60 + particleGap, 0, 0), MyVector(0, 10, 0), MyVector(0, 0, 0));
    P6::P6Particle* p5 = new P6::P6Particle(MyVector(-60 + particleGap, 0, 0), MyVector(0, 10, 0), MyVector(0, 0, 0));

    /*These anchor particles will be seen on screen*/
    P6::P6Particle* p6 = new P6::P6Particle(MyVector(30 + particleGap,0,0), MyVector(0,10,0), MyVector(0, 0, 0));
    P6::P6Particle* p7 = new P6::P6Particle(MyVector(0,30 + particleGap, 0), MyVector(0, 10, 0), MyVector(0, 0, 0));
    P6::P6Particle* p8 = new P6::P6Particle(MyVector(-30 + particleGap, 0, 0), MyVector(0, 10, 0), MyVector(0, 0, 0));
    P6::P6Particle* p9 = new P6::P6Particle(MyVector(60 + particleGap, 0, 0), MyVector(0, 10, 0), MyVector(0, 0, 0));
    P6::P6Particle* p10 = new P6::P6Particle(MyVector(-60 + particleGap, 0, 0), MyVector(0, 10, 0), MyVector(0, 0, 0));

    pWorld.AddParticle(p6);
    pWorld.AddParticle(p7);
    pWorld.AddParticle(p8);
    pWorld.AddParticle(p9); 
    pWorld.AddParticle(p10); 

    /*PARITCLE RENDERING*/
    Model3D* m1 = new Model3D(glm::vec3(particleRadius, particleRadius, particleRadius), glm::vec4(1, 0, 0, 0), shaderProg);
    m1->loadModel("3D/sphere.obj", &VBO);
    modelManager.AddModel(m1);

    RenderParticle* rp1 = new RenderParticle(p6, m1);
    RenderParticles.push_back(rp1);
    RenderParticle* rp2 = new RenderParticle(p7, m1);
    RenderParticles.push_back(rp2);
    RenderParticle* rp3 = new RenderParticle(p8, m1);
    RenderParticles.push_back(rp3);
    RenderParticle* rp4 = new RenderParticle(p9, m1);
    RenderParticles.push_back(rp4);
    RenderParticle* rp5 = new RenderParticle(p10, m1);
    RenderParticles.push_back(rp5);

    // The cables hold on to the invisible spheres
    // Cable* cable = new Cable(cableLength);
    // pWorld.forceRegistry.Add(p1,cable);
    // pWorld.forceRegistry.Add(p2,cable);
    // pWorld.forceRegistry.Add(p3,cable);
    // pWorld.forceRegistry.Add(p4,cable);
    // pWorld.forceRegistry.Add(p5,cable);

    P6::Rod* r1 = new P6::Rod();
    r1->particles[0] = p1;
    r1->particles[1] = p6;
    r1->length = 100;

    P6::Rod* r2 = new P6::Rod();
    r2->particles[0] = p2;
    r2->particles[1] = p7;
    r2->length = 100;
    pWorld.Links.push_back(r2);

    P6::Rod* r3 = new P6::Rod();
    r3->particles[0] = p3;
    r3->particles[1] = p8;
    r3->length = 100;
    pWorld.Links.push_back(r3);

    P6::Rod* r4 = new P6::Rod();
    r4->particles[0] = p4;
    r4->particles[1] = p9;
    r4->length = 100;
    pWorld.Links.push_back(r4);

    P6::Rod* r5 = new P6::Rod();
    r5->particles[0] = p5;
    r5->particles[1] = p10;
    r5->length = 100;
    pWorld.Links.push_back(r5);
    
    // p10->AddForce(P6::MyVector(0,6000,0));

    //Renderline* renderl = new Renderline(MyVector(0, p2->Position.x, 0), MyVector(0, cableLength, 0), shaderProg);

    srand((unsigned)time(NULL));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        if (bStart)
        {
        //FIXED UPDATE
        curr_time = clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds> (curr_time - prev_time);
        prev_time = curr_time;

        unsigned int viewLoc = glGetUniformLocation(shaderProg, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mainCamera->getView()));

        unsigned int projectionLoc = glGetUniformLocation(shaderProg, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(mainCamera->giveProjection()));

            curr_ns += dur;
            timePoint += (float)dur.count() / 1000;

            if (curr_ns >= timestep) {
                auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);

                curr_ns -= curr_ns;

                pWorld.Update((float)ms.count() / 1000);

                m1->setCameraProperties(mainCamera->giveProjection(), mainCamera->getView());
               //renderl->Update(MyVector(p2->Position.x, 0, 0), MyVector(0, cableLength, 0), mainCamera->giveProjection());
            }

            //--------DRAW MODEL-------
            for (std::list<RenderParticle*>::iterator i = RenderParticles.begin();
                i != RenderParticles.end();
                i++
                ) {

                (*i)->draw();
            }
        }

        //Key Callback
        glfwSetKeyCallback(window, key_callback);
        glClear(GL_COLOR_BUFFER_BIT);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}