include_directories(
  ${VTK_INCLUDE_DIRS}
  ${MantaView_SOURCE_DIR}/VTK
  ${MantaView_BINARY_DIR}/VTK
)

IF(PARAVIEW_BUILD_QT_GUI)
  INCLUDE_DIRECTORIES(
    ${PARAVIEW_GUI_INCLUDE_DIRS}
    )
  INCLUDE(${QT_USE_FILE})
  QT4_WRAP_CPP(MOC_SRCS
    MantaView.h
    MantaDisplay.h
    MantaViewOptions.h)

  QT4_WRAP_UI(UI_SRCS
    MantaDisplay.ui
    MantaViewOptions.ui
    )

  ADD_PARAVIEW_VIEW_MODULE(
    VIEW_IFACE VIEW_IFACE_SRCS
    VIEW_TYPE MantaView
    VIEW_NAME Manta
    VIEW_XML_GROUP views
    VIEW_XML_NAME Manta
    )

  ADD_PARAVIEW_VIEW_OPTIONS(
    OPTIONS_IFACE OPTIONS_IFACE_SRCS
    VIEW_TYPE MantaView
    ACTIVE_VIEW_OPTIONS pqActiveRenderViewOptions
    GLOBAL_VIEW_OPTIONS MantaViewOptions
    )

  ADD_PARAVIEW_DISPLAY_PANEL_DECORATOR(
    DISPLAY_IFACE DISPLAY_IFACE_SRCS
    CLASS_NAME MantaDisplay
    PANEL_TYPES pqDisplayProxyEditor)

ENDIF()

LINK_DIRECTORIES ( ${MANTA_BUILD_LIB} )

add_paraview_plugin(
  MantaView "2.0"
  REQUIRED_ON_SERVER
  REQUIRED_ON_CLIENT
  SERVER_MANAGER_SOURCES
    vtkPVMantaView.cxx
    vtkSMMantaViewProxy.cxx
  SERVER_MANAGER_XML
    MantaView.xml
  GUI_INTERFACES
    ${VIEW_IFACE} ${OPTIONS_IFACE} ${DISPLAY_IFACE}
  GUI_SOURCES
    ${VIEW_IFACE_SRCS} ${OPTIONS_IFACE_SRCS} ${DISPLAY_IFACE_SRCS} ${UI_SRCS}
    ${MOC_SRCS}
    MantaView.cxx
    MantaDisplay.cxx
    MantaViewOptions.cxx
  CS_KITS
    vtkManta
)

TARGET_LINK_LIBRARIES (MantaView vtkManta vtkMantaCS)

if (BUILD_TESTING)
  add_subdirectory(Testing)
endif()
