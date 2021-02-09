#include <Keypad_MC17.h>
#include <Wire.h>
#include <Keypad.h>
#include <elapsedMillis.h>
#define I2CADDR 0x26
const byte ROWS = 4; // four rows
const byte COLS = 4; // three columns
elapsedMillis toggle;
// char keys[ROWS][COLS] =
// {
// 	{
// 		1, 2, 3,4
// 	},
// 	{
// 		5, 6,7, 8
// 	},
// 	{
// 		9,10,11,12
// 	},
// 	{
// 		13,14,15,16
// 	}
// };
int keys[ROWS][COLS] =
    {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};
byte rowPins[ROWS] =
    {
        0, 1, 2, 3}; // connect to the row pinouts of the keypad

byte colPins[COLS] =
    {
        4, 5, 6, 7}; // connect to the column pinouts of the keypad
Keypad_MC17 keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR);
void setup()
{
  // put your setup code here, to run once:
  DDRA = 0x00;
  PORTA = 0xff;
  DDRB = 0x00;
  PORTB = 0xff;
  DDRC = 0x00;
  PORTC = 0xff;
  // DDRD = 0x00;
  // PORTD = 0xff;
  // DDRE = 0x00;
  // PORTE = 0xff;
  // DDRF = 0x00;
  // PORTF = 0xff;
  DDRG = 0x00;
  PORTG = 0xff;
  // DDRH = 0x00;
  // PORTH = 0xff;
  DDRL = 0x00;
  PORTL = 0xff;
  // DDRK = 0x00;
  // PORTK = 0xff;
  Serial.begin(500000);
  Wire.setClock(1700000);
  Wire.begin(); // now needed
  keypad.begin();
}
uint16_t handleKeypad(uint16_t data);
void loop()
{

  Serial.print(PINA, BIN);
  Serial.print(PINB, BIN);
  Serial.print(PINC, BIN);

  uint8_t pinVal_G = PING;
  pinVal_G = pinVal_G << 2;
  pinVal_G = pinVal_G | 0b00000011;
  Serial.print(pinVal_G, BIN);

  // Serial.print(PINH, BIN);
  Serial.print(PINL, BIN);
  uint16_t keypadPress = 0b1111111111111111;
  keypadPress = handleKeypad(keypadPress);
  if (toggle >= 100)
  {
    keypadPress = 0b1111111111111111;
    toggle = 0;
  }

  // Serial.print(keypadPress, BIN);

  // EOF
  Serial.print("\n");
}

uint16_t handleKeypad(uint16_t data)
{
  int key = keypad.getKey();
  if (key)
  {

    bitWrite(data, key, 0);
  }
  // After 100 ms reset the byte register.

  return data;
  /**/
}