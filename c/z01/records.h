typedef struct datetime_st
{
  int Day;
  int Month;
  int Year;
  int Hour;
  int Minute;
}datetime;

typedef struct record_st
{
  char ID[9];
  char InmateID[8];
  datetime InmateArrival;
  char CellID[6];
  int SentenceLength;
  int Deleted;
}record;

typedef struct block_st
{
  record Sectors[BLOCKING_FACTOR];
}block;

int
SearchRecords(FILE* File, char* ID, record* Record);
void
PrintRecordHeader();
void
PrintRecord(record* Record, int HeaderFlag);
void
PrintAllRecords(FILE* file);
int
InsertRecord(FILE* File, record* Record);
int
UpdateRecord(FILE* File, char* ID, char* NewCellID, int NewSentenceLength);
int
DeleteRecordSoft(FILE* File, char* ID);
void
DeleteRecordHard(FILE* File, char* ID);
