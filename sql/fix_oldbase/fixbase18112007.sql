-- Добавлено поле, для определения типа жеребьевки (A - автоматическая, 
--  M - ручная) 
alter table category add  drawtype  char(1) default null

-- Тригер, для типа жеребьевки 
SET TERM ^;
CREATE TRIGGER TRIG_UPDATECATEGORY_DT
FOR COMPETITORTOCATEGORY
ACTIVE AFTER INSERT OR DELETE 
AS
BEGIN
 update Category set drawType = NULL where id = OLD.categoryId;
 update Category set drawType = NULL where id = NEW.categoryId;
END^
SET TERM ;^