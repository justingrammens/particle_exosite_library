//*****************************************************************************
//
// ReadWriteString - A Simple read/write to the Exosite RPC API for the
//                   Particle using the String library
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
* Particle setup function.
*=============================================================================*/
void setup(){  
  Serial.begin(115200);
  delay(3000);
  Serial.println("Boot");
}

/*==============================================================================
* loop 
*
* Particle loop function.
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
