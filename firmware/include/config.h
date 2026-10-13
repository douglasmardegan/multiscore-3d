#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ============================================================================
// MAPEAMENTO DE PINOS (ESP32 DevKit V1 - 30 Pinos)
// ============================================================================
#define PIN_I2C_SDA          21    // Linha de Dados I2C
#define PIN_I2C_SCL          22    // Linha de Clock I2C
#define PIN_GATILHO          18    // Botão de Disparo / Gatilho (Pull-up interno)
#define PIN_BUZZER           19    // Buzzer Ativo (Sinalização sonora)
#define PIN_LED_VERDE        4     // LED de Estado: Alinhado / Sucesso
#define PIN_LED_VERMELHO     5     // LED de Estado: Inclinado / Erro
#define PIN_BATERIA_ADC      34    // Leitura analógica do divisor de tensão (0-3.3V)

// ============================================================================
// ENDEREÇOS DO BARRAMENTO I2C
// ============================================================================
#define ADDR_OLED            0x3C  // Display OLED SSD1306 (128x64)
#define ADDR_MPU6050         0x68  // Acelerômetro / Giroscópio
#define ADDR_VL53L5CX        0x29  // Sensor ToF Matricial (8x8 zonas)

// ============================================================================
// LIMIARES DE OPERAÇÃO E TOLERÂNCIA
// ============================================================================
#define LIMIAR_INCLINACAO_MAX 6.0f  // Desvio angular máximo permitido em graus (90° ± 6°)
#define DEBOUNCE_GATILHO_MS   350   // Tempo de debounce do botão de disparo
#define TIMEOUT_EXIBICAO_MS   2500  // Tempo de exibição dos resultados no visor

// ============================================================================
// MATRIZ DE 5 CLASSES DE MANEJO NUTRICIONAL (AGROCERES MULTIMIX)
// ============================================================================
#define P2_LIMIAR_C1_MAX     12.0f // Classe 1: Muito Magra  (< 12.0 mm)
#define P2_LIMIAR_C2_MAX     14.0f // Classe 2: Magra        (12.0 - 13.9 mm)
#define P2_LIMIAR_C3_MAX     18.0f // Classe 3: Ideal        (14.0 - 18.0 mm)
#define P2_LIMIAR_C4_MAX     21.0f // Classe 4: Sobrecond.   (18.1 - 21.0 mm)
                                   // Classe 5: Gorda/Obesa  (> 21.0 mm)

// ============================================================================
// PERSISTÊNCIA E TELEMETRIA BLE
// ============================================================================
#define ARQUIVO_LEITURAS     "/leituras.json"
#define BLE_DEVICE_NAME      "MultiScore3D-Agroceres"
#define BLE_SERVICE_UUID     "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART Service
#define BLE_CHARACTERISTIC_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

#endif // CONFIG_H