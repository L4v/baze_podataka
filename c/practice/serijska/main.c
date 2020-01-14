#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>

#define BLOCKING_FACTOR 3
#define FILE_END "********"

#define FileSeek(File, Offset, Whence) _FileSeek(File, Offset, Whence)
void
_FileSeek(FILE* File, long Offset, int Whence)
{
  if(fseek(File, Offset, Whence))
    {
      printf("Greska prilikom pomeranja kursora\n");
    }
}

typedef struct datetime_st
{
  int Day;
  int Month;
  int Year;
  int Hour;
  int Minute;
} datetime;

typedef struct record_st
{
  char Id[9];
  char InmateId[8];
  datetime CheckInDate;
  char CellId[6];
  int SentenceLength;
  int Deleted;
} record;

typedef struct block_st
{
  record Records[BLOCKING_FACTOR];
} block;

void
PrintRecord(record* Record)
{
  printf("%8s  %7s  %02d-%02d-%4d %02d:%02d %7s %6d\n",
  	 Record->Id,
  	 Record->InmateId,
  	 Record->CheckInDate.Day,
  	 Record->CheckInDate.Month,
  	 Record->CheckInDate.Year,
  	 Record->CheckInDate.Hour,
  	 Record->CheckInDate.Minute,
  	 Record->CellId,
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
      printf("BL SL Evid.Br   Sif.Zat      Dat.Vrem.Dol  Celija  Kazna\n");
      while(fread(&Block, sizeof(block), 1, File))
	{
	  for(int i = 0;
	      i < BLOCKING_FACTOR;
	      ++i)
	    {
	      if(!strcmp(Block.Records[i].Id, FILE_END))
		{
		  printf("B%d S%d *\n", BlockCount, i);
		  break;
		}

	      if(!Block.Records[i].Deleted)
		{
		  printf("B%d S%d ", BlockCount, i);
		  PrintRecord(&Block.Records[i]);
		}
	    }
	  ++BlockCount; 
	}
    }
  else
    {
      printf("Fajl nije otvoren\n");
    }
}

FILE*
OpenFile()
{
  FILE* Result = 0;
  char FileName[20] = {};
  printf("Unesite naziv datoteke: ");
  scanf("%s", FileName);
  Result = fopen(FileName, "rb+");
  if(!Result)
    {
      printf("Doslo je do greske prilikom otvaranja %s\n", FileName);
    }
  else
    {
      printf("Uspesno otvorena\n");
    }
  return Result;
}

FILE*
CreateFile()
{
  FILE* Result = 0;
  char FileName[20] = {};
  printf("Unesite naziv zeljene datoteke: ");
  scanf("%s", FileName);
  Result = fopen(FileName, "wb");
  if(!Result)
    {
      printf("Doslo je do greske prilikom kreiranja %s\n", FileName);
    }
  else
    {
      printf("%s uspesno kreirana\n", FileName);
    }
  return Result;
}

int
SearchRecord(FILE* File, record* Record, char* ID)
{
  int Result = 0;
  
  if(File)
    {
      FileSeek(File, 0, SEEK_SET);
      block Block = {};
      while(fread(&Block, sizeof(block), 1, File))
	{
	  for(int i = 0;
	      i < BLOCKING_FACTOR;
	      ++i)
	    {
	      if(!strcmp(Block.Records[i].Id, FILE_END))
		{
		  Result = 0;
		  return Result;
		}
	      if(!strcmp(Block.Records[i].Id, ID) &&
		 !Block.Records[i].Deleted)
		{
		  *Record = Block.Records[i];
		  Result = 1;
		  return Result;
		}
	    }
	}
    }
  
  return Result;
}

