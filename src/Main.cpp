/*
MIT License

Copyright (c) 2020 Irseny

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "stdafx.h"
#include "RTSShared.h"
#include "RivaCross.h"



int main(int argc, char** argv) {
	// curses initialization
	initscr();
	keypad(stdscr, true);
	noecho();
	
	// put commands on top, continue with the active config 
	// and finally state error output
	RenderPassState state = {
		0
	};
	helpCommands(&state);
	addch('\n');
	// continue with the active config
	// since this is not the loaded config we will override this information below
	RTSSCrossConfig config;
	initConfig(&config);
	helpActiveConfig(&config, &state);
	addch('\n');
	// now we have made space to put log output about the current action
	// which is loading a config in this case
	helpWelcome(&state);
	config = configureStart(argc, argv, &state);
	if (RTSSUpdateOSDEntry(&config, RivaCrossOSDEntryName) != 0) {
		printw("Failed to connect to RTSS\n");
	} else {
		printw("Successfully connected to RTSS\n");
	}
	// after loading we go back to page start and restate the previous information
	move(0, 0);
	state.linesFilled = 0;
	helpCommands(&state);
	addch('\n');
	state.linesFilled += 1;
	// and put the loaded config exactly where the initial config information was located
	helpActiveConfig(&config, &state);
	refresh();
	// run the interesting program part
	CrossActionType exitMode = runInteractiveProgram(&config, &state);
	// cleanup
	endwin();
	if (exitMode == CrossActionType::ExitHard) {
		printf("Hard exit\n");
	} else {
		printf("Clean exit\n");
		// cleanup RTSS view
		if (RTSSReleaseOSDEntry(RivaCrossOSDEntryName) != 0) {
			printf("Failed to disconnect from RTSS\n");
		} else {
			printf("Successfully disconnected from RTSS\n");
		}
	}
	return 0;
}
