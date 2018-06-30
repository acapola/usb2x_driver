##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=test
ConfigurationName      :=Debug
WorkspacePath          :=/home/user/dev/usb2x_driver
ProjectPath            :=/home/user/dev/usb2x_driver/test
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=user
Date                   :=24/06/18
CodeLitePath           :=/home/user/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="test.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)usb $(LibrarySwitch)usb-1.0 
ArLibs                 :=  "usb" "usb-1.0" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/test3.c$(ObjectSuffix) $(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/test2.c$(ObjectSuffix) $(IntermediateDirectory)/test1.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/test3.c$(ObjectSuffix): test3.c $(IntermediateDirectory)/test3.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/user/dev/usb2x_driver/test/test3.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/test3.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/test3.c$(DependSuffix): test3.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/test3.c$(ObjectSuffix) -MF$(IntermediateDirectory)/test3.c$(DependSuffix) -MM test3.c

$(IntermediateDirectory)/test3.c$(PreprocessSuffix): test3.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/test3.c$(PreprocessSuffix) test3.c

$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/user/dev/usb2x_driver/test/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c

$(IntermediateDirectory)/test2.c$(ObjectSuffix): test2.c $(IntermediateDirectory)/test2.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/user/dev/usb2x_driver/test/test2.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/test2.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/test2.c$(DependSuffix): test2.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/test2.c$(ObjectSuffix) -MF$(IntermediateDirectory)/test2.c$(DependSuffix) -MM test2.c

$(IntermediateDirectory)/test2.c$(PreprocessSuffix): test2.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/test2.c$(PreprocessSuffix) test2.c

$(IntermediateDirectory)/test1.c$(ObjectSuffix): test1.c $(IntermediateDirectory)/test1.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/user/dev/usb2x_driver/test/test1.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/test1.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/test1.c$(DependSuffix): test1.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/test1.c$(ObjectSuffix) -MF$(IntermediateDirectory)/test1.c$(DependSuffix) -MM test1.c

$(IntermediateDirectory)/test1.c$(PreprocessSuffix): test1.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/test1.c$(PreprocessSuffix) test1.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


