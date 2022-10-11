#ifndef _ZAPLIB_H_
#define _ZAPLIB_H_

#ifdef __cplusplus
extern "C" {
#endif

// written by Doug Fraker 2019-2020
// NES zapper gun code

// pass it 0 or 1, which port
// returns 0 or 1 if trigger pulled
__attribute__((leaf)) char zap_shoot(char pad);

// pass it 0 or 1, which port
// returns 0 or 1 if detects light this frame
__attribute__((leaf)) char zap_read(char pad);

// alt. version from "Falling Tiles" game.
// always reads from port 2
// pass it 1-224, NOT zero
// = approximately how many scanlines to keep reading
// note, PAL will need a little more than NTSC
// allows you to avoid lag frames on misses.
// "Falling Tiles" used 196 for shooting low objects
// and 176 for shooting objects that are higher
// and should exit this loop before the end of the frame.

// returns 0 or 1 if detects light this frame
__attribute__((leaf)) char zap_read2(char pad);

#ifdef __cplusplus
}
#endif

#endif // _ZAPLIB_H_
