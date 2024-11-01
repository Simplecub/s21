SELECT
    pz.name as name, 
    count(*) as count_of_orders, 
    ROUND(AVG(price), 2) as average_price, 
    MAX(price) as max_price, 
    MIN(price) as min_price
FROM menu m
JOIN person_order po ON po.menu_id = m.id
JOIN pizzeria pz ON m.pizzeria_id = pz.id
GROUP BY pz.name
ORDER BY 1;