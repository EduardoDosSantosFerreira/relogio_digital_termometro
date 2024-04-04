//Pin connected to ST_CP of 74HC595
int latchPin = 12;
//Pin connected to SH_CP of 74HC595
int clockPin = 8;
////Pin connected to DS of 74HC595
int dataPin = 11;

unsigned long currentmicros = 0;
unsigned long nextmicros = 0;
unsigned long interval = 10000; // ajustado para minha placa

byte tens_hours = 0; 
byte ones_hours = 9;  
byte tens_minutes = 3;
byte ones_minutes = 5;
byte tens_seconds = 0;
byte ones_seconds = 0;
byte tenths = 0;
byte hundredths= 0;

byte prior_seconds = 0;

int dataArray[11] = {64, 121, 36, 48, 25, 18, 2, 120, 0, 16, 255};

void setup() {
  // coloque seu código de inicialização aqui, para ser executado uma vez:
  // define os pinos como saída para controlar o registrador de deslocamento
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  nextmicros = micros();
}

void loop() {
  // coloque seu código principal aqui, para ser executado repetidamente:
  generateTime();
  //displayTime();
  blinkTime(3);
}

void displayTime(){
    digitalWrite(latchPin, LOW);
    // desloca os bits:
    shiftOut(dataPin, clockPin, MSBFIRST, dataArray[tens_hours]);
    shiftOut(dataPin, clockPin, MSBFIRST, dataArray[ones_hours]);
    shiftOut(dataPin, clockPin, MSBFIRST, dataArray[tens_minutes]); 
    shiftOut(dataPin, clockPin, MSBFIRST, dataArray[ones_minutes]);
    shiftOut(dataPin, clockPin, MSBFIRST, dataArray[tens_seconds]);
    shiftOut(dataPin, clockPin, MSBFIRST, dataArray[ones_seconds]);
    // leva o pino de latch alto para que os LEDs acendam:
    digitalWrite(latchPin, HIGH);
    // pausa antes do próximo valor:
}

void generateTime(){
  currentmicros = micros(); // lê o tempo.

  if ((currentmicros - nextmicros) >= interval) // passaram-se 10 milissegundos

  {

    hundredths = hundredths +1;

    if (hundredths == 10){
      hundredths = 0;
      tenths = tenths +1;
    }

    if (tenths == 10){
      tenths = 0;
      ones_seconds = ones_seconds +1;
    }

    if (ones_seconds == 10){
      ones_seconds = 0;
      tens_seconds = tens_seconds +1;
    }

    if (tens_seconds == 6){
      tens_seconds = 0;
      ones_minutes = ones_minutes +1;
    }

    if (ones_minutes == 10){
      ones_minutes = 0;
      tens_minutes = tens_minutes +1;
    }

    if (tens_minutes == 6){
      tens_minutes = 0;
      ones_hours = ones_hours +1;
    }

    if (ones_hours == 10){
      ones_hours = 0;
      tens_hours = tens_hours +1;
    }
    if ((tens_hours == 2) && (ones_hours == 4)){
      ones_hours = 0;
      tens_hours = 0;
      delay(1000);
    }

    nextmicros = nextmicros + interval; // atualiza para a próxima comparação

  }  // fim da verificação do intervalo de tempo
}

void blinkTime(int position){
    // desloca os bits:
    int _second_one = ones_seconds, _second_two = tens_seconds, _minute_one = ones_minutes, _minute_two = tens_minutes,
        _hour_one = ones_hours, _hour_two = tens_hours;
        
    switch(position){
      case 1:
        _hour_two = 10;
        break;
      case 2:
        _hour_one = 10;
        break;
      case 3: 
        _minute_two = 10;
        break;
      case 4:  
        _minute_one = 10; 
        break;
      case 5:
        _second_two = 10;
        break;
      case 6: 
        _second_one = 10;
        break;
    }
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dataArray[_hour_two]);
    shiftOut(dataPin, clockPin, MSBFIRST, dataArray[_hour_one]);
    shiftOut(dataPin, clockPin, MSBFIRST, dataArray[_minute_two]);
    shiftOut(dataPin, clockPin, MSBFIRST, dataArray[_minute_one]);
    shiftOut(dataPin, clockPin, MSBFIRST, dataArray[_second_two]);
    shiftOut(dataPin, clockPin, MSBFIRST, dataArray[_second_one]);
    // leva o pino de latch alto para que os LEDs acendam:
    digitalWrite(latchPin, HIGH);
    // pausa antes do próximo valor:
}
