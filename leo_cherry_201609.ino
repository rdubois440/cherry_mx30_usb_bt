//	Todo
//	BT Bluefruit connection
//	left alt ctrl shift 		usb mode
//	left alt ctrl right shift 	bt mode


// build line
//rene@Sony:~/develop/arduino/leo_cherry_201609$ /opt/arduino-1.6.5-r5/arduino --board arduino:avr:micro --port /dev/ttyACM0  --upload leo_cherry_201609.ino


//Total keys
//13 + 14 + 14 + 13 + 13 + 8 + 4 = 79

/* Cherry MX 30 Layout - Connected Pin 4 - White (Yellow Green Blue)- Row

   D12 - 	Esc		Left\	F4	F5	F6		Rshift		LAlt	G	H	"
   D13 -	~		F1		F2		F9		=		F8		LCtrl	5 6 	-	
   D14 - 	Tab		CapsLock	F3	Bspace	F7 LShift T	Y I	[					Yellow - 	MISO
   D15 -	1	2	F10	8	9	4	7	0										Green - 	SCK	
   D16 -	
   D17 - 	Not accessible
   D18 -	Q	W	E	O	R	U	P
   D19 -	A	S	D	F	J	K	L	;
   D20 -	Z	X	C	V	m	,	.
   D21 -	B	N	Space	?	RAlt	down left right
    -	R\	RShift	
 */


/* Cherry MX 30 Layout - Connected Pin 1  Green - Column 

   D2 - 	Esc 	~	1	Q	A	Z	lwin 	Tab
   D3 -	F2	F3	F4	3	E	C
   D4 -	F1	2	W	S	X
   D5 -	F5	F9	F10	Space	BSP	Enter
   D6 -	F6	=	8	]	I	K	
   D7 -	F7	F8	9	O	L	.	RShift	
   D8 -	F11	Del	Down	
   D9 -	4	5	R	T	F	G	V	B
   D10 -	6	7	U	Y	H	J	N	M	CapsLock
   D11 -	-	P	[	; 	'	\	/Right	

   D -	Lctrl	Lalt	Lshif	Ralt	Rctl
   D -	Up	Left
   D9 -	F12	Ins	Right	
   Unconnected or unknown RWin Rctl Down Right 
 */




/*Cherry MX Keys pinout. Solder side
  1 and 2 connected on press
  2 and 3 connected by printed circuit
  3 and 4 alays connected by a diode. Cathode on 4, Anode on 3

  1
  2

  3	4
 */

#define MODE_USB 	0
#define MODE_BT 	1


char keyLookup[10 * 10];
char winKeyLookup[10 * 10];

char btLookup[10 * 10];
int isLWinDown;
int mode;

int rowCounter =0; // row counter
int columnCounter =0; // column counter
int foundColumn = 0;
boolean foundCol = false;
int keyValue = 0;
int noKey = 0;
boolean readKey = false;
int debounce = 5; // set this to the lowest value that gives the best result


// Columns - White - Set the line low one by one
const int row1 = 12;
const int row2 = 13;
const int row3 = 14;
const int row4 = 15;
const int row5 = 16;
const int row6 = 17;
const int row7 = 18;
const int row8 = 19;
const int row9 = 20;
const int row10= 21;


// Rows - Green - Check for low lines
const int colA = 2;
const int colB = 3;
const int colC = 4;
const int colD = 5;
const int colE = 6;
const int colF = 7;
const int colG = 8;
const int colH = 9;
const int colI = 10;
const int colJ = 11;

const int ledPin = 13; // onboard LED

int isKeyPressed[256];
int wasKeyPressed[256];

int previousKey;

//char usb2ascii[256];

