WITH 
visits AS (
SELECT pv.pizzeria_id, count(*) AS count, 'visit' AS action_type
FROM person_visits pv 
GROUP BY pv.pizzeria_id
ORDER BY 3, 2 DESC
),
orders AS (
SELECT m.pizzeria_id, count(*) AS count,  'order' AS action_type
FROM person_order po
JOIN menu m ON m.id = po.menu_id
GROUP BY m.pizzeria_id
ORDER BY 3, 2 DESC
)
SELECT pz.name AS name, count, action_type
FROM (
(SELECT * FROM visits LIMIT 3)
UNION ALL
(SELECT * FROM orders LIMIT 3)
) q
JOIN pizzeria pz ON q.pizzeria_id = pz.id
ORDER BY 3, 2 desc;
