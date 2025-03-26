// Fonction pour traiter les valeurs des capteurs
if (msg.payload.capteurs_pbs === 50) {
    return { payload: "Température trop haute" };
} else if (msg.payload.capteurs_pbs === 75) {
    return { payload: "Humidité trop haute" };
} else {
    // Retourne null si aucune condition n'est remplie (facultatif)
    return { payload: "Fonctionnement Normal" };
}