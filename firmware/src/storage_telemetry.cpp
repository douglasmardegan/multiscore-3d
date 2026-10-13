#include "storage_telemetry.h"

StorageTelemetry::StorageTelemetry() 
  : dispositivoConectadoBLE(false), pServer(nullptr), pTxCharacteristic(nullptr) {}

bool StorageTelemetry::inicializar() {
  pinMode(PIN_BATERIA_ADC, INPUT);

  // 1. Inicializa o sistema de arquivos LittleFS na memória Flash
  if (!LittleFS.begin(true)) {
    Serial.println("Erro ao inicializar LittleFS");
    return false;
  }

  // 2. Inicializa o servidor Bluetooth Low Energy (BLE)
  BLEDevice::init(BLE_DEVICE_NAME);
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(this);

  BLEService* pService = pServer->createService(BLE_SERVICE_UUID);
  pTxCharacteristic = pService->createCharacteristic(
                        BLE_CHARACTERISTIC_TX,
                        BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ
                      );
  pTxCharacteristic->addDescriptor(new BLE2902());

  pService->start();
  BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(BLE_SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  return true;
}

uint8_t StorageTelemetry::obterPercentualBateria() {
  int rawAdc = analogRead(PIN_BATERIA_ADC);
  float tensao = (rawAdc / 4095.0f) * 3.3f * 2.0f;
  
  int pct = (int)((tensao - 3.2f) / (4.2f - 3.2f) * 100.0f);
  if (pct > 100) pct = 100;
  if (pct < 0) pct = 0;
  return (uint8_t)pct;
}

void StorageTelemetry::salvarRegistoLocal(int baia, ResultadoPerfilometria res) {
  File file = LittleFS.open(ARQUIVO_LEITURAS, FILE_APPEND);
  if (!file) {
    Serial.println("Falha ao abrir arquivo para escrita");
    return;
  }

  StaticJsonDocument<256> doc;
  doc["baia"] = baia;
  doc["p2"] = res.p2EstimadoMm;
  doc["ecc"] = res.eccScore;
  doc["classe"] = res.classeNum;
  doc["nome"] = res.nomeClasse;
  doc["racao"] = res.ajusteRacaoKg;
  doc["bat"] = obterPercentualBateria();

  serializeJson(doc, file);
  file.println(); // Quebra de linha por registro (NDJSON format)
  file.close();

  // Se o aplicativo do consultor estiver conectado via BLE no momento do disparo, envia em tempo real
  if (dispositivoConectadoBLE) {
    char buffer[256];
    serializeJson(doc, buffer);
    pTxCharacteristic->setValue(buffer);
    pTxCharacteristic->notify();
  }
}

size_t StorageTelemetry::obterTotalRegistos() {
  if (!LittleFS.exists(ARQUIVO_LEITURAS)) return 0;
  
  File file = LittleFS.open(ARQUIVO_LEITURAS, FILE_READ);
  size_t contagem = 0;
  while (file.available()) {
    String line = file.readStringUntil('\n');
    if (line.length() > 5) contagem++;
  }
  file.close();
  return contagem;
}

void StorageTelemetry::transmitirRondaViaBLE() {
  if (!dispositivoConectadoBLE || !LittleFS.exists(ARQUIVO_LEITURAS)) return;

  File file = LittleFS.open(ARQUIVO_LEITURAS, FILE_READ);
  while (file.available()) {
    String line = file.readStringUntil('\n');
    if (line.length() > 5) {
      pTxCharacteristic->setValue(line.c_str());
      pTxCharacteristic->notify();
      delay(40); // Intervalo de transmissão contínua
    }
  }
  file.close();
}

void StorageTelemetry::limparMemoriaLocal() {
  if (LittleFS.exists(ARQUIVO_LEITURAS)) {
    LittleFS.remove(ARQUIVO_LEITURAS);
  }
}

void StorageTelemetry::onConnect(BLEServer* pServer) {
  dispositivoConectadoBLE = true;
  transmitirRondaViaBLE(); // Sincronização automática dos dados armazenados ao conectar
}

void StorageTelemetry::onDisconnect(BLEServer* pServer) {
  dispositivoConectadoBLE = false;
  BLEDevice::startAdvertising(); // Reinicia visibilidade BLE para novas conexões
}