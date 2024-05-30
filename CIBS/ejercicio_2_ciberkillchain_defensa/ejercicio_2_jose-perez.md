# Ejercicio CiberKillChain - Ataque

## Contenido

- [Ejercicio CiberKillChain - Ataque](#ejercicio-ciberkillchain---ataque)
  - [Contenido](#contenido)
  - [Enunciado](#enunciado)
  - [Alumno](#alumno)
  - [Resolución](#resolución)
    - [Action of Objectives](#action-of-objectives)
    - [Command \& Control](#command--control)
    - [Installation](#installation)
    - [Exploitation](#exploitation)
    - [Delivery](#delivery)
    - [Weaponization](#weaponization)
    - [Reconnaissance](#reconnaissance)

## Enunciado

Desarrollar la defensa en función del ataque planteado en orden inverso. No es una respuesta a un incidente, hay que detectar el ataque independientemente de la etapa.

Para cada etapa elegir una sola defensa, la más importante, considerar recursos limitados.

## Alumno

Jose Perez Galindo

## Resolución

> A través de la Plataforma de rendmiento de computadoras monoplaca, el usuario administrador se percata que algunos dispositivos tienen usos elevados de CPU y RAM. Es ahí donde decide hacer un troubleshooting de esos equipos para diagnosticar el problema y se da con la sorpresa que hay un intruso utilizando los dispositivos.

### Action of Objectives

- Cambiar las contraseñas de los dispositivos comprometidos e implementar políticas de contraseñas seguras, incluyendo requisitos de complejidad, cambios periódicos y prohibición de compartir contraseñas. [M1027 - Password Policies](https://attack.mitre.org/mitigations/M1027/) 

- Implementar monitoreo continuo y alertas para detectar y responder a intentos de acceso o actividades anómalas relacionadas con el uso de red. [M1047 - Audit](https://attack.mitre.org/mitigations/M1047/)

### Command & Control

- Utilizar listas de bloqueo y servicios de inteligencia de amenazas (_Network Behavior Analysis_) para identificar y bloquear dominios y direcciones IP asociadas con servidores y/o usuarios desconocidos. [M1050 - Exploit Protection](https://attack.mitre.org/mitigations/M1050/)
  
- Implementar soluciones de monitoreo de red que puedan identificar y analizar tráfico sospechoso. De esta manera hallar patrones de tráfico inusuales que podrían indicar el uso de proxies y VPNs. [M1037 - Filter Network Traffic](https://attack.mitre.org/mitigations/M1037/)

### Installation

- Instalar soluciones de seguridad como antivirus y antimalware que puedan detectar y bloquear la instalación de software malicioso. Así mismo, Implementar herramientas para prevenir la ejecución de scripts no aprobados. [M1049 - Antivirus/Antimalware](https://attack.mitre.org/mitigations/M1049/), [M1038 - Execution Prevention](https://attack.mitre.org/mitigations/M1038/)

- Configurar políticas que aseguren que solo los administradores TI puedan instalar software. Limitar los privilegios de los usuarios regulares para prevenir la instalación de software no autorizado. [M1026 - Privileged Account Management](https://attack.mitre.org/mitigations/M1026/)

### Exploitation

- Realizar programas de concienciación y formación en seguridad para educar a los usuarios sobre los riesgos de hacer clic en enlaces y abrir archivos adjuntos de fuentes desconocidas o no confiables. [M1017 - User Training](https://attack.mitre.org/mitigations/M1017/)

### Delivery

- Configurar filtros de spam y antivirus en los servidores de correo para inspeccionar y analizar los correos electrónicos entrantes en busca de contenido malicioso. [M1031 - Network Intrusion Prevention](https://attack.mitre.org/mitigations/M1031/)
  
- Realizar programas de concienciación y formación en seguridad para educar a los usuarios, especialmente a los administradores del sistema, sobre los riesgos del phishing y cómo identificar correos electrónicos sospechosos. [M1017 - User Training](https://attack.mitre.org/mitigations/M1017/)

### Weaponization

- Fuera del alcance de las defensas y controles de la empresa.

### Reconnaissance

- Los esfuerzos deben centrarse en reducir al mínimo la cantidad y la sensibilidad de los datos disponibles para las partes externas. Educando a los empleados sobre la importancia de no compartir información personal en sitios abieirtos. [M1056 - Pre-compromise](https://attack.mitre.org/mitigations/M1056/), [M1017 - User Training](https://attack.mitre.org/mitigations/M1017/)
