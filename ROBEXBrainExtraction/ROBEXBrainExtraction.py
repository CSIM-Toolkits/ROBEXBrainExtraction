# Copyright 2017 Antonio Carlos da Silva Senra Filho
#
# Licensed under the Apache License, Version 2.0(the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http: // www.apache.org / licenses / LICENSE - 2.0
#
# Unless required by applicable law or agreed to in writing, software distributed
# under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
# CONDITIONS OF ANY KIND, either express or implied. See the License for the
# specific language governing permissions and limitations under the License.
import os
import sys
import platform
import unittest
import vtk, qt, ctk, slicer
from slicer.ScriptedLoadableModule import *
import logging

#
# ROBEXBrainExtraction
#

class ROBEXBrainExtraction(ScriptedLoadableModule):
  """Uses ScriptedLoadableModule base class, available at:
  https://github.com/Slicer/Slicer/blob/master/Base/Python/slicer/ScriptedLoadableModule.py
  """

  def __init__(self, parent):
    ScriptedLoadableModule.__init__(self, parent)
    self.parent.title = "ROBEX Brain Extraction"
    self.parent.categories = ["Segmentation"]
    self.parent.dependencies = []
    self.parent.contributors = ["Antonio Carlos da S. Senra Filho (University of Sao Paulo)"] # replace with "Firstname Lastname (Organization)"
    self.parent.helpText = """
    This extension aims to extract the brain from the skull. This tool was intensively tested with T1 MRI images, but the pipeline could be applied to any other structural MRI images,
    namely T2 and PD. This module is an adaptation of ROBEX brain extraction tool, given by Iglesias, J. E. et al (2011). Robust Brain Extraction Across Datasets and Comparison With
    Publicly Available Methods. IEEE Transactions on Medical Imaging, 30(9). DOI:10.1109/TMI.2011.2138152
    """
    self.parent.acknowledgementText = """
    This file was originally developed by Antonio Carlos da S. Senra Filho, CSIM Lab. and was partially funded by CAPES.
""" # replace with organization, grant and thanks.

#
# ROBEXBrainExtractionWidget
#

class ROBEXBrainExtractionWidget(ScriptedLoadableModuleWidget):
  """Uses ScriptedLoadableModuleWidget base class, available at:
  https://github.com/Slicer/Slicer/blob/master/Base/Python/slicer/ScriptedLoadableModule.py
  """

  def setup(self):
    ScriptedLoadableModuleWidget.setup(self)

    # Instantiate and connect widgets ...

    #
    # Parameters Area
    #
    parametersCollapsibleButton = ctk.ctkCollapsibleButton()
    parametersCollapsibleButton.text = "Parameters"
    self.layout.addWidget(parametersCollapsibleButton)

    # Layout within the dummy collapsible button
    parametersFormLayout = qt.QFormLayout(parametersCollapsibleButton)

    #
    # input volume selector
    #
    self.inputSelector = slicer.qMRMLNodeComboBox()
    self.inputSelector.nodeTypes = ["vtkMRMLScalarVolumeNode"]
    self.inputSelector.selectNodeUponCreation = True
    self.inputSelector.addEnabled = False
    self.inputSelector.removeEnabled = False
    self.inputSelector.noneEnabled = False
    self.inputSelector.showHidden = False
    self.inputSelector.showChildNodeTypes = False
    self.inputSelector.setMRMLScene( slicer.mrmlScene )
    self.inputSelector.setToolTip( "Pick the input to the algorithm." )
    parametersFormLayout.addRow("Input Volume: ", self.inputSelector)

    #
    # output volume selector
    #
    self.outputSelector = slicer.qMRMLNodeComboBox()
    self.outputSelector.nodeTypes = ["vtkMRMLScalarVolumeNode"]
    self.outputSelector.selectNodeUponCreation = True
    self.outputSelector.addEnabled = True
    self.outputSelector.renameEnabled = True
    self.outputSelector.removeEnabled = True
    self.outputSelector.noneEnabled = False
    self.outputSelector.showHidden = False
    self.outputSelector.showChildNodeTypes = False
    self.outputSelector.setMRMLScene( slicer.mrmlScene )
    self.outputSelector.setToolTip( "Pick the output to the algorithm." )
    parametersFormLayout.addRow("Output Volume: ", self.outputSelector)

    #
    # brain mask label selector
    #
    self.brainMaskSelector = slicer.qMRMLNodeComboBox()
    self.brainMaskSelector.nodeTypes = ["vtkMRMLLabelMapVolumeNode"]
    self.brainMaskSelector.selectNodeUponCreation = True
    self.brainMaskSelector.addEnabled = True
    self.brainMaskSelector.renameEnabled = True
    self.brainMaskSelector.removeEnabled = True
    self.brainMaskSelector.noneEnabled = True
    self.brainMaskSelector.showHidden = False
    self.brainMaskSelector.showChildNodeTypes = False
    self.brainMaskSelector.setMRMLScene(slicer.mrmlScene)
    self.brainMaskSelector.setToolTip(
      "Output the brain extraction binary mask.")
    parametersFormLayout.addRow("Brain Mask ", self.brainMaskSelector)

    #
    # Apply Button
    #
    self.applyButton = qt.QPushButton("Apply")
    self.applyButton.toolTip = "Run the algorithm."
    self.applyButton.enabled = False
    parametersFormLayout.addRow(self.applyButton)

    # connections
    self.applyButton.connect('clicked(bool)', self.onApplyButton)
    self.inputSelector.connect("currentNodeChanged(vtkMRMLNode*)", self.onSelect)
    self.outputSelector.connect("currentNodeChanged(vtkMRMLNode*)", self.onSelect)

    # Add vertical spacer
    self.layout.addStretch(1)

    # Refresh Apply button state
    self.onSelect()

  def cleanup(self):
    pass

  def onSelect(self):
    self.applyButton.enabled = self.inputSelector.currentNode() and self.outputSelector.currentNode()

  def onApplyButton(self):
    logic = ROBEXBrainExtractionLogic()
    logic.run(self.inputSelector.currentNode(), self.outputSelector.currentNode(), self.brainMaskSelector.currentNode())

