
#-----------------------------------------------------------------------------
set(MODULE_NAME ROBEXBrainExtraction)

#-----------------------------------------------------------------------------

#
# SlicerExecutionModel
#
find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})


#
# ITK
#
set(${PROJECT_NAME}_ITK_COMPONENTS
  ITKIOImageBase
  ITKSmoothing
  ITKRegistrationCommon
  )
find_package(ITK 4.6 COMPONENTS ${${PROJECT_NAME}_ITK_COMPONENTS} REQUIRED)
set(ITK_NO_IO_FACTORY_REGISTER_MANAGER 1) # See Libs/ITKFactoryRegistration/CMakeLists.txt
include(${ITK_USE_FILE})

#-----------------------------------------------------------------------------
set(MODULE_INCLUDE_DIRECTORIES
  )

set(MODULE_SRCS
  )

set(MODULE_TARGET_LIBRARIES
  ${ITK_LIBRARIES}
  )

#-----------------------------------------------------------------------------
SEMMacroBuildCLI(
  NAME ${MODULE_NAME}
  TARGET_LIBRARIES ${MODULE_TARGET_LIBRARIES}
  INCLUDE_DIRECTORIES ${MODULE_INCLUDE_DIRECTORIES}
  ADDITIONAL_SRCS ${MODULE_SRCS}
aux_methods.cxx
loadModel.cpp
graph.cpp
maxflow.cpp
maxflow_main.cpp
RobustStrip.h
  )

if (WIN32)
add_custom_target(build-time-make-directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory %userprofile%\\ROBEX-data)
endif (WIN32)
if (UNIX)
add_custom_target(build-time-make-directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ~/ROBEX-data)
endif (UNIX)

## we don't want to copy if we're building in the source dir
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)

    # list of files for which we add a copy rule
    if (WIN32)
        set(INPUTS
    ref_vols\\atlas.nii.gz
    ref_vols\\atlas.nii.gz
    ref_vols\\atlas_mask.nii.gz
    ref_vols\\atlas_mask_dilated.nii.gz
    ref_vols\\atlas_mask_eroded.nii.gz
    ref_vols\\Mini.nii.gz

    dat\\256.dat
    dat\\bestvar.dat
    dat\\classwt.dat
    dat\\cutoff.dat
    dat\\EDGES_ir.dat
    dat\\EDGES_jc.dat
    dat\\EDGES_pr.dat
    dat\\face.dat
    dat\\lambda.dat
    dat\\lambda2.dat
    dat\\mean_normals.dat
    dat\\mu.dat
    dat\\ndbigtree.dat
    dat\\nodeclass.dat
    dat\\nodestatus.dat
    dat\\PHI.dat
    dat\\PHI2.dat
    dat\\T_ir.dat
    dat\\T_jc.dat
    dat\\T_pr.dat
    dat\\treemap.dat
    dat\\xbestsplit.dat
    )
    endif (WIN32)
    if (UNIX)
        set(INPUTS
    ref_vols/atlas.nii.gz
    ref_vols/atlas.nii.gz
    ref_vols/atlas_mask.nii.gz
    ref_vols/atlas_mask_dilated.nii.gz
    ref_vols/atlas_mask_eroded.nii.gz
    ref_vols/Mini.nii.gz

    dat/256.dat
    dat/bestvar.dat
    dat/classwt.dat
    dat/cutoff.dat
    dat/EDGES_ir.dat
    dat/EDGES_jc.dat
    dat/EDGES_pr.dat
    dat/face.dat
    dat/lambda.dat
    dat/lambda2.dat
    dat/mean_normals.dat
    dat/mu.dat
    dat/ndbigtree.dat
    dat/nodeclass.dat
    dat/nodestatus.dat
    dat/PHI.dat
    dat/PHI2.dat
    dat/T_ir.dat
    dat/T_jc.dat
    dat/T_pr.dat
    dat/treemap.dat
    dat/xbestsplit.dat
    )
    endif (UNIX)


#    foreach(item IN LISTS INPUTS)
#        message(STATUS ${item})
#        add_custom_command(
#            TARGET ${MODULE_NAME} POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${item}" "${PROJECT_BINARY_DIR}/lib/Slicer-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}/cli-modules/${item}"
#            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}"
#        )
#    endforeach()

    foreach(item IN LISTS INPUTS)
        message(STATUS ${item})
        if (WIN32)
            add_custom_command(
                TARGET ${MODULE_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}\\${item}" "%userprofile%\\ROBEX-data\\${item}"
                DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}\\${item}"
                )
        endif (WIN32)
        if (UNIX)
            add_custom_command(
                TARGET ${MODULE_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${item}" "~/ROBEX-data/${item}"
                DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}"
                )
        endif (UNIX)
    endforeach()
