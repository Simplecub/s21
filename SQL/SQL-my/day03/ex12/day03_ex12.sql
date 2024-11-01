
INSERT INTO person_order  (id, person_id, menu_id, order_date)
SELECT generate_series( (SELECT MAX(id) FROM person_order) + 1,
                        (SELECT MAX(id) FROM person) + (SELECT count(*) FROM person_order)) as id,
       generate_series( (SELECT MIN(id) FROM person), (SELECT  count(*) FROM person)) as person_id,
       (SELECT id FROM menu WHERE pizza_name = 'greek pizza') menu_id,
       '2022-02-25' as order_date;