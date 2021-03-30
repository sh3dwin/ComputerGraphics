#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#pragma once


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

const char* vertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;"
"}\0";

const char* fragmentShader = 
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";


const char* vertexShader_finkiLogo = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"}\0";

const char* fragmentShader_finkiLogo = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

const char* fragmentShaderWithInputColor = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 Color;\n"
"void main()\n"
"{\n"
"   FragColor = Color;\n"
"}\n\0";

struct Circle
{
    unsigned int VAO;
    unsigned int numOfVertices;
};

 Circle get_circle(double x_coordinate, double y_coordinate, double circle_radius) {
    float vertices[10000] = {0};

    float x0 = 255 * x_coordinate; //starting x
    float y0 = 255 * y_coordinate; // starting y
    float radius = int(circle_radius * 255); //radius
    float x = radius;
    float y = 0;
    float err = 0;
    vertices[0] = x_coordinate;
    vertices[1] = y_coordinate;
    vertices[2] = 0.0;
    int i = 3;
    while (x >= y - 1)
    {

        vertices[i++] = (x0 + x) / 255;
        vertices[i++] = (y0 + y) / 255;
        vertices[i++] = 0.0f;

        vertices[i++] = (x0 - x) / 255;
        vertices[i++] = (y0 - y) / 255;
        vertices[i++] = 0.0f;

        vertices[i++] = (x0 - x) / 255;
        vertices[i++] = (y0 + y) / 255;
        vertices[i++] = 0.0f;

        vertices[i++] = (x0 + x) / 255;
        vertices[i++] = (y0 - y) / 255;
        vertices[i++] = 0.0f;

        vertices[i++] = (x0 + y) / 255;
        vertices[i++] = (y0 + x) / 255;
        vertices[i++] = 0.0f;

        vertices[i++] = (x0 - y) / 255;
        vertices[i++] = (y0 - x) / 255;
        vertices[i++] = 0.0f;

        vertices[i++] = (x0 + y) / 255;
        vertices[i++] = (y0 - x) / 255;
        vertices[i++] = 0.0f;

        vertices[i++] = (x0 - y) / 255;
        vertices[i++] = (y0 + x) / 255;
        vertices[i++] = 0.0f;

        if (err <= 0)
        {
            y += 0.5;
            err += 2 * (float)y + 0.1;
        }
        if (err > 0)
        {
            x -= 0.5;
            err -= 2 * (float)x + 0.1;
        }
    }


    unsigned int object[10000] = {0};

    int t = 0;
    unsigned int numTriangles = 0;
    for (int j = 0; j < i - 24;) {
        for (int k = 0; k < 8; k++) {
            object[j++] = 0;
            object[j++] = t * 8 + 1 + k;
            object[j++] = t * 8 + 9 + k;
            numTriangles += 3;
        }
        t++;
    }


    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(object), object, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return Circle{VAO, numTriangles};
}

unsigned int get_rectangle_vertex_array(float bottom_left_x, float bottom_left_y, float top_right_x, float top_right_y) {
    float vertices[] = {
        bottom_left_x, bottom_left_y, 0.0f, // bottom left
        bottom_left_x, top_right_y,   0.0f, // top left
        top_right_x, top_right_y,     0.0f, // top right
        top_right_x, bottom_left_y,   0.0f  // bottom right 
    };

    unsigned int object_array[] = {
        0, 1, 2, // upper right side triangle
        0, 2, 3  // lower left side triangle
    };

    unsigned int VAO = 0, VBO = 0, EBO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(object_array), object_array, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    return VAO;
}



