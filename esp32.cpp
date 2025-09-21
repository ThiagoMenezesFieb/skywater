#define bomba 13
#define sensor_umidade 32
const int tempo_atualizar = 100; // temporizador para aguardar mensagens do server
volatile bool irrigar = false; // verifica se deve irrigar ou não via HTTP //implementar interrupção
bool irrigou = false;  // flag para ver se deve irrigar

const char* ssid1 =""; //por nome da rede
const char* senha1 = ""; //por senha da rede
char* ssid2 =""; //por lógica para alteração da rede
char* senha2 = "";

void setup() {
 Serial.begin(115200);
 pinMode (bomba, OUTPUT);
 digitalWrite(BOMBA, LOW);
}

int ler_umidade() {

}

bool irrigacao() {
  if (irrigar) {
    digitalWrite(BOMBA, HIGH);
    irrigou = true;
  }
  return irrigar;  // retorna true se irrigou, false se não
}


void loop() {
  irrigacao();
  ler_umidade();
}

