
TARGET     	 = GGFConverter

ARCHITECTURE = PC
#ARCHITECTURE 	= RASPBERRYPI
#ARCHITECTURE = ODROIDC1
DEBUGMODE    	= YES
#TOOLCHAIN		=	LINARO
TOOLCHAIN			=	RASPBIAN
SYSROOT				=	JESSIE

ADDDIRECTORYGEN = ../../GENFrameWork/

FLAGS  			+= -D LINUX
FLAGS  			+= -D UNICODE
#FLAGS  		+= -D XMEM
FLAGS				+= -D GRP_ACTIVE
#FLAGS				+= -D GRPDEFORMERS_ACTIVE
#FLAGS				+= -D GRPVERTEX_EXTENDED
FLAGS			  += -D INP_ACTIVE
FLAGS				+= -D SND_ACTIVE
FLAGS				+= -D DIO_ACTIVE
FLAGS				+= -D DIOI2C_ACTIVE
FLAGS				+= -D DIOSPI_ACTIVE
#FLAGS			+= -D DIOPORTDATA_ACTIVE
FLAGS				+= -D DIOPING_ACTIVE
#FLAGS			+= -D PHY_ACTIVE
#FLAGS 			+= -D VIDEO_ACTIVE

FLAGSC  		+= -DHAVE_MEMMOVE
FLAGSCPP		+= 

#---- INCLUDES -------------------------------------------------------------------

CPPDIR  = ../../Application	

#---- SOURCES CPP ----------------------------------------------------------------

SOURCESCPP 	+= GGFConverter.cpp

SOURCESCPP 	+= AIController.cpp
SOURCESCPP 	+= AILogic.cpp
SOURCESCPP 	+= AIState.cpp
SOURCESCPP 	+= AITransition.cpp
SOURCESCPP 	+= AIAnimation.cpp

SOURCESCPP  += DIOFactory.cpp
SOURCESCPP	+= DIOStream.cpp
SOURCESCPP	+= DIOStreamConfig.cpp
SOURCESCPP	+= DIOStreamDevice.cpp
SOURCESCPP	+= DIOStreamDeviceIP.cpp
SOURCESCPP	+= DIOStreamEnumDevices.cpp
SOURCESCPP	+= DIOStreamSPI.cpp
SOURCESCPP	+= DIOStreamSPIConfig.cpp
SOURCESCPP  += DIOStreamTCPIPConfig.cpp
SOURCESCPP 	+= DIOStreamTCPIP.cpp
SOURCESCPP  += DIOStreamICMP.cpp
SOURCESCPP  += DIOStreamICMPConfig.cpp
SOURCESCPP 	+= DIOStreamUDPLocalEnumServers.cpp
SOURCESCPP  += DIOStreamEnumServers.cpp
SOURCESCPP 	+= DIOStreamUDPConfig.cpp
SOURCESCPP 	+= DIOStreamUDP.cpp
SOURCESCPP	+= DIOSPILCDScreenILI9341.cpp
SOURCESCPP	+= DIOSPITouchScreenSTMPE610.cpp
SOURCESCPP	+= DIOSPILCDScreenPCF8833.cpp
SOURCESCPP  += DIOURL.cpp
SOURCESCPP  += DIOIP.cpp
SOURCESCPP  += DIOMAC.cpp
SOURCESCPP  += DIOPing.cpp
SOURCESCPP  += DIORemoteFileConfig.cpp

SOURCESCPP 	+= DIOStreamI2C.cpp
SOURCESCPP 	+= DIOStreamI2CConfig.cpp
SOURCESCPP	+= DIOI2CPWMControlerPCA9685.cpp

SOURCESCPP  += DIOStreamUSBConfig.cpp
SOURCESCPP  += DIOStreamIPLocalEnumDevices.cpp

SOURCESCPP  += DIOWebScraper.cpp
SOURCESCPP  += DIOWebHeader.cpp
SOURCESCPP  += DIOWebClient.cpp
SOURCESCPP  += DIOWebScraperCache.cpp
SOURCESCPP  += DIOWebScraperPublicIP.cpp

