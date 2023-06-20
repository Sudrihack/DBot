# DBot
[![DeepScan grade](https://deepscan.io/api/teams/10089/projects/24928/branches/771414/badge/grade.svg)](https://deepscan.io/dashboard#view=project&tid=10089&pid=24928&bid=771414)
Ce projet consiste en la conception et la construction d'un chien robot imprimé en 3D, utilisant une puce ESP32 pour la communication WiFi UDP et Bluetooth. Le robot est contrôlé à distance depuis un appareil externe et peut réagir à certains stimuli externes.

## Fonctionnalités

- Mouvement : Le robot est capable de se déplacer à l'aide de ses pattes.
- Contrôle à distance : Vous pouvez contrôler le robot via une connexion WiFi sur un serveur UDP ou Bluetooth depuis un appareil externe.


## Configuration du projet

1. Cloner le projet
2. Assurez-vous d'avoir les outils nécessaires pour compiler et téléverser le code sur la carte ESP32.
(Ex: VSCode)
3. Ouvrez le projet dans votre environnement de développement Platform.io


## Utilisation

1. Compilez et téléversez le code sur la carte.
2. Alimentez le chien robot et assurez-vous qu'il est connecté au réseau WiFi ou au périphérique Bluetooth approprié.
3. Utilisez l'application DBotControl ou un programme de contrôle à distance pour envoyer des commandes au chien robot et observer ses réactions.
    // wifiManager.WiFiManagerInit();
## Auteurs

- Baptiste Desfontaines (@baptistedftn)

- Oscar Debacker (@Oscardbk)

## Licence

Voir le fichier [LICENSE](LICENSE) pour plus d'informations.
