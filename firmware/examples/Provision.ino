//*****************************************************************************
//
// Provision - This example shows how to use Exosite's provision API to activate
//             as a type of product (vendor, model, unique serial number).  This
//             is used to activate and get a CIK instead of using a generic hard
//             -coded CIK.
//             http://docs.exosite.com/provision/device/
//
// Copyright (c) 2015 Exosite LLC.  All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

//  * Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of Exosite LLC nor the names of its contributors may
//    be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

#include "exosite/exosite.h"

/*==============================================================================
* Configuration Variables
*
* Change these variables to your own settings.
*=============================================================================*/

// Use these variables to customize what datasources are read and written to.
String readString = "command&uptime";
String writeString = "uptime=";
String returnString;

// Number of Errors before we try a reprovision.
const unsigned char reprovisionAfter = 3;

/*==============================================================================
* End of Configuration Variables
*=============================================================================*/
unsigned char errorCount = reprovisionAfter;  // Force Provision On First Loop
char macString[18];  // Used to store a formatted version of the MAC Address
byte macData[6];

class TCPClient client;
Exosite exosite(&client);

/*==============================================================================
* setup
*
* Particle setup function.
*=============================================================================*/
void setup(){
  Serial.begin(115200);
  Serial.println("Boot");


  // Create MAC Address String in the format FF:FF:FF:FF:FF:FF
  WiFi.macAddress(macData);
  snprintf(macString, 18, "%02X:%02X:%02X:%02X:%02X:%02X",
           macData[5], macData[4], macData[3], macData[2], macData[1], macData[0]);

  // Print Some Useful Info
  Serial.print(F("MAC Address: "));
  Serial.println(macString);

  Serial.print(F("IP Address: "));
  Serial.println(WiFi.localIP());
}

/*==============================================================================
* loop
*
* Particle loop function.
*=============================================================================*/
void loop(){
  // Check if we should reprovision.
  if(errorCount >= reprovisionAfter){
    if(exosite.provision("exosite", "arduinoyun-generic", macString)){
      errorCount = 0;
    }
  }

  //Write to "uptime" and read from "uptime" and "command" datasources.
  if ( exosite.writeRead(writeString+String(millis()), readString, returnString)){
    Serial.println("OK");
    Serial.println(returnString);
    errorCount = 0;
  }else{
    Serial.println("Error");
    errorCount++;
  }

  delay(5000);
}
