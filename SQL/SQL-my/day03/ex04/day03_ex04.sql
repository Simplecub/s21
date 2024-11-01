WITH 
female_order AS (
    SELECT pz.name as pizzeria_name 
    FROM  person_order po
    INNER JOIN person p ON p.id = po.person_id 
    INNER JOIN menu m ON m.id = po.menu_id
    INNER JOIN pizzeria pz ON pz.id  = m.pizzeria_id
    WHERE p.gender = 'female' 
),
male_order AS (
    SELECT pz.name as pizzeria_name 
    FROM  person_order po
    INNER JOIN person p ON p.id = po.person_id 
    INNER JOIN menu m ON m.id = po.menu_id
    INNER JOIN pizzeria pz ON pz.id  = m.pizzeria_id
    WHERE p.gender = 'male' 
)
(SELECT pizzeria_name 
    FROM female_order
EXCEPT 
SELECT pizzeria_name 
    FROM male_order)
UNION
(SELECT pizzeria_name 
    FROM male_order
EXCEPT
SELECT pizzeria_name 
    FROM female_order
)
ORDER BY 1;