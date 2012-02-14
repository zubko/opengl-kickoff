#define HELLO_MAGIC_MAIN
#include "common.h"

#include "Time.h"
#include "Shader.h"

int window_width = 800;
int window_height = 600;

static SDL_Window *win;
static SDL_GLContext ctx;

Shader shader;
Time gameTime;
float perspectiveMatrix[16] = {0};


const int numberOfVertices = 36;

#define RIGHT_EXTENT 0.8f
#define LEFT_EXTENT -RIGHT_EXTENT
#define TOP_EXTENT 0.20f
#define MIDDLE_EXTENT 0.0f
#define BOTTOM_EXTENT -TOP_EXTENT
#define FRONT_EXTENT -1.25f
#define REAR_EXTENT -1.75f

#define GREEN_COLOR 0.75f, 0.75f, 1.0f, 1.0f
#define BLUE_COLOR  0.0f, 0.5f, 0.0f, 1.0f
#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f
#define GREY_COLOR 0.8f, 0.8f, 0.8f, 1.0f
#define BROWN_COLOR 0.5f, 0.5f, 0.0f, 1.0f

const float vertexData[] = {
    //Object 1 positions
    LEFT_EXTENT,    TOP_EXTENT,     REAR_EXTENT,
    LEFT_EXTENT,    MIDDLE_EXTENT,  FRONT_EXTENT,
    RIGHT_EXTENT,   MIDDLE_EXTENT,  FRONT_EXTENT,
    RIGHT_EXTENT,   TOP_EXTENT,     REAR_EXTENT,
    
    LEFT_EXTENT,    BOTTOM_EXTENT,  REAR_EXTENT,
    LEFT_EXTENT,    MIDDLE_EXTENT,  FRONT_EXTENT,
    RIGHT_EXTENT,   MIDDLE_EXTENT,  FRONT_EXTENT,
    RIGHT_EXTENT,   BOTTOM_EXTENT,  REAR_EXTENT,
    
    LEFT_EXTENT,    TOP_EXTENT,     REAR_EXTENT,
    LEFT_EXTENT,    MIDDLE_EXTENT,  FRONT_EXTENT,
    LEFT_EXTENT,    BOTTOM_EXTENT,  REAR_EXTENT,
    
    RIGHT_EXTENT,   TOP_EXTENT,     REAR_EXTENT,
    RIGHT_EXTENT,   MIDDLE_EXTENT,  FRONT_EXTENT,
    RIGHT_EXTENT,   BOTTOM_EXTENT,  REAR_EXTENT,
    
    LEFT_EXTENT,    BOTTOM_EXTENT,  REAR_EXTENT,
    LEFT_EXTENT,    TOP_EXTENT,     REAR_EXTENT,
    RIGHT_EXTENT,   TOP_EXTENT,     REAR_EXTENT,
    RIGHT_EXTENT,   BOTTOM_EXTENT,  REAR_EXTENT,
    
    //Object 2 positions
    TOP_EXTENT,     RIGHT_EXTENT,   REAR_EXTENT,
    MIDDLE_EXTENT,  RIGHT_EXTENT,   FRONT_EXTENT,
    MIDDLE_EXTENT,  LEFT_EXTENT,    FRONT_EXTENT,
    TOP_EXTENT,     LEFT_EXTENT,    REAR_EXTENT,
    
    BOTTOM_EXTENT,  RIGHT_EXTENT,   REAR_EXTENT,
    MIDDLE_EXTENT,  RIGHT_EXTENT,   FRONT_EXTENT,
    MIDDLE_EXTENT,  LEFT_EXTENT,    FRONT_EXTENT,
    BOTTOM_EXTENT,  LEFT_EXTENT,    REAR_EXTENT,
    
    TOP_EXTENT,     RIGHT_EXTENT,   REAR_EXTENT,
    MIDDLE_EXTENT,  RIGHT_EXTENT,   FRONT_EXTENT,
    BOTTOM_EXTENT,  RIGHT_EXTENT,   REAR_EXTENT,
    
    TOP_EXTENT,     LEFT_EXTENT,    REAR_EXTENT,
    MIDDLE_EXTENT,  LEFT_EXTENT,    FRONT_EXTENT,
    BOTTOM_EXTENT,  LEFT_EXTENT,    REAR_EXTENT,
    
    BOTTOM_EXTENT,  RIGHT_EXTENT,   REAR_EXTENT,
    TOP_EXTENT,     RIGHT_EXTENT,   REAR_EXTENT,
    TOP_EXTENT,     LEFT_EXTENT,    REAR_EXTENT,
    BOTTOM_EXTENT,  LEFT_EXTENT,    REAR_EXTENT,
    
    //Object 1 colors
    GREEN_COLOR,
    GREEN_COLOR,
    GREEN_COLOR,
    GREEN_COLOR,
    
    BLUE_COLOR,
    BLUE_COLOR,
    BLUE_COLOR,
    BLUE_COLOR,
    
    RED_COLOR,
    RED_COLOR,
    RED_COLOR,
    
    GREY_COLOR,
    GREY_COLOR,
    GREY_COLOR,
    
    BROWN_COLOR,
    BROWN_COLOR,
    BROWN_COLOR,
    BROWN_COLOR,
    
    //Object 2 colors
    RED_COLOR,
    RED_COLOR,
    RED_COLOR,
    RED_COLOR,
    
    BROWN_COLOR,
    BROWN_COLOR,
    BROWN_COLOR,
    BROWN_COLOR,
    
    BLUE_COLOR,
    BLUE_COLOR,
    BLUE_COLOR,
    
    GREEN_COLOR,
    GREEN_COLOR,
    GREEN_COLOR,
    
    GREY_COLOR,
    GREY_COLOR,
    GREY_COLOR,
    GREY_COLOR,
};

