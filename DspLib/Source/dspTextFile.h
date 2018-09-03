#pragma once

/*==============================================================================

text files 

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <stdio.h>

//******************************************************************************
//******************************************************************************
//******************************************************************************
// log files

namespace Dsp
{

class LogFileWriter
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // File handle.
   FILE*  mFile;

   // Text buffer.
   static const int cMaxStringSize = 400;
   char mString[cMaxStringSize];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   LogFileWriter();

   // Open the text file for write.
   bool open (char* aFileName);

   // Write to the text file.
   void write (const char* aFormat, ...);

   // Close the text file.
   void close ();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// CSV files of doubles, writer

class CsvFileWriter
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // File handle.
   FILE*  mFile;

   // Text buffer.
   static const int cMaxStringSize = 400;
   char mString[cMaxStringSize];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   CsvFileWriter();

   // Open the text file for write.
   bool open (char* aFilename);

   // Close the file.
   void close ();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Write a row to the text file.
   void writeRow  (int aRowIndex,const char* aFormat, ...);
   void writeRowN (int aRowIndex,int aNumArgs, ...);
   void writeRow  (int aRowIndex,double aX1);
   void writeRow  (int aRowIndex,double aX1,double aX2);
   void writeRow  (int aRowIndex,double aX1,double aX2,double aX3);
   void writeRow  (int aRowIndex,double aX1,double aX2,double aX3,double aX4);
   void writeRow  (int aRowIndex,double aX1,double aX2,double aX3,double aX4,double aX5);
   void writeRow  (int aRowIndex,double aX1,double aX2,double aX3,double aX4,double aX5,double aX6);
   void writeRow  (int aRowIndex,double aX1,double aX2,double aX3,double aX4,double aX5,double aX6,double aX7);
   void writeRow  (int aRowIndex,double aX1,double aX2,double aX3,double aX4,double aX5,double aX6,double aX7,double aX8);
   void writeRow  (int aRowIndex,double aX1,double aX2,double aX3,double aX4,double aX5,double aX6,double aX7,double aX8,double aX9);
   void writeRow  (int aRowIndex,double aX1,double aX2,double aX3,double aX4,double aX5,double aX6,double aX7,double aX8,double aX9,double aX10);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// CSV files of doubles, reader

class CsvFileReader
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // File handle
   FILE*  mFile;

   // Text buffer.
   static const int cMaxStringSize = 400;
   char mString[cMaxStringSize];
   char mDelimiters[8];

   // Matrix components.
   static const int cMaxNumOfCols = 100;
   double mValues[cMaxNumOfCols];
   int mCols;
   int mRowIndex;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   CsvFileReader();

   // Open the text file for read/
   bool open (char* aFilename);

   // Close the text file.
   void close ();

   // Read from the file.
   bool readRow ();

   // Access column values from the last row that was read.
   double& e(int aCol);
   double& operator()(int aCol);

   // Helpers.
   void show();
   static void trimString(char* aString);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

