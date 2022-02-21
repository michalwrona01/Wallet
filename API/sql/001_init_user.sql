
CREATE TABLE AppUser (
    id          INTEGER PRIMARY KEY,
    username    VARCHAR UNIQUE,
    email       VARCHAR UNIQUE,
    password    VARCHAR,
    budget FLOAT
);

INSERT INTO AppUser
(username, email, password) VALUES ('admin', 'admin@domain.com', 'admin');
