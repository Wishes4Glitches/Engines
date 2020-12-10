#include "rapidxml.hpp"
#include <fstream>
#include "../../Engine/Core/CoreEngine.h"

using namespace rapidxml;

int main()
{
	std::ifstream file("./Resources/main.xml");
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

	return 0;
}