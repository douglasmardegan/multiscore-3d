#include "config.h"
#include "spatial_engine.h"
#include "hmi_ui.h"
#include "storage_telemetry.h"

// Instâncias Globais
SpatialEngine spatialEngine;
HmiUI hmi;
StorageTelemetry telemetry;

int baiaAtual = 1;
unsigned long ultimoDisparoMs = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL, 400000);

  pinMode(PIN_GATILHO, INPUT_PULLUP);

  hmi.inicializar();
  spatialEngine.inicializar();
  telemetry.inicializar();

  hmi.exibirSplashScreen();
}

void loop() {
  // 1. Verificação contínua de nivelamento
  float desvio = spatialEngine.calcularDesvioVertical();
  bool alinhado = (desvio <= LIMIAR_INCLINACAO_MAX);

  // 2. Atualização contínua do visor com indicador de registros salvos na Flash
  size_t totalRegistos = telemetry.obterTotalRegistos();
  hmi.atualizarNivelamento(alinhado, desvio, baiaAtual, totalRegistos);

  // 3. Processamento do Gatilho
  if (digitalRead(PIN_GATILHO) == LOW) {
    if (millis() - ultimoDisparoMs > DEBOUNCE_GATILHO_MS) {
      ultimoDisparoMs = millis();

      if (alinhado) {
        ResultadoPerfilometria resultado = spatialEngine.processarArcoDorsal();
        
        if (resultado.leituraValida) {
          hmi.exibirResultado(resultado, baiaAtual);
          telemetry.salvarRegistoLocal(baiaAtual, resultado);
          
          baiaAtual++;
          delay(TIMEOUT_EXIBICAO_MS);
        }
      } else {
        hmi.alertarInclinacaoIncorreta();
        delay(1200);
      }
    }
  }
}