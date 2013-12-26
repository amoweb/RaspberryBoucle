#ifndef MIDI_H
#define MIDI_H

#include <stdbool.h>

struct Note {
        int note;
        int vol;
        long t;
};

bool midiInit();
void midiOpenDevice(int inId, int outId);
bool inputAvailable();
void midiNoteOn(int note, int velocity);
void midiNoteOff(int note);
void midiReadLast(struct Note *note);

#endif
