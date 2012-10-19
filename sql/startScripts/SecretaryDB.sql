-- Уровень проводимых соревнований
CREATE TABLE CompetitionRank(
       id INTEGER NOT NULL ,
       description VARCHAR(255) NOT NULL,
       comments VARCHAR(1024),
       PRIMARY KEY(id)
);

CREATE GENERATOR CompetitionRankGen;
COMMIT;
SET TERM !! ;
CREATE TRIGGER CREATE_CompetitionRankId FOR CompetitionRank
	BEFORE INSERT
	AS BEGIN
		NEW.id = GEN_ID(CompetitionRankGen, 1);
 END !!
SET TERM ; !!



-- Соответствие балов занятому месту, в зависимости от ранга соревнований 
CREATE TABLE ScoreRanking(
       rank SMALLINT NOT NULL,
       score SMALLINT NOT NULL,
       competitionRankId INTEGER NOT NULL,
       FOREIGN KEY(competitionRankId) REFERENCES competitionRank(id) on delete cascade
);


-- Соревнование 
CREATE TABLE Competition(
       id INTEGER NOT NULL ,
       beginDate DATE NOT NULL,
       endDate DATE NOT NULL,
       comments VARCHAR(1024),
       competitionRankId INTEGER NOT NULL,
       PRIMARY KEY(id),
       FOREIGN KEY(competitionRankId) REFERENCES CompetitionRank(id) on delete cascade
);

CREATE GENERATOR CompetitionGen;
COMMIT;
SET TERM !! ;
CREATE TRIGGER CREATE_CompetitionId FOR Competition
	BEFORE INSERT
	AS BEGIN
		NEW.id = GEN_ID(CompetitionGen, 1);
 END !!
SET TERM ; !!


-- Боевая версия 
CREATE TABLE FightVersion(
       id INTEGER NOT NULL ,
       code VARCHAR(10) NOT NULL,
       description VARCHAR(255) NOT NULL,
       comments VARCHAR(1024),
       PRIMARY KEY(id)
);

CREATE GENERATOR FightVersionGen;
COMMIT;
SET TERM !! ;
CREATE TRIGGER CREATE_FightVersionId FOR FightVersion
	BEFORE INSERT
	AS BEGIN
		NEW.id = GEN_ID(FightVersionGen, 1);
 END !!
SET TERM ; !!


-- Уровень мастерства 
CREATE TABLE Skill(
       id INTEGER NOT NULL ,
       shortDescription VARCHAR(10) NOT NULL,
       fullDescription VARCHAR(255),
       weight SMALLINT NOT NULL,
       comments VARCHAR(1024),
       PRIMARY KEY(id)
);

CREATE GENERATOR SkillGen;
COMMIT;
SET TERM !! ;
CREATE TRIGGER CREATE_SkillId FOR Skill
	BEFORE INSERT
	AS BEGIN
		NEW.id = GEN_ID(SkillGen, 1);
 END !!
SET TERM ; !!


-- Персона (участник, представитель и т.п.) 
CREATE TABLE Person(
       id INTEGER NOT NULL ,
       name VARCHAR(50) NOT NULL,
       surname VARCHAR(50) NOT NULL,
       patronymic VARCHAR(50) NOT NULL,
       DOB DATE,
       female CHAR DEFAULT 'F',
       phone VARCHAR(100),	-- Может быть несколько контактных телефонов 
       additions VARCHAR(1024),
       PRIMARY KEY(id)
);

CREATE GENERATOR PersonGen;
COMMIT;
SET TERM !! ;
CREATE TRIGGER CREATE_PersonId FOR Person
	BEFORE INSERT
	AS BEGIN
		NEW.id = GEN_ID(PersonGen, 1);
 END !!
SET TERM ; !!

-- Клуб или организация 
CREATE TABLE Club(
       id INTEGER NOT NULL,
       name VARCHAR(100),
	 shortName VARCHAR(10) NOT NULL, -- Короткое название клуба 
       country VARCHAR(50),
       city VARCHAR(50) NOT NULL,
       personId INTEGER NOT NULL,
       comments VARCHAR(1024),
       PRIMARY KEY(id),
       FOREIGN KEY(personId) REFERENCES Person(id) on delete cascade
);

CREATE GENERATOR ClubGen;
COMMIT;
SET TERM !! ;
CREATE TRIGGER CREATE_ClubId FOR Club
	BEFORE INSERT
	AS BEGIN
		NEW.id = GEN_ID(ClubGen, 1);
 END !!
SET TERM ; !!


-- Заявка 
CREATE TABLE Request(
       id INTEGER NOT NULL ,
       competitionId INTEGER NOT NULL,
       clubId INTEGER NOT NULL,
       personId INTEGER NOT NULL, -- Представитель на текущие соревнования, может отличаться от представителя, определенного для клуба 
       comments VARCHAR(1024),
       PRIMARY KEY(id),
       FOREIGN KEY(personId) REFERENCES Person(id) on delete cascade,
       FOREIGN KEY(competitionId) REFERENCES Competition(id) on delete cascade,
       FOREIGN KEY(clubId) REFERENCES Club(id) on delete cascade
);

