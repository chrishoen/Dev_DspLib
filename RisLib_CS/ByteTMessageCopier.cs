using System;
using System.Text;
using System.IO;

namespace Ris
{ 

    //******************************************************************************
    //******************************************************************************
    //******************************************************************************

    public abstract class BaseTMessageCopier
    { 
        //***********************************************************************
        // This creates a new record, based on a record type

        public abstract ByteTMessage createMessage (int aType);

        //***********************************************************************
        // This copies byte buffers to/from records

        public abstract void copyToFrom( ByteBuffer aBuffer, ByteTMessage aMsg);
    };

}
