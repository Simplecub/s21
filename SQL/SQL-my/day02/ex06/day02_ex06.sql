SELECT  m.pizza_name,  pz.name AS pizzeria_name
FROM person p
 JOIN person_order po ON p.id = po.person_id
 JOIN menu m ON m.id = po.menu_id
 JOIN pizzeria pz ON pz.id = m.pizzeria_id
WHERE p.name IN ('Denis', 'Anna')
ORDER BY 1, 2;