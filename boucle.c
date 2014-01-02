#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <porttime.h>
#include "midi.h"
#include "ihm.h"

#define TAB_SIZE 1000

struct Note record[TAB_SIZE];

int main()
{
        printf("Boucle Midi - amoweb.fr\n");

        IHMinit();

        if(midiInit())
                exit(-1);

        midiOpenDevice(3, 2);

beginRecord:
        while(true) {
                // Record
                int tStartRecord = 0;
                int pos = 0;
                while(true) {
                        // New event
                        if(inputAvailable()) {
                                midiReadLast(&(record[pos%TAB_SIZE]));
                                if(tStartRecord == 0) {
                                        tStartRecord = record[pos%TAB_SIZE].t;
                                        printf("Recording\n");
                                }

                                pos++;
                        }
                        // User entry
                        if(IHMuserEntry()){
                                break;
                        }
                }
                
                printf("Recorded=%d t=%ld\n", pos, record[pos%TAB_SIZE].t-tStartRecord);

                // Play
                while(true) {
                        if(pos == 0)
                                goto beginRecord;
                        printf("Playing\r\n");
                        int tStartPlay = Pt_Time(NULL);
                        for(int i=0; i<pos; i++) {
                                while(Pt_Time(NULL)-tStartPlay < record[i].t-tStartRecord) {
                                        if(IHMuserEntry())
                                                goto beginRecord;
                                        midiFlush();
                                }

                                midiWrite(&record[i]);
                                i++;
                        }
                }
                pos = 0;
                midiFlush();
        }
}
