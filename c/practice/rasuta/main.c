#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define DEFAULT_FILENAME "in.dat"
#define DEFAULT_INFILENAME "in.dat"
#define DEFAULT_FILENANAME "test.dat"
#define OVERFLOW_FILE_NAME "overflow.dat"

#define B 7             
#define STEP 1          
#define BUCKET_SIZE 3   

#define WITH_HEADER 1
#define WITHOUT_HEADER 0
#define WITH_KEY 1
#define WITHOUT_KEY 0

#define RECORD_FOUND 0

#define CODE_LEN 8
#define DATE_LEN 11

typedef enum
  {
   EMPTY = 0,
   ACTIVE,
   DELETED
  } record_status;

typedef struct record_st
{
  int Key;
  char Code[CODE_LEN];
  char Date[DATE_LEN];
  record_status Status;
} record;

typedef struct bucket_st
{
  record Records[BUCKET_SIZE];
} bucket;

typedef struct find_record_result_st
{
  int Ind1;
  int Ind2;
  bucket Bucket;
  record Record;
  int BucketIndex;
  int RecordIndex;
} find_record_result;

#define FileSeek(File, Offset, Whence) _FileSeek((File), (Offset), (Whence))
void
_FileSeek(FILE* File, long Offset, int Whence)
{
  if(fseek(File, Offset, Whence))
    {
      printf("Greska prilikom pomeranja fajl kursora\n");
    }
}

FILE*
OpenFile(char* FileName)
{
  FILE* Result = 0;
  Result = fopen(FileName, "rb+");
  if(!Result)
    {
      Result = fopen(FileName, "wb+");
      CreateHashFile(Result);
      printf("Kreirana prazna datoteka");
    }
  else
    {
      printf("Otvorena postojeca datoteka\n");
    }
  if(!Result)
    {
      printf("Greska prilikom otvaranja datoteke\n");
    }
  return Result;
}

record
ScanRecord(int WithKey)
{
  record Result = {};
  if(WithKey)
    {
      printf("Key = ");
      scanf("%d", &Result.Key);
    }

  printf("Code = ");
  scanf("%s", Result.Code);
  printf("Date = ");
  scanf("%s", Result.Date);
  
  return Result;
}

static inline int
TransformKey(int ID)
{
  return ID % B;
}

int
ReadBucket(FILE* File, bucket* Bucket, int BucketIndex)
{
  FileSeek(File, BucketIndex * sizeof(bucket), SEEK_SET);
  return fread(Bucket, sizeof(bucket), 1, File) == 1;
}

int
NextBucketIndex(int BucketIndex)
{
  return (BucketIndex + STEP) % B;
}

find_record_result
FindRecord(FILE* File, int Key)
{
  find_record_result Result = {};
  int BucketIndex = TransformKey(Key);
  int InitialIndex = BucketIndex;
  bucket Bucket = {};
  Result.Ind1 = 99;
  Result.Ind2 = 0;

  while(Result.Ind1 == 99)
    {
      int RecordIndex = 0;
      ReadBucket(File, &Bucket, BucketIndex);
      Result.Bucket = Bucket;
      Result.BucketIndex = BucketIndex;
      while(RecordIndex < BUCKET_SIZE && Result.Ind1 == 99)
	{
	  record Record = Bucket.Records[RecordIndex];
	  Result.Record = Record;
	  Result.RecordIndex = RecordIndex;
	  if(Key == Record.Key && Record.Status != EMPTY)
	    {
	      Result.Ind1 = 0;
	    }
	  else if(Record.Status == EMPTY)
	    {
	      Result.Ind1 = 1;
	    }
	  else
	    {
	      ++RecordIndex;
	    }
	}

      if(RecordIndex >= BUCKET_SIZE)
	{
	  BucketIndex = NextBucketIndex(BucketIndex);

	  if(BucketIndex == InitialIndex)
	    {
	      Result.Ind1 = 1;
	      Result.Ind2 = 1;
	    }
	}
    }
  return Result;
}

int
ExistsForInsert(find_record_result FindResult)
{
  if(FindResult.Ind1 == 0)
    {
#ifdef LOGICAL
      if(FindResult.Record.Status == ACTIVE)
	{
	  return 1;
	}
#else
      return 1;
#endif
    }

  return 0;
}

int
ExistsForModify(find_record_result FindResult)
{
  if(FindResult.Ind1)
    {
      return 0;
    }
#ifdef LOGICAL
  if(FindResult.Record.Status == DELETED)
    {
      return 0;
    }
#endif
  return 1;
}

int
SaveBucket(FILE* File, bucket* Bucket, int BucketIndex)
{
  int Result = 0;
  FileSeek(File, BucketIndex * sizeof(bucket), SEEK_SET);
  Result = fwrite(Bucket, sizeof(bucket), 1, File) == 1;
  return Result;
}

