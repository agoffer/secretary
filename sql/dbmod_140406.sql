ALTER TABLE Club ADD shortName VARCHAR(15);
UPDATE Club SET shortName = name;