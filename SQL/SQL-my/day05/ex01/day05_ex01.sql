SET enable_seqscan = off;
EXPLAIN ANALYZE 
SELECT
  m.pizza_name,
  pz.name as pizzeria_name
from menu m
INNER JOIN pizzeria pz ON pz.id = m.pizzeria_id;




