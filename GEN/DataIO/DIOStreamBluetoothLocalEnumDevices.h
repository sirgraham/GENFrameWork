//------------------------------------------------------------------------------------------
//  DIOSTREAMBLUETOOTHLOCALENUMDEVICES.H
//
/**
// \class
//
//  Data IO Stream Bluetooth Local Enum Devices class
//
//  @author  Abraham J. Velez
//  @version 23/05/2002
*/
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------

#ifndef _DIOSTREAMBLUETOOTHLOCALENUMDEVICES_H_
#define _DIOSTREAMBLUETOOTHLOCALENUMDEVICES_H_


//---- INCLUDES ----------------------------------------------------------------------------

#include "DIOStreamEnumDevices.h"

//---- DEFINES & ENUMS  --------------------------------------------------------------------



//---- CLASS -------------------------------------------------------------------------------

class XFACTORY;
class XPUBLISHER;

class DIOSTREAMBLUETOOTHLOCALENUMDEVICES :  public DIOSTREAMENUMDEVICES
{
  public:
                            DIOSTREAMBLUETOOTHLOCALENUMDEVICES        ();
    virtual                ~DIOSTREAMBLUETOOTHLOCALENUMDEVICES        ();

    virtual bool            Search                                    ()                                  { return false;         };
    virtual bool            StopSearch                                (bool waitend)                      { return false;         };
    bool                    IsSearching                               ()                                  { return issearching;   };

    virtual bool            IsDeviceAvailable                         (XCHAR* resource)                   { return false;         };

  private:

    void                    Clean                                     ();

    bool                    issearching;
};


//---- INLINE FUNCTIONS --------------------------------------------------------------------

#endif
