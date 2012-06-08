#include <string.h>
#include <jni.h>

#include <android_native_app_glue.h>

#include "Application.h"

Application* ApplicationInstance;

/**
 * Process the next input event.
 */
static int32_t engine_handle_input(
	struct android_app* app,
	AInputEvent* event)
{
	return ApplicationInstance->engine_handle_input(app,event);
}

/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
	ApplicationInstance->engine_handle_cmd(app,cmd);
}

void android_main(struct android_app* state) {
	struct engine engine;

	// Make sure glue isn't stripped.
	app_dummy();

	//prepare static functions
	memset(&engine, 0, sizeof(engine));
	state->userData = &engine;
	state->onAppCmd = engine_handle_cmd;
	state->onInputEvent = engine_handle_input;
	engine.app = state;

	ApplicationInstance = new Application(state, &engine);

	// loop waiting for stuff to do.
	ApplicationInstance->start();
}
