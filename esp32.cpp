#define bomba 13
#define sensor_umidade 32
const int tempo_atualizar = 100; // temporizador para aguardar mensagens do server
volatile bool irrigar = false; // verifica se deve irrigar ou não via HTTP //implementar interrupção
bool irrigou = false;  // flag para ver se deve irrigar

const char* ssid1 =""; //por nome da rede
const char* senha1 = ""; //por senha da rede
char ssid2[32]; //por lógica para alteração da rede
char senha2[64];

void setup() {
 Serial.begin(115200);
 pinMode (bomba, OUTPUT);
 digitalWrite(bomba, LOW);
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
  irrigacao();
  ler_umidade();
}

