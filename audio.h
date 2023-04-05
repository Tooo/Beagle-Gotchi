// audio.h
// Referred to Brian Fraser code, which is heavily based on code found at:
// http://www.alsa-project.org/alsa-doc/alsa-lib/_2test_2pcm_min_8c-example.html
#ifndef AUDIO_H_
#define AUDIO_H_

// Initialize/cleanup the module's data structures.
void Audio_init();
void Audio_cleanup();

void Audio_playSoundWithThread(char *fileName);
void Audio_joinThread();

#endif
