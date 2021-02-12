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

const char RivaCrossOSDEntryName[32] = "RivaCross_crosshair";

void helpWelcome(RenderPassState* state) {
	printw("Welcome to RivaCross\n");
	state->linesFilled += 1;
}
void helpCommands(RenderPassState* state) {
	// TODO use lines filled state or remove it entirely
	//move(state->linesFilled, 0);
	printw("Commands:\n");
	printw("Q - quit RivaCross\n");
	printw("CTRL + Q - quit RivaCross but retain a visible crosshair\n");
	printw("CTRL + O - load an existing config\n");
	printw("T - set the crosshair character/text\n");
	printw("NUM- and NUM+ - change the crosshair size\n");
	printw("S - set the crosshair size\n");
	printw("C - set the crosshair color\n");
	printw("Direction keys - move the crosshair on screen\n");
	printw("M - set the crosshair position\n");
	printw("U - retransmit the current config to RTSS\n");
	state->linesFilled += 11;
}

void helpActiveConfig(RTSSCrossConfig* config, RenderPassState* state) {
	//move(state->linesFilled, 0);
	printw("Active config:\n");
	printw("Crosshair: %s\n", config->crosshair);
	printw("Position: %d %d\n", config->position[0], config->position[1]);
	printw("Size: %d\n", config->scale);
	printw("Color: #%02x%02x%02x\n", config->color[0], config->color[1], config->color[2]);
	state->linesFilled += 5;
}

bool initConfig(RTSSCrossConfig* config) {
	if (config == NULL) {
		return false;
	}
	strcpy(config->crosshair, "O");
	config->position[0] = 477;
	config->position[1] = 265;
	config->color[0] = 0xFF;
	config->color[1] = 0xFF;
	config->color[2] = 0xFF;
	config->scale = 100;
	return true;
}
int loadConfig(char* configPath, RTSSCrossConfig* config) {
	if (configPath == NULL || config == NULL) {
		return -1;
	}
	// attempt to read from file
	FILE* file = fopen(configPath, "r");
	if (file == NULL) {
		return -2;
	}
	bool complete = false;
	char line[32];
	char crosshair[32];
	unsigned int posX, posY, scale;
	unsigned int red, green, blue;
	do {
		// read crosshair line
		char* content = fgets(line, sizeof(line), file);
		if (!content) {
			break;
		}
		// exclude everything from the first newline character
		int lineLength = strlen(content);
		int crosshairLength = 0;
		for (; crosshairLength < lineLength; crosshairLength++) {
			if (content[crosshairLength] == '\n' ||
				content[crosshairLength] == '\r') {
				break;
			}
		}
		crosshairLength = min(crosshairLength, sizeof(crosshair) - 1);
		strncpy(crosshair, content, crosshairLength);
		crosshair[crosshairLength] = '\0';
		
		// read position x
		content = fgets(line, sizeof(line), file);
		if (!content) {
			break;
		}
		if (sscanf(content, "%i", &posX) < 1) {
			break;
		}
		// read position y
		content = fgets(line, sizeof(line), file);
		if (!content) {
			break;
		}
		if (sscanf(content, "%i", &posY) < 1) {
			break;
		}
		// read scale
		content = fgets(line, sizeof(line), file);
		if (!content) {
			break;
		}
		if (sscanf(content, "%i", &scale) < 1) {
			break;
		}
		// read color
		content = fgets(line, sizeof(line), file);
		if (!content) {
			break;
		}
		int colorLength = strlen(content);
		// require red at index 1 and 2, green at 3 and 4 ...
		if (colorLength < 7) {
			break;
		}
		if (sscanf(content, "#%02x%02x%02x", &red, &green, &blue) < 3) {
			break;
		}
		complete = true;
	} while (false);
	fclose(file);
	// apply values after reading successfully
	if (complete) {

		strncpy(config->crosshair, crosshair, min(sizeof(config->crosshair) - 1, sizeof(crosshair) - 1));
		config->crosshair[sizeof(config->crosshair) - 1] = '\0';
		config->position[0] = posX;
		config->position[1] = posY;
		config->scale = scale;
		config->color[0] = red;
		config->color[1] = green;
		config->color[2] = blue;
		return 0;
	} else {
		return -3;
	}
}
bool makeConfigPath(char* configName, char* configPath) {
	if (configName == NULL || configPath == NULL) {
		return false;
	}
	char prefix[] = "config";
	char extension[] = "txt";
	sprintf(configPath, "%s/%s.%s", prefix, configName, extension);
	return true;
}
RTSSCrossConfig configureStart(int argc, char** argv, RenderPassState* state) {
	//move(state->linesFilled, 0);
	char configName[32] = "default";
	// determine config usage
	if (argc < 2) {
		printw("Using default config\n");
	} else {
		strncpy(configName, argv[1], sizeof(configName) - 1);
		configName[sizeof(configName) - 1] = '\0';
		printw("Using config %s\n", configName);
	}
	state->linesFilled += 1;
	char configPath[256] = "";
	makeConfigPath(configName, configPath);
	RTSSCrossConfig config;
	if (loadConfig(configPath, &config) != 0) {
		printw("Failed to load config from %s\n", configPath);
		initConfig(&config);
		printw("Continuing with stock config\n");
		state->linesFilled += 2;
	}
	return config;
}
bool pollUserAction(CrossActionArgs* args) {
	if (args == NULL) {
		return false;
	}
	// ctrl+char is observed if bits 6 and 7 are not set
	const int ctrlMod = 0x60; 
	// TODO enable after debugging
	noecho();
	int input = getch();
	switch (input) {
		case ctrlMod^'c':
		case KEY_EXIT:
		case 'q':
			args->action = CrossActionType::ExitClean;
			break;
		case ctrlMod^'q':
			args->action = CrossActionType::ExitHard;
			break;
		case 't':
			args->action = CrossActionType::Rename;
			break;
		case 'm':
			args->action = CrossActionType::Move;
			break;
		case 's':
			args->action = CrossActionType::Scale;
			break;
		case 'c':
			args->action = CrossActionType::Tint;
			break;
		case ctrlMod^'o':
			args->action = CrossActionType::Load;
			break;
		case 'u':
			args->action = CrossActionType::Update;
			break;
		// move
		case KEY_UP:
			args->deltaY = -1;
			break;
		case CTL_UP:
			args->deltaY = -10;
			break;
		case KEY_DOWN:
			args->deltaY = 1;
			break;
		case CTL_DOWN:
			args->deltaY = 10;
			break;
		case KEY_RIGHT:
			args->deltaX = 1;
			break;
		case CTL_RIGHT:
			args->deltaX = 10;
			break;
		case KEY_LEFT:
			args->deltaX = -1;
			break;
		case CTL_LEFT:
			args->deltaX = -10;
			break;
		// scale
		case PADMINUS:
			args->deltaScale = -1;
			break;
		case CTL_PADMINUS:
			args->deltaScale = -10;
			break;
		case PADPLUS:
			args->deltaScale = 1;
			break;
		case CTL_PADPLUS:
			args->deltaScale = 10;
			break;
		// special cases
		case KEY_RESIZE:
			resize_term(0, 0);
			break;
		default:
			// skip anything else
			args->skippedInput = input;
			break;
	}
	// hint at that the user has input something
	bool toProcess = (args->deltaScale != 0) || (args->deltaX != 0) || (args->deltaY != 0) ||
		(args->action != CrossActionType::None) || (args->skippedInput != 0);
	return toProcess;
}

