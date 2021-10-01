#include "LedControl.h"

LedControl lc = LedControl(10, 8, 9, 4);

int B0_button = 2; //Button (B0) for counter start and stop
int B1_button = 3; //Buttion (B1) for counter up and down

int g1_LED = 4;
int g2_LED = 5;

int B0_state = 1;
int B1_state = 1;
int count = 30;
int countg1 = 10;
int mainCount = 0;

void setup() {
  Serial.begin(9600);

  //INITIALIZE SEVEN SEGMENT DISPLAY
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 7);
  /* and clear the display */
  lc.clearDisplay(0);

  //Enable the Global Interupt Bit
  sei();

  DDRD &= ~(1 << B0_button);
  PORTD |= (1 << B0_button);

  DDRD |= (1 << g1_LED) | (1 << g2_LED);

  //Enable the required timer interupt
  TIMSK1 |= (1 << TOIE1);

  //Set mode of the timer
  TCCR1A &= (~(1 << WGM10)) & (~(1 << WGM11));
  TCCR1B &= (~(1 << WGM12)) & (~(1 << WGM13));

  //Set the prescaler for the timer
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TCCR1B &= (~(1 << CS11));         //PRE 1024

  //Setthe period for the timer
  TCNT1 = 49910;    //1 Second

  //TRIGGER AT THE FALLING EDGE (INT0)
  EICRA |= (1 << ISC01);
  EICRA &= (1 << ISC00);

  //TRIGGER AT THE FALLING EDGE (INT1)
  EICRA |= (1 << ISC11);
  EICRA &= (1 << ISC10);

  //Enable external Interupt for counter START AND STOP (INT0)
  EIMSK |= (1 << INT0);

  //Enable external Interupt for counter UP AND DOWN (INT1)
  EIMSK |= (1 << INT1);

}

void loop() {

//  B0_state = (PIND & (1 << B0_button)) >> B0_button;
//  B1_state = (PIND & (1 << B1_button)) >> B1_button;

}

ISR(TIMER1_OVF_vect) {

  if (!B0_state) {
    if (count > 0) {
      count--;
      ssdMainCount(count);
      
    } else {
      greenlight1();
    }
  }

  TCNT1 = 49910;
}

ISR(INT0_vect) { //This is exicute when 0
  count =30;
  countg1 =10;
  B0_state = !B0_state;
}

ISR(INT1_vect) {  //This is exicute when 1
  B1_state = !B1_state;
}

void greenlight1() {
  if (countg1 > 0) {
    PORTD |= (1 << g1_LED);
    PORTD |= (1 << g2_LED);
    countg1--;
    ssdg1(countg1);
  } else {
    PORTD &= ~(1 << g1_LED);
    PORTD &= ~(1 << g2_LED);
  }
}

void ssdg1(int x) {
  lc.setDigit(0, 4, ((int)x % 100) / 10, false);
  lc.setDigit(0, 5, (int)x % 10, false);

  lc.setDigit(0, 2, ((int)x % 100) / 10, false);
  lc.setDigit(0, 3, (int)x % 10, false);
}

void ssdMainCount(int y) {
  lc.setDigit(0, 6, ((int)y % 100) / 10, false);
  lc.setDigit(0, 7, (int)y % 10, false);

  lc.setDigit(0, 0, ((int)y % 100) / 10, false);
  lc.setDigit(0, 1, (int)y % 10, false);
}
