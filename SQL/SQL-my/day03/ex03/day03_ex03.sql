WITH 
female_visit AS (
    SELECT pz.name as pizzeria_name 
    FROM  person_visits pv
    INNER JOIN person p ON p.id = pv.person_id 
    INNER JOIN pizzeria pz ON pz.id  = pv.pizzeria_id
    WHERE p.gender = 'female' 
),
male_visit AS (
    SELECT pz.name as pizzeria_name 
    FROM  person_visits pv
    INNER JOIN person p ON p.id = pv.person_id 
    INNER JOIN pizzeria pz ON pz.id  = pv.pizzeria_id
    WHERE p.gender = 'male' 
)
(SELECT pizzeria_name 
    FROM female_visit
EXCEPT ALL
SELECT pizzeria_name 
    FROM male_visit)
UNION ALL
(SELECT pizzeria_name 
    FROM male_visit
EXCEPT ALL
SELECT pizzeria_name 
    FROM female_visit
)
ORDER BY 1;

