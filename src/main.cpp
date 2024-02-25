#include "header.hpp"

#include "utils.cpp"
#include "shader.cpp"
#include "texture.cpp"
#include "ShapeGenerator.cpp"
#include "buffer.cpp"
#include "Camera.cpp"
#include "Shape.cpp"
#include "Transform.cpp"

using glm::vec2, glm::vec3, glm::vec4, glm::mat4;
float fov = 90.f;
float cube1z = -3.0f;
bool shouldClose = false;


vec3 camPos;
float camSpeed = 20.0f;
float camSpinspeed = 0.5f;
float pitch = 0.0f;
float yaw = 0.0f;
float sensitivity = .4f;
u_int fps_last = 0;

bool trapped = true;
bool fullscreen = false;

Camera cam;

sf::Text debugText;

WINDOWPLACEMENT g_wpPrev;

float deltaTimeSec;


bool Initialize(sf::RenderWindow& window)
{
    sf::ContextSettings settings;
    settings.majorVersion = 4;
    settings.minorVersion = 6;
    settings.attributeFlags = sf::ContextSettings::Attribute::Default;
    settings.depthBits = 24;
    window.create(sf::VideoMode(800, 600), "LearnOpenGL", sf::Style::Default, settings);
    g_wpPrev.length = sizeof(WINDOWPLACEMENT);
    GetWindowPlacement(window.getSystemHandle(), &g_wpPrev);

#ifdef GLAD_BUILD
    if (!gladLoadGLLoader((GLADloadproc)sf::Context::getFunction))
    {
        fmt::print("Failed to init GLAD\n");
        return false;
    }
#endif
#ifdef GLEW_BUILD
    if (glewInit() != GLEW_OK)
    {
        fmt::print("Failed to init GLEW\n");
        return false;
    }
#endif
    GLCALL(glViewport(0, 0, 800, 600));
    GLCALL(glEnable(GL_DEPTH_TEST));
    return true;
}




void Input(sf::RenderWindow& window, bool& wireframe, glm::vec2& mPos, std::vector<Shape>& shapes)
{
#define IsKey(k) sf::Keyboard::isKeyPressed(k)
    using enum sf::Keyboard::Key;
    if (IsKey(W))
    {
        cam.moveForward(camSpeed * deltaTimeSec);
    }
    if (IsKey(S))
    {
        cam.moveForward(-camSpeed * deltaTimeSec);
    }
    if (IsKey(A))
    {
        cam.moveRight(-camSpeed * deltaTimeSec);
    }
    if (IsKey(D))
    {
        cam.moveRight(camSpeed * deltaTimeSec);
    }
    if (IsKey(Space))
    {
        cam.moveUp(camSpeed * deltaTimeSec);
    }
    if (IsKey(LControl))
    {
        cam.moveUp(-camSpeed * deltaTimeSec);
    }
    if (IsKey(Home))
    {
        cam.reposition({ 0.f, 0.f, 0.f }, { 0.f, 0.f, -1.f });
        sf::Mouse::setPosition(screenCenter(window));
    }
    if (IsKey(I))
    {
        shapes.at(0).transform.moveBy({ 0.0f, 0.0f, 1.0f * deltaTimeSec });
    }
    if (IsKey(K))
    {
        shapes.at(0).transform.moveBy({ 0.0f, 0.0f, -1.0f * deltaTimeSec });
    }
    if (IsKey(J))
    {
        shapes.at(0).transform.moveBy({ 1.0f * deltaTimeSec, 0.0f, 0.0f });
    }
    if (IsKey(L))
    {
        shapes.at(0).transform.moveBy({ -1.0f * deltaTimeSec, 0.0f, 0.0f });
    }
    // Camera movement
    if (trapped && window.hasFocus())
    {
        vec2 mPos = s2g(sf::Mouse::getPosition(window));
        sf::Mouse::setPosition(screenCenter(window), window);
        vec2 center = s2g(screenCenter(window));
        cam.mouseUpdate(mPos, center);
    }
    for (sf::Event e; window.pollEvent(e);)
    {
        if (e.type == sf::Event::Closed)
        {
            fmt::print("Goodbye\n");
            shouldClose = true;
        }
        if (e.type == sf::Event::Resized)
        {
            fmt::print("Resized to {}, {}\n", e.size.width, e.size.height);
            GLCALL(glViewport(0, 0, e.size.width, e.size.height));
        }
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Key::F)
        {
            wireframe = !wireframe;
        }
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Key::Escape)
        {
            trapped = !trapped;
            window.setMouseCursorVisible(!trapped);
        }
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Key::F11)
        {
            fullscreen = !fullscreen;

            ToggleFullscreen(window, g_wpPrev);
        }
        if (e.type == sf::Event::MouseButtonPressed)
        {
            fmt::print("Click at {}, {}\n", e.mouseButton.x, e.mouseButton.y);
        }
        if (e.type == sf::Event::MouseWheelScrolled)
        {
            fov -= e.mouseWheelScroll.delta;
        }
    }
