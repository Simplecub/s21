SELECT 
    p.name,
    m.pizza_name,
    m.price,
    ROUND((m.price - (m.price * pd.discount) / 100)) AS discount_price,
    pz.name as pizzeria_name
FROM person_order po
JOIN menu m ON m.id = po.menu_id
JOIN person_discounts pd ON pd.person_id = po.person_id AND pd.pizzeria_id = m.pizzeria_id
JOIN person p ON p.id = po.person_id
JOIN pizzeria pz ON pz.id = m.pizzeria_id
ORDER BY 1,2;