bool processUserAction(CrossActionArgs* args, RTSSCrossConfig* config, RenderPassState* state) {
	// skip one line
	// it does sometimes contain user input which makes printing buggy
	addch('\n');
	state->linesFilled += 1;
	bool changed = false;
	// debug output for key combinations
	if (false && args->skippedInput != 0) {
		//move(state->linesFilled, 0);
		printw("Skipped input: %i|0x%x (", args->skippedInput, args->skippedInput);
		addch(args->skippedInput>>24);
		addch(' ');
		addch(args->skippedInput>>16);
		addch(' ');
		addch(args->skippedInput>>8);
		addch(' ');
		addch(args->skippedInput);
		addstr(")\n");
		args->skippedInput = 0;
		state->linesFilled += 1;
	}
	switch (args->action) {
	case CrossActionType::None:
		break;
	case CrossActionType::Move:
		changed = processMoveUserAction(args, config, state);
		break;
	case CrossActionType::Scale:
		changed = processScaleUserAction(args, config, state);
		break;
	case CrossActionType::Tint:
		changed = processTintUserAction(args, config, state);
		break;
	case CrossActionType::Load:
		changed = processLoadUserAction(args, config, state);
		break;
	case CrossActionType::Rename:
		changed = processRenameUserAction(args, config, state);
		break;
	case CrossActionType::Update:
		changed = processUpdateUserAction(args, config, state);
		break;
	default:
		break;
	}
	// move 
	if (args->deltaX != 0) {
		config->position[0] += args->deltaX;
		if ((int)config->position[0] < 0) {
			config->position[0] = 0;
		}
		args->deltaX = 0;
		changed = true;
	}
	if (args->deltaY != 0) {
		config->position[1] += args->deltaY;
		if ((int)config->position[1] < 0) {
			config->position[1] = 0;
		}
		args->deltaY = 0;
		changed = true;
	}
	// scale
	if (args->deltaScale != 0) {
		config->scale += args->deltaScale;
		if ((int)config->scale < 0) {
			config->scale = 0;
		}
		args->deltaScale = 0;
		changed = true;
	}
	return changed;
}
bool processUpdateUserAction(CrossActionArgs* args, RTSSCrossConfig* config, RenderPassState* state) {
	args->action = CrossActionType::None;
	printw("Resending active config to RTSS\n");
	state->linesFilled += 1;
	// indicate that an update of RTSS state is required
	return true;
}
bool processTintUserAction(CrossActionArgs* args, RTSSCrossConfig* config, RenderPassState* state) {
	bool changed = false;
	//move(state->linesFilled, 0);
	printw("Current color is #%02x%02x%02x\n", config->color[0], 
		config->color[1], config->color[2]);
	printw("Enter new color (r, g, b) or (rrggbb): #");
	refresh();
	char inputBuffer[256];
	echo();
	getstr(inputBuffer);
	if (!changed) {
		// search for r, g, b pattern
		int r, g, b;
		if (sscanf(inputBuffer, "%03i,%03i,%03i", &r, &g, &b) >= 3) {
			if (r < 256 && g < 256 && b < 256) {
				config->color[0] = r;
				config->color[1] = g;
				config->color[2] = b;
				changed = true;
			}
		}
	}
	
	if (!changed) {
		// search for #rrggbb pattern
		int r, g, b;
		if (sscanf(inputBuffer, "%02x%02x%02x", &r, &g, &b) >= 3) {
			config->color[0] = r;
			config->color[1] = g;
			config->color[2] = b;
			changed = true;
		}
	}
	if (!changed) {
		printw("Wrong format! Please specify your desired color as ");
		printw("three comma delimited values in [0-255] (e.g. 128,234,56) or ");
		printw("a hexadecimal representation (e.g. 70FF3A)\n");
	}
	// we expect some lines to wrap so we get the actual number of lines written from curses
	int cursorX, cursorY;
	getsyx(cursorY, cursorX);
	state->linesFilled = cursorY;
	args->action = CrossActionType::None;
	// indicate if an update of RTSS memory is required
	return changed;
}
bool processMoveUserAction(CrossActionArgs* args, RTSSCrossConfig* config, RenderPassState* state) {
	printw("Current position is %i, %i\n", config->position[0], config->position[1]);
	printw("Use the direction keys and exit with ENTER or\n");
	printw("Enter new position (x, y): ");
	refresh();
	
	// get user input
	// first allow crosshair movement with the direction keys
	// but enter number input mode as soon as a number key is pressed
	const int ctrlMod = 0x60; 
	bool numberStarted = false;
	bool moveOrdered = false;
	bool moveAborted = false;
	nodelay(stdscr, true);
	while (!numberStarted && !moveOrdered && !moveAborted) {
		int input = getch();
		// scan for direction keys
		// these also activate if the console window is out of focus
		bool moved = false;
		int modifier = 1;
		if (GetKeyState(VK_CONTROL) & 0x8000) {
			modifier = 10;
		}
		if (GetKeyState(VK_LEFT) & 0x8000) {
			args->deltaX = -modifier;
			moved = true;
		}
		if (GetKeyState(VK_RIGHT) & 0x8000) {
			args->deltaX = modifier;
			moved = true;
		}
		if (GetKeyState(VK_UP) & 0x8000) {
			args->deltaY = -modifier;
			moved = true;
		}
		if (GetKeyState(VK_DOWN) & 0x8000) {
			args->deltaY = modifier;
			moved = true;
		}
		if (GetKeyState(VK_RETURN) & 0x8000) {
			moveAborted = true;
		}
		// process the details outside this function
		// but come back to it (action type is still MOVE)
		if (moved) {
			flushinp(); // throw away repeated direction keys from the input queue
			ungetch('m'); // put something in the queue so that this function is called again
			moveOrdered = true;
		} else {
			switch (input) {
			case 'q':
			case '\n':
			case KEY_ENTER:
			case (ctrlMod^'c'):
				// end position modification with CTRL+C, Q and ENTER
				moveAborted = true;
				break;
			case '0': case '1':
			case '2': case '3':
			case '4': case '5':
			case '6': case '7':
			case '8': case '9':
				// jump to manual specification below
				ungetch(input);
				numberStarted = true;
				break;
			default:
				// ignore everything else
				break;
			}
		}
		Sleep(50); // wait some more so that the user easily do single steps
	}
	nodelay(stdscr, false);
	if (moveAborted) {
		args->action = CrossActionType::None;
		return false;
	}
	if (moveOrdered) {
		return true;
	}
	if (numberStarted) {
		// a number key was pressed
		// continue to read number input until the user hits enter
		bool changed = false;
		char inputBuffer[256];
		echo();
		getnstr(inputBuffer, sizeof(inputBuffer)-1);
		state->linesFilled += 2;
		// process user input
		int posX, posY;
		if (sscanf(inputBuffer, "%i,%i", &posX, &posY) < 2) {
			printw("Wrong format! Please specify your desired position as ");
			printw("two comma separated integers (e.g. 477, 245)\n");
		} else if (posX < 0 || posY < 0) {
			printw("Wrong format! Please use only positive valus\n");
		} else {
			config->position[0] = posX;
			config->position[1] = posY;
			changed = true;
			printw("New position is %i, %i\n", config->position[0], config->position[1]);
		}
		int cursorX, cursorY;
		getsyx(cursorY, cursorX);
		state->linesFilled = cursorY;
		args->action = CrossActionType::None;
		return changed;
	}
	args->action = CrossActionType::None;
	return false;
}
bool processScaleUserAction(CrossActionArgs* args, RTSSCrossConfig* config, RenderPassState* state) {
	bool changed = false;
	// get user input
	printw("Current size is %i\n", config->scale);
	printw("Enter new size: ");
	refresh();
	char inputBuffer[16];
	echo();
	getnstr(inputBuffer, sizeof(inputBuffer)-1);
	state->linesFilled += 2;
	// process user input
	int scale;
	if (sscanf(inputBuffer, "%i", &scale) < 1) {
		printw("Wrong format! Please specify your desired size as a single integer\n");
	} else {
		if (scale < 0) {
			printw("Wrong format! Cannot have a negative crosshair size\n");
		} else {
			config->scale = scale;
			changed = true;
			printw("New size is %i\n", config->scale);
		}
	}
	state->linesFilled += 1;
	args->action = CrossActionType::None;
	return changed;
}
bool processRenameUserAction(CrossActionArgs* args, RTSSCrossConfig* config, RenderPassState* state) {
	// get user input
	printw("Current crosshair is %s\n", config->crosshair);
	printw("Enter new crosshair: ");
	refresh();
	char inputBuffer[64];
	echo();
	getnstr(inputBuffer, sizeof(inputBuffer) - 1);
	state->linesFilled += 2;
	// process user input
	strncpy(config->crosshair, inputBuffer, min(sizeof(config->crosshair) - 1, sizeof(inputBuffer)));
	config->crosshair[sizeof(config->crosshair) - 1] = '\0';
	printw("New crosshair is %s\n", config->crosshair);
	state->linesFilled += 1;
	args->action = CrossActionType::None;
	return true;
}
bool processLoadUserAction(CrossActionArgs* args, RTSSCrossConfig* config, RenderPassState* state) {
	args->action = CrossActionType::None;
	// get user input
	printw("Enter config to load: ");
	refresh();
	char inputBuffer[128];
	echo();
	getnstr(inputBuffer, sizeof(inputBuffer)-1);
	state->linesFilled += 1;
	// process user input
	char configPath[256];
	if (!makeConfigPath(inputBuffer, configPath)) {
		printw("Internal error\n");
		state->linesFilled += 1;
		return false;
	}
	if (loadConfig(configPath, config) != 0) {
		printw("Failed to load config from %s\n", configPath);
		printw("Please state your desired config without file extension (.txt) ");
		printw("and make sure it is formatted correctly\n");
		state->linesFilled += 1;
		return false;
	}
	return true;
}
CrossActionType runInteractiveProgram(RTSSCrossConfig* config, RenderPassState* state) {
	// wait and process user input
	char entryName[32] = "RivaCross_Crosshair";
	bool updatePending = false;
	bool exit = false;
	CrossActionArgs actionArgs =  {
		CrossActionType::None,
		0, 0, 0, 0
	};
	
	do {
		if (pollUserAction(&actionArgs)) {
			// even if there is log output visible
			// the cursor sits below commands and active config output currently
			// so we can clear to bottom in order to remove log output
			int cursorX, cursorY;
			getsyx(cursorY, cursorX);
			clrtobot();
			// and restore the cursor position
			// to have new log output correctly placed
			setsyx(cursorY, 0);
			
			if (processUserAction(&actionArgs, config, state)) {
				updatePending = true;
			}
			// update the displayed information
			clrtobot();
			move(0, 0);
			state->linesFilled = 0;
			helpCommands(state);
			addch('\n');
			state->linesFilled += 1;
			helpActiveConfig(config, state);
			// and stop here in order to not override
			// what processUserAction() has printed
		}
		if (updatePending) {
			addch(' ');
			state->linesFilled += 1;
			if (RTSSUpdateOSDEntry(config, RivaCrossOSDEntryName) != 0) {
				printw("Failed to send active config to RTSS\n");
				state->linesFilled += 1;
			} 
			updatePending = false;
		}
		refresh();
		// be cautious and add alittle more delay
		Sleep(20);
		exit = actionArgs.action == CrossActionType::ExitClean || 
			actionArgs.action == CrossActionType::ExitHard;
	} while (!exit);
	
	return actionArgs.action;
}