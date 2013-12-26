#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <portmidi.h>
#include <porttime.h>
#include "midi.h"

#define INPUT_BUFFER_SIZE 100
#define OUTPUT_BUFFER_SIZE 0

PmEvent outBuffer[1];
PmEvent inBuffer[INPUT_BUFFER_SIZE];

PmStream *in, *out;
bool midiInit()
{
        Pm_Initialize();

        int portIn = -1;
        int portOut = -1;
        /* List device information */
        for (int i = 0; i < Pm_CountDevices(); i++) {
                const PmDeviceInfo *info = Pm_GetDeviceInfo(i);
                if ((info->input) || (info->output)) {
                        printf("%d: %s, %s", i, info->interf, info->name);
                        if (info->input) {
                                portIn = i;
                                printf(" (input)");
                        }

                        if (info->output) {
                                portOut = i;
                                printf(" (output)");
                        }
                        printf("\n");
                }
        }

        if(portOut == -1 || portIn == -1) {
                printf("Midi port not found.\r\n");
                return -1;
        }

        return false;
}

void midiOpenDevice(int inId, int outId)
{
        // Open input
        Pm_OpenInput(&in, inId, NULL, INPUT_BUFFER_SIZE, 
                        (PmTimestamp (*)(void *)) Pt_Time, NULL);
        Pm_SetFilter(in, PM_FILT_ACTIVE | PM_FILT_CLOCK);
        

        // Open output
        Pm_OpenOutput(&out, outId, NULL, OUTPUT_BUFFER_SIZE,
                        (PmTimestamp (*)(void *)) Pt_Time, NULL, 0);

}

bool inputAvailable()
{
        if(Pm_Poll(in) == 1)
                return true;
        else if(Pm_Poll(in) == 0)
                return false;
        //else
        //        printf("Error while reading midi input.\r\n");
        return false;
}

void midiNoteOn(int note, int vol)
{
        outBuffer[0].timestamp = Pt_Time(NULL);
        outBuffer[0].message = Pm_Message(0x90, note, vol); /* program change */
        Pm_Write(out, outBuffer, 1);
}


void midiNoteOff(int note)
{
        midiNoteOn(note, 0);
}

void midiReadLast(struct Note *note)
{
        Pm_Read(in, inBuffer, 1);
        note->t = inBuffer[0].timestamp;
        note->note = Pm_MessageData1(inBuffer[0].message);
        note->vol = Pm_MessageData2(inBuffer[0].message);
}
