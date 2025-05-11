const int sensorCorrentePin = A0; // pino analógico para corrente
const int sensorTensaoPin = A1;   // pino analógico para tensão

const int numAmostras = 50;       // número de amostras por ciclo
unsigned long tempoAnterior = 0;
const unsigned long intervaloLeitura = 1000; // intervalo entre ciclos (ms)

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long agora = millis();
  if (agora - tempoAnterior >= intervaloLeitura) {
    tempoAnterior = agora;

    float somaCorrenteQuadrado = 0.0;
    float somaTensaoQuadrado = 0.0;
    float picoCorrente = 0.0;
    float picoTensao = 0.0;

    // Amostragem simulada
    for (int i = 0; i < numAmostras; i++) {
      int leituraCorrente = analogRead(sensorCorrentePin);
      int leituraTensao   = analogRead(sensorTensaoPin);

      // Converte para tensão (0-5V)
      float correnteVolts = leituraCorrente * (5.0 / 1023.0);
      float tensaoVolts   = leituraTensao   * (5.0 / 1023.0);

      // Simula grandezas reais
      float corrente = correnteVolts * 20.0; // até 20A
      float tensao   = tensaoVolts   * 230.0; // até 230V

      somaCorrenteQuadrado += corrente * corrente;
      somaTensaoQuadrado   += tensao * tensao;

      if (corrente > picoCorrente) picoCorrente = corrente;
      if (tensao > picoTensao)     picoTensao = tensao;

      delay(1); // pequeno atraso para espaçar as amostras
    }

    // Cálculo RMS
    float correnteRMS = sqrt(somaCorrenteQuadrado / numAmostras);
    float tensaoRMS   = sqrt(somaTensaoQuadrado / numAmostras);

    // Exibe no formato: <Corrente RMS, Pico> , <Tensão RMS, Pico>
    Serial.print("Corrente RMS: ");
    Serial.print(correnteRMS);
    Serial.print(" A | Pico: ");
    Serial.print(picoCorrente);
    Serial.println(" A");

    Serial.print("Tensao RMS: ");
    Serial.print(tensaoRMS);
    Serial.print(" V | Pico: ");
    Serial.print(picoTensao);
    Serial.println(" V");
    
    Serial.println("--------");
  }
}
