#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCKING_FACTOR 3
#define FILE_END "********"

#define FileSeek(File, Offset, Whence) _FileSeek(File, Offset, Whence)
void
_FileSeek(FILE* File, long Offset, int Whence)
{
  if(fseek(File, Offset, Whence))
    {
      printf("Greska prilikom pomeranja fajl kursora\n");
    }
}

typedef struct datetime_st {
  int Day;
  int Month;
  int Year;
  int Hour;
  int Minute;
} datetime;

typedef struct record_st {
  char ID[9];
  char InmateID[7+1];
  datetime DatetimeArrival;
  char CellID[6];
  int SentenceLength;
  int Deleted;
} record;

typedef struct block_st {
  record Records[BLOCKING_FACTOR];
} block;

void
PrintRecord(record* Record)
{
  printf("%8s  %7s  %02d-%02d-%4d %02d:%02d %7s %6d",
	 Record->ID,
	 Record->InmateID,
	 Record->DatetimeArrival.Day,
	 Record->DatetimeArrival.Month,
	 Record->DatetimeArrival.Year,
	 Record->DatetimeArrival.Hour,
	 Record->DatetimeArrival.Minute,
	 Record->CellID,
	 Record->SentenceLength);
}

void
PrintAllRecords(FILE* File)
{
  if(File)
    {
      FileSeek(File, 0, SEEK_SET);
      block Block = {};
      int BlockCount = 0;
      while(fread(&Block, sizeof(block), 1, File))
	{
	  for(int RecordIndex = 0;
	      RecordIndex < BLOCKING_FACTOR;
	      ++RecordIndex)
	    {
	      if(!strcmp(Block.Records[RecordIndex].ID, FILE_END))
		{
		  printf("B%d, S%d *\n", BlockCount, RecordIndex);
		  return;
		}
	      if(!Block.Records[RecordIndex].Deleted)
	      {
		printf("B%d S%d ", BlockCount, RecordIndex);
		PrintRecord(&Block.Records[RecordIndex]);
		printf("\n");
	      }
	    }
	  ++BlockCount;
	}
    }
  else
    {
      printf("File nije otvoren\n");
    }
}

FILE*
OpenFile(char* FileName)
{
  FILE* Result = 0;
  Result = fopen(FileName, "rb+");
  if(!Result)
    {
      printf("Greska prilikom otvaranja datoteke\n");
    }
  return Result;
}

FILE*
CreateFile(char* FileName)
{
  FILE* Result = 0;
  Result = fopen(FileName, "wb");
  if(!Result)
    {
      printf("Greska prilikom kreiranja datoteke\n");
    }
  return Result;
}

int
SearchRecords(FILE* File, char* ID, record* Record)
{
  int Result = 0;
  if(File)
    {
      FileSeek(File, 0, SEEK_SET);
      block Block = {};
      while(fread(&Block, sizeof(block), 1, File))
	{
	  for(int RecordIndex = 0;
	      RecordIndex < BLOCKING_FACTOR;
	      ++RecordIndex)
	    {
	      if(!strcmp(Block.Records[RecordIndex].ID, FILE_END))
		{
		  Result = 0;
		  return Result;
		}
	      if(!strcmp(Block.Records[RecordIndex].ID, ID) &&
		 !Block.Records[RecordIndex].Deleted)
		{
		  *Record = Block.Records[RecordIndex];
		  Result = 1;
		  return Result;
		}
	    }
	}
    }
  else
    {
      printf("Fajl nije otvoren\n");
    }
  return Result;
}

void
UpdateRecord(FILE* File, char* ID, char* NewCellID, int NewSentenceLength)
{
  if(File)
    {
      FileSeek(File, 0, SEEK_SET);
      block Block = {};
      while(fread(&Block, sizeof(block), 1, File))
	{
	  for(int RecordIndex = 0;
	      RecordIndex < BLOCKING_FACTOR;
	      ++RecordIndex)
	    {
	      if(!strcmp(Block.Records[RecordIndex].ID, FILE_END))
		{
		  printf("Zeljeni slog nije pronadjen\n");
		  return;
		}
	      if(!strcmp(Block.Records[RecordIndex].ID, ID) &&
		 !Block.Records[RecordIndex].Deleted)
		{
		  strcpy(Block.Records[RecordIndex].CellID, NewCellID);
		  Block.Records[RecordIndex].SentenceLength = NewSentenceLength;
		  FileSeek(File, -sizeof(block), SEEK_CUR);
		  fwrite(&Block, sizeof(block), 1, File);
		  printf("Slog izmenjen\n");
		  return; 
		}
	    }
	}
    }
  else
    {
      printf("Fajl nije otvoren\n");
    }
}

void
DeleteRecordSoft(FILE* File, char* ID)
{
  if(File)
    {
      FileSeek(File, 0, SEEK_SET);
      block Block = {};
      while(fread(&Block, sizeof(block), 1, File))
	{
	  for(int RecordIndex = 0;
	      RecordIndex < BLOCKING_FACTOR;
	      ++RecordIndex)
	    {
	      if(!strcmp(Block.Records[RecordIndex].ID, FILE_END))
		{
		  printf("Zeljeni slog nije nadjen\n");
		  return;
		}

	      if(!strcmp(Block.Records[RecordIndex].ID, ID) &&
		 !Block.Records[RecordIndex].Deleted)
		{
		  ++Block.Records[RecordIndex].Deleted;
		  FileSeek(File, -sizeof(block), SEEK_CUR);
		  fwrite(&Block, sizeof(block), 1, File);
		  printf("Slog logicki obrisan\n");
		  return;
		}
	    }
	}
    }
  else
    {
      printf("Fajl nije otvoren\n");
    }
}

