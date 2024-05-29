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

[Planificación del trabajo final](https://drive.google.com/file/d/16kA59A4iBf29dcPQbXB0o-8YjzdNrehf/view?usp=sharing)

## Resolución

Objetivo del ataque: Utilizar la plataforma de monitoreo de rendimiento de computadoras monoplaca (SBC) para instalar un backdoor, mantener acceso persistente, y utilizar las SBC como punto de entrada para comprometer objetivos de mayor relevancia.

### Reconnaissance
  - Buscaré información pública sobre la infraestructura del sistema de monitoreo. [T1595.001 - Active Scanning: Scanning IP Blocks](https://attack.mitre.org/techniques/T1595/001/)
  - Escanearé la IP pública del servidor en busca de puertos abiertos y servicios vulnerables. [T1590.005 - Gather Victim Network Information: IP Addresses](https://attack.mitre.org/techniques/T1590/005/)
  - Utilizaré consultas DNS para recopilar información sobre la infraestructura de red y el dominio del sistema de monitoreo. [T1590.002 - Gather Victim Network Information: DNS](https://attack.mitre.org/techniques/T1590/005/)

### Weaponization
  - Crearé un payload malicioso que incluya un backdoor para mantener acceso persistente y herramientas para la explotación de objetivos de mayor relevancia. [T1027 - Obfuscated Files or Information](https://attack.mitre.org/techniques/T1027/) [T1203 - Exploitation for Client Execution](https://attack.mitre.org/techniques/T1203/) [T1132.001 - Data Encoding: Standard Encoding](https://attack.mitre.org/techniques/T1132/001/)

### Delivery
  - Enviaré correos electrónicos de phishing dirigidos a los administradores del sistema, conteniendo enlaces maliciosos que exploten vulnerabilidades del sistema. [T1566.001 - Phishing: Spearphishing Attachment](https://attack.mitre.org/techniques/T1566/001) [T1566.002 - Phishing: Spearphishing Link](https://attack.mitre.org/techniques/T1566/002/) 
  - Aprovecharé una vulnerabilidad en el frontend para cargar el payload malicioso y establecer un punto de entrada al backend. [T1071.001 - Application Layer Protocol: Web Protocols](https://attack.mitre.org/techniques/T1071/001/)

### Exploitation
  - Utilizaré el exploit para obtener acceso inicial al backend del sistema, escalando privilegios para obtener control total del servidor. [T1068 - Exploitation for Privilege Escalation](https://attack.mitre.org/techniques/T1068/)
  - Extraeré credenciales del servidor y de las computadoras de los administradores del sistema, buscando las que permitan el acceso a las SBC. [T1059 - Command and Scripting Interpreter](https://attack.mitre.org/techniques/T1059/)

### Installation
  - Instalaré el backdoor en el backend y en las SBC comprometidas mediante script bash. [T1105 - Ingress Tool Transfer](https://attack.mitre.org/techniques/T1105/) [T1059 - Command and Scripting Interpreter](https://attack.mitre.org/techniques/T1059/) [T1036.004 - Masquerading: Masquerade Task or Service](https://attack.mitre.org/techniques/T1036/004/)

### Command & Control
  - Estableceré comunicaciones con un servidor de comando y control a través de un servicio web. [T1071.001 - Application Layer Protocol: Web Protocols](https://attack.mitre.org/techniques/T1071/001/) [T1090.002 - Proxy: External Proxy](https://attack.mitre.org/techniques/T1090/002/)
  - Estableceré un túnel HTTPS para mantener la comunicación segura entre el servidor de comando y control y las SBC comprometidas. [T1573.001 - Encrypted Channel: Symmetric Cryptography](https://attack.mitre.org/techniques/T1573/001/)

### Action of Objectives
  - Utilizaré las SBC comprometidas como puntos de acceso para lanzar ataques a objetivos de mayor relevancia en la red. [T1078 - Valid Accounts] [T1071.001 - Application Layer Protocol: Web Protocols]
  - Monitorearé la actividad en la red comprometida para identificar y explotar objetivos de mayor relevancia, como servidores de bases de datos o sistemas de información sensibles. [T1071.001 - Application Layer Protocol: Web Protocols] [T1105 - Ingress Tool Transfer]

