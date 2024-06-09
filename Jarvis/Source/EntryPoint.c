#include "core/runtime.h"
#include "core/plugins.h"
#include "core/tasks.h"

int main()
{
	Application.Start();
	return 0;
}

Plugin ttsPlugin;

OnStart(1)
{
	ttsPlugin = Plugins.Load(stack_string("TTSPlugin.dll"));
}


OnUpdate(1)
{
}

AfterUpdate(1)
{
}

OnClose(1)
{
	Plugins.Dispose(ttsPlugin);
}