int
InsertRecord(FILE* File, record Record)
{
  Record.Status = ACTIVE;
  find_record_result FindResult = FindRecord(File, Record.Key);
  if(File)
    {
      if(ExistsForInsert(FindResult))
	{
	  return -1;
	}
      FindResult.Bucket.Records[FindResult.RecordIndex] = Record;
      if(SaveBucket(File, &FindResult.Bucket, FindResult.BucketIndex))
	{
	  return FindResult.BucketIndex; 
	}
      else
	{
	  return -2;
	}
    }
  else
    {
      printf("Fajl nije otvoren\n");
    }

  return -2;
}

void
HandleResult(int ReturnCode)
{
  if(ReturnCode < 0)
    {
      printf("Operacija neuspesna\n");
    }
  else
    {
      printf("Operacija uspesna\n");
    }
}

int
ScanKey()
{
  int Result = 0;
  printf("Key = ");
  scanf("%d", &Result);
  return Result;
}

void
PrintRecord(record Record, int Header)
{
  if(Header)
    {
      printf("status \t key \t code \t date\n");
    }
  printf("%d \t %d \t %s \t %s\n",
	 Record.Status,
	 Record.Key,
	 Record.Code,
	 Record.Date);
}

int
ModifyRecord(FILE* File, record Record)
{
  Record.Status = ACTIVE;
  find_record_result FindResult = FindRecord(File, Record.Key);
  if(!ExistsForModify(FindResult))
    {
      return -1;
    }
  FindResult.Bucket.Records[FindResult.RecordIndex] = Record;
  if(SaveBucket(File, &FindResult.Bucket, FindResult.BucketIndex))
    {
      return FindResult.BucketIndex;
    }
  else
    {
      return -2;
    }
}

int
RemoveRecordSoft(FILE* File, int Key)
{
  find_record_result FindResult = FindRecord(File, Key);
  if(FindResult.Ind1)
    {
      return -1;
    }
  FindResult.Bucket.Records[FindResult.RecordIndex].Status = DELETED;
  if(SaveBucket(File, &FindResult.Bucket, FindResult.BucketIndex))
    {
      return FindResult.BucketIndex;
    }
  else
    {
      return -2;
    }
}

void
TestCandidate(record Record, int BucketIndex, int TargetBucketIndex, int* Found)
{
  int M = TransformKey(Record.Key);
  if(BucketIndex > TargetBucketIndex)
    {
      if(M > BucketIndex || M <= TargetBucketIndex)
	{
	  *Found = 1;
	}
    }
  else
    {
      if(M > BucketIndex && M <= TargetBucketIndex)
	{
	  *Found = 1;
	}
    }
}

int
RemoveRecordHard(FILE* File, int Key)
{
  find_record_result FindResult = FindRecord(File, Key);
  if(FindResult.Ind1)
    {
      return -1;
    }
  int RecordIndex = FindResult.RecordIndex;
  bucket Bucket = FindResult.Bucket;
  int BucketIndex = FindResult.BucketIndex;
  int Moving = 1;
  while(Moving)
    {
      while(RecordIndex < BUCKET_SIZE -1 &&
	    Bucket.Records[RecordIndex].Status != EMPTY)
	{
	  Bucket.Records[RecordIndex] = Bucket.Records[RecordIndex + 1];
	  ++RecordIndex;
	}
      bucket TargetBucket = Bucket;
      int TargetBucketIndex = BucketIndex;

      if(Bucket.Records[RecordIndex].Status == EMPTY)
	{
	  Moving = 0;
	}
      else
	{
	  int Found = 0;
	  while(!Found && Moving)
	    {
	      if(RecordIndex == BUCKET_SIZE - 1)
		{
		  BucketIndex = NextBucketIndex(BucketIndex);
		  ReadBucket(File, &Bucket, BucketIndex);
		  RecordIndex = -1;
		}
	      ++RecordIndex;
	      if(Bucket.Records[RecordIndex].Status != EMPTY &&
		 BucketIndex != TargetBucketIndex)
		{
		  TestCandidate(Bucket.Records[RecordIndex], BucketIndex,
				TargetBucketIndex, &Found);
		}
	      else
		{
		  Moving = 0;
		}
	    }
	  if(Found)
	    {
	      TargetBucket.Records[BUCKET_SIZE - 1] = Bucket.Records[RecordIndex];
	    }
	  else
	    {
	      TargetBucket.Records[BUCKET_SIZE - 1].Status = EMPTY;
	    }
	}
      SaveBucket(File, &TargetBucket, TargetBucketIndex);
    }
  return 0;
}

int
RemoveRecord(FILE* File, int Key)
{
#ifdef LOGICAL
  return RemoveRecordSoft(File, Key);
#else
  return RemoveRecordHard(File, Key);
#endif
}

void
PrintBucket(bucket Bucket)
{
  printf("status \t key \t code \t date\n");
  for(int RecordIndex = 0;
      RecordIndex < BUCKET_SIZE;
      ++RecordIndex)
    {
      PrintRecord(Bucket.Records[RecordIndex], WITHOUT_HEADER);
    }

}

void
PrintAllRecords(FILE* File)
{
  bucket Bucket = {};
  for(int BucketIndex = 0;
      BucketIndex < B;
      ++BucketIndex)
    {
      ReadBucket(File, &Bucket, BucketIndex);
      printf("\n####### BUCKET - %d #######\n", BucketIndex);
      PrintBucket(Bucket);
    }
}

