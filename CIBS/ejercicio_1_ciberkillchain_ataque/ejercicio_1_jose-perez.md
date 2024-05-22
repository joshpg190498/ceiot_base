# Ejercicio CiberKillChain - Ataque

## Contenido

- [Ejercicio CiberKillChain - Ataque](#ejercicio-ciberkillchain---ataque)
  - [Contenido](#contenido)
  - [Enunciado](#enunciado)
  - [Alumno](#alumno)
  - [Resumen TP](#resumen-tp)
  - [Resolución](#resolución)
    - [Reconnaissance](#reconnaissance)
    - [Weaponization](#weaponization)
    - [Delivery](#delivery)
    - [Exploitation](#exploitation)
    - [Installation](#installation)
    - [Command \& Control](#command--control)
    - [Action of Objectives](#action-of-objectives)

## Enunciado

Armar una cyberkillchain usando técnicas de la matriz de Att&ck para un escenario relacionado al trabajo práctico de la carrera.

## Alumno

Jose Perez Galindo

## Resumen TP

Se implementará una plataforma para monitorear el rendimiento de computadoras monoplaca (SBC) basadas en Linux, centralizando datos de CPU, RAM, espacio libre en disco, estado de la red, entre otros, en un servidor.

Las SBCs enviarán estos datos al servidor mediante protocolo MQTT. El servidor contará con servicios para recibir y enviar configuraciones, almacenar y procesar datos y generar alertas vía mail. Asimismo, el servidor desplegará una web que permitirá la gestión de SBCs y visualización de datos en tablas y gráficos.

Planificación del trabajo final: https://drive.google.com/file/d/16kA59A4iBf29dcPQbXB0o-8YjzdNrehf/view?usp=sharing

## Resolución

Objetivo del ataque: Utilizar la plataforma de monitoreo de rendimiento de computadoras monoplaca (SBC) para instalar un backdoor, mantener acceso persistente, y utilizar las SBC como punto de entrada para comprometer objetivos de mayor relevancia.

### Reconnaissance
  - Buscaré información pública sobre la infraestructura del sistema de monitoreo.
  - Escanearé la IP pública del servidor en busca de puertos abiertos y servicios vulnerables.
  - Utilizaré consultas DNS para recopilar información sobre la infraestructura de red y el dominio del sistema de monitoreo.

### Weaponization
  - Crearé un payload malicioso que incluya un backdoor para mantener acceso persistente y herramientas para la explotación de objetivos de mayor relevancia.

### Delivery
  - Enviaré correos electrónicos de phishing dirigidos a los administradores del sistema, conteniendo enlaces maliciosos que exploten vulnerabilidades del sistema.
  - Aprovecharé una vulnerabilidad en el frontend para cargar el payload malicioso y establecer un punto de entrada al backend.

### Exploitation
  - Utilizaré el exploit para obtener acceso inicial al backend del sistema, escalando privilegios para obtener control total del servidor.
  - Extraeré credenciales del servidor y de las computadoras de los administradores del sistema, buscando las que permitan el acceso a las SBC.

### Installation
  - Instalaré el backdoor en el backend y en las SBC comprometidas mediante script bash.

### Command & Control
  - Estableceré comunicaciones con un servidor de comando y control a través de un servicio web.
  - Estableceré un túnel HTTPS para mantener la comunicación segura entre el servidor de comando y control y las SBC comprometidas.

### Action of Objectives
  - Utilizaré las SBC comprometidas como puntos de acceso para lanzar ataques a objetivos de mayor relevancia en la red.
  - Monitorearé la actividad en la red comprometida para identificar y explotar objetivos de mayor relevancia, como servidores de bases de datos o sistemas de información sensibles.