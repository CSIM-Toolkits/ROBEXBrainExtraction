cmake_minimum_required(VERSION 2.8.9)

project(ROBEXBrainExtraction)

#-----------------------------------------------------------------------------
# Extension meta-information
set(EXTENSION_HOMEPAGE "http://slicer.org/slicerWiki/index.php/Documentation/Nightly/Extensions/ROBEXBrainExtraction")
set(EXTENSION_CATEGORY "Segmentation")
set(EXTENSION_CONTRIBUTORS "Antonio Carlos da S. Senra Filho (University of Sao Paulo)")
set(EXTENSION_DESCRIPTION "This extension aims to extract the brain from the skull. This tool was intensively tested with T1 MRI images, but the pipeline could be applied to any other structural MRI images, namely T2 and PD. This module is an adaptation of ROBEX brain extraction tool, given by Iglesias, J. E. et al (2011). Robust Brain Extraction Across Datasets and Comparison With Publicly Available Methods. IEEE Transactions on Medical Imaging, 30(9). DOI:10.1109/TMI.2011.2138152")
set(EXTENSION_ICONURL "https://www.slicer.org/w/images/7/7a/ROBEXBrainExtraction-logo.png")
set(EXTENSION_SCREENSHOTURLS "https://www.slicer.org/w/images/c/ca/AllHeadMRI.png https://www.slicer.org/w/images/0/06/BrainMRI.png https://www.slicer.org/w/images/7/71/ROBEXBrainExtraction-GUI.png")

#-----------------------------------------------------------------------------
# Extension dependencies
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})

#-----------------------------------------------------------------------------
# Extension modules
add_subdirectory(ROBEXBrainExtractionCore)
add_subdirectory(ROBEXBrainExtraction)
## NEXT_MODULE

#-----------------------------------------------------------------------------
include(${Slicer_EXTENSION_CPACK})
