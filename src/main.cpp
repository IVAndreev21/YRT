#include "Application.hpp"

int main()
{
	YRT::Application* application = new YRT::Application(1280, 1024, "YRT Bank");
	application->Run();
	delete application;

}