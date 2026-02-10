#include "App.h"

int main()
{
	App* app = new App();
	app->Init();
	app->Run();
	app->Close();
	delete app;
}