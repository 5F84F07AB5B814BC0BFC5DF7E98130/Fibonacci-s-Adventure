#pragma once
#include <map>
#include <string>
#include <vector>

std::map<std::string, int> stringIndex
{
	{ "start", 0 },
	{ "settings", 1 },
	{ "language", 2 },
	{ "exit", 3 },
	{ "fullscreen", 4 },
	{ "backToMainMenu", 5 },
	{ "resetLevel", 6 },
	{ "stepsText", 7 },
	{ "selectLevel", 8 }
};

std::vector<std::vector<std::string>> strings
{
	{ "Start", "Incepe Jocul" },
	{ "Settings", "Setari" },
	{ "Language", "Limba" },
	{ "Exit", "Iesire" },
    { "Fullscreen", "Ecran Complet"},
    { "Back To Main Menu", "Inapoi La Meniu"},
    { "Reset Level", "Reseta Nivelul"},
    { "Step", "Lungime Saritura"},
    { "Select Level", "Selectare Nivel"}
};
