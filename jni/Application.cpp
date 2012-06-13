/*
 * Application.cpp
 *
 *  Created on: 08.06.2012
 *      Author: trex
 */

#include "Application.h"

#include <android/sensor.h>

#include "AndroidLogs.h"
#include "SimpleGlFuncs.h"
#include "GLTriangle.h"
#include "DrawConfig.h"
#include "DrawConfigPrivate.h"


Application::Application(struct android_app* state, struct engine* engine)
	:m_state(state)
	,m_engine(engine)
	,m_configPrivate(new DrawConfigPrivate() )
{
	// Prepare to monitor accelerometer
	m_engine->sensorManager = ASensorManager_getInstance();

	m_engine->accelerometerSensor = ASensorManager_getDefaultSensor(
		m_engine->sensorManager,
		ASENSOR_TYPE_ACCELEROMETER
	);

	m_engine->sensorEventQueue = ASensorManager_createEventQueue(
		m_engine->sensorManager,
		m_state->looper,
		LOOPER_ID_USER,
		NULL,
		NULL
	);

	if (m_state->savedState != NULL) {
			// We are starting with a previous saved state; restore from it.
			m_engine->state = *(struct saved_state*)m_state->savedState;
	}
}

Application::~Application()
{
	// TODO Auto-generated destructor stub
}

void Application::start()
{
	while (1)
	{
		// Read all pending events.
		int ident;
		int events;
		struct android_poll_source* source;

		// If not animating, we will block forever waiting for events.
		// If animating, we loop until all events are read, then continue
		// to draw the next frame of animation.
		while ((ident=ALooper_pollAll(m_engine->animating ? 0 : -1, NULL, &events,
						(void**)&source)) >= 0)
		{
			// Process this event.
			if (source != NULL) {
				source->process(m_state, source);
			}
			// If a sensor has data, process it now.
			if (ident == LOOPER_ID_USER)
			{
				if (m_engine->accelerometerSensor != NULL)
				{
					ASensorEvent event;
					while (ASensorEventQueue_getEvents(m_engine->sensorEventQueue,
									&event, 1) > 0)
					{
						//process sensor data
					}
				}
			}

			// Check if we are exiting.
			if (m_state->destroyRequested != 0) {
					this->termDisplay(m_engine);
					return;
			}
		}

		if (m_engine->animating) {
				// Done with events; draw next animation frame.
				m_engine->state.angle += .01f;
				if (m_engine->state.angle > 1) {
						m_engine->state.angle = 0;
				}
				// Drawing is throttled to the screen update rate, so there
				// is no need to do timing here.
				this->draw(m_engine);
		}
	}
}

void Application::initTriangles()
{
	m_drawables.push_back(
		new GLTriangle( 20, 20, DrawConfig(m_configPrivate) )
	);
}

