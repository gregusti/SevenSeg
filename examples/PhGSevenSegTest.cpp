#include <SevenSeg.h>

// Segment     A  B  C  D  E  F  G  .
// 5461AS     11  7  4  2  1 10  5  3
SevenSeg disp(11, 7, 3, 5, 6,10, 2, 4);

const int numOfDigits=4;

// Digit                     1  2  3  4
// 5461AS                    6  3  2 12
int digitPins[numOfDigits]={12, 9, 8,13};

void setup() {
	// put your setup code here, to run once:
	disp.setDigitPins(numOfDigits, digitPins);
	disp.setCommonCathode();
	//disp.setDPPin(4);

	disp.setTimer(2) ;
	disp.startTimer();

	Serial.begin(115200);
}

const char* scroll="AbCdEF0123456789-LPqSUy[]='\"oABCDEFGHIJKLMNOPQRSTUVWXYZ";
//const char* scroll="A0123456789F";
int count=0;
void loop() {

	//disp.write(8);
	//disp.write(888);
	//disp.write(8888);
	//disp.write("1738");

	// scroll loop
	char d[5]="0000";
	for(int i=0;i<4;i++) {
		d[i]=scroll[(i+count)%strlen(scroll)];
	}

	// Counter loop
	disp.write(d);

	//disp.write(count);
	delay(500);
	count++;
}

ISR( TIMER2_COMPA_vect ) {
	disp.interruptAction ();
}
