#include "Include.h"
#include "Constant.h"

Framework::Framework()
    : timeScale(1.f), devMode(false)
{
}

Framework::~Framework()
{
}

float Framework::GetDT() const
{
    return deltaTime.asSeconds() * timeScale;
}

float Framework::GetRealDT() const
{
    return deltaTime.asSeconds();
}

void Framework::SetWindowSize(int width, int height)
{
    windowSize = Vector2u(width, height);
    window.setSize(windowSize);
}

const Vector2u& Framework::GetWindowSize() const
{
    return windowSize;
}

RenderWindow& Framework::GetWindow()
{
    return window;
}

bool Framework::Init(int width, int height, std::string title)
{
    windowSize = Vector2u(width, height);
    window.create(VideoMode(windowSize.x, windowSize.y), title);

    RESOURCE_MGR->LoadAll();
    SOUND_MGR->Init();
    //DATATABLE_MGR->Init();
    SCENE_MGR->Init();
    InputMgr::Init();

    return true;
}

bool Framework::Do()
{
    while ( window.isOpen() )
    {
        deltaTime = clock.restart();
        float dt = GetDT();

        InputMgr::Update(dt);
        Event ev;
        while ( window.pollEvent(ev) )
        {
            if ( ev.type == Event::Closed )
            {
                window.close();
            }
            InputMgr::ProcessInput(ev);
        }
        SCENE_MGR->Update(dt);
        SOUND_MGR->Update(dt);

        window.clear();
        SCENE_MGR->Draw(window);
        window.display();
    }

	return true;
}