#
# ROBEXBrainExtractionLogic
#

class ROBEXBrainExtractionLogic(ScriptedLoadableModuleLogic):
  """This class should implement all the actual
  computation done by your module.  The interface
  should be such that other python code can import
  this class and make use of the functionality without
  requiring an instance of the Widget.
  Uses ScriptedLoadableModuleLogic base class, available at:
  https://github.com/Slicer/Slicer/blob/master/Base/Python/slicer/ScriptedLoadableModule.py
  """

  def hasImageData(self,volumeNode):
    """This is an example logic method that
    returns true if the passed in volume
    node has valid image data
    """
    if not volumeNode:
      logging.debug('hasImageData failed: no volume node')
      return False
    if volumeNode.GetImageData() is None:
      logging.debug('hasImageData failed: no image data in volume node')
      return False
    return True

  def isValidInputOutputData(self, inputVolumeNode, outputVolumeNode):
    """Validates if the output is not the same as input
    """
    if not inputVolumeNode:
      logging.debug('isValidInputOutputData failed: no input volume node defined')
      return False
    if not outputVolumeNode:
      logging.debug('isValidInputOutputData failed: no output volume node defined')
      return False
    if inputVolumeNode.GetID()==outputVolumeNode.GetID():
      logging.debug('isValidInputOutputData failed: input and output volume is the same. Create a new volume for output to avoid this error.')
      return False
    return True

  def run(self, inputVolume, outputVolume, brainmask):
    """
    Run the actual algorithm
    """

    if not self.isValidInputOutputData(inputVolume, outputVolume):
      slicer.util.errorDisplay('Input volume is the same as output volume. Choose a different output volume.')
      return False

    # Get the path to ROBEX-Data files
    path2files = os.path.dirname(slicer.modules.robexbrainextraction.path)

    logging.info('Processing started')

    cliParams={}
    cliParams["inputVolume"] = inputVolume.GetID()
    cliParams["outputVolume"] = outputVolume.GetID()
    if brainmask is not None:
      cliParams["brainMask"] = brainmask.GetID()
    if platform.system() == "Windows":
      cliParams["datPath"] = path2files + '\\Resources\\dat\\'
      cliParams["refVolsPath"] = path2files + '\\Resources\\ref_vols'
    else:
      cliParams["datPath"] = path2files + '/Resources/dat/'
      cliParams["refVolsPath"] = path2files + '/Resources/ref_vols'

    slicer.cli.run(slicer.modules.robexbrainextractioncore, None, cliParams, wait_for_completion=True)


    logging.info('Processing completed')

    return True


class ROBEXBrainExtractionTest(ScriptedLoadableModuleTest):
  """
  This is the test case for your scripted module.
  Uses ScriptedLoadableModuleTest base class, available at:
  https://github.com/Slicer/Slicer/blob/master/Base/Python/slicer/ScriptedLoadableModule.py
  """

  def setUp(self):
    """ Do whatever is needed to reset the state - typically a scene clear will be enough.
    """
    slicer.mrmlScene.Clear(0)

  def runTest(self):
    """Run as few or as many tests as needed here.
    """
    self.setUp()
    self.test_ROBEXBrainExtraction1()

  def test_ROBEXBrainExtraction1(self):
    """ Ideally you should have several levels of tests.  At the lowest level
    tests should exercise the functionality of the logic with different inputs
    (both valid and invalid).  At higher levels your tests should emulate the
    way the user would interact with your code and confirm that it still works
    the way you intended.
    One of the most important features of the tests is that it should alert other
    developers when their changes will have an impact on the behavior of your
    module.  For example, if a developer removes a feature that you depend on,
    your test should break so they know that the feature is needed.
    """

    self.delayDisplay("Starting the test")
    #
    # first, get some data
    #
    import urllib
    downloads = (
        ('http://slicer.kitware.com/midas3/download?items=5767', 'FA.nrrd', slicer.util.loadVolume),
        )

    for url,name,loader in downloads:
      filePath = slicer.app.temporaryPath + '/' + name
      if not os.path.exists(filePath) or os.stat(filePath).st_size == 0:
        logging.info(f'Requesting download {name} from {url}...\n')
        urllib.urlretrieve(url, filePath)
      if loader:
        logging.info(f'Loading {name}...')
        loader(filePath)
    self.delayDisplay('Finished with download and loading')

    volumeNode = slicer.util.getNode(pattern="FA")
    logic = ROBEXBrainExtractionLogic()
    self.assertIsNotNone( logic.hasImageData(volumeNode) )
    self.delayDisplay('Test passed!')
