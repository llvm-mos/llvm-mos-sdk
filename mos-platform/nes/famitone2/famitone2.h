#ifndef _FAMITONE2_H_
#define _FAMITONE2_H_

#ifdef __cplusplus
extern "C" {
#endif

// Set up music data in bank always accessible to Famitone2 code.
__attribute__((leaf)) void music_init(const void *music_data);

// Set up music data in bank that must be switched to.
__attribute__((leaf)) void banked_music_init(char bank, const void *music_data);

// play a music in FamiTone format
__attribute__((leaf)) void music_play(char song);

// stop music
__attribute__((leaf)) void music_stop(void);

// pause and unpause music
__attribute__((leaf)) void music_pause(char pause);

// Set up sounds data in bank always accessible to Famitone2 code.
__attribute__((leaf)) void sounds_init(const void *sounds_data);

// Set up sounds data in bank that must be switched to.
__attribute__((leaf)) void banked_sounds_init(char bank,
                                              const void *sounds_data);

// play FamiTone sound effect on channel 0..3
__attribute__((leaf)) void sfx_play(char sound, char channel);

// play a DPCM sample, 1..63
__attribute__((leaf)) void sample_play(char sample);

#ifdef __cplusplus
}
#endif

#endif // _FAMITONE2_H_