void
DeleteRecordHard(FILE* File, char* ID)
{
  if(File)
    {
      block Block = {};
      block NextBlock = {};
      char IDToDelete[9] = {};
      strcpy(IDToDelete, ID);
      FileSeek(File, 0, SEEK_SET);
      while(fread(&Block, sizeof(block), 1, File))
	{
	  for(int i = 0;
	      i < BLOCKING_FACTOR;
	      ++i)
	    {
	      if(!strcmp(Block.Records[i].ID, FILE_END))
		{
		  if(i==0)
		    {
		      printf("Skracivanje fajla...\n");
		      FileSeek(File, -sizeof(block), SEEK_END);
		      long BytesToKeep = ftell(File);
		      ftruncate(fileno(File), BytesToKeep);
		      fflush(File);
		    }
		  printf("Slog je fizicki obrisan\n");
		  return;
		}
	      if(!strcmp(Block.Records[i].ID, IDToDelete))
		{
		  if(!strcmp(Block.Records[i].ID, ID) &&
		     Block.Records[i].Deleted)
		    {
		      continue;
		    }

		  for(int j = i + 1;
		      j < BLOCKING_FACTOR;
		      ++j)
		    {
		      memcpy(&(Block.Records[j-1]), &(Block.Records[j]), sizeof(record));
		    }

		  int BytesRead = fread(&NextBlock, sizeof(block), 1, File);
		  if(BytesRead)
		    {
		      FileSeek(File, -sizeof(block), SEEK_CUR);
		      memcpy(&(Block.Records[BLOCKING_FACTOR-1]), &NextBlock.Records[0], sizeof(record));
		      strcpy(IDToDelete, NextBlock.Records[0].ID);
		    }

		  FileSeek(File, -sizeof(block), SEEK_CUR);
		  fwrite(&Block, sizeof(block), 1, File);
		  FileSeek(File, 0, SEEK_CUR);

		  if(!BytesRead)
		    {
		      printf("Slog je fizicki obrisan\n");
		      return;
		    }
		  break;
		}
		
	    }
	}
    }
  else
    {
      printf("Fajl nije otvoren\n");
    }
}

int
Menu()
{
  int Result = 0;
  printf("Odaberite opciju:\n");
  printf("1 - Otvaranje datoteke\n");
  printf("2 - Formiranje datoteke\n");
  printf("3 - Pretraga datoteke\n");
  printf("4 - Unos sloga\n");
  printf("5 - Ispis svi slogova\n");
  printf("6 - Azuriranje sloga\n");
  printf("7 - Brisanje sloga (logicko)\n");
  printf("8 - Brisanje sloga (fiziko)\n");
  printf("9 - Reorgranizuj datoteku\n");
  printf("0 - Izlaz\n");
  scanf("%d", &Result);
  getc(stdin);
  return Result;
}

int
main()
{
  int Running = 1;
  FILE* File = 0;

  while(Running)
    {
      int Input = Menu();
      switch(Input)
	{
	case 1:
	  {
	    char FileName[20] = {};
	    printf("Unesite naziv datoteke: ");
	    scanf("%s", FileName);
	    File = OpenFile(FileName);
	  }break;
	case 2:
	  {
	    char FileName[20] = {};
	    printf("Unesite naziv datoteke: ");
	    scanf("%s", FileName);
	    File = CreateFile(FileName);
	  }break;
	case 3:
	  {
	    char ID[9] = {};
	    printf("Unesite Evid.Br: ");
	    scanf("%s", ID);
	    record Record = {};
	    if(SearchRecords(File, ID, &Record))
	      {
		printf("Evid.Br   Sif.Zat      Dat.Vrem.Dol  Celija  Kazna\n");
		PrintRecord(&Record);
	      }
	    else
	      {
		printf("Zeljeni slog nije nadjen\n");
	      }
	  }break;
	case 4:
	  {
	    record Record = {};
	    printf("Evid. br: ");
	    scanf("%s", Record.ID);
	    printf("Sifra zatvorenika: ");
	    scanf("%s", Record.InmateID);
	    printf("Datum i vreme dolaska (dd-mm-YYYY HH:mm): ");
	    scanf("%d-%d-%d %d:%d",
		  &Record.DatetimeArrival.Day,
		  &Record.DatetimeArrival.Month,
		  &Record.DatetimeArrival.Year,
		  &Record.DatetimeArrival.Hour,
		  &Record.DatetimeArrival.Minute);
	  }break;
	case 5:
	  {
	    PrintAllRecords(File);
	  }break;
	case 6:
	  {
	    char ID[9];
	    printf("Unesite Evid.br: ");
	    scanf("%s", ID);
	    char NewCellID[8] = {};
	    int NewSentenceLength;
	    printf("Unesite novu sifru celije: ");
	    scanf("%s", NewCellID);
	    printf("Unesite novu duzinu kazne: ");
	    scanf("%d", &NewSentenceLength);
	    UpdateRecord(File, ID, NewCellID, NewSentenceLength);
	  }break;
	case 7:
	  {
	    char ID[9] = {};
	    printf("Unesite Evid.br: ");
	    scanf("%s", ID);
	    DeleteRecordSoft(File, ID);
	  }break;
	case 8:
	  {
	    char ID[9] = {};
	    printf("Unesite Evid.br: ");
	    scanf("%s", ID);
	    DeleteRecordHard(File, ID);
	  }break;
	case 0:
	  {
	    Running = 0;
	  }break;
	}
    }
  if(File)
    {
      fclose(File);
    }
  return 0;
}
