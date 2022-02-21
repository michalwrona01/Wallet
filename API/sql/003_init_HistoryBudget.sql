CREATE TABLE AppHistoryBudget(
    id INTEGER PRIMARY KEY,
    amount FLOAT,
    receiptId INTEGER DEFAULT NULL,
    dateCreated TEXT,
    topic VARCHAR,
    userId INTEGER,
    FOREIGN KEY(userId) REFERENCES AppUser(id)
);

INSERT INTO AppHistoryBudget (amount, userId) VALUES (1597, 1);