#ifndef _FAMITONE2_H_
#define _FAMITONE2_H_

#ifdef __cplusplus
extern "C" {
#endif

// play a music in FamiTone format
__attribute__((leaf)) void music_play(unsigned char song);

// stop music
__attribute__((leaf)) void music_stop(void);

// pause and unpause music
__attribute__((leaf)) void music_pause(char pause);

// play FamiTone sound effect on channel 0..3
__attribute__((leaf)) void sfx_play(char sound, char channel);

// play a DPCM sample, 1..63
__attribute__((leaf)) void sample_play(char sample);

#ifdef __cplusplus
}
#endif

#endif // _FAMITONE2_H_
