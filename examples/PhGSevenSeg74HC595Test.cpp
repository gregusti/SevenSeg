#include <SevenSeg74HC595.h>

SevenSeg74HC595 disp(9, 8, 10);

const int numOfDigits=4;

// Digit                     1  2  3  4
// 5461AS                    6  3  2 12
int digitPins[numOfDigits]={5, 4, 3, 2};

char banner[5]="8-8-";
void setup() {
	// put your setup code here, to run once:
	disp.setDigitPins(numOfDigits, digitPins);
	disp.setCommonCathode();

	//disp.setDPPin(4);

	disp.setTimer(2) ;
	disp.startTimer();

	// Counter loop
	disp.write(banner);

	Serial.begin(115200);
	Serial.println("ready");
}

// forward def prototypes
void serialInLoop();
void scrollLoop();
void snakeLoop();

// Main loop, uncomment one of the 3 test loops
void loop() {
	//serialInLoop();
	scrollLoop();
	//snakeLoop();
}

// Loop that displays characters entered on serial
void serialInLoop() {
	if(Serial.available()) {
		char c=Serial.read();
		banner[0]=banner[1];
		banner[1]=banner[2];
		banner[2]=banner[3];
		banner[3]=c;
		Serial.println(banner);

		// write
		disp.write(banner);
	}
}

const char snakePos[]={
	0b10000011,
	0b10000110,
	0b10001100,
	0b10011000,
	0b10110000,
	0b10100001,

	0b10000011,
	0b10000110,
	0b10001100,
	0b10011000,
	0b10110000,
	0b10100001,

	0b10000011,
	0b11000010,
	0b11010000,
	0b10011000,
	0b10001100,
	0b11000100,
	0b11100000,
	0b10100001,
};

#define _LEN(array) (sizeof(array)/sizeof(*array))

#define WAIT_UNIT 10
int snake=0;
int wait=WAIT_UNIT*10;
// loop that gets a snake around, using the 7th bit set
void snakeLoop() {

	for(int j=0;j<numOfDigits;j++) {
		banner[j]=snakePos[(j+snake)%_LEN(snakePos)];
	}

	disp.write(banner);
	if(Serial.available()) {
		int speed=Serial.read();
		switch(speed) {
		case '+': if(wait>WAIT_UNIT) wait-=WAIT_UNIT; break;
		case '-': wait+=WAIT_UNIT; break;
		case '=': wait=WAIT_UNIT*10; break;
		}
	}
	snake++;
	delay(wait);
}

// loop that scrolls a banner across, with letters from the scroll char* here
const char* scroll="AbCdEF_0123456789_ABCDEFGHIJKLMNOPQRSTUVWXYZ_[]=-_#<>/\\\"'^?|{};:`!,";
int count=0;
// Test all characters in a scroll banner
void scrollLoop() {
	// scroll loop
	for(int i=0;i<4;i++) {
		banner[i]=scroll[(i+count)%strlen(scroll)];
	}

	// Counter loop
	disp.write(banner);

	//disp.write(count);
	delay(500);
	count++;
}

ISR( TIMER2_COMPA_vect ) {
	disp.interruptAction ();
}
