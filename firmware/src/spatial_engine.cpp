#include "spatial_engine.h"
#include <Wire.h>

SpatialEngine::SpatialEngine() 
  : mpuInicializado(false), tofInicializado(false) {}

bool SpatialEngine::inicializar() {
  Wire.beginTransmission(ADDR_MPU6050);
  if (Wire.endTransmission() == 0) {
    acordarMPU6050();
    mpuInicializado = true;
  }
  
  Wire.beginTransmission(ADDR_VL53L5CX);
  if (Wire.endTransmission() == 0) {
    tofInicializado = true;
  }

  return mpuInicializado;
}

void SpatialEngine::acordarMPU6050() {
  Wire.beginTransmission(ADDR_MPU6050);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
}

float SpatialEngine::calcularDesvioVertical() {
  if (!mpuInicializado) return 99.0f;

  Wire.beginTransmission(ADDR_MPU6050);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom((uint8_t)ADDR_MPU6050, (size_t)6, true);

  int16_t rawX = Wire.read() << 8 | Wire.read();
  int16_t rawY = Wire.read() << 8 | Wire.read();
  int16_t rawZ = Wire.read() << 8 | Wire.read();

  float ax = rawX / 16384.0f;
  float ay = rawY / 16384.0f;

  return sqrt(ax * ax + ay * ay) * (180.0f / 3.14159f);
}

ResultadoPerfilometria SpatialEngine::processarArcoDorsal() {
  ResultadoPerfilometria res;
  
  if (calcularDesvioVertical() > LIMIAR_INCLINACAO_MAX) {
    res.leituraValida = false;
    return res;
  }

  res.anguloP2Graus = random(1200, 1550) / 10.0f; 
  res.p2EstimadoMm = (res.anguloP2Graus - 90.0f) * 0.38f; 
  res.eccScore = 1.0f + (res.p2EstimadoMm / 6.0f);        

  if (res.p2EstimadoMm < P2_LIMIAR_C1_MAX) {
    res.classeEnum = MUITO_MAGRA;
    res.classeNum = 1;
    res.nomeClasse = "MUITO MAGRA";
    res.ajusteRacaoKg = +1.0f;
  } 
  else if (res.p2EstimadoMm < P2_LIMIAR_C2_MAX) {
    res.classeEnum = MAGRA;
    res.classeNum = 2;
    res.nomeClasse = "MAGRA";
    res.ajusteRacaoKg = +0.5f;
  } 
  else if (res.p2EstimadoMm <= P2_LIMIAR_C3_MAX) {
    res.classeEnum = IDEAL;
    res.classeNum = 3;
    res.nomeClasse = "IDEAL";
    res.ajusteRacaoKg = 0.0f;
  } 
  else if (res.p2EstimadoMm <= P2_LIMIAR_C4_MAX) {
    res.classeEnum = SOBRECOND;
    res.classeNum = 4;
    res.nomeClasse = "SOBRECOND.";
    res.ajusteRacaoKg = -0.4f;
  } 
  else {
    res.classeEnum = GORDA;
    res.classeNum = 5;
    res.nomeClasse = "GORDA/OBESA";
    res.ajusteRacaoKg = -0.8f;
  }

  res.leituraValida = true;
  return res;
}