SELECT order_date, CONCAT(name, ' (age:', age, ')') as person_information
	FROM person_order
    INNER JOIN person  ON person_order.person_id = person.id
ORDER BY 1,  2