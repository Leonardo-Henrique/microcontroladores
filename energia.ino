// energia.ino

const int sensorCorrentePin = A0; // pino analógico para corrente
const int sensorTensaoPin = A1;   // pino analógico para tensão

float sensorCorrenteValor = 0.0;
float sensorTensaoValor = 0.0;
unsigned long tempoAnterior = 0;
const unsigned long intervaloLeitura = 100; // ms

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long agora = millis();
  if (agora - tempoAnterior >= intervaloLeitura) {
    tempoAnterior = agora;
    // Leitura simulada: mapeia valores analógicos para grandezas
    sensorCorrenteValor = analogRead(sensorCorrentePin) * (5.0 / 1023.0) * 20.0; // simula até 20A
    sensorTensaoValor   = analogRead(sensorTensaoPin)   * (5.0 / 1023.0) * 230.0; // simula até 230V

    // Envia via Serial: <corrente, tensão>
    Serial.print(sensorCorrenteValor);
    Serial.print(",");
    Serial.println(sensorTensaoValor);
  }
}