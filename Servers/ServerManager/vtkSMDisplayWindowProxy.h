/*=========================================================================

  Program:   ParaView
  Module:    vtkSMDisplayWindowProxy.h

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkSMDisplayWindowProxy - composite proxy for renderer, render window...
// .SECTION Description
// vtkSMDisplayWindowProxy is a composite proxy that manages objects related
// to rendering including renderer, render window, composite manager,
// camera, image writer (for screenshots)
// .SECTION See Also
// vtkSMDisplayerProxy vtkSMProxy

#ifndef __vtkSMDisplayWindowProxy_h
#define __vtkSMDisplayWindowProxy_h

#include "vtkSMProxy.h"
#include "vtkClientServerID.h" // Needed for ClientServerID

class vtkSMDisplayerProxy;

class VTK_EXPORT vtkSMDisplayWindowProxy : public vtkSMProxy
{
public:
  static vtkSMDisplayWindowProxy* New();
  vtkTypeRevisionMacro(vtkSMDisplayWindowProxy, vtkSMProxy);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Render without LOD.
  void StillRender();

  // Description:
  // Render with LOD. Not used yet.
  void InteractiveRender();

  // Description:
  // Adds a display to the list of managed displays. This adds
  // the actor(s) to the renderer.
  void AddDisplayer(vtkSMDisplayerProxy* displayer);

  // Description:
  // Update all VTK objects. Including the ones managed by the
  // sub-proxies.
  virtual void UpdateVTKObjects();

  // Description:
  // Generate a screenshot from the render window.
  void WriteImage(const char* filename, const char* writerName);

protected:
  vtkSMDisplayWindowProxy();
  ~vtkSMDisplayWindowProxy();

  // Description:
  // Create all VTK objects including the ones for sub-proxies.
  virtual void CreateVTKObjects(int numObjects);

  vtkSMProxy* RendererProxy;
  vtkSMProxy* CameraProxy;
  vtkSMProxy* CompositeProxy;
  vtkSMProxy* WindowToImage;

private:
  vtkSMDisplayWindowProxy(const vtkSMDisplayWindowProxy&); // Not implemented
  void operator=(const vtkSMDisplayWindowProxy&); // Not implemented
};

#endif