SOURCESCPP  += GRP2DCollisionDetection.cpp
SOURCESCPP  += GRP2DRendererPrimitives.cpp
SOURCESCPP  += GRPApplication.cpp
SOURCESCPP  += GRPAnimation.cpp
SOURCESCPP  += GRPArrayAlignTool.cpp
SOURCESCPP  += GRPBezierSpline.cpp
SOURCESCPP  += GRPBlendingPass.cpp
SOURCESCPP  += GRPBitmapSequence.cpp
SOURCESCPP  += GRPBufferOpenGLRender.cpp
SOURCESCPP  += GRPCamera.cpp
SOURCESCPP  += GRPColor.cpp
SOURCESCPP  += GRPConsole.cpp
SOURCESCPP  += GRPContext.cpp
SOURCESCPP  += GRPCubeCoords.cpp
SOURCESCPP  += GRPDeformer.cpp
SOURCESCPP  += GRPElement.cpp
SOURCESCPP  += GRPFactory.cpp
SOURCESCPP  += GRPFile3DGGF.cpp
SOURCESCPP  += GRPFile3D.cpp
SOURCESCPP  += GRPFile3DOBJ.cpp
SOURCESCPP  += GRPFile3DFBX.cpp
SOURCESCPP  += GRPFile3DXML.cpp
SOURCESCPP  += GRPFileBitmap.cpp
SOURCESCPP  += GRPFileBitmapTGA.cpp
SOURCESCPP  += GRPFileBitmapJPG.cpp
SOURCESCPP  += GRPFileBitmapPNG.cpp
SOURCESCPP  += GRPFileBitmapBMP.cpp
SOURCESCPP  += GRPFileTTF.cpp
SOURCESCPP  += GRPFontManager.cpp
SOURCESCPP  += GRPLight.cpp
SOURCESCPP  += GRPLoader.cpp
SOURCESCPP  += GRPLoaderInterface.cpp
SOURCESCPP  += GRPMatrix.cpp
SOURCESCPP  += GRPMaterial.cpp
SOURCESCPP  += GRPMaterialLibrary.cpp
SOURCESCPP  += GRPMappingProjectionCubic.cpp
SOURCESCPP  += GRPMappingProjection.cpp
SOURCESCPP  += GRPMappingProjectionCylinder.cpp
SOURCESCPP  += GRPMappingProjectionPlanar.cpp
SOURCESCPP  += GRPMesh.cpp
SOURCESCPP  += GRPNode.cpp
SOURCESCPP  += GRPObject.cpp
SOURCESCPP  += GRPObjectBuilder.cpp
SOURCESCPP  += GRPObjectBuilderAlgorithm.cpp
SOURCESCPP  += GRPObjectBuilderAlgorithmExtrude.cpp
SOURCESCPP  += GRPObjectBuilderAlgorithmLathe.cpp
SOURCESCPP  += GRPObjectBuilderAlgorithmTriangulationEar.cpp
SOURCESCPP  += GRPObjectBuilderAlgorithmStroke.cpp
SOURCESCPP  += GRPObjectLibrary.cpp
SOURCESCPP  += GRPOpenGL.cpp
SOURCESCPP  += GRPObserver.cpp
SOURCESCPP  += GRPPass.cpp
SOURCESCPP  += GRPPassManager.cpp
SOURCESCPP  += GRPPath.cpp
SOURCESCPP  += GRPProfiler.cpp
SOURCESCPP  += GRPUserDataContainer.cpp
SOURCESCPP  += GRPRenderer.cpp
SOURCESCPP  += GRPRenderTarget.cpp
SOURCESCPP  += GRPReflectionPass.cpp
SOURCESCPP  += GRPShaderLibrary.cpp
SOURCESCPP  += GRPShader.cpp
SOURCESCPP  += GRPScene.cpp
SOURCESCPP  += GRPSpline.cpp
SOURCESCPP  += GRPSkinning.cpp
SOURCESCPP  += GRPShaderDot.cpp
SOURCESCPP  += GRPScreen.cpp
SOURCESCPP  += GRPSubject.cpp
SOURCESCPP  += GRPShadowPass.cpp
SOURCESCPP  += GRPStencilPass.cpp
SOURCESCPP  += GRPSlotNumber.cpp
SOURCESCPP  += GRPTexture.cpp
SOURCESCPP  += GRPTextureEXT.cpp
SOURCESCPP  += GRPFont.cpp
SOURCESCPP  += GRPTextBox.cpp
SOURCESCPP  += GRPVisualDebugger.cpp
SOURCESCPP  += GRPVector.cpp
SOURCESCPP  += GRPViewport.cpp
SOURCESCPP  += GRPFrustum.cpp
SOURCESCPP  += GRPSettings.cpp
SOURCESCPP  += GRPPlane.cpp
SOURCESCPP  += GRPBackgroundPass.cpp
SOURCESCPP  += GRPStyleProcessorCSS.cpp
SOURCESCPP  += GRPSkyboxPass.cpp
SOURCESCPP  += GRPEnvMapPass.cpp
SOURCESCPP  += GRPViewportPass.cpp
SOURCESCPP  += GRPOverlayPass.cpp
SOURCESCPP  += GRPDepthPass.cpp
SOURCESCPP  += GRPRenderTargetPass.cpp
SOURCESCPP  += GRPHighDinamicRangePass.cpp
SOURCESCPP  += GRPWidget.cpp
SOURCESCPP  += GRPWidgetPage.cpp
SOURCESCPP  += GRPWidgetPass.cpp
SOURCESCPP  += GRPWidgetStyle.cpp

