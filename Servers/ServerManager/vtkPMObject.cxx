/*=========================================================================

  Program:   ParaView
  Module:    vtkPMObject.cxx

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkPMObject.h"

#include "vtkClientServerInterpreter.h"
#include "vtkObjectFactory.h"
#include "vtkSMSessionCore.h"

#include <assert.h>

//----------------------------------------------------------------------------
vtkPMObject::vtkPMObject()
{
  this->Interpreter = 0;
  this->SessionCore = 0;
}

//----------------------------------------------------------------------------
vtkPMObject::~vtkPMObject()
{
}

//----------------------------------------------------------------------------
void vtkPMObject::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
void vtkPMObject::Initialize(vtkSMSessionCore* session)
{
  assert(session != NULL);
  this->SessionCore = session;
  this->Interpreter = session->GetInterpreter();
}

//----------------------------------------------------------------------------
vtkPMObject* vtkPMObject::GetPMObject(vtkTypeUInt32 globalid)
{
  if (this->SessionCore)
    {
    return this->SessionCore->GetPMObject(globalid);
    }
  return NULL;
}

//----------------------------------------------------------------------------
vtkClientServerInterpreter* vtkPMObject::GetInterpreter()
{
  return this->Interpreter;
}
//----------------------------------------------------------------------------
void vtkPMObject::Push(vtkSMMessage* msg)
{
  LastPushedMessage.CopyFrom(*msg);
}

//----------------------------------------------------------------------------
void vtkPMObject::Pull(vtkSMMessage* msg)
{
  msg->CopyFrom(LastPushedMessage);
}
//----------------------------------------------------------------------------
void vtkPMObject::Invoke(vtkSMMessage* msg)
{
  // Nothing
}