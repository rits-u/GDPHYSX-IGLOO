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

bool bPaused = false;

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
        if(cameraType == "Ortho") 
            orthoCamera->topMost += 20;
        else 
            persCamera->cameraPos.x += 30;
        
        std::cout << "Shifted upwards" << std::endl;
    }

    //Rotate to the left
    else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
    {
        if(cameraType == "Ortho")
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

    //Pause/Play the game
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        if (!bPaused) {
            bPaused = true;
            std::cout << "PAUSED" << std::endl;
        }
        else {
            bPaused = false;
            std::cout << "RESUMED" << std::endl;
        }
        
    }
 
}


//----------MAIN FUNCTION-----------
int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "hello", NULL, NULL);
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

    GLuint VAO, VBO;

    int numSparks = 0;
    int spawned = 0;
    bool spawn_done = false;

    int lowerBoundVel[3] = { -200, 10, -200 };
    int upperBoundVel[3] = { 200, 500, 200 };
    int lowerBoundAcc[3] = { -100, 600, -100 };
    int upperBoundAcc[3] = { 100, 6000, 100 };
    int lowerBoundCol[3] = { 50, 50, 50 };
    int upperBoundCol[3] = { 254, 254, 254 };

    MyVector defaultSpawn(0, -SCREEN_HEIGHT + 150, 0);
    Utility utility;

    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);


    float timePoint = 0.0f;
    float converter = 1000000;  //used for converting timePoint to seconds

    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);

    //asks user for the number of sparks to spawn
    std::cout << "Input spark count: ";
    std::cin >> numSparks;

    srand((unsigned)time(NULL));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        //Key Callback
        glfwSetKeyCallback(window, key_callback);

        glClear(GL_COLOR_BUFFER_BIT);


        //FIXED UPDATE
        curr_time = clock::now();       
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds> (curr_time - prev_time);
        prev_time = curr_time;     
       
        
        //std::cout << time << std::endl;


        //--------CAMERA-------
        if (cameraType == "Perspective") {
            projection = persCamera->giveProjection(SCREEN_WIDTH, SCREEN_HEIGHT);
            viewMatrix = persCamera->giveView(1);
        }
        else {
          //  orthoCamera->setPosition(-SCREEN_WIDTH, SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT);
            viewMatrix = orthoCamera->giveView();
            projection = orthoCamera->giveProjection();
            
        }


        if (!bPaused)
        {
            curr_ns += dur;
            timePoint += (float)dur.count() / 1000;

            if (curr_ns >= timestep){
                auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);

                curr_ns -= curr_ns;

                pWorld.Update((float)ms.count() / 1000);

                // keep spawning a particle if the number of spawned particles has 
                // not reached the requested amount of sparks yet
                if (spawned < numSparks) {

                    //GENERATE RANDOM LIFESPAN
                    int lifespan = utility.getRandomNumber(1, 10);

                    //GENERATE RANDOM VELOCITY
                    glm::vec3 rngVel = utility.getRandomVector(lowerBoundVel, upperBoundVel);

                    //GENERATE RANDOM ACCELERATION
                    glm::vec3 rngAcc = utility.getRandomVector(lowerBoundAcc, upperBoundAcc);

                    //INSTANTIATE PARTICLE
                    P6Particle* particle = new P6Particle(defaultSpawn,
                            MyVector(rngVel.x, rngVel.y, rngVel.z),
                            MyVector(rngAcc.x, rngAcc.y, rngAcc.z),
                            lifespan,
                            timePoint / converter);
                    pWorld.AddParticle(particle);

                    //GENERATE RANDOM COLOR
                    glm::vec3 rngColor = utility.getRandomVector(lowerBoundCol, upperBoundCol);
                    glm::vec4 colorVec = glm::vec4(rngColor.x / 254.0f, rngColor.y / 254.0f, rngColor.z / 254.0f, 1.0f);

                    //GENERATE RANDOM RADIUS
                    int radius = utility.getRandomNumber(2, 10);

                    //INSTANTIATE MODEL
                    Model3D* model = new Model3D(glm::vec3(radius * 2, radius * 2, radius * 2), colorVec, shaderProg);
                    model->loadModel("3D/sphere.obj", &VBO);
                    model->setCameraProperties(projection, viewMatrix);
                    modelManager.AddModel(model);

                    //INSTANTIATE RENDER_PARTICLE
                    RenderParticle* rp = new RenderParticle(particle, model);
                    RenderParticles.push_back(rp);

                    spawned += 1;
                    if (spawned >= numSparks && !spawn_done) {
                        spawn_done = true;
                        std::cout << "SPAWNED: " << spawned << std::endl;
                    }
                }
            }
        
            pWorld.CheckLifespan(timePoint / converter);

        }
        

        //--------DRAW MODEL--------
        int test = 0;
        for (std::list<RenderParticle*>::iterator i = RenderParticles.begin();
            i != RenderParticles.end();
            i++
            ) {

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