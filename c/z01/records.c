#include "records.h"

int
SearchRecords(FILE* File, char* ID, record* Record)
{
  int Result = 0;
  if(File)
    {
      block Block = {};
      FileSeek(File, 0, SEEK_SET);
      while(fread(&Block, sizeof(block), 1, File))
	{
	  for(int SectorIndex = 0;
	      SectorIndex < BLOCKING_FACTOR;
	      ++SectorIndex)
	    {
	      if(!strcmp(Block.Sectors[SectorIndex].ID, FILE_END))
		{
		  Result = 0;
		  return Result;
		}
	      if(!strcmp(Block.Sectors[SectorIndex].ID, ID) &&
		 !Block.Sectors[SectorIndex].Deleted)
		{
		  *Record = Block.Sectors[SectorIndex];
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
PrintRecordHeader()
{
  printf("Evid.Br   Sif.Zat      Dat.Vrem.Dol  Celija  Kazna\n");
}

void
PrintRecord(record* Record, int HeaderTag)
{
  if(HeaderTag)
    {
      PrintRecordHeader();
    }
  printf("%8s  %7s  %02d-%02d-%4d %02d:%02d %7s %6d\n",
	 Record->ID,
	 Record->InmateID,
	 Record->InmateArrival.Day,
	 Record->InmateArrival.Month,
	 Record->InmateArrival.Year,
	 Record->InmateArrival.Hour,
	 Record->InmateArrival.Minute,
	 Record->CellID,
	 Record->SentenceLength);
}

void
PrintAllRecords(FILE* File)
{
  if(File)
    {
      block Block = {};
      int BlockCount = 0;
      FileSeek(File, 0, SEEK_SET);
      printf("B S  ");
      PrintRecordHeader();
      while(fread(&Block, sizeof(block), 1, File))
	{
	  for(int SectorIndex = 0;
	      SectorIndex < BLOCKING_FACTOR;
	      ++SectorIndex)
	    {
	      if(!strcmp(Block.Sectors[SectorIndex].ID, FILE_END))
		{
		  printf("B%d S%d  *\n", BlockCount, SectorIndex);
		  return;
		}
	      if(!Block.Sectors[SectorIndex].Deleted)
		{
		  printf("B%d S%d  ", BlockCount, SectorIndex);
		  PrintRecord(&Block.Sectors[SectorIndex], WITHOUT_HEADER);
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

int
InsertRecord(FILE* File, record* Record)
{
  int Result = 0;
  if(File)
    {
      block Block = {};
      record Tmp = {};
      int SectorIndex = 0;
      if(SearchRecords(File, Record->ID, &Tmp))
	{
	  printf("Vec postoji\n");
	  return Result;
	}
      FileSeek(File, -sizeof(block), SEEK_END);
      fread(&Block, sizeof(block), 1, File);
      for(SectorIndex = 0;
	  SectorIndex < BLOCKING_FACTOR;
	  ++SectorIndex)
	{
	  if(!strcmp(Block.Sectors[SectorIndex].ID, FILE_END))
	    {
	      Block.Sectors[SectorIndex] = *Record;
	      break;
	    }
	}
      ++SectorIndex;
      if(SectorIndex < BLOCKING_FACTOR)
	{
	  strcpy(Block.Sectors[SectorIndex].ID, FILE_END);
	  FileSeek(File, -sizeof(block), SEEK_CUR);
	  fwrite(&Block, sizeof(block), 1, File);
	}
      else
	{
	  block NewBlock = {};
	  FileSeek(File, -sizeof(block), SEEK_CUR);
	  fwrite(&Block, sizeof(block), 1, File);
	  strcpy(NewBlock.Sectors[0].ID, FILE_END);
	  fwrite(&NewBlock, sizeof(block), 1, File);
	}
      Result = 1;
    }
  else
    {
      printf("Fajl nije otvoren\n");
    }

  return Result;
}

int
UpdateRecord(FILE* File, char* ID, char* NewCellID, int NewSentenceLength)
{
  int Result = 0;
  if(File)
    {
      block Block = {};
      FileSeek(File, 0, SEEK_SET);
      while(fread(&Block, sizeof(block), 1, File))
	{
	  for(int SectorIndex = 0;
	      SectorIndex < BLOCKING_FACTOR;
	      ++SectorIndex)
	    {
	      record* Curr = &Block.Sectors[SectorIndex];
	      if(!strcmp(Curr->ID, FILE_END))
		{
		  Result = 0;
		  printf("Ne postoji\n");
		  return Result;
		}
	      if(!strcmp(Curr->ID, ID) && !Curr->Deleted)
		{
		  strcpy(Curr->CellID, NewCellID);
		  Curr->SentenceLength = NewSentenceLength;
		  FileSeek(File, -sizeof(block), SEEK_CUR);
		  fwrite(&Block, sizeof(block), 1, File);
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

int
DeleteRecordSoft(FILE* File, char* ID)
{
  int Result = 0;
  if(File)
    {
      block Block = {};
      FileSeek(File, 0, SEEK_SET);
      while(fread(&Block, sizeof(block), 1, File))
	{
	  for(int SectorIndex = 0;
	      SectorIndex < BLOCKING_FACTOR;
	      ++SectorIndex)
	    {
	      record* Curr = &Block.Sectors[SectorIndex];
	      if(!strcmp(Curr->ID, FILE_END))
		{
		  Result = 0;
		  printf("Nije pronadjen\n");
		  return Result;
		}
	      if(!strcmp(Curr->ID, ID) && !Curr->Deleted)
		{
		  ++Curr->Deleted;
		  Result = 1;
		  FileSeek(File, -sizeof(block), SEEK_CUR);
		  fwrite(&Block, sizeof(block), 1, File);
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
	  for(int SectorIndex = 0;
	      SectorIndex < BLOCKING_FACTOR;
	      ++SectorIndex)
	    {
	      int BytesRead = 0;
	      record* Curr = &Block.Sectors[SectorIndex];
	      if(!strcmp(Curr->ID, FILE_END))
		{
		  if(SectorIndex == 0)
		    {
		      int Keeping = 0;
		      printf("Skracivanje fajla...\n");
		      FileSeek(File, -sizeof(block), SEEK_END);
		      Keeping = ftell(File);
		      ftruncate(fileno(File), Keeping);
		      fflush(File);
		    }
		  printf("Obrisano\n");
		  return;
		}
	      if(!strcmp(Curr->ID, IDToDelete))
		{
		  if(!strcmp(Curr->ID, ID) && Curr->Deleted)
		    {
		      continue;
		    }
		  for(int i = SectorIndex + 1;
		      i < BLOCKING_FACTOR;
		      ++i)
		    {
		      Block.Sectors[i-1] = Block.Sectors[i];
		    }
		  BytesRead = fread(&NextBlock, sizeof(block), 1, File);
		  if(BytesRead)
		    {
		      FileSeek(File, -sizeof(block), SEEK_CUR);
		      Block.Sectors[BLOCKING_FACTOR-1] = NextBlock.Sectors[0];
		      strcpy(IDToDelete, NextBlock.Sectors[0].ID);
		    }
		  FileSeek(File, -sizeof(block), SEEK_CUR);
		  fwrite(&Block, sizeof(block), 1, File);
		  if(!BytesRead)
		    {
		      printf("Obrisano\n");
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
