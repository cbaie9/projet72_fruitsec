// Vérifier si msg.payload est une chaîne de caractères
if (typeof msg.payload === 'string') {
  try {
    // Convertir la chaîne en tableau JSON
    msg.payload = JSON.parse(msg.payload);
  } catch (e) {
    // En cas d'erreur de conversion, définir msg.payload à null
    msg.payload = null;
    return msg;
  }
}

// Vérifier si msg.payload est un tableau non vide
if (Array.isArray(msg.payload) && msg.payload.length > 0) {
  // Trier le tableau par date (du plus récent au plus ancien)
  msg.payload.sort((a, b) => b.date - a.date);
  // Extraire la température de l'objet le plus récent
  msg.payload = msg.payload[0].capteurs_temp;
} else {
  // Si le tableau est vide ou non valide, définir une valeur par défaut
  msg.payload = null;
}
return msg;