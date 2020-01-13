#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCKING_FACTOR 3
#define FILE_END "********"

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
  char CellId[6];
  int SentenceLength;
  int Deleted;
  datetime CheckInDate;
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

  return Result;
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
SearchRecord(FILE* File, record* Record)
{
  int Result = 0;
  char ID[9];
  printf("Unesite evid. broj: ");
  scanf("%s", ID);

  if(File)
    {
      fseek(File, 0, SEEK_SET);
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
		  break;
		}
	      if(!strcmp(Block.Records[i].Id, ID) &&
		 !Block.Records[i].Deleted)
		{
		  *Record = Block.Records[i];
		  Result = 1;
		  break;
		}
	    }
	}
    }
  
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
	  }
	case 2:
	  {
	    File = CreateFile();
	  }
	case 3:
	  {
	    record Record = {};
	    if(SearchRecord(File, &Record))
	      {
		printf("Evid. broj (8 cifara): ");
		PrintRecord(&Record);
	      }
	    else
	      {
		printf("Nema tog sloga u datoteci\n");
	      }
	  }
	case 4:
	  {
	    // TODO(Jovan): Implement
	  }
	case 5:
	  {
	    // TODO(Jovan): Implement
	  }
	case 6:
	  {
	    // TODO(Jovan): Implement
	  }
	case 7:
	  {
	    // TODO(Jovan): Implement
	  }
	case 8:
	  {
	    // TODO(Jovan): Implement
	  }
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