void setup()
{
		Serial.begin(115200);
		Serial1.begin(9600);

		pinMode(row1, OUTPUT);
		pinMode(row2, OUTPUT);
		pinMode(row3, OUTPUT);
		pinMode(row4, OUTPUT);
		pinMode(row5, OUTPUT);
		pinMode(row6, OUTPUT);
		pinMode(row7, OUTPUT);
		pinMode(row8, OUTPUT);
		pinMode(row9, OUTPUT);
		pinMode(row10, OUTPUT);

		pinMode(colA, INPUT_PULLUP);
		pinMode(colB, INPUT_PULLUP);
		pinMode(colC, INPUT_PULLUP);
		pinMode(colD, INPUT_PULLUP);
		pinMode(colE, INPUT_PULLUP);
		pinMode(colF, INPUT_PULLUP);
		pinMode(colG, INPUT_PULLUP);
		pinMode(colH, INPUT_PULLUP);
		pinMode(colI, INPUT_PULLUP);
		pinMode(colJ, INPUT_PULLUP);

		pinMode(ledPin, OUTPUT);

		digitalWrite(ledPin, LOW); // turn LED off
		Keyboard.begin();

		keyValue = 0;
		previousKey = 0;

		for(int i=0; i<256; i++)
		{
				isKeyPressed[i] = 0;
				wasKeyPressed[i] = 0;
		}

	//	keyLookup[row * 10 + col] = 0;
		keyLookup[0] = KEY_ESC;
		keyLookup[1] = KEY_F4;		
		//keyLookup[2] = '\\';		// No key press on left \
		keyLookup[3] = KEY_F5;
		keyLookup[4] = KEY_F6;
		keyLookup[5] = KEY_RIGHT_SHIFT;
		keyLookup[6] = KEY_LEFT_ALT;
		keyLookup[7] = 'g';
		keyLookup[8] = 'h';
		keyLookup[9] = '\'';

		keyLookup[10] = '`';
		keyLookup[11] = KEY_F2;
		keyLookup[12] = KEY_F1;
		keyLookup[13] = KEY_F9;
		keyLookup[14] = '=';
		keyLookup[15] = KEY_F8;
		keyLookup[16] = KEY_LEFT_CTRL;
		keyLookup[17] = '5';
		keyLookup[18] = '6';
		keyLookup[19] = '-';

		keyLookup[20] = KEY_TAB;
		keyLookup[21] = KEY_F3;
		//keyLookup[22] = KEY_CAPS_LOCK; // No key press for caps lock
		keyLookup[23] = KEY_BACKSPACE;
		keyLookup[24] = ']';
		keyLookup[25] = KEY_F7;
		keyLookup[26] = KEY_LEFT_SHIFT;
		keyLookup[27] = 't';
		keyLookup[28] = 'y';
		keyLookup[29] = '[';

		keyLookup[30] = '1';
		keyLookup[31] = '3';
		keyLookup[32] = '2';
		keyLookup[33] = KEY_F10;
		keyLookup[34] = '8';
		keyLookup[35] = '9';
		keyLookup[36] = 0xce;			// F11 is print screen
		keyLookup[37] = '4';
		keyLookup[38] = '7';
		keyLookup[39] = '0';

		keyLookup[42] = 0xed;	// App Key
		keyLookup[49] = KEY_UP_ARROW;	// App Key

		keyLookup[50] = KEY_ESC;
		keyLookup[51] = KEY_F4;
		keyLookup[52] = KEY_F4;
		keyLookup[53] = KEY_F5;
		keyLookup[54] = KEY_F6;
		keyLookup[55] = KEY_F6;
		keyLookup[56] = KEY_F6;
		keyLookup[57] = KEY_F6;
		keyLookup[58] = KEY_F6;
		keyLookup[59] = KEY_F6;

		keyLookup[60] = 'q';
		keyLookup[61] = 'e';
		keyLookup[62] = 'w';
		keyLookup[63] = KEY_RETURN;
		keyLookup[64] = 'i';
		keyLookup[65] = 'o';
		keyLookup[66] = KEY_DELETE;		// F12 is delete
		keyLookup[67] = 'r';
		keyLookup[68] = 'u';
		keyLookup[69] = 'p';

		keyLookup[70] = 'a';
		keyLookup[71] = 'd';
		keyLookup[72] = 's';
		keyLookup[74] = 'k';
		keyLookup[75] = 'l';
		keyLookup[76] = KEY_RIGHT_GUI;
		keyLookup[77] = 'f';
		keyLookup[78] = 'j';
		keyLookup[79] = ';';

		keyLookup[80] = KEY_LEFT_GUI;
		keyLookup[82] = KEY_LEFT_ARROW;
		keyLookup[83] = ' ';
		keyLookup[84] = KEY_DOWN_ARROW;
		keyLookup[85] = KEY_RIGHT_ARROW;
		keyLookup[86] = KEY_RIGHT_ALT;
		keyLookup[87] = 'b';
		keyLookup[88] = 'n';
		keyLookup[89] = '/';

		keyLookup[90] = 'z';
		keyLookup[91] = 'c';
		keyLookup[92] = 'x';
		keyLookup[94] = ',';
		keyLookup[95] = '.';
		keyLookup[96] = KEY_RIGHT_CTRL;
		keyLookup[97] = 'v';
		keyLookup[98] = 'm';
		keyLookup[99] = '\\';

	// 	winKeyLookup contains a different mapping, used when Left Win key is down
	//	winKeyLookup[row * 10 + col] = 0;
		winKeyLookup[0] = KEY_ESC;
		winKeyLookup[1] = KEY_F4;
		//winKeyLookup[2] = '\\';		// No key press on left \
		winKeyLookup[3] = KEY_F5;
		winKeyLookup[4] = KEY_F6;
		winKeyLookup[5] = KEY_RIGHT_SHIFT;
		winKeyLookup[6] = KEY_LEFT_ALT;
		winKeyLookup[7] = 'g';
		winKeyLookup[8] = 'h';
		winKeyLookup[9] = '\'';

		winKeyLookup[10] = '`';
		winKeyLookup[11] = KEY_F12; 		// F2 is F12 when lwin is down
		winKeyLookup[12] = KEY_F11;			// F1 is F11 when lwin is down
		winKeyLookup[13] = KEY_F9;
		winKeyLookup[14] = '=';
		winKeyLookup[15] = KEY_F8;
		winKeyLookup[16] = KEY_LEFT_CTRL;
		winKeyLookup[17] = '5';
		winKeyLookup[18] = '6';
		winKeyLookup[19] = '-';

		winKeyLookup[20] = KEY_TAB;
		winKeyLookup[21] = KEY_F3;
		//winKeyLookup[22] = KEY_CAPS_LOCK; // No key press for caps lock
		winKeyLookup[23] = KEY_BACKSPACE;
		winKeyLookup[24] = ']';
		winKeyLookup[25] = KEY_F7;
		winKeyLookup[26] = KEY_LEFT_SHIFT;
		winKeyLookup[27] = 't';
		winKeyLookup[28] = 'y';
		winKeyLookup[29] = '[';

		winKeyLookup[30] = '1';
		winKeyLookup[31] = '3';
		winKeyLookup[32] = '2';
		winKeyLookup[33] = KEY_F10;
		winKeyLookup[34] = '8';
		winKeyLookup[35] = '9';
		winKeyLookup[36] = 0xce;			// F11 is Print screen
		winKeyLookup[37] = '4';
		winKeyLookup[38] = '7';
		winKeyLookup[39] = '0';

		winKeyLookup[42] = 0xed;	// App Key
		winKeyLookup[49] = KEY_PAGE_UP;	// Arrow up is page up when lwin is pressed

		winKeyLookup[50] = KEY_ESC;
		winKeyLookup[51] = KEY_F4;
		winKeyLookup[52] = KEY_F4;
		winKeyLookup[53] = KEY_F5;
		winKeyLookup[54] = KEY_F6;
		winKeyLookup[55] = KEY_F6;
		winKeyLookup[56] = KEY_F6;
		winKeyLookup[57] = KEY_F6;
		winKeyLookup[58] = KEY_F6;
		winKeyLookup[59] = KEY_F6;

		winKeyLookup[60] = 'q';
		winKeyLookup[61] = 'e';
		winKeyLookup[62] = 'w';
		winKeyLookup[63] = KEY_RETURN;
		winKeyLookup[64] = 'i';
		winKeyLookup[65] = 'o';
		winKeyLookup[66] = KEY_DELETE;		// F12 is delete
		winKeyLookup[67] = 'r';
		winKeyLookup[68] = 'u';
		winKeyLookup[69] = 'p';

		winKeyLookup[70] = 'a';
		winKeyLookup[71] = 'd';
		winKeyLookup[72] = 's';
		winKeyLookup[74] = 'k';
		winKeyLookup[75] = 'l';
		winKeyLookup[76] = KEY_RIGHT_GUI;
		winKeyLookup[77] = 'f';
		winKeyLookup[78] = 'j';
		winKeyLookup[79] = ';';

		winKeyLookup[80] = KEY_LEFT_GUI;
		winKeyLookup[82] = KEY_HOME;		// left arrow is home when lwin is down
		winKeyLookup[83] = ' ';
		winKeyLookup[84] = KEY_PAGE_DOWN;	// down arrow is page down when lwin is down
		winKeyLookup[85] = KEY_END;			// right arrow is End when lwin is down
		winKeyLookup[86] = KEY_RIGHT_ALT;
		winKeyLookup[87] = 'b';
		winKeyLookup[88] = 'n';
		winKeyLookup[89] = '/';

		winKeyLookup[90] = 'z';
		winKeyLookup[91] = 'c';
		winKeyLookup[92] = 'x';
		winKeyLookup[94] = ',';
		winKeyLookup[95] = '.';
		winKeyLookup[96] = KEY_RIGHT_CTRL;
		winKeyLookup[97] = 'v';
		winKeyLookup[98] = 'm';
		winKeyLookup[99] = '\\';




	//	btLookup[row * 10 + col] = 0;
		btLookup[0] = 0x1b;
		btLookup[1] = 0x12;
		//btLookup[2] = '\\';		// No key press on left \
		btLookup[3] = 0x13;
		btLookup[4] = 0x14;
		btLookup[5] = 0xe5;
		btLookup[6] = 0xe2;
		btLookup[7] = 'g';
		btLookup[8] = 'h';
		btLookup[9] = '\'';

		btLookup[10] = '`';
		btLookup[11] = 0x10;
		btLookup[12] = 0x0f;
		btLookup[13] = 0x17;
		btLookup[14] = '=';
		btLookup[15] = 0x16;
		btLookup[16] = 0xe0;
		btLookup[17] = '5';
		btLookup[18] = '6';
		btLookup[19] = '-';

		btLookup[20] = 0x09;
		btLookup[21] = 0x11;
		//btLookup[22] = KEY_CAPS_LOCK; // No key press for caps lock
		btLookup[23] = 0x08;
		btLookup[24] = ']';
		btLookup[25] = 0x15;
		btLookup[26] = 0xe1;
		btLookup[27] = 't';
		btLookup[28] = 'y';
		btLookup[29] = '[';

		btLookup[30] = '1';
		btLookup[31] = '3';
		btLookup[32] = '2';
		btLookup[33] = 0x19;
		btLookup[34] = '8';
		btLookup[35] = '9';
		btLookup[36] = 0x46;			// F11 is print screen
		btLookup[37] = '4';
		btLookup[38] = '7';
		btLookup[39] = '0';

		btLookup[42] = 0x7f;	// App Key
		btLookup[49] = 0x0e;	// App Key

		btLookup[50] = 0x1b;
		btLookup[51] = 0x12;
		btLookup[52] = 0x12;
		btLookup[53] = 0x13;
		btLookup[54] = 0x14;
		btLookup[55] = 0x14;
		btLookup[56] = 0x14;
		btLookup[57] = 0x14;
		btLookup[58] = 0x14;
		btLookup[59] = 0x14;

		btLookup[60] = 'q';
		btLookup[61] = 'e';
		btLookup[62] = 'w';
		btLookup[63] = 0x0a;
		btLookup[64] = 'i';
		btLookup[65] = 'o';
		btLookup[66] = 0x04;		// F12 is delete
		btLookup[67] = 'r';
		btLookup[68] = 'u';
		btLookup[69] = 'p';

		btLookup[70] = 'a';
		btLookup[71] = 'd';
		btLookup[72] = 's';
		btLookup[74] = 'k';
		btLookup[75] = 'l';
		btLookup[76] = 0xe7;
		btLookup[77] = 'f';
		btLookup[78] = 'j';
		btLookup[79] = ';';

		btLookup[80] = 0xe3;
		btLookup[81] = ' ';
		btLookup[82] = 0x0b;
		btLookup[83] = ' ';
		btLookup[84] = 0x0c;
		btLookup[85] = 0x07;
		btLookup[86] = 0xe6;
		btLookup[87] = 'b';
		btLookup[88] = 'n';
		btLookup[89] = '/';

		btLookup[90] = 'z';
		btLookup[91] = 'c';
		btLookup[92] = 'x';
		btLookup[94] = ',';
		btLookup[95] = '.';
		btLookup[96] = 0xe4;
		btLookup[97] = 'v';
		btLookup[98] = 'm';
		btLookup[99] = '\\';



	mode = MODE_USB;

}

