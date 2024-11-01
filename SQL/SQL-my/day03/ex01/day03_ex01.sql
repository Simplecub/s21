SELECT m.id AS menu_id
FROM menu m
EXCEPT SELECT menu_id FROM person_order
ORDER BY 1;