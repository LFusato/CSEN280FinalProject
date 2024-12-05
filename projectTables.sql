DROP DATABASE IF EXISTS Project;
CREATE DATABASE Project;
USE Project;

CREATE TABLE Attendee (
ticket_no INTEGER,
name VARCHAR(40) NOT NULL,
ticket_type ENUM('day', 'weekend') NOT NULL,
status ENUM('general', 'volunteer', 'press') NOT NULL,
PRIMARY KEY (ticket_no));

CREATE TABLE Exhibitor (
ex_id INTEGER, 
name VARCHAR(40) NOT NULL , 
start DATETIME NOT NULL, 
end DATETIME NOT NULL,
PRIMARY KEY (ex_id));

CREATE TABLE Vendor (
ex_id INTEGER,
vend_type ENUM('artist', 'corporate', 'retailer'),
PRIMARY KEY (ex_id),
FOREIGN KEY (ex_id) REFERENCES Exhibitor(ex_id) ON DELETE CASCADE);

CREATE TABLE Guest (
ex_id INTEGER, 
PRIMARY KEY (ex_id),
FOREIGN KEY (ex_id) REFERENCES Exhibitor(ex_id) ON DELETE CASCADE);

CREATE TABLE Room (
room_no INTEGER, 
hall_no INTEGER, 
PRIMARY KEY (room_no, hall_no));

CREATE TABLE Booth (
booth_no INTEGER, 
hall_no INTEGER, 
PRIMARY KEY (booth_no, hall_no));

CREATE TABLE Event (
event_id INTEGER,
event_type ENUM('panel', 'meet & greet', 'fan meet up', 'screening'),
datetime DATETIME NOT NULL,
attendance INTEGER,
room_no INTEGER,
hall_no INTEGER,
UNIQUE (room_no, hall_no),
PRIMARY KEY (event_id),
FOREIGN KEY (room_no, hall_no) REFERENCES Room(room_no, hall_no) ON DELETE CASCADE);

CREATE TABLE Occupied (
ex_id INTEGER UNIQUE,
booth_no INTEGER, 
hall_no INTEGER, 
UNIQUE (booth_no, hall_no),
PRIMARY KEY (ex_id, booth_no, hall_no),
FOREIGN KEY (booth_no, hall_no) REFERENCES Booth(booth_no, hall_no) ON DELETE CASCADE,
FOREIGN KEY (ex_id) REFERENCES Vendor(ex_id));

CREATE TABLE Hosts (
ex_id INTEGER,
event_id INTEGER, 
PRIMARY KEY (ex_id, event_id),
FOREIGN KEY (event_id) REFERENCES Event(event_id) ON DELETE CASCADE,
FOREIGN KEY (ex_id) REFERENCES Guest(ex_id) ON DELETE CASCADE);

CREATE TABLE Attends (
ticket_no INTEGER,
event_id INTEGER,
PRIMARY KEY (ticket_no, event_id),
FOREIGN KEY (ticket_no) REFERENCES Attendee(ticket_no) ON DELETE CASCADE,
FOREIGN KEY (event_id) REFERENCES Event(event_id) ON DELETE CASCADE);

@delimiter %%%;
CREATE TRIGGER update_attendance AFTER INSERT ON Attends
FOR EACH ROW
BEGIN
UPDATE Event
SET Event.attendance = Event.attendance + 1
WHERE Event.event_id = NEW.event_id;
END;
%%% 
@delimiter; 
%%%

INSERT INTO Attendee VALUES ('0','John Doe','day','general'), ('1','Mike Smith','day','volunteer'), ('2','Amy Johnson','day','press'), ('3','Catherine Greene','weekend','general'), ('4','Michelle Chang','weekend','volunteer'), ('5','Jacob Black','weekend','press');
INSERT INTO Booth VALUES ('001','01'), ('002','01'), ('003','01'), ('004','01'), ('005','01'), ('123','01'), ('001','02'), ('106','02'), ('099','02');
INSERT INTO Room VALUES ('101','01'), ('102','01'), ('203','01'), ('104','02'), ('205','02');

INSERT INTO Exhibitor VALUES ('0','Arts Interactive','2024-11-11 12:00:00','2024-11-11 15:00:00'), ('1','Cool Crafts','2024-11-11 12:00:00','2024-11-12 12:00:00'), ('2','Carey Sovina','2024-11-11 08:00:00','2024-11-11 13:30:00'), ('3','Morgan Reeves','2024-11-12 13:00:00','2024-11-12 16:30:00'), ('4','Gabriel Lopez','2024-11-11 08:30:00','2024-11-12 15:30:00'), ('5','Henry White','2024-11-11 08:45:00','2024-11-12 17:45:00');
INSERT INTO Vendor VALUES ('0','corporate'), ('1','retailer'), ('2','artist');
INSERT INTO Guest VALUES ('3'), ('4'), ('5');

INSERT INTO Occupied VALUES ('0','001','01'), ('1','003','01'), ('2','123','01');
INSERT INTO Event VALUES ('0', 'panel', '2024-11-11 12:00:00', '0', '101', '01'), ('1', 'fan meet up', '2024-11-12 13:00:00', '0', '104', '02'), ('2', 'screening', '2024-11-12 14:00:00', '0', '205', '02');
INSERT INTO Hosts Values ('4', '0'), ('3', '2');

INSERT INTO Attends VALUES ('0','0'), ('1','1'), ('2','1'), ('3','1'), ('4','2'), ('5','2');