#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <porttime.h>
#include "midi.h"

#define TAB_SIZE 1000

struct Note record[TAB_SIZE];

int main()
{
        printf("Boucle Midi - amoweb.fr\n");

        if(midiInit())
                exit(-1);

        midiOpenDevice(3, 2);

        midiNoteOn(60, 100);
        int pos = 0;
        while(true) {
                // New score
                if(inputAvailable()) {
                        midiReadlast(&(record[pos%TAB_SIZE]));
                        //record[pos].t ;
                        pos++;
                        //midiNoteOn(80, 100);
                }
                if(pos == 15) {
                        int tStartPlay = Pt_Time(NULL);
                        for(int i=0; i<pos; i++) {
                                while(Pt_Time(NULL)-tStartPlay < record[i].t) {
                                        // rien
                                }
                                midiNoteOn(record[i].note, record[i].vol);
                                i++;
                        }
                        pos = 0;
                }
        }
}