SOURCESCPP  += GRPLINUXFactory.cpp


ifneq (,$(findstring PHY_ACTIVE,$(FLAGS)))
SOURCESCPP	+= PHYEngine.cpp
endif

SOURCESCPP  += FBX.cpp


SOURCESCPP  += Hash.cpp
SOURCESCPP  += HashSHA1.cpp
SOURCESCPP  += HashCRC32.cpp
SOURCESCPP  += Cipher.cpp
SOURCESCPP  += CipherAES.cpp

SOURCESCPP  += CompressBase.cpp
SOURCESCPP  += CompressLZRW1KH.cpp
SOURCESCPP  += CompressLZW.cpp
SOURCESCPP  += CompressManager.cpp
SOURCESCPP  += CompressZIP.cpp
SOURCESCPP  += CompressGZ.cpp

SOURCESCPP  += INPButton.cpp
SOURCESCPP  += INPCursor.cpp
SOURCESCPP  += INPDevice.cpp
SOURCESCPP  += INPManager.cpp
SOURCESCPP  += INPPath.cpp
SOURCESCPP  += INPFactory.cpp

SOURCESCPP  += INPLINUXFactory.cpp


SOURCESCPP  += Main.cpp



ifneq (,$(findstring SND_ACTIVE,$(FLAGS)))
SOURCESCPP  += SNDFile.cpp
#SOURCESCPP  += SNDFileOGG.cpp
SOURCESCPP  += SNDFileFFMPEG.cpp
SOURCESCPP  += SNDLINUXResampler.cpp
SOURCESCPP  += SNDOpenALBuffer.cpp
SOURCESCPP  += SNDOpenALSource.cpp
SOURCESCPP  += SNDOpenALElement.cpp
SOURCESCPP  += SNDOpenALStreamElement.cpp
SOURCESCPP  += SNDOpenAL.cpp
SOURCESCPP  += SNDEvent.cpp
SOURCESCPP  += SNDElement.cpp
SOURCESCPP  += SNDLINUXFactory.cpp
SOURCESCPP  += SNDFactory.cpp
SOURCESCPP  += SNDCodecFFMPEG.cpp
SOURCESCPP  += SNDSource.cpp
SOURCESCPP  += SNDStreamInstance.cpp
SOURCESCPP  += SNDAnimationListener.cpp
SOURCESCPP  += SNDManager.cpp
endif

