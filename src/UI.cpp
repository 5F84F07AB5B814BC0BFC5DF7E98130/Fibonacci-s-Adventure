#include "MainWindow.h"
#include "Utility.h"

void MainWindow::InitializeUIAndSettings()
{
    objects["background"] = new DynamicObject;
    objects["background"]->setParent(*objects["content"]);
    objects["background"]->autoDraw(true);
    objects["background"]->setRelativePosition(50.f, 50.f);
    objects["background"]->setSize(sf::Vector2f(1920, 1080));
    backgroundAnimation.setTarget(objects["background"]);

    objects["spiral"] = new DynamicObject;
    objects["spiral"]->setParent(*objects["content"]);
    objects["spiral"]->autoDraw(true);
    objects["spiral"]->hide();
    objects["spiral"]->setRelativePosition(50.f, 60.f);
    objects["spiral"]->setSize(sf::Vector2f(900, 600));
    static sf::Texture spiralTexture;
    spiralTexture.loadFromFile(resourcesPath + "/Assets/Images/Spiral/spiral.png");
    objects["spiral"]->setTexture(&spiralTexture);

    objects["spiral1"] = new DynamicObject;
    objects["spiral1"]->setParent(*objects["content"]);
    objects["spiral1"]->autoDraw(true);
    objects["spiral1"]->hide();
    objects["spiral1"]->setRelativePosition(50.f, 60.f);
    objects["spiral1"]->setSize(sf::Vector2f(900, 600));
    static sf::Texture spiral1Texture;
    spiral1Texture.loadFromFile(resourcesPath + "/Assets/Images/Spiral/1.png");
    objects["spiral1"]->setTexture(&spiral1Texture);
    objects["spiral1"]->setFillColor(sf::Color(255,255,255,160));

    objects["spiral2"] = new DynamicObject;
    objects["spiral2"]->setParent(*objects["content"]);
    objects["spiral2"]->autoDraw(true);
    objects["spiral2"]->hide();
    objects["spiral2"]->setRelativePosition(50.f, 60.f);
    objects["spiral2"]->setSize(sf::Vector2f(900, 600));
    static sf::Texture spiral2Texture;
    spiral2Texture.loadFromFile(resourcesPath + "/Assets/Images/Spiral/2.png");
    objects["spiral2"]->setTexture(&spiral2Texture);
    objects["spiral2"]->setFillColor(sf::Color(255, 255, 255, 160));

    objects["spiral3"] = new DynamicObject;
    objects["spiral3"]->setParent(*objects["content"]);
    objects["spiral3"]->autoDraw(true);
    objects["spiral3"]->hide();
    objects["spiral3"]->setRelativePosition(50.f, 60.f);
    objects["spiral3"]->setSize(sf::Vector2f(900, 600));
    static sf::Texture spiral3Texture;
    spiral3Texture.loadFromFile(resourcesPath + "/Assets/Images/Spiral/3.png");
    objects["spiral3"]->setTexture(&spiral3Texture);
    objects["spiral3"]->setFillColor(sf::Color(255, 255, 255, 160));

    objects["spiral4"] = new DynamicObject;
    objects["spiral4"]->setParent(*objects["content"]);
    objects["spiral4"]->autoDraw(true);
    objects["spiral4"]->hide();
    objects["spiral4"]->setRelativePosition(50.f, 60.f);
    objects["spiral4"]->setSize(sf::Vector2f(900, 600));
    static sf::Texture spiral4Texture;
    spiral4Texture.loadFromFile(resourcesPath + "/Assets/Images/Spiral/4.png");
    objects["spiral4"]->setTexture(&spiral4Texture);
    objects["spiral4"]->setFillColor(sf::Color(255, 255, 255, 160));

    objects["spiral5"] = new DynamicObject;
    objects["spiral5"]->setParent(*objects["content"]);
    objects["spiral5"]->autoDraw(true);
    objects["spiral5"]->hide();
    objects["spiral5"]->setRelativePosition(50.f, 60.f);
    objects["spiral5"]->setSize(sf::Vector2f(900, 600));
    static sf::Texture spiral5Texture;
    spiral5Texture.loadFromFile(resourcesPath + "/Assets/Images/Spiral/5.png");
    objects["spiral5"]->setTexture(&spiral5Texture);
    objects["spiral5"]->setFillColor(sf::Color(255, 255, 255, 160));

    Button* start{ new Button };
    objects["start"] = start;
    start->autoDraw(true);
    start->setParent(*objects["content"]);
    start->setSize(sf::Vector2f(400.f, 80.f));
    start->setTextSize(80.f);
    start->setRelativePosition(17.f, 45.f);
    start->setFillColor(sf::Color::Transparent);
    start->setTextFont(resourcesPath + "/Assets/Fonts/DK Brushzilla.otf");
    start->setTextFillColor(sf::Color::White);
    start->taskManager.setTaskContextData(start);
    start->setBehaviorContextData(this);
    start->setHoverBehavior
    (
        [](Interactive::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };
            Button* newGame{ (Button*)window->objects["start"] };

            static int runningTaskId{ -1 };
            newGame->taskManager.killTask(runningTaskId);

            if (transition == Interactive::Direction::In)
            {
                runningTaskId = newGame->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        Button* newGame{ (Button*)taskContextData };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)newGame;
                        }

                        newGame->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color(100, 100, 100), percentageComplete));
                    }
                );
            }
            else
            {
                runningTaskId = newGame->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        Button* newGame{ (Button*)taskContextData };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)newGame;
                        }

                        newGame->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color::White, percentageComplete));
                    }
                );
            }
        }
    );
    start->setPressBehavior
    (
        [](Button::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };

            if (transition == Button::Direction::In)
            {
                window->objects["title"]->hide();
                window->objects["start"]->hide();
                window->objects["settings"]->hide();
                window->objects["language"]->hide();
                window->objects["exit"]->hide();
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
            }
        }
    );

    Button* settings{ new Button };
    objects["settings"] = settings;
    *settings = *start;
    settings->autoDraw(true);
    settings->setRelativePosition(17.f, 55.f);
    settings->taskManager.setTaskContextData(settings);
    settings->setHoverBehavior
    (
        [](Interactive::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };
            Button* settings{ (Button*)window->objects["settings"] };

            static int runningTaskId{ -1 };
            settings->taskManager.killTask(runningTaskId);

            if (transition == Interactive::Direction::In)
            {
                runningTaskId = settings->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        Button* settings{ (Button*)taskContextData };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)settings;
                        }

                        settings->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color(100, 100, 100), percentageComplete));
                    }
                );
            }
            else
            {
                runningTaskId = settings->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        Button* settings{ (Button*)taskContextData };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)settings;
                        }

                        settings->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color::White, percentageComplete));
                    }
                );
            }
        }
    );
    settings->setPressBehavior
    (
        [](Button::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };

            if (transition == Button::Direction::In)
            {
                window->objects["title"]->hide();
                window->objects["start"]->hide();
                window->objects["settings"]->hide();
                window->objects["language"]->hide();
                window->objects["exit"]->hide();
                window->objects["fullscreen"]->show();
                window->objects["fullscreenOption"]->show();
            }
        }
    );

    Button* language{ new Button };
    objects["language"] = language;
    *language = *start;
    language->autoDraw(true);
    language->setRelativePosition(17.f, 65.f);
    language->taskManager.setTaskContextData(language);
    language->setHoverBehavior
    (
        [](Interactive::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };
            Button* language{ (Button*)window->objects["language"] };

            static int runningTaskId{ -1 };
            language->taskManager.killTask(runningTaskId);

            if (transition == Interactive::Direction::In)
            {
                runningTaskId = language->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        Button* language{ (Button*)taskContextData };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)language;
                        }

                        language->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color(100, 100, 100), percentageComplete));
                    }
                );
            }
            else
            {
                runningTaskId = language->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        Button* language{ (Button*)taskContextData };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)language;
                        }

                        language->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color::White, percentageComplete));
                    }
                );
            }
        }
    );
    language->setPressBehavior
    (
        [](Button::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };

            if (transition == Button::Direction::In)
            {
                window->objects["title"]->hide();
                window->objects["start"]->hide();
                window->objects["settings"]->hide();
                window->objects["language"]->hide();
                window->objects["exit"]->hide();
                window->objects["english"]->show();
                window->objects["romanian"]->show();
            }
        }
    );

    Button* exit{ new Button };
    objects["exit"] = exit;
    *exit = *start;
    exit->autoDraw(true);
    exit->setRelativePosition(17.f, 75.f);
    exit->taskManager.setTaskContextData(exit);
    exit->setHoverBehavior
    (
        [](Interactive::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };
            Button* exit{ (Button*)window->objects["exit"] };

            static int runningTaskId{ -1 };
            exit->taskManager.killTask(runningTaskId);

            if (transition == Interactive::Direction::In)
            {
                runningTaskId = exit->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        Button* exit{ (Button*)taskContextData };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)exit;
                        }

                        exit->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color(100, 100, 100), percentageComplete));
                    }
                );
            }
            else
            {
                runningTaskId = exit->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        Button* exit{ (Button*)taskContextData };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)exit;
                        }

                        exit->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color::White, percentageComplete));
                    }
                );
            }
        }
    );
    exit->setPressBehavior
    (
        [](Button::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };

            DestroyWindow(window->window.getSystemHandle());
        }
    );


    Button* english{ new Button };
    objects["english"] = english;
    *english = *start;
    english->autoDraw(true);
    english->hide();
    english->setTextSize(100.f);
    english->setRelativePosition(15.f, 40.f);
    english->setTextString("English");
    english->taskManager.setTaskContextData(this);
    english->setHoverBehavior
    (
        [](Interactive::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };
            Button* english{ (Button*)window->objects["english"] };

            static int runningTaskId{ -1 };
            english->taskManager.killTask(runningTaskId);

            if (transition == Interactive::Direction::In)
            {
                runningTaskId = english->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        MainWindow* window{ (MainWindow*)taskContextData };
                        Button* english{ (Button*)window->objects["english"] };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)english;
                        }

                        english->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color(100, 100, 100), percentageComplete));
                    }
                );
            }
            else
            {
                runningTaskId = english->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        MainWindow* window{ (MainWindow*)taskContextData };
                        Button* english{ (Button*)window->objects["english"] };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)english;
                        }

                        english->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color::White, percentageComplete));
                    }
                );
            }
        }
    );
    english->setPressBehavior
    (
        [](Button::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };
            Button* english{ (Button*)window->objects["english"] };

            if (transition == Interactive::Direction::In)
            {
                english->taskManager.addTask
                (
                    Time::Seconds(0.1f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        MainWindow* window{ (MainWindow*)taskContextData };
                        Button* english{ (Button*)window->objects["english"] };
                        Button* romanian{ (Button*)window->objects["romanian"] };

                        static Label initialValuesEnglish;
                        static Label initialValuesRomanian;
                        if (percentageComplete == 0.f)
                        {
                            initialValuesEnglish = *(Label*)english;
                            initialValuesRomanian = *(Label*)romanian;
                        }

                        english->setTextSize(LinearInterpolation(initialValuesEnglish.getTextSize(), 100.f, percentageComplete));
                        romanian->setTextSize(LinearInterpolation(initialValuesRomanian.getTextSize(), 80.f, percentageComplete));
                    }
                );
            }

            window->language = 0;
            window->UpdateLanguage();
        }
    );

    Button* romanian{ new Button };
    objects["romanian"] = romanian;
    *romanian = *start;
    romanian->autoDraw(true);
    romanian->hide();
    romanian->setRelativePosition(15.f, 60.f);
    romanian->setTextString("Romana");
    romanian->taskManager.setTaskContextData(this);
    romanian->setHoverBehavior
    (
        [](Interactive::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };
            Button* romanian{ (Button*)window->objects["romanian"] };

            static int runningTaskId{ -1 };
            romanian->taskManager.killTask(runningTaskId);

            if (transition == Interactive::Direction::In)
            {
                runningTaskId = romanian->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        MainWindow* window{ (MainWindow*)taskContextData };
                        Button* romanian{ (Button*)window->objects["romanian"] };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)romanian;
                        }

                        romanian->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color(100, 100, 100), percentageComplete));
                    }
                );
            }
            else
            {
                runningTaskId = romanian->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        MainWindow* window{ (MainWindow*)taskContextData };
                        Button* romanian{ (Button*)window->objects["romanian"] };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)romanian;
                        }

                        romanian->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color::White, percentageComplete));
                    }
                );
            }
        }
    );
    romanian->setPressBehavior
    (
        [](Button::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };
            Button* romanian{ (Button*)window->objects["romanian"] };

            if (transition == Interactive::Direction::In)
            {
                romanian->taskManager.addTask
                (
                    Time::Seconds(0.1f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        MainWindow* window{ (MainWindow*)taskContextData };
                        Button* english{ (Button*)window->objects["english"] };
                        Button* romanian{ (Button*)window->objects["romanian"] };

                        static Label initialValuesEnglish;
                        static Label initialValuesRomanian;
                        if (percentageComplete == 0.f)
                        {
                            initialValuesEnglish = *(Label*)english;
                            initialValuesRomanian = *(Label*)romanian;
                        }

                        english->setTextSize(LinearInterpolation(initialValuesEnglish.getTextSize(), 80.f, percentageComplete));
                        romanian->setTextSize(LinearInterpolation(initialValuesRomanian.getTextSize(), 100.f, percentageComplete));
                    }
                );
            }

            window->language = 1;
            window->UpdateLanguage();
        }
    );

    Label* fullscreen{ new Label };
    objects["fullscreen"] = fullscreen;
    fullscreen->autoDraw(true);
    fullscreen->setParent(*objects["content"]);
    fullscreen->setSize(sf::Vector2f(400.f, 80.f));
    fullscreen->setTextSize(80.f);
    fullscreen->setRelativePosition(15.f, 35.f);
    fullscreen->setFillColor(sf::Color::Transparent);
    fullscreen->setTextFont(resourcesPath + "/Assets/Fonts/DK Brushzilla.otf");
    fullscreen->setTextFillColor(sf::Color::White);
    fullscreen->hide();

    Button* fullscreenOption{ new Button };
    objects["fullscreenOption"] = fullscreenOption;
    *fullscreenOption = *start;
    fullscreenOption->autoDraw(true);
    fullscreenOption->hide();
    fullscreenOption->setTextString("On");
    fullscreenOption->setSize(sf::Vector2f(200.f, 80.f));
    fullscreenOption->setRelativePosition(35.f, 35.f);
    fullscreenOption->taskManager.setTaskContextData(fullscreenOption);
    fullscreenOption->setHoverBehavior
    (
        [](Interactive::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };
            Button* fullscreenOption{ (Button*)window->objects["fullscreenOption"] };

            static int runningTaskId{ -1 };
            fullscreenOption->taskManager.killTask(runningTaskId);

            if (transition == Interactive::Direction::In)
            {
                runningTaskId = fullscreenOption->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        Button* fullscreenOption{ (Button*)taskContextData };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)fullscreenOption;
                        }

                        fullscreenOption->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color(100, 100, 100), percentageComplete));
                    }
                );
            }
            else
            {
                runningTaskId = fullscreenOption->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        Button* fullscreenOption{ (Button*)taskContextData };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)fullscreenOption;
                        }

                        fullscreenOption->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color::White, percentageComplete));
                    }
                );
            }
        }
    );
    fullscreenOption->setPressBehavior
    (
        [](Button::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };

            if (transition == Button::Direction::In)
            {
                window->SwitchScreenMode();
                if (((Button*)window->objects["fullscreenOption"])->getTextString() == "On")
                {
                    ((Button*)window->objects["fullscreenOption"])->setTextString("Off");
                }
                else
                {
                    ((Button*)window->objects["fullscreenOption"])->setTextString("On");
                }
            }
        }
    );

    Button* level1{ new Button };
    objects["level1"] = level1;
    *level1 = *start;
    level1->autoDraw(true);
    level1->hide();
    level1->setParent(*objects["spiral"]);
    level1->setSize(sf::Vector2f(400.f, 450.f));
    level1->setRelativePosition(38.f, 60.f);
    level1->taskManager.setTaskContextData(this);
    level1->setHoverBehavior
    (
        [](Interactive::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };
            Button* level1{ (Button*)window->objects["level1"] };

            static int runningTaskId{ -1 };
            level1->taskManager.killTask(runningTaskId);

            if (transition == Interactive::Direction::In)
            {
                runningTaskId = level1->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        MainWindow* window{ (MainWindow*)taskContextData };

                        static sf::Color initialColor;
                        if (percentageComplete == 0.f)
                        {
                            initialColor = window->objects["spiral1"]->getFillColor();
                        }

                        window->objects["spiral1"]->setFillColor(LinearInterpolation(initialColor, sf::Color(100, 100, 100, 160), percentageComplete));
                    }
                );
            }
            else
            {
                runningTaskId = level1->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        MainWindow* window{ (MainWindow*)taskContextData };

                        static sf::Color initialColor;
                        if (percentageComplete == 0.f)
                        {
                            initialColor = window->objects["spiral1"]->getFillColor();
                        }

                        window->objects["spiral1"]->setFillColor(LinearInterpolation(initialColor, sf::Color(255, 255, 255, 160), percentageComplete));
                    }
                );
            }
        }
    );
    level1->setPressBehavior
    (
        [](Button::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };

            if (transition == Button::Direction::In)
            {
                window->objects["background"]->hide();
                window->objects["selectLevel"]->hide();
                window->objects["spiral"]->hide();
                window->objects["spiral1"]->hide();
                window->objects["spiral2"]->hide();
                window->objects["spiral3"]->hide();
                window->objects["spiral4"]->hide();
                window->objects["spiral5"]->hide();
                window->objects["level1"]->hide();
                window->objects["level2"]->hide();
                window->objects["level3"]->hide();
                window->objects["level4"]->hide();
                window->objects["level5"]->hide();
                window->objects["stepsText"]->show();
                window->objects["step"]->show();
                window->objects["costText"]->show();
                window->objects["cost"]->show();
                window->selectedLevel = 1;
                window->highlight.show();
                window->fibonacci.show();
                int i{ 16 };
                int j{ 7 };
                window->whereIsFibonacci = { i,j };
                window->fibonacci.setRelativePosition(3.125f * i + 1.5625f, 5.55f * j + 2.5f);
                window->step = 1;
                window->lastStep = 0;
                ((Label*)window->objects["step"])->setTextString("1");
            }
        }
    );

    Button* level2{ new Button };
    objects["level2"] = level2;
    *level2 = *level1;
    level2->autoDraw(true);
    level2->hide();
    level2->setParent(*objects["spiral"]);
    level2->setSize(sf::Vector2f(290.f, 270.f));
    level2->setRelativePosition(78.f, 37.f);
    level2->taskManager.setTaskContextData(this);
    level2->setHoverBehavior
    (
        [](Interactive::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };
            Button* level2{ (Button*)window->objects["level2"] };

            static int runningTaskId{ -1 };
            level2->taskManager.killTask(runningTaskId);

            if (transition == Interactive::Direction::In)
            {
                runningTaskId = level2->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        MainWindow* window{ (MainWindow*)taskContextData };

                        static sf::Color initialColor;
                        if (percentageComplete == 0.f)
                        {
                            initialColor = window->objects["spiral2"]->getFillColor();
                        }

                        window->objects["spiral2"]->setFillColor(LinearInterpolation(initialColor, sf::Color(100, 100, 100, 160), percentageComplete));
                    }
                );
            }
            else
            {
                runningTaskId = level2->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        MainWindow* window{ (MainWindow*)taskContextData };

                        static sf::Color initialColor;
                        if (percentageComplete == 0.f)
                        {
                            initialColor = window->objects["spiral2"]->getFillColor();
                        }

                        window->objects["spiral2"]->setFillColor(LinearInterpolation(initialColor, sf::Color(255, 255, 255, 160), percentageComplete));
                    }
                );
            }
        }
    );
    level2->setPressBehavior
    (
        [](Button::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };

            if (transition == Button::Direction::In)
            {
                window->objects["background"]->hide();
                window->objects["selectLevel"]->hide();
                window->objects["spiral"]->hide();
                window->objects["spiral1"]->hide();
                window->objects["spiral2"]->hide();
                window->objects["spiral3"]->hide();
                window->objects["spiral4"]->hide();
                window->objects["spiral5"]->hide();
                window->objects["level1"]->hide();
                window->objects["level2"]->hide();
                window->objects["level3"]->hide();
                window->objects["level4"]->hide();
                window->objects["level5"]->hide();
                window->objects["stepsText"]->show();
                window->objects["step"]->show();
                window->objects["costText"]->show();
                window->objects["cost"]->show();
                window->selectedLevel = 2;
                window->highlight.show();
                window->fibonacci.show();
                int i{ 13 };
                int j{ 5 };
                window->whereIsFibonacci = { i,j };
                window->fibonacci.setRelativePosition(3.125f * i + 1.5625f, 5.55f * j + 2.5f);
                window->step = 1;
                window->lastStep = 0;
                ((Label*)window->objects["step"])->setTextString("1");
            }
        }
    );

    Button* level3{ new Button };
    objects["level3"] = level3;
    *level3 = *level1;
    level3->autoDraw(true);
    level3->hide();
    level3->setParent(*objects["spiral"]);
    level3->setSize(sf::Vector2f(190.f, 173.f));
    level3->setRelativePosition(86.f, 76.f);
    level3->taskManager.setTaskContextData(this);
    level3->setHoverBehavior
    (
        [](Interactive::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };
            Button* level3{ (Button*)window->objects["level3"] };

            static int runningTaskId{ -1 };
            level3->taskManager.killTask(runningTaskId);

            if (transition == Interactive::Direction::In)
            {
                runningTaskId = level3->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        MainWindow* window{ (MainWindow*)taskContextData };

                        static sf::Color initialColor;
                        if (percentageComplete == 0.f)
                        {
                            initialColor = window->objects["spiral3"]->getFillColor();
                        }

                        window->objects["spiral3"]->setFillColor(LinearInterpolation(initialColor, sf::Color(100, 100, 100, 160), percentageComplete)); 
                    }
                );
            }
            else
            {
                runningTaskId = level3->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        MainWindow* window{ (MainWindow*)taskContextData };

                        static sf::Color initialColor;
                        if (percentageComplete == 0.f)
                        {
                            initialColor = window->objects["spiral3"]->getFillColor();
                        }

                        window->objects["spiral3"]->setFillColor(LinearInterpolation(initialColor, sf::Color(255, 255, 255, 160), percentageComplete));
                    }
                );
            }
        }
    );
    level3->setPressBehavior
    (
        [](Button::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };

            if (transition == Button::Direction::In)
            {

            }
        }
    );

    Button* level4{ new Button };
    objects["level4"] = level4;
    *level4 = *level1;
    level4->autoDraw(true);
    level4->hide();
    level4->setParent(*objects["spiral"]);
    level4->setSize(sf::Vector2f(100.f, 100.f));
    level4->setRelativePosition(69.f, 84.f);
    level4->taskManager.setTaskContextData(this);
    level4->setHoverBehavior
    (
        [](Interactive::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };
            Button* level4{ (Button*)window->objects["level4"] };

            static int runningTaskId{ -1 };
            level4->taskManager.killTask(runningTaskId);

            if (transition == Interactive::Direction::In)
            {
                runningTaskId = level4->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        MainWindow* window{ (MainWindow*)taskContextData };

                        static sf::Color initialColor;
                        if (percentageComplete == 0.f)
                        {
                            initialColor = window->objects["spiral4"]->getFillColor();
                        }

                        window->objects["spiral4"]->setFillColor(LinearInterpolation(initialColor, sf::Color(100, 100, 100, 160), percentageComplete));
                    }
                );
            }
            else
            {
                runningTaskId = level4->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        MainWindow* window{ (MainWindow*)taskContextData };

                        static sf::Color initialColor;
                        if (percentageComplete == 0.f)
                        {
                            initialColor = window->objects["spiral4"]->getFillColor();
                        }

                        window->objects["spiral4"]->setFillColor(LinearInterpolation(initialColor, sf::Color(255, 255, 255, 160), percentageComplete));
                    }
                );
            }
        }
    );
    level4->setPressBehavior
    (
        [](Button::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };

            if (transition == Button::Direction::In)
            {

            }
        }
    );
    Button* level5{ new Button };
    objects["level5"] = level5;
    *level5 = *level1;
    level5->autoDraw(true);
    level5->hide();
    level5->setParent(*objects["spiral"]);
    level5->setSize(sf::Vector2f(78.f, 70.f));
    level5->setRelativePosition(70.f, 68.f);
    level5->taskManager.setTaskContextData(this);
    level5->setHoverBehavior
    (
        [](Interactive::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };
            Button* level5{ (Button*)window->objects["level5"] };

            static int runningTaskId{ -1 };
            level5->taskManager.killTask(runningTaskId);

            if (transition == Interactive::Direction::In)
            {
                runningTaskId = level5->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        MainWindow* window{ (MainWindow*)taskContextData };

                        static sf::Color initialColor;
                        if (percentageComplete == 0.f)
                        {
                            initialColor = window->objects["spiral5"]->getFillColor();
                        }

                        window->objects["spiral5"]->setFillColor(LinearInterpolation(initialColor, sf::Color(100, 100, 100, 160), percentageComplete));
                    }
                );
            }
            else
            {
                runningTaskId = level5->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        MainWindow* window{ (MainWindow*)taskContextData };

                        static sf::Color initialColor;
                        if (percentageComplete == 0.f)
                        {
                            initialColor = window->objects["spiral5"]->getFillColor();
                        }

                        window->objects["spiral5"]->setFillColor(LinearInterpolation(initialColor, sf::Color(255, 255, 255, 160), percentageComplete));
                    }
                );
            }
        }
    );
    level5->setPressBehavior
    (
        [](Button::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };

            if (transition == Button::Direction::In)
            {

            }
        }
    );

    Button* backToMainMenu{ new Button };
    objects["backToMainMenu"] = backToMainMenu;
    *backToMainMenu = *start;
    backToMainMenu->hide();
    backToMainMenu->setRelativePosition(50.f, 45.f);
    backToMainMenu->taskManager.setTaskContextData(backToMainMenu);
    backToMainMenu->setHoverBehavior
    (
        [](Interactive::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };
            Button* backToMainMenu{ (Button*)window->objects["backToMainMenu"] };

            static int runningTaskId{ -1 };
            backToMainMenu->taskManager.killTask(runningTaskId);

            if (transition == Interactive::Direction::In)
            {
                runningTaskId = backToMainMenu->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        Button* backToMainMenu{ (Button*)taskContextData };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)backToMainMenu;
                        }

                        backToMainMenu->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color(100, 100, 100), percentageComplete));
                    }
                );
            }
            else
            {
                runningTaskId = backToMainMenu->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        Button* backToMainMenu{ (Button*)taskContextData };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)backToMainMenu;
                        }

                        backToMainMenu->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color::White, percentageComplete));
                    }
                );
            }
        }
    );
    backToMainMenu->setPressBehavior
    (
        [](Button::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };

            if (transition == Button::Direction::In)
            {
                window->objects["title"]->show();
                window->objects["start"]->show();
                window->objects["settings"]->show();
                window->objects["language"]->show();
                window->objects["exit"]->show();
                window->objects["background"]->show();
                window->objects["backToMainMenu"]->hide();
                window->objects["resetLevel"]->hide();
                window->objects["stepsText"]->hide();
                window->objects["step"]->hide();
                window->objects["costText"]->hide();
                window->objects["cost"]->hide();
                window->fibonacci.hide();
                window->selectedLevel = -1;
            }
        }
    );

    Button* resetLevel{ new Button };
    objects["resetLevel"] = resetLevel;
    *resetLevel = *start;
    resetLevel->hide();
    resetLevel->setRelativePosition(50.f, 55.f);
    resetLevel->taskManager.setTaskContextData(resetLevel);
    resetLevel->setHoverBehavior
    (
        [](Interactive::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };
            Button* resetLevel{ (Button*)window->objects["resetLevel"] };

            static int runningTaskId{ -1 };
            resetLevel->taskManager.killTask(runningTaskId);

            if (transition == Interactive::Direction::In)
            {
                runningTaskId = resetLevel->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        Button* resetLevel{ (Button*)taskContextData };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)resetLevel;
                        }

                        resetLevel->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color(100, 100, 100), percentageComplete));
                    }
                );
            }
            else
            {
                runningTaskId = resetLevel->taskManager.addTask
                (
                    Time::Seconds(0.2f),
                    [](float percentageComplete, void* taskContextData)
                    {
                        Button* resetLevel{ (Button*)taskContextData };

                        static Label initialValues;
                        if (percentageComplete == 0.f)
                        {
                            initialValues = *(Label*)resetLevel;
                        }

                        resetLevel->setTextFillColor(LinearInterpolation(initialValues.getTextFillColor(), sf::Color::White, percentageComplete));
                    }
                );
            }
        }
    );
    resetLevel->setPressBehavior
    (
        [](Button::Direction transition, void* behaviorContextData)
        {
            if (!behaviorContextData) return;
            MainWindow* window{ (MainWindow*)behaviorContextData };

            if (transition == Button::Direction::In)
            {
                window->highlight.show();
                window->objects["backToMainMenu"]->hide();
                window->objects["resetLevel"]->hide();
                ((Label*)window->objects["step"])->setTextString("1");
                window->step = 1;
                window->lastStep = 0;

                switch (window->selectedLevel)
                {
                    case 1:
                    {
                        int i{ 16 };
                        int j{ 7 };
                        window->whereIsFibonacci = { i,j };
                        window->fibonacci.setRelativePosition(3.125f * i + 1.5625f, 5.55f * j + 2.5f);
                        break;
                    }
                    case 2:
                    {
                        int i{ 13 };
                        int j{ 5 };
                        window->whereIsFibonacci = { i,j };
                        window->fibonacci.setRelativePosition(3.125f * i + 1.5625f, 5.55f * j + 2.5f);
                        break;
                    }
                }
            }
        }
    );

    Label* stepsText{ new Label };
    objects["stepsText"] = stepsText;
    stepsText->autoDraw(true);
    stepsText->setParent(*objects["content"]);
    stepsText->setSize(sf::Vector2f(400.f, 80.f));
    stepsText->setTextSize(80.f);
    stepsText->setRelativePosition(35.f, 70.f);
    stepsText->setFillColor(sf::Color::Transparent);
    stepsText->setTextFont(resourcesPath + "/Assets/Fonts/DK Brushzilla.otf");
    stepsText->setTextFillColor(sf::Color::White);
    stepsText->hide();

    Label* step{ new Label };
    objects["step"] = step;
    step->autoDraw(true);
    step->setParent(*objects["content"]);
    step->setSize(sf::Vector2f(400.f, 80.f));
    step->setTextSize(80.f);
    step->setTextString("1");
    step->setRelativePosition(35.f, 75.f);
    step->setFillColor(sf::Color::Transparent);
    step->setTextFont(resourcesPath + "/Assets/Fonts/Alkatra-Bold.ttf");
    step->setTextStyle(sf::Text::Style::Bold);
    step->setTextFillColor(sf::Color::White);
    step->hide();

    Label* costText{ new Label };
    objects["costText"] = costText;
    costText->autoDraw(true);
    costText->setParent(*objects["content"]);
    costText->setSize(sf::Vector2f(400.f, 80.f));
    costText->setTextSize(80.f);
    costText->setTextString("Cost");
    costText->setRelativePosition(65.f, 70.f);
    costText->setFillColor(sf::Color::Transparent);
    costText->setTextFont(resourcesPath + "/Assets/Fonts/DK Brushzilla.otf");
    costText->setTextFillColor(sf::Color::White);
    costText->hide();

    Label* cost{ new Label };
    objects["cost"] = cost;
    cost->autoDraw(true);
    cost->setParent(*objects["content"]);
    cost->setSize(sf::Vector2f(400.f, 80.f));
    cost->setTextSize(80.f);
    cost->setTextString("1");
    cost->setRelativePosition(65.f, 75.f);
    cost->setFillColor(sf::Color::Transparent);
    cost->setTextFont(resourcesPath + "/Assets/Fonts/Alkatra-Bold.ttf");
    cost->setTextStyle(sf::Text::Style::Bold);
    cost->setTextFillColor(sf::Color::White);
    cost->hide();

    Label* selectLevel{ new Label };
    objects["selectLevel"] = selectLevel;
    selectLevel->autoDraw(true);
    selectLevel->setParent(*objects["content"]);
    selectLevel->setSize(sf::Vector2f(400.f, 100.f));
    selectLevel->setTextSize(80.f);
    selectLevel->setRelativePosition(50.f, 20.f);
    selectLevel->setFillColor(sf::Color::Transparent);
    selectLevel->setTextFont(resourcesPath + "/Assets/Fonts/DK Brushzilla.otf");
    selectLevel->setTextStyle(sf::Text::Style::Bold);
    selectLevel->setTextFillColor(sf::Color::White);
    selectLevel->hide();

    Label* title{ new Label };
    objects["title"] = title;
    title->autoDraw(true);
    title->setParent(*objects["content"]);
    title->setSize(sf::Vector2f(400.f, 150.f));
    title->setTextSize(80.f);
    title->setTextString("Fibonacci's\n     Adventure");
    title->setRelativePosition(20.f, 18.f);
    title->setFillColor(sf::Color::Transparent);
    title->setTextFont(resourcesPath + "/Assets/Fonts/Sucesion-slab-font-FFP.otf");
    title->setTextFillColor(sf::Color::White);

    backgroundGray.setFillColor(sf::Color(60, 60, 60, 120));
}