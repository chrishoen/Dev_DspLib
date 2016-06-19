#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "my_functions.h"
#include "prnPrint.h"
#include "dspTextFile.h"

#include "CmdLineExec.h"

using namespace std;
//******************************************************************************
CmdLineExec::CmdLineExec()
{
}
//******************************************************************************
void CmdLineExec::reset()
{
}
//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1(aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2(aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3(aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4(aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5(aCmd);
}


//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   Dsp::LogFileWriter tWriter;
   tWriter.open("C:\\Alpha\\Data\\log_file_101.txt");
   tWriter.write("%d %d",101,102);
   tWriter.write("%d %d",201,202);
   tWriter.close();
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   Dsp::CsvFileWriter tWriter;
   tWriter.open("C:\\Alpha\\Data\\file_101.csv");
   tWriter.writeRowN(101,2,101.1,102.2);
   tWriter.writeRowN(103,2,201.1,202.2);
   tWriter.writeRow (103,301.1,302.2);
   tWriter.writeRow (104,401.1,302.2);
   tWriter.close();
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   Dsp::CsvFileReader tReader;
   tReader.open("C:\\Alpha\\Data\\file_101.csv");

   while(true)
   {
      if (!tReader.readRow()) return;
      tReader.show();
   }
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   char tString[100];
   strcpy(tString,"1234.0, \n");

   Prn::print(0, "%d %s", strlen(tString),tString);
   Dsp::CsvFileReader::trimString(tString);
   Prn::print(0, "%d %s", strlen(tString),tString);
}


//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


