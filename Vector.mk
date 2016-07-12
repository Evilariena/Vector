##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Vector
ConfigurationName      :=Debug
WorkspacePath          := "/home/monika/Documents/workspace"
ProjectPath            := "/home/monika/Documents/workspace/Vector"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Monika
Date                   :=12/07/16
CodeLitePath           :="/home/monika/.codelite"
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
ObjectsFileList        :="Vector.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)gtest 
ArLibs                 :=  "gtest" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)~/Downloads/googletest-master/googletest 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -std=c++14 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/VectorTestSuite.cpp$(ObjectSuffix) $(IntermediateDirectory)/RandomAccessIteratorTestSuite.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/VectorTestSuite.cpp$(ObjectSuffix): VectorTestSuite.cpp $(IntermediateDirectory)/VectorTestSuite.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/monika/Documents/workspace/Vector/VectorTestSuite.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/VectorTestSuite.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/VectorTestSuite.cpp$(DependSuffix): VectorTestSuite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/VectorTestSuite.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/VectorTestSuite.cpp$(DependSuffix) -MM "VectorTestSuite.cpp"

$(IntermediateDirectory)/VectorTestSuite.cpp$(PreprocessSuffix): VectorTestSuite.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/VectorTestSuite.cpp$(PreprocessSuffix) "VectorTestSuite.cpp"

$(IntermediateDirectory)/RandomAccessIteratorTestSuite.cpp$(ObjectSuffix): RandomAccessIteratorTestSuite.cpp $(IntermediateDirectory)/RandomAccessIteratorTestSuite.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/monika/Documents/workspace/Vector/RandomAccessIteratorTestSuite.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/RandomAccessIteratorTestSuite.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/RandomAccessIteratorTestSuite.cpp$(DependSuffix): RandomAccessIteratorTestSuite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/RandomAccessIteratorTestSuite.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/RandomAccessIteratorTestSuite.cpp$(DependSuffix) -MM "RandomAccessIteratorTestSuite.cpp"

$(IntermediateDirectory)/RandomAccessIteratorTestSuite.cpp$(PreprocessSuffix): RandomAccessIteratorTestSuite.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/RandomAccessIteratorTestSuite.cpp$(PreprocessSuffix) "RandomAccessIteratorTestSuite.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


