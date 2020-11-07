# GestionDesTransports

Pour pouvoir s'intégrer au système, l'unité de gestion des transports devra pouvoir au minimum:
- Servir de passerelle entre les éléments du système qui communiquent sur le réseau CAN et la tour de transmission qui communique avec le véhicule à l’aide d’un lien Wi-Fi/UDP ;
- Communiquer par lien série avec la tour de communications pour recevoir des messages en provenance du véhicule ou en sa direction ;
- Reconnaître et récupérer les messages CAN qui seront d'intérêts pour le véhicule ;
- Transmettre à la tour de communications l'information qu'elle aura récupérer à l'intention du véhicule ;
- Échanger avec la tour de communications pour récupérer les informations qui seront rendues disponibles par le véhicule ;
- Transmettre des messages CAN qui contiendront les informations que lui fera parvenir le véhicule ;
- Décoder les messages qui lui permettront de savoir si le système est en arrêt ou en opération ;
- Émettre des messages qui permettront de connaître s'il est en fonction, en erreur ou en arrêt ;
- Se mettre en arrêt ou en opération ;
- Opérer à l'aide d'une base de temps, d'un service de base de temps, de pilotes, d'interfaces, de processus et de services.
