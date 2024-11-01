WITH last_updates AS (
    SELECT q1.id, q1.name AS currency_name, q1.updated_last, currency.rate_to_usd 
        FROM
         (
            SELECT id, name, max (updated) AS updated_last from currency
            GROUP BY id, name) q1
        JOIN currency ON q1.id = currency.id AND q1.updated_last = currency.updated
)
SELECT 
    COALESCE(u.name, 'not defined') AS name, 
    COALESCE(u.lastname, 'not defined') AS lastname,
    b.type, 
    sum(b.money) AS volume, 
    COALESCE(lu.currency_name, 'not defined') AS currency_name,
    COALESCE(lu.rate_to_usd, 1) AS last_rate_to_usd, 
    sum(b.money) * COALESCE(lu.rate_to_usd, 1) AS total_volume_in_usd
FROM "user" u
FULL JOIN balance b ON b.user_id = u.id
LEFT JOIN last_updates lu ON lu.id = b.currency_id
GROUP BY u.name, u,lastname, b.type, lu.currency_name, lu.rate_to_usd
ORDER BY 1 DESC, 2, 3;