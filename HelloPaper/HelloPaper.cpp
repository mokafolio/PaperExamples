// This example shows the very basic steps to create a Paper Document
// and draw it.

// we use GLFW to open a simple window
#include <GLFW/glfw3.h>

//include some paper headers.
#include <Paper/Document.hpp>

//we want to use the OpenGL renderer, so we include it.
#include <Paper/OpenGL/GLRenderer.hpp>

#include <Crunch/Randomizer.hpp>

#include <Stick/Thread.hpp>


//we want to use the paper, brick, crunch & stick namespaces
using namespace paper; // paper namespace
using namespace brick; // brick namespace for entity / component things
using namespace crunch; // crunch namespace for math
using namespace stick; // stick namespace for core data structures/containers etc.

int main(int _argc, const char * _args[])
{
    // initialize glfw
    if (!glfwInit())
        return EXIT_FAILURE;

    // and set some hints to get the correct opengl versions/profiles
    glfwWindowHint(GLFW_SAMPLES, 8);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create the window
    GLFWwindow * window = glfwCreateWindow(800, 600, "Hello Paper Example", NULL, NULL);
    if (window)
    {
        glfwMakeContextCurrent(window);

        // the brick entity hub to use by the paper document.
        Hub hub;
        // create the document.
        Document doc = createDocument(hub);
        doc.setSize(800, 600);
        // create the opengl renderer for the document
        opengl::GLRenderer renderer(doc);

        Path bg = doc.createRectangle(Vec2f(0), Vec2f(800, 600));
        bg.setFill(ColorRGBA(0.3, 0.3, 0.3, 1.0));

        //create a simple donut from two circles
        Path circle = doc.createCircle(Vec2f(400, 300.0), 60.0);
        circle.setFill(ColorRGBA(1.0, 1.0, 0.0, 1.0));
        circle.setStrokeWidth(5.0);
        circle.setStroke(ColorRGBA(1.0, 0.0, 1.0, 1.0));

        //create the hole
        Path innerCircle = circle.clone();
        innerCircle.scale(0.5);
        circle.addChild(innerCircle);


        Path rct = doc.createRectangle(Vec2f(100, 100), Vec2f(200, 300));
        rct.setFill(ColorRGBA(1.0, 0.0, 0.0, 1.0));

        Path arc = doc.createPath();
        arc.addPoint(Vec2f(200, 300));
        arc.arcTo(Vec2f(300, 300), Vec2f(100.0, 50.0), crunch::Constants<Float32>::pi() * 0.25, false, false);
        arc.setFill(ColorRGBA(1, 1, 0, 1));

        //arc.rotate(Constants<Float>::pi() * 0.5);
        rct.skew(Vec2f(0, Constants<Float>::pi() * 0.1), arc.position());

        //doc.translateTransform(Vec2f());

        Randomizer r;
        /*for(int i=0; i<10000; ++i)
        {
            Path circle = doc.createCircle(Vec2f(r.randomf(0, 800), r.randomf(0, 600)), 10.0);
            circle.setFill(ColorRGBA(1.0, 1.0, 0.0, 1.0));
        }*/

        // the main loop
        while (!glfwWindowShouldClose(window))
        {
            // clear the background to black
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            // get the window size from the glfw window
            // and set it as the viewport on the renderer
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            renderer.setViewport(width, height);
            renderer.setTransform(Mat3f::identity());

            auto err = renderer.draw();
            if(err)
                return EXIT_FAILURE;

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    else
    {
        glfwTerminate();
        printf("Could not open GLFW window :(\n");
        return EXIT_FAILURE;
    }

    // clean up glfw
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
