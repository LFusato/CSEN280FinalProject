INSERT INTO Attendee VALUES ('0','John Doe','day','general'), ('1','Mike Smith','day','volunteer'), ('2','Amy Johnson','day','press'), ('3','Catherine Greene','weekend','general'), ('4','Michelle Chang','weekend','volunteer'), ('5','Jacob Black','weekend','press'), ('6','Jane Doe','day','general'), ('7','Kyle Doe','day','general'), ('8','Steve Lacey','weekend','volunteer');
INSERT INTO Booth VALUES ('001','01'), ('002','01'), ('003','01'), ('004','01'), ('005','01'), ('123','01'), ('001','02'), ('002','02'), ('003','02'), ('004','02'), ('005','02'), ('099','02'), ('106','02');
INSERT INTO Room VALUES ('101','01'), ('102','01'), ('103','01'), ('104','01'), ('105','01'), ('106','01'), ('203','01'), ('101','02'), ('102','02'), ('103','02'), ('104','02'), ('105','02'), ('205','02');

INSERT INTO Exhibitor VALUES ('0','Arts Interactive','2024-11-11 12:00:00','2024-11-11 15:00:00'), ('1','Cool Crafts','2024-11-11 12:00:00','2024-11-12 12:00:00'), ('2','Carey Sovina','2024-11-11 08:00:00','2024-11-11 13:30:00'), ('3','Morgan Reeves','2024-11-12 13:00:00','2024-11-12 16:30:00'), ('4','Gabriel Lopez','2024-11-11 08:30:00','2024-11-12 15:30:00'), ('5','Henry White','2024-11-11 08:45:00','2024-11-12 17:45:00'), ('6','Miles Robinson','2024-11-11 14:00:00','2024-11-12 14:00:00');
INSERT INTO Vendor VALUES ('0','corporate'), ('1','retailer'), ('2','artist'), ('6','artist');
INSERT INTO Guest VALUES ('3'), ('4'), ('5'), ('6');

INSERT INTO Occupied VALUES ('0','001','01'), ('1','003','01'), ('2','123','01');
INSERT INTO Event VALUES ('0', 'panel', '2024-11-11 12:00:00', '0', '101', '01'), ('1', 'fan meet up', '2024-11-12 13:00:00', '0', '104', '02'), ('2', 'screening', '2024-11-12 14:00:00', '0', '205', '02'), ('3', 'fan meet up', '2024-11-12 14:00:00', '0', '102','01');
INSERT INTO Hosts Values ('4', '0'), ('3', '2'), ('4', '3');

INSERT INTO Attends VALUES ('0','0'), ('1','1'), ('2','1'), ('3','1'), ('4','2'), ('5','2'), ('0','1'), ('0','2'), ('6','0'), ('7','0'), ('7','3'), ('8','3');