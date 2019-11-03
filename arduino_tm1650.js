#include <TM1650.h>
#include <Wire.h>
#include <TimeLib.h> 
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#define SDA_PIN 4
#define SCL_PIN 5
TM1650 d;
const char ssid[] = "Nexus"; 
const char pass[] = "13033883439";
IPAddress timeServer(223,113,97,104);
const int timeZone = 8;
WiFiUDP Udp;
unsigned int localPort = 8888;
void setup() 
{
  Wire.begin();
  Serial.begin(38400);
  d.init();
 while (!Serial) ; // Needed for Leonardo only
  delay(250);
  Serial.println("TimeNTP Example");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP number assigned by DHCP is ");
  Serial.println(WiFi.localIP());
  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(Udp.localPort());
  Serial.println("waiting for sync");
  setSyncProvider(getNtpTime);
}

void loop() 
{
 displaytime();
 displaydata();
}

const int NTP_PACKET_SIZE = 48;
byte packetBuffer[NTP_PACKET_SIZE];
void displaytime(){
  d.setBrightness(1);
  String a;
 String b;
 if (hour() < 10){
  a = '0' + String(hour());
 }else{
  a = String(hour());
 }
 if (minute() < 10){
  b ='0' + String(minute());
 }else{
  b = String(minute());
 }
 char line[] = "hour" ;
 String s = String(a + b);
 s.toCharArray(line,5);
 d.displayString(line);
 for( int i = 1;i<=4;i++){
 delay(1000);
  d.setDot(1,true);
  delay(1000);
   d.setDot(1,false); 
   }
}
void displaydata(){
  d.setBrightness(1);
  String a;
 String b;
 if (month() < 10){
  a = '0' + String(month());
 }else{
  a = String(month());
 }
 if (day() < 10){
  b ='0' + String(day());
 }else{
  b = String(day());
 }
 char line[] = "hour" ;
 String s = String(a + b);
 s.toCharArray(line,5);
 d.displayString(line);
   d.setDot(1,false); 
   delay(1000);
}
time_t getNtpTime()
{
  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  sendNTPpacket(timeServer);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}
void sendNTPpacket(IPAddress &address)
{
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
   packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
   Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
