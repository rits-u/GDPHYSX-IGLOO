#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define TINYOBJLOADER_IMPLEMENTATION
//#include "tiny_obj_loader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>


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

#include "P6/Links/Rod.h"
#include "P6/Links/Cable.h"


#include "Utility/RenderLine.h"

#include <chrono>
using namespace std::chrono_literals;
constexpr std::chrono::nanoseconds timestep(16ms);

using namespace model;
using namespace P6;
using namespace utility;

//SCREEN SIZE
float width = 800.0f;
float height = 800.0f;

//FOR CAMERA ROTATION
float rotate = 0.0f;

//FOR "SPACE" INPUT
bool addForce = false;
bool startedSimulation = false;

//FOR CAMERA SWITCH
std::string cameraType = "Ortho";


void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //switch to ortho
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (cameraType != "Ortho") {
            cameraType = "Ortho";
            std::cout << "Switched to Ortho Camera" << std::endl;

        }
        else {
            std::cout << "Already using ortho projection" << std::endl;
        }
    }

    //switch to perspective
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (cameraType != "Perspective") {
            cameraType = "Perspective";
            std::cout << "Switched to Perspective Camera" << std::endl;
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

    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !startedSimulation) {
        addForce = true;
        startedSimulation = true;
        std::cout << "Started simulation!" << std::endl;
    }
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "IGLOO", NULL, NULL);
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

    
    //--------CREATE SHADER--------
    Shader* shader = new Shader();
    GLuint shaderProg = shader->createShader("Shaders/shader.vert", "Shaders/shader.frag");
    glLinkProgram(shaderProg);
    shader->deleteShader();


    //--------DECLARATION OF NEEDED VARIABLES-----------
    Camera* camera = new Camera();
    P6::PhysicsWorld* pWorld = new P6::PhysicsWorld();
    std::list<RenderParticle*> RenderParticles;

    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);

    GLuint VBO;

    //default values
    float length = 200;
    float gap = 100;
    float radius = 30;
    float gravityStr = -100;
    float fX = 50000, fY = 0, fZ = 0;
    
   
    //USER INPUT
    std::cout << "Cable Length: "; std::cin >> length;
    std::cout << "Particle Gap: "; std::cin >> gap;
    std::cout << "Particle Radius: "; std::cin >> radius;
    std::cout << "Gravity Strength: "; std::cin >> gravityStr;
    std::cout << "Apply Force" << std::endl;
    std::cout << "x: "; std::cin >> fX;
    std::cout << "y: "; std::cin >> fY;
    std::cout << "z: "; std::cin >> fZ;


    float mass = 50;
    float default_y = 200;
    MyVector applyForce = MyVector(fX, fY, fZ);
    glm::vec4 colorVec = glm::vec4(254 / 254.0f, 0 / 254.0f, 0 / 254.0f, 1.0f); //red


    //----------------1ST PARTICLE------------------
    //instantiate anchor particle
    P6Particle* a1 = new P6Particle(MyVector(-gap*2, default_y, 0), 0, mass, radius);
    pWorld->AddParticle(a1);

    //instantiate actual particle
    P6Particle* p1 = new P6Particle(gravityStr, MyVector(a1->Position.x, -10, 0), mass, radius);
    pWorld->AddParticle(p1);

    //instantiate the particle's model
    Model3D* m1 = new Model3D(colorVec, shaderProg);
    m1->loadModel("3D/sphere.obj", &VBO);

    //instantiate a render particle
    RenderParticle* rp1 = new RenderParticle(p1, m1);
    rp1->Scale = MyVector(p1->radius, p1->radius, p1->radius);
    RenderParticles.push_back(rp1);

    //instantiate cable for these particles
    Cable* cable1 = new Cable(a1, length);
    cable1->particles[1] = p1;
    pWorld->Links.push_back(cable1);

    //instantiate render line 
    RenderLine* line1 = new RenderLine(a1->Position, p1->Position, MyVector(1, 1, 1));
    


    //----------------2ND PARTICLE------------------
    P6Particle* a2 = new P6Particle(MyVector(-gap, default_y, 0), 0, mass, radius);
    pWorld->AddParticle(a2);

    P6Particle* p2 = new P6Particle(gravityStr, MyVector(a2->Position.x, -10, 0), mass, radius);
    pWorld->AddParticle(p2);

    Model3D* m2 = new Model3D(colorVec, shaderProg);
    m2->loadModel("3D/sphere.obj", &VBO);

    RenderParticle* rp2 = new RenderParticle(p2, m2);
    rp2->Scale = MyVector(p2->radius, p2->radius, p2->radius);
    RenderParticles.push_back(rp2);

    Cable* cable2 = new Cable(a2, length);
    cable2->particles[1] = p2;
    pWorld->Links.push_back(cable2);

    RenderLine* line2 = new RenderLine(a2->Position, p2->Position, MyVector(1, 1, 1));



    //----------------3RD PARTICLE------------------
    P6Particle* a3 = new P6Particle(MyVector(0, default_y, 0), 0, mass, radius);
    pWorld->AddParticle(a3);

    P6Particle* p3 = new P6Particle(gravityStr, MyVector(a3->Position.x, -10, 0), mass, radius);
    pWorld->AddParticle(p3);

    Model3D* m3 = new Model3D(colorVec, shaderProg);
    m3->loadModel("3D/sphere.obj", &VBO);

    RenderParticle* rp3 = new RenderParticle(p3, m3);
    rp3->Scale = MyVector(p3->radius, p3->radius, p3->radius);
    RenderParticles.push_back(rp3);

    Cable* cable3 = new Cable(a3, length);
    cable3->particles[1] = p3;
    pWorld->Links.push_back(cable3);

    RenderLine* line3 = new RenderLine(a3->Position, p3->Position, MyVector(1, 1, 1));


    
    //----------------4TH PARTICLE------------------
    P6Particle* a4 = new P6Particle(MyVector(gap, default_y, 0), 0, mass, radius);
    pWorld->AddParticle(a4);

    P6Particle* p4 = new P6Particle(gravityStr, MyVector(a4->Position.x, -10, 0), mass, radius);
    pWorld->AddParticle(p4);

    Model3D* m4 = new Model3D(colorVec, shaderProg);
    m4->loadModel("3D/sphere.obj", &VBO);

    RenderParticle* rp4 = new RenderParticle(p4, m4);
    rp4->Scale = MyVector(p4->radius, p4->radius, p4->radius);
    RenderParticles.push_back(rp4);

    Cable* cable4 = new Cable(a4, length);
    cable4->particles[1] = p4;
    pWorld->Links.push_back(cable4);

    RenderLine* line4 = new RenderLine(a4->Position, p4->Position, MyVector(1, 1, 1));



    //----------------5TH PARTICLE------------------
    P6Particle* a5 = new P6Particle(MyVector(gap*2, default_y, 0), 0, mass, radius);
    pWorld->AddParticle(a5);

    P6Particle* p5 = new P6Particle(gravityStr, MyVector(a5->Position.x, -10, 0), mass, radius);
    pWorld->AddParticle(p5);

    Model3D* m5 = new Model3D(colorVec, shaderProg);
    m5->loadModel("3D/sphere.obj", &VBO);

    RenderParticle* rp5 = new RenderParticle(p5, m5);
    rp5->Scale = MyVector(p5->radius, p5->radius, p5->radius);
    RenderParticles.push_back(rp5);

    Cable* cable5 = new Cable(a5, length);
    cable5->particles[1] = p5;
    pWorld->Links.push_back(cable5);

    RenderLine* line5 = new RenderLine(a5->Position, p5->Position, MyVector(1, 1, 1));


  

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        curr_time = clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds> (curr_time - prev_time);
        prev_time = curr_time;

        curr_ns += dur;

        if (curr_ns >= timestep) {
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);

            curr_ns -= curr_ns;

            pWorld->Update((float)ms.count() / 1000);

        }

        //adds force to the leftmost particle when [SPACE] is pressed once
        if (addForce) {
            p1->AddForce(MyVector(50000, 0, 0) * 10);
            addForce = false;
        }

        //accumulates the length of the cables
        if (cable1->length < length) {
            cable1->length += 0.1f;
            cable2->length += 0.1f;
            cable3->length += 0.1f;
            cable4->length += 0.1f;
            cable5->length += 0.1f;
        }


        //get the projection and view matrix
        glm::mat4 projection = camera->getProjection(cameraType, width, height);
        glm::mat4 view = camera->getView(cameraType, rotate);

        //bind camera to the shader
        camera->bindCamera(cameraType, width, height, rotate, shaderProg);


        //draw the particles
        for (std::list<RenderParticle*>::iterator i = RenderParticles.begin();
            i != RenderParticles.end();
            i++
            ) {

            (*i)->draw(cameraType);
        }


        //display the render lines
        line1->Update(a1->Position, p1->Position, projection);
        line1->Draw();

        line2->Update(a2->Position, p2->Position, projection);
        line2->Draw();

        line3->Update(a3->Position, p3->Position, projection);
        line3->Draw();

        line4->Update(a4->Position, p4->Position, projection);
        line4->Draw();

        line5->Update(a5->Position, p5->Position, projection);
        line5->Draw();
     

        //swap front and back buffers
        glfwSwapBuffers(window);

        //poll for and process events
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}