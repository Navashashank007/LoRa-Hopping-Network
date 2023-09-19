//node_reciever node
#include <SPI.h>
#include <RHRouter.h>
#include <RHMesh.h>
#include <RH_RF95.h>

#define CLIENT_ADDRESS 3 //Receiever address

RH_RF95 rf95(4, 2); // Set the LoRa module pins

RHMesh manager(rf95, CLIENT_ADDRESS);

void setup() {
  pinMode(14, OUTPUT); // Set the LED pin as an output
  Serial.begin(115200);
  if (!manager.init()) {
    Serial.println("LoRa initialization failed.");
    while (1);
  }
  rf95.setFrequency(866.0); // Set the frequency (915 MHz for US)
}

void loop() {
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  uint8_t from;

  if (manager.recvfromAck(buf, &len, &from)) {
    String receivedData = (char*)buf;
    Serial.print("Received data from Node " + String(from) + ": " + receivedData);
//Remote on and off street light logic
    if (receivedData == "on") {
      digitalWrite(14, HIGH);
      Serial.println(" - LED ON");
    } else if (receivedData == "off") {
      digitalWrite(14, LOW);
      Serial.println(" - LED OFF");
    } else {
      Serial.println(" - Invalid command");
    }
  }
}
