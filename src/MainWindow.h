#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include "Button.h"
#include "Animation.h"

class MainWindow
{
public:

    sf::RenderWindow window;
    WINDOWPLACEMENT wpPrev{ sizeof(wpPrev) };
    std::string resourcesPath;
    int edge{ 0 };

    std::map<std::string, DynamicObject*> objects;

    Animation backgroundAnimation;
    sf::Color windowColor;

    //fibonacci
    Button fibonacci;
    sf::Vector2i whereIsFibonacci;
    sf::Vector2i mouseCoords;
    int step;
    int lastStep;

    sf::Font AndikaNewBasic;
    sf::String newFpsValue;

    float timeSinceLastDraw;
    int averageFrameRate;
    int language;
    int selectedLevel;

    sf::RectangleShape backgroundGray;
    DynamicObject highlight;

    // Create and initialize the window
    MainWindow(int width, int height, const char* title);

    // Set window icons
    void SetIcon();

    // Gets resources filepath and initializes them
    void InitializeTexturesAndResources();

    // Initializes the user interface and applies default settings
    void InitializeUIAndSettings();

    // Calculates the layout of the elements within the window
    void CalculateLayout();

    // The main loop
    void GameLoop();

    // Draws the UI
    void Paint();

    // Calculates the average frame rate
    void UpdateFrameRate();

    // Switches from Windowed to Fullscreen and vice versa
    void SwitchScreenMode();

    // Called when the mouse moves within the window
    void OnMouseMove(int xPos, int yPos);

    // Called when the mouse left button is pressed 
    void OnMouseDown(int xPos, int yPos);

    // Called when the mouse left button is released
    void OnMouseUp(int xPos, int yPos);

    // Called when the keyboard Escape key is pressed
    void OnEscapeDown();

    // Updates text to selected language
    void UpdateLanguage();
};