#undef IKP
    debugText.setString(fmt::format("X: {:.3f}, Y: {:.3f}, Z: {:.3f}, Pitch: {:.3f}, Yaw: {:.3f}\nFPS: {}",
        cam.pos().x, cam.pos().y, cam.pos().z, glm::degrees(cam.pitch_rad()), glm::degrees(cam.yaw_rad()), fps_last
    ));
}


uint indexCount = 0;

void VertexSpecification(std::vector<Shape>& shapes)
{

    shapes.emplace_back(ShapeGenerator::makeArrow);

    shapes.emplace_back(ShapeGenerator::makeTexCube);
    shapes.back().tex = Texture("../resources/textures/wall_marked.jpg");
}

void Draw(bool wireframe, Shader& shader, sf::Window& window, std::vector<Shape>& shapes)
{
    shader.use();
    GLCALL(glClearColor(119.f / 255.f, 181.f / 255.f, 254.f / 255.f, .180f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GLCALL(glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL));


    float aspect_ratio = (float)window.getSize().x / (float)window.getSize().y;

    mat4 viewToProjMat = glm::perspective(glm::radians(fov),
        aspect_ratio, 0.1f, 100.0f);

    mat4 worldToViewMat = cam.getWorldToViewMat();

    mat4 worldToProj = viewToProjMat * worldToViewMat;


    for (Shape& shape : shapes)
    {
        shape.Draw(worldToProj, shader);
    }

}

void DrawSFMLObjects(sf::RenderWindow& window, std::vector<sf::Drawable*>& drawables)
{
    GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
    UnbindallGL();
    window.setActive(false); // Contain all SFML draw calls to this section
    window.pushGLStates();

    window.setView(sf::View(sf::FloatRect(0.0, 0.0, window.getSize().x, window.getSize().y)));

    for (auto d : drawables)
    {
        window.draw(*d);
    }


    window.popGLStates();
    window.setActive(true);
}

int main()
{
    sf::RenderWindow window;
    window.setActive(true);
    window.setMouseCursorVisible(false);

    if (!Initialize(window))
    {
        return -1;
    }
    GLCALL(;);
    sf::Clock clock;
    { // OpenGL objects should live in this scope
        std::vector<Shape> shapes;

        VertexSpecification(shapes);
        Shader shader(vertShaderPath, fragShaderPath);



        bool wireframe = false;
        vec2 mPos;

        sf::Font font;
        font.loadFromFile("C:/Windows/Fonts/consola.ttf");
        debugText.setCharacterSize(24.f);
        debugText.setFillColor(sf::Color::White);
        debugText.setOutlineThickness(2.f);
        debugText.setOutlineColor(sf::Color::Black);
        debugText.setFont(font);

        std::vector<sf::Drawable*> drawables;
        drawables.push_back(&debugText);

        u_int accumulatedFrames = 0;
        sf::Clock frameTimer;

        while (!shouldClose)
        {
            accumulatedFrames += 1;
            deltaTimeSec = frameTimer.getElapsedTime().asSeconds() / (float)accumulatedFrames;
            if (frameTimer.getElapsedTime().asSeconds() > 1.f)
            {
                fps_last = accumulatedFrames;
                accumulatedFrames = 0;
                frameTimer.restart();
            }



        // OpenGL draw
        // window.setActive(true);
            Draw(wireframe, shader, window, shapes);



            DrawSFMLObjects(window, drawables);


            window.display();

            Input(window, wireframe, mPos, shapes);
        }
    }

    window.close();


    return 0;
}

