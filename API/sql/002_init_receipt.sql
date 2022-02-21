-- CREATE TABLE AppUser (
--                          id          INTEGER PRIMARY KEY,
--                          username    VARCHAR UNIQUE,
--                          email       VARCHAR UNIQUE,
--                          password    VARCHAR
-- );
--
-- INSERT INTO AppUser
-- (username, email, password) VALUES ('admin', 'admin@domain.com', 'admin');
--

CREATE TABLE AppReceipt (
                         id          INTEGER PRIMARY KEY,
                         shopName    VARCHAR,
                         companyName VARCHAR,
                         numberReceipt INTEGER,
                         nipNumber INTEGER,
                         price FLOAT,
                         dateCreated TEXT,
                         userId INTEGER,
                         FOREIGN KEY(userId) REFERENCES AppUser(id)
);

INSERT INTO AppReceipt
(shopName, companyName, numberReceipt, nipNumber, price, dateCreated, userId)
VALUES ('Shop', 'CompanyShop', 1111, 987654321, 500.75, '2022.01.01', 1);