SOURCESCPP  += XFactory.cpp
SOURCESCPP  += XSleep.cpp
SOURCESCPP  += XApplication.cpp
SOURCESCPP  += XFileConfig.cpp
SOURCESCPP  += XBase.cpp
SOURCESCPP  += XBuffer.cpp
SOURCESCPP  += XBufferBits.cpp
SOURCESCPP  += XConsole.cpp
SOURCESCPP  += XDebug.cpp
SOURCESCPP  += XDir.cpp
SOURCESCPP  += XErrorMsg.cpp
SOURCESCPP  += XFile.cpp
SOURCESCPP  += XFileINI.cpp
SOURCESCPP  += XFileTXT.cpp
SOURCESCPP  += XFileXML.cpp
SOURCESCPP  += XFileZIP.cpp
SOURCESCPP  += XFileJSON.cpp
SOURCESCPP  += XFSMachine.cpp
SOURCESCPP  += XLanguage.cpp
SOURCESCPP  += XLog.cpp
SOURCESCPP  += XLoader.cpp
SOURCESCPP  += XMemory.cpp
SOURCESCPP  += XPath.cpp
SOURCESCPP  += XPathsManager.cpp
SOURCESCPP  += XPublisher.cpp
SOURCESCPP  += XScheduler.cpp
SOURCESCPP  += XSerialize.cpp
SOURCESCPP  += XString.cpp
SOURCESCPP  += XSystem.cpp
SOURCESCPP  += XThread.cpp
SOURCESCPP  += XTimer.cpp
SOURCESCPP  += XDateTime.cpp
SOURCESCPP  += XVariant.cpp
SOURCESCPP  += XInterpolator.cpp
SOURCESCPP  += XFString.cpp

SOURCESCPP  += DIOLINUXFactory.cpp
SOURCESCPP  += DIOLINUXStreamSPI.cpp
SOURCESCPP  += DIOLINUXStreamI2C.cpp
SOURCESCPP  += DIOLINUXPing.cpp
SOURCESCPP  += DIOLINUXURL.cpp
SOURCESCPP  += DIOLINUXStreamICMP.cpp


ifneq (,$(findstring VIDEO_ACTIVE,$(FLAGS)))
FLAGS += -D MEDIA_ACTIVE
endif

ifneq (,$(findstring SND_ACTIVE,$(FLAGS)))
FLAGS += -D MEDIA_ACTIVE
endif

ifneq (,$(findstring SND_ACTIVE,$(FLAGS)))
SOURCESCPP += MEDIAFile.cpp
SOURCESCPP += MEDIAFrameReaderLibAV.cpp
endif

ifeq "$(ARCHITECTURE)" "PC"
SOURCESCPP  += GRPLINUXScreenX11.cpp
SOURCESCPP  += GRPLINUXX11GLContext.cpp
SOURCESCPP  += INPLINUXDeviceKeyboardX11.cpp
SOURCESCPP  += INPLINUXDeviceMouseX11.cpp
SOURCESC    += glew.c
endif

ifeq "$(ARCHITECTURE)" "RASPBERRYPI"
SOURCESCPP  += GRPLINUXScreenDispman.cpp
SOURCESCPP  += GRPLINUXDispmanContext.cpp
SOURCESCPP  += INPLINUXDeviceKeyboardDirect.cpp
SOURCESCPP  += INPLINUXDeviceMouseDirect.cpp


ifneq (,$(findstring VIDEO_ACTIVE,$(FLAGS)))
SOURCESCPP  += VIDEOLINUXCodecH264ILClient.cpp

endif

endif

ifeq "$(ARCHITECTURE)" "ODROIDC1"
#SOURCESCPP += GRPLINUXScreenX11.cpp
#SOURCESCPP += GRPLINUXScreenX11GLES.cpp
#SOURCESCPP += INPLINUXDeviceKeyboardX11.cpp
#SOURCESCPP += INPLINUXDeviceMouseX11.cpp
SOURCESCPP  += GRPLINUXScreenFrameBuffer.cpp
SOURCESCPP  += GRPLINUXScreenFrameBufferGLES.cpp
SOURCESCPP  += INPLINUXDeviceKeyboardDirect.cpp
SOURCESCPP  += INPLINUXDeviceMouseDirect.cpp
endif

ifneq (,$(findstring VIDEO_ACTIVE,$(FLAGS)))
SOURCESCPP += VIDEOLINUXFactory.cpp
SOURCESCPP += VIDEOFactory.cpp
#SOURCESCPP += VIDEOH264FrameReader.cpp
SOURCESCPP += VIDEOCodecH264.cpp
SOURCESCPP += VIDEOPlayer.cpp

SOURCESCPP += MEDIAFrameReaderLibAV.cpp

