SELECT 
    address, 
    ROUND((MAX(age::numeric) - MIN(age::numeric) / MAX(age::numeric)), 2) as formula, 
    ROUND(AVG(age), 2) as average, 
    (MAX(age) - (MIN(age) / MAX(age))) > AVG(age) as comparison
FROM person
GROUP BY address
ORDER BY 1;

