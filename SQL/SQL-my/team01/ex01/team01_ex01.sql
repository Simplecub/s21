insert into currency values (100, 'EUR', 0.85, '2022-01-01 13:29');
insert into currency values (100, 'EUR', 0.79, '2022-01-08 13:29');


SELECT 
    COALESCE(u.name, 'not defined') AS name, 
    COALESCE(u.lastname, 'not defined') AS lastname, 
    c.name AS currency_name,
    (b.money * COALESCE(
        (SELECT rate_to_usd FROM currency WHERE currency.id = b.currency_id AND  currency.updated < b.updated
        ORDER BY currency.updated DESC
        LIMIT 1
        ),
        (SELECT rate_to_usd FROM currency WHERE currency.id = b.currency_id AND currency.updated >= b.updated
        ORDER BY currency.updated  
        LIMIT 1))
    )::real AS currency_in_usd 
FROM "user" u
    RIGHT JOIN balance b ON b.user_id = u.id
    JOIN currency c ON c.id = b.currency_id
GROUP BY b.user_id, b.money, b.updated, u.name, u.lastname, b.currency_id, c.name
ORDER BY 1 DESC, 2, 3;