#define trigPinV 8
#define echoPinV 9
#define trigPinH 10
#define echoPinH 11
#define trigPinB 12
#define echoPinB 13

#define RED 0xF800
#define GREEN 0x07E0
#define YELLOW 0xFFE0

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_ADDR 0x3C

String teller = "333";
String VenstreTeller = "3";
String HoyreTeller = "3";
String BakTeller = "3";
String nyTeller = "333";

int narme = 80;
int nestenNarme = 150;
int grense = 300;

const int Venstre0 = 36;
const int Venstre1 = 42;
const int Venstre2 = 50;

const int Hoyre0 = 28;
const int Hoyre1 = 20;
const int Hoyre2 = 12;

const int Bak0 = 100;
const int Bak1 = 108;
const int Bak2 = 116;

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  
  Serial.begin(115200);
  pinMode(trigPinV, OUTPUT);
  pinMode(echoPinV, INPUT);
  
  pinMode(trigPinH, OUTPUT);
  pinMode(echoPinH, INPUT);
  
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);
}

void loop() {
  
  long duration, distance;
  long duration2, distance2;
  long duration3, distance3;

  //Sender ut signal fra venstre sensor
  digitalWrite(trigPinV, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPinV, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPinV, LOW);

  // Deklarerer variabel for avstand til venstre
  duration = pulseIn(echoPinV, HIGH);
  distance = (duration/2) / 29.1;

  //---------------------------------

  //Sender ut signal fra høyre sensor
  digitalWrite(trigPinH, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPinH, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPinH, LOW);

  // Deklarerer variabel for avstand til høyre
  duration2 = pulseIn(echoPinH, HIGH);
  distance2 = (duration2/2) / 29.1;

  //-----------------------------------

  // Sender ut signal fra bakre sensor
  digitalWrite(trigPinB, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPinB, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPinB, LOW);

  // Deklarerer variabel for avstand bak
  duration3 = pulseIn(echoPinB, HIGH);
  distance3 = (duration3/2) / 29.1;
  
  //-----------------------------------

  //Skriver ut avstanden fra et objekt individuelt for alle sens.
  Serial.print("Venstre: ");
  Serial.print(distance);
  Serial.print("\n");

  Serial.print("Høyre: ");
  Serial.print(distance2);
  Serial.print("\n");

  Serial.print("Bak: ");
  Serial.print(distance3);
  Serial.print("\n");

  //------------------------------------------------

  display.clearDisplay();
    
  //------------------------------------------------

  //Sjekker om venstre avstand er innen for en av tre tilstander.
  //Herfra blir en variabel tildelt en verdi innenfor hver av de tre.
  //Dette skjer for alle tre sensorene individuelt.
  if (distance <= narme)
  {
    VenstreTeller = "0";
  }
  else if ((distance > narme)&&(distance <= nestenNarme))
  {
    VenstreTeller = "1";
  }
  else if ((distance > nestenNarme)&&(distance < grense))
  {
    VenstreTeller = "2";
  }
  else if (distance > grense)
  {
    VenstreTeller = "3";
  }
  
  //------------------------------------------------
  
  if (distance2 <= narme)
  {
    HoyreTeller = "0";
  }
  else if ((distance2 > narme)&&(distance2 <= nestenNarme))
  {
    HoyreTeller = "1";
  }
  else if ((distance2 > nestenNarme)&&(distance2 < grense))
  {
    HoyreTeller = "2";
  }
  else if (distance2 > grense)
  {
    HoyreTeller = "3";
  }
  
  //------------------------------------------------
  
  if (distance3 <= narme)
  {
    BakTeller = "0";
  }
  else if ((distance3 > narme)&&(distance3 <= nestenNarme))
  {
    BakTeller = "1";
  }
  else if ((distance3 > nestenNarme)&&(distance3 < grense))
  {
    BakTeller = "2";
  }
  else if (distance3 > grense)
  {
    BakTeller = "3";
  }

  //------------------------------------------------

  //Skjøter sammen de tre tilegnet variablene slik at jeg har en fast string å gå etter.
  teller = VenstreTeller + HoyreTeller + BakTeller;
  Serial.print(teller);
  Serial.print("\n");
  Serial.print(nyTeller);
  Serial.print("\n \n");

  //------------------------------------------------

  // F. eks. her:
  // Sjekker om avstanden tilegnet venstre, høyre og bakre alle er 2 (lengst unna)
  // I så fall, ikke gjør noe.
  if (teller == "222")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre2, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre2, YELLOW); //Høyre
      display.fillRect(Bak2, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "111")
  {
    if (teller != nyTeller)
    {
      // Sletter tidligere utskrift på skjermen
      display.clearDisplay();
      display.display();

      // Skriver ut ny utskrift på skjermen
      display.fillRect(0, Venstre1, display.width(), 28, YELLOW); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre1, YELLOW); //Høyre
      display.fillRect(Bak1, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "000")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre0, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre0, RED); //Høyre
      display.fillRect(Bak0, 0, 28, display.height(), RED); //Bak
      display.display();
    }
  }

  if (teller == "333")
  {
    if (teller != nyTeller)
    {
      // Sletter utskriften på skjermen
      display.clearDisplay();
      display.display();
    }
  }

  //------------------------------------------------

   if (teller == "122")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre1, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre2, YELLOW); //Høyre
      display.fillRect(Bak2, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "121")
  {
    if (teller != nyTeller);
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre1, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre2, YELLOW); //Høyre
      display.fillRect(Bak1, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "212")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre2, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre1, YELLOW); //Høyre
      display.fillRect(Bak2, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "112")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre1, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre1, YELLOW); //Høyre
      display.fillRect(Bak2, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "211")
  {
    if (teller !=  nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre2, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre1, YELLOW); //Høyre
      display.fillRect(Bak1, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "221")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre2, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre2, YELLOW); //Høyre
      display.fillRect(Bak1, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  //------------------------------------------------

  if (teller == "022")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre0, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre2, YELLOW); //Høyre
      display.fillRect(Bak2, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "021")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre0, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre2, YELLOW); //Høyre
      display.fillRect(Bak1, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "020")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre0, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre2, YELLOW); //Høyre
      display.fillRect(Bak0, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "012")
  {
    if (teller != nyTeller)
    {
        display.clearDisplay();
        display.display();
  
        display.fillRect(0, Venstre0, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre1, YELLOW); //Høyre
      display.fillRect(Bak2, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "002")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre0, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre0, YELLOW); //Høyre
      display.fillRect(Bak2, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "011")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre0, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre1, YELLOW); //Høyre
      display.fillRect(Bak1, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "001")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre0, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre0, RED); //Høyre
      display.fillRect(Bak1, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "010")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre0, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre1, YELLOW); //Høyre
      display.fillRect(Bak0, 0, 28, display.height(), RED); //Bak
      display.display();
    }
  }

  if (teller == "033")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
  
      display.fillRect(0, Venstre0, display.width(), 28, RED); //Venstre
      display.display();
    }
  }

  if (teller == "032")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre0, display.width(), 28, RED); //Venstre
      display.fillRect(Bak2, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "031")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre0, display.width(), 28, RED); //Venstre
      display.fillRect(Bak1, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "030")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre0, display.width(), 28, RED); //Venstre
      display.fillRect(Bak0, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "023")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre0, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre2, YELLOW); //Høyre
      display.display();
    }
  }

  if (teller == "013")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre0, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre1, YELLOW); //Høyre
      display.display();
    }
  }

  if (teller == "003")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre0, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre0, YELLOW); //Høyre
      display.display();
    }
  }

  if (teller == "133")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre1, display.width(), 28, RED); //Venstre
      display.display();
    }
  }

  if (teller == "132")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre1, display.width(), 28, RED); //Venstre
      display.fillRect(Bak2, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "131")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre1, display.width(), 28, RED); //Venstre
      display.fillRect(Bak1, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "130")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre1, display.width(), 28, RED); //Venstre
      display.fillRect(Bak0, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "123")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre1, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre2, YELLOW); //Høyre
      display.display();
    }
  }

  if (teller == "113")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre1, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre1, YELLOW); //Høyre
      display.display();
    }
  }

  if (teller == "103")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre1, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre0, YELLOW); //Høyre
      display.display();
    }
  }

  if (teller == "233")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre2, display.width(), 28, RED); //Venstre
      display.display();
    }
  }

  if (teller == "232")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre2, display.width(), 28, RED); //Venstre
      display.fillRect(Bak2, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "231")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre2, display.width(), 28, RED); //Venstre
      display.fillRect(Bak1, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "230")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre2, display.width(), 28, RED); //Venstre
      display.fillRect(Bak0, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "223")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre2, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre2, YELLOW); //Høyre
      display.display();
    }
  }

  if (teller == "213")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre2, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre1, YELLOW); //Høyre
      display.display();
    }
  }

  if (teller == "203")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre2, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre0, YELLOW); //Høyre
      display.display();
    }
  }
  
  //------------------------------------------------

  if (teller == "202")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre2, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre0, YELLOW); //Høyre
      display.fillRect(Bak2, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "102")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre1, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre0, YELLOW); //Høyre
      display.fillRect(Bak2, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "201")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre2, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre0, YELLOW); //Høyre
      display.fillRect(Bak1, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "200")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre2, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre0, YELLOW); //Høyre
      display.fillRect(Bak0, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "101")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre1, display.width(), 28, YELLOW); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre0, RED); //Høyre
      display.fillRect(Bak1, 0, 28, display.height(), YELLOW); //Bak
      display.display(); 
    }
  }
  
  if (teller == "100")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre1, display.width(), 28, YELLOW); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre0, RED); //Høyre
      display.fillRect(Bak0, 0, 28, display.height(), RED); //Bak
      display.display();
    }
  }

  if (teller == "303")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, 0, display.width(), Hoyre0, YELLOW); //Høyre
      display.display();
    }
  }

  if (teller == "302")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, 0, display.width(), Hoyre0, YELLOW); //Høyre
      display.fillRect(Bak2, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "301")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, 0, display.width(), Hoyre0, YELLOW); //Høyre
      display.fillRect(Bak1, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "300")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, 0, display.width(), Hoyre0, YELLOW); //Høyre
      display.fillRect(Bak0, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "313")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, 0, display.width(), Hoyre1, YELLOW); //Høyre
      display.display();
    }
  }

  if (teller == "312")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, 0, display.width(), Hoyre1, YELLOW); //Høyre
      display.fillRect(Bak2, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "311")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, 0, display.width(), Hoyre1, YELLOW); //Høyre
      display.fillRect(Bak1, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "310")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, 0, display.width(), Hoyre1, YELLOW); //Høyre
      display.fillRect(Bak0, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "323")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, 0, display.width(), Hoyre2, YELLOW); //Høyre
      display.display();
    }
  }

  if (teller == "322")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, 0, display.width(), Hoyre2, YELLOW); //Høyre
      display.fillRect(Bak2, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "321")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, 0, display.width(), Hoyre2, YELLOW); //Høyre
      display.fillRect(Bak1, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "320")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, 0, display.width(), Hoyre2, YELLOW); //Høyre
      display.fillRect(Bak0, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  //------------------------------------------------

  if (teller == "220")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(0, Venstre2, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre2, YELLOW); //Høyre
      display.fillRect(Bak0, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "120")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre1, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre2, YELLOW); //Høyre
      display.fillRect(Bak0, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "210")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre2, display.width(), 28, RED); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre1, YELLOW); //Høyre
      display.fillRect(Bak0, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "110")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();

      display.fillRect(0, Venstre1, display.width(), 28, YELLOW); //Venstre
      display.fillRect(0, 0, display.width(), Hoyre1, YELLOW); //Høyre
      display.fillRect(Bak0, 0, 28, display.height(), RED); //Bak
      display.display();
    }
  }

  if (teller == "330")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(Bak0, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "331")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(Bak1, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }

  if (teller == "332")
  {
    if (teller != nyTeller)
    {
      display.clearDisplay();
      display.display();
      
      display.fillRect(Bak2, 0, 28, display.height(), YELLOW); //Bak
      display.display();
    }
  }
  
  //------------------------------------------------

  //Tilegner en ny variabel den gamle verdien til stringen som måler avstand
  //Denne bruker igjen for neste iterasjon
  nyTeller = teller;
  delay(500);
}
