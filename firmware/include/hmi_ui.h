#ifndef HMI_UI_H
#define HMI_UI_H

#include "config.h"
#include "spatial_engine.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class HmiUI {
public:
  HmiUI();
  bool inicializar();
  void exibirSplashScreen();
  void atualizarNivelamento(bool alinhado, float desvio, int baia, size_t totalRegistos);
  void exibirResultado(ResultadoPerfilometria res, int baia);
  void alertarInclinacaoIncorreta();
  void emitirBeep(uint16_t duracaoMs);

private:
  Adafruit_SSD1306 display;
};

#endif // HMI_UI_H