CREATE GENERATOR RequestGen;
COMMIT;
SET TERM !! ;
CREATE TRIGGER CREATE_RequestId FOR Request
	BEFORE INSERT
	AS BEGIN
		NEW.id = GEN_ID(RequestGen, 1);
 END !!
SET TERM ; !!

-- Участник соревнований 
CREATE TABLE Competitor(
       id INTEGER NOT NULL ,
       skillId INTEGER NOT NULL,
       personId INTEGER NOT NULL,
       requestId INTEGER NOT NULL,
       weight DOUBLE PRECISION NOT NULL,
       PRIMARY KEY(id),
       FOREIGN KEY(personId) REFERENCES Person(id) on delete cascade,
       FOREIGN KEY(skillId) REFERENCES Skill(id) on delete cascade,
       FOREIGN KEY(requestId) REFERENCES Request(id) on delete cascade
);

CREATE GENERATOR CompetitorGen;
COMMIT;
SET TERM !! ;
CREATE TRIGGER CREATE_CompetitorId FOR Competitor
	BEFORE INSERT
	AS BEGIN
		NEW.id = GEN_ID(CompetitorGen, 1);
 END !!
SET TERM ; !!

-- Доступные весовые и возрастные категории 
CREATE TABLE AvailableCategory(
       id INTEGER NOT NULL ,
       startAge SMALLINT NOT NULL,
       endAge SMALLINT NOT NULL,
       startWeight FLOAT NOT NULL,
       endWeight FLOAT NOT NULL,
       female CHAR DEFAULT 'F',
	 ruleCategory CHAR DEFAULT 'F', -- Категория определена правилами 
       comments VARCHAR(1024),
       PRIMARY KEY(id)
);

CREATE GENERATOR AvailableCategoryGen;
COMMIT;
SET TERM !! ;
CREATE TRIGGER CREATE_AvailableCategoryId FOR AvailableCategory
	BEFORE INSERT
	AS BEGIN
		NEW.id = GEN_ID(AvailableCategoryGen, 1);
 END !!
SET TERM ; !!


-- Категория, полученная на соревнованиях 
CREATE TABLE Category(
       id INTEGER NOT NULL ,
       availableCategoryId INTEGER NOT NULL,
       fightVersionId INTEGER NOT NULL,
       competitionId INTEGER NOT NULL,
       PRIMARY KEY(id),
       FOREIGN KEY(availableCategoryId) REFERENCES AvailableCategory(id) on delete cascade,
       FOREIGN KEY(fightVersionId) REFERENCES FightVersion(id) on delete cascade,
       FOREIGN KEY(competitionId) REFERENCES Competition(id) on delete cascade
);

CREATE GENERATOR CategoryGen;
COMMIT;
SET TERM !! ;
CREATE TRIGGER CREATE_CategoryId FOR Category
	BEFORE INSERT
	AS BEGIN
		NEW.id = GEN_ID(CategoryGen, 1);
 END !!
SET TERM ; !!


-- Определяет заявленные боевые версии для участника 
CREATE TABLE CompetitorToFightVersion(
       competitorId INTEGER NOT NULL,
       fightVersionId INTEGER NOT NULL,
       destributed CHAR DEFAULT 'F',
	 CONSTRAINT PK_CompetitorToFightVersion PRIMARY KEY (competitorId, fightVersionId),
       FOREIGN KEY(competitorId) REFERENCES Competitor(id) on delete cascade,
       FOREIGN KEY(fightVersionId) REFERENCES FightVersion(id) on delete cascade
);

-- Определяет нахождение спортсмена в категории 
CREATE TABLE CompetitorToCategory(
       competitorId INTEGER NOT NULL,
       categoryId INTEGER NOT NULL,
       sortion SMALLINT DEFAULT NULL, 

-- Результаты участника, зависящие от категории 

       shootRank SMALLINT, 
	 fightWoKnifeRank SMALLINT, 
	 fightWoKnifeScore SMALLINT, 
	 fightWKnifeRank SMALLINT, 
	 fightWKnifeScore SMALLINT,
	 commonRank SMALLINT, -- Общее место, по всем разделам для участника 

	 CONSTRAINT PK_CompetitorToCategory PRIMARY KEY (competitorId, categoryId ),
       FOREIGN KEY(competitorId) REFERENCES Competitor(id) on delete cascade,
       FOREIGN KEY(categoryId) REFERENCES Category(id) on delete cascade
);

-- Результат участника 
CREATE TABLE Result(
       competitorId INTEGER NOT NULL,
-- Результаты участника, в целом за соревнование 
       crossTime VARCHAR(25),
	 shootScore SMALLINT,

	 
       FOREIGN KEY(competitorId) REFERENCES Competitor(id) on delete cascade
);

-- Добавленные боевые версии 
CREATE TABLE ExtendedFightVersion(
       competitorId INTEGER NOT NULL,
	 fightVersionId INTEGER NOT NULL, 
       FOREIGN KEY(competitorId) REFERENCES Competitor(id) on delete cascade,
       FOREIGN KEY(fightVersionId) REFERENCES FightVersion(id) on delete cascade
);