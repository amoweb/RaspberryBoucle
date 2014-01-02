#ifndef IHM_C
#define IHM_C

/**
 * Initialization of IHM
 **/
void IHMinit();

/**
 * Indicate the mouse state
 * @require : call IHMinit
 * @return 'L', 'M', 'R', if left, middle, or
 * right button of the mouse activated, or 0
 **/
char IHMuserEntry();

#endif
