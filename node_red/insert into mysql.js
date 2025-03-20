// Récupérer le message d'entrée
let input = msg.payload;

// Extraire les valeurs de temp et humid
let temp = input.match(/temp: (\d+\.\d+)/)[1];
let humid = input.match(/humid: (\d+\.\d+)/)[1];

// Formater la requête SQL
let sqlQuery = `
    USE projet72h;
    INSERT INTO capteurs_info (date, capteurs_temp, capteurs_humide)
    VALUES (UNIX_TIMESTAMP(), ${temp}, ${humid});
`;

// Passer la requête SQL dans le message
msg.topic = sqlQuery;

// Retourner le message
return msg;