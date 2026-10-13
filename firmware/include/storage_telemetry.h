#ifndef STORAGE_TELEMETRY_H
#define STORAGE_TELEMETRY_H

#include "config.h"
#include "spatial_engine.h"
#include <LittleFS.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <ArduinoJson.h>

class StorageTelemetry : public BLEServerCallbacks {
public:
  StorageTelemetry();
  bool inicializar();
  void salvarRegistoLocal(int baia, ResultadoPerfilometria res);
  size_t obterTotalRegistos();
  void transmitirRondaViaBLE();
  void limparMemoriaLocal();
  uint8_t obterPercentualBateria();

  // Callbacks do Servidor BLE
  void onConnect(BLEServer* pServer) override;
  void onDisconnect(BLEServer* pServer) override;

private:
  bool dispositivoConectadoBLE;
  BLEServer* pServer;
  BLECharacteristic* pTxCharacteristic;
};

#endif // STORAGE_TELEMETRY_H