#include "core/runtime.h"
#include "core/plugins.h"
#include "core/tasks.h"

int main()
{
	Application.Start();
	return 0;
}

Plugin plugin;
Plugin ttsPlugin;

OnStart(1)
{
	plugin = Plugins.Load(stack_string("Plugin.dll"));
	ttsPlugin = Plugins.Load(stack_string("TTSPlugin.dll"));
}

int i = 0;
int x = 0;

OnUpdate(1)
{
	fprintf_red(stdout, "Jarvis OnUpdate: %i\n", i++);
}

AfterUpdate(1)
{
	fprintf_red(stdout, "Jarvis AfterUpdate: %i\n", x++);
}

OnClose(1)
{
	Plugins.Dispose(plugin);
	Plugins.Dispose(ttsPlugin);
}