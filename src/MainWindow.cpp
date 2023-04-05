#include "MainWindow.h"
#include "Utility.h"
#include "Languages.h"
#include "Levels.h"

MainWindow::MainWindow(int width, int height, const char* title)
    : windowColor{ sf::Color(24,24,24) }
    , language{ 0 }
    , selectedLevel{ -1 }
{
    window.create(sf::VideoMode(width, height), title);
    SetIcon();
    InitializeTexturesAndResources();
    InitializeUIAndSettings();
    CalculateLayout();
    UpdateLanguage();
    SwitchScreenMode();
}

void MainWindow::SetIcon()
{
    HICON largeIcon{ (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(102), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED) };
    SetClassLongPtr(window.getSystemHandle(), GCLP_HICON, reinterpret_cast<LONG_PTR>(largeIcon));

    HICON smallIcon{ (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(103), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED) };
    SetClassLongPtr(window.getSystemHandle(), GCLP_HICONSM, reinterpret_cast<LONG_PTR>(smallIcon));
}

void MainWindow::InitializeTexturesAndResources()
{
    char* relativePath;
    _get_pgmptr(&relativePath);

    std::string path{ relativePath };
    path.erase(path.find_last_of('\\'));
    path += "/Resources";
    resourcesPath = path;

    for (int i{ 1 }; i <= 136; i++)
    {
        sf::Texture* texture{ new sf::Texture };
        texture->loadFromFile(resourcesPath + "/Assets/Images/Background/(" + std::to_string(i) + ").jpg");
        backgroundAnimation.addFrame({ texture, 0.05 });
    }

    objects["content"] = new DynamicObject;
    objects["content"]->setParent(window);
    objects["content"]->setSize(sf::Vector2f(1920.f, 1080.f));
    objects["content"]->setRelativePosition(50.f, 50.f);
    objects["content"]->setFillColor(sf::Color::Transparent);
    objects["content"]->hide();

    static sf::Texture t1;
    t1.loadFromFile(resourcesPath + "/Assets/Images/Grass1.png");
    DynamicObject* s1{ new DynamicObject };
    s1->setParent(*objects["content"]);
    s1->setSize(sf::Vector2f(60.f, 60.f));
    s1->setTexture(&t1);
    tiles.push_back(s1);

    static sf::Texture t2;
    t2.loadFromFile(resourcesPath + "/Assets/Images/Grass2.png");
    DynamicObject* s2{ new DynamicObject };
    s2->setParent(*objects["content"]);
    s2->setSize(sf::Vector2f(60.f, 60.f));
    s2->setTexture(&t2);
    tiles.push_back(s2);

    static sf::Texture t3;
    t3.loadFromFile(resourcesPath + "/Assets/Images/Grass3.png");
    DynamicObject* s3{ new DynamicObject };
    s3->setParent(*objects["content"]);
    s3->setSize(sf::Vector2f(60.f, 60.f));
    s3->setTexture(&t3);
    tiles.push_back(s3);

    static sf::Texture t4;
    t4.loadFromFile(resourcesPath + "/Assets/Images/House.png");
    DynamicObject* s4{ new DynamicObject };
    s4->setParent(*objects["content"]);
    s4->setSize(sf::Vector2f(60.f, 60.f));
    s4->setTexture(&t4);
    tiles.push_back(s4);

    static sf::Texture fibonacciTexture;
    fibonacciTexture.loadFromFile(resourcesPath + "/Assets/Images/Fibonacci.jpg");
    fibonacci.hide();
    fibonacci.setParent(*objects["content"]);
    fibonacci.setSize(sf::Vector2f(60.f, 60.f));
    fibonacci.setTexture(&fibonacciTexture);
    fibonacci.taskManager.setTaskContextData(this);

    highlight.autoDraw(true);
    highlight.setSize(sf::Vector2f(60.f, 60.f));
    highlight.setParent(*objects["content"]);
}

