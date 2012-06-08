#ifndef APPLICATION_H_
#define APPLICATION_H_

/*
 * Application.h
 *
 *  Created on: 08.06.2012
 *      Author: trex
 */

#include <android/sensor.h>
#include <android_native_app_glue.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>


#include "FrameDrawer.h"
#include "IDrawable.h"

struct engine;

class Application
{
public:
	Application(struct android_app* state, struct engine* engine);
	virtual ~Application();

	void initTriangles();
	int initDisplay(struct engine* engine);
	void termDisplay(struct engine* engine);

	void engine_handle_cmd(struct android_app* app, int32_t cmd);

	int32_t engine_handle_input(
		struct android_app* app,
		AInputEvent* event
	);

	void draw(struct engine* engine);

	void start();
private:

//Our drawer
	FrameDrawer m_frameDrawer;
	std::vector<IDrawable*> m_drawables;

	struct engine* m_engine;
	struct android_app* m_state;
};

//from main

/**
 * Our saved state data.
 */
struct saved_state {
    float angle;
    int32_t x;
    int32_t y;
};

/**
 * Shared state for our app.
 */
struct engine {
    struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;

    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
    struct saved_state state;
};

#endif /* APPLICATION_H_ */
