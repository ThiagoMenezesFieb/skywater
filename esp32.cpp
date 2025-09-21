#include <WiFi.h>
#include <PubSubClient.h>

#define bomba 13
#define sensor_umidade 32
const int tempo_atualizar = 2000; // temporizador para aguardar mensagens do server
volatile bool irrigar = false; // verifica se deve irrigar ou não via HTTP //implementar interrupção
bool irrigou = false;  // flag para ver se deve irrigar

const char* ssid1 =""; //por nome da rede
const char* senha1 = ""; //por senha da rede
char ssid2[32]; //por lógica para alteração da rede
char senha2[64];

const char* mqtt_server = "test.mosquitto.org"; // broker
const int mqtt_port = 1883;
const char* mqtt_topic = "esp32/umidade";       // tópico para enviar dados

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println("onectando ao WiFi.");
  WiFi.begin(ssid1, senha1);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi conectado, IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop até reconectar
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT.");
    if (client.connect("ESP32Client")) { 
      Serial.println("conectado!");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 3s");
      delay(3000);
    }
  }
}

void setup() {
 Serial.begin(115200);
 pinMode (bomba, OUTPUT);
 digitalWrite(bomba, LOW);

 setup_wifi();
 client.setServer(mqtt_server, mqtt_port);
 
 Serial.println("PROGRAMA INICIADO");
}

int ler_umidade() {
 int leitura_sensor= analogRead(sensor_umidade); // valor bruto
 int umidade = map(leitura_sensor, 4095, 0, 0, 100); //valor tratado de 0 a 100%
 Serial.println(umidade);
 return umidade;
}

bool irrigacao() {
  if (irrigar) {
    digitalWrite(bomba, HIGH);
    irrigou = true;
  } else {
    digitalWrite(bomba, LOW);   // desliga bomba
    irrigou = false;
  }
   return irrigou;  // retorna true se irrigou, false se não
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
 
 int umidade = ler_umidade();
  irrigacao();
 
// Converter para string e enviar via MQTT
  char mensagem[10];
  snprintf(mensagem, 10, "%d", umidade);
  client.publish(mqtt_topic, mensagem);

  delay(tempo_atualizar);
}

