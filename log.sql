-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE street = "Chamberlin Street" AND year = 2020 AND month = 7 AND day = 28;

-- witnesses
SELECT name, transcript FROM interviews WHERE transcript LIKE "%courthouse%" AND year = 2020 AND month = 7 AND day = 28;

-- checking information from interviews

-- parking
SELECT name FROM people JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate 
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25;

--ATM
SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street"
AND people.id IN (SELECT people.id FROM people JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate 
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25);

-- phone call (receiver is the accomplice)
SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60
AND people.id IN (SELECT people.id FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street"
AND people.id IN (SELECT people.id FROM people JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate 
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25));


-- flights
-- destination
SELECT city FROM flights JOIN airports ON flights.destination_airport_id = airports.id WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1;

--purchasing ticket
SELECT name FROM people JOIN passengers ON people.passport_number = passengers.passport_number JOIN flights ON passengers.flight_id = flights.id WHERE

people.id IN (SELECT people.id FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60
AND people.id IN (SELECT people.id FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street"
AND people.id IN (SELECT people.id FROM people JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate 
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25)))

AND flights.id IN (SELECT flights.id FROM flights JOIN airports ON flights.destination_airport_id = airports.id WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1);

-- accomplice
SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.receiver 
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60
AND caller IN (SELECT phone_number FROM people JOIN passengers ON people.passport_number = passengers.passport_number JOIN flights ON passengers.flight_id = flights.id WHERE
people.id IN (SELECT people.id FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller 
WHERE people.id IN (SELECT people.id FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street"
AND people.id IN (SELECT people.id FROM people JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate 
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25)))

AND flights.id IN (SELECT flights.id FROM flights JOIN airports ON flights.destination_airport_id = airports.id WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1));