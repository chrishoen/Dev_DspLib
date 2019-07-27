/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <stdarg.h>
#include <ctype.h>

#include "risAlphaDir.h"

#include "dspTextFile.h"


namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Log file writer

LogFileWriter::LogFileWriter()
{
   mFile=0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Open the file

bool LogFileWriter::open(char* aFileName)
{
   char tBuf[400];
   mFile = fopen(Ris::getAlphaFilePath_Data(tBuf, aFileName), "w");

   if (mFile==0)
   {
      printf("LogFileWriter::open FAIL");
      return false;
   }

   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Open the file

bool LogFileWriter::openWithPath(char* aFilePath)
{
   mFile = fopen(aFilePath, "w");

   if (mFile == 0)
   {
      printf("LogFileWriter::open FAIL");
      return false;
   }

   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Close the file

void LogFileWriter::close()
{       
   if (mFile)
   {
      fclose(mFile);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write to the file

void LogFileWriter::write(const char* aFormat, ...)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Do a vsprintf with variable arg list into print string.

   int tPrintSize;
   va_list  ArgPtr;
   va_start(ArgPtr, aFormat);
   tPrintSize = vsnprintf(mString, cMaxStringSize, aFormat, ArgPtr);
   va_end(ArgPtr);

   mString[tPrintSize++] = '\n';
   mString[tPrintSize++] = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Print the string.

   fputs(mString,mFile);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// CSV file writer

CsvFileWriter::CsvFileWriter()
{
   mFile=0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Open the file

bool CsvFileWriter::open(char* aFileName)
{            
   char tBuf[400];
   mFile = fopen(Ris::getAlphaFilePath_Data(tBuf, aFileName), "w");

   if (mFile==0)
   {
      printf("CsvFileWriter::::open FAIL");
      return false;
   }

   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Open the file

bool CsvFileWriter::openWithPath(char* aFilePath)
{
   mFile = fopen(aFilePath, "w");

   if (mFile == 0)
   {
      printf("CsvFileWriter::open FAIL");
      return false;
   }

   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Close the file

void CsvFileWriter::close()
{       
   if (mFile)
   {
      fclose(mFile);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write to the file

void CsvFileWriter::writeRow(const char* aFormat, ...)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Do a vsprintf with variable arg list into print string.

   int tPrintSize;
   va_list  ArgPtr;
   va_start(ArgPtr, aFormat);
   tPrintSize = vsnprintf(mString, cMaxStringSize, aFormat, ArgPtr);
   va_end(ArgPtr);

   mString[tPrintSize++] = '\n';
   mString[tPrintSize++] = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Print the string.

   fprintf(mFile,"%s\n",mString);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write to the file

void CsvFileWriter::writeRowN(int aNumArgs, ...)
{
   va_list valist;
   va_start(valist,aNumArgs);
   for (int i=0;i<aNumArgs;i++)
   {
      double tValue = va_arg(valist,double);
      if (i != aNumArgs)
      {
         fprintf(mFile, "%f,", tValue);
      }
      else
      {
         fprintf(mFile, "%f", tValue);
      }
   }
   va_end(valist);

   fprintf(mFile, "\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write to the file

void CsvFileWriter::writeRow(double aX1)
{
   fprintf(mFile, "%f\n",aX1);
}

void CsvFileWriter::writeRow(double aX1,double aX2)
{
   fprintf(mFile, "%f,%f\n",aX1,aX2);
}

void CsvFileWriter::writeRow(double aX1,double aX2,double aX3)
{
   fprintf(mFile, "%f,%f,%f\n",aX1,aX2,aX3);
}

void CsvFileWriter::writeRow(double aX1,double aX2,double aX3,double aX4)
{
   fprintf(mFile, "%f,%f,%f,%f\n",aX1,aX2,aX3,aX4);
}

void CsvFileWriter::writeRow(double aX1,double aX2,double aX3,double aX4,double aX5)
{
   fprintf(mFile, "%f,%f,%f,%f,%f\n",aX1,aX2,aX3,aX4,aX5);
}

void CsvFileWriter::writeRow(double aX1,double aX2,double aX3,double aX4,double aX5,double aX6)
{
   fprintf(mFile, "%f,%f,%f,%f,%f,%f\n",aX1,aX2,aX3,aX4,aX5,aX6);
}

void CsvFileWriter::writeRow(double aX1,double aX2,double aX3,double aX4,double aX5,double aX6,double aX7)
{
   fprintf(mFile, "%f,%f,%f,%f,%f,%f,%f\n",aX1,aX2,aX3,aX4,aX5,aX6,aX7);
}

void CsvFileWriter::writeRow(double aX1,double aX2,double aX3,double aX4,double aX5,double aX6,double aX7,double aX8)
{
   fprintf(mFile, "%f,%f,%f,%f,%f,%f,%f,%f\n",aX1,aX2,aX3,aX4,aX5,aX6,aX7,aX8);
}

void CsvFileWriter::writeRow(double aX1,double aX2,double aX3,double aX4,double aX5,double aX6,double aX7,double aX8,double aX9)
{
   fprintf(mFile, "%f,%f,%f,%f,%f,%f,%f,%f,%f\n",aX1,aX2,aX3,aX4,aX5,aX6,aX7,aX8,aX9);
}

void CsvFileWriter::writeRow(double aX1,double aX2,double aX3,double aX4,double aX5,double aX6,double aX7,double aX8,double aX9,double aX10)
{
   fprintf(mFile, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",aX1,aX2,aX3,aX4,aX5,aX6,aX7,aX8,aX9,aX10);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// CSV file reader.

CsvFileReader::CsvFileReader()
{
   mFile=0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Open the file.

bool CsvFileReader::open(char* aFileName)
{            
   strcpy(mDelimiters," ,\t");
   mRowIndex=0;
   
   char tBuf[400];
   mFile = fopen(Ris::getAlphaFilePath_Data(tBuf, aFileName), "w");

   if (mFile==0)
   {
      return false;
   }

   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Close the file.

void CsvFileReader::close()
{       
   if (mFile)
   {
      fclose(mFile);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read from the file.

bool CsvFileReader::readRow()
{            
   mCols=0;
   // Read the row
   if (fgets(mString, cMaxStringSize, mFile) == NULL)
   {
      return false;
   }

   // Trim the end of the string
   trimString(mString);

   // Extract row index for the row
   char* tPtr = strtok (mString,mDelimiters);
   if (tPtr==NULL) return false;
   mRowIndex = atoi(tPtr);

   // Extract column values for the row
   while (tPtr != NULL)
   {
      tPtr = strtok (NULL,mDelimiters);
      if (tPtr==NULL) break;;
      e(mCols++) = atof(tPtr);
   }

   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

double& CsvFileReader::e (int aCol)
{
   return mValues[aCol];
}

double& CsvFileReader::operator() (int aCol)
{
   return mValues[aCol];
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CsvFileReader::show()
{
   printf("%d ",mRowIndex);

   for (int j=0;j<mCols;j++)
   {
      printf("%12.8f ",e(j));
   }

   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers

void CsvFileReader::trimString(char* aString)
{
   // Remove any character that is not a digit at end of the string
   unsigned tStringLen = (unsigned)strlen(aString);

   int tIndex=tStringLen-1;
   while (true)
   {
      if (isdigit(aString[tIndex]))
      {
         break;
      }
      else
      {
         aString[tIndex]=0;
         if (--tIndex==0) break;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

