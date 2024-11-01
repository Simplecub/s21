SELECT p.name AS person_name, menu.pizza_name AS pizza_name, pizzeria.name AS pizzeria_name
FROM person_order 
JOIN person p ON p.id = person_order.person_id 
JOIN menu ON menu.id = person_order.menu_id
JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
ORDER BY 1, 2, 3