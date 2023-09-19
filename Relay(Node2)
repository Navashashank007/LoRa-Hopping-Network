//Node 2
#include <SPI.h>
#include <RHRouter.h>
#include <RHMesh.h>
#include <RH_RF95.h>

//imcrease the servers and respective server address to add more devices.
#define CLIENT_ADDRESS 2 //transmitter node address.
#define SERVER_ADDRESS 3 //reciever node address.

RH_RF95 rf95(4, 2); // Set the LoRa module pins

RHMesh manager(rf95, CLIENT_ADDRESS);

void setup() {
  Serial.begin(115200); //set the Baud rate
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

  if (manager.recvfromAck(buf, &len, &from)) { // reciever code line    
    String receivedData = (char*)buf;
    Serial.println("Received data from Node " + String(from) + ": " + receivedData);

    // Process the received data
    // Implement your logic here if any functionality is required from node 2 or relay.

    // Forward the data to Node 3
    manager.sendtoWait(buf, len, SERVER_ADDRESS);// sender code line
  }
}
