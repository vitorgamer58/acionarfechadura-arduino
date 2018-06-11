#include <SPI.h>
// Biblioteca utilizada para comunicação com o Arduino
#include <Ethernet.h> 
 
// A linha abaixo permite definir o endereço físico (MAC ADDRESS) da placa...
//de rede.  
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

byte ip[] = { 192, 168, 0, 177 }; // Define o endereço IP.

// Porta onde estará aberta para comunicação Internet e Arduino.
EthernetServer server(8090);  
 
String readString;
int Pin = 9; //  Pino digital onde será ligado o relê
 
void setup(){
 
  pinMode(Pin, OUTPUT); // Define o Pino 9 como saída.
  Ethernet.begin(mac, ip); // Chama o MAC e o endereço IP da placa Ethernet.
  //  Inicia o servidor que esta inserido junto a placa Ethernet.
  server.begin();  
}
 
void loop(){
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
 
        if (readString.length() < 100) {
          readString += c;             
        }

        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
    
           // A partir daqui começa os códigos html.
    
          client.println("<HTML>");
          client.println("<BODY>");
          client.println("<H1>Abre Porta</H1>");
          client.println("<H1>Projeto basico para abrir o porta pelo celular</H1>");
          client.println("<hr />");
          client.println("<br />");
          
          client.println("<a href=\"comandoabrir/abrir\"\">Abrir Portão</a>");
          
          client.println("</BODY>");
          client.println("</HTML>");
          
          delay(1);
          client.stop();
          
          if(readString.indexOf("comandoabrir/abrir") > 0)
          {
            digitalWrite(Pin, HIGH);  // manda comando para abrir o Portão.
            delay(90); // Espera por 1s
            digitalWrite(Pin, LOW);  // para de mandar comando.
          }
          
          readString="";    
        }
      }
    }
  }
}
