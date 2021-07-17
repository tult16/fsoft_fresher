#include <stdio.h>
#include "main.h"

int TIME_WAIT_SPACE = 800;
int TIME_DOT_MIN = 150;
int TIME_DOT_MAX = 375;
int TIME_DASH_MIN = 500;
int TIME_DASH_MAX = 1000;

//Hardware millisecond timer
void delay(unsigned short ms){

	SIM_SCGC6 |= (1 << 24); //Enable clock gate for TPM0
	SIM_SOPT2 |= (0x2 << 24); //Use OSCERCLK setting
	TPM0_CONF |= (0x1 << 17); //Stop when overflow
	TPM0_SC = (1 << 7) | (0x7); //Set prescaler to 128

	TPM0_MOD = ms*62 + ms/2 - 1; //Set the MOD register

	TPM0_SC |= 0x01 << 3; //Start timer

	while (!(TPM0_SC & 0x80)) {} //Do nothing while waiting for the flag

	return;
}

//Setup the ADC module
void SetupADC(){ 
	int cal_v;

	//Enable clock gate for ADC0
	SIM_SCGC6 |= (1 << 27);

	// Setup ADC Clock ( < 4 MHz)
	ADC0_CFG1 = 0;  // Default everything.

	// Analog Calibrate
	ADC0_SC3 = 0x07; // Enable Maximum Hardware Averaging
	ADC0_SC3 |= 0x80; // Start Calibration

	// Wait for Calibration to Complete (either COCO or CALF)
	while(!(ADC0_SC1A & 0x80)){	}


	// Calibration Complete, write calibration registers.
	cal_v = ADC0_CLP0 + ADC0_CLP1 + ADC0_CLP2 + ADC0_CLP3 + ADC0_CLP4 + ADC0_CLPS;
	cal_v = cal_v >> 1 | 0x8000;
	ADC0_PG = cal_v;

	cal_v = 0;
	cal_v = ADC0_CLM0 + ADC0_CLM1 + ADC0_CLM2 + ADC0_CLM3 + ADC0_CLM4 + ADC0_CLMS;
	cal_v = cal_v >> 1 | 0x8000;
	ADC0_MG = cal_v;


	ADC0_SC3 = 0; // Turn off Hardware Averaging

	return;
}

//Decode a string of morse .-.- to a letter
char DecodeMorse(char * morse){

	//PRINTF("\r\nChecking %s \r\n", morse);
	//PRINTF("\r\nStrcmp: %d\r\n", strcmp(morse, "..."));

	if (strcmp(morse, ".-") == 0){ //Compare the string of morse to be exact
		return((char)'a'); //Return a letter if found.
	}
	else if (strcmp(morse, "-...") == 0){
		return((char)'b');
	}
	else if (strcmp(morse, "-.-.") == 0){
		return((char)'c');
	}
	else if (strcmp(morse, "-..") == 0){
		return((char)'d');
	}
	else if (strcmp(morse, ".") == 0){
		return((char)'e');
	}
	else if (strcmp(morse, "..-.") == 0){
		return((char)'f');
	}
	else if (strcmp(morse, "--.") == 0){
		return((char)'g');
	}
	else if (strcmp(morse, "....") == 0){
		return((char)'h');
	}
	else if (strcmp(morse, "..") == 0){
		return((char)'i');
	}
	else if (strcmp(morse, ".---") == 0){
		return((char)'j');
	}
	else if (strcmp(morse, "-.-") == 0){
		return((char)'k');
	}
	else if (strcmp(morse, ".-..") == 0){
		return((char)'l');
	}
	else if (strcmp(morse, "--") == 0){
		return((char)'m');
	}
	else if (strcmp(morse, "-.") == 0){
		return((char)'n');
	}
	else if (strcmp(morse, "---") == 0){
		return((char)'o');
	}
	else if (strcmp(morse, ".--.") == 0){
		return((char)'p');
	}
	else if (strcmp(morse, "--.-") == 0){
		return((char)'q');
	}
	else if (strcmp(morse, ".-.") == 0){
		return((char)'r');
	}
	else if (strcmp(morse, "...") == 0){
		return((char)'s');
	}
	else if (strcmp(morse, "-") == 0){
		return((char)'t');
	}
	else if (strcmp(morse, "..-") == 0){
		return((char)'u');
	}
	else if (strcmp(morse, "...-") == 0){
		return((char)'v');
	}
	else if (strcmp(morse, ".--") == 0){
		return((char)'w');
	}
	else if (strcmp(morse, "-..-") == 0){
		return((char)'x');
	}
	else if (strcmp(morse, "-.--") == 0){
		return((char)'y');
	}
	else if (strcmp(morse, "--..") == 0){
		return((char)'z');
	}
	else if (strcmp(morse, "-----") == 0){
		return((char)'0');
	}
	else if (strcmp(morse, ".----") == 0){
		return((char)'1');
	}
	else if (strcmp(morse, "..---") == 0){
		return((char)'2');
	}
	else if (strcmp(morse, "...--") == 0){
		return((char)'3');
	}
	else if (strcmp(morse, "....-") == 0){
		return((char)'4');
	}
	else if (strcmp(morse, ".....") == 0){
		return((char)'5');
	}
	else if (strcmp(morse, "-....") == 0){
		return((char)'6');
	}
	else if (strcmp(morse, "--...") == 0){
		return((char)'7');
	}
	else if (strcmp(morse, "---..") == 0){
		return((char)'8');
	}
	else if (strcmp(morse, "----.") == 0){
		return((char)'9');
	}else{
		return((char)'?'); //Could not be found.
	}

}