endif()

# files are only copied if a target depends on them
if (WIN32)
    add_custom_target(data-target ALL DEPENDS
    "%userprofile%\\ROBEX-data\\ref_vols\\atlas.nii.gz"
    "%userprofile%\\ROBEX-data\\ref_vols\\atlas_mask.nii.gz"
    "%userprofile%\\ROBEX-data\\ref_vols\\atlas_mask_dilated.nii.gz"
    "%userprofile%\\ROBEX-data\\ref_vols\\atlas_mask_eroded.nii.gz"
    "%userprofile%\\ROBEX-data\\ref_vols\\Mini.nii.gz"

    "%userprofile%\\ROBEX-data\\dat\\256.dat"
    "%userprofile%\\ROBEX-data\\dat\\bestvar.dat"
    "%userprofile%\\ROBEX-data\\dat\\classwt.dat"
    "%userprofile%\\ROBEX-data\\dat\\cutoff.dat"
    "%userprofile%\\ROBEX-data\\dat\\EDGES_ir.dat"
    "%userprofile%\\ROBEX-data\\dat\\EDGES_jc.dat"
    "%userprofile%\\ROBEX-data\\dat\\EDGES_pr.dat"
    "%userprofile%\\ROBEX-data\\dat\\face.dat"
    "%userprofile%\\ROBEX-data\\dat\\lambda.dat"
    "%userprofile%\\ROBEX-data\\dat\\lambda2.dat"
    "%userprofile%\\ROBEX-data\\dat\\mean_normals.dat"
    "%userprofile%\\ROBEX-data\\dat\\mu.dat"
    "%userprofile%\\ROBEX-data\\dat\\ndbigtree.dat"
    "%userprofile%\\ROBEX-data\\dat\\nodeclass.dat"
    "%userprofile%\\ROBEX-data\\dat\\nodestatus.dat"
    "%userprofile%\\ROBEX-data\\dat\\PHI.dat"
    "%userprofile%\\ROBEX-data\\dat\\PHI2.dat"
    "%userprofile%\\ROBEX-data\\dat\\T_ir.dat"
    "%userprofile%\\ROBEX-data\\dat\\T_jc.dat"
    "%userprofile%\\ROBEX-data\\dat\\T_pr.dat"
    "%userprofile%\\ROBEX-data\\dat\\treemap.dat"
    "%userprofile%\\ROBEX-data\\dat\\xbestsplit.dat"
    )
endif (WIN32)
if (UNIX)
    add_custom_target(data-target ALL DEPENDS
    "~/ROBEX-data/ref_vols/atlas.nii.gz"
    "~/ROBEX-data/ref_vols/atlas_mask.nii.gz"
    "~/ROBEX-data/ref_vols/atlas_mask_dilated.nii.gz"
    "~/ROBEX-data/ref_vols/atlas_mask_eroded.nii.gz"
    "~/ROBEX-data/ref_vols/Mini.nii.gz"

    "~/ROBEX-data/dat/256.dat"
    "~/ROBEX-data/dat/bestvar.dat"
    "~/ROBEX-data/dat/classwt.dat"
    "~/ROBEX-data/dat/cutoff.dat"
    "~/ROBEX-data/dat/EDGES_ir.dat"
    "~/ROBEX-data/dat/EDGES_jc.dat"
    "~/ROBEX-data/dat/EDGES_pr.dat"
    "~/ROBEX-data/dat/face.dat"
    "~/ROBEX-data/dat/lambda.dat"
    "~/ROBEX-data/dat/lambda2.dat"
    "~/ROBEX-data/dat/mean_normals.dat"
    "~/ROBEX-data/dat/mu.dat"
    "~/ROBEX-data/dat/ndbigtree.dat"
    "~/ROBEX-data/dat/nodeclass.dat"
    "~/ROBEX-data/dat/nodestatus.dat"
    "~/ROBEX-data/dat/PHI.dat"
    "~/ROBEX-data/dat/PHI2.dat"
    "~/ROBEX-data/dat/T_ir.dat"
    "~/ROBEX-data/dat/T_jc.dat"
    "~/ROBEX-data/dat/T_pr.dat"
    "~/ROBEX-data/dat/treemap.dat"
    "~/ROBEX-data/dat/xbestsplit.dat"
    )
endif (UNIX)


#-----------------------------------------------------------------------------
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()
