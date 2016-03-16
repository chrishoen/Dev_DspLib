using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace Ris
{
    //**************************************************************************
    // This class is a command line processor for text files that contain a
    // sequence of command lines. It opens a command line file and applies an
    // executive to process all of the commands in the file, one at a time, as
    // if they were commands typed into a console command line interface. If an
    // "EXIT" command is encountered then no further commands are processed.

    public class CmdLineFile
    {
        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        // Members

        // File stream reader
        public StreamReader mReader;

        // Open stream reader
        public bool open (String aFilePath)
        {
            mReader = null;

            try
            {
                mReader = File.OpenText(aFilePath);
            }
            catch (Exception e)
            {
                Console.WriteLine("Error reading from {0}. Message = {1}", aFilePath, e.Message);
            }

            return mReader  != null;
        }

        // Open stream reader
        public void close ()
        {
            mReader.Close();
        }

        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        // This method applies a command line executive to process all of the
        // command lines in the file

        public void execute(BaseCmdLineExec aExec)
        {
            // Guard
            if (mReader == null) return;

            //--------------------------------------------------------------
            //--------------------------------------------------------------
            //--------------------------------------------------------------
            // Locals

            // Command line executive for current nesting level
            BaseCmdLineExec tExec = aExec;

            // Command line string for current line
            String          tCmdLine;

            // Loop line number
            int             tLineNumber = 0;

            // True if current line is a comment
            bool            tCommentFlag = false;

            // Nested anchor. This is used to manage files that contain nested records,
            // which are processed by nested executives.
            CmdLineExecNestedAnchor tNestedAnchor = new CmdLineExecNestedAnchor();

            // Initialize to the initial executive
            tNestedAnchor.initialize(aExec);

            //--------------------------------------------------------------
            //--------------------------------------------------------------
            //--------------------------------------------------------------
            // Loop to read each command line in the file

            tLineNumber = 0;

            bool tGoing = true;
            while (tGoing)
            {
                // Command for current line
                CmdLineCmd      tCmd = new CmdLineCmd();

                // Set the command nested anchor pointer.  This is piggybacked 
                // onto the command so that it can be used by the executive.
                tCmd.mNestedAnchor = tNestedAnchor;

                tLineNumber++;

                // Read command line
                tCmdLine = mReader.ReadLine();

                if (tCmdLine == null) break;

                // Test for comment line    
                tCommentFlag = false;

                if (tCmdLine.Length > 0)
                {
                    if (tCmdLine[0] == '#') tCommentFlag = true;
                    if (tCmdLine[0] == '/') tCommentFlag = true;
                }

                // If the command line is not empty and not a comment
                // then process it, else go on to the next line
                if (tCmdLine.Length > 0 && !tCommentFlag)
                {
                    // Put command line string to command line command
                    // for parsing
                    tCmd.putCmdLineString(tCmdLine);

                    // Process the parsed command line
                    if (tCmd.isCmd("EXIT"))
                    {
                        // If exit then exit the loop
                        tGoing = false;
                    }
                    // If not an exit then process the parsed command line
                    else
                    {
                        // If tExec is not zero
                        if (tExec != null)
                        {
                            // Call the executive to process the command
                            tExec.execute(tCmd);
                        }
                        // Else tExec is not valid, there was a prior unrecognized Begin 
                        // and zero was nestedPushed
                        else
                        {
                            if (tCmd.isCmd("END"))
                            {
                                // Pop the executive from the nested executive stack
                                // This will balance the unrecognized Begin
                                tNestedAnchor.nestedPop();
                            }
                        }

                        // If the command pushed to the anchor stack 
                        if (tNestedAnchor.mChangeFlag)
                        {
                            // If the command pushed a new executive onto the anchor
                            // stack because it entered a new nested section, or if it 
                            // popped an executive from the anchor stack because it is
                            // leaving a nested section then get the next executive from
                            // the anchor stack
                            tNestedAnchor.mChangeFlag = false;
                            tExec = tNestedAnchor.mExec;
                        }

                        // If the command set the exit flag then exit the loop
                        if (tExec != null)
                        {
                            if (tExec.mExitFlag)
                            {
                                tGoing = false;
                            }
                        }
                    }
                }
            }
        }
    }

}//namespace
