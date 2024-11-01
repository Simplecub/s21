SELECT order_date, name||' (age:'||age||')' AS person_information
	FROM person_order
    NATURAL JOIN 
   (SELECT id AS person_id, name, age from person ) AS p
ORDER BY 1, 2