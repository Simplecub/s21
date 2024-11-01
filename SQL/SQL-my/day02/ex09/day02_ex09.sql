SELECT  p.name
FROM person_order po
    JOIN person p ON p.id = po.person_id
    JOIN menu m ON po.menu_id = m.id
WHERE p.gender='female'  
   AND m.pizza_name IN ('pepperoni pizza', 'cheese pizza')
GROUP BY p.id
HAVING COUNT(DISTINCT m.pizza_name) = 2
ORDER BY 1 ;