void MainWindow::CalculateLayout()
{
    int width{ static_cast<int>(window.getSize().x) };
    int height{ static_cast<int>(window.getSize().y) };

    float ratio{ 1920.f / 1080.f };
    if (width > height * ratio)
    {
        float newWidth{ height * ratio };
        objects["content"]->setScale(newWidth / 1920.f, height / 1080.f);
    }
    else
    {
        float newHeight{ width / ratio };
        objects["content"]->setScale(width / 1920.f, newHeight / 1080.f);
    }

    sf::FloatRect contentBounds{ objects["content"]->getGlobalBounds() };
    backgroundGray.setSize(sf::Vector2f(contentBounds.width, contentBounds.height));
    backgroundGray.setPosition(contentBounds.left, contentBounds.top);

    GameLoop();
}

void MainWindow::GameLoop()
{
    UpdateFrameRate();
    Scheduler::executeTasks();
    Paint();
}

void MainWindow::Paint()
{
    window.clear(windowColor);

    if (selectedLevel != -1)
    {
        three* level = &level1;
        switch (selectedLevel)
        {
            case 1:
            {
                level = &level1;
                break;
            }
            case 2:
            {
                level = &level2;
                break;
            }
        }

        for (int i{ 0 }; i < 32; i++)
        {
            for (int j{ 0 }; j < 18; j++)
            {
                int first = (*level).first[j][i];
                int second = (*level).second[j][i];

                tiles[first]->setRelativePosition(3.125f * i + 1.5625f, 5.55f * j + 2.5f);
                window.draw(*tiles[first]);

                if (second != -1)
                {
                    tiles[second]->setRelativePosition(3.125f * i + 1.5625f, 5.55f * j + 2.5f);
                    window.draw(*tiles[second]);
                }
            }
        }
    }

    backgroundAnimation.update(timeSinceLastDraw);
    Visible::drawVisibleObjects(window);

    if (fibonacci.isVisible()) window.draw(fibonacci);
    if (objects["backToMainMenu"]->isVisible())
    {
        window.draw(backgroundGray);
        window.draw(*objects["backToMainMenu"]);
        window.draw(*objects["resetLevel"]);
    }

    window.display();
}

void MainWindow::UpdateFrameRate()
{
    static sf::Clock clock;
    static int index{ 0 };
    timeSinceLastDraw = clock.restart().asSeconds();

    static float timeIntervals[60]{ 0 };
    timeIntervals[index++] = timeSinceLastDraw;
    if (index > 59) index = 0;

    float sum{ 0 };
    for (int i{ 0 }; i < 60; i++) sum += timeIntervals[i];
    averageFrameRate = static_cast<int>(1.f / (sum / 60.f));
}