Circle get_colorful_circle_vertex_array(unsigned int x_coordinate, unsigned int y_coordinate, float circle_radius) {
    unsigned int verticesAmount = 33;

    // ------------------------------------------------------------- finding the circle's vertices using Circle Midpoint Algorithm ------------------------------------------------------------------

    float vertices[40000] = {0};

    float x0 = 255 * x_coordinate; //starting x
    float y0 = 255 * y_coordinate; // starting y
    float x =  circle_radius * 255; //radius
    float y = 0;
    float err = 0;
    
    unsigned int number_of_triangles_in_octant = 0;
    int i = 0;
    while (x >= y)
    {
        //-------------------------------- mirroring each vertex starting from positive x-axis going counter clockwise -----------------------------------------------------

        // first octant
        vertices[i++] = (x0 + x) / 255;
        vertices[i++] = (y0 + y) / 255;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        // second octant
        vertices[i++] = (x0 + y) / 255;
        vertices[i++] = (y0 + x) / 255;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        // third octant
        vertices[i++] = (x0 - y) / 255;
        vertices[i++] = (y0 + x) / 255;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        // fourth octant
        vertices[i++] = (x0 - x) / 255;
        vertices[i++] = (y0 + y) / 255;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        // fifth octant
        vertices[i++] = (x0 - x) / 255;
        vertices[i++] = (y0 - y) / 255;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        // sixth octant
        vertices[i++] = (x0 - y) / 255;
        vertices[i++] = (y0 - x) / 255;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        // seventh octant
        vertices[i++] = (x0 + y) / 255;
        vertices[i++] = (y0 - x) / 255;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        //eight octant
        vertices[i++] = (x0 + x) / 255;
        vertices[i++] = (y0 - y) / 255;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        vertices[i++] = 0.0f;
        number_of_triangles_in_octant++;

        //finding the position of the next vertex
        if (err <= 0)
        {
            y += 0.5;
            err += 2.0 * y + 0.1;
        }
        if (err > 0)
        {
            x -= 0.5;
            err -= 2.0 * x + 0.1;
        }
    }

    unsigned int numVertices = number_of_triangles_in_octant * 8 * 3;

    // this is used later as a starting index for the vertices at the center of the circle
    int center_vertices_starting_index = i;




    // ------------------------------------ creating the object array ------------------------------------------------

    unsigned int object[10000] = { 0 };
    int j = 0;
    for (int octant = 0; octant < 8; octant++) {
        if (octant % 2 == 0) {
            for (int t = 0; t < number_of_triangles_in_octant; t++) {

                object[j++] = i / 6; // circle center
                object[j++] = t * 8 + octant; // vertex lying on the circle
                object[j++] = t * 8 + 8 + octant; // the neighboring vertex of the previous vertex offset by 8 to skip the vertices to be used in mirrored triangles
                vertices[i++] = x_coordinate;
                vertices[i++] = y_coordinate;
                vertices[i++] = 0.0f;
                vertices[i++] = 0.0f;
                vertices[i++] = 0.0f;
                vertices[i++] = 0.0f;
                numVertices += 6;
            }
        }
        else {
            for (int t = number_of_triangles_in_octant - 1; t >= 0; t--) {

                object[j++] = i / 6; // circle center
                object[j++] = t * 8 + octant; // vertex lying on the circle
                object[j++] = t * 8 + 8 + octant; // the neighboring vertex of the previous vertex offset by 8 to skip the vertices to be used in mirrored triangles
                vertices[i++] = x_coordinate;
                vertices[i++] = y_coordinate;
                vertices[i++] = 0.0f;
                vertices[i++] = 0.0f;
                vertices[i++] = 0.0f;
                vertices[i++] = 0.0f;
                numVertices += 6;
            }
        }
    }
    float R = 1.0f;
    float G = 0.0f;
    float B = 0.0f;
    int sixth = j / 6;
    float increment = 0.25 / (float)number_of_triangles_in_octant;
    for (int k = 0; k < j; k++) {
        switch (k / sixth) {
            case 0: {
                G += increment;
                vertices[6 * object[k] + 3] = R;
                vertices[6 * object[k] + 4] = G;
                vertices[6 * object[k] + 5] = B; 
                break;
            }
            case 1: {
                R -= increment;
                vertices[6 * object[k] + 3] = R;
                vertices[6 * object[k] + 4] = G;
                vertices[6 * object[k] + 5] = B;     
                break;
            }
            case 2: {
                B += increment;
                vertices[6 * object[k] + 3] = R;
                vertices[6 * object[k] + 4] = G;
                vertices[6 * object[k] + 5] = B;     
                break;
            }
            case 3: {
                G -= increment;
                vertices[6 * object[k] + 3] = R;
                vertices[6 * object[k] + 4] = G;
                vertices[6 * object[k] + 5] = B;              
                break;
            }
            case 4: {
                R += increment;
                vertices[6 * object[k] + 3] = R;
                vertices[6 * object[k] + 4] = G;
                vertices[6 * object[k] + 5] = B;       
                break;
            }
            case 5: {
                B -= increment;
                vertices[6 * object[k] + 3] = R;
                vertices[6 * object[k] + 4] = G;
                vertices[6 * object[k] + 5] = B;       
                break;
            }
            default:
                break;
        }
    }

    unsigned int VBO = 0, VAO = 0, EBO = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(object), object, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    std::cout << "Num vertices is: " << numVertices << std::endl;

    return Circle{ VAO, numVertices };
}

void draw_circle(double x_coordinate, double y_coordinate, double circle_radius) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(400, 400, "lab2_196013", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    unsigned int vertex_shader1 = 0;
    vertex_shader1 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader1, 1, &vertexShader, NULL);
    glCompileShader(vertex_shader1);

    unsigned int fragment_shader1 = 0;
    fragment_shader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader1, 1, &fragmentShader, NULL);
    glCompileShader(fragment_shader1);

    unsigned int shader_program1 = 0;
    shader_program1 = glCreateProgram();
    glAttachShader(shader_program1, vertex_shader1);
    glAttachShader(shader_program1, fragment_shader1);
    glLinkProgram(shader_program1);
    glDeleteShader(vertex_shader1);
    glDeleteShader(fragment_shader1);
    Circle circle = get_colorful_circle_vertex_array(x_coordinate, y_coordinate, circle_radius);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        /* Render here */
        glUseProgram(shader_program1);
        
        glBindVertexArray(circle.VAO);
        glDrawElements(GL_TRIANGLES, circle.numOfVertices, GL_UNSIGNED_INT, 0);
        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }
    glDeleteProgram(shader_program1);
    glfwTerminate;
}

