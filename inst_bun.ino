#include <util/delay.h>
#define IR_USE_AVR_TIMER1
#include <IRremote.h>

const int receiver = 5;


#define BUZZERPIN 4
const int releu1 = 7;
const int releu2 = 8;

//IRrecv irrecv(receiver);
//decode_results results;
IRrecv irrecv(receiver);

volatile int stat = 0;
volatile int soundON = 1;



#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

void setup() {

  Serial.begin(9600);  // Inițializează consola serială

  IrReceiver.enableIRIn();
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(releu1, OUTPUT);
  pinMode(releu2, OUTPUT);
  digitalWrite(releu1, HIGH);
  digitalWrite(releu2, HIGH);
}

void playTone(int tone, int duration)
{
 for (long i = 0; i < duration * 1000L; i += tone * 2)
 {
 digitalWrite(BUZZERPIN, HIGH);
 delayMicroseconds(tone);
 digitalWrite(BUZZERPIN, LOW);
 delayMicroseconds(tone);
 }
}

void loop() {
  check_command();
  // songTempo is a uint8_t so it can be 0-255.
  if (stat == 1) {
    uint8_t songTempo = 135;
    int16_t melody[]{
      NOTE_AS4, 4, NOTE_A4, 8, NOTE_AS4, 8, NOTE_G4, 4, NOTE_AS4, 4, NOTE_A4, 8, NOTE_AS4, 8, NOTE_G4, 4, NOTE_AS4, 4, NOTE_A4, 8, NOTE_AS4, 8, NOTE_G4, 4, NOTE_AS4, 4, NOTE_A4, 8, NOTE_AS4, 8, NOTE_G4, 4, NOTE_AS4, 4, NOTE_A4, 8, NOTE_AS4, 8, NOTE_G4, 4, NOTE_AS4, 4, NOTE_A4, 8, NOTE_AS4, 8, NOTE_G4, 4,
      NOTE_D5, 4, NOTE_C5, 8, NOTE_D5, 8, NOTE_AS4, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_D5, 8, NOTE_AS4, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_D5, 8, NOTE_AS4, 4, NOTE_D5, 4, NOTE_C5, 8, NOTE_D5, 8, NOTE_AS4, 4, NOTE_G5, 4, NOTE_G5, 8, NOTE_G5, 8, NOTE_F5, 8, NOTE_DS5, 8, NOTE_D5, 4, NOTE_D5, 8, NOTE_D5, 8, NOTE_C5, 8, NOTE_AS4, 8,
      NOTE_C5, 4, NOTE_C5, 8, NOTE_C5, 8, NOTE_D5, 8, NOTE_C5, 8, NOTE_AS4, 4, NOTE_A4, 8, NOTE_AS4, 8, NOTE_G4, 4, NOTE_D4, 8, NOTE_E4, 8, NOTE_FS4, 8, NOTE_G4, 8, NOTE_A4, 8, NOTE_AS4, 8, NOTE_C5, 8, NOTE_D5, 8, NOTE_C5, 4, NOTE_AS4, 4, NOTE_D5, 8, NOTE_D5, 8, NOTE_FS5, 8, NOTE_G5, 8, NOTE_A5, 8, NOTE_AS5, 8,
      NOTE_C6, 8, NOTE_D6, 8, NOTE_C6, 4, NOTE_AS5, 4, NOTE_AS5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_G5, 4, NOTE_AS5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_G5, 4, NOTE_AS5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_G5, 4, NOTE_AS5, 4, NOTE_A5, 8, NOTE_AS5, 8, NOTE_G5, 4,
      NOTE_AS5, -4, NOTE_A5, -8, NOTE_AS5, -8, NOTE_G5, 2
    };
    uint16_t notes = sizeof(melody) / sizeof(melody[0]) / 2;
    uint16_t wholenote = (60000 * 4) / songTempo;
    int8_t divider;
    uint16_t noteDuration;
    for (uint16_t i = 0; i < notes * 2; i += 2) {
      if (i % 4 == 0) {
        digitalWrite(releu1, HIGH);
        digitalWrite(releu2, LOW);
      } else {
        digitalWrite(releu1, LOW);
        digitalWrite(releu2, HIGH);
      }
      divider = melody[i + 1];
      if (divider > 0) {
        noteDuration = wholenote / divider;
      } else {
        noteDuration = wholenote / abs(divider) * 1.5;
      }
      if (soundON == 1) {
      tone(BUZZERPIN, melody[i], noteDuration * 0.9);
      }
      delay(noteDuration);
      check_command();
      if (stat != 1) break;
      //noTone(BUZZERPIN);
      
    }
  }

  else if (stat == 2) {
    uint8_t songTempo = 115;
    int16_t melody[]{
      NOTE_D4, 4, NOTE_G4, -8, NOTE_G4, 16, NOTE_G4, 4, NOTE_A4, 4, NOTE_B4, -8, NOTE_B4, 16, NOTE_B4, -4, NOTE_B4, 8, NOTE_A4, 8, NOTE_B4, 8, NOTE_C5, 4, NOTE_F4, 4, NOTE_A4, 4, NOTE_G4, 4, NOTE_D4, 2, REST, 16,
      NOTE_G4, -8, NOTE_G4, 16, NOTE_G4, 4, NOTE_A4, 4, NOTE_B4, -8, NOTE_B4, 16, NOTE_B4, -4, NOTE_B4, 8, NOTE_A4, 8, NOTE_B4, 8, NOTE_C5, 4, NOTE_F4, 4, NOTE_A4, 4, NOTE_G4, -4, REST, 4, NOTE_D5, 8,
      NOTE_D5, 8, NOTE_B4, 8, NOTE_E5, -4, NOTE_D5, 8, NOTE_D5, 8, NOTE_C5, 8, NOTE_C5, -4, NOTE_C5, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_D5, -4, NOTE_C5, 8, NOTE_C5, 8, NOTE_B4, 8, NOTE_B4, 4, NOTE_D4, 4,
      NOTE_G4, -8, NOTE_G4, 16, NOTE_G4, 4, NOTE_A4, 4, NOTE_B4, -8, NOTE_B4, 16, NOTE_B4, -4, NOTE_B4, 8, NOTE_A4, 8, NOTE_B4, 8, NOTE_C5, 4, NOTE_F4, 4, NOTE_A4, 4, NOTE_G4, 2
    };
    uint16_t notes = sizeof(melody) / sizeof(melody[0]) / 2;
    uint16_t wholenote = (60000 * 4) / songTempo;
    int8_t divider;
    uint16_t noteDuration;
    for (uint16_t i = 0; i < notes * 2; i += 2) {
      if (i % 4 == 0) {
        digitalWrite(releu1, HIGH);
        digitalWrite(releu2, LOW);
      } else {
        digitalWrite(releu1, LOW);
        digitalWrite(releu2, HIGH);
      }
      divider = melody[i + 1];
      if (divider > 0) {
        noteDuration = wholenote / divider;
      } else {
        noteDuration = wholenote / abs(divider) * 1.5;
      }
      if (soundON == 1) {
      tone(BUZZERPIN, melody[i], noteDuration * 0.9);}
      delay(noteDuration);
      check_command();
      if (stat != 2) break;
      //noTone(BUZZERPIN);
      
    }
  }

  else if (stat == 3) {
    uint8_t songTempo = 160;
    int16_t melody[] {
    NOTE_F5,2, NOTE_E5,-4, NOTE_D5,8, NOTE_C5,-2, NOTE_AS4,4, NOTE_A4,2, NOTE_G4,2, NOTE_F4,-2,
    NOTE_C5,4, NOTE_D5,-2, NOTE_D5,4, NOTE_E5,-2, NOTE_E5,4, NOTE_F5,1,
    NOTE_F5,4, NOTE_F5,4, NOTE_E5,4, NOTE_D5,4, NOTE_C5,4, NOTE_C5,-4, NOTE_AS4,8, NOTE_A4,4, NOTE_F5,4, NOTE_F5,4, NOTE_E5,4, NOTE_D5,4,
    NOTE_C5,4, NOTE_C5,-4, NOTE_AS4,8, NOTE_A4,4, NOTE_A4,4, NOTE_A4,4, NOTE_A4,4, NOTE_A4,4, NOTE_A4,8, NOTE_AS4,8, NOTE_C5,-2,
    NOTE_AS4,8, NOTE_A4,8, NOTE_G4,4, NOTE_G4,4, NOTE_G4,4, NOTE_G4,8, NOTE_A4,8, NOTE_AS4,-2,
    NOTE_A4,8, NOTE_G4,8, NOTE_F4,4, NOTE_F5,2, NOTE_D5,4, NOTE_C5,-4, NOTE_AS4,8, NOTE_A4,4, NOTE_C5,4, NOTE_E4,2, NOTE_D4,2, NOTE_C4,1
  };
  uint16_t notes = sizeof(melody) / sizeof(melody[0]) / 2;
  uint16_t wholenote = (60000 * 4) / songTempo;
  int8_t divider;
  uint16_t noteDuration;
  for (uint16_t i=0; i<notes*2; i+=2) {
    if (i % 4 == 0) {
        digitalWrite(releu1, HIGH);
        digitalWrite(releu2, LOW);
      } else {
        digitalWrite(releu1, LOW);
        digitalWrite(releu2, HIGH);
      }
    divider = melody[i+1];
    if (divider > 0) {
      noteDuration = wholenote / divider;
    } else {
      noteDuration = wholenote / abs(divider) * 1.5;
    }
    if (soundON == 1) {
    tone(BUZZERPIN, melody[i], noteDuration * 0.9);}
    delay(noteDuration);
    check_command();
      if (stat != 3) break;
    //noTone(BUZZERPIN);
  }
  }

  else if (stat == -1) {  // starea de turn on
    digitalWrite(releu1, LOW);
    digitalWrite(releu2, LOW);
  }

  else if (stat == 0) {  // starea de reset total
    digitalWrite(releu1, HIGH);
    digitalWrite(releu2, HIGH);
  }

}

void check_command() {
  if (IrReceiver.decode()) {
    Serial.print("Cod IR primit: ");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);  // Afișează codul IR

    if (IrReceiver.decodedIRData.decodedRawData == 0xBA45FF00) { stat = 1; }  // sunet1
    else if (IrReceiver.decodedIRData.decodedRawData == 0xB946FF00) { stat = 2; }                                                                              // sunet2
    else if (IrReceiver.decodedIRData.decodedRawData == 0xB847FF00) { stat = 3; }  // sunet3

    else if (IrReceiver.decodedIRData.decodedRawData == 0xE916FF00) { stat = 0; }                                                                               // turn off
    else if (IrReceiver.decodedIRData.decodedRawData == 0xF20DFF00) { stat = -1; }  // turn on
    else if (IrReceiver.decodedIRData.decodedRawData == 0xAD52FF00) {
      soundON = 0;
    }  // diez
    else if (IrReceiver.decodedIRData.decodedRawData == 0xE718FF00) { soundON = 1; }
    Serial.print("stat: ");
    Serial.println(stat);
    IrReceiver.resume();
  }
}

void oChristmasTree(uint8_t songTempo) {
}

void carolofTheBells(uint8_t songTempo) {
}