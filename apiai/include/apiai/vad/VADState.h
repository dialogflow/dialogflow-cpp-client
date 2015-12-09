#ifndef VAD_STATE_H
#define VAD_STATE_H

typedef enum {
    VADStateError = -2,
    VADStateUnknown = -1,
    VADStateInProgress = 1,
    VADStateEndOfSpeech = 2,
    VADStateNoSpeech = 3
} VADState;

#endif // VAD_H