const GLshort indexData[] =
{
    0, 2, 1,
    3, 2, 0,
    
    4, 5, 6,
    6, 7, 4,
    
    8, 9, 10,
    11, 13, 12,
    
    14, 16, 15,
    17, 16, 14,
};

GLuint vertexBufferObject;
GLuint indexBufferObject;

GLuint vaoObject;

static bool running = true;

void InitializeViewport();

static void critical_error(const std::string &title, const std::string &text)
{
#if defined(WIN32) || defined(_WINDOWS)
    MessageBoxA(0, text.c_str(), title.c_str(),
                MB_OK | MB_SETFOREGROUND | MB_ICONSTOP);
#else
    std::cout << "Critical error: " << title << std::endl << text << std::endl;
#endif
    exit(1);
}

void handle_event(SDL_Event &evt, float dt)
{
    if (evt.type == SDL_QUIT) {
        running = false;
    } else if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE) {
        running = false;
    } else if (evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_RESIZED) {
        InitializeViewport();
    }
}

void update(float dt)
{
}

void render()
{
    GL(glClearColor(0.3, 0.6, 0.9, 0));
	GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        
    GL(shader.Use());
    GL(glBindVertexArray(vaoObject));
    
    GL(shader.SetUniform1f("time", gameTime.elapsed_));
    GL(shader.SetUniform3f("offset", 0, 0, 0));
    GL(glDrawElements(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0));

    GL(shader.SetUniform1f("time", gameTime.elapsed_*1.5));
    GL(shader.SetUniform3f("offset", 0, 0, -1));
    GL(glDrawElementsBaseVertex(GL_TRIANGLES, ARRAY_COUNT(indexData), GL_UNSIGNED_SHORT, 0, 
                                numberOfVertices / 2));
    
    GL(glBindVertexArray(0));
    GL(shader.Leave());
}

void mainloop()
{
    SDL_Event evt;
    gameTime.Init();
    
    while (running) {
        gameTime.Tick();
        
        while (SDL_PollEvent(&evt))
            handle_event(evt, gameTime.delta_);
        
        update(gameTime.delta_);
        render();
        
        SDL_GL_SwapWindow(win);
        SDL_Delay(1);
    }
}

void InitializeVertexBuffer() {
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void InitializedVertextArrayObjects() {
    glGenVertexArrays(1, &vaoObject);
    glBindVertexArray(vaoObject);
    size_t colorDataOffset = sizeof(float) * 3 * numberOfVertices;
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)colorDataOffset);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBindVertexArray(0);
}

bool InitializeProgram()
{
    CHECK_RESULT(shader.InitWithName("simple"));
    CHECK_RESULT(shader.AddUniform("loopDuration"));
    CHECK_RESULT(shader.AddUniform("time"));
    CHECK_RESULT(shader.AddUniform("fragLoopDuration"));
    CHECK_RESULT(shader.AddUniform("perspectiveMatrix"));
    CHECK_RESULT(shader.AddUniform("offset"));
    
    shader.Use();
    shader.SetUniform1f("loopDuration", 5.0f);
    shader.SetUniform1f("fragLoopDuration", 10.f);
    
    float fzNear = 0.5f, fzFar = 3.0f;
    perspectiveMatrix[10] = (fzFar + fzNear) / (fzNear - fzFar);
    perspectiveMatrix[14] = (2 * fzFar * fzNear) / (fzNear - fzFar);
    perspectiveMatrix[11] = -1.0f;
    shader.SetUniformMatrix4fv("perspectiveMatrix", 1, GL_FALSE, perspectiveMatrix);
    
    shader.Leave();
    
    return true;
}

void InitializeViewport() 
{
    SDL_GetWindowSize(win, &window_width, &window_height);

    float fFrustumScale = 1.0f; 
    perspectiveMatrix[0] = fFrustumScale / (window_width / (float)window_height);
    perspectiveMatrix[5] = fFrustumScale;
    shader.Use();
    shader.SetUniformMatrix4fv("perspectiveMatrix", 1, GL_FALSE, perspectiveMatrix);
    shader.Leave();

    glViewport(0, 0, window_width, window_height);
}

bool Initialize()
{
	fprintf(
            stdout,
            "INFO: OpenGL Version: %s\n",
            glGetString(GL_VERSION)
            );
    fprintf(stdout,
            "INFO: OpenGL Shader Version: %s\n",
            glGetString(GL_SHADING_LANGUAGE_VERSION));

    CHECK_RESULT(InitializeProgram());
    InitializeViewport();
    InitializeVertexBuffer();
    InitializedVertextArrayObjects();
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    
    return true;
}

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        critical_error("Could not initialize SDL", SDL_GetError());
    
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    
    win = SDL_CreateWindow("Hello SDL",
                           SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED,
                           window_width, window_height,
                           SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!win)
        critical_error("Unable to create render window", SDL_GetError());
    SDL_CHECK_ERROR;
    
    ctx = SDL_GL_CreateContext(win);
    SDL_CHECK_ERROR;
    
    SDL_GL_SetSwapInterval(1);
    
    if (!Initialize())
        critical_error("Initialization error", "");
    
    mainloop();
    
    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
