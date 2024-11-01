SELECT m.pizza_name, m.price, pz.name AS pizzeria_name
FROM 
(SELECT id AS menu_id
FROM menu 
EXCEPT SELECT menu_id FROM person_order) q
INNER JOIN menu m ON q.menu_id = m.id
INNER JOIN pizzeria pz ON pz.id = m.pizzeria_id
ORDER BY 1,2;

