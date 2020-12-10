#include "Engine/Core/CoreEngine.h"
#include "Game/Game0.h"
#include "Resources/XML/rapidxml.hpp"
#include <fstream>

int main(int argc, char* argv[]) {

	std::ifstream file("Resources/XML/main.xml");
	rapidxml::xml_document<> doc;
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	rapidxml::xml_node<>* root = doc.first_node();
	int id = atoi(root->first_node("person")->first_attribute("id")->value());
	std::string title = root->first_node("person")->first_node("name")->first_node("title")->value();
	std::string given = root->first_node("person")->first_node("name")->first_node("given")->value();
	std::string family = root->first_node("person")->first_node("name")->first_node("family")->value();

	std::cout << title << std::endl;
	std::cout << given << std::endl;
	std::cout << family << std::endl;

	CoreEngine::GetInstance()->SetGameInterface(new Game0);

	if (!CoreEngine::GetInstance()->OnCreate("GAME258 Engine", 800, 600))
	{
		return 0;
	}

	CoreEngine::GetInstance()->Run();

	return 0;
}