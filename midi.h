#ifndef MIDI_H
#define MIDI_H

#include <stdbool.h>

#define MIDI_STATUS_NOTE 0x90

struct Note {
        int note;
        int vol;
        int status;
        long t;
};

bool midiInit();
void midiOpenDevice(int inId, int outId);
bool inputAvailable();
void midiNoteOn(int note, int velocity);
void midiNoteOff(int note);
void midiReadLast(struct Note *note);
void midiWrite(struct Note *note);
void midiFlush();

#endif
