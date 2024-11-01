SELECT DISTINCT p.name
FROM person_order po
    JOIN person p ON p.id = po.person_id
    JOIN menu m ON po.menu_id = m.id
WHERE p.gender='male'  
    AND p.address IN ('Samara', 'Moscow') 
    AND m.pizza_name IN ('pepperoni pizza', 'mushroom pizza')
ORDER BY 1 DESC;