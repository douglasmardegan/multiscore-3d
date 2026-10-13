#include "hmi_ui.h"

HmiUI::HmiUI() 
  : display(128, 64, &Wire, -1) {}

bool HmiUI::inicializar() {
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_VERMELHO, OUTPUT);

  digitalWrite(PIN_LED_VERDE, LOW);
  digitalWrite(PIN_LED_VERMELHO, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, ADDR_OLED)) {
    return false;
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  return true;
}

void HmiUI::exibirSplashScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(8, 6);
  display.println("AGROCERES MULTIMIX");

  display.setTextSize(2);
  display.setCursor(4, 25);
  display.println("MultiScore");
  display.setTextSize(1);
  display.setCursor(108, 25);
  display.println("3D");

  display.setCursor(2, 50);
  display.println("Precisao na sua mao");
  display.display();

  emitirBeep(100);
  delay(1500);
}

void HmiUI::atualizarNivelamento(bool alinhado, float desvio, int baia, size_t totalRegistos) {
  digitalWrite(PIN_LED_VERDE, alinhado ? HIGH : LOW);
  digitalWrite(PIN_LED_VERMELHO, alinhado ? LOW : HIGH);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("BAIA: M-"); display.print(baia);
  display.setCursor(85, 0);
  display.print("#"); display.println(totalRegistos); // Contador de leituras gravadas

  display.setCursor(0, 22);
  if (alinhado) {
    display.println("STATUS: ALINHADO [OK]");
    display.setCursor(0, 42);
    display.println("Premir gatilho...");
  } else {
    display.print("AJUSTE NIVEL: ");
    display.print(desvio, 0);
    display.println((char)247);
    display.setCursor(0, 42);
    display.println("Aponte na vertical");
  }
  display.display();
}

void HmiUI::exibirResultado(ResultadoPerfilometria res, int baia) {
  emitirBeep(80);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("BAIA M-"); display.print(baia);
  display.setCursor(75, 0);
  display.print(res.p2EstimadoMm, 1); display.println("mm P2");

  display.setCursor(0, 16);
  display.print("CLASSE "); display.print(res.classeNum); display.print("/5: ");
  display.println(res.nomeClasse);

  display.setCursor(0, 30);
  display.setTextSize(2);
  display.print("ECC "); display.println(res.eccScore, 1);

  display.setTextSize(1);
  display.setCursor(0, 52);
  display.print("RACAO: ");
  if (res.ajusteRacaoKg > 0) display.print("+");
  display.print(res.ajusteRacaoKg, 1); display.println(" kg/dia");
  
  display.display();
}

void HmiUI::alertarInclinacaoIncorreta() {
  emitirBeep(300);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.println("ERRO: INCLINADO!");
  display.setCursor(5, 38);
  display.println("Manter a 90 graus");
  display.display();
}

void HmiUI::emitirBeep(uint16_t duracaoMs) {
  digitalWrite(PIN_BUZZER, HIGH);
  delay(duracaoMs);
  digitalWrite(PIN_BUZZER, LOW);
}