void MainWindow::SwitchScreenMode()
{
    HWND hwnd = window.getSystemHandle();
    DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);

    if (dwStyle & WS_OVERLAPPEDWINDOW)
    {
        MONITORINFO mi = { sizeof(mi) };
        if (GetWindowPlacement(hwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY), &mi))
        {
            SetWindowLong(hwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
            SetWindowPos(hwnd, HWND_TOP,
                mi.rcMonitor.left,
                mi.rcMonitor.top,
                mi.rcMonitor.right - mi.rcMonitor.left,
                mi.rcMonitor.bottom - mi.rcMonitor.top,
                SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
        }
    }
    else
    {
        SetWindowLong(hwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
        SetWindowPlacement(hwnd, &wpPrev);
        SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
            SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    }

    CalculateLayout();
}

void MainWindow::OnMouseMove(int xPos, int yPos)
{
    Interactive::updateInteractives(Interactive::Event::Hover, xPos, yPos);
    if (selectedLevel != -1)
    {
        sf::FloatRect contentBounds{ objects["content"]->getGlobalBounds() };

        if (contentBounds.contains(xPos, yPos))
        {
            int i = (xPos - contentBounds.left) / (contentBounds.width * 0.03125f);
            int j = (yPos - contentBounds.top) / (contentBounds.height * 0.055f);

            if (j > 17) j = 17;
            mouseCoords = { i,j };

            three* level = &level1;
            switch (selectedLevel)
            {
                case 1:
                {
                    level = &level1;
                    break;
                }
                case 2:
                {
                    level = &level2;
                    break;
                }
            }

            ((Label*)objects["cost"])->setTextString(std::to_string((*level).cost[j][i]));
            highlight.setRelativePosition(3.125f * i + 1.5625f, 5.55f * j + 2.5f);
            highlight.setFillColor(sf::Color(255, 0, 0, 120));
            
            if (abs(whereIsFibonacci.y - j) == 0)
            {
                if (whereIsFibonacci.x > i)
                {
                    highlight.setFillColor(sf::Color(255, 0, 0, 120));

                    int cost{ step };
                    for (int k{ i }; k < whereIsFibonacci.x; k++)
                    {
                        cost -= (*level).cost[j][k];
                        if (cost < 0) break;
                    }
                    if (cost == 0) highlight.setFillColor(sf::Color(0, 255, 0, 120));
                }

                if (whereIsFibonacci.x < i)
                {
                    highlight.setFillColor(sf::Color(255, 0, 0, 120));

                    int cost{ step };
                    for (int k{ i }; k > whereIsFibonacci.x; k--)
                    {
                        cost -= (*level).cost[j][k];
                        if (cost < 0) break;
                    }
                    if (cost == 0) highlight.setFillColor(sf::Color(0, 255, 0, 120));
                }
            }

            if (abs(whereIsFibonacci.x - i) == 0)
            {
                if (whereIsFibonacci.y > j)
                {
                    highlight.setFillColor(sf::Color(255, 0, 0, 120));

                    int cost{ step };
                    for (int k{ j }; k < whereIsFibonacci.y; k++)
                    {
                        cost -= (*level).cost[k][i];
                        if (cost < 0) break;
                    }
                    if (cost == 0) highlight.setFillColor(sf::Color(0, 255, 0, 120));
                }
                if (whereIsFibonacci.y < j)
                {
                    highlight.setFillColor(sf::Color(255, 0, 0, 120));

                    int cost{ step };
                    for (int k{ j }; k > whereIsFibonacci.y; k--)
                    {
                        cost -= (*level).cost[k][i];
                        if (cost < 0) break;
                    }
                    if (cost == 0) highlight.setFillColor(sf::Color(0, 255, 0, 120));
                }
            }
        }
    }
}

void MainWindow::OnMouseDown(int xPos, int yPos)
{
    Interactive::updateInteractives(Interactive::Event::Press);

    if (selectedLevel != -1 && !objects["backToMainMenu"]->isVisible())
    {
        if (highlight.getFillColor() == sf::Color(0, 255, 0, 120))
        {
            fibonacci.taskManager.addTask
            (
                Time::Seconds(0.5f),
                [](float percentageComplete, void* taskContextData)
                {
                    MainWindow* window{ (MainWindow*)taskContextData };
                    Button* fibonacci{ &(window->fibonacci) };

                    static sf::Vector2f initialValuesA;
                    static sf::Vector2i initialValuesB;
                    if (percentageComplete == 0.f)
                    {
                        initialValuesA = fibonacci->getRelativePosition();
                        initialValuesB = window->mouseCoords;
                    }
                    if (percentageComplete == 1.f)
                    {
                        three* level = &level1;
                        switch (window->selectedLevel)
                        {
                            case 1:
                            {
                                level = &level1;
                                break;
                            }
                            case 2:
                            {
                                level = &level2;
                                break;
                            }
                        }

                        if ((*level).second[window->whereIsFibonacci.y][window->whereIsFibonacci.x] == 3)
                        {
                            window->objects["background"]->show();
                            window->objects["selectLevel"]->show();
                            window->objects["spiral"]->show();
                            window->objects["spiral1"]->show();
                            window->objects["spiral2"]->show();
                            window->objects["spiral3"]->show();
                            window->objects["spiral4"]->show();
                            window->objects["spiral5"]->show();
                            window->objects["level1"]->show();
                            window->objects["level2"]->show();
                            window->objects["level3"]->show();
                            window->objects["level4"]->show();
                            window->objects["level5"]->show();
                            window->objects["stepsText"]->hide();
                            window->objects["step"]->hide();
                            window->objects["costText"]->hide();
                            window->objects["cost"]->hide();
                            window->selectedLevel = -1;
                            window->highlight.hide();
                            window->fibonacci.hide();
                        }
                    }
                    
                    float x{ LinearInterpolation(initialValuesA.x, 3.125f * initialValuesB.x + 1.5625f, percentageComplete) };
                    float y{ LinearInterpolation(initialValuesA.y, 5.55f * initialValuesB.y + 2.5f, percentageComplete) };
                    fibonacci->setRelativePosition(x, y);
                }
            );
            int temp{ lastStep };
            lastStep = step;
            step = temp + step;
            ((Label*)objects["step"])->setTextString(std::to_string(step));
            whereIsFibonacci = mouseCoords;
            highlight.setFillColor(sf::Color(255, 0, 0, 120));
        }
    }
}

void MainWindow::OnMouseUp(int xPos, int yPos)
{
    Interactive::updateInteractives(Interactive::Event::Release);
}

void MainWindow::OnEscapeDown()
{
    if (objects["english"]->isVisible())
    {
        objects["english"]->hide();
        objects["romanian"]->hide();
        objects["title"]->show();
        objects["start"]->show();
        objects["settings"]->show();
        objects["language"]->show();
        objects["exit"]->show();
    }
    else if (objects["spiral"]->isVisible())
    {
        objects["selectLevel"]->hide();
        objects["spiral"]->hide();
        objects["spiral1"]->hide();
        objects["spiral2"]->hide();
        objects["spiral3"]->hide();
        objects["spiral4"]->hide();
        objects["spiral5"]->hide();
        objects["level1"]->hide();
        objects["level2"]->hide();
        objects["level3"]->hide();
        objects["level4"]->hide();
        objects["level5"]->hide();
        objects["title"]->show();
        objects["start"]->show();
        objects["settings"]->show();
        objects["language"]->show();
        objects["exit"]->show();

        ((Button*)objects["level1"])->onHover(-1,-1);
        ((Button*)objects["level2"])->onHover(-1,-1);
        ((Button*)objects["level3"])->onHover(-1,-1);
        ((Button*)objects["level4"])->onHover(-1,-1);
        ((Button*)objects["level5"])->onHover(-1,-1);
    }
    else if (objects["fullscreen"]->isVisible())
    {
        objects["fullscreen"]->hide();
        objects["fullscreenOption"]->hide();
        objects["title"]->show();
        objects["start"]->show();
        objects["settings"]->show();
        objects["language"]->show();
        objects["exit"]->show();
    }
    else if (selectedLevel != -1)
    {
        if (objects["backToMainMenu"]->isVisible())
        {
            objects["backToMainMenu"]->hide();
            objects["resetLevel"]->hide();
            highlight.show();
        }
        else
        {
            objects["backToMainMenu"]->show();
            objects["resetLevel"]->show();
            highlight.hide();
        }
    }

    Interactive::updateInteractives(Interactive::Event::Hover, -1, -1);
    Interactive::updateInteractives(Interactive::Event::Press);
    Interactive::updateInteractives(Interactive::Event::Release);
}

void MainWindow::UpdateLanguage()
{
    ((Button*)objects["start"])->setTextString(strings[stringIndex["start"]][language]);
    ((Button*)objects["settings"])->setTextString(strings[stringIndex["settings"]][language]);
    ((Button*)objects["language"])->setTextString(strings[stringIndex["language"]][language]);
    ((Button*)objects["exit"])->setTextString(strings[stringIndex["exit"]][language]);
    ((Button*)objects["fullscreen"])->setTextString(strings[stringIndex["fullscreen"]][language]);
    ((Button*)objects["backToMainMenu"])->setTextString(strings[stringIndex["backToMainMenu"]][language]);
    ((Button*)objects["resetLevel"])->setTextString(strings[stringIndex["resetLevel"]][language]);
    ((Button*)objects["stepsText"])->setTextString(strings[stringIndex["stepsText"]][language]);
    ((Button*)objects["selectLevel"])->setTextString(strings[stringIndex["selectLevel"]][language]);
}