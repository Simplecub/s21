 INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)
 VALUES ( (SELECT max(id) +1 FROM person_visits), 
          (SELECT id FROM person WHERE name = 'Dmitriy'),
          (SELECT DISTINCT pz.id AS pizzeria_id
            FROM  pizzeria pz 
            JOIN menu m ON pz.id= m.pizzeria_id
            WHERE m.price < 800 
                AND pz.id NOT IN (
                    SELECT pv.pizzeria_id
                    FROM person_visits pv
                    JOIN person p ON p.id = pv.person_id AND p.name != 'Dmitriy')
               ), 
          '2022-01-08'::date);

REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;


--SELECT * from person_visits;
--DELETE FROM person_visits  WHERE id= 20;