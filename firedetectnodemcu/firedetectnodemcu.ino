#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "firedetectio.firebaseio.com"
#define FIREBASE_AUTH "TdTFrAnYf96KBHhLm2YNMIacOtrC66Wu5zYZr4Sq"
#define WIFI_SSID "desktop"
#define WIFI_PASSWORD "147258369"

int val;
int tempPin =A0;
int r2 = D1;
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  pinMode(tempPin,INPUT);
  pinMode(r2,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
   delay(500);
  Serial.println("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop() {
  // put your main code here, to run repeatedly:

  val = analogRead(tempPin);
float mv = ( val/1024.0)*5000; 
float cel = mv/10;
float farh = (cel*9)/5 + 32;

Serial.print("TEMEPRATURE = ");
Serial.print(cel);
Serial.print("*C");
Serial.println();
delay(1000);

 Firebase.setFloat("Temperature", cel);

    if (Firebase.failed()) {
        Serial.print("setting /number failed:");
        Serial.println(Firebase.error());
        return;
    }

    int buzz = Firebase.getInt("Buzzer");
    if(buzz==1)
    digitalWrite(r2,HIGH);
    else 
    digitalWrite(r2,LOW);

}
