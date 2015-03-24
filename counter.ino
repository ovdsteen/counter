#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x0F, 0x57, 0xBE};
IPAddress ip(192,168,2,12);

unsigned int localPort = 8888;      // local port to listen on

int d1=9,d2=10,d3=11,d4=12;
int i = 0;

//segments
int a = 1;
int b = 2;
int c = 3;
int d = 4;
int e = 5;
int f = 6;
int g = 7;
int p = 8;


    int first = 0;
    int second = 0;
    int third = 0;
    int fourth = 0;


//int mynumber = 1234;

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged";       // a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;


void setup()
{

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  Serial.println("Hallo");
    // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);

  Serial.println(Ethernet.localIP());

  Udp.begin(localPort);

  Serial.begin(9600);

    // start the Ethernet and UDP:


  pinMode(d1, OUTPUT);
/*  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);*/
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(p, OUTPUT);

       //digitalWrite(A3, HIGH);



//DDRD=0xff; // all pins 0-7 OUTPUTs
//DDRB=0xff; // all pins 8-13 OUTPUTs even though we only use pins 8-12


//PORTD=0x00; // make pins 0-7 LOWs
//PORTB=0x00; // make pins 8-13 LOWs

//  number = mynumber.parseFloat();




}
void displayNumber(int number)
{

  /*

  int res = number.split("");
  int digitalPorts = 4;
  int digitalIn = 0;
  for (i = 0; i < digitalPorts; i++) {
      digitalIn = i+1;
      if (res[i] != undefined ){
          console.log( "YES D"+(digitalIn)+"="+res[i] );
      }else{
          console.log( "NO D"+(digitalIn)+"=false" );
      }
  };

*/

}




void displayDigit(int num)
{
    switch(num)
    {
        case 0:
            PORTD=B00000011; // pins 2-7 on
            digitalWrite(8,HIGH); // turn off pin 8
            break;
        case 1:
            PORTD=B11100111; // only pins 2 and 3 are on
            digitalWrite(8,HIGH); // turn off pin 8
        break;
        case 2:
            PORTD=B10010011; // only pins 2,3,5 and 6 on
            digitalWrite(8,LOW); // segment g on
        break;
        case 3:
            PORTD=B11000011; // only pins 2,3,4 and 5 on
            digitalWrite(8,LOW); // segment g on
        break;
        case 4:
            PORTD=B01100111; // only pins 3,4 and 7 on
            digitalWrite(8,LOW); // segment g on
        break;
        case 5:
            PORTD=B01001011; //B10110100; // only pins 2,4,5 and 7 on
            digitalWrite(8,LOW); // segment g on
        break;
        case 6:
            PORTD=B00001011; //B11110100; // only pins 2,4,5,6 and 7 on
            digitalWrite(8,LOW); // segment g on
        break;
        case 7:
            PORTD=B11100011; // only pins 2,3 and 4 on
            digitalWrite(8,HIGH); // segment g off
        break;
        case 8:
            PORTD=B00000011; // pins 2-7 on
            digitalWrite(8,LOW); // turn on pin 8
        break;
        case 9:
            PORTD=B01000011; // only pins 2,3, 4 and 5 on
            digitalWrite(8,LOW); // segment g on
        break;
    }
}
void turnOnSquare(int num)
{
//    int d1=9,d2=10,d3=11,d4=12;
    switch(num)
    {
        case 1:
/*            digitalWrite(d2,LOW);
            digitalWrite(d3,LOW);
            digitalWrite(d4,LOW);
            digitalWrite(d1,HIGH);*/
          digitalWrite(A0, LOW);
          digitalWrite(A1, LOW);
          digitalWrite(A2, LOW);
          digitalWrite(A3, HIGH);
        break;
        case 2:
/*            digitalWrite(d1,LOW);
            digitalWrite(d3,LOW);
            digitalWrite(d4,LOW);
            digitalWrite(d2,HIGH);*/
          digitalWrite(A0, LOW);
          digitalWrite(A1, LOW);
          digitalWrite(A2, HIGH);
          digitalWrite(A3, LOW);
        break;
        case 3:
/*            digitalWrite(d1,LOW);
            digitalWrite(d2,LOW);
            digitalWrite(d4,LOW);
            digitalWrite(d3,HIGH);*/
            digitalWrite(A0, LOW);
            digitalWrite(A1, HIGH);
            digitalWrite(A2, LOW);
            digitalWrite(A3, LOW);
        break;
        case 4:


          digitalWrite(A0, HIGH);
          digitalWrite(A1, LOW);
          digitalWrite(A2, LOW);
          digitalWrite(A3, LOW);


        /*    digitalWrite(d1,LOW);
            digitalWrite(d2,LOW);
            digitalWrite(d3,LOW);
            digitalWrite(d4,HIGH);*/




        break;
        default:
        // this should never occur, but do what you want here
        break;
    }

}

