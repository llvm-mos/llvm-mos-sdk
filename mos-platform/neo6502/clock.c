// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <time.h>
#include <neo6502.h>

long clock(void) {
	ControlPort.function = API_FN_TIMER;
	ControlPort.command = API_GROUP_SYSTEM;
	while (ControlPort.command);
	return *((long*) ControlPort.params);
}
