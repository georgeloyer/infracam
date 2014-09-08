/*
 * infracam.c
 * Description
 * Test programs for the infracam project
 *
 * History:
 *   2014-09-01  gel first tests
 *

 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softTone.h>

#define SWITCH    0       // GPIO pin for switch
#define BEEP      1       // GPIO pin for beeper
#define PIEZO     3       // GPIO pin for piezo speaker

/*
 * ******************************************************************************
 * local functions
 * ******************************************************************************
 */

/* beeper */
void beeper(int beeps [], int numbeeps) {
  int i;
  for (i = 0; i < numbeeps; i++ ) {
		digitalWrite(BEEP,1);	        // beep on
		delay(beeps[i]);              // length of beep from beeps list
		digitalWrite(BEEP,0);	        // beep off
		delay(25);                    // interval between beeps
  }
}

 /* myInterrupt: gotButton */

void gotButton(void) {
  int twobeeps [] = { 50, 50 } ;
  int numtwobeeps = sizeof(twobeeps) /sizeof(twobeeps[0]);
  printf ("Got a button press");
  beeper (twobeeps, numtwobeeps);
  return ;
}
/*
 *********************************************************************************
 * main
 *********************************************************************************
 */

int main (void) {
  int sequence [] = { 262, 294, 330, 349, 392, 440, 494, 525, 0 } ;
  int numsequence = sizeof(sequence) / sizeof (sequence[0]);
  int vbeep [] = { 50, 50, 50, 200 } ;
  int numvbeep = sizeof(vbeep) / sizeof(vbeep[0]);
  int onebeep [] = { 50 } ;
  int numonebeep = sizeof(onebeep) / sizeof(onebeep[0]);

  wiringPiSetup();                //For the original sequential pin numbering
  pinMode (SWITCH, INPUT);            // Pin for switch, INPUT
  pullUpDnControl (SWITCH, PUD_DOWN);   // set pull UP resistor for switch
  pinMode (BEEP, OUTPUT);             // beeper pin, OUTPUT
  softToneCreate(PIEZO) ;             // initialize softTone 

  wiringPiISR(SWITCH, INT_EDGE_RISING, &gotButton) ;
  int k=3 ;
  int i;

  while (k>0) {
	  for ( i=0 ; i<numsequence; i++ ) {
		  printf("%d\n", sequence[i]);
		  softToneWrite (PIEZO, sequence[i]);
		  delay(500);
    }
	  beeper (onebeep, numonebeep);
	  k--;
  }
  delay(500);
  beeper (vbeep, numvbeep);
  return 0;
}


