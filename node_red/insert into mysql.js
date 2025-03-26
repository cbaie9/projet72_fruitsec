// Récupérer le message d'entrée
let input = msg.payload;

// Extraire les valeurs de temp et humid
let temp = parseFloat(input.match(/temp: (\d+\.\d+)/)[1]);
let humid = parseFloat(input.match(/humid: (\d+\.\d+)/)[1]);

// Initialiser capteurs_pbs à 0 (pas de problème)
let capteurs_pbs = 0;

// Déterminer la valeur de capteurs_pbs selon les seuils
if (temp > 40) {
    capteurs_pbs = 50;  // Code pour température trop haute
} 
else if (humid > 80) {
    capteurs_pbs = 75;  // Code pour humidité trop haute
}

// Formater la requête SQL
let sqlQuery = `
    USE projet72h;
    INSERT INTO capteurs_info (date, capteurs_temp, capteurs_humide, capteurs_pbs)
    VALUES (UNIX_TIMESTAMP(), ${temp}, ${humid}, ${capteurs_pbs});
`;

// Passer la requête SQL dans le message
msg.topic = sqlQuery;

// Retourner le message
return msg;