void loop()
{

		int keyCount = 0;
		int index = 0;

		previousKey = keyValue;
		isLWinDown = 0;

		for(int i=0; i<256; i++)
		{
				wasKeyPressed[i] = isKeyPressed[i];
				isKeyPressed[i] = 0;
		}
		//   isKeyPressed = 0;
		keyValue = 0;


		if(noKey == 16)
		{ // no keys were pressed
				readKey = true; // keyboard is ready to accept a new keypress
		}
		noKey = 0;
		for(rowCounter=row1; rowCounter<(row10 +1); rowCounter++)
		{
				scanRow(); // switch on one row at a time
				//Serial.print("Looping on rows: ");
				//Serial.println(rowCounter);

				for(columnCounter = colA; columnCounter <colJ +1; columnCounter++)
				{
						//delay(100); 
						//Serial.print("Looping on columns: ");
						//Serial.println(columnCounter);


						readColumn(); // read the switch pressed
						if ((foundCol== true) && (keyCount++ <3)) // k roll over limited to 3
						{

								index = (rowCounter - row1) * 10 + (columnCounter - colA);
								isKeyPressed[index] = 1;

								if (index == 80)
								{
									isLWinDown = 1;
									Serial.println("isLWinDown is pressed");
								}

								Serial.print("Found pressed key at row: ");
								Serial.print(rowCounter);
								Serial.print(" column: ");
								Serial.print(columnCounter);
								Serial.print(" key code: ");
								Serial.print(index);
								Serial.print(" mode : ");
								Serial.print(mode);

								      //Serial.print("Pressed key at index - ");
									//	Serial.println(index); 

								//keyValue =((rowCounter-row1) +4*(columnCounter - colA)) + 'a';
								//		isKeyPressed = keyValue;

						}
				}
		}
		if (noKey > 0) 
		{
			Serial.println("");
		}



		delay(debounce);

		if ((isKeyPressed[6] == 1) && (isKeyPressed[16] == 1) && (isKeyPressed[26] == 1))
		{
			Serial.println("Switching to usb");
			mode = MODE_USB;
		}

		else if ((isKeyPressed[6] == 1) && (isKeyPressed[16] == 1) && (isKeyPressed[5] == 1))
		{
			Serial.println("Switching to bt");
			mode = MODE_BT;
		}

		else
		{
			for(int i=0; i<256; i++)
			{
				if ((isKeyPressed[i] == 1) && (wasKeyPressed[i] == 0))
				{
					if (mode == MODE_USB)
					{
						if (isLWinDown == 0)
						{
							Keyboard.press(keyLookup[i]);
						}
						else
						{
							Keyboard.press(winKeyLookup[i]);
						}
					}
					if (mode == MODE_BT)
					{	
						Serial.println("Write to bt");
						Serial1.print(btLookup[i]);
					}

				}

				if ((isKeyPressed[i] == 0) && (wasKeyPressed[i] == 1))
				{
					if (mode == MODE_USB)
					{
						if (isLWinDown == 0)
						{
							Keyboard.release(keyLookup[i]);
						}
						else
						{
							Keyboard.release(winKeyLookup[i]);
						}
					}
				}
			}

			// Special handling for caps lock and left \ (left and right mouse clicks)
			if ((isKeyPressed[22] == 1) && (wasKeyPressed[22] == 0))
			{
				Mouse.press();
				Serial.println("left click press");
			}

			if ((isKeyPressed[22] == 0) && (wasKeyPressed[22] == 1))
			{
				Mouse.release();
				Serial.println("left click release");
			}

			if ((isKeyPressed[2] == 1) && (wasKeyPressed[2] == 0))
			{
				Mouse.press(MOUSE_RIGHT);
				Serial.println("right click press");
			}

			if ((isKeyPressed[2] == 0) && (wasKeyPressed[2] == 1))
			{
				Mouse.release(MOUSE_RIGHT);
				Serial.println("right click release");
			}
		}

}

void scanRow()
{
		for(int j =row1; j < (row10 +1); j++)
		{
				digitalWrite(j, HIGH);
		}
		digitalWrite(rowCounter , LOW); // switch on one row
}

void readColumn()
{

		foundColumn = digitalRead(columnCounter);
		if(foundColumn == 0)
		{
				foundCol = true;
				noKey=noKey +1; // counter for number of Pressed columns
		}
		else
		{
				foundCol=false;
		}
}

