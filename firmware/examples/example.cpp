#include "exosite/exosite.h"
/*==============================================================================
* Configuration Variables
*
* Change these variables to your own settings.
*=============================================================================*/
String cikData = "0000000000000000000000000000000000000000";  // <-- Fill in your CIK here! (https://portals.exosite.com -> Add Device)

// Use these variables to customize what datasources are read and written to.
String readString = "command&uptime";
String writeString = "uptime=";
String returnString;

/*==============================================================================
* End of Configuration Variables
*=============================================================================*/
class TCPClient client;
Exosite exosite(cikData, &client);

/*==============================================================================
* setup
*
* Arduino setup function.
*=============================================================================*/
void setup(){  
  Serial.begin(115200);
  delay(3000);
  Serial.println("Boot");
}

/*==============================================================================
* loop 
*
* Arduino loop function.
*=============================================================================*/
void loop(){
  //Write to "uptime" and read from "uptime" and "command" datasources.
  if ( exosite.writeRead(writeString+String(millis()), readString, returnString)){
    Serial.println("OK");
    Serial.println(returnString);
    delay(5000);
  }else{
    Serial.println("Error");
    delay(500);
  }

}
