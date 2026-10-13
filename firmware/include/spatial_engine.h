#ifndef SPATIAL_ENGINE_H
#define SPATIAL_ENGINE_H

#include "config.h"

enum CategoriaECC {
  MUITO_MAGRA = 1,
  MAGRA       = 2,
  IDEAL       = 3,
  SOBRECOND   = 4,
  GORDA       = 5
};

struct ResultadoPerfilometria {
  float anguloP2Graus;
  float p2EstimadoMm;
  float eccScore;
  CategoriaECC classeEnum;
  int classeNum;
  String nomeClasse;
  float ajusteRacaoKg;
  bool leituraValida;
};

class SpatialEngine {
public:
  SpatialEngine();
  bool inicializar();
  float calcularDesvioVertical();
  ResultadoPerfilometria processarArcoDorsal();

private:
  bool mpuInicializado;
  bool tofInicializado;
  void acordarMPU6050();
};

#endif // SPATIAL_ENGINE_H