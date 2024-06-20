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


    PerspectiveCamera* persCamera = new PerspectiveCamera();
    OrthoCamera* orthoCamera = new OrthoCamera();


    //--------ORTHO CAMERA-------
    orthoCamera->setPosition(-SCREEN_WIDTH, SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT);
    glm::mat4 viewMatrix = orthoCamera->giveView();
    glm::mat4 projection = orthoCamera->giveProjection();



    P6::PhysicsWorld pWorld = P6::PhysicsWorld();
    ModelManager modelManager = ModelManager();
    std::list<RenderParticle*> RenderParticles;

    GLuint VAO, VBO;

    int numSparks = 0;
    std::cout << "Input spark count: ";
    std::cin >> numSparks;



    int vec[3];
    int lowerBoundVel[3] = { -200, 10, -200 };
    int upperBoundVel[3] = { 200, 500, 200 };
    int lowerBoundAcc[3] = { -100, 600, -100 };
    int upperBoundAcc[3] = { 100, 6000, 100 };

    MyVector defaultSpawn(0, -SCREEN_HEIGHT + 150, 0);
    Utility utility;

    int spawned = 0;
    float timePoint = 0.0f;
    float converter = 1000000;


    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);



    srand((unsigned)time(NULL));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);


        //FIXED UPDATE
        curr_time = clock::now();       
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds> (curr_time - prev_time);
        prev_time = curr_time;     
       
        timePoint += (float)dur.count() / 1000;
      //  std::cout << time << std::endl;

        curr_ns += dur;


        if (curr_ns >= timestep){
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);

            curr_ns -= curr_ns;

            pWorld.Update((float)ms.count() / 1000);

          //  modelManager.checkModels(); FOR DEBUGGING ONLY


            if (spawned < numSparks) {

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
                        lifespan,
                        timePoint / converter);
                pWorld.AddParticle(particle);

                //GENERATE RANDOM COLOR
                for (int j = 0; j < 3; j++)
                    vec[j] = utility.getRandomNumber(50, 254);

                glm::vec4 colorVec = glm::vec4(vec[0] / 254.0f, vec[1] / 254.0f, vec[2] / 254.0f, 1.0f);

                //GENERATE RADIUS
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

                std::cout << "SPAWNED: " << spawned << std::endl;
            }
        }
        
        pWorld.CheckLifespan(timePoint / converter);

        
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