int main(void)
{

    hardware_init();
    dbg_uart_init();

    SetupADC();

	SIM_SCGC5 |= (1<<13); // Enable Light Sensor I/O Port
	SIM_SCGC5 |= (1<<12); //Enable green LED

	PORTD_PCR5 &= ~0x700; // Clear First
	PORTD_PCR5 |= 0x700 & (1 << 8); // Set MUX bits
	GPIOD_PDDR |= (1 << 5); //Set green LED as output

    PRINTF("\r\n\nStarting.\n\r\n");

    int light_val;
    int sensitivity = 240;

    short detected = 0; //Boolean, whether or not light is being detected.
    short counting_low = 0; //Whether or not we are counting the length of the pause

    int count = 0; //How many cycles the light have been on
    int count_low = 0; //How many cycles the light has been off

    int resolution = 25; //Delay time resolution for the conversion

    int character = 0; //Number of characters detected in this morse sequence

    char* sequence = malloc(16); //allocate a decent character array
    sequence[16] = '\0'; //put end character line

    //Clear sequence
    for (int i = 0; i < 16; i++){
    	sequence[i] = '\0';
    }

    PRINTF("\rReady.\r\n\n");


    //functional program loop
	while(1) {

		ADC0_SC1A = 0x03; //Prepare ADC for data

		while(!(ADC0_SC1A & 0x80)){	} //Collecting data

		delay(resolution); //We can detect signals at a resolution defined by how long to wait

		light_val = ADC0_RA; 		//Get the result


		//Main light logic
		if (light_val < sensitivity) { //Light detected
			GPIOD_PDOR &= ~(1<<5);  //Light detected, enable active low LED

			if (detected == 0){  //Transition from not detected to detected
				detected = 1; //Now we are detecting
			}else{
				count++;   //Still receiving signal, increment count of how long the light is on in cycles (resolution time)
			}
		}

		else { //Light not detected

			if (detected == 1){  //This is a transition from detection to end of detection
				detected = 0; //We are no longer detecting
				GPIOD_PDOR |= (1<<5);  //Light not detected, disable LED (active low)

				counting_low = 1; //Enable counting dark time.
				count_low = 0; //Reset dark counter.

				if (count*resolution >= TIME_DOT_MIN && count*resolution <= TIME_DOT_MAX){ //Pulse approximately 150 to 375 milliseconds, or dot.
					//PRINTF("\r\nDot\r");
					sequence[character] = '.'; //Append a dot to the character array of dot-dash morse to be decoded
					character++; //Increment character index

				}else if (count*resolution >= TIME_DASH_MIN && count*resolution <= TIME_DASH_MAX){ //Pulse was 500 to 1000 milliseconds, or dash.
					//PRINTF("\r\nDash.\r");
					sequence[character] = '-'; //Append a dash to the array
					character++; //Next character

				}else{ //Not a character in morse
					//Do nothing

				}

				detected = 0; //No longer detected so set flag back to disabled in case it hasn't already
				count = 0; //Reset counter for next on cycle counting

			}else{ //Has not been detecting
				if (counting_low){ //If we are supposed to be counting dark time
					count_low++; //Keep counting the length of pause

					if (count_low * resolution >= TIME_WAIT_SPACE){ //If we have xceeded time for a space,

						if (sequence[0] != ' '){ //If there were any characters in the sequence, space in 0 means it is not a sequence
							PRINTF("\r\nThe sequence was %s\r\n", sequence); //Other wise print the sequence

							char result = DecodeMorse(sequence); //Decode the morse Sequence (big if statement)

							PRINTF("\rThe program guesses: %c \r\n", result); //Display the decoded letter

							//Clear sequence
						    for (int i = 0; i < 16; i++){
						    	sequence[i] = '\0';
						    }
						}

						character = 0; //Reset amount of characters for this conversion due to space.
						count_low = 0; //no longer need to keep counting the time off, because we are past time for a space.
						counting_low = 0; //Stop counting low.
					}

					//PRINTF("\r\n%d\r\n", count_low * resolution); //Print milliseconds of dark time

				} // else not counting low, do nothing
			}
			detected = 0; //No longer detected light
		}
		//End light logic, restart loop
	}

	return 0;

}