void loop()
{



   // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if(packetSize)
  {

     //turnOnSquare(4);
     //displayDigit(0);

    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i =0; i < 4; i++)
    {
      Serial.print(remote[i], DEC);
      if (i < 3)
      {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");



    Serial.println(packetBuffer);




    //Serial.println(packetBuffer[0]);
    //Serial.println(packetBuffer[1]);
    //Serial.println(packetBuffer[2]);
    //Serial.println(packetBuffer[3]);





    first = (packetBuffer[0] - '0') % 48;
    second = (packetBuffer[1] - '0') % 48;
    third = (packetBuffer[2] - '0') % 48;
    fourth = (packetBuffer[3] - '0') % 48;

   //Serial.println(second);




       // turnOnSquare(1);
   //  displayDigit(fourth);
   //  delay(2);
     // turnOnSquare(2);
    // displayDigit(third);
   //  delay(2);
    // turnOnSquare(3);
    // displayDigit(second);
    // delay(2);
    // turnOnSquare(4);
    // displayDigit(first);
    // delay(2);






    // send a reply, to the IP address and port that sent us the packet we received
    //Udp.beginPacket(Udp.remoteIP(), 5000);
    //Udp.write(ReplyBuffer);
    //Udp.endPacket();




  }

     turnOnSquare(1);
     displayDigit(first);
     delay(2);
      turnOnSquare(2);
     displayDigit(second);
     delay(2);
     turnOnSquare(3);
     displayDigit(third);
     delay(2);
     turnOnSquare(4);
     displayDigit(fourth);
     delay(2);


//  pinMode(A0, OUTPUT);

  //digitalWrite(A0, HIGH);
  //PORTD=B01000011; // pins 2-7 on
   //digitalWrite(8,LOW); // segment g on

   /* delay(2);
     turnOnSquare(2);
  displayDigit(0);
    delay(2);
     turnOnSquare(3);
  displayDigit(0);

    delay(2);
   turnOnSquare(4);
  displayDigit(0);*/


//  digitalWrite(d1,HIGH);



//  digitalWrite(d3,LOW);
 // digitalWrite(d4,LOW);
 // digitalWrite(d2,HIGH);

//  PORTD=B11100111; // only pins 2 and 3 are on
 // digitalWrite(7,HIGH); // turn off pin 8



  /*
  turnOnSquare(1);
  displayDigit(1);
  delay(2);
  turnOnSquare(2);
  displayDigit(9);
  delay(2);
  turnOnSquare(3);
  displayDigit(8);
  delay(2);
  turnOnSquare(4);
  displayDigit(4);
  */






// light up first digit only

/*digitalWrite(d2,LOW);
digitalWrite(d3,LOW);
digitalWrite(d4,LOW);
digitalWrite(d1,HIGH);*/

// light up segments of first digit, display number #1, segments bc
//PORTD=B11100111; //B00011000; // only pins 2 and 3 are on
//digitalWrite(8,HIGH); // turn off pin 8

// light up second digit only
/*digitalWrite(d1,LOW);
digitalWrite(d3,LOW);
digitalWrite(d4,LOW);
digitalWrite(d2,HIGH);*/

// light up segments of second digit, display #2, segments abdeg
//PORTD=B10010011; //B01101100; // only pins 2,3,5 and 6 on
//digitalWrite(8,LOW); // segment g on

// light up third digit only
/*digitalWrite(d1,LOW);
digitalWrite(d2,LOW);
digitalWrite(d4,LOW);
digitalWrite(d3,HIGH);*/

// light up segments of third digit, display #3
//PORTD=B11000011; //B00111100; // only pins 2,3 and 5 on
//digitalWrite(8,LOW); // segment g on

// light up fourth digit only

// light up segments of fourth digit only, display #4
//PORTD=B01100111; //B10011000; // only pins 3,4 and 7 on


//digitalWrite(8,LOW); // segment g on

delay(10);
}
