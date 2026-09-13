//
//  Sleep.cpp
//

#include <cassert>

#include "Sleep.h"



#ifdef __EMSCRIPTEN__

	// nanosleep() has no real OS thread to yield on Emscripten's default
	//   single-threaded target - it compiles to a busy-wait that blocks
	//   the browser's main thread (and therefore rendering) for the full
	//   duration.  requestAnimationFrame already paces glutIdleFunc at
	//   the display's refresh rate, so there is nothing useful to sleep
	//   for here.
	void sleep (double seconds)
	{
		assert(seconds >= 0.0);
	}

#elif defined(_WIN32)

	#include <windows.h>  // needed for Sleep(millisec)

	void sleep (double seconds)
	{
		assert(seconds >= 0.0);

		int milliseconds = (int)(seconds * 1000.0);

		if(milliseconds > 0)
			Sleep(milliseconds);
	}

#elif __WIN32__

	#include <windows.h>  // needed for Sleep(millisec)

	void sleep (double seconds)
	{
		assert(seconds >= 0.0);

		int milliseconds = (int)(seconds * 1000.0);

		if(milliseconds > 0)
			Sleep(milliseconds);
	}

#else	// Posix

	#include <time.h>

	void sleep (double seconds)
	{
		assert(seconds >= 0.0);

		if(seconds > 0.0)
		{
			timespec spec;
			spec.tv_sec  = (int)(seconds);
			spec.tv_nsec = (int)((seconds - spec.tv_sec) * 1000000000);
			// beware rounding erros
			if(spec.tv_nsec < 0)
				spec.tv_nsec = 0;
			else if(spec.tv_nsec > 999999999)
				spec.tv_nsec = 999999999;

			nanosleep(&spec, NULL);
		}
	}

#endif