#ifeq "$(ARCHITECTURE)" "PC"
SOURCESCPP += VIDEOCodecH264ffmpeg.cpp
#endif

endif

SOURCESCPP  += XLINUXFactory.cpp
SOURCESCPP  += XLINUXSleep.cpp
SOURCESCPP  += LINUXMain.cpp
SOURCESCPP  += XLINUXConsole.cpp
SOURCESCPP  += XLINUXDebug.cpp
SOURCESCPP  += XLINUXDir.cpp
SOURCESCPP  += XLINUXFile.cpp
SOURCESCPP  += XLINUXRand.cpp
SOURCESCPP  += XLINUXSystem.cpp
SOURCESCPP  += XLINUXThread.cpp
SOURCESCPP  += XLINUXTimer.cpp
SOURCESCPP  += XLINUXDateTime.cpp


#---- SOURCES C --------------------------------------------------------------------------------------------------

SOURCESC 		+= adler32.c
SOURCESC		+= compress.c
SOURCESC 		+= crc32.c
SOURCESC 		+= deflate.c
SOURCESC 		+= infback.c
SOURCESC 		+= inffast.c
SOURCESC 		+= inflate.c
SOURCESC 		+= inftrees.c
SOURCESC 		+= ioapi.c
SOURCESC 		+= trees.c
SOURCESC 		+= uncompr.c
SOURCESC 		+= unzip.c
SOURCESC 		+= zip.c
SOURCESC 		+= zutil.c

SOURCESC		+= jaricom.c
SOURCESC		+= jcapimin.c
SOURCESC		+= jcapistd.c
SOURCESC		+= jcarith.c
SOURCESC		+= jccoefct.c
SOURCESC		+= jccolor.c
SOURCESC		+= jcdctmgr.c
SOURCESC		+= jchuff.c
SOURCESC		+= jcinit.c
SOURCESC		+= jcmainct.c
SOURCESC		+= jcmarker.c
SOURCESC		+= jcmaster.c
SOURCESC		+= jcomapi.c
SOURCESC		+= jcparam.c
SOURCESC		+= jcprepct.c
SOURCESC		+= jcsample.c
SOURCESC		+= jctrans.c
SOURCESC		+= jdapimin.c
SOURCESC		+= jdapistd.c
SOURCESC		+= jdarith.c
SOURCESC		+= jdatadst.c
SOURCESC		+= jdatasrc.c
SOURCESC		+= jdcoefct.c
SOURCESC		+= jdcolor.c
SOURCESC		+= jddctmgr.c
SOURCESC		+= jdhuff.c
SOURCESC		+= jdinput.c
SOURCESC		+= jdmainct.c
SOURCESC		+= jdmarker.c
SOURCESC		+= jdmaster.c
SOURCESC		+= jdmerge.c
SOURCESC		+= jdpostct.c
SOURCESC		+= jdsample.c
SOURCESC		+= jdtrans.c
SOURCESC		+= jerror.c
SOURCESC		+= jfdctflt.c
SOURCESC		+= jfdctfst.c
SOURCESC		+= jfdctint.c
SOURCESC		+= jidctflt.c
SOURCESC		+= jidctfst.c
SOURCESC		+= jidctint.c
SOURCESC		+= jmemmgr.c
SOURCESC		+= jmemnobs.c
SOURCESC		+= jquant1.c
SOURCESC		+= jquant2.c
SOURCESC		+= jutils.c
     
SOURCESC 		+= png.c
SOURCESC 		+= pngerror.c
SOURCESC 		+= pngget.c
SOURCESC 		+= pngmem.c
SOURCESC 		+= pngpread.c
SOURCESC 		+= pngread.c
SOURCESC 		+= pngrio.c
SOURCESC 		+= pngrtran.c
SOURCESC 		+= pngrutil.c
SOURCESC 		+= pngset.c
SOURCESC 		+= pngtrans.c
SOURCESC 		+= pngwio.c
SOURCESC 		+= pngwrite.c
SOURCESC 		+= pngwtran.c
SOURCESC 		+= pngwutil.c
SOURCESC 	 	+= stb_vorbis.c
            
include ../../../../GEN/Platforms/Linux/makefile    
  
   

