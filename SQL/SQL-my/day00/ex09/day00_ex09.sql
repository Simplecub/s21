SELECT 	(SELECT name from person WHERE id = pv.person_id) AS person_name ,
    	(SELECT name from pizzeria WHERE id = pv.pizzeria_id) AS pizzeria_name 
FROM (SELECT  * FROM person_visits WHERE visit_date BETWEEN '2022-01-07' and '2022-01-09') AS pv 
ORDER BY person_name, pizzeria_name DESC