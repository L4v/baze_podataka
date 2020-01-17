#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCKING_FACTOR 3
#define FILE_END "********"
#define WITH_HEADER 1
#define WITHOUT_HEADER 0


#define FileSeek(File, Offset, Whence) _FileSeek(File, Offset, Whence)
void
_FileSeek(FILE* File, long Offset, int Whence)
{
  if(fseek(File, Offset, Whence))
    {
      printf("Greska prilikom pomeranja kursora\n");
    }
}

#include "records.c"

FILE*
CreateFile(char* FileName)
{
  FILE* Result = 0;
  Result = fopen(FileName, "wb+");
  if(!Result)
    {
      printf("Greska prilikom kreiranja fajla\n");
    }
  else
    {
      printf("Uspesno kreiran fajl\n");
    }
  return Result;
}

FILE*
OpenFile(char* FileName)
{
  FILE* Result = 0;
  Result = fopen(FileName, "rb+");
  if(!Result)
    {
      Result = CreateFile(FileName);
    }
  else
    {
      printf("Otvoren fajl\n");
    }
  return Result;
}

int Menu()
{
  int Result = 0;
  printf("\tUnesite opciju: \n");
  printf("\t1. Otvori datoteku\n");
  printf("\t2. Pretrazi datoteku\n");
  printf("\t3. Unos podatka\n");
  printf("\t4. Kreiraj datoteku\n");
  printf("\t5. Ispis svih\n");
  printf("\t6. Azuriranje\n");
  printf("\t7. Logicko brisanje\n");
  printf("\t8. Fizicko brisanje\n");
  printf("\t0. Izadji\n");
  scanf("%d", &Result);
  getc(stdin);
  return Result;
}

int main()
{
  FILE* File = 0;
  int Result = -1;
  do
    {
      if(!File)
	{
	  printf("Fajl nije otvoren\n");
	}
      Result = Menu();
      switch(Result)
	{
	case 1:
	  {
	    char FileName[20];
	    printf("Unesite naziv fajla: ");
	    scanf("%s", FileName);
	    File = OpenFile(FileName);
	  }break;
	case 2:
	  {
	    record Record = {};
	    char ID[9] = {};
	    printf("Unesite ID: ");
	    scanf("%s", ID);
	    if(SearchRecords(File, ID, &Record))
	      {
		PrintRecord(&Record, WITH_HEADER);
	      }
	    else
	      {
		printf("Zatvorenik nije pronadjen\n");
	      }
	  }break;
	case 3:
	  {
	    record Record = {};
	    printf("Unesite Evid.br: ");
	    scanf("%s", Record.ID);
	    printf("Unesite Sifr.zat: ");
	    scanf("%s", Record.InmateID);
	    printf("Unesite datum primanja (dd-dd-yyyy hh:mm): ");
	    scanf("%d-%d-%d %d:%d",
		  &Record.InmateArrival.Day,
		  &Record.InmateArrival.Month,
		  &Record.InmateArrival.Year,
		  &Record.InmateArrival.Hour,
		  &Record.InmateArrival.Minute);
	    printf("Unesite Sifr.celije: ");
	    scanf("%s", Record.CellID);
	    printf("Unesite duzinu kazne (do 480 meseci): ");
	    scanf("%d", &Record.SentenceLength);
	    if(Record.SentenceLength > 480)
	      {
		printf("Kazna predugacka\n");
		break;
	      }
	    Record.Deleted = 0;
	    if(InsertRecord(File, &Record))
	      {
		printf("Uspesno uneseno\n");
	      }
	    else
	      {
		printf("Neuspelo\n");
	      }
	  }break;
	case 4:
	  {
	    char FileName[20] = {};
	    printf("Unesite naziv fajla: ");
	    scanf("%s", FileName);
	    File = CreateFile(FileName);
	  }break;
	case 5:
	  {
	    PrintAllRecords(File);
	  }break;
	case 6:
	  {
	    char ID[9] = {};
	    char NewCellID[6] = {};
	    int NewSentenceLength;
	    printf("Unesite Evid.br: ");
	    scanf("%s", ID);
	    printf("Unesite novu Sifr.Celije: ");
	    scanf("%s", NewCellID);
	    printf("Unesite novu duzinu kazne: ");
	    scanf("%d", &NewSentenceLength);
	    if(UpdateRecord(File, ID, NewCellID, NewSentenceLength))
	      {
		printf("Uspesno izmenjeno\n");
	      }
	    else
	      {
		printf("Neuspelo\n");
	      }
	  }break;
	case 7:
	  {
	    char ID[9] = {};
	    printf("Unesite Evid.br: ");
	    scanf("%s", ID);
	    if(DeleteRecordSoft(File, ID))
	      {
		printf("Uspesno obrisan\n");
	      }
	    else
	      {
		printf("Neuspelo\n");
	      }
	  }break;
	case 8:
	  {
	    char ID[9] = {};
	    printf("Unesite Evid.br: ");
	    scanf("%s", ID);
	    DeleteRecordHard(File, ID);
	  }break;
	case 0:
	default:
	  {
	    
	  }break;
	}
    }while(Result);
  if(File)
    {
      fclose(File);
    }
  return 0;
}
