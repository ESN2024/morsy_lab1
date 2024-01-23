# Introduction
Au cours de ce Tp, nous allons appliquer les connaissances théoriques acquises en cours en travaillant avec la carte Terasic DE10-Lite, qui est basée sur un FPGA Altera MAX 10.
L'objectif principal de ce TP est de mettre en œuvre un chenillard de LEDs à l'aide d'interruptions. Pour ce faire, nous utiliserons les fonctionnalités disponibles sur la carte, notamment les LEDs, les interrupteurs et les boutons poussoirs.

# Architecture

![image](https://github.com/ESN2024/morsy_lab1/assets/74385250/12b8163e-c3b8-46bc-a93c-1bd9a3972c8b)

Tout d'abord, j'ai inclus les composants nécessaires pour reconstruire mon système de base.

* RAM
* JTAG
* NIOS-2
* CLOCK

Apres, on ajoute :

* un PIO 8 bits pour les switches
* un PIO 8 bits pour les leds 
* un PIO 1 bits pour le boutton poussoir
* un PIO 1 bits pour RESET (SWITCH)

# Platform Designer 
voici notre l'architecture sous Platform Designer (QSYS)

![image](https://github.com/ESN2024/morsy_lab1/assets/74385250/ccdb5bec-5759-42b8-81c0-bb99fc97d4aa)

# Questions de tps
J'ai cree mon fichier "morsy_lab1.vhd" et apres j'ai effectue es affectations de broches (pin assignments) et compilé mon système dans Quartus pour passer à la partie logicielle. Mon objectif est de mettre en œuvre le chenillard LED sur les LEDs, d'activer et de désactiver le chenillard LED à l'aide d'interruptions de bouton, et enfin de gérer la vitesse à l'aide d'interruptions de SWITCHEs
et apres j'ai cree 3 fichiers .c : "cheneillard.c","cheneillard_interrup.c","led_cheneillard_interrup_vitesse.c"

# cheneillard 

Pour mettre en œuvre le chenillard de LEDs, j'ai simplement effectué des décalages de bits vers la gauche dans une boucle, en commençant par la LED 0 jusqu'à la LED 7, puis des décalages vers la droite de la LED 7 à la LED 0.

# Cheneillard avec une interruption 

 j'ai implémenté différentes fonctions pour gérer les interruptions. "irqhandler_btn()" gère les interruptions pour les boutons. Dans ma fonction principale, j'ai initialisé les interruptions en spécifiant les masques et que ma fonction d'interruption va etre declenche avec le boutton poussoir "PUSH_BTN_IRQ" (On peut savoir le nom depuis le fichier systeme.h). Dans la fonction "irqhandler_btn()", je vérifie que le bouton est pressé. Selon le bouton, je démarre le chenillard de LEDs ou le réinitialise en remettant à zéro les variables utilisées pour le contrôler.

# Vitesse ed cheneillard controlle par les SWITCHES 

Dans la fonction "irqhandler_switch", je commence par lire le registre du SWITCHES. Ensuite, je reupere le nombre de bits positionnés à 1 dans le registre. En fonction de ce nombre, je modifie la variable "time" pour ajuster la vitesse du chenillard de LEDs.

https://github.com/ESN2024/morsy_lab1/assets/74385250/84c23ee5-dbba-4857-b2b2-5cf358cd1093

# Conclusion 

Ce Tp m'appris comment faire la conception conjointe sur Quartus en utilisant le systeme NIOS II .j'ai pu créer une architecture système pour contrôler un chenillard de LED en utilisant des entrées telles que des boutons et des Switch. Aussi m'a appris comment generer les interruptions au niveau de gpio et comment les utiliser et les declarer dans le code.


Les difficultés principales rencontrées lors de ce premier TP sont 

* Lors de la création du projet, ne pas choisir la vraie board pour le de10 .
* gérer les interruptions
