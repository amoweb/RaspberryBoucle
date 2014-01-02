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

/**
 * Initialisation of midi I/O
 **/
bool midiInit();

/**
 * Open the devices
 * @param inId  input device ID
 * @param outId output device ID
 **/
void midiOpenDevice(int inId, int outId);

/**
 * @return true if the a new score was received
 **/
bool inputAvailable();

/**
 * Send a score
 **/
void midiNoteOn(int note, int velocity);

/**
 * Stop a score
 **/
void midiNoteOff(int note);

/**
 * Read the last midi event
 **/
void midiReadLast(struct Note *note);

/**
 * Write a midi event
 **/
void midiWrite(struct Note *note);

/**
 * Flush the midi input
 **/
void midiFlush();

#endif