void
UpdateRecord(FILE* File, char* ID, char* NewCellId, int NewSentenceLength)
{
  if(File)
    {
      FileSeek(File, 0, SEEK_SET);
      block Block = {};
      while(fread(&Block, sizeof(block), 1, File))
	{
	  for(int i = 0;
	      i < BLOCKING_FACTOR;
	      ++i)
	    {
	      if(!strcmp(Block.Records[i].Id, FILE_END))
		{
		  printf("Slog koji zelite menjati ne postoji\n");
		  return;
		}
	      if(!strcmp(Block.Records[i].Id, ID) &&
		 !Block.Records[i].Deleted)
		{
		  strcpy(Block.Records[i].CellId, NewCellId);
		  Block.Records[i].SentenceLength = NewSentenceLength;
		  FileSeek(File, -sizeof(block), SEEK_CUR);
		  fwrite(&Block, sizeof(block), 1, File);
		  printf("Azuriranje uspesno\n");
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
	  for(int i = 0;
	      i < BLOCKING_FACTOR;
	      ++i)
	    {
	      if(!strcmp(Block.Records[i].Id, FILE_END))
		{
		  printf("Slog koji zelite logicki obrisati nije pronadjen\n");
		  return;
		}
	      if(!strcmp(Block.Records[i].Id, ID) && !Block.Records[i].Deleted)
		{
		  ++Block.Records[i].Deleted;
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
      record Record = {};
      if(!SearchRecord(File, &Record, ID))
	{
	  printf("Slog koji zelite obrisati ne postoji\n");
	  return;
	}
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
	      // NOTE(Jovan): Provera kraja
	      if(!strcmp(Block.Records[i].Id, FILE_END))
		{
		  if(i == 0)
		    {
		      printf("Skracujem fajl...\n");
		      fseek(File, -sizeof(block), SEEK_END);
		      long BytesToKeep = ftell(File);
		      ftruncate(fileno(File), BytesToKeep);
		      fflush(File);
		    }
		  printf("Slog je fizicki obrisan\n");
		  return;
		}

	      // NOTE(Jovan): Provera da li je pronadjen slog
	      if(!strcmp(Block.Records[i].Id, IDToDelete))
		{
		  if(!strcmp(Block.Records[i].Id, ID) &&
		     Block.Records[i].Deleted)
		    {
		      // NOTE(Jovan): Logicki je obrisan, njega ne diramo
		      continue;
		    }

		  // NOTE(Jovan): Brisemo slog i pomeramo sve ispred njega za jedno mesto
		  for(int j = i + 1;
		      j < BLOCKING_FACTOR;
		      ++j)
		    {
		      memcpy(&(Block.Records[j-1]), &(Block.Records[j]), sizeof(record));
		    }

		  // NOTE(Jovan): Upisujemo na poslednju poziciju blocka prvi slog narednog bloka
		  int BytesRead = fread(&NextBlock, sizeof(block), 1, File);
		  if(BytesRead)
		    {
		      fseek(File, -sizeof(block), SEEK_CUR);
		      memcpy(&(Block.Records[BLOCKING_FACTOR-1]), &(NextBlock.Records[0]), sizeof(record));
		      strcpy(IDToDelete, NextBlock.Records[0].Id);
		    }
		  fseek(File, -sizeof(block), SEEK_CUR);
		  fwrite(&Block, sizeof(block), 1, File);
		  fseek(File, 0, SEEK_CUR);

		  // NOTE(Jovan): Svi su pomereni
		  if(!BytesRead)
		    {
		      printf("Slog je fizicki obrisan\n");
		      return;
		    }

		  // NOTE(Jovan): Uradili smo ono sto treba u bloku, moze se terminirati for
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
      Running = Menu();
      switch(Running)
	{
	case 1:
	  {
	    File = OpenFile();
	  }break;
	case 2:
	  {
	    File = CreateFile();
	  }break;
	case 3:
	  {
	    record Record = {};
	    char ID[9];
	    printf("Unesite evid. broj: ");
	    scanf("%s", ID);
	    if(SearchRecord(File, &Record, ID))
	      {
		printf("Evid.Br   Sif.Zat      Dat.Vrem.Dol  Celija  Kazna\n");
		PrintRecord(&Record);
	      }
	    else
	      {
		printf("Nema tog sloga u datoteci\n");
	      }
	  }break;
	case 4:
	  {
	    record Record = {};
	    printf("Unesite Evid.Br: ");
	    scanf("%s", Record.Id);
	    printf("Unesite Sifr.Zat: ");
	    scanf("%s", Record.InmateId);
	    printf("Unesite Celiju: ");
	    scanf("%s", Record.CellId);
	    printf("Unesite duzinu kazne: ");
	    scanf("%d", &Record.SentenceLength);
	    Record.Deleted = 0;
	    printf("Datum i vreme dolaska (dd-mm-YYYY HH:mm): ");
	    scanf("%d-%d-%d %d:%d",
		  &Record.CheckInDate.Day,
		  &Record.CheckInDate.Month,
		  &Record.CheckInDate.Year,
		  &Record.CheckInDate.Hour,
		  &Record.CheckInDate.Minute);
	  }break;
	case 5:
	  {
	    PrintAllRecords(File);
	  }break;
	case 6:
	  {
	    char ID[9] = {};
	    printf("Unesite Evid.Br sloga za azuriranje: ");
	    scanf("%s", ID);
	    char CellId[6] = {};
	    printf("Unesite novu oznaku celije: ");
	    scanf("%s", CellId);
	    int SentenceLength;
	    printf("Unesite novu duzinu kazne: ");
	    scanf("%d", &SentenceLength);
	    UpdateRecord(File, ID, CellId, SentenceLength);
	  }break;
	case 7:
	  {
	    char ID[9] = {};
	    printf("Unesite Evid.Br: ");
	    scanf("%s", ID);
	    DeleteRecordSoft(File, ID);
	  }break;
	case 8:
	  {
	    char ID[9] = {};
	    printf("Unesite Evid.Br: ");
	    scanf("%s", ID);
	    DeleteRecordHard(File, ID);
	  }break;
	case 0:
	  {
	    break;
	  }
	default:
	  {
	    printf("Unesite validan validnu opciju\n");
	  }
	}
    }
  if(File)
    {
      fclose(File);
    }
  return 0;
}

