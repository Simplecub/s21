SELECT m1.pizza_name, m1.name AS pizzeria_name_1, m2.name AS pizzeria_name_2, m1.price
FROM (
    SELECT pizza_name, price, pizzeria_id, pz.name 
    FROM menu m
    INNER JOIN pizzeria pz ON pz.id  = m.pizzeria_id
     ) m1
JOIN (
    SELECT pizza_name, price, pizzeria_id, pz.name 
    FROM menu m
    INNER JOIN pizzeria pz ON pz.id  = m.pizzeria_id
     ) m2 ON m1.pizza_name = m2.pizza_name AND m1.price = m2.price 
WHERE m1.price = m2.price AND m1.pizzeria_id > m2.pizzeria_id
ORDER BY 1;