int Application::initDisplay(struct engine* engine)
{
	// initialize OpenGL ES and EGL

	/*
	 * Here specify the attributes of the desired configuration.
	 * Below, we select an EGLConfig with at least 8 bits per color
	 * component compatible with on-screen windows
	 */
	const EGLint attribs[] = {
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_NONE
	};
	EGLint w, h, dummy, format;
	EGLint numConfigs;
	EGLConfig config;
	EGLSurface surface;
	EGLContext context;

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(display, 0, 0);

	/* Here, the application chooses the configuration it desires. In this
	 * sample, we have a very simplified selection process, where we pick
	 * the first EGLConfig that matches our criteria */
	eglChooseConfig(display, attribs, &config, 1, &numConfigs);

	/* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
	 * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
	 * As soon as we picked a EGLConfig, we can safely reconfigure the
	 * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

	surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);


	static const EGLint ctx_attribs[] = {
		  EGL_CONTEXT_CLIENT_VERSION, 2,
		  EGL_NONE
		};
	context = eglCreateContext(display, config, NULL, ctx_attribs);

	if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
		LOGW("Unable to eglMakeCurrent");
		return -1;
	}

	eglQuerySurface(display, surface, EGL_WIDTH, &w);
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);

	engine->display = display;
	engine->context = context;
	engine->surface = surface;
	engine->width = w;
	engine->height = h;
	engine->state.angle = 0;

	m_configPrivate->setWidth(w);
	m_configPrivate->setHeight(h);

	checkGlError("before all start");

	// Initialize GL state.
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);//Error here. What is that?
	checkGlError("GL_PERSPECTIVE_CORRECTION_HINT");

	glEnable(GL_CULL_FACE);
	checkGlError("GL_CULL_FACE");

	//    glShadeModel(GL_SMOOTH); dropped from GLESv2
	glDisable(GL_DEPTH_TEST);
	checkGlError("GL_DEPTH_TEST");

	glViewport(0, 0, w, h);
	checkGlError("glViewport");

	this->initTriangles();

	return 0;
}

void Application::termDisplay(struct engine* engine)
{
	if (engine->display != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

		if (engine->context != EGL_NO_CONTEXT)
		{
			eglDestroyContext(engine->display, engine->context);
		}

		if (engine->surface != EGL_NO_SURFACE)
		{
			eglDestroySurface(engine->display, engine->surface);
		}

		eglTerminate(engine->display);
	}
	engine->animating = 0;
	engine->display = EGL_NO_DISPLAY;
	engine->context = EGL_NO_CONTEXT;
	engine->surface = EGL_NO_SURFACE;
}

void Application::engine_handle_cmd(struct android_app* app, int32_t cmd)
{
	struct engine* engine = (struct engine*)app->userData;
	switch (cmd)
	{
		case APP_CMD_SAVE_STATE:
		{
			// The system has asked us to save our current state.  Do so.
			engine->app->savedState = malloc(sizeof(struct saved_state));
			*((struct saved_state*)engine->app->savedState) = engine->state;
			engine->app->savedStateSize = sizeof(struct saved_state);
			break;
		}
		case APP_CMD_INIT_WINDOW:
		{
			// The window is being shown, get it ready.
			if (engine->app->window != NULL) {
					this->initDisplay(engine);//engine_init_display(engine);
					this->draw(engine);//engine_draw_frame(engine);
			}
			break;
		}
		case APP_CMD_TERM_WINDOW:
		{
			// The window is being hidden or closed, clean it up.
			this->termDisplay(engine);//engine_term_display(engine);
			break;
		}
		case APP_CMD_GAINED_FOCUS:
		{
			// When our app gains focus, we start monitoring the accelerometer.
			if (engine->accelerometerSensor != NULL) {
					ASensorEventQueue_enableSensor(engine->sensorEventQueue,
									engine->accelerometerSensor);
					// We'd like to get 60 events per second (in us).
					ASensorEventQueue_setEventRate(engine->sensorEventQueue,
									engine->accelerometerSensor, (1000L/60)*1000);
			}
			break;
		}
		case APP_CMD_LOST_FOCUS:
		{
			// When our app loses focus, we stop monitoring the accelerometer.
			// This is to avoid consuming battery while not being used.
			if (engine->accelerometerSensor != NULL)
			{
				ASensorEventQueue_disableSensor(
					engine->sensorEventQueue,
					engine->accelerometerSensor
				);
			}
			// Also stop animating.
			engine->animating = 0;
			this->draw(engine);//engine_draw_frame(engine);
			break;
		}
	}
}

int32_t Application::engine_handle_input(
	struct android_app* app,
	AInputEvent* event)
{
	struct engine* engine = (struct engine*)app->userData;
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	{
		int pointsCount = AMotionEvent_getPointerCount(event);
		for(int pointIdx=0; pointIdx<pointsCount; ++pointIdx)
		{
			float pointX = AMotionEvent_getX(event,pointIdx);
			float pointY = AMotionEvent_getY(event,pointIdx);
			LOGI("Touch event x=%f, y=%f",pointX,pointY);

			m_drawables.push_back(
				new GLTriangle(
					(int)pointX,
					(int)pointY,
					DrawConfig(m_configPrivate)
				)
			);
		}

		AMotionEvent_getHistorySize(event);

		engine->animating = 1;
		engine->state.x = AMotionEvent_getX(event, 0);
		engine->state.y = AMotionEvent_getY(event, 0);

		return 1;
	}

	return 0;
}

void Application::draw(struct engine* engine)
{
	if (engine->display == NULL)
	{
		// No display.
		LOGI("No display");
		return;
	}

	m_frameDrawer.drawFrame(m_drawables);

	eglSwapBuffers(engine->display, engine->surface);
}
