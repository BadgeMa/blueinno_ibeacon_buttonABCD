/*
  The sketch demonstrates iBecaon from an RFduino
*/

/*
  Copyright (c) 2014 OpenSourceRF.com.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <RFduinoBLE.h>

// pin 3 on the RGB shield is the green led
int led = 3;
int my_led = 4;
int ButtonA = 7;
int ButtonB = 8;
int ButtonC = 9;
int ButtonD = 10;

boolean BA = false;
boolean BB = false;
boolean BC = false;
boolean BD = false;

void setup() {
  // led used to indicate that iBeacon has started
  pinMode(led, OUTPUT);
  pinMode(my_led, OUTPUT);
  pinMode(ButtonA, INPUT);
  pinMode(ButtonB, INPUT);
  pinMode(ButtonC, INPUT);
  pinMode(ButtonD, INPUT);

  // do iBeacon advertising
  RFduinoBLE.iBeacon = true;

  // override the default iBeacon settings
  uint8_t uuid[16] = {0xE2, 0xC5, 0x6D, 0xB5, 0xDF, 0xFB, 0x48, 0xD2, 0xB0, 0x60, 0xD0, 0xF5, 0xA7, 0x10, 0x96, 0xE0};
  memcpy(RFduinoBLE.iBeaconUUID, uuid, sizeof(RFduinoBLE.iBeaconUUID));
  RFduinoBLE.iBeaconMajor = 1234;
  RFduinoBLE.iBeaconMinor = 5670;
  RFduinoBLE.iBeaconMeasuredPower = 0xC6;

  // start the BLE stack
  RFduinoBLE.begin();
}

void loop() {
  // switch to lower power mode
  //RFduino_ULPDelay(INFINITE);

  if (digitalRead(ButtonA) == LOW) {


    if (!BA) {
      my_led_func(true);
      //      RFduinoBLE.iBeacon = true;
      RFduinoBLE.end();
      RFduinoBLE.iBeaconMajor = 1234;
      RFduinoBLE.iBeaconMinor = 5671;
      RFduinoBLE.begin();

      //단지, end, begin 없이 Major와 Minor만 바꾸면 동작 안함.
      //      RFduinoBLE.iBeaconMajor = 1234;
      //      RFduinoBLE.iBeaconMinor = 5671;
    }


    while (digitalRead(ButtonA) == LOW);

    BA = true;
  } else {


    if (BA) {
      my_led_func(false);

      RFduinoBLE.end();
      RFduinoBLE.iBeaconMajor = 1234;
      RFduinoBLE.iBeaconMinor = 5670;
      RFduinoBLE.begin();
    }


    while (digitalRead(ButtonA) == HIGH);

    BA = false;
  }

}
void my_led_func(bool start)
{
  // turn the green led on if we start advertisement, and turn it
  // off if we stop advertisement

  if (start)
    digitalWrite(my_led, HIGH);
  else
    digitalWrite(my_led, LOW);
}

void RFduinoBLE_onAdvertisement(bool start)
{
  // turn the green led on if we start advertisement, and turn it
  // off if we stop advertisement

  if (start)
    digitalWrite(led, HIGH);
  else
    digitalWrite(led, LOW);
}
