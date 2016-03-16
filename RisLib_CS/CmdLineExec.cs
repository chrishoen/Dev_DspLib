using System;
using System.Collections.Generic;
using System.Text;

namespace Ris
{

    //**************************************************************************
    //**************************************************************************
    //**************************************************************************
    // Command line executive base class

    public abstract class BaseCmdLineExec
    {
        //**********************************************************************
        // Constructor

        public BaseCmdLineExec()
        {
            mExitFlag = false;
        }

        public virtual void reset() {}

        //**********************************************************************
        // This is called by an executer to execute a single command line.
        // It is passed in a pointer to the command and a pointer to an
        // command line file executer. The pointers are stored so as to 
        // be available to inherited class methods used to process specific
        // commands.

        public abstract void execute(CmdLineCmd aCmd);

        //**********************************************************************
        // Push the executive onto the nested executive stack that is
        // contained in the nested anchor that is contained in the command

        public void nestedPush(CmdLineCmd aCmd, BaseCmdLineExec aNextExec)
        {
            // Guard
            if (aCmd.mNestedAnchor == null) return;

            // Push the executive onto the nested executive stack
            aCmd.mNestedAnchor.nestedPush(aNextExec);
        }

        //**********************************************************************
        // Pop the executive from the nested executive stack that is
        // contained in the nested anchor that is contained in the command

        public void nestedPop(CmdLineCmd aCmd)
        {
            // Guard
            if (aCmd.mNestedAnchor == null) return;

            // Pop the executive from the nested executive stack
            aCmd.mNestedAnchor.nestedPop();
        }

        //**********************************************************************
        // This can be called to indicate to the command line processor to exit a
        // sequence of commands, as if "EXIT" was the command.

        public void forceExit()
        {
            mExitFlag = true;
        }

        public bool mExitFlag;

        //**********************************************************************
        // This can be called when an exit is encountered.

        public virtual void executeExit() { }

    };


    //**************************************************************************
    //**************************************************************************
    //**************************************************************************
    // Command line executive nested anchor.
    // This is used for sequences of commands that process nested records, which
    // are processed by different executives. It contains a stack of executive
    // pointers. When processing for a nested record is entered, the current
    // executive is pushed onto the stack. When the processing is exited, the
    // executive is restored by popping it from the stack.

    public class CmdLineExecNestedAnchor
    {
        //**********************************************************************
        // Constructor

        public CmdLineExecNestedAnchor()
        {
            mChangeFlag = false;
            mExec = null;
            mExecStack = new Stack<BaseCmdLineExec>(10);
        }

        // Initialize 
        public void initialize(BaseCmdLineExec aInitialExec)
        {
            mChangeFlag = false;
            mExec = aInitialExec;
        }

        //**********************************************************************
        // Push executive onto the stack and set current executive

        public void nestedPush(BaseCmdLineExec aNextExec)
        {
            // Push current executive onto the stack
            mExecStack.Push(mExec);

            // Set the current executive
            mExec = aNextExec;

            // Change
            mChangeFlag = true;
        }

        //**********************************************************************
        // Pop executive from the stack to set the current executive

        public void nestedPop()
        {
            // Pop from the stack to set the current executive 
            mExec = mExecStack.Pop();

            // Change
            mChangeFlag = true;
        }

        //**********************************************************************
        // Members

        // True if there was a push or pop
        public bool mChangeFlag;

        // Current executive
        public BaseCmdLineExec mExec;

        // Stack of nested executive pointers
        public Stack<BaseCmdLineExec> mExecStack;
    };

}//namespace
