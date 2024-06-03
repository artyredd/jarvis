#include "core/runtime.h"
#include "core/plugins.h"

int main()
{
	Application.Start();
	return 0;
}

Plugin plugin;

OnStart(1)
{
	plugin = Plugins.Load(stack_string("ExamplePlugin.dll"));
}

OnUpdate(1)
{
	fprintf(stdout, "Jarvis OnUpdate\n");
}

AfterUpdate(1)
{
	fprintf(stdout, "Jarvis AfterUpdate\n");
}

OnClose(1)
{
	Plugins.Dispose(plugin);
}