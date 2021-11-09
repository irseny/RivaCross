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

#pragma once

#include "RTSShared.h"

extern const char RivaCrossOSDEntryName[32];

enum CrossActionType {
	None,
	ExitClean,
	ExitHard,
	Rename,
	Move,
	Scale,
	Tint,
	Load,
	Update
};

typedef struct CrossActionArgs {
	CrossActionType action;
	int deltaX;
	int deltaY;
	int deltaScale;
	int skippedInput;
} CrossActionArgs;

typedef struct RenderPassState {
	int linesFilled;
} RenderPassState;

void helpWelcome(RenderPassState* state);
void helpCommands(RenderPassState* state);
void helpActiveConfig(RTSSCrossConfig* config, RenderPassState* state);

RTSSCrossConfig configureStart(int argc, char** argv, RenderPassState* state);
bool makeConfigPath(char* configName, char* configPath);
bool initConfig(RTSSCrossConfig* config);
int loadConfig(char* configName, RTSSCrossConfig* config);
bool pollUserAction(CrossActionArgs* args, RenderPassState* state);

bool processUserAction(CrossActionArgs* args, RTSSCrossConfig* config, RenderPassState* state);
bool processUpdateUserAction(CrossActionArgs* args, RTSSCrossConfig* config, RenderPassState* state);
bool processRenameUserAction(CrossActionArgs* args, RTSSCrossConfig* config, RenderPassState* state);
bool processLoadUserAction(CrossActionArgs* args, RTSSCrossConfig* config, RenderPassState* state);
bool processTintUserAction(CrossActionArgs* args, RTSSCrossConfig* config, RenderPassState* state);
bool processMoveUserAction(CrossActionArgs* args, RTSSCrossConfig* config, RenderPassState* state);
bool processScaleUserAction(CrossActionArgs* args, RTSSCrossConfig* config, RenderPassState* state);
int imin(int i1, int i2);

CrossActionType runInteractiveProgram(RTSSCrossConfig* config, RenderPassState* state);
