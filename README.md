# MultiScore 3D — Smart Livestock Scoring System

> *A precisão na palma da sua mão.*

[![Status](https://img.shields.io/badge/Status-Proprietary%20Dev-blue.svg)](#-propriedade-intelectual)
[![Framework](https://img.shields.io/badge/Framework-Embedded%20C%2B%2B-orange.svg)](#)
[![License](https://img.shields.io/badge/License-All%20Rights%20Reserved-red.svg)](#-intellectual-property--copyright)

*Read this document in [English](README.en.md).*

O **MultiScore 3D** é um sistema embarcado portátil projetado para a automação e padronização do Escore de Condição Corporal (ECC) e mensuração da curvatura dorsal em matrizes suínas.

A solução substitui métricas visuais subjetivas por perfilometria tridimensional e validação espacial contínua, permitindo a integração de dados biométricos em tempo real com programas de nutrição de precisão.

## 🚀 Funcionalidades principais

- **Perfilometria dorsal não invasiva 3D:** Mapeamento geométrico tridimensional do relevo anatômico via matrizes ToF (*Time-of-Flight*) sem contato físico ou estresse ao animal.
- **Validação espacial em tempo real:** Filtro inercial (IMU) e correção angular que garantem capturas precisas e descartam leituras fora dos limiares de tolerância.
- **Filtragem inteligente de ambientes (Oclusão):** Algoritmo de filtragem espacial capaz de isolar o dorso do animal e descartar automaticamente interferências de barras metálicas de gaiolas e pisos ripados.
- **Suporte a 5 níveis de manejo nutricional:** Categorização biométrica direta alinhada às réguas das caixas dosadoras do galpão de gestação/maternidade.
- **Interface HMI inteligente:** Indicação visual e sonora imediata para suporte à tomada de decisão rápida no corredor de manejo.
- **Arquitetura *Offline-First*:** Armazenamento local de avaliações com sincronização assíncrona via *Bluetooth Low Energy* para ambientes sem conectividade Wi-Fi.
- **Estrutura de campo sanitizável:** Projeto ergonômico vedado, resistente a agentes de desinfecção e rotinas severas do ambiente agrícola.

## 🔒 Propriedade intelectual & direitos de autor

- **Uso restrito:** Este repositório é disponibilizado publicamente apenas para fins de demonstração acadêmica e portfólio técnico.
- **Direitos reservados:** Os modelos de calibração, algoritmos de regressão e lógica de negócios são de propriedade exclusiva do autor.
- **Licenciamento:** A reprodução, redistribuição, engenharia reversa ou uso comercial do código e esquemáticos sem autorização prévia por escrito é estritamente proibida.