void
FromTxtToSerialFile(FILE* Input, FILE* Output)
{
  record Record = {};
  while(fscanf(Input, "%d%s%s", &Record.Key, Record.Code, Record.Date) != EOF)
    {
      fwrite(&Record, sizeof(record), 1, Output);
    }
}

int
CreateHashFile(FILE* File)
{
  int Result = 0;
  bucket *EmptyContent = calloc(B, sizeof(bucket));
  FileSeek(File, 0, SEEK_SET);
  Result = fwrite(EmptyContent, sizeof(bucket), B, File);
  free(EmptyContent);
  return Result;
}

int
IsBucketFull(bucket Bucket)
{
  int Result = 0;
  Result = Bucket.Records[BUCKET_SIZE - 1].Status != EMPTY;
  return Result;
}

int
SaveRecordToOverflow(FILE* File, record* Record)
{
  return fwrite(Record, sizeof(record), 1, File);
}

int
ReadRecordFromSerial(FILE* File, record* Record)
{
  return fread(Record, sizeof(record), 1, File);
}

int
InitHashFile(FILE* File, FILE*Input)
{
  if(feof(File))
    {
      CreateHashFile(File);
    }

  FILE* OverflowFile = fopen(OVERFLOW_FILE_NAME, "wb+");
  record Record = {};
  while(ReadRecordFromSerial(Input, &Record))
    {
      int H = TransformKey(Record.Key);
      bucket Bucket = {};
      ReadBucket(File, &Bucket, H);
      if(IsBucketFull(Bucket))
	{
	  SaveRecordToOverflow(OverflowFile, &Record);
	}
      else
	{
	  InsertRecord(File, Record);
	}
    }
  fclose(Input);
  FileSeek(OverflowFile, 0, SEEK_SET);
  while(ReadRecordFromSerial(OverflowFile, &Record))
    {
      InsertRecord(File, Record);
    }
  fclose(OverflowFile);
  remove(OVERFLOW_FILE_NAME);

  return 0;
}

int
Menu()
{
  int Result = 0;
  
  printf("\n\nIzaberite opciju:\n");
  printf("\t1. Otvaranje datoteke\n");
  printf("\t2. Unos novog sloga\n");
  printf("\t3. Modifikacija sloga\n");
  printf("\t4. Brisanje sloga\n");
  printf("\t5. Trazenje sloga\n");
  printf("\t6. Prikaz sadrzaja datoteke\n");
  printf("\t7. Formiranje u dva prolaza\n");
  printf("\t0. Kraj programa\n");
  scanf("%d", &Result);
  return Result;
}

int main()
{
  int Running = 1;
  FILE* File = OpenFile(DEFAULT_FILENAME);
  while(Running)
    {
      int Input = Menu();
      switch(Input)
	{
	case 1:
	  {
	    if(File)
	      {
		fclose(File);
	      }
	    char FileName[20] = {};
	    printf("Unesite naziv datoteke: ");
	    scanf("%s", FileName);
	    File = OpenFile(FileName);
	  }break;
	case 2:
	  {
	    record Record = ScanRecord(WITH_KEY);
	    HandleResult(InsertRecord(File, Record));
	  }break;
	case 3:
	  {
	    int Key = ScanKey();
	    find_record_result FindResult = FindRecord(File, Key);
	    record Record = {};

	    if(FindResult.Ind1 != RECORD_FOUND ||
	       FindResult.Record.Status != ACTIVE)
	      {
		printf("Neuspesno trazenje\n");
	      }
	    else
	      {
		PrintRecord(FindResult.Record, WITH_HEADER);
		Record  = ScanRecord(WITHOUT_KEY);
		Record.Key = Key;
		HandleResult(ModifyRecord(File, Record));
	      }
	  }break;
	case 4:
	  {
	    int Key = ScanKey();
	    HandleResult(RemoveRecord(File, Key));
	  }break;
	case 5:
	  {
	    int Key = ScanKey();
	    find_record_result FindResult = FindRecord(File, Key);
	    if(FindResult.Ind1 != RECORD_FOUND)
	      {
		printf("Neuspesno trazenje\n");
	      }
	    else
	      {
		PrintRecord(FindResult.Record, WITH_HEADER);
	      }
	  }break;
	case 6:
	  {
	    PrintAllRecords(File);
	  }break;
	case 7:
	  {
	    FILE* InputTxtFile = fopen("in.txt", "r");
	    FILE* InputSerialFile = fopen(DEFAULT_INFILENAME, "wb+");
	    FromTxtToSerialFile(InputTxtFile, InputSerialFile);
	    InitHashFile(File, InputSerialFile);
	    fclose(InputSerialFile);
	    remove(DEFAULT_INFILENAME);
	  }break;
	case 0:
	  {
	    Running = 0;
	  }break;
	default:
	  break;
	}
    }
  if(File)
    {
      fclose(File);
    }
  return 0;
}
