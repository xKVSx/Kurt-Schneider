DROP TABLE IF EXISTS account;
DROP TABLE IF EXISTS trnsaction;
DROP TABLE IF EXISTS merchant;
DROP TABLE IF EXISTS cardholder;

CREATE TABLE cardHolder (
	ID INT NOT NULL AUTO_INCREMENT,
    fName VARCHAR(50),
    lName VARCHAR(50),
	CONSTRAINT cardHolder_pk PRIMARY KEY (ID)
);

CREATE TABLE account (
	acountNum VARCHAR(100),
    avlLimit DOUBLE,
    ID INT,
    CONSTRAINT acount_pk PRIMARY KEY (acountNum),
    CONSTRAINT acount_fk FOREIGN KEY (ID) REFERENCES cardHolder (ID)
);

CREATE TABLE merchant (
	mName VARCHAR (50),
	mID INT,
    CONSTRAINT merchant_pk PRIMARY KEY (mID)
);

CREATE TABLE trnsaction (
	tID INT NOT NULL AUTO_INCREMENT,
    amount DOUBLE,
    cID INT,
    mID INT,
    CONSTRAINT trnsaction_pk PRIMARY KEY (tID),
    CONSTRAINT trnsaction_fk1 FOREIGN KEY (cID) REFERENCES cardHolder (ID),
	CONSTRAINT trnsaction_fk2 FOREIGN KEY (mID) REFERENCES merchant (mID)
);

INSERT INTO cardholder (fName, lName) VALUES 
	('Bart', 'Simpson'),
    ('Brian', 'Griffin'),
    ('Roger', 'Smith');

INSERT INTO account (acountNum, avlLimit, ID) VALUES
	(SHA2('aaaaaaaaaaaaa', 256), 10000, 1),
    ('bbbbbbbbbbbbb', 1250, 2),
    ('ccccccccccccc', 100, 3);

INSERT INTO merchant (mName, mID) VALUES
	('Brian', 1234),
    ('Lisa', 5678);
    
INSERT INTO trnsaction (amount, cID, mID) VALUES
	(23.50, 1, 1234),
    (125.30, 2, 1234),
    (67.25, 1, 5678);
    



SELECT acountNum
 FROM cardholder AS c INNER JOIN account AS a ON c.ID = a.ID;