void draw_color_gradient_rectangles() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(400, 400, "lab2_196013", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    unsigned int vertex_shader1 = 0;
    vertex_shader1 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader1, 1, &vertexShader, NULL);
    glCompileShader(vertex_shader1);

    unsigned int fragment_shader1 = 0;
    fragment_shader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader1, 1, &fragmentShaderWithInputColor, NULL);
    glCompileShader(fragment_shader1);

    unsigned int shader_program = 0;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader1);
    glAttachShader(shader_program, fragment_shader1);
    glLinkProgram(shader_program);



    while (!glfwWindowShouldClose(window))
    {

        processInput(window);
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        /* Render here */

        //Drawing Red Color Gradient Rectangle
        for (int i = 0; i < 10; i++) {
            glUseProgram(shader_program);
            int colorID = glGetUniformLocation(shader_program, "Color");
            glUniform4f(colorID, (double)i / 10.0, 0.0f, 0.0f, 1.0f);
            unsigned int VAO = get_rectangle_vertex_array(-0.6, 0.4 + ((double)i / 20.0), 0.6, 0.4 + ((double)(i + 1)/ 20.0));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        glBindVertexArray(0);
        for (int i = 0; i < 10; i++) {
            glUseProgram(shader_program);
            int colorID = glGetUniformLocation(shader_program, "Color");
            glUniform4f(colorID, 0.0f, (double)i / 10.0, 0.0f, 1.0f);
            unsigned int VAO = get_rectangle_vertex_array(-0.6, -0.25 + ((double)i / 20.0), 0.6, -0.25 + ((double)(i + 1) / 20.0));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        glBindVertexArray(0);
        for (int i = 0; i < 10; i++) {
            glUseProgram(shader_program);
            int colorID = glGetUniformLocation(shader_program, "Color");
            glUniform4f(colorID, 0.0f, 0.0f, (double)i / 10.0, 1.0f);
            unsigned int VAO = get_rectangle_vertex_array( -0.6, -0.9 + ((double)i / 20.0), 0.6, -0.9 + ((double)(i + 1) / 20.0));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        glBindVertexArray(0);
        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }
    glDeleteShader(vertex_shader1);
    glDeleteShader(fragment_shader1);
    glDeleteProgram(shader_program);
    glfwTerminate;
}

void draw_finki_logo() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(400, 400, "lab2_196013", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    unsigned int vertex_shader1;
    vertex_shader1 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader1, 1, &vertexShader_finkiLogo, NULL);
    glCompileShader(vertex_shader1);

    unsigned int fragment_shader1;
    fragment_shader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader1, 1, &fragmentShader_finkiLogo, NULL);
    glCompileShader(fragment_shader1);

    unsigned int shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader1);
    glAttachShader(shader_program, fragment_shader1);
    glLinkProgram(shader_program);
    

    Circle outerCircle = get_circle(0.2f, 0.0f, 0.4);
    Circle innerCircle = get_circle(0.2f, 0.0f, 0.25);
    unsigned int VAO_rectangle = get_rectangle_vertex_array(-0.5, -0.3, -0.3, 0.3);


    while (!glfwWindowShouldClose(window))
    {

        processInput(window);
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        /* Render here */
        
        
        glUseProgram(shader_program);
        int color = glGetUniformLocation(shader_program, "ourColor");
        glUniform4f(color, 0.0f, 0.3f, 0.7f, 1.0f);
        glBindVertexArray(outerCircle.VAO);
        glDrawElements(GL_TRIANGLES, outerCircle.numOfVertices - 24, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glUseProgram(shader_program);
        color = glGetUniformLocation(shader_program, "ourColor");
        glUniform4f(color, 1.0f, 1.0f, 1.0f, 1.0f);
        glBindVertexArray(innerCircle.VAO);
        glDrawElements(GL_TRIANGLES, innerCircle.numOfVertices - 24, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glUseProgram(shader_program);
        color = glGetUniformLocation(shader_program, "ourColor");
        glUniform4f(color, 0.0f, 0.0f, 0.5f, 1.0f);
        glBindVertexArray(VAO_rectangle);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }
    glDeleteShader(vertex_shader1);
    glDeleteShader(fragment_shader1);
    glDeleteProgram(shader_program);
    glfwTerminate;
}